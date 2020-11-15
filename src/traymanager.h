#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QObject>
#include <QThread>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>

#include "pulseaudio.h"

class TrayManager: public QThread {
Q_OBJECT
private:
    QSystemTrayIcon *trayIcon;
    PulseAudio *pulseAudio;
protected:
    void run();
public:
    TrayManager();
    ~TrayManager();
};

#endif // TRAYMANAGER_H
