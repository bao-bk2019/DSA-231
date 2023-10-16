#include<iostream>
#include<algorithm>
using namespace std;


// Modified version of Insertion Sort for varying increments
template <typename E>
void my_swap(E A[], int i, int j) {
    std::swap(A[i], A[j]);
}

template <typename E, typename Comp>
void inssort2(E A[], int n, int incr, int& swap) {
    for (int i = incr; i < n; i += incr){
        for (int j = i; (j >= incr) && (Comp::prior(A[j], A[j - incr])); j -= incr){
            my_swap(A, j, j - incr);
            swap++;
        }
    }
}
template <typename E, typename Comp>
void shellsort(E A[], int n, int& swap) { // Shellsort
  for (int i=n/2; i>1; i/=2)      // For each increment
    for (int j=0; j<i; j++)       // Sort each sublist
      inssort2<E,Comp>(&A[j], n-j, i, swap);
  inssort2<E,Comp>(A, n, 1, swap);
}

// Example comparison function
struct CustomComparator {
    static bool prior(int a, int b) {
        return a < b; // Sort in ascending order
    }
};

int main() {
    int count = 0;
    int a[]={59, 20, 17, 13, 28, 14, 23, 83, 36, 98, 11, 70, 65, 41, 42, 15};  
    int b[] = {3, 5, 6, 8, 1, 2};  
    int n = sizeof(a) / sizeof(a[0]);
    int x = sizeof(b) / sizeof(b[0]);
    // Call shellsort with the custom comparison function
    shellsort<int, CustomComparator>(a, n, count);

    // Output the sorted array
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl << count << endl;
    // Call shellsort with the custom comparison function
    count = 0;
    shellsort<int, CustomComparator>(b, x, count);

    // Output the sorted array
    for (int i = 0; i <x; ++i) {
        cout << b[i] << " ";
    }
    cout << endl << count;

    return 0;
}
