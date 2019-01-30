/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    C++ 语言: 二叉查找树
 * Created on   2017年8月19日, 下午3:19
 */


#include <iostream>
#include "BSTree.hpp"
using namespace std;

static int arr[]= {1,5,4,3,2,6};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int i, ilen;
    BSTree<int>* tree=new BSTree<int>();

    cout << "== 依次添加: ";
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++) 
    {
        cout << arr[i] <<" ";
        tree->Insert(arr[i]);
    }

    cout << "\n== 前序遍历: ";
    tree->PreOrder();

    cout << "\n== 中序遍历: ";
    tree->InOrder();

    cout << "\n== 后序遍历: ";
    tree->PostOrder();
    cout << endl;

    cout << "== 最小值: " << tree->Minimum() << endl;
    cout << "== 最大值: " << tree->Maximum() << endl;
    cout << "== 树的详细信息: " << endl;
    tree->Print();

    cout << "\n== 删除根节点: " << arr[3];
    tree->Remove(arr[3]);

    cout << "\n== 中序遍历: ";
    tree->InOrder();
    cout << endl;

    // 销毁二叉树
    tree->Destroy();

    return 0;
}
