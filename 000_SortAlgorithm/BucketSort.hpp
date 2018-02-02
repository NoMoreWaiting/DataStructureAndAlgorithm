/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BucketSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月13日, 下午6:44
 */

#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP

#include "Common.h"

#include <iostream>

/*
 *  非比较 -- 分配式排序 -- 桶排序
 * 
 * 平均时间复杂度: O(n + k)
 * 最好情况: O(n + k)
 * 最坏情况: O(n^2)
 * 空间复杂度: O(n + k)
 * 排序方式: Out-place
 * 稳定性: 稳定
 * 
 * 基本思想: 桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。
 *      假设输入数据服从均匀分布，将数据分到有限数量的桶里，
 *      每个桶再分别排序
 *      （有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序)
 * 
 * 注意要点:
 * 
 * 改进1: 
 *
 */


typedef struct node {
    int keyNum; //桶中数的数量
    int key; //存储的元素
    struct node * next;
} KeyNode;



// 关键是映射函数的选择, 如果映射函数不能保证桶之间元素没有交集, 那么处理就会复杂, 就是失败的桶排序

// keys待排序数组，size数组长度，bucket_size桶的数量

void BucketSort(int *target, int keys[], int size, int bucket_size) {
    KeyNode* k = (KeyNode *) malloc(sizeof (KeyNode)); //用于控制打印
    int i, j, b;
    KeyNode **bucket_table = (KeyNode **) malloc(bucket_size * sizeof (KeyNode *));
    for (i = 0; i < bucket_size; i++) {
        bucket_table[i] = (KeyNode *) malloc(sizeof (KeyNode));
        bucket_table[i]->keyNum = 0; //记录当前桶中是否有数据
        bucket_table[i]->key = 0; //记录当前桶中的数据  
        bucket_table[i]->next = NULL;
    }

    for (j = 0; j < size; j++) {
        int index;
        KeyNode *p;
        KeyNode *node = (KeyNode *) malloc(sizeof (KeyNode));
        node->key = keys[j];
        node->next = NULL;

        index = keys[j] / 10; // 映射函数计算桶号  import, 保证桶之间的元素不会产生交集
        p = bucket_table[index]; // 初始化P成为桶中数据链表的头指针  
        if (p->keyNum == 0)// 该桶中还没有数据 
        {
            bucket_table[index]->next = node;
            (bucket_table[index]->keyNum)++; // 桶的头结点记录桶内元素各数，此处加一
        }
        else// 该桶中已有数据 
        {
            // 链表结构的插入排序 
            while (p->next != NULL && p->next->key <= node->key)
                p = p->next;
            node->next = p->next;
            p->next = node;
            (bucket_table[index]->keyNum)++;
        }
    }

    i = 0;
    for (b = 0; b < bucket_size; b++)
        // 判断条件是跳过桶的头结点，桶的下个节点为元素节点不为空
        for (k = bucket_table[b]; k->next != NULL; k = k->next) {
            *(target + i++) = k->next->key;
        }
}

void TestBucketSort() {
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6, 10, 10, 10, 1, 1, 1, 1, 1, 1, 2, 2, 2, 6, 6};
    int len = sizeof (arr) / sizeof (int);
    int * target = (int *) malloc(sizeof (int) * len);

    cout << "排序前: ";
    ShowArr(arr, len);

    BucketSort(target, arr, len, 2);

    cout << "排序后: ";
    for (int i = 0; i < len; i++) {
        if (0 != i) {
            cout << ", ";
        }
        cout << *(target + i);
    }
    cout << endl;
}


#endif /* BUCKETSORT_HPP */

