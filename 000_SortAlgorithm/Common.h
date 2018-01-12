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

#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;



// 打印数组元素

void ShowArr(const int arr[], int len) {
    for (int i = 0; i < len; i++) {
        if (0 != i) {
            cout << ", ";
        }
        cout << arr[i];
    }
    cout << endl;
}



// 打印vector中元素的值

template <typename T>
void ShowVector(vector<T> & vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (0 != i) {
            cout << ", ";
        }
        cout << vec[i];
    }
    cout << endl;
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


#endif /* COMMON_H */

