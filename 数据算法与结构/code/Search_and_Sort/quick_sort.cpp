#include <iostream>
#include <algorithm>

// 三点取中法选择基准值
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    // 将low, mid, high三个值按大小排序
    if (arr[low] > arr[mid])
        std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high])
        std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high])
        std::swap(arr[mid], arr[high]);
    
    // 使用中间值作为基准值
    std::swap(arr[mid], arr[high - 1]); // 将基准值放在high-1的位置
    return arr[high - 1];
}

// 分区函数
int partition(int arr[], int low, int high) {
    int pivot = medianOfThree(arr, low, high);  // 基准值为三点取中的值
    int i = low;
    int j = high - 1;  // pivot已经放在high - 1的位置
    
    while (true) {
        // 从左边找到第一个比pivot大的元素
        while (arr[++i] < pivot);
        // 从右边找到第一个比pivot小的元素
        while (arr[--j] > pivot);
        
        if (i < j)
            std::swap(arr[i], arr[j]);
        else
            break;
    }
    
    // 将pivot放回正确的位置
    std::swap(arr[i], arr[high - 1]);  // i是第一个比pivot大的位置
    return i;  // 返回pivot的最终位置
}

// 快速排序主函数
void quickSort(int arr[], int low, int high) {
    if (low + 10 <= high) {  // 使用插入排序的阈值，可以根据需要调整
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    } else {
        // 当子数组较小时，使用插入排序优化
        for (int i = low + 1; i <= high; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j > low && arr[j - 1] > temp; --j)
                arr[j] = arr[j - 1];
            arr[j] = temp;
        }
    }
}

// 快速排序的外部接口
void quickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

int main() {
    int arr[] = {24, 97, 40, 67, 88, 85, 15, 66, 53, 44};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    quickSort(arr, n);
    
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}