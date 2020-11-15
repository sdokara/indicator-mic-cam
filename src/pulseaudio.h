#ifndef PULSEAUDIO_H
#define PULSEAUDIO_H

#include <string>
#include <list>
#include <pulse/pulseaudio.h>

enum state {
    CONNECTING,
    CONNECTED,
    ERROR
};
typedef enum state state_t;

struct Device {
    uint32_t index;
    const char* description;
    pa_source_state_t state;
};
inline bool operator == (const Device& dev1, const Device& dev2) {
    return dev1.index == dev2.index;
}

class PulseAudio {
private:
    pa_mainloop* mainloop;
    pa_mainloop_api* mainloop_api;
    pa_context* context;
    state_t state;
    int retval;

    void iterate(pa_operation* op);

public:
    PulseAudio(std::string name);
    ~PulseAudio();

    std::list<Device> getSources();

    friend void state_cb(pa_context* context, void* raw);
};

#endif // PULSEAUDIO_H
