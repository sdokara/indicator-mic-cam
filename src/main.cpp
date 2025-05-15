#include "traymanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }

    TrayManager trayManager;
    trayManager.start();

    return application.exec();
}
