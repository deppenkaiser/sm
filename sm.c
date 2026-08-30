#include "sm/sm.h"

/* Leere Defaults als weak Definitionen: Sie existieren fuer den Linker, tun aber
 * nichts, solange die Anwendung sie nicht ueberschreibt. Eine starke Definition
 * der Anwendung (`callback void sm_on_start(...)`) gewinnt gegen den weak-Default. */
__attribute__((weak)) void sm_on_start(sm_core_t core) { (void) core; }
__attribute__((weak)) void sm_on_stop(sm_core_t core) { (void) core; }

void* _sm_thread(void* core)
{
    sm_core_t sm_core = (sm_core_t) core;
    sm_on_start(sm_core);
    while (sm_core->current_state.state_function(&sm_core->current_state, sm_core->user_data));
    sm_on_stop(sm_core);
    return NULL;
}

void sm_run(sm_state_t next_state, void* user_data)
{
    struct sm_core sm_core = {0};
    sm_core.current_state.state_function = next_state->state_function;
    sm_core.user_data = user_data;
    sm_core.thread = threading_thread_create(_sm_thread, &sm_core);
    threading_thread_join(sm_core.thread);
}
