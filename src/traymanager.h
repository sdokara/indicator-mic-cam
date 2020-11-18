#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QObject>
#include <QThread>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>

#include "pulseaudio.h"
#include "webcamera.h"


class TrayManager: public QThread {
    Q_OBJECT

private:
    QSystemTrayIcon *micTrayIcon;
    QSystemTrayIcon *camTrayIcon;
    PulseAudio *pulseAudio;
    WebCamera *webCamera;

    void refresh(SourceSupplier* supplier, std::list<Device>& oldInUseDevices, QSystemTrayIcon* trayIcon);

protected:
    void run();

public:
    TrayManager();
    ~TrayManager();
};

#endif // TRAYMANAGER_H
