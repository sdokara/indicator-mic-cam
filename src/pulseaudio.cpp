#include <QtDebug>

#include "pulseaudio.h"
#include "unused.h"


PulseAudio::PulseAudio(std::string clientName) {
    mainloop = pa_mainloop_new();
    mainloop_api = pa_mainloop_get_api(mainloop);
    context = pa_context_new(mainloop_api, clientName.c_str());
    pa_context_set_state_callback(context, &pa_state_cb, this);

    state = CONNECTING;
    if (pa_context_connect(context, NULL, PA_CONTEXT_NOFLAGS, NULL) < 0) {
        throw "Connection error";
    }
    while (state == CONNECTING) {
        if (pa_mainloop_iterate(mainloop, 1, &retval) < 0) {
            throw "Mainloop error";
        }
    }
    if (state == ERROR) {
        throw "Connection error";
    }
}

PulseAudio::~PulseAudio() {
    pa_context_set_state_callback(context, NULL, NULL);
    if (state == CONNECTED) {
        pa_context_disconnect(context);
    }
    pa_context_unref(context);
    pa_mainloop_free(mainloop);
}

void PulseAudio::iterate(pa_operation* op) {
    while (pa_operation_get_state(op) == PA_OPERATION_RUNNING) {
        pa_mainloop_iterate(mainloop, 1, &retval);
    }
}

std::list<Device> PulseAudio::getSources() {
    std::list<Device> devices;
    pa_operation* op = pa_context_get_source_info_list(context, &pa_source_list_cb, &devices);
    iterate(op);
    pa_operation_unref(op);
    return devices;
}


void pa_state_cb(pa_context* context, void* raw) {
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

void pa_source_list_cb(pa_context* UNUSED(context), const pa_source_info *i, int eol, void *raw) {
    if (eol != 0) {
        return;
    }
    std::list<Device>* devices = (std::list<Device>*) raw;
    if (i->monitor_of_sink == PA_INVALID_INDEX) {
        Device device(i->index, i->description, i->state == PA_SOURCE_RUNNING);
        devices->push_back(device);
    }
}
