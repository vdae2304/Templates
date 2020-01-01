/*********************************************************************************
* Treap                                                                          *
* Implementacion de un treap.                                                    *
*********************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int T; //Tipo de dato del arbol.

struct node {
    T item;      //Valor del nodo.
    int p, sz;   //Prioridad, Tamaño del subarbol.
    node *l, *r; //Hijos izquierdo y derecho.

    node(const T &x) {
        item = x;
        p = rand(); sz = 1;
        l = NULL; r = NULL;
    }
};

typedef node* pnode;

//Regresa el tamaño del arbol.
int size(pnode root) {
    if (root != NULL)
        return root->sz;
    return 0;
}

//Combina l y r en un nuevo arbol. Los elementos de l deben ser menores que los elementos de r.
void Merge(pnode &out, pnode l, pnode r) {
    if (l = NULL)
        out = r;
    else if (r == NULL)
        out = l;
    else if (l->p > r->p) {
        Merge(l->r, l->r, r);
        out = l;
    }
    else {
        Merge(r->l, l, r->l);
        out = r;
    }
    out->sz = size(out->l) + size(out->r) + 1;
}

//Separa un arbol en dos de manera que l contiene todos los elementos menores que x.
void Split(pnode in, const T &x, pnode &l, pnode &r) {
    if (in == NULL) {
        l = NULL;
        r = NULL;
    }
    else if (in->item < x) {
        Split(in->r, x, in->r, r);
        l = in;
        l->sz = size(l->l) + size(l->r) + 1;
    }
    else {
        Split(in->l, x, l, in->l);
        r = in;
        r->sz = size(r->l) + size(r->r) + 1;
    }
}

//Regresa el k-esimo elemento del arbol (indexado en 0).
pnode kth_element(pnode root, int k) {
    if (root != NULL) {
        if (k < size(root->l))
            return kth_element(root->l, k);
        else if (k > size(root->l))
            return kth_element(root->r, k - size(root->l) - 1);
    }
    return root;
}

//Regresa el numero de elementos menores en el arbol.
int index(pnode root, const T &x) {
    if (root != NULL) {
        if (x < root->item)
            return index(root->l, x);
        else if (x == root->item)
            return size(root->l);
        else
            return size(root->l) + 1 + index(root->r, x);
    }
    return 0;
}

//Inserta x in el treap.
void insert(pnode &root, const T &x) {
    pnode l, r;
    Split(root, x, l, r);
    Merge(l, l, new node(x));
    Merge(root, l, r);
}

//Elimna x del treap.
void erase(pnode &root, const T &x) {
    pnode l, m, r;
    Split(root, x, l, r);
    Split(root, kth_element(root, 1)->item, m, r);
    delete m;
    Merge(root, l, r);
}

//Regresa el nodo con el elemento o NULL si no existe.
pnode find(pnode root, const T &x) {
    if (root != NULL) {
        if (x < root->item)
            return find(root->l, x);
        else if (root->item < x)
            return find(root->r, x);
    }
    return root;
}

int main() {
    return 0;
}
