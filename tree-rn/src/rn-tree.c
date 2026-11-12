#include <stdio.h>
#include <stdlib.h>
#include "rn-tree.h"

// Fonction de création de l'arbre
TreeRN tree_rn_create() {
    TreeRN tree;
    tree.root = NULL;
    return tree;
}

// Fonction de création d'un nouveau noeud
TreeRNNode* tree_rn_node_create(int value) {
    TreeRNNode* node = (TreeRNNode*)malloc(sizeof(TreeRNNode));
    node->value = value;
    node->color = RED;  // Par défaut, un nouveau noeud est rouge
    node->left = node->right = node->parent = NULL;
    return node;
}

// Fonction d'insertion d'un élément dans l'arbre (rééquilibrage à faire après insertion)
void insert_tree_rn(TreeRN* tree, int value) {
    TreeRNNode* node = tree_rn_node_create(value);

    if (tree->root == NULL) {
        tree->root = node;
        node->color = BLACK;  // La racine doit être noire
        return;
    }

    TreeRNNode* current = tree->root;
    TreeRNNode* parent = NULL;

    // Trouver l'endroit où insérer
    while (current != NULL) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Insérer le nœud
    if (value < parent->value) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    node->parent = parent;

    // Rééquilibrage après insertion
    tree_rn_fix_insert(tree, node);
}

// Fonction de rééquilibrage après insertion
void tree_rn_fix_insert(TreeRN* tree, TreeRNNode* node) {
    TreeRNNode* uncle;
    while (node != tree->root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                // Cas 1 : L'oncle est rouge
                printf("Rotation nécessaire : L'oncle est rouge\n");
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    // Cas 2 : Le nœud est à droite
                   printf("Rotation gauche sur %d\n", node->parent->value);
                    node = node->parent;
                    tree_rn_left_rotate(tree, node);
                }
                // Cas 3 : Le nœud est à gauche
               printf("Rotation droite sur %d\n", node->parent->parent->value);
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                tree_rn_right_rotate(tree, node->parent->parent);
            }
        } else {
            // Cas symétrique si le parent est à droite
            uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                  //  printf("Rotation droite sur %d\n", node->value);
                    tree_rn_right_rotate(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                printf("Rotation gauche sur %d\n", node->parent->parent->value);
                tree_rn_left_rotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; // La racine doit toujours être noire
   printf("La racine est maintenant noire.\n");
}

// Fonction de recherche dans l'arbre
TreeRNNode* tree_rn_search(TreeRN* tree, int value) {
    TreeRNNode* current = tree->root;
    while (current && current->value != value) {
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

// Fonction de suppression d'un élément dans l'arbre (rééquilibrage à faire après suppression)
void tree_rn_delete(TreeRN* tree, int value) {
    TreeRNNode* node = tree_rn_search(tree, value);
    if (node == NULL) {
        printf("Node not found.\n");
        return;  // Si le nœud n'est pas trouvé, rien à faire
    }

    TreeRNNode* child;
    TreeRNNode* parent;
    int color;

    // Cas 1: Le nœud à supprimer a deux enfants
    if (node->left != NULL && node->right != NULL) {
        // Trouver le successeur (le plus petit élément du sous-arbre droit)
        TreeRNNode* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }

        // Remplacer la valeur du nœud à supprimer par celle du successeur
        node->value = successor->value;
        node = successor;  // Maintenant, nous supprimons le successeur (qui a au maximum un enfant)
    }

    // Cas 2: Le nœud à supprimer a un ou aucun enfant
    if (node->left != NULL) {
        child = node->left;
    } else {
        child = node->right;
    }

    parent = node->parent;
    color = node->color;

    if (child != NULL) {
        // Connecter le parent du nœud supprimé au fils
        child->parent = parent;
    }

    if (parent == NULL) {
        tree->root = child;  // Si le nœud à supprimer est la racine, mettre le fils comme racine
    } else if (node == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }

    if (color == BLACK) {
        // Rééquilibrage si le nœud supprimé était noir
        tree_rn_fix_delete(tree, child, parent);
    }

    free(node);
}

// Fonction de rééquilibrage après suppression
void tree_rn_fix_delete(TreeRN* tree, TreeRNNode* node, TreeRNNode* parent) {
    TreeRNNode* sibling;

    while (node != tree->root && (node == NULL || node->color == BLACK)) {
        if (node == parent->left) {
            sibling = parent->right;

            if (sibling->color == RED) {
                // Cas 1: Le frère est rouge
                printf("Rotation nécessaire : Le frère est rouge\n");
                sibling->color = BLACK;
                parent->color = RED;
                tree_rn_left_rotate(tree, parent);
                sibling = parent->right;
            }

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                // Cas 2: Le frère et ses enfants sont noirs
                printf("Le frère et ses enfants sont noirs, changement de couleur.\n");
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    // Cas 3: Le frère est noir et son enfant droit est noir
                    printf("Rotation nécessaire : Le frère est noir et son enfant droit est noir\n");
                    if (sibling->left != NULL) {
                        sibling->left->color = BLACK;
                    }
                    sibling->color = RED;
                    tree_rn_right_rotate(tree, sibling);
                    sibling = parent->right;
                }

                // Cas 4: Le frère est noir et son enfant droit est rouge
                printf("Rotation nécessaire : Le frère est noir et son enfant droit est rouge\n");
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }
                tree_rn_left_rotate(tree, parent);
                node = tree->root;
            }
        } else {
            sibling = parent->left;

            if (sibling->color == RED) {
                // Cas 1: Le frère est rouge
                printf("Rotation nécessaire : Le frère est rouge\n");
                sibling->color = BLACK;
                parent->color = RED;
                tree_rn_right_rotate(tree, parent);
                sibling = parent->left;
            }

            if ((sibling->right == NULL || sibling->right->color == BLACK) &&
                (sibling->left == NULL || sibling->left->color == BLACK)) {
                // Cas 2: Le frère et ses enfants sont noirs
                printf("Le frère et ses enfants sont noirs, changement de couleur.\n");
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    // Cas 3: Le frère est noir et son enfant gauche est noir
                    printf("Rotation nécessaire : Le frère est noir et son enfant gauche est noir\n");
                    if (sibling->right != NULL) {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    tree_rn_left_rotate(tree, sibling);
                    sibling = parent->left;
                }

                // Cas 4: Le frère est noir et son enfant gauche est rouge
                printf("Rotation nécessaire : Le frère est noir et son enfant gauche est rouge\n");
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }
                tree_rn_right_rotate(tree, parent);
                node = tree->root;
            }
        }
    }

    if (node != NULL) {
        node->color = BLACK;
    }
}

// Rotation gauche
void tree_rn_left_rotate(TreeRN* tree, TreeRNNode* x) {
    TreeRNNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Rotation droite
void tree_rn_right_rotate(TreeRN* tree, TreeRNNode* x) {
    TreeRNNode* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void tree_rn_pre_print(TreeRNNode* node) {
    if (node) {
        printf("%d(%s) ", node->value, node->color == RED ? "Rouge" : "Noir");
        tree_rn_pre_print(node->left);
        tree_rn_pre_print(node->right);
    }
}

// Fonction d'affichage en ordre avec la couleur des nœuds
void tree_rn_in_print(TreeRNNode* node) {
    if (node) {
        tree_rn_in_print(node->left);
        printf("%d(%s) ", node->value, node->color == RED ? "Rouge" : "Noir");
        tree_rn_in_print(node->right);
    }
}

// Fonction d'affichage post-ordre avec la couleur des nœuds
void tree_rn_post_print(TreeRNNode* node) {
    if (node) {
        tree_rn_post_print(node->left);
        tree_rn_post_print(node->right);
        printf("%d(%s) ", node->value, node->color == RED ? "Rouge" : "Noir");
    }
}

// Libération mémoire de l'arbre
void tree_rn_delete_all(TreeRNNode* node) {
    if (node != NULL) {
        tree_rn_delete_all(node->left);
        tree_rn_delete_all(node->right);
        free(node);
    }
}

void tree_rn_free(TreeRN* tree) {
    tree_rn_delete_all(tree->root);
    tree->root = NULL;
}

