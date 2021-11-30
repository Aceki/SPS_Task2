#include <iostream>

#include <QtWidgets>

#include <Minesweeper/cell.h>

#include "field.h"
#include "cell.h"

Field::Field(int n, int m, QWidget* parent) 
    : QFrame(parent), m_n(n), m_m(m)
{
    const char* noneString = " ";
    const char* flagString = "F";
    const char* questionString = "?";
    const char* mineString = "*";

    m_game = new Minesweeper::Game(n, m, Minesweeper::Game::Normal, this);

    m_buttonsGrid = new QGridLayout(this);
    m_buttonsGrid->setSpacing(0);

    for (int i = 0; i < m_game->n(); i++) 
    {
        for (int j = 0; j < m_game->m(); j++)
        {
            Cell* cellButton = new Cell(this);
            cellButton->setText(noneString);

            connect(cellButton, &Cell::leftMouseButtonClicked, m_game, [i, j, this] { m_game->uncoverCell(i, j); });

            connect(cellButton, &Cell::rightMouseButtonClicked, m_game, [i, j, this] { m_game->switchCellMarker(i, j); });

            connect(cellButton, &Cell::bothMouseButtonsClicked, m_game, [i, j, this] { m_game->uncoverCellsAround(i, j); });

            connect(cellButton, &Cell::leftMouseButtonDoubleClicked, m_game, [i, j, this] { m_game->uncoverCellsAround(i, j); });
            
            m_buttonsGrid->addWidget(cellButton, i, j);
        }
    }

    connect(m_game, &Minesweeper::Game::cellUncovered, [this, noneString, mineString](int i, int j) {
        Cell* cellButton = qobject_cast<Cell*>(m_buttonsGrid->itemAtPosition(i, j)->widget());
        const Minesweeper::Cell& cell = m_game->cell(i, j);

        cellButton->setDisabled(true);

        if (cell.isMined())
            cellButton->setText(mineString);
        else if (cell.value() > 0)
            cellButton->setText(QString::number(cell.value()));
        else
            cellButton->setText(noneString);
    });

    connect(m_game, &Minesweeper::Game::cellMarkerSwitched, [this, noneString, flagString, questionString]
            (int i, int j, Minesweeper::Cell::Marker marker) {
        Cell* cellButton = qobject_cast<Cell*>(m_buttonsGrid->itemAtPosition(i, j)->widget());

        if (marker == Minesweeper::Cell::Flag)
            cellButton->setText(flagString);
        else if (marker == Minesweeper::Cell::Question)
            cellButton->setText(questionString);
        else 
            cellButton->setText(noneString);
    });

    connect(m_game, &Minesweeper::Game::timeChanged, [this](int newValue) { this->emit timeChanged(newValue); });

    connect(m_game, &Minesweeper::Game::flagsCountChanged, [this](int newValue) { this->emit flagsCountChanged(newValue); });

    connect(m_game, &Minesweeper::Game::gameEnded, [this](Minesweeper::Game::EndStatus status) {
        if (status == Minesweeper::Game::EndStatus::Win)
            this->emit win();
        else
            this->emit loose();
    });

    connect(m_game, &Minesweeper::Game::wasReset, [this, noneString] {
        for (int i = 0; i < m_buttonsGrid->count(); i++)
        {
            QPushButton* button = qobject_cast<QPushButton*>(m_buttonsGrid->itemAt(i)->widget());

            button->setText(noneString);

            button->setDisabled(false);
        }
    });
}

void Field::reset() 
{
    this->m_game->reset();
}

