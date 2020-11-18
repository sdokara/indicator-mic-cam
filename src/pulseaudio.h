#ifndef PULSEAUDIO_H
#define PULSEAUDIO_H

#include <string>
#include <list>
#include <pulse/pulseaudio.h>

#include "device.h"

enum state {
    CONNECTING,
    CONNECTED,
    ERROR
};
typedef enum state state_t;


class PulseAudio: public SourceSupplier {
private:
    pa_mainloop* mainloop;
    pa_mainloop_api* mainloop_api;
    pa_context* context;
    state_t state;
    int retval;

    void iterate(pa_operation* op);

public:
    PulseAudio(std::string name);
    virtual ~PulseAudio();

    virtual std::list<Device> getSources() final;

    friend void pa_state_cb(pa_context* context, void* raw);
};


void pa_state_cb(pa_context* context, void* raw);
void pa_source_list_cb(pa_context* context, const pa_source_info *i, int eol, void *raw);

#endif // PULSEAUDIO_H
