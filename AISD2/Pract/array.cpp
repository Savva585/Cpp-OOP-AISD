#include <iostream>
#include <unordered_set>
using namespace std;

void reverseArray(int *arr, int size)
{
    if (!size || !arr)
        return;
    int buf = 0;
    int cnt = size - 1;
    for (int i = 0; i < size / 2; ++i)
    {
        buf = arr[i];
        arr[i] = arr[cnt];
        arr[cnt] = buf;
        cnt--;
    }
}

void shiftRight(int *arr, int size, int k)
{
    if (!arr || !size || !k)
        return;
    int buf = 0;
    while (k)
    {
        buf = arr[0];
        arr[0] = arr[size - 1];
        for (int i = size - 1; i > 1; ++i)
        {
            arr[i] = arr[i - 1];
        }
        arr[1] = buf;
        k--;
    }
}

int removeDuplicatesInSort(int *arr, int size)
{
    if (!arr || size <= 1)
        return size;

    int newSize = size;
    int i = 0;

    while (i < newSize - 1)
    {
        if (arr[i] == arr[i + 1])
        {
            for (int j = i + 1; j < newSize - 1; ++j)
            {
                arr[j] = arr[j + 1];
            }
            --newSize;
        }
        else
        {
            ++i;
        }
    }

    return newSize;
}
int findSecondMax(const int *arr, int size)
{
    if (!arr || size < 2)
        return -1;

    int max = arr[0];
    int second_max = INT_MIN;

    for (int i = 1; i < size; ++i)
    {
        if (arr[i] > max)
        {
            second_max = max;
            max = arr[i];
        }
        else if (arr[i] > second_max && arr[i] < max)
        {
            second_max = arr[i];
        }
    }

    return (second_max == INT_MIN) ? -1 : second_max;
}

void moveZeroes(int *arr, int size)
{
    if (!arr || !size)
        return;

    int cnt = 0;
    int currentSize = size;

    for (int i = 0; i < currentSize;)
    {
        if (arr[i] == 0)
        {
            ++cnt;
            --currentSize;
            for (int j = i; j < currentSize; ++j)
            {
                arr[j] = arr[j + 1];
            }
            arr[currentSize] = 0;
        }
        else
        {
            ++i;
        }
    }
}

bool binaryFind(int *arr, int size, int target)
{
    if (!arr)
        return false;
    int left = 0;
    int right = size - 1;
    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        if (arr[middle] == target)
            return true;
        if (arr[middle] > target)
        {
            right = middle - 1;
            continue;
        }
        else
        {
            left = middle + 1;
            continue;
        }
    }
    return false;
}

bool is_palindrom(int *arr, int size)
{
    if (!arr || size == 0)
    {
        return true;
    }
    for (int i = 0; i < size / 2; ++i)
    {
        if (arr[i] != arr[size - 1 - i])
            return false;
    }
    return true;
}

void sort_bubble(int *arr, int size)
{
    if (!arr || size == 0 || size == 1)
        return;
    for (int i = 0; i < size - 1; ++i)
    {
        bool flag = true;
        for (int j = 0; j < size - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                flag = false;
                int buf = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = buf;
            }
        }
        if (flag == true)
            return;
    }
}

void sort_selection(int *arr, int size)
{
    if (!arr || size <= 1) return;
    
    for (int i = 0; i < size - 1; ++i)
    {
        int min_ind = i;           
        int min = arr[i];          
        
        for (int j = i + 1; j < size; ++j)  
        {
            if(arr[j] < min){
                min = arr[j];      
                min_ind = j;      
            }
        }
        
        if(min_ind != i){          
            int buf = arr[i];
            arr[i] = arr[min_ind];
            arr[min_ind] = buf;
        }
    }
}


void sort_insertion(int* arr, int size) {
    if (!arr || size <= 1) return;
    
    for (int i = 1; i < size; ++i) {
        int key = arr[i];        
        int j = i - 1;           
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        
        arr[j + 1] = key;
    }
}