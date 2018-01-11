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
using std::cout;
using std::endl;

void ShowArr(const int arr[], int len) {
    for (int i = 0; i < len; i++) {
        if (0 != i) {
            cout << ", ";
        }
        cout << arr[i];
    }
    cout << endl;
}


void Swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}


#endif /* COMMON_H */

