#pragma once

#include <QMainWindow>

#include "Minesweeper/game.h"

class Field;

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

private slots:
    void showMessage(QString message);

private:
    Field* m_field;
    GameSettings m_settings;
};
