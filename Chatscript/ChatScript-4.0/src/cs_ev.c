#ifndef DISCARDSERVER
#ifdef EVSERVER
#define EV_STANDALONE 1
#define EV_CHILD_ENABLE 1
#include "ev.c"
#endif
#endif
