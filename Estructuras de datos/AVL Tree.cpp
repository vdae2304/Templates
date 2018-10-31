/*************************************************
* Arbol AVL                                      *
* Implementacion de un arbol AVL autobalanceable *
*************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

typedef char T; //Tipo de dato del arbol

struct node {
    T item;      //Valor del nodo
    int h, sz;   //Altura, Tamaño del subarbol
    node *l, *r; //Hijos izquierdo y derecho

    node(const T &x) {
        item = x;
        h = 0; sz = 1;
        l = NULL; r = NULL;
    }
};

/*Retorna la altura del arbol*/
int height(node *root) {
    if (root != NULL)
        return root->h;
    return 0;
}

/*Retorna el tamaño del arbol*/
int size(node *root) {
    if (root != NULL)
        return root->sz;
    return 0;
}

/*Retorna el nodo con el elemento o NULL si no existe*/
node *find(node *root, const T &x) {
    if (root != NULL) {
        if (x < root->item)
            return find(root->l, x);
        else if (root->item < x)
            return find(root->r, x);
    }
    return root;
}

/*Retorna el k-esimo elemento del arbol*/
node *kth_element(node *root, int k) {
    if (root != NULL) {
        if (k < size(root->l))
            return kth_element(root->l, k);
        else if (k > size(root->l))
            return kth_element(root->r, k - size(root->l) - 1);
    }
    return root;
}

/*Retorna el indice del elemento en el arbol*/
int index(node *root, const T &x) {
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

/*Actualiza la altura y tamaño de un nodo*/
void update(node *p) {
    p->h = max(height(p->l), height(p->r)) + 1;
    p->sz = size(p->l) + size(p->r) + 1;
}

/*Rota a la izquierda el nodo y retorna el nuevo padre*/
node *left_rotate(node *x) {
    node *y = x->r;
    x->r = y->l;
    update(x);
    y->l = x;
    update(y);
    return y;
}

/*Rota a la derecha el nodo y retorna el nuevo padre*/
node *right_rotate(node *y) {
    node *x = y->l;
    y->l = x->r;
    update(y);
    x->r = y;
    update(x);
    return x;
}

/*Calcula el factor de balance de un nodo*/
int getBalance(node *p) {
    if (p != NULL)
        return height(p->l) - height(p->r);
    return 0;
}

/*Balancea el subarbol de ser necesario*/
node *Balance(node *p) {
    if (getBalance(p) > 1) {
        if (getBalance(p->l) >= 0)
            return right_rotate(p);   //Caso izquierda-izquierda
        else {
            p->l = left_rotate(p->l); //Caso izquierda-derecha
            return right_rotate(p);
        }
    }
    else if (getBalance(p) < -1) {
        if (getBalance(p->r) <= 0)
            return left_rotate(p);     //Caso derecha-derecha
        else {
            p->r = right_rotate(p->r); //Caso derecha-izquierda
            return left_rotate(p);
        }
    }
    return p;
}

/*Inserta un nuevo elemento al arbol y lo balancea. Retorna la raiz*/
node *insert(node *root, const T &x) {
    if (root == NULL)
        return new node(x);
    else {
        if (x < root->item)
            root->l = insert(root->l, x);
        else if (root->item < x) //No se permiten duplicados
            root->r = insert(root->r, x);
        update(root);
        return Balance(root);
    }
}

/*Si el elemento esta en el arbol, lo elimina. Retorna la raiz*/
node *erase(node *root, const T &x) {
    if (root == NULL)
        return root;
    else {
        if (x < root->item)
            root->l = erase(root->l, x);
        else if (root->item < x)
            root->r = erase(root->r, x);
        else {
            if (root->l != NULL && root->r != NULL) {
                root->item = kth_element(root->r, 0)->item;
                root->r = erase(root->r, root->item);
            }
            else {
                node *aux = (root->l != NULL) ? root->l : root->r;
                delete root;
                return aux;
            }
        }
        update(root);
        Balance(root);
        return root;
    }
}

/*Visualiza el arbol*/
void Debug(node *root, int h = 0) {
    if (root != NULL) {
        Debug(root->l, h + 2);
        for (int i = 0; i < h; i++)
            cout << " ";
        cout << root->item << "\n";
        Debug(root->r, h + 2);
    }
}

int main() {
    node *arbol = NULL, *p;
    int op = 1, k;
    char c;
    while (op != 0) {
        cout << "1. Insertar letra\n2. Eliminar letra\n3. Buscar letra\n4. Letra en posicion\n5. Posicion de letra\n6. Imprimir arbol\n0. Salir\n";
        cin >> op;
        switch (op) {
            case 1: cin >> c; arbol = insert(arbol, c); break;
            case 2: cin >> c; arbol = erase(arbol, c); break;
            case 3: cin >> c; cout << (find(arbol, c) != NULL ? "Esta en el arbol\n" : "No esta en el arbol\n"); break;
            case 4: cin >> k; p = kth_element(arbol, k); cout << (p != NULL ? p->item : '*') << "\n"; break;
            case 5: cin >> c; cout << index(arbol, c) << "\n"; break;
            case 6: Debug(arbol);
        }
        system("pause");
        system("cls");
    }
    return 0;
}
