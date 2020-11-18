#ifndef DEVICE_H
#define DEVICE_H

#include <list>
#include <QString>


class Device {
private:
    unsigned int index;
    QString description;
    bool inUse;

public:
    Device(unsigned int index, QString description, bool inUse):
        index(index), description(description), inUse(inUse) {}

    Device(const Device& device):
        Device(device.index, device.description, device.inUse) {}

    unsigned int getIndex() const {
        return index;
    }
    QString getDescription() const {
        return description;
    }
    bool isInUse() const {
        return inUse;
    }

    void setIndex(unsigned int index) {
        this->index = index;
    }
    void setDescription(QString description) {
        this->description = description;
    }
    void setInUse(bool inUse) {
        this->inUse = inUse;
    }

    friend bool operator == (const Device& device1, const Device& device2);
};

inline bool operator == (const Device& device1, const Device& device2) {
    return device1.description == device2.description;
}


class SourceSupplier {
public:
    virtual std::list<Device> getSources() = 0;
};

#endif // DEVICE_H
