#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void selectSort(int arr[], int n)
{
    int i, j , minValue, tmp;
    for(i = 0; i < n-1; i++)
    {
        minValue = i;
        for(j = i + 1; j < n; j++)
        {
            if(arr[minValue] > arr[j])
            {
                minValue = j;
            }
        }
        if(minValue != i)
        {
            tmp = arr[i];
            arr[i] = arr[minValue];
            arr[minValue] = tmp;
        }
    }
}

void bubbleSort(int arr[], int n)
{
    int i, j, tmp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 1; j < n; j++)
        {
            if(arr[j] < arr[j - 1])
            {
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
            }
        }
    }
}
void bubbleSort_1(int arr[], int n)
{
    int i, nflag, tmp;
    do
    {
        nflag = 0;
        for(i = 0; i < n - 1; i++)
        {
            if(arr[i] > arr[i + 1])
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                nflag = i + 1;
            }
        }
        n = nflag;
    }while(nflag);
}

void insertSort(int arr[], int n)
{
    int i, j, tmp;

    for(i = 1; i < n; i++)
    {
        for(j = i; j > 0; j--)
        {
            if(arr[j] < arr[j-1])
            {
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
            }
            else
            {
                break;
            }
        }
    }

    return;
}

void insertSort_1(int arr[], int n)
{
    int i, j, tmp, elem;

    for(i = 1; i < n; i++)
    {
        elem = arr[i];
        for(j = i; j > 0; j--)
        {
            if(elem < arr[j-1])
            {
                arr[j] = arr[j-1];
            }
            else
            {
                break;
            }
        }
        arr[j] = elem;
    }

    return;
}

void shellSort(int arr[], int n)
{
    int i, j, elem;
    int k = n/2;

    while(k>=1)
    {
        for(i = k; i < n; i ++)
        {
            elem = arr[i];
            for(j = i; j >= k; j-=k)
            {
                if(elem < arr[j-k])
                {
                    arr[j] = arr[j-k];
                }
                else
                {
                    break;
                }
            }
            arr[j] = elem;
        }
        k = k/2;
    }
}

void merge(int arr[], int l, int mid, int r)
{
    int len,i, pl, pr;
    int *tmp = NULL;

    len = r - l + 1;
    tmp = (int*)malloc(len * sizeof(int));  //申请存放完整序列内存
    memset(tmp, 0x0, len * sizeof(int));

    pl = l;
    pr = mid + 1;
    i  = 0;
    while(pl <= mid && pr <= r)  //两个子序列都有值，比较最小值
    {
        if(arr[pl] < arr[pr])
        { 
            tmp[i++] = arr[pl++];
        }
        else
        {
            tmp[i++] = arr[pr++];
        }
    }
    while(pl <= mid)        //左边子序列还有值，直接拷贝到新序列中
    {
        tmp[i++] = arr[pl++];
    }
    while(pr <= r)      //右边子序列还有值
    {
        tmp[i++] = arr[pr++];
    }

    for(i = 0; i < len; i++)
    {
        arr[i+l] = tmp[i];
    }

    free(tmp);
    return;
}
int min(int x, int y)
{
    return (x > y)? y : x;
}
/*
归并完成的条件是得到子序列长度等于n，用sz表示当前子序列的长度。从1开始每次翻倍直到等于n。根据上面归并的方法，从i=0开始分组，下一组坐标应该i + 2*sz，第i组第一个元素为arr[i],最右边元素应该为arr[i+2*sz -1]，遇到序列最右边元素不够分组的元素个数时应该取n-1,中间的元素为arr[i+sz -1],依次类推进行归并得到完整的序列
*/
void mergeSortBu(int arr[], int n)
{
    int sz, i, mid,l, r;
    for(sz = 1; sz < n; sz+=sz)
    {
        for(i = 0; i < n - sz; i += 2*sz)
        {
            l = i;
            r = i + sz + sz;
            mid = i + sz -1;
            merge(arr, l, mid, min(r-1, n-1));
        }
    }
    return;
}

void mergeSort(int arr[], int l, int r)
{
    if(l >= r)
    {
        return;
    }

    int mid = (l + r)/2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid+1, r);
    merge(arr, l, mid, r);
    return;
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a  = *b;
    *b  = tmp;
    return;
}
//arr[l+1...j] < arr[l], arr[j+1,..i)>arr[l]
static int partition(int arr[], int l, int r)
{
    int i, j;
    i = l + 1;
    j = l;

    while(i <= r)
    {
        if(arr[i] > arr[l])
        {
            i++;
        }
        else
        {
            swap(&arr[j + 1], &arr[i]);
            i++;
            j++;
        }
    }
    swap(&arr[l], &arr[j]);
    return j;
}

static void _quickSort(int arr[], int l, int r)
{
    int key;
    if(l >= r)
    {
        return;
    }
    key = partition(arr, l, r);
    _quickSort(arr, l, key - 1);
    _quickSort(arr, key + 1, r);
}

void quickSort(int arr[], int n)
{
    _quickSort(arr, 0, n - 1);
    return;
}




/*parent(i) = (i-1)/2
  left child  (i) = 2*i + 1
  right child (i) = 2*i + 2
*/



 void shiftUp(int arr[], int n, int k)
 {
    while((k - 1)/2 >= 0 && arr[k] > arr[(k - 1)/2])
    {
        swap(&arr[k], &arr[(k-1)/2]);
        k = (k - 1)/2;
    }
    return;
 }

 void shiftDown(int arr[], int n, int k)
 {
    int j = 0 ;

     while(2*k + 1 < n)
     {
        j = 2 *k + 1;
        if (j + 1 < n && arr[j] < arr[j+1])
        {
            j ++;   
        }

        if(arr[k] < arr[j])
        {
            swap(&arr[k], &arr[j]);
            k = j;
        }
        else
        {
            break;
        }
     }

     return;
 }

 void heapSort(int arr[], int n)
 {
    int i = 0;
    for(i = (n - 1 -1)/2; i >=0; i--)
    {
        shiftDown(arr, n, i);
    }

    for(i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        shiftDown(arr, i, 0);
    }
    return;
 }

 
 

void printArray(int arr[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int arr[10] = {2,5,6,4,3,7,9,8,1,0};
    printArray(arr, 10);
    selectSort(arr, 10);
    printArray(arr, 10);
    bubbleSort(arr,10);
    printArray(arr, 10);
    bubbleSort_1(arr,10);
    printArray(arr, 10);
    insertSort(arr,10);
    printArray(arr, 10);
    bubbleSort_1(arr,10);
    printArray(arr, 10);
    shellSort(arr,10);
    printArray(arr, 10);
    mergeSortBu(arr,10);
    printArray(arr, 10);
    mergeSort(arr,1,10);
    printArray(arr, 10);
    quickSort(arr,10);
    printArray(arr, 10);
    heapSort(arr,10);
    printArray(arr, 10);
    return 0;
}




