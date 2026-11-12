#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rn-tree.h"

#define MAX_VALUES 1500   // Taille maximale de l'arbre à tester

void measure_insertion_time(int num_values, FILE *file) {
    TreeRN tree = tree_rn_create();
    srand(time(NULL));  // Initialiser le générateur de nombres aléatoires

    clock_t start, end;
    double cpu_time_used;

    // Mesurer le temps pour insérer num_values éléments dans l'arbre
    start = clock();  // Temps de départ

    for (int i = 0; i < num_values; i++) {
        int value = rand() % 1000 + 1;  // Générer un nombre aléatoire entre 1 et 1000
        insert_tree_rn(&tree, value);
    }

    end = clock();  // Temps de fin
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Temps d'insertion pour %d éléments: %f secondes\n", num_values, cpu_time_used);

    // Enregistrer le résultat dans le fichier
    fprintf(file, "%d %f\n", num_values, cpu_time_used);

    // Libérer l'arbre
    tree_rn_free(&tree);
}

int main() {
    int sizes[] = {10, 100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 5000};  // Différentes tailles d'arbres à tester
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    // Ouvrir le fichier pour enregistrer les résultats
    FILE *file = fopen("temps_insertion.txt", "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    for (int i = 0; i < num_sizes; i++) {
        int num_values = sizes[i];
        printf("\nTest avec %d insertions:\n", num_values);
        measure_insertion_time(num_values, file);
    }

    fclose(file);  // Fermer le fichier après avoir enregistré tous les résultats

    return 0;
}

