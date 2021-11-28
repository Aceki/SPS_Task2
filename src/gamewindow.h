#pragma once

#include <QMainWindow>

#include "Minesweeper/game.h"

struct GameSettings
{
    int n = 9;
    int m = 9;
};

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr, GameSettings settings = GameSettings());

private:
    GameSettings m_settings;
};
