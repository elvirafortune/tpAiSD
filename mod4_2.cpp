#include <iostream>
#include <vector>
using namespace std;

vector<vector<long long> > Numbers(10);

void CountNumbers(int size, vector<long long> &vec) {
    if (size == 0) {
        return;
    }
    vector<long long> buf(10);
  
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < Numbers[i].size(); ++j) {
            buf[i] += vec[Numbers[i][j]];
        }
    }
    vec = buf; // xranim kol-vo chisel nachin. na index massiva
    CountNumbers(size - 1, vec);
}

int main()
{
    Numbers[0].push_back(4);
    Numbers[0].push_back(6);
    
    Numbers[1].push_back(6);
    Numbers[1].push_back(8);
    
    Numbers[2].push_back(7);
    Numbers[2].push_back(9);
    
    Numbers[3].push_back(4);
    Numbers[3].push_back(8);
    
    Numbers[4].push_back(0);
    Numbers[4].push_back(3);
    Numbers[4].push_back(9);
    
    Numbers[6].push_back(1);
    Numbers[6].push_back(7);
    Numbers[6].push_back(0);
    
    Numbers[7].push_back(2);
    Numbers[7].push_back(6);
    
    Numbers[8].push_back(1);
    Numbers[8].push_back(3);
    
    Numbers[9].push_back(4);
    Numbers[9].push_back(2);
    
    vector<long long> buf;
    for (int i = 0; i < 10; ++i) {
        buf.push_back(1);
    }
    int size;
    std::cin >> size;
    long long count = 0;

    CountNumbers(size - 1, buf);

    for (int i = 0; i < buf.size(); ++i) {
        if (i != 0 && i!= 8) {
            count += buf[i];
        }
    }
    std::cout << count;
    //system("pause");
    return 0;
}

