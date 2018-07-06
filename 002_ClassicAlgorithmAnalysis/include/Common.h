/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Common.h
 * Author: xuwei.huang
 *
 * Created on 2018年1月10日, 下午4:57
 */

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>


// 打印数组元素

void ShowArr(const int arr[], int len) {
    for (int i = 0; i < len; i++) {
        if (0 != i) {
            std::cout << ", ";
        }
        std::cout << arr[i];
    }
    std::cout << std::endl;
}



// 打印vector中元素的值

template <typename T>
void ShowVector(std::vector<T> & vec) {
    for (int i = 0; i < int(vec.size()); i++) {
        if (0 != i) {
            std::cout << ", ";
        }
        std::cout << vec[i];
    }
    std::cout << std::endl;
}



// 交换两个int类型的值

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


// 注意模板类型必须有 复制构造函数 和 赋值重载函数
// 交换两个模板类型的值

template<typename T>
void Swap(T &a, T&b) {
    T temp = a;
    a = b;
    b = temp;
}



// 将src中的值拷入dest从first开始的位置

template<typename T>
void copyVector(std::vector<T> & dest, std::vector<T> & src, int len, int first) {
    for (int i = 0, j = first; i < len; i++, j++) {
        dest[j] = src[i];
    }
}

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(NULL) {
    }

    ListNode(int x) : val(x), next(NULL) {
    }

    bool operator<(const ListNode& other) {
        return val < other.val;
    }
};

ListNode* string2ListNode(std::string& str) {
    ListNode*head = new ListNode(0);
    ListNode * next = head;
    for (int i = 0; i < (int) str.length(); i++) {
        char tmp = str[i];
        const char * pTmp = &tmp;
        int test = atoi(pTmp);
        next->next = new ListNode(test);
        next = next->next;
    }
    return head->next;
}

void ShowListNode(ListNode* head) {
    while (NULL != head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << " end" << std::endl;
}

#endif /* COMMON_H */

