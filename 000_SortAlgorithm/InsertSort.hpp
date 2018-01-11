/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InsertSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月10日, 上午9:57
 * 
 * 插入排序—直接插入排序(Straight Insertion Sort)
 * 
 * 基本思想: 将一个记录插入到已排序好的有序表中，从而得到一个新，记录数增1的有序表。
 * 即：先将序列的第1个记录看成是一个有序的子序列，然后从第2个记录逐个进行插入，直至整个序列有序为止。
 * 要点：设立哨兵，作为临时存储和判断数组边界之用。
 * 稳定性: 插入排序是稳定的, 相等元素的前后顺序没有改变
 * 效率: 时间复杂度: O(n^2), 空间复杂度: O(1)
 * 
 */

#ifndef INSERTSORT_HPP
#define INSERTSORT_HPP

#include "Common.h"

#include <iostream>
using std::cout;
using std::endl;


// 直接插入排序: 将第一个数据看成有序表, 将后面的元素插入此表中

void InsertSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        if (arr[i] < arr[i - 1]) {
            int temp = arr[i]; // 保存要出入的元素
            int j = i - 1; // 有序表中最后一个元素的位置
            arr[i] = arr[i - 1]; // 先移走有序表最后一个元素
            while (j >= 0 && temp < arr[j]) {
                arr[j] = arr[j - 1]; // 有序表元素依次后移
                j--;
            }
            arr[j + 1] = temp; // 将保存的元素插入到正确的位置
        }
        ShowArr(arr, len);
    }
}

void TestInsertSort() {
    int arr[10] = {12, 3, 66, 999, 35, 77, 112, 465, 908, 232};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    InsertSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}

/*
 * 插入排序—折半插入排序(二分插入)
 * 基本思想: 将有序数列折半，看看插入到哪个序列中去
 * 效率: 
 */

// 折半插入

void BInsertSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int low = 0, high = i;
        if (arr[i] < arr[i - 1]) { //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入    
            int temp = arr[i]; // 保存待排序元素
            arr[i] = arr[i - 1];
            while (low <= high) { // 折半查找有序表中的插入位置
                int mid = (low + high) / 2;
                if (temp < arr[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            int j = i - 1;
            for (; j > high; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = temp; // 插入到正确位置

        }
        ShowArr(arr, len);
    }
}

void TestBInsertSort() {
    int arr[10] = {12, 3, 66, 999, 35, 77, 112, 465, 908, 232};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BInsertSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}


/*
 * 
 * 基本思想: 通过一个辅助的循环数组, 
 * 如果大于最大的元素, 则插入至尾部, 
 * 如果小于最小的元素, 则插入至头部, 
 * 如果在两者之间, 采用折半查找的方式,移动一部分的元素
 * 
 * 设计到循环数组的中间值的查找和数据移动的问题:
 * 循环数组: 实际插入数组尾部的元素作为起点, 循环时使用 (first + step) % len, 作为实际数组的下标. 
 * 
 * 效率: 时间复杂度: O(n^2), O(n)
 * 折半查找可以减少比较次数, 首尾插入又不需要移动元素, 移动次数为[(n^2)/8]
 * 需要n个辅助空间
 *
 */

// 2-路插入排序

void DoubleInsertSort(int arr[], int len) {
    int final = 0;
    int first = 0;
    int *temp = new int[len]; // 建立一个临时数组

    temp[0] = arr[0]; // 也可以将 temp[0] 元素作为不变位置的, 在之后的二分位置时多比较一次

    for (int i = 1; i < len; i++) {
        if (arr[i] > temp[final]) { // 大于最大值
            final = (final + 1 + len) % len;
            temp[final] = arr[i];
        }
        else if (arr[i] < temp[first]) { // 小于最小值
            first = (first - 1 + len) % len;
            temp[first] = arr[i];
        }
        else {
            // 折半查找插入
            int low = 0, high = final + (len - first);
            while (low <= high) {
                int mid = (low + high) / 2;
                if (arr[i] < temp[(first + mid + len) % len]) {
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }

            temp[final + 1] = temp[final]; // 先转移最后一个元素

            // 然后依次转移间隔 high 位置 --> final之间的元素(不包括边界)
            for (int j = final + (len - first) - 1; j > high; j--) {
                temp[(j + first + 1) % len] = temp[(j + first) % len];
            }
            temp[(high + first + 1) % len] = arr[i];
            final = (final + 1 + len) % len;
        }

        ShowArr(temp, len);
    }

    // 复制数组
    for (int i = 0; i < len; i++) {
        arr[i] = temp[(first + i) % len];
    }

    delete []temp;

    return;
}

void TestDoubleInsertSort() {
    int arr[10] = {12, 3, 66, 999, 35, 77, 112, 465, 908, 232};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    DoubleInsertSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}


/*
 * 希尔排序: 缩小增量排序, 应该算是插入排序的一种
 * 基本思想: 先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，
 * 待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。
 * 
 * 简单处理增量序列：增量序列d = {n/2 ,n/4, n/8 .....1} n为要排序数的个数
 * 
 * 效率: 效分析很难，关键码的比较次数与记录移动次数依赖于增量因子序列d的选取，特定情况下可以准确估算出关键码的比较次数和记录的移动次数。目前还没有人给出选取最好的增量因子序列的方法
 * 增量因子中除1 外没有公因子，且最后一个增量因子必须为1
 * 
 * 稳定性: 不稳定的排序方法
 */


// 希尔排序: 取增量为d1的分为一组, 共分成d1组分别进行插入排序, 然后每组对应元素放在一起, 再取增量d2..., 直到增量dn = 1

void ShellSort(int arr[], int len) {
    int dk;
    int temp;
    for (dk = len / 2; dk > 0; dk /= 2) { // 增量分隔
        for (int i = dk; i < len; i++) { // 从每组元素的尾部开始比较
            temp = arr[i];
            int j = i;
            for (; j >= dk; j -= dk) // 向前遍历本数组, 插入排序
                if (temp < arr[j - dk])
                    arr[j] = arr[j - dk];
                else
                    break;
            arr[j] = temp; // 插入到本分隔序列中的应当位置
        }

        ShowArr(arr, len);
    }
}

void TestShellSort() {
    int arr[10] = {12, 3, 66, 999, 35, 77, 112, 465, 908, 232};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    ShellSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
    return;
}



#endif /* INSERTSORT_HPP */

