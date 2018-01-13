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

#include <stdlib.h>
#include <vector>
#include <stack>
#include <iostream>

using std::cout;
using std::endl;

using std::stack;
using std::vector;

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



// 冒泡排序基础版

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
        //        ShowArr(a, n);
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
        //        ShowArr(a, n);
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
 * 基本思想: 使用两个指针来遍历待排序的数组，
 * 根据两个指针遍历的方向可以分为两类：
 *      第一，两个指针从待排序数组的同一个方向遍历。
 *      第二，两个指针分别从带排序数组的两端进行遍历
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
        //        ShowArr(a, right + 1);
    }
    // 这里以右侧元素作为枢纽元, 那么low指向最后一个小于枢纽元的元素, low+1 指向序列中第一个大于枢纽元的大数. 互换之后, 从 low+2 到right 是大值区间, left 到 low 是小值区间.
    Swap(a[pivot], a[low + 1]);
    //    ShowArr(a, right + 1);
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
            //            ShowArr(a, right + 1);
        } else { // 当找不到左右侧可交换的大小值时, low >= high 退出循环
            break;
        }
    }

    // 直接交换元素法, 不能保证一次筛选后, 枢纽元在最终位置上, 只能保证枢纽元在大值区间中. 
    // high元素本来指向右侧开始最后一个大于枢纽元的元素, 但经过 Swap(a[low], a[high]) 已经变为指向左侧元素最后一个小于枢纽元的元素.
    //所以大值区间 high+1 -- right, 小值区间为 left -- right
    QuickSort2HoareLeft(a, left, high);
    QuickSort2HoareLeft(a, high + 1, right); // 画图: 最后一次 ++ --, 让 low指向右区间第一个元素, high 指向左区间最后一个元素
}


// Hoare法(直接交换, 右侧枢纽元), 处理一次筛选

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
            //            ShowArr(a, right + 1);
        } else {
            break;
        }
    }
    return high;
}

// Hoare方法, 以右侧作为枢纽元

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
            //            ShowArr(a, right + 1);
        } else {
            break;
        }
    }

    QuickSort2HoareRight(a, left, high); // 注意这里有个 4, 5 传入之后递归死循环了
    QuickSort2HoareRight(a, high + 1, right);
}



// hoare的变形版本: 空洞法, 以左侧为枢纽元
// 该算法一趟排序后枢纽被放在了最终的位置上, 所以递归时不需要再递归此枢纽元
// 算法中之所以可以在循环中赋值是因为枢纽元素值已经保存在了pivot中

void QuickSort3HoleLeft(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int low = left;
    int high = right;
    int pivot = a[low]; // 先保存枢纽元的值, 此时枢纽元相当于空洞

    while (low < high) {
        // 注意两个内层while的顺序不能换
        while (low < high && a[high] >= pivot) { // 这里是>=不能使>，否则当数组元素等于枢纽时会死循环
            high--;
        }
        a[low] = a[high]; // 将右侧开始第一个小于枢纽元的值插入左侧的空洞, 此时 high 位置的值相当于空洞
        while (low < high && a[low] <= pivot) {// 这里是<=不能使<，否则当数组元素等于枢纽时会死循环
            low++;
        }
        a[high] = a[low];
    }

    a[low] = pivot; // low此时为枢纽的位置

    QuickSort3HoleLeft(a, left, low - 1); // 空洞法一次筛选后, 枢纽元位于最终的位置不需要在带入计算
    QuickSort3HoleLeft(a, low + 1, right);

}



// hoare的变形版本: 空洞法, 以左侧为枢纽元, 以右侧为枢纽元

void QuickSort3HoleRight(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int low = left;
    int high = right;
    int pivot = a[high]; // 保存尾值为枢纽元

    while (low < high) {
        // 注意: 这里和以左值为枢纽元相反,
        // 因为: 一开始的a[high]的值被保存了, a[high]相当于空洞, 所以先将a[low]的值赋值给 a[high]这个空洞
        while (a[low] <= pivot && low < high) {
            low++;
        }
        a[high] = a[low];
        while (a[high] >= pivot && low < high) {
            high--;
        }
        a[low] = a[high];
    }
    a[high] = pivot;
    //    ShowArr(a, right + 1);
    QuickSort3HoleRight(a, left, high - 1);
    QuickSort3HoleRight(a, high + 1, right);
}



// 空洞法中一次筛选使用, 确定枢纽元的最终位置, 左侧区间为 <= 区间, 右侧区间为 >= 区间

template<typename T>
int PartionQuickSort3Hole(vector<T> &vec, int left, int right) {

    int low = left;
    int high = right;
    T pivot = vec[low];

    while (low < high) {
        while (low < high && vec[high] >= pivot) {
            high--;
        }
        vec[low] = vec[high];

        while (low < high && vec[low] <= pivot) {
            low++;
        }
        vec[high] = vec[low];
    }
    vec[low] = pivot;
    return low;
}



// hoare变形版本: 空洞法, 非递归版本. 以第一个元素为枢纽  
// 非递归算法用一个stack辅助数据结构，栈存放下一次要排序的两个下标 

template<typename T>
void QuickSort3HoleNoRecursion(vector<T>&vec, int left, int right) {
    stack<int> st;
    // 注意每次入栈都将较大的下标先入栈  
    // 每次出栈相反：较大的小标会后出栈
    st.push(right);
    st.push(left);
    int maxSize = 0;
    while (!st.empty()) {
        if (st.size() > maxSize) {
            maxSize = st.size();
            cout << "max stack size: " << maxSize << endl;
        }
        int low = st.top();
        st.pop();
        int high = st.top();
        st.pop();
        //        cout << low << " " << high << endl;  
        // mid 是确定最终位置的枢纽元
        int mid = PartionQuickSort3Hole(vec, low, high);
        //        ShowVector(vec); 
        // 相当于左侧区间
        if (mid - 1 > low) {
            // 存储下次循环中需要处理的 left 和 right
            st.push(mid - 1);
            st.push(low);
        }
        // 相当于右侧区间
        if (mid + 1 < high) {
            st.push(high);
            st.push(mid + 1);
        }
    }
    //    cout << "max stack size: " << maxSize << endl;
    return;
}



// 随机枢纽的快速排序
// 首先产生随机的枢纽位置i，然后交换i、right或者交换i、left。那么接下来就可以继续使用上述的方法

int Rand(int left, int right) {
    int size = right - left + 1;
    return left + rand() % size;
}

// 使用 hole 法, 右侧枢纽

template <typename T>
int PartionQuickSort4(vector<T> &vec, int left, int right) {
    Swap(vec[Rand(left, right)], vec[right]); // 将随机枢纽交换到右侧位置
    T pivot = vec[right]; //设置枢纽  
    int low = left;
    int high = right;
    while (low < high) {//注意两个内层while的顺序不能换  
        while (low < high && vec[low] <= pivot)
            low++;
        vec[high] = vec[low];
        while (low < high && vec[high] >= pivot)
            high--;
        vec[low] = vec[high];
    }
    vec[low] = pivot;
    return low;
}

// 随机枢纽的快速排序

template<typename T>
void QuickSort4Rand(vector<T> &vec, int left, int right) {
    if (left < right) {
        int partion = PartionQuickSort4(vec, left, right);
        QuickSort4Rand(vec, left, partion - 1);
        QuickSort4Rand(vec, partion + 1, right);
    }
}



// 快速排序, 枢纽三数中间值法

// 中间值法小数组时使用的插入排序

template<typename T>
void insertSortForQuickSort(vector<T> & vec, int left, int right) {
    for (int p = left + 1; p <= right; p++) {
        T temp = vec[p];
        int j;
        for (j = p; j > left && temp < vec[j - 1]; j--) {
            vec[j] = vec[j - 1];
        }
        vec[j] = temp;
    }
}

// 中间值法取中间值为枢纽值

template<typename T>
const T & median(vector<T> &vec, int left, int right) {
    // 取数据的头、尾和中间三个数，并对他们进行排序  
    // 排序结果直接保存在数组中  
    int center = (left + right) / 2;
    if (vec[center] < vec[left]) {
        Swap(vec[center], vec[left]);
    }
    if (vec[right] < vec[left]) {
        Swap(vec[right], vec[left]);
    }
    if (vec[right] < vec[center]) { // 此时vec[center]为三值中的中值
        Swap(vec[right], vec[center]);
    }
    // 把中值，即枢纽与数组倒数第二个元素交换  
    // 将此3值最大值与倒数第二元素交换
    // 现在第一个值小, 倒数第二值中, 最后值大
    Swap(vec[center], vec[right - 1]);
    return vec[right - 1];
}

// 三值法快排

template<typename T>
void QuickSort5TriValue(vector<T> &vec, int left, int right) {
    // 少于三个值, 不能使用中值法快排
    if (left + 3 <= right) {
        
        // 三值选择中就已经确定了3个值的相对位置, 并且枢纽元的值也确定是一个偏中间的值, 不是边缘极值, 避免了极端情况的产生
        T pivot = median(vec, left, right);
        cout << "pivot: " << pivot << endl;

        int low = left, high = right - 1;
        while (true) {
            //向后扫描数组  
            //由于在选择枢纽时，已经把比枢纽值大的数据放在right位置  
            //所以不会越界 
            while (vec[++low] < pivot) {
            }
            //向前扫描数组  
            //由于在选择枢纽时，已经把比枢纽值小的数据放在left位置 
            //所以不会越界  
            while (vec[--high] > pivot) {
            }
            //把比枢纽小的数据放在前部，大的放到后部 
            if (low < high) {
                Swap(vec[low], vec[high]);
            } else {
                //已经对要排序的数据都与枢纽比较了一次  
                //把中枢纽保存在适当的位置，因为begin的数一定比枢纽大  
                //所以把这个数放在数组后面  
                Swap(vec[low], vec[right - 1]);
                break;
            }
        }
        QuickSort5TriValue(vec, left, low - 1);
        QuickSort5TriValue(vec, low + 1, right);
    } else {
        //使用插入排序来处理很小的数组(n < 10)提高效率
        insertSortForQuickSort(vec, left, right);
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

void TestQuickSort3HoleLeft() {
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort3HoleLeft(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestQuickSort3HoleRight() {
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    QuickSort3HoleRight(arr, 0, len - 1);

    cout << "排序后: ";
    ShowArr(arr, len);
}

void TestQuickSort3HoleNoRecursion() {
    vector<int> vec;
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }

    cout << "排序前: ";
    ShowVector(vec);

    QuickSort3HoleNoRecursion(vec, 0, vec.size() - 1);

    cout << "空洞法无递归版本 排序后: ";
    ShowVector(vec);
}

void TestQuickSort4Rand() {
    vector<int> vec;
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }

    cout << "排序前: ";
    ShowVector(vec);

    QuickSort4Rand(vec, 0, vec.size() - 1);

    cout << "排序后: ";
    ShowVector(vec);
}

void TestQuickSort5TriValue() {
    vector<int> vec;
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }

    cout << "排序前: ";
    ShowVector(vec);

    QuickSort5TriValue(vec, 0, vec.size() - 1);

    cout << "排序后: ";
    ShowVector(vec);
}


#endif /* SWAPSORT_HPP */

