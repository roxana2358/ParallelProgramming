#include <string.h>
#include <stdlib.h>

int const MAX_LINE_LENGTH = 200;
int const MAX_PATTERN_LENGTH = 20;

// FUNZIONE CHE POPOLA LA LSP (LONGEST PREFIX SUFFIX) TABLE
void fillLPS(int *LSPtable, char pattern[]) {
    // primo elemento 0
    LSPtable[0] = 0;

    // lunghezza dell'ultima sequenza che è insieme prefisso e suffisso
    int lsp = 0;

    // indice per scorrere il pattern
    int i = 1;

    // lunghezza del pattern
    int max = strlen(pattern);

    while (i<max) {
        if (pattern[i]==pattern[lsp]) {     // match - incremento gli indici e assegno il valore nella table
            lsp+=1;
            LSPtable[i] = lsp;
            i+=1;
        } else {                            // no match
            if (lsp!=0) {                   // sequenza spezzata
                lsp = LSPtable[lsp-1];
            } else {                        // no sequenza
                LSPtable[i] = 0;
                i+=1;
            }
        }
    }
}

// FUNZIONE CHE ESEGUE L'ALGORITMO KHUTH-MORRIS-PRATT
int KMPmatch(char string[], char pattern[]) {
    // indici per scorrere stringa e pattern
    int i=0, j=0;

    // contatore di occorrenze
    int cont=0;

    // lunghezze di stringa e pattern
    int lenS=strlen(string), lenP=strlen(pattern);

    // alloco spazio e popolo la LSP table
    int *LSPtable = (int *) malloc(lenP*sizeof(int));
    fillLPS(LSPtable, pattern);

    while (i<lenS) {
        if (string[i]==pattern[j]) {
            i+=1;
            j+=1;
            if (j==lenP) {
                cont+=1;
                j=LSPtable[j-1];
            }
        } else {
            if (j>0) j=LSPtable[j-1];
            else i+=1;
        }
    }

    // libero la memoria allocata
    free(LSPtable);

    // restituisco il numero di occorrenze trovate
    return cont;
}

// FUNZIONE CHE POPOLA UN ARRAY CON LE RIGHE DI UN FILE E RESTITUISCE IL NUOVO PUNTATORE
char ** splitFile(FILE *file, int *arrayLength, int k) {
    char **array = (char **) malloc(sizeof(char *));
    int count = 0;
    char line[k];

    while (fgets(line, k, file)!=NULL) {
        array = realloc(array, (count+1)*sizeof(char*));
        line[strcspn(line, "\n")] = 0;
        array[count] = (char *) malloc(strlen(line)*sizeof(char));
        strcpy(array[count], line);
        count+=1;
    }
    *(arrayLength) = count;
    return array;
}