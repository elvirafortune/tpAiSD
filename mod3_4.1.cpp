
#include <iostream>
#include <cstdio>

struct node_t {
    int data;
    int hight;
    int count; 
    node_t* left;
    node_t* right;
        node_t(int key) : data(key), hight(1), left(0), right(0),  count(1) {}
};

int Height(node_t* node)
{
        return node == 0 ? 0 : node->hight;
}

int Count(node_t* node) //poschitaem kol-vo uzlov v left & right poddereve
{
        return node == 0 ? 0 : node->count;
}

int BalanceFactor(node_t* node)
{
        return Height(node->right) - Height(node->left);
}

void FixHeight(node_t* node)
{
    int h_l = Height(node->left);
    int h_r = Height(node->right);
    node->hight = (h_l > h_r ? h_l : h_r)+1;
}
void FixCount(node_t* node)
{
    node->count = Count(node->right) + Count(node->left) + 1;
}

node_t* Rotateright(node_t* root)
{
    node_t* node = root->left;
    root->left = node->right;
    node->right = root;
    FixHeight(root);
    FixHeight(node);
    FixCount(root); 
    FixCount(node);
    return node;
}

node_t* Rotateleft(node_t* root)
{
    node_t* node = root->right;
    root->right = node->left;
    node->left = root;
    FixHeight(root);
    FixHeight(node);
    FixCount(root); 
    FixCount(node);
    return node;
}

node_t* Balance(node_t* root)
{
    if( BalanceFactor(root) == 2 )
    {
        if( BalanceFactor(root->right) < 0 ) {
            root->right = Rotateright(root->right);
        }
        return Rotateleft(root);
    }
    if( BalanceFactor(root)==-2 )
    {
        if( BalanceFactor(root->left) > 0  ) {
            root->left = Rotateleft(root->left);
        }
        return Rotateright(root);
    }
   
    FixHeight(root);
    FixCount(root);
    return root;
}

node_t* Insert(node_t* root, int key, int answer) 
{
    if( root == NULL ) {
        std::cout << answer << std::endl;
                return new node_t(key);
    }
    if( key < root->data ) {
       
        answer += Count(root->right) + 1;  // idem vlevo i dobavl kol-vo vershin > key
        root->left = Insert(root->left, key, answer);
    }
    else {
        
        root->right = Insert(root->right, key, answer);
    }
    return Balance(root);
}

node_t* FindMin(node_t* p)
{
    return p->left == 0 ? p : FindMin(p->left);
}

node_t* RemoveMin(node_t* p)
{
    if( p->left == 0 )
        return p->right;
    p->left = RemoveMin(p->left);
    return Balance(p);
}

node_t* Remove(node_t* p, int position)
{
    if( p == 0  || position > Count(p) ) return 0;
    int current_size = Count(p->right) + 1;
   
        if( position == current_size ) {    // udalim soldata po pozicii

        node_t* left = p->left;
        node_t* right = p->right;
        delete p;
        if( right == 0 ) return left;
        node_t* min = FindMin(right);
        min->right = RemoveMin(right);
        min->left = left;
        return Balance(min);
    }

    if( position < current_size )
        p->right = Remove(p->right, position);
    else
        p->left = Remove(p->left, position - current_size);
    return Balance(p);
}

void Delete(node_t* node)
{
        if (!node) return;
        Delete(node->left);
        Delete(node->right);
        delete node;
}

int main()
{
    node_t* root = 0;
    int n;
    std::cin >> n;
    for(int i = 0;i < n; i++) {
        int command;
                int X;
                std::cin >> command >>X;
                if( command ==  1 ) {
                        root = Insert(root, X, 0);
                } else if (command == 2){
                        root = Remove(root, X + 1);
                } else break;
        }

        Delete(root);

        return 0;
}
