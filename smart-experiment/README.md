# Smart Experiment

Si vuole realizzare un sistema embedded che permetta di fare esperimenti di cinematica, tracciando la posizione, velocità e accelerazione di un corpo che si muove su una linea retta.

Il sistema proposto si compone di due parti: un sottosistema su Arduino realizzato con un approccio a task ed un sottosistema su PC che permette di tracciare i dati registrati durante l’esperimento.
Le due parti comunicano mediante scambio di messaggi sottoforma di stringhe comunicati tramite Seriale.