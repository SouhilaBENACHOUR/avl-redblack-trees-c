Projet : Structures de données - Arbres Rouges et Noirs et Arbres AVL  

Auteurs : NOURINE Abdelmalek, REKAI Nesrine, HADDADOU Lina, BENACHOUR Souhila


Description :
Ce projet implémente les structures de données des arbres Rouges et Noirs et arbres AVL en langage C. Les fichiers source sont organisés comme suit :

-TEA :
        -plot.py : 
        -tree-rn 
            -Debug
            -src 
                -rn-tree.h: Fichier d'en-tête pour les arbres Rouges et Noirs.
                -rn-tree.c : Implémentation des procedures d’insertion,recherche et suppression de donnees dans un arbre bicolore
                -test-rn-tree : Programme de test pour les arbres Rouges et Noirs (le menu contextuel).
                -Temps-Exe-rn-tree.c : Implémentation des fonctions d'evaluation de la complexite des arbres rouges et noirs
                -test-temps.c : Programme de test pour la complexite des arbres rouges et noirs.
        -tree-avl 
            -Debug
            -src :  
                -avl-tree.h: Fichier d'en-tête pour les arbres AVL.
                -avl-tree.c : Implémentation des procedures d’insertion,recherche et suppression de donnees dans un arbre AVL
                -test-avl-tree :  Programme de test pour la complexite des arbres AVL.

Instructions pour la compilation :
Pour compiler les programmes de test, vous pouvez utiliser un compilateur C tel que gcc. Par exemple, pour compiler le test des arbres AVL, vous pouvez utiliser la commande :

gcc test-avl-tree.c avl-tree.c -o test-avl-tree
Ou bien juste utiliser la commande : ./test-avl-tree

Rapport :
Le rapport détaillé de ce projet est disponible dans un document séparé nommé "Rapport_TEA_std.pdf".
        
                


















- avl-tree.c : Implémentation des arbres AVL.
- treern.c : Implémentation des arbres Rouges et Noirs.
- test-avl-tree.c : Programme de test pour les arbres AVL.
- test-treern.c : Programme de test pour les arbres Rouges et Noirs.
- avl-tree.h : Fichier d'en-tête pour les arbres AVL.
- treern.h : Fichier d'en-tête pour les arbres Rouges et Noirs.

Instructions pour la compilation :
Pour compiler les programmes de test, vous pouvez utiliser un compilateur C tel que gcc. Par exemple, pour compiler le test des arbres AVL, vous pouvez utiliser la commande :

gcc test-avl-tree.c avl-tree.c -o test-avl-tree
Ou bien juste utiliser la commande : ./test-avl-tree

Rapport :
Le rapport détaillé de ce projet est disponible dans un document séparé nommé "Rapport_Structures_De_Donnees.pdf".

