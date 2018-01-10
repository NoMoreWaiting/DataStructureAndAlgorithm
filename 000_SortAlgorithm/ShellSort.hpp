/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShellSort.hpp
 * Author: xuwei.huang
 *
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
 * 
 * Created on 2018年1月10日, 下午3:33
 */

#ifndef SHELLSORT_HPP
#define SHELLSORT_HPP

#include "Common.h"
#include <iostream>
using std::cout;
using std::endl;


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



#endif /* SHELLSORT_HPP */

