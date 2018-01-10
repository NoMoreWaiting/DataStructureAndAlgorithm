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

// 双向选择排序

void BinarySelectSort(int arr[], int len) {

    for (int i = 0; i < len / 2; i++) {
        for (int j = i + 1; j <= len - i - 1; j++) {
            int min = i, max = len -i -1; // 假定首位最小, 尾部最大.
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
            
            if(arr[j] < arr[min]){ // 判断, 防止交换错误
                int temp = arr[min];
                arr[min] = arr[j];
                arr[j] = temp;
            }
        }

        ShowArr(arr, len);
    }
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




#endif /* SELECTSORT_HPP */

