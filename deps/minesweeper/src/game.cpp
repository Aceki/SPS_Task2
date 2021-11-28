#include <unordered_set>
#include <stack>
#include <cstdlib>
#include <cassert>
#include <ctime>

#include "game.h"

Minesweeper::Game::Game(int n, int m, Minesweeper::Game::Difficulty difficulty, QObject* parent) 
    : QObject(parent), m_n(n), m_m(m), m_difficulty(difficulty), m_field() 
{
    constexpr int minN = 5;
    constexpr int minM = 5;

    if (m_n < minN || m_m < minM)
        throw Minesweeper::RangeError("Field sizes should be positive and greater than one.");

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, [this]{ 
        m_time++;

        this->emit timeChanged(m_time);
    });

    m_field.reserve(m_n * m_m);

    reset();
}

void Minesweeper::Game::startGame(int startI, int startJ) 
{
    m_startI = startI;
    m_startJ = startJ;
    m_isGameStart = true;

    initializeField();

    m_timer->start();

    emit flagsCountChanged(m_flagsCount);
    emit gameStarted();
}

void Minesweeper::Game::uncoverCell(int i, int j)
{
    if (i < 0 || i >= m_n || j < 0 || j >= m_m)
        throw OutOfBounds();

    if (m_isGameEnd)
        return;

    if (!m_isGameStart)
        startGame(i, j);

    Cell& cell = m_field[coordToIndex(i, j)];

    if (cell.isCovered() && cell.marker() == Cell::None)
    {
        cell.uncover();

        emit cellUncovered(i, j);

        if (cell.isMined())
            endGame(EndStatus::Loose);
        else
        {
            m_safeCellsCount--;

            if (m_safeCellsCount == 0)
                endGame(EndStatus::Win);
            else
            {
                if (cell.value() == 0)
                    uncoverCellsAround(i, j);
            }
        }

    }
}

void Minesweeper::Game::switchCellMarker(int i, int j)
{
    if (i < 0 || i >= m_n || j < 0 || j >= m_m)
        throw OutOfBounds();

    Cell& cell = m_field[coordToIndex(i, j)];

    if (cell.isCovered())
    {
        if (cell.marker() == Cell::Flag)
        {
            m_flagsCount++;

            emit flagsCountChanged(m_flagsCount);
        }

        cell.switchMarker();

        if (cell.marker() == Cell::Flag)
        {
            m_flagsCount--;

            emit flagsCountChanged(m_flagsCount);
        }

        emit cellMarkerSwitched(i, j, cell.marker());
    }
}

void Minesweeper::Game::uncoverCellsAround(int i, int j)
{
    int cellsWithFlag = 0;

    Cell& cell = m_field[coordToIndex(i, j)];

    if (!cell.isCovered())
    {
        std::vector<std::pair<int, int>> neighbours = getNeighboursCoords(i, j);
        std::vector<std::pair<int, int>> neighboursToUncover;
        for (std::pair<int, int>& neighbour : neighbours)
        {
            Cell& neighbouringCell = m_field[coordToIndex(neighbour.first, neighbour.second)];
            
            if (neighbouringCell.marker() == Cell::Flag)
                cellsWithFlag++;
            else
                neighboursToUncover.push_back(neighbour);
        }

        if (cellsWithFlag == cell.value())
        {
            for (std::pair<int, int>& neighbour : neighboursToUncover)
                uncoverCell(neighbour.first, neighbour.second);
        }
    }
}

std::vector<std::pair<int, int>> Minesweeper::Game::getNeighboursCoords(int i, int j) const
{
    std::vector<std::pair<int, int>> allNeighboursCoords = {
        { i - 1, j + 1 },
        { i, j + 1 },
        { i + 1, j + 1 },
        { i + 1, j },
        { i + 1, j - 1 },
        { i, j - 1 },
        { i - 1, j - 1 },
        { i - 1, j }
    };

    std::vector<std::pair<int, int>> inBoundsNeighboursCoords;
    inBoundsNeighboursCoords.reserve(allNeighboursCoords.size());

    for (std::pair<int, int>& coord : allNeighboursCoords)
    {
        if (coord.first >= 0 && coord.first < m_n 
         && coord.second >= 0 && coord.second < m_m)
            inBoundsNeighboursCoords.push_back(coord);
    }
    
    return inBoundsNeighboursCoords;
}

void Minesweeper::Game::endGame(EndStatus status)
{
    m_isGameStart = false;
    m_isGameEnd = true;

    m_timer->stop();

    uncoverMinedCells();

    emit gameEnded(status);
}

void Minesweeper::Game::uncoverMinedCells()
{
    for (Cell& cell : m_field)
    {
        if (cell.isMined())
        {
            cell.uncover();

            emit cellUncovered(cell.i(), cell.j());
        }
    }
}

void Minesweeper::Game::initializeField()
{
    std::unordered_set<int> minedIndices = generateMinedCellsIndices();

    for (int i = 0; i < m_n; i++)
    {
        for (int j = 0; j < m_m; j++)
        {
            int minedNeighbours = 0;
            std::vector<std::pair<int, int>> neighbours = getNeighboursCoords(i, j);
            for (std::pair<int, int>& neighbour : neighbours)
            {
                if (minedIndices.find(coordToIndex(neighbour.first, neighbour.second)) != minedIndices.end())
                    minedNeighbours++;
            }

            bool mined = minedIndices.find(coordToIndex(i, j)) != minedIndices.end();
            m_field.push_back(Cell(i, j, minedNeighbours, mined));
        }
    }
}

void Minesweeper::Game::reset() 
{
    m_timer->stop();

    m_isGameStart = false;
    m_isGameEnd = false;
    m_minesCount = (m_n * m_m) / m_difficulty; 
    m_flagsCount = m_minesCount;
    m_safeCellsCount = (m_n * m_m) - m_minesCount;
    m_time = 0;
    m_field.clear();

    emit timeChanged(0);
    emit flagsCountChanged(0);
    emit wasReset();
}

std::unordered_set<int> Minesweeper::Game::generateMinedCellsIndices() const
{
    int startIndex = coordToIndex(m_startI, m_startJ);
    std::unordered_set<int> minedIndices;

    int cellsCount = m_n * m_m;
    int c = m_minesCount;
    while (c > 0)
    {
        int randIndex = std::rand() % cellsCount;

        if (randIndex != startIndex && minedIndices.find(randIndex) == minedIndices.end())
        {
            minedIndices.insert(randIndex);
            c--;
        }
    }

    return minedIndices;
}

