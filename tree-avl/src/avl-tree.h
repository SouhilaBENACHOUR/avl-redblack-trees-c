#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct _TreeNode *Tree;

// Structure AVL avec hauteur, balance et left/right
struct _TreeNode {
    Tree left;
    Tree right;
    struct _TreeNode *parent;
    int height;
    int balance;
    char data[1];
};

// Fonctions de base
Tree tree_new();
void tree_delete(Tree tree, void (*delete)(void *));
Tree tree_create(const void *data, size_t size);
Tree tree_get_left(Tree tree);
Tree tree_get_right(Tree tree);
Tree tree_get_parent(Tree tree);
void *tree_get_data(Tree tree);
bool tree_set_left(Tree tree, Tree left);
bool tree_set_right(Tree tree, Tree right);
bool tree_set_parent(Tree tree, Tree parent);
bool tree_set_data(Tree tree, const void *data, size_t size);

// Parcours de l'arbre
void tree_pre_order(Tree tree, void (*func)(void *, void *), void *extra_data);
void tree_in_order(Tree tree, void (*func)(void *, void *), void *extra_data);
void tree_post_order(Tree tree, void (*func)(void *, void *), void *extra_data);

// Taille et Hauteur de l'arbre
size_t tree_height(Tree tree);
size_t tree_size(Tree tree);

// Recherche et Insertion dans un arbre non-équilibré
bool tree_insert_sorted(Tree *ptree, const void *data, size_t size, int (*compare)(const void *, const void *));
void *tree_search(Tree tree, const void *data, int (*compare)(const void *, const void *));

// Tri avec insertion dans un arbre
int tree_sort(void *array, size_t length, size_t size, int (*compare)(const void *, const void *));

// Fonctions AVL spécifiques pour équilibrage
int getBalance(Tree tree);
Tree rightRotate(Tree y);
Tree leftRotate(Tree x);
Tree avl_insert(Tree node, const void *data, size_t size, int (*compare)(const void *, const void *));
Tree avl_delete(Tree root, const void *data, size_t size, int (*compare)(const void *, const void *));

#endif

