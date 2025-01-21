#include<iostream>
#include<vector>
#include<mutex>
#include<future>
#include"Header.h"

using namespace std;

int threadNum = 1;           // ����� ������
int threadNumber = 8;        // ���������� �������
bool threadNeed = true;      // ���� ������ ��������� ������������� �������
std::mutex mx;               // ������� ��� ����������������� ����������� ���������� 'threadNum'

/* ������� ������� ������ ��������� � �������� ������ */
void merge(int* arr, int l, int m, int r)  // ������� ������ ��������� � �������� ������
{
    int nl = m - l + 1;
    int nr = r - m;

    vector<int> left;                // ������� ��������� �������
    vector<int> right;

    for (int i = 0; i < nl; i++)     // ���������� ������ �� ��������� �������
        left.push_back(arr[l + i]);
    for (int j = 0; j < nr; j++)
        right.push_back(arr[m + 1 + j]);

    int i = 0, j = 0;
    int k = l;                       // ������ ����� �����

    while (i < nl && j < nr)
    {
        if (left[i] <= right[j])     // �������� ����������� �������� ������� �� ������� ������
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
    while (i < nl)                   // �������� ���������� �������� ����� �����
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < nr)                   // �������� ���������� �������� ������ �����
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

/* ����������� ������� ���������� */
void mergeSort(int* arr, int l, int r)
{
    if (l >= r) return;              // ����� �� ��������

    int m = l + (r - l) / 2;

    future<void> f;
    if (threadNum - 1 < threadNumber && threadNeed)  // ��������� ������������� ���������� ��� ������������� � � ������� ������������ ����������� �������
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
    if (f.valid())     // ���������, ��� �� ������� ����������� �������
    {
        f.get();                         // ��������� ���������� ������������ ����������
    }
    merge(arr, l, m, r);
}