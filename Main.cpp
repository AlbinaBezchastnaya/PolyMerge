#include<iostream>
#include<random>
#include"Header.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    system("chcp 1251");      // строка для корректного отображения кириллических символов
    long arr_size = 2000000;  // размер массива для сортировки
    // srand(0);
    int* array = new int[arr_size];
    for (long i = 0; i < arr_size; i++) {
        array[i] = rand() % 10000;
    }
    if (arr_size < 51)        // если количество элементов в массиве не превышат 50
    {
        cout << "Массив до сортировки: " << endl;
        for (int i = 0; i < arr_size; i++) cout << array[i] << " ";  // отобразить массив до сортировки
        cout << endl;
    }
    int r = arr_size - 1;
    int l = 0;
    cout << "Список активных потоков: " << endl;
    mergeSort(array, l, r);   // функция сортировки
    cout << "\nСортировка закончена!" << endl;
    if (arr_size < 51)        // если количество элементов в массиве не превышат 50
    {
        cout << "Массив после сортировки: " << endl;
        for (int i = 0; i < arr_size; i++) cout << array[i] << " ";  // отобразить массив после сортировки
    }

    delete[] array;

    return 0;
}