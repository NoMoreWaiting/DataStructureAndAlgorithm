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
 * 平均时间复杂度: O(n^2)
 * 最好情况: O(n)
 * 最坏情况: O(n^2)
 * 空间复杂度: O(1)
 * 排序方式: in-place
 * 稳定性: 稳定
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



/*
 * 交换排序 -- 快速排序
 * 
 * 平均时间复杂度: O(n * log n)
 * 最好情况: O(n * log n)
 * 最坏情况: O(n^2)
 * 空间复杂度: O(log n)
 * 排序方式: in-place
 * 稳定性: 不稳定
 * 
 * 基本思想:
 * 
 * 注意要点:
 * 
 * 改进1: 
 *
 */

// 快速排序 单向划分 <<编程珠玑第2版>> 第112页的实现方法, 以最左侧作为枢纽元

void QuickSort1Left(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = left;
    int low = left;

    for (int high = left + 1; high <= right; high++) {
        if (a[high] < a[pivot]) {
            low++; // 注意: 这里的low需要先计算++, 然后再交换值. 因为最左边是枢纽元, 先++之后才能交换
            Swap(a[high], a[low]);
            //            ShowArr(a, right+1);
        }
        //        ShowArr(a, right+1);
    }
    Swap(a[pivot], a[low]);
    //    ShowArr(a, right+1);
    QuickSort1Left(a, pivot, low - 1); // 递归调用左侧
    QuickSort1Left(a, low + 1, right); // 递归调用右侧
}


// 快速排序 单向划分 算法导论上的方法 以最右侧作为枢纽元

void QuickSort1Right(int a[], int left, int right) {
    if (left >= right) {
        return;
    }
    // low总是指向小于a[pivot]值区间的最右端
    // 因此一开始的left如果为0, 那么low是-1, 因为还没有排序, 没有小于区间的最右值
    int low = left - 1; // low, high, pivot, left, right 都是数组的下标. 数组下标从0开始
    int pivot = right;

    for (int high = left; high < right; high++) {
        // 这里使用 <, 那么下面使用 low, 就会死循环. 如果一次遍历就确定了元素的最终位置, 那么下次分区间时就不能带入次分区
        if (a[high] <= a[pivot]) { // 交换包括自己交换, 这样才能移动low(low总是指向小于a[pivot]值区间的最右端)
            low++; // low++后low指向了数组第一个大于枢纽的位置
            Swap(a[high], a[low]);
        }
        ShowArr(a, right + 1);
    }
    // 这里以右侧元素作为枢纽元, 那么low指向最后一个小于枢纽元的元素, low+1 指向序列中第一个大于枢纽元的大数. 互换之后, 从 low+2 到right 是大值区间, left 到 low 是小值区间.
    Swap(a[pivot], a[low + 1]);
    ShowArr(a, right + 1);
    QuickSort1Right(a, left, low);
    QuickSort1Right(a, low + 2, right);
}


// hoare版本只能保证左区间都是 <=枢纽元的值, 右区间都是 >=枢纽元的值
// 迭代左侧 和 右侧元素时, 枢纽元要加入一侧进行迭代.
// 所以迭代为: a, left, high 和 a, high+1, right  
// 或者 a, left, low-1 和 a, low, right
// low 和 high 的值,可能会一样, 所以不能同时使用low和high来分界
// 快速排序 Hoare版本(直接交换元素), 以左侧作为枢纽元

void QuickSort2HoareLeft(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = a[left];
    int low = left - 1;
    int high = right + 1;

    while (true) {
        // 一开始 low 和 high 都是指向数组外侧, 先做一次 ++ 或者 -- 运算指向数组中的实际元素
        while (a[--high] > pivot) { // 从右向左第一次遇到不大于pivot的值就停下, 也就是说同值大小的也被交换了
        }
        while (a[++low] < pivot) {
        }

        // 目前的准则: 遇到等于枢纽元的值都会停下进行交换
        // 因为以左侧元素为枢纽元, 右侧第一个元素(即枢纽元)天生不符合大于枢纽元的条件, 因此high少--了一次, 导致后面循环的时候会遇到 low = high的情况
        // 为什么这里需要<=, 而前面的以左元素为枢纽元是 < 的条件?
        if (low < high) {
            Swap(a[low], a[high]);
            ShowArr(a, right + 1);
        }
        else { // 当找不到左右侧可交换的大小值时, low >= high 退出循环
            break;
        }
    }

    // 直接交换元素法, 不能保证一次筛选后, 枢纽元在最终位置上, 只能保证枢纽元在大值区间中. 
    // high元素本来指向右侧开始最后一个大于枢纽元的元素, 但经过 Swap(a[low], a[high]) 已经变为指向左侧元素最后一个小于枢纽元的元素.
    //所以大值区间 high+1 -- right, 小值区间为 left -- right
    QuickSort2HoareLeft(a, left, high);
    QuickSort2HoareLeft(a, high + 1, right); // 画图: 最后一次 ++ --, 让 low指向右区间第一个元素, high 指向左区间最后一个元素
}

int PartionQuickSort2HoareRight(int a[], int left, int right) {
    int pivot = a[right];
    int low = left - 1;
    int high = right + 1;
    while (true) {
        while (a[++low] < pivot) {
        }
        while (a[--high] > pivot) {
        }
        if (low <= high) {
            Swap(a[low], a[high]);
            ShowArr(a, right + 1);
        }
        else {
            break;
        }
    }
    return high;
}

void QuickSort2HoareRight(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = a[right];
    int low = left - 1;
    int high = right + 1;
    while (true) {
        while (a[--high] > pivot) {
        }
        while (a[++low] < pivot) {
        }

        // 目前的准则: 遇到等于枢纽元的值都会停下进行交换
        // 因为以右端元素为枢纽元, 右侧第一个元素(即枢纽元)天生不符合大于枢纽元的条件, 因此high少--了一次, 导致后面循环的时候会遇到 low = high的情况
        // 为什么这里需要<=, 而前面的以左元素为枢纽元是 < 的条件?
        if (low <= high) { 
            Swap(a[low], a[high]);
            ShowArr(a, right + 1);
        }
        else {
            break;
        }
    }

    QuickSort2HoareRight(a, left, high); // 注意这里有个 4, 5 传入之后递归死循环了
    QuickSort2HoareRight(a, high + 1, right);
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

void TestQuickSort1Left() {
    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort1Left(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestQuickSort1Right() {
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {9, 6, 12, 3, 10, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort1Right(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestQuickSort2HoareLeft() {
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 6, 12, 3, 6, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort2HoareLeft(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestQuickSort2HoareRight() {
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 6, 12, 3, 6, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort2HoareRight(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}





#endif /* SWAPSORT_HPP */

