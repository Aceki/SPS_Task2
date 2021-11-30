#pragma once 

#include <unordered_set>
#include <vector>

#include <QObject>
#include <QTimer>

#include "exceptions.h"
#include "cell.h"

namespace Minesweeper
{
    class Game : public QObject
    {
        Q_OBJECT

    public:
        enum Difficulty 
        {
            Hard = 4,
            Normal = 6,
            Easy = 8
        };

        enum EndStatus
        {
            Loose,
            Win
        };

        Game(int n, int m, Difficulty difficulty, QObject* parent = nullptr);
        const Cell& cell(int i, int j) const;
        int n() const;
        int m() const;
        bool isGameStart() const;
        bool isGameEnd() const;
        int flagsCount() const;
        int time() const;

    signals:
        void gameStarted();
        void gameEnded(EndStatus);
        void cellUncovered(int i, int j);
        void cellMarkerSwitched(int i, int j, Cell::Marker marker);
        void flagsCountChanged(int newValue);
        void timeChanged(int newValue);
        void wasReset();

    public slots:
        void uncoverCell(int i, int j);
        void switchCellMarker(int i, int j);
        void uncoverCellsAround(int i, int j);
        void reset();

    private:
        void startGame(int startI, int startJ);
        void endGame(EndStatus);
        void uncoverRegion(int i, int j);
        void uncoverMinedCells();
        void initializeField();
        std::unordered_set<int> generateMinedCellsIndices() const;
        int coordToIndex(int i, int j) const;
        std::vector<std::pair<int, int>> getNeighboursCoords(int i, int j) const;

        int m_n;
        int m_m;
        Difficulty m_difficulty;
        std::vector<Cell> m_field;
        QTimer* m_timer;
        int m_startI;
        int m_startJ;
        int m_time = 0;
        int m_minesCount = 0;
        int m_flagsCount = 0;
        int m_safeCellsCount = 0;
        bool m_isGameStart = false;
        bool m_isGameEnd = false;
    };

    inline int Game::n() const 
    {
        return m_n;
    }

    inline int Game::m() const
    {
        return m_m;
    }

    inline bool Game::isGameStart() const
    {
        return m_isGameStart;
    }

    inline bool Game::isGameEnd() const
    {
        return m_isGameEnd;
    }

    inline int Game::flagsCount() const
    {
        return m_flagsCount;
    }

    inline int Game::time() const
    {
        return m_time;
    }

    inline const Cell& Game::cell(int i, int j) const 
    {
        if (i < 0 || i >= m_n || j < 0 || j >= m_m)
            throw Minesweeper::OutOfBounds();

        return m_field[coordToIndex(i, j)];
    }

    inline int Game::coordToIndex(int i, int j) const
    {
        return i * m_m + j;
    }
}
