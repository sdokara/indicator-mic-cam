#include <QDebug>
#include <QMenu>

#include "traymanager.h"
#include <pulse/pulseaudio.h>

TrayManager::TrayManager() {
    this->trayIcon = new QSystemTrayIcon(QIcon::fromTheme("audio-input-microphone"));
    this->trayIcon->setContextMenu(new QMenu());
    this->pulseAudio = new PulseAudio("indicator-mic-cam");
}

TrayManager::~TrayManager() {
    delete this->trayIcon;
    delete this->pulseAudio;
}

void TrayManager::run() {
    std::list<Device> oldInUseDevices;
    while (true) {
        this->msleep(1000);
        std::list<Device> devices = this->pulseAudio->getSources();
        std::list<Device> inUseDevices;
        for (Device device : devices) {
            if (device.state == PA_SOURCE_RUNNING) {
                inUseDevices.push_back(device);
            }
        }
        if (oldInUseDevices != inUseDevices) {
            this->trayIcon->contextMenu()->clear();
            for (Device device : inUseDevices) {
                this->trayIcon->contextMenu()->addAction(new QAction(device.description));
            }
        }
        this->trayIcon->setVisible(inUseDevices.size() > 0);
        oldInUseDevices = inUseDevices;
    }
}
