#include<iostream>
#include<vector>
#include<mutex>
#include<future>
#include"Header.h"

using namespace std;

int threadNum = 1;           // номер потока
int threadNumber = 8;        // количество потоков
bool threadNeed = true;      // флаг работы алгоритма многопоточным методом
std::mutex mx;               // мьютекс для потокобезопасного определения переменной 'threadNum'

/* функция слияния записи элементов в исходный массив */
void merge(int* arr, int l, int m, int r)  // функция записи элементов в исходный массив
{
    int nl = m - l + 1;
    int nr = r - m;

    vector<int> left;                // создать временные массивы
    vector<int> right;

    for (int i = 0; i < nl; i++)     // копировать данные во временные массивы
        left.push_back(arr[l + i]);
    for (int j = 0; j < nr; j++)
        right.push_back(arr[m + 1 + j]);

    int i = 0, j = 0;
    int k = l;                       // начало левой части

    while (i < nl && j < nr)
    {
        if (left[i] <= right[j])     // записать минимальные элементы обратно во входной массив
        {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < nl)                   // записать оставшиеся элементы левой части
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < nr)                   // записать оставшиеся элементы правой части
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

/* рекурсивная функция сортировки */
void mergeSort(int* arr, int l, int r)
{
    if (l >= r) return;              // выйти из рекурсии

    int m = l + (r - l) / 2;

    future<void> f;
    if (threadNum - 1 < threadNumber && threadNeed)  // запустить многопоточное выполнение при необходимости и с заранее определенным количеством потоков
    {
        mx.lock();
        cout << "<thread number " << threadNum++ << " is active> ";
        f = async(launch::async, [arr, l, m]() {mergeSort(arr, l, m); });
        mx.unlock();
    }
    else
    {
        mergeSort(arr, l, m);
    }

    mergeSort(arr, m + 1, r);
    if (f.valid())     // проверить, был ли запущен асинхронный процесс
    {
        f.get();                         // дождаться завершения асинхронного вычисления
    }
    merge(arr, l, m, r);
}