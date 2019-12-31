/*********************************************************************************
* Policy based data structure. (Order Satistics Tree)                            *
*********************************************************************************/

#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<char, null_type, less<char>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef ordered_set::node_iterator pnode;

//Imprime el arbol rotado 90° hacia la izquierda.
void print_tree(pnode it, pnode nil, int indent = 0) {
    if (it == nil)
        return;
    print_tree(it.get_l_child(), nil, indent + 2);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << **it << '\n';
    print_tree(it.get_r_child(), nil, indent + 2);
}

int main() {
    ordered_set v, w;

    //Llena el arbol con los letras de la 'a' a la 'z'.
    for (char i = 'a'; i < 'z'; ++i)
        v.insert(i);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';

    //Separa el arbol en dos y los imprime.
    v.split('l', w);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';
    print_tree(w.node_begin(), w.node_end()); cout << '\n';

    //Vuelve a unir ambos arboles y lo imprime.
    v.join(w);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';
    
    //Imprime el indice de 'f'.
    cout << v.order_of_key('f') << '\n';
    //Imprime la 10-esima letra.
    cout << *v.find_by_order(10) << '\n';

    return 0;
}
