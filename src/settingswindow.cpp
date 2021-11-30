#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Settings");

    setFixedSize(200, 200);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* verticalLayout = new QVBoxLayout(this);

    QSpinBox* nSpinBox = new QSpinBox(this);
    nSpinBox->setMinimum(5);
    nSpinBox->setMaximum(30);
    nSpinBox->setDisabled(true);
    connect(nSpinBox, &QSpinBox::valueChanged, [this] (int value) {
        m_settings.n = value;
    });
    QSpinBox* mSpinBox = new QSpinBox(this);
    mSpinBox->setMinimum(5);
    mSpinBox->setMaximum(30);
    mSpinBox->setDisabled(true);
    connect(mSpinBox, &QSpinBox::valueChanged, [this] (int value) {
        m_settings.m = value;
    });

    QRadioButton* easyRadioButton = new QRadioButton("9x9", this);
    connect(easyRadioButton, &QRadioButton::toggled, [this] (bool checked) {
        if (checked)
        {
            m_settings.n = 9;
            m_settings.m = 9;
        }
    });
    easyRadioButton->toggle();
    QRadioButton* normalRadioButton = new QRadioButton("16x16", this);
    connect(normalRadioButton, &QRadioButton::toggled, [this] (bool checked) {
        if (checked)
        {
            m_settings.n = 16;
            m_settings.m = 16;
        }
    });
    QRadioButton* hardRadioButton = new QRadioButton("16x30", this);
    connect(hardRadioButton, &QRadioButton::toggled, [this] (bool checked) {
        if (checked)
        {
            m_settings.n = 16;
            m_settings.m = 30;
        }
    });
    QRadioButton* customRadioButton = new QRadioButton("custom", this);
    connect(customRadioButton, &QRadioButton::toggled, [this, nSpinBox, mSpinBox] (bool checked) {
        if (checked == true)
        {
            nSpinBox->setEnabled(true);
            m_settings.n = nSpinBox->value();
            mSpinBox->setEnabled(true);
            m_settings.m = mSpinBox->value();
        }
        else
        {
            nSpinBox->setEnabled(false);
            mSpinBox->setEnabled(false);
        }
    });

    QHBoxLayout* customSizeLayout = new QHBoxLayout(this);


    QPushButton* startButton = new QPushButton("Start", this);
    connect(startButton, &QPushButton::clicked, [this] {
        GameWindow* gameWindow = new GameWindow(nullptr, m_settings);

        gameWindow->show();
    });

    customSizeLayout->addWidget(nSpinBox);
    customSizeLayout->addWidget(mSpinBox);

    verticalLayout->addWidget(easyRadioButton);
    verticalLayout->addWidget(normalRadioButton);
    verticalLayout->addWidget(hardRadioButton);
    verticalLayout->addWidget(customRadioButton);
    verticalLayout->addLayout(customSizeLayout);
    verticalLayout->addWidget(startButton);

    centralWidget->setLayout(verticalLayout);
}
