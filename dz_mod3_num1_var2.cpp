#include <iostream>
#include <stack>
using namespace std;


struct CTreeNode
{
    CTreeNode(int key) {
        this->key = key;
        left = NULL;
        right = NULL;
    }

    int key;
    CTreeNode *left, *right;
};


void Insert(CTreeNode *root, int key) {
    if (root->key <= key) {
        if(root->right == NULL)
            root->right = new CTreeNode(key);
        else
            Insert(root->right, key);
    } else {
        if(root->left == NULL)
            root->left = new CTreeNode(key);
        else
            Insert(root->left, key);
    }
}


void Travers(CTreeNode *root) {
    stack<CTreeNode*> upper_level;
    CTreeNode *pos = root;
    bool go_upper = false;

    for (;;) {
        if (go_upper) { 

            if(pos == root) 
                break;

            CTreeNode *was_at = pos; 
            pos = upper_level.top(); 
            upper_level.pop(); 

           
            if (was_at == pos->left && pos->right != NULL) { 
                upper_level.push(pos); 
                pos = pos->right; 
                go_upper = false; 
            }

        } else {

            cout << pos->key << " "; 
            if (pos->left == NULL && pos->right == NULL) {
                go_upper = true; 
            } else if (pos->left != NULL) { 
                upper_level.push(pos); 
                pos = pos->left; 
            } else { 
                upper_level.push(pos);
                pos = pos->right;
            }

        }
    }
}





int main()
{
    int n;
    cin >> n;
    int key;
    cin >> key;
    CTreeNode *tree = new CTreeNode(key);

    while(--n > 0) {
        cin >> key;
        Insert(tree, key);
    }

    Travers(tree);
    return 0;
}