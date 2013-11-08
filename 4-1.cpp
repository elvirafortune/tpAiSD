#include <iostream>

int* merge(int *a, int *b, int n) {

    int* rezult = new int[n];

    for (int i = 0, j = 0; i < n && j < n && (i+j) < n;) {
        if (a[i] < b[j]) {
            rezult[i+j] = a[i];
            ++i;
        } else {
            rezult[i+j] = b[j];
            ++j;
        }
    }
    delete[] a;
    return rezult;
}

void build_heap(int *a, int n) {

    for (int i = n/2; i >= 1; --i) {
        for (int j = i; j <= n/2; ) {
            int k = j*2;
            
            if ((k+1 <= n) && (a[k] < a[k+1]))
                ++k;

            if (a[j] < a[k]) {
                std::swap(a[k], a[j]);
                j = k;
            } else
                break;
        }
    }
}

void add_heap(int *a, int n) {

    std::swap(a[n], a[1]);

    for (int i = 1; 2*i < n; ) {
        i *= 2;

        if ((a[i] < a[i+1]) && (i+1 < n))
            ++i;

        if (a[i/2] < a[i])
            std::swap(a[i/2], a[i]);
    }
}

void heap_sort(int *a, int n) {
    build_heap(a-1, n);
    for (int i = 0; i < n; ++i)
        add_heap(a - 1, n - i);
}



int main() {

    int n;
    int k;
    const int max = 10000000000000;

    std::cin >> n;
    std::cin >> k;

    int* a = new int[k];
    int* b = new int[k];

    if (k < n) {
        for (int j = 0; j < k; ++j)
            std::cin >> a[j];
    }
    else
        return 0;

    heap_sort(a, k); //otsortiruem dlya sliyaniya

    int i = k;
    while (i < n) {
        int unused = 0; 
        if ((i+k) < n) {
            i = i + k;
            for (int j = 0; j < k; ++j)
                std::cin >> b[j];
        } else {
            unused = n - i;
            for (int j = 0; j < k; ++j) {
                if (j < unused)
                    std::cin >> b[j];
                else
                b[j] = max;//zapolnyaem ostavshiesya dabi ne meshat' osnovnoy sortirovke
            i = n;
            }
        }
        if (i != n)
            heap_sort(b, k);
        else
            heap_sort(b, unused);
        a = merge(a, b, k);
    }

    for (int j = 0; j < k; j++)
        std::cout << a[j] << " ";

    delete[] b;
    delete[] a;
  //  system("PAUSE");


    return 0;
};
