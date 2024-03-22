
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting
{
private:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *start, T *middle, T *end);

public:
    static void InsertionSort(T *start, T *end);
    static void TimSort(T *start, T *end, int min_size);
};
template <class T>
static void Sorting<T>::merge(T *start, T *middle, T *end)
{
    int leftSize = middle - start + 1;
    int rightSize = end - middle;

    T left[leftSize], right[rightSize];
    for (int i = 0; i < leftSize; ++i)
        left[i] = start[i];
    for (int j = 0; j < rightSize; ++j)
        right[j] = middle[j + 1];

    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            start[k] = left[i];
            ++i;
        }
        else
        {
            start[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < leftSize)
    {
        start[k] = left[i];
        ++i;
        ++k;
    }

    while (j < rightSize)
    {
        start[k] = right[j];
        ++j;
        ++k;
    }
}
template <class T>
static void Sorting<T>::InsertionSort(T *start, T *end)
{
    for (T *i = start + 1; i < end; ++i)
    {
        T key = *i;
        T *j = i - 1;

        while (j >= start && *j > key)
        {
            *(j + 1) = *j;
            --j;
        }

        *(j + 1) = key;
    }
}
template <class T>
static void Sorting<T>::TimSort(T *start, T *end, int min_size)
{
    // TODO
    // You must print out the array after using insertion sort and everytime calling method merge.
    const int N = end - start;

    for (int i = 0; i < N; i += min_size)
    {
        // Apply Insertion Sort to small subarrays of size min_size
        InsertionSort(start + i, start + min(i + min_size, N));

        // Print intermediate result after each insertion sort step
    }
    cout << "Insertion Sort: ";
    printArray(start, end);
    // Merge the sorted subarrays using merge function
    int i = 0;
    for (int size = min_size; size < N; size *= 2)
    {

        for (int left = 0; left < N; left += 2 * size)
        {

            int mid = left + size - 1;
            (mid > N) ? mid = (N - 1 + left) / 2 : mid;
            int right = min(left + 2 * size - 1, N - 1);
            merge(start + left, start + mid, start + right);
            // Print intermediate result after each merge step
            cout << "Merge " << ++i << ": ";
            printArray(start, end);
        }
    }
}
int main()
{
    int array[] = {19, 20, 18, 17, 12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3};
    int min_size = 4;
    Sorting<int>::TimSort(&array[0], &array[20], min_size);
}