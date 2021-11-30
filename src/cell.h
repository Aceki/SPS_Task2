#pragma once

#include <QtWidgets>

class Cell : public QPushButton
{
    Q_OBJECT

public:
    explicit Cell(QWidget* parent = nullptr);

    bool event(QEvent* event) override;

signals:
    void leftMouseButtonClicked();
    void rightMouseButtonClicked();
    void leftMouseButtonDoubleClicked();
    void bothMouseButtonsClicked();
};
