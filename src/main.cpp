#include "traymanager.h"


int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
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
