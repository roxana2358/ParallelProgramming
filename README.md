# Progetto per il corso di programmazione multicore

## Name
Implementazione di algoritmi paralleli per string matching

## Description
Dato un insieme di stringhe *S* ed uno stream di pacchetti di dati (righe di un file di testo) *T* viene controlalto se all’interno dei pacchetti sono presenti delle stringhe di S e quante volte. Progetto svolto utilizzando l'algoritmo __Knuth-Morris-Pratt__.
Le implementazioni parallele utilizzano un sistema a memoria distribuita __MPI__ e un’implementazione a memoria condivisa __OpenMP__.
Comprende la *verifica della correttezza* degli algoritmi implementati, confrontando con una versione single-threaded, e la  *valutazione delle prestazioni* degli algoritmi sviluppati in termini di Speed-up ed efficienza al variare del numero di thread e delle dimensioni del problema (numero stringhe di S o numero di pacchetti di T).