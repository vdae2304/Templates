/*********************************************************************************
* Implementacion de un Treap.                                                    *
* Complejidad promedio por operacion: O(log n)                                   *
*********************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int T;          //Tipo de las llaves.
struct node {
    T key;              //Llave.
    int size, priority; //Tamaño, prioridad.
    node *left, *right; //Hijos izquierdo y derecho.

    //Constructor.
    node(T key, int priority) : key(key), size(1), priority(priority), left(NULL), right(NULL) {};
};

//Regresa el tamaño de un treap.
int size(node *root) {
    return root ? root->size : 0;
}

//Actualiza el tamaño de un treap y demas informacion adicional.
void update(node *root) {
    if (root)
        root->size = size(root->left) + size(root->right) + 1;
}

//Divide un treap en dos partes, la mitad izquierda con los elementos menores que key.
void split(node *root, T key, node *&left, node *&right) {
    if (!root)
        left = right = NULL;
    else if (key < root->key) {
        split(root->left, key, left, root->left);
        right = root;
    }
    else {
        split(root->right, key, root->right, right);
        left = root;
    }
    update(root);
}

//Inserta un nuevo elemento en un treap ordenado.
void insert(node *&root, node *item) {
    if (!root)
        root = item;
    else if (item->priority > root->priority) {
        split(root, item->key, item->left, item->right);
        root = item;
    }
    else
        insert(item->key < root->key ? root->left : root->right, item);
    update(root);
}

//Combina dos treaps en uno solo en el orden dado.
void merge(node *&root, node *left, node *right) {
    if (!left || !right)
        root = left ? left : right;
    else if (left->priority > right->priority) {
        merge(left->right, left->right, right);
        root = left;
    }
    else {
        merge(right->left, left, right->left);
        root = right;
    }
    update(root);
}

//Elimina una llave dada en un treap ordenado.
void erase(node *&root, T key) {
    if (!root)
        return;
    if (root->key == key) {
        node *tmp = root;
        merge(root, root->left, root->right);
        delete tmp;
    }
    else 
        erase(key < root->key ? root->left : root->right, key);
    update(root);
}

//Divide un treap en dos partes, la mitad izquierda con los primeros k elementos.
void split_by_order(node *root, int k, node *&left, node *&right) {
    if (!root)
        left = right = NULL;
    else if (k < size(root->left)) {
        split(root->left, k, left, root->left);
        right = root;
    }
    else {
        split(root->right, k - 1 - size(root->left), root->right, right);
        left = root;
    }
    update(root);
}

//Regesa el k-esimo elemento (indexado en 0) del treap.
node *kth_element(node *root, int k) {
    if (!root || k == size(root->left))
        return root;
    if (k < size(root->left))
        return kth_element(root->left, k);
    else 
        return kth_element(root->right, k - size(root->left) - 1);
}

//Regresa el numero de elementos menores que key.
int order_of_key(node *root, T key) {
    if (key < root->key)
        return order_of_key(root->left, key);
    if (key == root->key)
        return size(root->left) + 1;
    else
        return size(root->left) + 1 + order_of_key(root->right, key);
}

//Imprime los elementos de un treap.
void print(node *root) {
    if (root) {
        print(root->left);
        cout << root->key << ' ';
        print(root->right);
    }
}

int main() {
    node *treap = NULL, *it, *l, *r;
    char op;
    T x;
    int k;
    
    while (cin >> op) {
        switch (op) {
            case 'I': cin >> x; 
                      insert(treap, new node(x, rand()));
                      break;
            case 'E': cin >> x; 
                      erase(treap, x);
                      break;
            case 'K': cin >> k; 
                      it = kth_element(treap, k); 
                      if (it) 
                        cout << it->key << '\n';
                      break;
            case 'O': cin >> x;
                      cout << order_of_key(treap, x);
                      break;
            case 'S': cin >> x;
                      split(treap, x, l, r);
                      print(l); cout << '\n';
                      merge(treap, l, r);
                      break;
            case 'F': cin >> k;
                      split_by_order(treap, k, l, r);
                      print(l); cout << '\n';
                      merge(treap, l, r);
                      break;
            case 'P': print(treap); cout << '\n';
        }        
    }

    return 0;
}
