# sm – State Machine

Minimale, threaded State-Machine in C: `sm_run` startet einen Thread, ruft
die Handler-Schleife (solange ein Handler `true` liefert) und joined den
Thread danach wieder.

Ein Zustand ist ein `struct sm_state` mit einer Handler-Funktion; der
„nächste Zustand" wird dem Handler als Argument übergeben.

## Nutzung

```c
#include <sm/sm.h>

bool my_state(sm_state_t next_state, void* user_data)
{
    /* Zustandskörper ... */
    return false; /* false -> Maschine terminiert */
}

sm_run(my_state, user_data);
```

## Zusammenarbeit

`rbs` (Rule Based System) nutzt `sm` über `rbs_sm`: jeder Schritt sucht den
ersten aktiven Slot-Marker und routet dessen Handler hierher. Fortschritt
passiert über Konsumieren von Fakten, Beendigung über `false` des Handlers.

## Abhängigkeiten

- `threading` (transitiv: Thread-Erzeugung/-Joining)

## Build

```bash
cmake -S . -B build
cmake --build build
```

In ein Projekt einbinden: `add_subdirectory(../../libraries/sm …)`,
Einbindung des Headers über den Include-Pfad `<sm/sm.h>`.