#ifndef __SORT_H__
#define __SORT_H__

void InsertionSort(int *arr, int size);
void BubbleSort(int *arr, int size);
void SelectionSort(int *arr, int size);
void ShellSort(int *arr, int size);
void HeapSort(int *arr, int size);
void percdown(int *arr, int size, int position);
void MergeSort(int *arr, int lo, int hi);
void merge(int *arr, int lo, int mi, int hi);
void QuickSort(int *arr, int size);
void qsort(int *arr, int lo, int hi);

#endif
