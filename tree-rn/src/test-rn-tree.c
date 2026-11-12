#include <stdio.h>
#include "rn-tree.h"

// Fonction principale pour tester l'arbre Rouge-Noir
int main() {
    TreeRN tree = tree_rn_create();
    int choice, value;
    TreeRNNode* searchResult;

    while (1) {
        // Affichage du menu
        printf("\nMenu des opérations de l'arbre Rouge-Noir :\n");
        printf("1. Insérer un nœud\n");
        printf("2. Rechercher un nœud\n");
        printf("3. Supprimer un nœud\n");
        printf("4. Afficher l'arbre en pré-ordre\n");
        printf("5. Afficher l'arbre en ordre\n");
        printf("6. Afficher l'arbre en post-ordre\n");
        printf("7. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insérer un nœud
                printf("Entrez la valeur à insérer : ");
                scanf("%d", &value);
                insert_tree_rn(&tree, value);
                printf("Nœud inséré.\n");
                break;
            
            case 2: // Rechercher un nœud
                printf("Entrez la valeur à rechercher : ");
                scanf("%d", &value);
                searchResult = tree_rn_search(&tree, value);
                if (searchResult) {
                    printf("Valeur %d trouvée dans l'arbre Rouge-Noir.\n", value);
                } else {
                    printf("Valeur %d non trouvée dans l'arbre Rouge-Noir.\n", value);
                }
                break;

            case 3: // Supprimer un nœud
                printf("Entrez la valeur à supprimer : ");
                scanf("%d", &value);
                tree_rn_delete(&tree, value);
                printf("Nœud supprimé.\n");
                break;

            case 4: // Afficher l'arbre en pré-ordre
                printf("Affichage en pré-ordre de l'arbre : ");
                tree_rn_pre_print(tree.root);
                printf("\n");
                break;

            case 5: // Afficher l'arbre en ordre
                printf("Affichage en ordre de l'arbre : ");
                tree_rn_in_print(tree.root);
                printf("\n");
                break;

            case 6: // Afficher l'arbre en post-ordre
                printf("Affichage post-ordre de l'arbre : ");
                tree_rn_post_print(tree.root);
                printf("\n");
                break;

            case 7: // Quitter
                printf("Au revoir !\n");
                tree_rn_free(&tree);
                return 0;

            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}

