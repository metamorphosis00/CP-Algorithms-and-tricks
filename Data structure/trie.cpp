#include<iostream>

using namespace std;

const int SIZE = 26;

struct node {
    node* next[SIZE];

    int strings;

    node()
    {
        for (int i = 0; i < SIZE; i++) {
            next[i] = nullptr;
        }

        strings = 0;
    }
};
void add(struct node* root, string key)
{
    struct node* cur_v = root;

    for (int i = 0; i < key.length(); i++) {
        char c = key[i];

        if (cur_v->next[c - 'a'] == nullptr) {
            cur_v->next[c - 'a'] = new node();
        }

        cur_v = cur_v->next[c - 'a'];
    }

    cur_v->strings++;
}
bool has(struct node* root, string key)
{
    struct node *cur_v = root;

    for (int i = 0; i < key.length(); i++) {
        cur_v = cur_v->next[key[i] - 'a'];
        if (cur_v == nullptr) {
            return false;
        }
    }

    return cur_v->strings > 0;
}
int main()
{
    struct node* root = new node();

    add(root, "qwe123");
    add(root, "zxc");

    cout<<has(root, "qwe123")<<endl;
    cout<<has(root, "few")<<endl;
}
