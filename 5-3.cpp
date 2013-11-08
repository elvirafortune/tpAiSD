#include <iostream>
#include <stdint.h>

bool get_num(int64_t element, int bitnum);
void partition(int64_t* a, int &i, int &j, int num);

void binquick_sort(int64_t *a , int left , int right , int num) {
    int i = left;
    int j = right;
    if ( right <= left || num < 0)
        return;

    partition(a, i, j, num);
    if ( get_num (a[right] , num) == 0)
        j++;

    binquick_sort(a, left, j-1, num-1);
    binquick_sort(a, j, right, num-1);
}

void partition(int64_t* a, int &i, int &j, int num) {
    while (j != i) {
        while (get_num(a[i], num) == 0 && (i < j))
            i++;
        while (get_num(a[j], num) == 1 && (j > i))
            j--;
        std::swap(a[i], a[j]);
    }
}

bool get_num(int64_t element, int bitnum) {
    return ((element >> bitnum) & 0x1);
}

int main() {

    int n = 0;
    int n64= 63;
    std::cin >> n;
    int64_t *a = new int64_t[n];

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    binquick_sort(a, 0, n-1, n64);

    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    return 0;
};
