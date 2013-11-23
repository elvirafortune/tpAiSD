#include <iostream>
#include <math.h>

using namespace std;

struct CTreapNode
{
    int Key;
    int Priority;
    CTreapNode *left;
    CTreapNode *right;
    CTreapNode(int key, int priority):Key(key), Priority(priority), left(0), right(0){}
    CTreapNode(){};
    ~CTreapNode() {delete left; delete right;}
};

struct node_t
{
    int data;
    node_t(int value):data(value), left(0), right(0){}
    node_t(){};
    node_t *left;
    node_t *right;
    ~node_t(){delete left; delete right;}
};

typedef node_t* pnode;

void add_to_tree(pnode &node, int value)
{
    if (node == 0)
    {
        node = new node_t(value);
        return;
    }
    if (node->data > value)
        add_to_tree(node->left, value);
    else
        add_to_tree(node->right, value);
}

typedef CTreapNode* _node;

void split(CTreapNode* root, int key, _node& left, _node& right)
{
    if (root == 0)
    {
        left = right = 0;
        return;
    }
    if (root->Key <= key)
    {
        
        split(root->right, key, root->right, right);
        left = root;
    }
    else{
        split(root->left, key, left, root->left);
        right = root;
    }
}

//Слияние поддеревьев
CTreapNode* Merge(CTreapNode* leftTree, CTreapNode* rightTree)
{
    if( leftTree == 0 || rightTree == 0 ) {
        return leftTree == 0 ? rightTree : leftTree;
    }
    
    if( leftTree->Priority <= rightTree->Priority ) {
        rightTree->left = Merge(leftTree, rightTree->left);
        return rightTree;
    }
    leftTree->right = Merge(leftTree->right, rightTree);
    return leftTree;
}

//Добавление в декартово дерево
void add_to_tree(_node &node, int key, int prior)
{
    if (node == 0)
    {
        node = new CTreapNode(key, prior);
        return;
    }
    CTreapNode *left = 0, *right = 0;
    split(node, key, left, right);
    node = Merge(Merge(left, new CTreapNode(key, prior)), right);
}
//Глубина декартового дерева
int lvl(CTreapNode *root )
{
    if (root == NULL)
        return 0;
    else
    {
        int lvl_left, lvl_right;
        lvl_left = lvl(root->left);
        lvl_right = lvl(root->right);
        return 1 + max(lvl_left, lvl_right);
    }
}
//Глубина наивного дерева
int lvl(node_t *root )
{
    if (root == NULL)
        return 0;
    else
    {
        int lvl_left, lvl_right;
        lvl_left = lvl(root->left);
        lvl_right = lvl(root->right);
        return 1 + max(lvl_left, lvl_right);
    }
}

int main(int argc, const char * argv[])
{
    int n;
    cin >> n;
    CTreapNode *tree = 0;
    node_t *tree_naiv = 0;
    for (int i = 0; i < n; i++)
    {
        int k, p;
        cin >> k >> p;
        add_to_tree(tree, k, p);
        add_to_tree(tree_naiv, k);
    }
    int raz = lvl(tree_naiv) - lvl(tree);
    if (raz < 0)
        raz = -raz;

    cout << raz << endl;
    return 0;
}

