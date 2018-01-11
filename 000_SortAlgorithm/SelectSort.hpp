/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SelectSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月10日, 下午4:06
 * 
 * 基本思想: 在要排序的一组数中，选出最小（或者最大）的一个数与第1个位置的数交换；
 * 然后在剩下的数当中再找最小（或者最大）的与第2个位置的数交换，依次类推
 * 
 */

#ifndef SELECTSORT_HPP
#define SELECTSORT_HPP

#include "Common.h"

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;


//简单选择排序：遍历一次找到最小与第一个元素呼唤位置，再从第二个元素开始遍历找到最小与第二个元素呼唤位置...  

void SelectSort(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        int k = i; // 记录最小元素的位置
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[k])
                k = j;
        }
        if (k != i) { // 需要交换位置
            arr[i] = arr[i] + arr[k];
            arr[k] = arr[i] - arr[k];
            arr[i] = arr[i] - arr[k];
        }

        ShowArr(arr, len);
    }
}



/*
 * 二元选择排序, 是对直接选择排序的改进
 * 
 * 基本思想: 在直接选择排序选择最小值的基础上, 同时选择出最大值
 * 减小比较次数. 交换次数并没有减少多次
 * 
 */


// 二元选择排序

void BinarySelectSort(int arr[], int len) {

    for (int i = 0; i < len / 2; i++) {
        for (int j = i + 1; j <= len - i - 1; j++) {
            // 博客原文先记录标志位然后使用特殊位置判断来交换元素. 这里直接先做两次交换, 后面在做一次保险判断
            int min = i, max = len - i - 1; // 假定首位最小, 尾部最大.
            if (arr[j] < arr[min]) { // 过滤首部最小, 立即交换
                int temp = arr[min];
                arr[min] = arr[j];
                arr[j] = temp;
            }
            if (arr[max] < arr[j]) { // 选出尾部最大, 立即交换. 因为前面已经判断过, 此元素必定不是最小的, 换值之后不会影响最小值的筛选
                int temp = arr[max];
                arr[max] = arr[j];
                arr[j] = temp;
            }

            if (arr[j] < arr[min]) { // 判断, 防止交换错误
                int temp = arr[min];
                arr[min] = arr[j];
                arr[j] = temp;
            }
        }

        ShowArr(arr, len);
    }
}





/*
 * 选择排序 -- 堆排序
 * 
 * 平均时间复杂度: O(n * log n)
 * 最好情况: O(n * log n)
 * 最坏情况: O(n * log n)
 * 空间复杂度: O(1)
 * 排序方式: in-place
 * 稳定性: 不稳定
 * 
 * 基本思想:
 * 
 * 注意要点:
 * 
 * 
 */

// 数组是从0开始的, 所以选择0编号开头
// 堆编号的选择: 
// 从0开始: 
// 父节点: n, 子节点: 2n+1, 2n+2; 
// 子节点: n, 父节点: n/2-1;
// 从1开始: 
// 父节点: n, 子节点: 2n, 2n+1; 
// 子节点: n, 父节点: n/2

// 第二步: 调整堆

void heapAdjust(int a[], int start, int end) { // 这里将堆的第一个元素编号为1
    // 调整为小根堆, 从小到大
    // 方法一:
    int rc = a[start]; // 保存要调整的元素

    // 将要调整的元素
    for (int l = 2 * start + 1; l <= end; l = 2 * l + 1) {
        if (l < end && a[l] > a[l + 1]) { // 判断左右子树大小, j<end, 保证了j+1 <= end, 也就不会越界
            l++;
        }
        // 方法一:
        if (rc <= a[l]) {
            // 方法二:
            //        if (a[start] <= a[j]) {
            break;
        }
        else {
            // 方法二:
            //            int temp = a[start];
            a[start] = a[l]; // 这里将父节点取到较大孩子节点的值. (有了j++的保证). (注意:这里堆中有了相同节点的值, 所以使用 rc <= a[j] 来判断, 打印中也会出现重复元素)
            start = l; // 当堆编号从1开始而不是0时: 父节点:n, 子节点为: 2n, 2n+1.  子节点为:n, 父节点为n/2
            // 方法二:
            //            a[start] = temp;
        }

        ShowArr(a, end);
    }
    // 方法一:
    a[start] = rc; // 此时start已经变为 要调整值 应该存放的位置了
    ShowArr(a, end);
}


// 第一步: 建堆

void createHeap(int a[], int n) {
    // 小根堆
    for (int i = n / 2 - 1; i > 0; i--) {
        heapAdjust(a, i, n - 1);
    }
}

// 考虑一下: 父节点与子节点比较时, 有左孩子没有有孩子的情况???

// 小根堆排序, 输出从大到小

void HeapSort(int a[], int n) {
    createHeap(a, n); // 建立小根堆
    for (int i = n - 1; i > 0; i--) {
        // 堆顶元素(最小)与最后一个元素互换, 最后一个元素变最小值
        Swap(a[0], a[i]);
        heapAdjust(a, 0, i - 1); // 去除最后一个元素后, 重新调整堆为小堆
    }
}

// 大根堆

void bigHeapAdjust(int a[], int start, int end) {
    int rc = a[start];
    for (int l = 2 * start + 1; l <= end; l = 2 * l + 1) {
        if (l < end && a[l] < a[l + 1]) {
            l++;
        }
        if (rc >= a[l])
            break;
        else {
            int temp = a[start];
            a[start] = a[l];
            start = l;
            a[start] = temp;
        }
        ShowArr(a, end);
    }


    return;
}

void createBigHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        bigHeapAdjust(a, i, n - 1);
    }
    cout << "建堆后: ";
    ShowArr(a, n);

}

void BigHeapSort(int a[], int n) {
    createBigHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
        Swap(a[0], a[i]);
        bigHeapAdjust(a, 0, i - 1); // i-1, 调整剩下的元素. 少一个
    }
}

void TestSelectSort() {
    int arr[10] = {12, 3, 66, 999, 35, 77, 112, 465, 908, 232};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    SelectSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}

void TestBinarySelectSort() {
    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BinarySelectSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}

void TestHeapSort() {
    int arr[10] = {3, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    HeapSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);

}

void TestBigHeapSort() {
    int arr[10] = {3, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BigHeapSort(arr, len);
    cout << "BigHeapSort 排序后: ";
    ShowArr(arr, len);

    fflush(stdout);
}





#endif /* SELECTSORT_HPP */

