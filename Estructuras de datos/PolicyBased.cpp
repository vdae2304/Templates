/*********************************************************************************
* Policy based data structure. (Order Satistics Tree)                            *
* Implementacion de un arbol AVL autobalanceable.                                *
* tree<Key, Mapped, Cmp_Fn, Tag, node_update>                                    *
*********************************************************************************/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <functional>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ordered_set v;
    return 0;
}
