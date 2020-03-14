/*********************************************************************************
* Implementacion de un Treap.                                                    *
* Complejidad promedio por operacion: O(log n)                                   *
*********************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

typedef T int;          //Tipo de las llaves.
struct node {
    T key;              //Llave.
    int size, priority; //Tamaño, prioridad.
    node *left, *right; //Hijos izquierdo y derecho.

    //Constructor.
    node(T key) : key(key), size(1), priority(rand()), left(NULL), right(NULL) {};
}

//Regresa el tamaño de un treap.
int size(node *root) {
    return root ? root->size : 0;
}

//Actualiza el tamaño de un treap.
void update(node *root) {
    root->size = size(root->left) + size(root->right) + 1;
}

//Divide un treap en dos partes, la mitad izquierda con los elementos menores que key.
void split(node *root, T key, node *&left, node *&right) {
    if (!root)
        left = right = NULL;
    if (key < root->key) {
        split(root->left, key, left, root->left);
        update(right = root);
    }
    else {
        split(root->right, key, root->right, right);
        update(left = root);
    }
}

//Combina dos treaps en uno en el orden dado.
void merge(node *&root, node *left, node *right) {
    if (!left || !right)
        root = left ? left : right;
    if (left->priority > right->priority) {
        merge(left->right, left->right, right);
        update(root = left);
    }
    else {
        merge(right->left, left, right->left);
        update(root = right);
    }
}

//Regesa el k-esimo elemento (indexado en 0) del treap.
node *kth_element(node *root, int k) {
    if (k < size(root->left))
        return kth_element(root->left, k);
    if (k == size(root->left))
        return root;
    return kth_element(root->right, k - size(root->left) - 1);
}

//Regresa el numero de elementos menores que key.
int order_of_key(node *root, T key) {
    if (key < root->key)
        return order_of_key(root->left, key);
    if (key == root->key)
        return size(root->left) + 1;
    return size(root->left) + 1 + order_of_key(root->right, key);
}

int main() {
    return 0;
}
