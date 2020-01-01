/*********************************************************************************
* Policy based data structures.                                                  *
* Order Satistics Tree                                                           *
*********************************************************************************/

#include <iostream>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef ordered_set::node_iterator pnode;

//Imprime el arbol rotado 90 grados hacia la izquierda.
void print_tree(pnode it, pnode nil, int indent = 0) {
    if (it != nil) {
        print_tree(it.get_l_child(), nil, indent + 2);
        for (int i = 0; i < indent; ++i)
            cout << ' ';
        cout << **it << '\n';
        print_tree(it.get_r_child(), nil, indent + 2);
    }
}

int main() {
	//Datos de ejemplo.
    int n = 10;
    int arr[] = {20, 15, 50, 30, 25, 36, 10, 35, 40, 21};

    //Crea un arbol con los datos de arr y lo imprime.
    ordered_set v, w;
    for (int i = 0; i < n; ++i)
        v.insert(arr[i]);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';

    //Separa el arbol en dos y los imprime.
    v.split(30, w);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';
    print_tree(w.node_begin(), w.node_end()); cout << '\n';

    //Vuelve a unir ambos arboles y lo imprime.
    v.join(w);
    print_tree(v.node_begin(), v.node_end()); cout << '\n';
    
    //Imprime el indice de 35.
    cout << v.order_of_key(35) << '\n';
    //Imprime el 7-esimo elemento.
    cout << *v.find_by_order(7) << '\n';

    return 0;
}
