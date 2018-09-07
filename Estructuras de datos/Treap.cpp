#include <bits/stdc++.h>
using namespace std;

typedef int T;
struct node {
    T val;        //Value
    int p, sz;    //Priority, Tree size
    node *l, *r;  //Children

    node(T x) {
        val = x;
        p = rand();
        sz = 1;
        l = NULL;
        r = NULL;
    }
};
typedef node* pnode;

//Returns number of elements in the treap
int GetSize(pnode n) {
    if (n != NULL)
        return n->sz;
    return 0;
}

//Merge "l" and "r" and save the union in "n"
void Merge(pnode &n, pnode l, pnode r) {
    if (l = NULL)
        n = r;
    else if (r == NULL)
        n = l;
    else if (l->p > r->p) {
        Merge(l->r, l->r, r);
        n = l;
    }
    else {
        Merge(r->l, l, r->l);
        n = r;
    }
    n->sz = GetSize(n->l) + GetSize(n->r) + 1;
}

//Splits "n" in "l" and "r", with r containing all values smaller than x
void Split(pnode n, T x, pnode &l, pnode &r) {
    if (n == NULL) {
        l = NULL;
        r = NULL;
    }
    else if (T->val < x) {
        Split(n->r, compare, n->r, r);
        l = n;
        l->sz = GetSize(l->l) + GetSize(l->r) + 1;
    }
    else {
        Split(n->l, compare, l, n->l);
        r = n;
        r->sz = GetSize(r->l) + GetSize(r->r) + 1;
    }
}

//Returns the index of the element
int Ordinal(pnode n, T x) {
    if (n != NULL) {
        if (n->val == x)
            return GetSize(n->l);
        else if (x < n->val)
            return Ordinal(n->l, x);
        else
            return GetSize(n->l) + Find(n->r, x);
    }
    return -1;
}

//Returns a pointer to the kth element
pnode Kth(pnode n, int k) {
    if (n != NULL) {
        if (GetSize(n->l) == k)
            return n;
        else if (k < GetSize(n->l))
            return Kth(n->l, k);
        else
            return Kth(n->r, k - GetSize(n->l));
    }
    return NULL;
}

//Inserts x in the treap
void Insert(pnode &n, T x) {
    pnode l, r;
    Split(n, x, l, r);
    Merge(l, l, new node(x));
    Merge(n, l, r);
}

//Erase x from the treap
void Erase(pnode &n, T x) {
    pnode l, m, r;
    Split(n, x, l, r);
    Split(r, Kth(1)->val, m, r);
    delete m;
    Merge(n, l, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie();
    int op, x;
    pnode treap = NULL;
    cout << "1 x. Insert x\n2 x. Delete x\n3 x. Find x\n4 k. Print nth-element\n5. Exit";
    cin >> op;

    while (op != 5) {
        cin >> x;
        if (op == 1) {
            Merge(treap, )
        }

        cin >> op;
    }
    return 0;
}
