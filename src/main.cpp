#include <QApplication>

#include "settingswindow.h"

int main(int argc, char* argv[]) 
{
    QApplication app(argc, argv);

    SettingsWindow settingsWindow;

    settingsWindow.show();

    return app.exec();
}
