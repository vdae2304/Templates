#ifndef AVLTree_H_INCLUDED
#define AVLTree_H_INCLUDED

template <class T> class AVLTree;

template <class T>
class AVLNode {
    friend class AVLTree<T>;

    private:
        T item;                //Item a guardar
        AVLNode<T> *p, *l, *r; //Padre, hijo izquierdo, hijo derecho
        int h;                 //Altura

    public:
        /*Constructor*/
        AVLNode(T item, AVLNode<T> *p = NULL, AVLNode<T> *l = NULL, AVLNode<T> *r = NULL, int h = 1) {
            this->item = item;
            this->p = p;
            this->l = l;
            this->r = r;
            this->h = h;
        }

        /*Retorna el item*/
        T getItem() const {
            return item;
        }
};

template <class T>
class AVLTree {
    private:
        AVLNode<T> *head; //Raiz

        /*Retorna la altura del subarbol. 0 si es nulo*/
        int height(AVLNode<T> *it) const {
            return it != NULL ? it->h : 0;
        }

        /*Rota a la izquierda el nodo it*/
        void left_rotate(AVLNode<T> *it) {
            AVLNode<T> *aux = it->r; //1) P           2) P
                                     //   |              |
            it->r = aux->l;          //   it             it    aux
            if (aux->l != NULL)      //  /   \          /   \ /  \.
                aux->l->p = it;      // Z   aux        Z     X    Y
                                     //     /  \ .
            aux->p = it->p;          //    X    Y
            if (it->p == NULL)
                head = aux;          //3)      P      4)   P
            else if (it == it->p->l) //        |           |
                it->p->l = aux;      //   it  aux         aux
            else                     //  /  \ /  \        /  \.
                it->p->r = aux;      // Z    X    Y     it    Y
                                     //                /  \.
            aux->l = it;             //               Z    X
            it->p = aux;
            it->h = std::max(height(it->l), height(it->r)) + 1;
            aux->h = std::max(height(aux->l), height(aux->r)) + 1;
        }

        /*Rota a la derecha el nodo it*/
        void right_rotate(AVLNode<T> *it) {
            AVLNode<T> *aux = it->l;  //1)   P        2)     P
                                     //     |               |
            it->l = aux->r;          //     it        aux   it
            if (aux->r != NULL)      //    /  \       /  \ /  \.
                aux->r->p = it;      //  aux   Y     Z    X    Y
                                     //  /  \.
            aux->p = it->p;          // Z    X
            if (it->p == NULL)
                head = aux;          //3) P          4)  P
            else if (it == it->p->l) //   |              |
                it->p->l = aux;      //  aux   it       aux
            else                     //  /  \ /  \      /  \.
                it->p->r = aux;      // Z    X    Y    Z   it
                                     //                   /  \.
            aux->r = it;             //                  X    Y
            it->p = aux;
            it->h = std::max(height(it->l), height(it->r)) + 1;
            aux->h = std::max(height(aux->l), height(aux->r)) + 1;
        }

        /*Intercambia la posicion de dos subarboles dentro del arbol*/
        void swap(AVLNode<T> *it1, AVLNode<T> *it2) {
            if (it2 != NULL)
                it2->p = it1->p;
            if (it1->p == NULL)
                head = it2;
            else if (it1 == it1->p->l)
                it1->p->l = it2;
            else
                it1->p->r = it2;
        }

        /*Calcula el factor de balance. Si el nodo es nulo, regresa 0*/
        int getBalance(AVLNode<T> *it) {
            return it != NULL ? height(it->l) - height(it->r) : 0;
        }

        /*Re-balancea el arbol desde un nodo dado*/
        void Balance(AVLNode<T> *it) {
            for (; it != NULL; it = it->p) {
                it->h = std::max(height(it->l), height(it->r)) + 1;
                if (getBalance(it) > 1) {
                    if (getBalance(it->l) >= 0) //Caso izquierda-izquierda
                        right_rotate(it);
                    else {                      //Caso izquierda-derecha
                        left_rotate(it->l);
                        right_rotate(it);

                    }
                }
                else if (getBalance(it) < -1) { //Caso derecha-derecha
                    if (getBalance(it->r) <= 0)
                        left_rotate(it);
                    else {
                        right_rotate(it->r);    //Caso derecha-izquierda
                        left_rotate(it);
                    }
                }
            }
        }

        /*Inserta un nuevo elemento al arbol y lo balancea*/
        void AVLinsert(AVLNode<T> *&it, T item, AVLNode<T> *p) {
            if (it == NULL) {
                it = new AVLNode<T>(item, p);
                Balance(it);
            }
            else {
                if (item < it->item)
                    AVLinsert(it->l, item, it);
                else
                    AVLinsert(it->r, item, it);
            }
        }

    public:
        /*Constructor*/
        AVLTree() {
            head = NULL;
        }

        /*Retorna el apuntador a la raiz*/
        AVLNode<T> *root() const {
            return head;
        }

        /*Devuelve el apuntador al elemento minimo del subarbol*/
        AVLNode<T> *min_element(AVLNode<T> *it) const {
            if (it != NULL)
                for (; it->l != NULL; it = it->l);
            return it;
        }

        /*Devuelve el apuntador al elemento maximo del subarbol*/
        AVLNode<T> *max_element(AVLNode<T> *it) const {
            if (it != NULL)
                for (; it->r != NULL; it = it->r);
            return it;
        }

        /*Devuelve el apuntador al antecesor de it*/
        AVLNode<T> *prev(AVLNode<T> *it) const {
            if (it == NULL)
                return NULL;
            else if (it->l != NULL)
                return max_element(it->l);
            else {
                for (; it->p != NULL && it == it->p->l; it = it->p);
                return it->p;
            }
        }

        /*Devuelve el apuntador al sucesor de it*/
        AVLNode<T> *next(AVLNode<T> *it) const {
            if (it == NULL)
                return NULL;
            else if (it->r != NULL)
                return min_element(it->r);
            else {
                for (; it->p != NULL && it == it->p->r; it = it->p);
                return it->p;
            }
        }

        /*Devuelve el apuntador al nodo con el item buscado o NULL en caso contrario*/
        AVLNode<T> *find(T item) const {
            AVLNode<T> *it;
            for (it = head; it != NULL && it->item != item; it = (item < it->item) ? it->l : it->r);
            return it;
        }

        /*Si el elemento no esta en el arbol, lo inserta*/
        void insert(T item) {
            if (find(item) == NULL)
                AVLinsert(head, item, NULL);
        }

        /*Si el elemento esta en el arbol, lo elimina*/
        void erase(T item) {
            AVLNode<T> *it = find(item);
            if (it != NULL) {
                //Si tiene dos hijos, intercambia posicion con el sucesor
                if (it->l != NULL && it->r != NULL) {
                    AVLNode<T> *aux = next(it);
                    it->item = aux->item;
                    it = aux;
                }

                //El nodo tiene a lo mas un hijo
                AVLNode<T> *aux = (it->r == NULL) ? it->l : it->r;
                swap(it, aux);
                Balance(it);
                delete it;
            }
        }
};

#endif // AVLTree_H_INCLUDED
