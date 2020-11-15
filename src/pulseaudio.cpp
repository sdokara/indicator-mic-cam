#include <QtDebug>

#include "pulseaudio.h"
#include "pulsecallbacks.h"

PulseAudio::PulseAudio(std::string clientName) {
    mainloop = pa_mainloop_new();
    mainloop_api = pa_mainloop_get_api(mainloop);
    context = pa_context_new(mainloop_api, clientName.c_str());
    pa_context_set_state_callback(context, &state_cb, this);

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
    pa_operation* op = pa_context_get_source_info_list(context, &source_list_cb, &devices);
    iterate(op);
    pa_operation_unref(op);
    return devices;
}

