/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SwapSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月11日, 下午4:08
 */

#ifndef SWAPSORT_HPP
#define SWAPSORT_HPP

#include "Common.h"

#include <iostream>
using std::cout;
using std::endl;

/*
 * 交换排序 -- 冒泡排序
 * 
 * 平均时间复杂度:
 * 最好情况:
 * 最坏情况:
 * 空间复杂度:
 * 排序方式:
 * 稳定性:
 * 
 * 基本思想:
 * 
 * 注意要点:
 * 
 * 改进1: 加入一标志性变量exchange，用于标志某一趟排序过程中是否有数据交换，如果进行某一趟排序时并没有进行数据交换，则说明数据已经按要求排列好，可立即结束排序，避免不必要的比较过程
 * 
 * 改进2: 添加标志位，记录最后一次交换位置的地方，证明最后一次交换位置之后的地方时排好序的，下一次只需要排最后一次之前的地方就好了
 * 
 * 改进3: 在每趟排序中进行正向和反向两遍冒泡的方法, 一次可以得到两个最终值(最大者和最小者) , 从而使排序趟数几乎减少了一半
 * 
 */

void BubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) { // 这里是从前向后比较, 依次向后堆积最大值, 所以 j < n -i-1
            if (a[j] > a[j + 1])
                Swap(a[j], a[j + 1]);
        }
        //        ShowArr(a, n);
    }
}



// 冒泡排序改进1，添加标志位，如果某一次排序中出现没有交换位置，说明排序完成  

void BubbleSort1(int a[], int n) {
    bool flag = true;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                Swap(a[j], a[j + 1]);
                flag = false;
            }
        }
        //        ShowArr(a, n);
        if (flag) {
            break;
        }
    }
}



// 冒泡排序改进2，添加标志位，记录最后一次交换位置的地方，证明最后一次交换位置之后的地方时排好序的，下一次只需要排最后一次之前的地方就好了  

void BubbleSort2(int a[], int n) {
    int flag = n - 1; // 刚开始, 设置最后交换的位置为数组的最后一位
    while (flag > 0) {// flag 逐渐变小, 最后变为0, (pos =0, 并且没有改变)
        int pos = 0;
        for (int i = 0; i < flag; i++) {
            if (a[i] > a[i + 1]) {
                Swap(a[i], a[i + 1]);
                pos = i; // 记录最近一次的交换位置
            }
        }
        flag = pos; // 记录上一轮循环中的最后交换位置
        //        ShowArr(a, n);
    }


}



// 冒泡改进3: 传统冒泡每趟排序遍历一次找到一个最大值或者最小值，每趟遍历两次就会找打一个最大值和一个最小值，减少了一半的排序趟数  

void BubbleSort3(int a[], int n) {
    int low = 0;
    int high = n - 1;
    while (low < high) {
        for (int j = low; j < high; j++) {
            if (a[j] > a[j + 1]) {
                Swap(a[j], a[j + 1]);
            }
        }
        //        ShowArr(a, n);
        --high;

        for (int j = high; j > low; j--) {
            if (a[j] < a[j - 1])
                Swap(a[j], a[j - 1]);
        }
        //        ShowArr(a, n);
        ++low;
    }
}



// 冒泡改进4: 在改进1,2和3基础上叠加

void BubbleSort4(int a[], int n) {
    int low = 0;
    int high = n - 1;

    while (low < high) {
        bool flag = true;
        int pos1 = 0;
        for (int j = low; j < high; j++) {
            if (a[j] > a[j + 1]) {
                Swap(a[j], a[j + 1]);
                pos1 = j;
                flag = false;
            }

        }
        ShowArr(a, n);
        high = pos1;
        if (flag) {
            return;
        }

        for (int j = high; j > low; j--) {
            if (a[j] < a[j - 1]) {
                Swap(a[j], a[j - 1]);
                pos1 = j;
                flag = false;
            }
        }
        ShowArr(a, n);
        low = pos1;
        if (flag) {
            return;
        }
    }
}



void TestBubbleSort() {
    int arr[10] = {3, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BubbleSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestBubbleSort1() {
    int arr[10] = {3, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BubbleSort1(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestBubbleSort2() {
    int arr[10] = {3, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BubbleSort2(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestBubbleSort3() {
    int arr[10] = {63, 999, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BubbleSort3(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestBubbleSort4() {
    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    BubbleSort4(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}








#endif /* SWAPSORT_HPP */

