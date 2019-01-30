/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MergeSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月13日, 下午3:18
 */

#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "Common.h"

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::cin;


/*
 * 分而治之 -- 归并排序
 * 
 * 平均时间复杂度: O(n * log n)
 * 最好情况: O(n * log n)
 * 最坏情况: O(n * log n)
 * 空间复杂度: O(n)
 * 排序方式: Out-place
 * 稳定性: 稳定
 * 
 * 基本思想: 将两个（或两个以上）有序表合并成一个新的有序表，
 *      即把待排序序列分为若干个子序列，每个子序列是有序的。
 *      然后再把有序子序列合并为整体有序序列。
 * 
 * 注意要点:
 * 
 * 改进1: 
 *
 */


// 归并排序 -- 两路归并排序

// 相邻两个有序子数列的归并函数(将 a[low...mid] 和 b[mid+1...high] 归并到 t[low...high]

template<typename T>
void merge(vector<T> & vec, int left, int right) {
    int low1 = left;
    int mid = (left + right) / 2;
    int low2 = mid + 1;
    int len = right - left + 1;
    int k = 0;

    vector<T> tmp; // 每次合并都使用一个临时容器. 
    while (low1 <= mid && low2 <= right) {
        if (vec[low1] <= vec[low2]) {
            tmp.push_back(vec[low1++]);
            k++;
        }
        else {
            tmp.push_back(vec[low2++]);
            k++;
        }
    }
    while (low1 <= mid) {
        tmp.push_back(vec[low1++]);
        k++;
    }
    while (low2 <= right) {
        tmp.push_back(vec[low2++]);
        k++;
    }
    copyVector(vec, tmp, len, left);
}

// 两路归并的递归算法

template <typename T>
void MergeSortBinaryWay(vector<T> & vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    MergeSortBinaryWay(vec, left, mid);
    MergeSortBinaryWay(vec, mid + 1, right);
    merge(vec, left, right); // 在每次递归的时候都使用了一个临时容器存储
}



// 两路递归算法改进: 递归过程中共享同一个容器

template<typename T>
void merge(vector<T> &vec, int left, int mid, int right, vector<T>&temp) {
    temp.clear(); // 每次合并之前清空共享容器的元素, 但空间保留
    int low1 = left, low2 = mid + 1;
    int len = right - left + 1;
    int k = 0;
    while (low1 <= mid && low2 <= right) {
        if (vec[low1] <= vec[low2]) {
            temp.push_back(vec[low1++]);
            k++;
        }
        else {
            temp.push_back(vec[low2++]);
            k++;
        }
    }

    while (low1 <= mid) {
        temp.push_back(vec[low1++]);
        k++;
    }
    while (low2 <= right) {
        temp.push_back(vec[low2++]);
        k++;
    }

    copyVector(vec, temp, len, left);
}



// 两路归并的递归算法. 使用了共享容器的递归

template<typename T>
void MergeSortBinaryWay1(vector<T> & vec, int left, int right, vector<T> & temp) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;
    MergeSortBinaryWay1(vec, left, mid, temp);
    MergeSortBinaryWay1(vec, mid + 1, right, temp);
    merge(vec, left, mid, right, temp);
}

void TestMergeSortBinaryWay() {
    vector<int> vec;
    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 15, 20, 6};
    int len = sizeof (arr) / sizeof (int);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }

    cout << "排序前: ";
    ShowVector(vec);

    MergeSortBinaryWay(vec, 0, vec.size() - 1);

    cout << "排序后: ";
    ShowVector(vec);
}

void TestMergeSortBinaryWay1() {
    vector<int> vec;

    //    int arr[10] = {999, 3, 66, 232, 35, 77, 112, 465, 908, 12};
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 15, 20, 6};
    int len = sizeof (arr) / sizeof (int);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }
    vector<int> temp;

    cout << "排序前: ";
    ShowVector(vec);

    MergeSortBinaryWay1(vec, 0, vec.size() - 1, temp);

    cout << "排序后: ";
    ShowVector(vec);
}



// 多路归并排序demo, 需要以后学习

#define LEN 10          //最大归并段长  
#define MINKEY -1     //默认全为正数  
#define MAXKEY 100    //最大值,当一个段全部输出后的赋值  
  
struct Array  
{  
    int arr[LEN];  
    int num;  
    int pos;  
}*A;  
  
int k,count;  
int *LoserTree,*External;  
  
void Adjust(int s)  
{  
    int t=(s+k)/2;//ls[t]是b[s]的双亲结点的下标  
    int temp;  
    while(t>0)  
    {  
        if(External[s] > External[LoserTree[t]])  
        {  
            temp = s;  
            s = LoserTree[t];  
            LoserTree[t]=temp;  
        }  
        t=t/2;  
    }  
    LoserTree[0]=s;  
}  
  
void CreateLoserTree()  
{  
    External[k]=MINKEY;  
    int i;  
    for(i=0;i<k;i++)LoserTree[i]=k;//设置ls中败者的初值，简化了败者树的建立过程，这样就可以直接通过(调整过程)来建立败者树。  
    for(i=k-1;i>=0;i--)Adjust(i);  
}  
  
void K_Merge()  
{  
    int i,p;  
    //初始化External数组，用以接下来创建LoserTree  
    for(i=0;i<k;i++)  
    {  
        p = A[i].pos;  
        External[i]=A[i].arr[p];  
        //cout<<External[i]<<",";  
        A[i].pos++;  
    }  
    //创建LoserTree  
    CreateLoserTree();  
    int NO = 0;  
    //输出最小值，并替代调整  
    while(NO<count)  
    {  
        p=LoserTree[0];  
        cout<<External[p]<<",";  
        NO++;  
        if(A[p].pos>=A[p].num)External[p]=MAXKEY;  
        else   
        {  
            External[p]=A[p].arr[A[p].pos];  
            A[p].pos++;  
        }  
        Adjust(p);  
    }  
    cout<<endl;  
}  


int TestMultiWayMergeSort()  
{  
    //freopen("in.txt","r",stdin);  
  
    int i,j;  
    count=0;  
    cin>>k;  
    A=(Array *)malloc(sizeof(Array)*k);  
    for(i=0;i<k;i++)  
    {  
        cin>>A[i].num;  
        count=count+A[i].num;  
        for(j=0;j<A[i].num;j++)  
        {  
            cin>>A[i].arr[j];  
        }  
        A[i].pos=0;
    }  
    LoserTree=(int *)malloc(sizeof(int)*k);  
    External=(int *)malloc(sizeof(int)*(k+1));  
  
    K_Merge();  
    system("pause");  
    return 0;  
}  






#endif /* MERGESORT_HPP */

