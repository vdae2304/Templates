#ifndef RBTree_H_INCLUDED
#define RBTree_H_INCLUDED

template <class T> class RBTree;

template <class T>
class RBNode {
    friend class RBTree<T>;

    private:
        T item;               //Item a guardar
        RBNode<T> *p, *l, *r; //Padre, hijo izquierdo, hijo derecho
        int red;              //Color, 1-rojo, 0-negro

    public:
        /*Constructor*/
        RBNode(T item, RBNode<T> *p = NULL, RBNode<T> *l = NULL, RBNode<T> *r = NULL, bool red = true) {
            this->item = item;
            this->p = p;
            this->l = l;
            this->r = r;
            this->red = red;
        }

        /*Retorna el item*/
        T getItem() const {
            return item;
        }
};

template <class T>
class RBTree {
    private:
        RBNode<T> *head; //Raiz

        /*Rota a la izquierda el nodo it*/
        void left_rotate(RBNode<T> *it) {
            RBNode<T> *aux = it->r;  //1) P           2) P
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
        }

        /*Rota a la derecha el nodo it*/
        void right_rotate(RBNode<T> *it) {
            RBNode<T> *aux = it->l;  //1)   P        2)     P
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
        }

        /*Retorna el color del nodo. Las hojas (NULL) son siempre negras*/
        bool red(RBNode<T> *it) const {
            return it != NULL ? it->red : false;
        }
    
        /*Cambia el color del nodo*/
        void setRed(RBNode<T> *it, int color) {
            if (it != NULL)
                it->red = color;
        }

        /*Inserta un item al arbol y lo balancea*/
        void RBinsert(RBNode<T> *&it, T item, RBNode<T> *p, bool flag) {
            if (it == NULL)
                it = new RBNode<T>(item, p);
            else {
                //Si ambos hijos son rojos, los cambia a negro y hace a it rojo
                if (red(it->l) && red(it->r)) {
                    it->red = true;
                    it->l->red = false;
                    it->r->red = false;
                }
                //Busca el subarbol donde se debe insertar e inserta recursivamente
                if (item < it->item) {
                    RBinsert(it->l, item, it, false);
                    if (red(it) && red(it->l) && flag)
                        right_rotate(it);
                    if (red(it->l) && red(it->l->l)) {
                        right_rotate(it);
                        it->red = false;
                        it->r->red = true;
                    }
                }
                else {
                    RBinsert(it->r, item, it, true);
                    if (red(it) && red(it->r) && !flag)
                        left_rotate(it);
                    if (red(it->r) && red(it->r->r)) {
                        left_rotate(it);
                        it->red = false;
                        it->l->red = true;
                    }
                }
            }
        }

        /*Intercambia la posicion de dos subarboles dentro del arbol*/
        void swap(RBNode<T> *it1, RBNode<T> *it2) {
            if (it2 != NULL)
                it2->p = it1->p;
            if (it1->p == NULL)
                head = it2;
            else if (it1 == it1->p->l)
                it1->p->l = it2;
            else
                it1->p->r = it2;
        }

        /*Balancea el arbol antes de eliminar el nodo*/
        void RBerase(RBNode<T> *it) {
            if (red(it) || red(it->l) || red(it->r)) {
                RBNode<T> *aux = (it->l != NULL) ? it->l : it->r;
                swap(it, aux);
                setRed(aux, false);
            }
            else {
                RBNode<T> *aux = it;
                aux->red = 2;

                while (aux != head && aux->red == 2) {
                    RBNode<T> *p = aux->p;
                    if (aux == p->l) {
                        RBNode<T> *sib = p->r;
                        if (red(sib)) {
                            sib->red = false;
                            p->red = true;
                            left_rotate(p);
                        }
                        else if (sib != NULL) {
                            if (!red(sib->l) && !red(sib->r)) {
                                sib->red = true;
                                if (p->red)
                                    p->red = false;
                                else
                                    p->red = 2;
                                aux = p;
                            }
                            else {
                                if (red(sib->l)) {
                                    sib->l->red = false;
                                    sib->red = true;
                                    right_rotate(sib);
                                    sib = p->r;
                                }
                                setRed(sib, p->red);
                                setRed(p, false);
                                setRed(sib->r, false);
                                left_rotate(p);
                                break;
                            }
                        }
                    }
                    else {
                        RBNode<T> *sib = p->l;
                        if (red(sib)) {
                            sib->red = false;
                            p->red = true;
                            right_rotate(p);
                        }
                        else if (sib != NULL) {
                            if (!red(sib->l) && !red(sib->r)) {
                                sib->red = true;
                                if (p->red)
                                    p->red = false;
                                else
                                    p->red = 2;
                                aux = p;
                            }
                            else {
                                if (red(sib->r)) {
                                    sib->r->red = false;
                                    sib->red = true;
                                    left_rotate(sib);
                                    sib = p->l;
                                }
                                setRed(sib, p->red);
                                setRed(p, false);
                                setRed(sib->l, false);
                                right_rotate(p);
                                break;
                            }
                        }
                    }
                }
                swap(it, NULL);
            }
        }

    public:
        /*Constructor*/
        RBTree() {
            head = NULL;
        }
            
        /*Retorna el apuntador a la raiz*/
        RBNode<T> *root() const {
            return head;
        }
        
        /*Devuelve el apuntador al elemento minimo del subarbol*/
        RBNode<T> *min_element(RBNode<T> *it) const {
            if (it != NULL)
                for (; it->l != NULL; it = it->l);
            return it;
        }

        /*Devuelve el apuntador al elemento maximo del subarbol*/
        RBNode<T> *max_element(RBNode<T> *it) const {
            if (it != NULL)
                for (; it->r != NULL; it = it->r);
            return it;
        }
        
        /*Devuelve el apuntador al antecesor de it*/
        RBNode<T> *prev(RBNode<T> *it) const {
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
        RBNode<T> *next(RBNode<T> *it) const {
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
        RBNode<T> *find(T item) const {
            RBNode<T> *it;
            for (it = head; it != NULL && it->item != item; it = (item < it->item) ? it->l : it->r);
            return it;
        }

        /*Si el elemento no esta en el arbol, lo inserta*/
        void insert(T item) {
            if (find(item) == NULL)
                RBinsert(head, item, NULL, false);
            head->red = false;
        }

        /*Si el elemento esta en el arbol, lo elimina*/
        void erase(T item) {
            RBNode<T> *it = find(item);
            if (it != NULL) {
                //Si tiene dos hijos, intercambia posicion con el sucesor
                if (it->l != NULL && it->r != NULL) {
                    RBNode<T> *aux = next(it);
                    it->item = aux->item;
                    it = aux;
                }
                //El nodo tiene a lo mas un hijo
                RBerase(it);
                head->red = false;
                delete it;
            }
        }
};

#endif // RBTree_H_INCLUDED
