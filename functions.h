int const MAX_PATTERN_LENGTH = 20;
int const MAX_PATTERNS_NUMBER = 3000;

// FUNZIONE CHE POPOLA L'ARRAY DI PATTERN E RESTITUISCE IL PUNTATORE A TALE ARRAY
char ** splitPatterns(FILE *file, int *patN) {
    // initialize patterns array
    char **array = (char **) malloc(sizeof(char *)*MAX_PATTERNS_NUMBER);

    // counter for patterns
    int count = 0;

    // buffer for the lines
    char line[MAX_PATTERN_LENGTH];

    while (fgets(line, MAX_PATTERN_LENGTH, file)!=NULL) {
        // remove line break
        line[strcspn(line, "\n")] = 0;
        // allocate space for the pattern
        array[count] = (char *) malloc(strlen(line)*sizeof(char));
        // copy pattern in array
        strcpy(array[count], line);
        count+=1;
    }

    // reallocate patterns array
    *patN = count;
    array = realloc(array, sizeof(char *)*count);
    return array;
}

// FUNZIONE CHE UNISCE I PACCHETTI IN UN'UNICA STRINGA E RESTITUISCE IL PUNTATORE A TALE ARRAY
char * fusePackets(FILE *file) {
    // seek end of file to see how many bytes necessary
    fseek(file, 0, SEEK_END);
    int packSize = ftell(file);

    // go back to start of file
    rewind(file);

    // initialize array for the string
    char *array = (char *) malloc((packSize+1)*sizeof(char));

    // read all file
    int readSize = fread(array, sizeof(char), packSize, file);
    
    // couldn't read entire file
    if (readSize!=packSize) {
        printf("Error reading packets file.");
        exit(EXIT_FAILURE);
    }

    // add end of string
    array[packSize] = 0;

    return array;
}