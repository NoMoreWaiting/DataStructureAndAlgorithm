/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年8月18日, 上午10:00
 */

/**
 * C 语言: AVL树
 *
 * @author skywang
 * @date 2013/11/07
 */

#include <iostream>
#include "AVLTree.hpp"
using namespace std;

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
//static int arr[]= {1,2,3,4,5};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int i, ilen;
    AVLTree<int>* tree = new AVLTree<int>();

    cout << "== 依次添加: ";
    ilen = TBL_SIZE(arr);
    for (i = 0; i < ilen; i++)
    {
        cout << arr[i] << " ";
        tree->Insert(arr[i]);
    }

    cout << "\n== 前序遍历: ";
    tree->PreOrder();

    cout << "\n== 中序遍历: ";
    tree->InOrder();

    cout << "\n== 后序遍历: ";
    tree->PostOrder();
    cout << endl;

    cout << "== 高度: " << tree->Height() << endl;
    cout << "== 最小值: " << tree->Minimum() << endl;
    cout << "== 最大值: " << tree->Maximum() << endl;
    cout << "== 树的详细信息: " << endl;
    tree->Print();

    i = 8;
    cout << "\n== 删除根节点: " << i;
    tree->Remove(i);

    cout << "\n== 高度: " << tree->Height();
    cout << "\n== 中序遍历: ";
    tree->InOrder();
    cout << "\n== 树的详细信息: " << endl;
    tree->Print();

    // 销毁二叉树
    tree->Destroy();

    return 0;
}
