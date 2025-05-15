#include <QDebug>
#include <QMenu>

#include "traymanager.h"
#include <pulse/pulseaudio.h>


TrayManager::TrayManager() {
    this->micTrayIcon = new QSystemTrayIcon(QIcon::fromTheme("audio-input-microphone"));
    this->micTrayIcon->setContextMenu(new QMenu());

    this->camTrayIcon = new QSystemTrayIcon(QIcon::fromTheme("camera-web"));
    this->camTrayIcon->setContextMenu(new QMenu());

    this->pulseAudio = new PulseAudio("indicator-mic-cam");
    this->webCamera = new WebCamera();
}

TrayManager::~TrayManager() {
    delete this->micTrayIcon;
    delete this->pulseAudio;
    delete this->webCamera;
}

void TrayManager::run() {
    std::list<Device> oldInUseAudioDevices;
    std::list<Device> oldInUseVideoDevices;
    while (true) {
        msleep(1000);
        refresh(pulseAudio, oldInUseAudioDevices, micTrayIcon);
        refresh(webCamera, oldInUseVideoDevices, camTrayIcon);
    }
}

void TrayManager::refresh(SourceSupplier* supplier, std::list<Device>& oldInUseDevices, QSystemTrayIcon* trayIcon) {
    std::list<Device> devices = supplier->getSources();
    std::list<Device> inUseDevices;
    for (Device &device : devices) {
        if (device.isInUse()) {
            inUseDevices.push_back(device);
        }
    }
    if (oldInUseDevices != inUseDevices) {
        trayIcon->contextMenu()->clear();
        for (Device &device : inUseDevices) {
            trayIcon->contextMenu()->addAction(new QAction(device.getDescription()));
        }
    }
    trayIcon->setVisible(!inUseDevices.empty());
    oldInUseDevices = inUseDevices;
}
