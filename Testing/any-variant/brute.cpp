#include<iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int a[n+1];

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }


    int id=1;
    for(int i=1;i<=n;i++){
        if(a[id]>a[i]){
            id=i;
        }
    }

    cout<<id;
}
