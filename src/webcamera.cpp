#include "webcamera.h"


WebCamera::WebCamera() {}
WebCamera::~WebCamera() {}

QString WebCamera::readProperty(QFileInfo dir, QString property) {
    QFile file(dir.absoluteFilePath() + "/" + property);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw "Failed reading name";
    }
    QByteArray data = file.readAll();
    return QString(data).replace("\n", "").trimmed();
}

bool WebCamera::isInUse(QString dev) {
    QString command("fuser /dev/" + dev + " > /dev/null");
    return system(command.toUtf8().constData()) == 0;
}

std::list<Device> WebCamera::getSources() {
    std::list<Device> devices;
    QDir directory("/sys/class/video4linux");
    QFileInfoList dirs = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (QFileInfo &dir : dirs) {
        int index = readProperty(dir, "index").toInt();
        QString name = readProperty(dir, "name");
        bool inUse = isInUse(dir.baseName());
        Device device(index, name, inUse);
        devices.push_back(device);
    }
    return devices;
}
