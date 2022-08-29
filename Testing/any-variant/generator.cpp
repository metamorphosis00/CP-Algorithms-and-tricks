#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n=rnd.next(1,100);
    println(n);

    for(int i=1;i<=n;i++){
        cout<<rnd.next(1,10)<<" ";
    }
    cout<<endl;
}
