#include <iostream>

#include <QObject>
#include <QtWidgets>

#include "Minesweeper/game.h"
#include "gamewindow.h"
#include "field.h"

GameWindow::GameWindow(QWidget* parent, GameSettings settings) 
    : QMainWindow(parent), m_settings(settings)
{
    this->setWindowTitle("Minesweeper");

    int width = 30 * m_settings.m;
    int height = 35 * m_settings.n;
    setFixedSize(width, height);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    m_field = new Field(m_settings.n, m_settings.m, this);

    QVBoxLayout* generalLayout = new QVBoxLayout(this);

    QHBoxLayout* labelsLayout = new QHBoxLayout(this);

    QLabel* flagsLabel = new QLabel(this);
    flagsLabel->setText("Flags: 0");
    labelsLayout->addWidget(flagsLabel);
    connect(m_field, &Field::flagsCountChanged, flagsLabel, [flagsLabel](int newValue) { 
        flagsLabel->setText(QStringLiteral("Flags: ") + QString::number(newValue));
    });

    QLabel* timeLabel = new QLabel(this);
    timeLabel->setText("Time: 0");
    timeLabel->setAlignment(Qt::AlignRight);
    connect(m_field, &Field::timeChanged, timeLabel, [timeLabel](int newValue) {
        timeLabel->setText(QStringLiteral("Time: ") + QString::number(newValue));
    });
    labelsLayout->addWidget(timeLabel);

    generalLayout->addLayout(labelsLayout);

    generalLayout->addWidget(m_field);

    QPushButton* resetButton = new QPushButton("Reset", this);

    connect(resetButton, &QPushButton::clicked, m_field, &Field::reset);

    generalLayout->QLayout::addWidget(resetButton);

    connect(m_field, &Field::loose, [this]() { showMessage(QStringLiteral("Вы проиграли =(")); });
    connect(m_field, &Field::win, [this]() { showMessage(QStringLiteral("Вы выиграли =)")); });

    centralWidget->setLayout(generalLayout);
}

void GameWindow::showMessage(QString message)
{
    QMessageBox* winMessageBox = new QMessageBox(this);
    winMessageBox->setText(message);
    winMessageBox->setWindowTitle(QStringLiteral("Message"));

    winMessageBox->show();

    connect(winMessageBox, &QMessageBox::buttonClicked, m_field, &Field::reset);
}
