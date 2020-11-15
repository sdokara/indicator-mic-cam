#include <QDebug>

#include "pulsecallbacks.h"
#include "pulseaudio.h"

void state_cb(pa_context* context, void* raw) {
    PulseAudio* pulse = (PulseAudio*) raw;
    switch(pa_context_get_state(context))
    {
    case PA_CONTEXT_READY:
        pulse->state = CONNECTED;
        break;
    case PA_CONTEXT_FAILED:
        pulse->state = ERROR;
        break;
    case PA_CONTEXT_UNCONNECTED:
    case PA_CONTEXT_AUTHORIZING:
    case PA_CONTEXT_SETTING_NAME:
    case PA_CONTEXT_CONNECTING:
    case PA_CONTEXT_TERMINATED:
        break;
    }
}

void source_list_cb(pa_context* UNUSED(context), const pa_source_info *i, int eol, void *raw) {
    if (eol != 0) {
        return;
    }
    std::list<Device>* devices = (std::list<Device>*) raw;
    Device device = {i->index, i->description, i->state};
    devices->push_back(device);
}
