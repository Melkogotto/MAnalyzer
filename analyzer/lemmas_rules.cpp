#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "analyzer.hpp"

//******************************************************************************
// LEMMAS RULES READING/FREEING
//******************************************************************************
LemmasRules lemmas_rules_fread(const char * filename)
{
    LemmasRules rules;

    FILE * file = fopen(filename, "r");

    // Reading count of them.
    fscanf(file, "%d", &(rules.count));
    rules.rules = (short int **) malloc(sizeof(short int *) * rules.count);

    char * buffer = (char *) calloc(1024, sizeof(char));

    for(int i = 0; i < rules.count; i++)
    {
        // Reading count of rules for this lemma.
        int count = 0;
        fscanf(file, "%d", &count);

        // +1 for count.
        rules.rules[i] = (short int *) malloc(sizeof(short int) * (count + 1));
        rules.rules[i][0] = (short int) count;

        for(int j = 0; j < count; j++)
            fscanf(file, "%hd", &(rules.rules[i][j + 1]));
    }

    fclose(file);
    free(buffer);

    return rules;
}

void lemmas_rules_free(LemmasRules rules)
{
    for(int i = 0; i < rules.count; i++)
        free(rules.rules[i]);

    free(rules.rules);
}
