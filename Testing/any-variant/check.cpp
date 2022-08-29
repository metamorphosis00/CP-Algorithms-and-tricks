#include "testlib.h"

/**Check, using testlib running format:
      check.exe <Input_File> <Output_File> <Answer_File>
**/
using namespace std;

int main(int argc, char *argv[]) {
    setName("check solution to minimum number id in array");
    registerTestlibCmd(argc, argv);

    int pa=ouf.readInt();
    int n=inf.readInt();

    int a[n+1];

    for(int i=1;i<=n;i++){
        a[i]=inf.readInt();
    }

    for(int i=1;i<=n;i++){
        if(a[pa]>a[i]){
            quitf(_wa,"there is better answer %d less than %d",a[i],a[pa]);
        }
    }

    quitf(_ok, "answer is %d", pa);
}

