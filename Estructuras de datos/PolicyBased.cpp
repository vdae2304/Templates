/*********************************************************************************
* Policy based data structure. (Order Satistics Tree)                            *
*                                                                                *
* tree<Key, Mapped, Cmp_Fn, Tag, node_update>                                    *
* find_by_order(), order_of_key(), split(), join()                               *
*********************************************************************************/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <functional>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ordered_set v, w;

    ordered_set::const_node_iterator it = v.node_begin() const;
    return 0;
}
