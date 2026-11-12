#ifndef TREE_RN_H
#define TREE_RN_H

#define RED 1
#define BLACK 0

// Structure pour un nœud de l'arbre rouge-noir
typedef struct TreeRNNode {
    int value;
    int color;
    struct TreeRNNode *left, *right, *parent;
} TreeRNNode;

// Structure de l'arbre rouge-noir
typedef struct {
    TreeRNNode* root;
} TreeRN;

// Déclaration des fonctions
TreeRN tree_rn_create();
TreeRNNode* tree_rn_node_create(int value);
void insert_tree_rn(TreeRN* tree, int value);
TreeRNNode* tree_rn_search(TreeRN* tree, int value);
void tree_rn_delete(TreeRN* tree, int value);
void tree_rn_fix_delete(TreeRN* tree, TreeRNNode* node, TreeRNNode* parent);
void tree_rn_left_rotate(TreeRN* tree, TreeRNNode* x);
void tree_rn_right_rotate(TreeRN* tree, TreeRNNode* x);
void tree_rn_pre_print(TreeRNNode* node);
void tree_rn_in_print(TreeRNNode* node);
void tree_rn_post_print(TreeRNNode* node);
void tree_rn_delete_all(TreeRNNode* node);
void tree_rn_free(TreeRN* tree);
void tree_rn_fix_insert(TreeRN* tree, TreeRNNode* node);

#endif // TREE_RN_H

