#ifndef WEBCAMERA_H
#define WEBCAMERA_H

#include <list>
#include <QString>
#include <QDir>

#include "device.h"


class WebCamera: public SourceSupplier {
public:
    WebCamera();
    virtual ~WebCamera();

    static QString readProperty(QFileInfo dir, QString property);
    static bool isInUse(QString dev);

    virtual std::list<Device> getSources() final;
};

#endif // WEBCAMERA_H
