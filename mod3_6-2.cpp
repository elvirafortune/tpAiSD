#include <iostream>
#include <vector>
#include "math.h"
using namespace std;

#define INT_MAX1 100000000000

struct Layer
{
    int color;
    int modify;
    Layer(int clr){color=clr; modify=-1;}
};

int log2(int n) {
    int arg = 1;
    int i;
    for( i=0; arg < n; ++i)
         arg = arg * 2;
    return i;
}; 

class Segment_Tree {
	vector <Layer> tree;
	int size;

	int getRMQ(int pos, int posL, int posR, int l, int r)
        {
    if (tree[pos].modify != -1) return tree[pos].modify; 
	if( l == posL && r == posR ) // Ves' diapazon
    {
        return tree[pos].color;
    }
    const int posM = ( posL + posR ) / 2;
    int result = INT_MAX1;
    if( l <= posM ) // levoe podderevo
        result = getRMQ( 2 * pos + 1, posL, posM, l, min( r, posM ) );
    if( r > posM ) // pravoe podderevo
        result = min( result, getRMQ( 2 * pos + 2, posM + 1, posR, max( l, posM + 1 ), r ) );
    return result;

}
    void Modification(int pos, int posL, int posR, int l, int r, int val)
        {
    if (l == posL && r == posR)
    { // if granici sovpali to modify vse derevo
        tree[pos].modify = val;
        int i = (pos - 1)/2;
        while (i >= 0) {// podnimaemsya vverx i modify vsw vershini
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
    if (tree[pos].modify != -1) //esli ne modificirovali, to go vniz i modify otrezok, kot men'she 
    {
        tree[pos * 2 + 1].modify = tree[pos].modify; 
        tree[pos * 2 + 2].modify = tree[pos].modify;
        tree[pos].color = tree[pos].modify;  
        tree[pos].modify = -1; 
    }
    int posM = (posL + posR)/2; 
    if (l <= posM)
        Modification(2 * pos + 1, posL, posM, l, min(r, posM), val); //modify t.k levoe zatronuto
    if (r > posM)
        Modification(2 * pos + 2, posM + 1, posR, max(l, posM + 1), r, val); //pravoe 
}
    public:

	Segment_Tree(const vector<int>& source, int n) {
        tree = vector<Layer>(source.size());
        for (long i = source.size() - 1; i >= source.size()/2; i--) {
            tree[i].modify = -1; //indikator okrawivaniya
            tree[i].color = source[i]; 
        }
        for (long i = source.size()/2 - 1; i >= 0; i--) {
            tree[i].color = min(tree[2 * i + 1].color, tree[2*i + 2].color);
            tree[i].modify = -1; 
            if (i == 0) 
                break;
        }
        size = n;
    }
	int RMQ(int l, int r) { return getRMQ(0, 0, size-1, l, r);}
    void Modify(int l, int r, int val) {Modification(0, 0, size-1, l, r, val); 
}


};


int main() {
    int n;
    cin >> n;

    int size = (1 << (log2(n) + 1)) - 1;

    vector <int > v(size);

    int  r, g, b;

    for (int i = size/2; i < size/2 + n; ++i) {
        cin >> r >> g >> b;
        v[i] = r + g + b; } // zanesem cvet
    
    for (int i = size/2 + n; i < size; ++i)
        v[i] = INT_MAX1;

    n = 1 << log2(n); // poschitaem dlinu nijnego urovnya poddereva

    Segment_Tree segtree(v, n); 

    int k, c, d, e, f;
    cin >> k; //vvedem kol-vo fotok
    for (int i = 0; i < k; ++i) {
        cin >> c >> d >> r >> g >> b >> e >> f; // granica, cvet, granica fotok
        segtree.Modify(c, d, r + g + b); //modif granici perekrawivaniya
        cout << segtree.RMQ(e, f) << " "; 
    }
	return 0;
}
