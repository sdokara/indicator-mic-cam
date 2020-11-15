#ifndef PULSECALLBACKS_H
#define PULSECALLBACKS_H

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#include <pulse/pulseaudio.h>

void state_cb(pa_context* context, void* raw);
void source_list_cb(pa_context* context, const pa_source_info *i, int eol, void *raw);

#endif // PULSECALLBACKS_H
