#pragma once

#include <QtWidgets>

#include <Minesweeper/game.h>

class Field : public QFrame 
{
    Q_OBJECT

public:
    Field(int n, int m, QWidget* parent = nullptr);

signals:
    void loose();
    void win();
    void flagsCountChanged(int newValue);
    void timeChanged(int newValue);

public slots:
    void reset();

private:
    int m_n;
    int m_m;
    QGridLayout* m_buttonsGrid = nullptr;
    Minesweeper::Game* m_game = nullptr;
};
