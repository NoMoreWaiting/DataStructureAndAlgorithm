/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BSTree.hpp
 * Author: xuwei.huang
 *
 * Created on 2017年8月19日, 下午3:24
 */

#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

template <class T>
class BSTreeNode
{
public:
    T key;
    BSTreeNode *parent;
    BSTreeNode *left;
    BSTreeNode *right;

    BSTreeNode(T value, BSTreeNode *p, BSTreeNode *l, BSTreeNode *r) : key(value), parent(p), left(l), right(r)
    {

    }
};

template <class T>
class BSTree
{
private:
    BSTreeNode<T> *m_root; // 根结点

public:
    BSTree();
    ~BSTree();

    // 前序遍历"二叉树"
    void PreOrder();
    // 中序遍历"二叉树"
    void InOrder();
    // 后序遍历"二叉树"
    void PostOrder();

    // (递归实现)查找"二叉树"中键值为key的节点
    BSTreeNode<T>* Search(T key);
    // (非递归实现)查找"二叉树"中键值为key的节点
    BSTreeNode<T>* IterativeSearch(T key);

    // 查找最小结点：返回最小结点的键值。
    T Minimum();
    // 查找最大结点：返回最大结点的键值。
    T Maximum();

    // 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
    BSTreeNode<T>* Successor(BSTreeNode<T> *x);
    // 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
    BSTreeNode<T>* Predecessor(BSTreeNode<T> *x);

    // 将结点(key为节点键值)插入到二叉树中
    void Insert(T key);

    // 删除结点(key为节点键值)
    void Remove(T key);

    // 销毁二叉树
    void Destroy();

    // 打印二叉树
    void Print();
private:
    // 前序遍历"二叉树"
    void PreOrder(BSTreeNode<T>* tree) const;
    // 中序遍历"二叉树"
    void InOrder(BSTreeNode<T>* tree) const;
    // 后序遍历"二叉树"
    void PostOrder(BSTreeNode<T>* tree) const;

    // (递归实现)查找"二叉树x"中键值为key的节点
    BSTreeNode<T>* Search(BSTreeNode<T>* x, T key) const;
    // (非递归实现)查找"二叉树x"中键值为key的节点
    BSTreeNode<T>* IterativeSearch(BSTreeNode<T>* x, T key) const;

    // 查找最小结点：返回tree为根结点的二叉树的最小结点。
    BSTreeNode<T>* Minimum(BSTreeNode<T>* tree);
    // 查找最大结点：返回tree为根结点的二叉树的最大结点。
    BSTreeNode<T>* Maximum(BSTreeNode<T>* tree);

    // 将结点(z)插入到二叉树(tree)中
    void Insert(BSTreeNode<T>* &tree, BSTreeNode<T>* z);

    // 删除二叉树(tree)中的结点(z)
    void Remove(BSTreeNode<T>* &tree, BSTreeNode<T> *target);

    // 销毁二叉树
    void Destroy(BSTreeNode<T>* &tree);

    // 打印二叉树
    void Print(BSTreeNode<T>* tree, T key, int direction);
};

/**
 * 构造函数
 */
template <class T>
BSTree<T>::BSTree() : m_root(NULL)
{

}

/**
 * 析构函数
 */
template <class T>
BSTree<T>::~BSTree()
{
    Destroy();
}

/**
 * 前序遍历
 */
template <class T>
void BSTree<T>::PreOrder()
{
    PreOrder(m_root);
}

/**
 * 前序遍历
 * @param tree
 */
template <class T>
void BSTree<T>::PreOrder(BSTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        cout << tree->key << "  ";
        PreOrder(tree->left);
        PreOrder(tree->right);
    }
}

/**
 * 中序遍历
 */
template <class T>
void BSTree<T>::InOrder()
{
    InOrder(m_root);
}

/**
 * 中序遍历
 * @param tree
 */
template <class T>
void BSTree<T>::InOrder(BSTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        InOrder(tree->left);
        cout << tree->key << "  ";
        InOrder(tree->right);
    }
}

/**
 * 后序遍历
 */
template <class T>
void BSTree<T>::PostOrder()
{
    PostOrder(m_root);
}

/**
 * 后序遍历
 * @param tree
 */
template <class T>
void BSTree<T>::PostOrder(BSTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        PostOrder(tree->left);
        PostOrder(tree->right);
        cout << tree->key << "  ";
    }
    return;
}

/**
 * (递归实现)查找"二叉树x"中键值为key的节点
 * @param key
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Search(T key)
{
    return Search(m_root, key);
}

/**
 * (递归实现)查找"二叉树x"中键值为key的节点
 * @param x
 * @param key
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Search(BSTreeNode<T>* x, T key) const
{
    if (NULL == x || x->key == key)
        return x;
    if (key < x->key)
        return Search(x->left, key);
    else
        return Search(x->left, key);
}

/**
 * (非递归实现)查找"二叉树x"中键值为key的节点
 * @param key
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::IterativeSearch(T key)
{
    return IterativeSearch(m_root, key);
}

/**
 * (非递归实现)查找"二叉树x"中键值为key的节点
 * @param x
 * @param key
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::IterativeSearch(BSTreeNode<T>* x, T key) const
{
    while (NULL != x && x->key != key)
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

/**
 * 查找最大值 返回tree为根结点的二叉树的最大结点。
 * @return 
 */
template <class T>
T BSTree<T>::Maximum()
{
    BSTreeNode<T> * p = Maximum(m_root);
    if (NULL != p)
        return p->key;
    return (T) NULL;
}

/**
 * 查找最大值 返回tree为根结点的二叉树的最大结点。
 * @param tree
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Maximum(BSTreeNode<T>* tree)
{
    while (NULL != tree && NULL != tree->right)
        tree = tree->right;
    return tree;
}

/**
 * 查找最小值 返回tree为根结点的二叉树的最小结点。
 * @return 
 */
template <class T>
T BSTree<T>::Minimum()
{
    BSTreeNode<T> *p = Minimum(m_root);
    if (NULL != p)
        return p->key;
    return (T) NULL;
}

/**
 * 查找最小值  返回tree为根结点的二叉树的最小结点。
 * @param tree
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Minimum(BSTreeNode<T>* tree)
{
    while (NULL != tree && NULL != tree->left)
        tree = tree->left;
    return tree;
}

/**
 * 查找前驱节点
 * @param x
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Predecessor(BSTreeNode<T>* x)
{
    if (NULL == x)
        return x;
    // 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
    if (NULL != x->left)
        return Maximum(x->left);

    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
    BSTreeNode<T> * y = x->parent;
    while (NULL != y && x == y->left)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 * 查找后继节点
 * @param x
 * @return 
 */
template <class T>
BSTreeNode<T> * BSTree<T>::Successor(BSTreeNode<T>* x)
{
    if (NULL == x)
        return x;
    // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
    if (NULL != x->right)
        return Minimum(x->right);
    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    BSTreeNode<T> * y = x->parent;
    while (NULL != y && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
 * 将结点(key为节点键值)插入到二叉树中
 * @param key
 */
template <class T>
void BSTree<T>::Insert(T key)
{
    BSTreeNode<T> * z = NULL;
    if (NULL == (z = new BSTreeNode<T>(key, NULL, NULL, NULL)))
        return;
    Insert(m_root, z);
}

/**
 * 将结点(key为节点键值)插入到二叉树中
 * @param tree
 * @param z
 */
template <class T>
void BSTree<T>::Insert(BSTreeNode<T>*& tree, BSTreeNode<T>* z)
{
    BSTreeNode<T> * y = NULL;
    BSTreeNode<T> * x = tree;

    while (NULL != x)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (NULL == y)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

/**
 * 删除节点, 并释放空间
 * @param key
 */
template <class T>
void BSTree<T>::Remove(T key)
{
    /*
    BSTreeNode<T> *z, *node;
    if (NULL != (z = Search(m_root, key)))
    {
        if (NULL != (node = Remove(m_root, z)))
            delete node;
    }
    */
    BSTreeNode<T> *z = Search(m_root, key);
    if(NULL != z)
        Remove(m_root, z);
}

/**
 * 参考算法导论p157叶：
 * 删除一个节点要分为三种情况：
 *  1. 删除节点z没有孩子节点，那么就可以直接删除
 *  2. 删除节点z只有一个孩子节点，那么直接将z的孩子节点接到z的父节点下
 *  3. 删除节点z有两个孩子的情况，根据算法导论上的方法
 *      先找到节点z的中序后继节点s，把节点s上的数据转移到节点z上，然后删除节点s，
 *      由于s节点为z节点的右子树总最左节点（因为s为z的后继节点），所以s无左子树，
 *      (如果有的话, 那么根据中序遍历的规则, s就不是z的后续节点了)
 *      删除节点s就和上面情况2一样了。
 * 删除节点 target, 并释放空间
 * @param tree
 * @param target
 * @return 
 */
template <class T>
void BSTree<T>::Remove(BSTreeNode<T>*& tree, BSTreeNode<T>* target)
{
    if(NULL == tree)
        return;
    else if(target->key < tree->key)
        Remove(tree->left, target);
    else if(target->key > tree->key)
        Remove(tree->right, target);
    else
    {
        BSTreeNode<T> * temp = NULL;
        temp = target;
        if(NULL == target->left)
        {
            target = target->left;
        }
        else if(NULL == target->right)
        {
            target = target->right;
        }
        else
        {
            BSTreeNode<T> * left = target->left;    ///左子树的根节点
            while(left->right)
                left = left->right; /// 寻找中序前节点, 也就是left为根节点的最右的节点
            left->right = target->right; /// 将target的右子树嫁接到left的右子树上.(left->right原来为空)
            target = target->left;
        }
        
        delete temp;
    }
    return;
    
    
    
    /*
    BSTreeNode<T> * x = NULL;
    BSTreeNode<T> * realDelete = NULL;

    if (NULL == target->left || NULL == target->right)
        realDelete = target;
    else
        realDelete = Successor(target);

    if (NULL != realDelete->left)
        x = realDelete->left;
    else
        x = realDelete->right;

    if (NULL != x)
        x->parent = realDelete->parent;

    if (NULL == realDelete->parent)
        tree = x;
    else if (realDelete == realDelete->parent->left)
        realDelete->parent->left = x;
    else
        realDelete->parent->right = x;

    if (realDelete != target)
        target->key = realDelete->key;

    return realDelete;
    */
}

/**
 * 销毁二叉树
 */
template <class T>
void BSTree<T>::Destroy()
{
    Destroy(m_root);
}

/**
 * 销毁二叉树
 * @param tree
 */
template <class T>
void BSTree<T>::Destroy(BSTreeNode<T>* &tree)
{
    if (NULL == tree)
        return;

    if (NULL != tree->left)
        return Destroy(tree->left);
    if (NULL != tree->right)
        return Destroy(tree->right);

    delete tree;
    tree = NULL;
}

/**
 * 打印"二叉查找树"
 */
template <class T>
void BSTree<T>::Print()
{
    if (m_root != NULL)
        Print(m_root, m_root->key, 0);
}

/**
 * 打印"二叉查找树"
 * @param tree
 * @param key
 * @param direction     0，表示该节点是根节点;
 *                      -1，表示该节点是它的父结点的左孩子;
 *                       1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void BSTree<T>::Print(BSTreeNode<T>* tree, T key, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0) // tree是根节点
            cout << setw(2) << tree->key << " is root" << endl;
        else // tree是分支节点
            cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

        Print(tree->left, tree->key, -1);
        Print(tree->right, tree->key, 1);
    }
}


#endif /* BSTREE_HPP */

