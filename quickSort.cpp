#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end) ;
public:
    static void QuickSort(T* start, T* end) ;
};
#endif /* SORTING_H */
template <class T>
T* Sorting<T>::Partition(T* start, T* end) {
    T pivot = *start; // Choose the first element as the pivot
    T* i = start;
    T* j = end;

   while (true) {
        // Find the rightmost element smaller than or equal to the pivot
        do {
            --j;
        } while (*j > pivot);

        // Find the leftmost element greater than or equal to the pivot
        do {
            ++i;
        } while (*i < pivot);

        // If the pointers meet or cross, the partitioning is done
        if (i >= j) {
            break;
        }

        // Swap *i and *j
        T temp = *i;
        *i = *j;
        *j = temp;
    }

    // Swap *start (pivot) with *j
    T temp = *start;
    *start = *j;
    *j = temp;
    return j; // Return the partitioning index
};
template <class T>
void Sorting<T>::QuickSort(T* start, T* end) {
    // TODO
    // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
    if (start < end) {
        // Partition the array into two halves and get the partitioning index
        T* partitionIndex = Partition(start, end);

        cout << partitionIndex - start << ' ';
        // Recursively sort elements before and after the partitioning index
        QuickSort(start, partitionIndex);
        QuickSort(partitionIndex + 1, end);
    }
    
};
int main(){
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
}