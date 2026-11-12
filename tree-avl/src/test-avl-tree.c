#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl-tree.h"

// Fonction de comparaison pour les entiers
int compare_int(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    return (int_a > int_b) - (int_a < int_b);
}

int main() {
    srand(time(NULL));  // Initialiser la génération de nombres aléatoires
    
    // Nombre de données pour tester les performances
    int sizes[] = {10, 100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    
    // Ouvrir un fichier pour enregistrer les résultats
    FILE *file = fopen("insertion_times.txt", "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }
    fprintf(file, "NumEntries,Time\n");

    for (int i = 0; i < num_tests; i++) {
        int num_entries = sizes[i];
        Tree root = NULL;
        
        clock_t start = clock();  // Début du chronométrage

        for (int j = 0; j < num_entries; j++) {
            int value = rand();  // Générer une valeur aléatoire
            root = avl_insert(root, &value, sizeof(int), compare_int);
        }

        clock_t end = clock();  // Fin du chronométrage
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

        // Enregistrer le nombre d'entrées et le temps dans le fichier
        fprintf(file, "%d,%.6f\n", num_entries, time_spent);

        // Nettoyer l'arbre pour le test suivant
        tree_delete(root, NULL);
    }

    fclose(file);
    printf("Les temps d'insertion ont été enregistrés dans 'insertion_times.txt'.\n");

    return 0;
}

