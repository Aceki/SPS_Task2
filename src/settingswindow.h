#pragma once

#include <QtWidgets>

#include "gamewindow.h"

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent = nullptr);

private:
    GameSettings m_settings = GameSettings();
};
