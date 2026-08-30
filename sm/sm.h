#pragma once

#include <api/api.h>
#include <threading/threading.h>

typedef struct sm_state *sm_state_t;
typedef bool (*sm_state_handler_t)(sm_state_t next_state, void* user_data);

struct sm_state
{
    sm_state_handler_t state_function;
};

void sm_run(sm_state_t next_state, void* user_data);

typedef struct sm_core
{
    struct sm_state current_state;
    pthread_t thread;
    void* user_data;
} *sm_core_t;

/* Lebenszyklus-Hooks (virtuelle Callbacks, api-Muster):
 * sm legt in sm.c leere weak-Defaults an, damit die Symbole fuer den
 * Linker existieren. Die Anwendung ueberschreibt sie im Bedarfsfall mit einer
 * starken `callback`-Definition (z. B. Speicherverwaltung/Ressourcen ganz am
 * Anfang bzw. zum Aufraeumen ganz am Ende des Worker-Threads). */
callback_declaration(void, sm_on_start(sm_core_t core));
callback_declaration(void, sm_on_stop(sm_core_t core));
