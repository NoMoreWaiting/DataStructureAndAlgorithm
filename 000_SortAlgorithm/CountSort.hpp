/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CountSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月13日, 下午5:51
 */

#ifndef COUNTSORT_HPP
#define COUNTSORT_HPP

#include "Common.h"

#include <string.h>
#include <iostream>

/*
 * 非比较 -- 计数排序
 * 
 * 平均时间复杂度: O(n+k)
 * 最好情况: O(n+k)
 * 最坏情况: O(n+k)
 * 空间复杂度: O(k)
 * 排序方式: Out-place
 * 稳定性: 稳定
 * 
 * 基本思想: 计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。
作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。
 * 
 * 注意要点: 计数排序是典型的以空间换时间的排序算法，对待排序的数据有严格的要求，比如待排序的数值中包含负数，最大值都有限制，请谨慎使用。
 * 
 * 改进1: 
 *
 */

#define MAXNUM 20    //待排序数的最大个数
#define MAX    100   //待排序数的最大值
int sorted_arr[MAXNUM] = {0};


// 计数排序
// arr:待排序数组，sorted_arr：排好序的数组，n：待排序数组长度

void CountSort(int *arr, int *sorted_arr, int n) {
    int i;
    int *count_arr = (int *) malloc(sizeof (int) * (MAX + 1));

    //初始化计数数组   
    memset(count_arr, 0, sizeof (int) * (MAX + 1));

    // 统计i的次数   
    for (i = 0; i < n; i++)
        count_arr[arr[i]]++;
    // 对所有的计数累加，作用是统计arr数组值和小于等于于arr数组值出现的个数
    // 计算出此下标代表的值在排序号数组中首次出现的位置
    for (i = 1; i <= MAX; i++)
        count_arr[i] += count_arr[i - 1];
    // 逆向遍历源数组（保证稳定性），根据计数数组中对应的值填充到新的数组中   
    for (i = n - 1; i >= 0; i--) {
        //        int j = count_arr[arr[i]] - 1;
        //        cout << "  " << j << ": " << arr[i] << endl;

        // count_arr[arr[i]]表示arr数组中包括arr[i]和小于arr[i]的总数
        sorted_arr[count_arr[arr[i]] - 1] = arr[i];

        // 如果arr数组中有相同的数，arr[i]的下标减一
        count_arr[arr[i]]--; // 相同值的, 在排序好数组的位置就要--


    }
    free(count_arr);
}

void TestCountSort() {

    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);
    int * target = (int *) malloc(sizeof (int) * len);
    cout << "排序前: ";
    ShowArr(arr, len);

    CountSort(arr, target, len);

    cout << "排序后: ";
    for (int i = 0; i < len; i++) {
        if (0 != i) {
            cout << ", ";
        }
        cout << *(target + i);
    }
    cout << endl;
}






#endif /* COUNTSORT_HPP */

