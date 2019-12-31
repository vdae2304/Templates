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

void 

int main() {
    ordered_set v, w;

    for (int i = 0; i < 10; ++i)
        v.insert(i + 1);

    cout << "Split:\n";
    v.split(5, w);
    for (ordered_set::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (ordered_set::iterator it = w.begin(); it != w.end(); ++it)
        cout << *it << ' ';
    cout << '\n';

    v.join(w);
    cout << "Join:\n";
    for (ordered_set::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    for (ordered_set::iterator it = w.begin(); it != w.end(); ++it)
        cout << *it << ' ';
    cout << '\n';
    return 0;
}
