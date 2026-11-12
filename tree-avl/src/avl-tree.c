#include <string.h>
#include "avl-tree.h"
#include <stdbool.h>
#include "min-max.h"
// Fonction pour créer un arbre vide
Tree tree_new() {
    return NULL;
}

// Fonction pour supprimer un arbre AVL récursivement
void tree_delete(Tree tree, void (*delete)(void *)) {
    if (tree) {
        tree_delete(tree->left, delete);  // Supprimer le sous-arbre gauche
        tree_delete(tree->right, delete);  // Supprimer le sous-arbre droit
        if (delete)
            delete(tree->data);  // Supprimer les données stockées dans le nœud
        free(tree);  // Libérer le nœud
    }
}

// Fonction pour créer un nœud avec les données spécifiées
Tree tree_create(const void *data, size_t size) {
    Tree node = (Tree)malloc(sizeof(struct _TreeNode) + size);
    if (node) {
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->height = 1;  // Initialisé à la hauteur de la feuille
        node->balance = 0; // Facteur d'équilibre initial
        memcpy(node->data, data, size);  // Copier les données dans le nœud
    }
    return node;
}

// Fonctions pour accéder aux nœuds left, right et parent
Tree tree_get_left(Tree tree) {
    return tree ? tree->left : NULL;
}

Tree tree_get_right(Tree tree) {
    return tree ? tree->right : NULL;
}

Tree tree_get_parent(Tree tree) {
    return tree ? tree->parent : NULL;
}

// Fonction pour obtenir les données du nœud
void *tree_get_data(Tree tree) {
    return tree ? tree->data : NULL;
}

// Fonctions pour définir les fils et le parent
bool tree_set_left(Tree tree, Tree left) {
    if (tree) {
        tree->left = left;
        return true;
    }
    return false;
}

bool tree_set_right(Tree tree, Tree right) {
    if (tree) {
        tree->right = right;
        return true;
    }
    return false;
}

bool tree_set_parent(Tree tree, Tree parent) {
    if (tree) {
        tree->parent = parent;
        return true;
    }
    return false;
}

// Fonction pour définir les données du nœud
bool tree_set_data(Tree tree, const void *data, size_t size) {
    if (tree) {
        memcpy(tree->data, data, size);
        return true;
    }
    return false;
}

// Fonction AVL pour calculer le facteur d'équilibre
int getBalance(Tree tree) {
    if (tree == NULL)
        return 0;
    return tree_height(tree->left) - tree_height(tree->right);
}

// Fonction pour obtenir la hauteur de l'arbre
size_t tree_height(Tree tree) {
    if (tree == NULL)
        return 0;
    return tree->height;
}

// Fonction pour obtenir la taille de l'arbre
size_t tree_size(Tree tree) {
    if (tree)
        return 1 + tree_size(tree->left) + tree_size(tree->right);
    else
        return 0;
}

// Mise à jour du facteur d'équilibre et des hauteurs après rotation
void updateBalanceAfterRotation(Tree node) {
    if (node) {
        node->height = 1 + MAX(tree_height(node->left), tree_height(node->right));
        node->balance = getBalance(node);
    }
}

// Fonction de rotation droite avec mise à jour des balances
Tree rightRotate(Tree y) {
    Tree x = y->left;
    Tree T2 = x->right;

    // Effectuer la rotation
    x->right = y;
    y->left = T2;

    // Mettre à jour les hauteurs et balances
    updateBalanceAfterRotation(y);
    updateBalanceAfterRotation(x);

    return x;
}

// Fonction de rotation gauche avec mise à jour des balances
Tree leftRotate(Tree x) {
    Tree y = x->right;
    Tree T2 = y->left;

    // Effectuer la rotation
    y->left = x;
    x->right = T2;

    // Mettre à jour les hauteurs et balances
    updateBalanceAfterRotation(x);
    updateBalanceAfterRotation(y);

    return y;
}

// Insertion AVL avec équilibrage et mise à jour des parents et balances
Tree avl_insert(Tree node, const void *data, size_t size, int (*compare)(const void *, const void *)) {
    if (node == NULL)
        return tree_create(data, size);

    if (compare(data, node->data) < 0) {
        node->left = avl_insert(node->left, data, size, compare);
        if (node->left) node->left->parent = node;
    } else if (compare(data, node->data) > 0) {
        node->right = avl_insert(node->right, data, size, compare);
        if (node->right) node->right->parent = node;
    } else
        return node;

    node->height = 1 + MAX(tree_height(node->left), tree_height(node->right));
    node->balance = getBalance(node);

    // Vérifier les déséquilibres et effectuer les rotations nécessaires
    if (node->balance > 1 && compare(data, node->left->data) < 0)
        return rightRotate(node);

    if (node->balance < -1 && compare(data, node->right->data) > 0)
        return leftRotate(node);

    if (node->balance > 1 && compare(data, node->left->data) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (node->balance < -1 && compare(data, node->right->data) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Recherche dans un arbre binaire
void *tree_search(Tree tree, const void *data, int (*compare)(const void *, const void *)) {
    if (tree) {
        switch (compare(data, tree->data)) {
            case -1:
                return tree_search(tree->left, data, compare);
            case 0:
                return tree->data;
            case 1:
                return tree_search(tree->right, data, compare);
            default:
                return NULL;
        }
    } else
        return NULL;
}

// Tri par insertion dans l'arbre
int tree_sort(void *array, size_t length, size_t size, int (*compare)(const void *, const void *)) {
    // Implémentation de tri avec insertion dans un arbre AVL
    return 0;  // Fonction non implémentée, ajout à faire
}

// Parcours pré-ordre
void tree_pre_order(Tree tree, void (*func)(void *, void *), void *extra_data) {
    if (tree) {
        func(tree->data, extra_data);
        tree_pre_order(tree->left, func, extra_data);
        tree_pre_order(tree->right, func, extra_data);
    }
}

// Parcours en ordre
void tree_in_order(Tree tree, void (*func)(void *, void *), void *extra_data) {
    if (tree) {
        tree_in_order(tree->left, func, extra_data);
        func(tree->data, extra_data);
        tree_in_order(tree->right, func, extra_data);
    }
}

// Parcours post-ordre
void tree_post_order(Tree tree, void (*func)(void *, void *), void *extra_data) {
    if (tree) {
        tree_post_order(tree->left, func, extra_data);
        tree_post_order(tree->right, func, extra_data);
        func(tree->data, extra_data);
    }
}
Tree avl_delete(Tree root, const void *data, size_t size, int (*compare)(const void *, const void *)) {
    // Implémentation de la suppression dans un arbre AVL
    return root; // Remplacez ceci par votre logique
}

