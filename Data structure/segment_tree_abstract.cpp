
#include "segment_tree_abstract.h"
#include<iostream>

int sum(int a, int b)
{
    return a + b;
}
int a[10] = {0,1,2,3,4,5,6,7,8,9};
int main()
{
    SegTree<int> st(10, sum, 0);
    st.build(a);

    std::cout<<st.get(1, 4) << std::endl;
    std::cout<<st.get(5) << std::endl;

    st.upd(3, 10);

    std::cout<<st.get(2, 6) << std::endl;
}
