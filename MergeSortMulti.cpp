#include <future>
#include <iostream>
#include <random>

using namespace std;
using namespace chrono;

void merge(int array[], const int left, const int mid, const int right)
{
    auto const first = mid - left + 1;
    auto const second = right - mid;

    auto* arrayOne = new int[first];
    auto* arrayTwo = new int[second];

    for (auto i = 0; i < first; i++)
        arrayOne[i] = array[left + i];
    for (auto j = 0; j < second; j++)
        arrayTwo[j] = array[mid + 1 + j];

    auto indexOne = 0, indexTwo = 0; int indexNewArray = left;

    while (indexOne < first && indexTwo < second)
    {
        if (arrayOne[indexOne] <= arrayTwo[indexTwo])
        {
            array[indexNewArray] = arrayOne[indexOne];
            indexOne++;
        }
        else
        {
            array[indexNewArray] = arrayTwo[indexTwo];
            indexTwo++;
        }
        indexNewArray++;
    }
    while (indexOne < first)
    {
        array[indexNewArray] = arrayOne[indexOne];
        indexOne++;
        indexNewArray++;
    }
    while (indexTwo < second)
    {
        array[indexNewArray] = arrayTwo[indexTwo];
        indexTwo++;
        indexNewArray++;
    }
    delete[] arrayOne;
    delete[] arrayTwo;
}

void mergeSort(int array[], const int begin, const int end)
{
    if (begin >= end)
        return;
    auto mid = begin + (end - begin) / 2;
    if (end - begin > 100000)
    {
       auto f1 = async(launch::async, [&]() { mergeSort(array, begin, mid); });        
       auto f2 = async(launch::async, [&]() { mergeSort(array, mid + 1, end); });
       f1.get();
       f2.get();
    }
    else
    {
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);        
    }
    merge(array, begin, mid, end);
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    srand(0);
    auto arr_size = 10000000;
    int* array = new int[arr_size];
    for (auto i = 0; i < arr_size; i++)
    {
        array[i] = rand() % 50000;
    }
    auto start1 = high_resolution_clock::now();
    mergeSort(array, 0, arr_size - 1);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout << "Время выполнения: " << duration1.count() << " миллисекунд" << endl;
    return 0;
}