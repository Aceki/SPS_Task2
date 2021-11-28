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

    Field* field = new Field(m_settings.n, m_settings.m, this);

    QVBoxLayout* generalLayout = new QVBoxLayout(this);

    QHBoxLayout* labelsLayout = new QHBoxLayout(this);

    QLabel* flagsLabel = new QLabel(this);
    flagsLabel->setText("Flags: 0");
    labelsLayout->addWidget(flagsLabel);
    connect(field, &Field::flagsCountChanged, flagsLabel, [flagsLabel](int newValue) { 
        flagsLabel->setText(QStringLiteral("Flags: ") + QString::number(newValue));
    });

    QLabel* timeLabel = new QLabel(this);
    timeLabel->setText("Time: 0");
    timeLabel->setAlignment(Qt::AlignRight);
    connect(field, &Field::timeChanged, timeLabel, [timeLabel](int newValue) {
        timeLabel->setText(QStringLiteral("Time: ") + QString::number(newValue));
    });
    labelsLayout->addWidget(timeLabel);

    generalLayout->addLayout(labelsLayout);

    generalLayout->addWidget(field);

    QPushButton* resetButton = new QPushButton("Reset", this);

    connect(resetButton, &QPushButton::clicked, field, &Field::reset);

    generalLayout->QLayout::addWidget(resetButton);

    connect(field, &Field::loose, [this, field] {  
        QMessageBox* looseMessageBox = new QMessageBox(this);
        looseMessageBox->setText("Вы проиграли =(");
        looseMessageBox->setWindowTitle("Message");

        looseMessageBox->show();

        connect(looseMessageBox, &QMessageBox::buttonClicked, field, &Field::reset);
    });

    connect(field, &Field::win, [this, field] {  
        QMessageBox* winMessageBox = new QMessageBox(this);
        winMessageBox->setText("Вы выиграли =)");
        winMessageBox->setWindowTitle("Message");

        winMessageBox->show();

        connect(winMessageBox, &QMessageBox::buttonClicked, field, &Field::reset);
    });

    centralWidget->setLayout(generalLayout);
}
