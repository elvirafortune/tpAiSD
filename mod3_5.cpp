#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


#define INT_MAX 100000000000000



struct Second_min 
{
    int min;
    int sec_min;

    Second_min(int _min = 0, int _sec_min = 0): min(_min), sec_min(_sec_min){}
};

class SparseTable
{
    typedef vector<Second_min> VECTOR;

public:
    SparseTable(const std::vector<int>& v);
    int RMQ(int l, int r);

private:
    vector<VECTOR> table;

    Second_min find_sec_min(const Second_min& m1, const Second_min& m2);
    Second_min find_sec_min(const VECTOR& row, int indx1, int indx2);
    vector<Second_min> ConvertTo_SecMinVector(const vector<int>& vec);
};


SparseTable::SparseTable(const std::vector<int>& v)
{
    //sostavlyaem massiv par eto budet 1 str v matrice
    VECTOR vec = ConvertTo_SecMinVector(v);
    table.push_back(vec); // perviy ryad
    //dobavim eshe (log(vec.size())/log(2)) strok
    for (int i = 1; i < (log((double)vec.size())/log(2.0)) + 1; ++i) //log((double)vec.size())/log(2.0) vichislenie log s osnovaniem 2 i +1,
        
    {
        int stepen = (1 << (i - 1)); 
        VECTOR row;
        for (int  j = 0; j + stepen < table[i-1].size(); ++j)
        {
        //budem iskat' vtoroy min, opirayas' na predidushuu stroku v matrice mejdu elem j & j+stepen i zapisiv v matr novuu stroku
            row.push_back(find_sec_min(table[i-1], j, j + stepen));
        }
        //dobavim poluchivshuusya stroku v tablicu i prodoljim sozdavat novuyu stroku
          table.push_back(row);  
    }
}

int SparseTable::RMQ(int l, int r)
{
    if (l == r)
        return table[0][l - 1].min;
    int k = log((double)r-l)/log(2.0);
    return find_sec_min(table[k][l - 1], table[k][r - (1 << k)]).sec_min;
}

Second_min SparseTable::find_sec_min(const Second_min& m1, const Second_min& m2)
{
    int a[2] = { m1.min, m1.sec_min };
    int b[2] = { m2.min, m2.sec_min };
    int res[2] = { 0 };

    if (a[0] == a[1] && b[0] == b[1]) // dlya sluchaya (3,3) (4,4) (5,5) i t.d.
    {
        if (a[0] < b[0])
        {
            res[0] = a[0];
            res[1] = b[0];
        }
        else
        {
            res[0] = b[0];
            res[1] = a[0];
        }
    }
    else
    {
        int i = 0, j = 0, k = 0;
        for (; k < 2; ++k)
        {
            if (a[i] == b[j])
            {
                res[k] = a[i];
                ++i;
                ++j;
            }
            else if (a[i] < b[j])
            {
                res[k] = a[i];
                ++i;
            }
            else
            {
                res[k] = b[j];
                ++j;
            }
        }
    }
    return Second_min(res[0], res[1]);
}

Second_min SparseTable::find_sec_min(const VECTOR& row, int indx1, int indx2)
{
    const Second_min& m1 = row[indx1];
    const Second_min& m2 = row[indx2];
    return find_sec_min(m1, m2);
}

vector<Second_min> SparseTable::ConvertTo_SecMinVector(const vector<int>& vec)
{
    std::vector<Second_min> res;
    for (int  i = 0; i < vec.size(); ++i)
        res.push_back(Second_min(vec[i], vec[i]));
    return res;
}



int main() {

    int N = 0, M = 0;
    cin >> N >> M;

    vector<int> vect(N);

    for (int i = 0; i < N; ++i)
        cin >> vect[i];

    SparseTable table(vect);
    for (int i = 0; i < M; ++i) {
        int l = 0, r = 0;
        cin >> l >> r;
        cout << table.RMQ(l, r) << endl;
    }

    return 0;
}

