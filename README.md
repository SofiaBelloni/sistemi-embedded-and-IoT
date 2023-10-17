**Sistemi Embedded e IoT  - a.a. 2020-2021**

# Progetto #1 - Track the Led Fly

Si vuole realizzare un sistema embedded che implementi un gioco che chiamiamo Track the Led Fly. 

Il gioco è implementato con architettura di controllo super loop.

La board del gioco è costituita da 4 led verdi L1, L2, L3, L4 un led rosso LS, quattro interruttori tattili T1, T2, T3, T4 e un potenziometro Pot.

# Progetto #2 - Smart Experiment

Si vuole realizzare un sistema embedded che permetta di fare esperimenti di cinematica, tracciando la posizione, velocità e accelerazione di un corpo che si muove su una linea retta.

Il sistema proposto si compone di due parti: un sottosistema su Arduino realizzato con un approccio a task ed un sottosistema su PC che permette di tracciare i dati registrati durante l’esperimento.
Le due parti comunicano mediante scambio di messaggi sottoforma di stringhe comunicati tramite Seriale.

# Progetto #3 - Smart Dam 


Si vuole realizzare un sistema IoT che implementi una versione semplificata di un sistema intelligente per il monitoraggio del livello idrometrico (*) di un fiume e controllo di una diga (dam).  In particolare, il sistema ha il principale compito di monitorare il livello dell’acqua in un punto del fiume e, in caso di situazione critica, controllare l’apertura di una diga per far defluire l’acqua (in apposite vasche di contenimento o nei campi).

*(\*) livello idrometrico -- per "livello idrometrico" in un determinato luogo del fiume si intende il dislivello tra la superficie dell'acqua di un fiume ed un punto di riferimento altimetrico, che può essere il livello medio del mare (l.m.m) oppure lo "zero" dell'idrometro stesso (detto "zero idrometrico"). L'idrometro è lo strumento che rileva le quote idrometriche, cioè il livello dell'acqua, dei fiumi o dei laghi.*