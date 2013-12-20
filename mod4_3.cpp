#include <iostream>
#include <vector>
using namespace std;


class Piramid_Table {
  
    vector<long long> vec;
    int block_count;
             
public:  
    Piramid_Table(int N) : vec(N*(N+1)/2, 0) { //nam dostatochno polovini matrici (ta chto pod diagonal'u)
        block_count = N;
    }

    int index(int x, int y) const {
        return (2*block_count - (y - 1))*(y - 1)/2 + (x - 1); // preobrazuem koordinati matr k indexu v vectore
    }

    long long get(int x, int y) const {
        return vec[index(x, y)];
    }
        
    long long Fill_func(const Piramid_Table &table, int x, int y) {
        long long sum = 0;
        for (int i = 1; i <= y; ++i) {
            if (x - i < 0)
                break;
            if (x - i == 0)
                sum += 1;
            else
                sum += table.get(x - i, i);
        }
        return sum;
    }

    void Fill_Table() {
        for(int i = 1; i <= block_count; ++i)
            for(int j = 1; j <= block_count - i + 1; ++j)
                vec[index(j, i)] = Fill_func(*this, j, i);
    }

    long long CountVariations(int N) {
        if (N < 0)
            return 0;
        else if (N == 0)
            return 1;
        else {
        Piramid_Table table(N);
        table.Fill_Table();
        long long result = Fill_func(table, N, N);
        return result;
        }
    }

};


int main() {
    int n;
    cin >> n;
    Piramid_Table p(n);
    cout << p.CountVariations(n);
   //system("pause");
    return 0;
}