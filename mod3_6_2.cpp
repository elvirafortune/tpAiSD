
#include <iostream>
#include <vector>
#include "math.h"
using namespace std;

#define INT_MAX1 100000000000

struct Layer{
    int color;
    int modify;
};

class MySegTree {
public:
	MySegTree(const vector<int>& source, int n)
    {
        tree = vector<Layer>(source.size());
        for (unsigned long i = source.size() - 1; i >= source.size()/2; i--)
        {
            tree[i].modify = -1; //indik okr
            tree[i].color = source[i]; //cvet okr
        }
        for (unsigned long i = source.size()/2 - 1; i >= 0; i--)
        {
            tree[i].color = min(tree[2 * i + 1].color, tree[2*i + 2].color); // выбираем мин из двух
            tree[i].modify = -1; //не модифиц
            if (i == 0) break;
        }
        size = n;
    };
	int RMQ(int l, int r);
    void Modify(int l, int r, int val);
private:
	vector<Layer>tree;
	int size;
	int getRMQ(int pos, int posL, int posR, int l, int r);
    void Modification(int pos, int posL, int posR, int l, int r, int val);
};

void MySegTree::Modify(int l, int r, int val)
{
    Modification(0, 0, size-1, l, r, val);
}

int MySegTree::RMQ(int l, int r)
{
	return getRMQ(0, 0, size-1, l, r);
}

int logarifm(unsigned int x)
{
    int logar = 1;
    int k = 0;
    while (logar < x) {
        logar = logar * 2;
        k++;
    }
    return k;
};

void MySegTree::Modification(int pos, int posL, int posR, int l, int r, int val) // модиФИЦИРУЕТ запис в модиф знач которое нам нужно
{
    if (l == posL && r == posR)
    { // если границы совпали то модиф не делаем отмеч сразу млдиф
        tree[pos].modify = val;
        int i = (pos - 1)/2;
        while (i >= 0) // поднимаемся вверх модифиц все ост верхние вершины обновл мин
        {
            if (tree[2 * i + 1].modify != -1 && tree[ 2*i +2].modify == -1)
                tree[i].color = min(tree[2 * i + 1].modify, tree[2* i + 2].color);
            if (tree[2 * i + 1].modify == -1 && tree[ 2*i +2].modify != -1)
                tree[i].color = min(tree[2 * i + 1].color, tree[2* i + 2].modify);
            if (tree[2 * i + 1].modify != -1 && tree[ 2*i +2].modify != -1)
                tree[i].color = min(tree[2 * i + 1].modify, tree[2* i + 2].modify);
            if (tree[2 * i + 1].modify == -1 && tree[ 2*i +2].modify == -1)
                tree[i].color = min(tree[2 * i + 1].color, tree[2* i + 2].color);
            
            if (i == 0) break; 
            i = (i - 1)/2;
        }
        return;
    }
    if (tree[pos].modify != -1) //есл не модифицир проталкиваем вниз нам надо модиф отрезок кот меньше 
    {
        tree[pos * 2 + 1].modify = tree[pos].modify; // отмеч левое и правое как модифицированное
        tree[pos * 2 + 2].modify = tree[pos].modify;
        tree[pos].color = tree[pos].modify;// говорим что не модифиц но цвет задаем такой как был в модифиц 
        tree[pos].modify = -1; //отмечаем как не модиф
    }
    const int posM = (posL + posR)/2; //берем центр
    if (l <= posM)
        Modification(2 * pos + 1, posL, posM, l, min(r, posM), val); //модиф левое так как затронуто
    if (r > posM)
        Modification(2 * pos + 2, posM + 1, posR, max(l, posM + 1), r, val); //правое
    
};

int MySegTree::getRMQ(int pos, int posL, int posR, int l, int r)
{
    if (tree[pos].modify != -1) return tree[pos].modify; //если модифиц то возвращаем все
	if( l == posL && r == posR ) // Весь диапазон.
    {
        return tree[pos].color;
    }
    const int posM = ( posL + posR ) / 2;
    int result = INT_MAX1;
    if( l <= posM ) // Затронуто левое поддерево.
        result = getRMQ( 2 * pos + 1, posL, posM, l, min( r, posM ) );
    if( r > posM ) // Затронуто правое поддерево.
        result = min( result, getRMQ( 2 * pos + 2, posM + 1, posR, max( l, posM + 1 ), r ) );
    return result;
}

int main() {
    int n, r, g, b;
    cin >> n;
    int size = pow(2, logarifm(n) + 1) - 1;
    vector <int > v(size);
    for (int i = size/2; i < size/2 + n; i++)
    {
        cin >> r >> g >> b;
        v[i] = r + g + b; //заносим цвет
    }
    for (int i = size/2 + n; i < size; i ++)
        v[i] = INT_MAX1;
    n = pow(2, logarifm(n)); // посчитаем длину нижнего уровня поддерева
    MySegTree a(v, n); //созд дерево
    int k, c, d, e, f;
    cin >> k; //вводим колво сфоткано
    for (int i = 0; i < k; i ++)
    {
        cin >> c >> d >> r >> g >> b >> e >> f; // граница цвет граница фоток
        a.Modify(c, d, r + g + b); //модифиц границ перекраш
        cout << a.RMQ(e, f) << " "; //здесь границы фотокы
    }
	return 0;
}
