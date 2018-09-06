/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.hpp
 * Author: xuwei.huang
 *
 * Created on 2017年8月18日, 上午10:01
 */

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

// AVL树的节点

template <class T>
class AVLTreeNode
{
public:
    T key;
    int height;
    AVLTreeNode * left;
    AVLTreeNode * right;

public:

    AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode * r) : key(value), height(0), left(l), right(r)
    {

    }
};

template <class T>
class AVLTree
{
private:
    AVLTreeNode<T> * m_root; //根节点

public:
    AVLTree();
    ~AVLTree();

    // 获取树的高度
    int Height();
    // 比较值大小
    int Max(int a, int b);

    // 前序遍历AVL树
    void PreOrder();
    // 中序遍历AVL树
    void InOrder();
    // 后序遍历AVL树
    void PostOrder();

    // (递归实现)查找AVL树中键值为key的节点
    AVLTreeNode<T> * Search(T key);
    // (非递归实现) 查找AVL树中键值为key的节点
    AVLTreeNode<T> * IterativeSearch(T key);

    // 查找最小节点: 返回最小节点的键值
    T Minimum();
    // 查找最大节点: 返回最大节点的键值
    T Maximum();

    // 将节点(key为键值)插入到AVL树中
    void Insert(T key);

    // 删除节点(key为键值)
    void Remove(T key);

    // 销毁AVL树
    void Destroy();

    // 打印AVL树
    void Print();

private:
    // 获取树的高度
    int Height(AVLTreeNode<T> * tree);

    // 前序遍历AVL树
    void PreOrder(AVLTreeNode<T> * tree) const;
    // 中序遍历AVL树
    void InOrder(AVLTreeNode<T> * tree) const;
    // 后序遍历AVL树
    void PostOrder(AVLTreeNode<T> * tree) const;

    // (递归实现)查找AVL树x中键值为key的节点
    AVLTreeNode<T> * Search(AVLTreeNode<T> * x, T key);
    // (非递归实现)查找AVL树x中键值为key的节点
    AVLTreeNode<T> * IterativeSearch(AVLTreeNode<T> * x, T key);

    // 查找最小节点: 返回tree为根节点的AVL树中最小节点
    AVLTreeNode<T> * Minimum(AVLTreeNode<T> * tree);
    // 查找最大节点: 返回tree为根节点的AVL树中最大节点
    AVLTreeNode<T> * Maximum(AVLTreeNode<T> * tree);

    // LL: 左左对应的情况(左单旋转)
    AVLTreeNode<T> * LeftLeftRotation(AVLTreeNode<T> * k2);
    // RR: 右右对应的情况(右单旋转)
    AVLTreeNode<T> * RightRightRotatin(AVLTreeNode<T> * k1);
    // LR: 左右对应的情况(左右旋转)
    AVLTreeNode<T> * LeftRightRotation(AVLTreeNode<T> * k3);
    // RL: 右左对应的情况(右左旋转)
    AVLTreeNode<T> * RightLeftRotation(AVLTreeNode<T> * k2);

    // 将节点(z)插入到AVL树(tree)中
    AVLTreeNode<T> * Insert(AVLTreeNode<T> * &tree, T key);

    // 删除AVL树中节点z, 并返回被删除的节点
    AVLTreeNode<T> * Remove(AVLTreeNode<T> * &tree, AVLTreeNode<T> * z);

    // 销毁AVL树
    void Destroy(AVLTreeNode<T> * &tree);

    // 打印AVL树
    void Print(AVLTreeNode<T> * tree, T key, int direction);

};

/**
 * 构造函数
 */
template <class T>
AVLTree<T>::AVLTree() : m_root(NULL)
{

}

/**
 * 析构函数
 */
template <class T>
AVLTree<T>::~AVLTree()
{
    Destroy(m_root);
}

/**
 * 获取树的高度
 * @return int 树高度
 */
template <class T>
int AVLTree<T>::Height()
{
    return Height(m_root);
}

/**
 * 获取树的高度
 * @param tree
 * @return int 树的高度
 */
template <class T>
int AVLTree<T>::Height(AVLTreeNode<T> * tree)
{
    if (NULL != tree)
        return tree->height;
    return 0;
}

/**
 * 比较值大小
 * @param a
 * @param b
 * @return int 较大值
 */
template <class T>
int AVLTree<T>::Max(int a, int b)
{
    return a > b ? a : b;
}

/**
 * 前序遍历AVL树
 */
template <class T>
void AVLTree<T>::PreOrder()
{
    PreOrder(m_root);
}

/**
 * 前序遍历AVL树
 * @param tree
 */
template <class T>
void AVLTree<T>::PreOrder(AVLTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        cout << "key: " << tree->key << " height: " << tree->height << "  ";
        PreOrder(tree->left);
        PreOrder(tree->right);
    }
}

/**
 * 中序遍历AVL树
 */
template <class T>
void AVLTree<T>::InOrder()
{
    InOrder(m_root);
}

/**
 * 中序遍历AVL树
 * @param tree
 */
template <class T>
void AVLTree<T>::InOrder(AVLTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        InOrder(tree->left);
        cout << "key: " << tree->key << " height: " << tree->height << "  ";
        InOrder(tree->right);
    }
}

/**
 * 后序遍历AVL树
 */
template <class T>
void AVLTree<T>::PostOrder()
{
    PostOrder(m_root);
}

/**
 * 后序遍历AVL树
 * @param tree
 */
template <class T>
void AVLTree<T>::PostOrder(AVLTreeNode<T>* tree) const
{
    if (NULL != tree)
    {
        PostOrder(tree->left);
        PostOrder(tree->right);
        cout << "key: " << tree->key << " height: " << tree->height << "  ";
    }
}

/**
 * (递归实现)查找"AVL树x"中键值为key的节点
 * @param key
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Search(T key)
{
    return Search(m_root, key);
}

/**
 * (递归实现)查找"AVL树x"中键值为key的节点
 * @param x
 * @param key
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Search(AVLTreeNode<T>* x, T key)
{
    if (NULL == x || x->key == key)
        return x;
    if (key < x->key)
        return Search(x->left, key);
    else
        return Search(x->right, key);
}

/**
 * (非递归实现)查找"AVL树x"中键值为key的节点
 * @param key
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::IterativeSearch(T key)
{
    return IterativeSearch(m_root, key);
}

/**
 * (非递归实现)查找"AVL树x"中键值为key的节点
 * @param x
 * @param key
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::IterativeSearch(AVLTreeNode<T>* x, T key)
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
 * 查找最小结点：返回tree为根结点的AVL树的最小结点
 * @return 节点
 */
template <class T>
T AVLTree<T>::Minimum()
{
    AVLTreeNode<T> * node = Minimum(m_root);
    if (NULL != node)
        return node->key;
    return (T) NULL;
}

/**
 * 查找最小结点：返回tree为根结点的AVL树的最小结点
 * @param tree
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Minimum(AVLTreeNode<T>* tree)
{
    if (NULL == tree)
        return tree;
    while (NULL != tree->left)
        tree = tree->left;
    return tree;
}

/**
 * 查找最大结点：返回tree为根结点的AVL树的最大结点
 * @return 节点
 */
template <class T>
T AVLTree<T>::Maximum()
{
    AVLTreeNode<T> * node = Maximum(m_root);
    if (NULL != node)
        return node->key;
    return (T) NULL;
}

/**
 * 查找最大结点：返回tree为根结点的AVL树的最大结点
 * @param tree
 * @return 节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Maximum(AVLTreeNode<T>* tree)
{
    if (NULL == tree)
        return tree;
    while (NULL != tree->right)
        tree = tree->right;
    return tree;
}

/**
 * 将结点插入到AVL树中
 * @param key
 */
template <class T>
void AVLTree<T>::Insert(T key)
{
    Insert(m_root, key);
}

/**
 * 将结点插入到AVL树中
 * @param tree  AVL树的根节点
 * @param key   插入的节点的键值
 * @return      返回根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Insert(AVLTreeNode<T>*& tree, T key)
{
    if (NULL == tree)
    {
        // 新建节点
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (NULL == tree)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key)
    {
        // 插入tree节点的左子树
        tree->left = Insert(tree->left, key);
        if (Height(tree->left) - Height(tree->right) > 1)
        {
            if (key < tree->left->key)
                // 插入tree节点左子树的左子树
                tree = LeftLeftRotation(tree);
            else
                // 插入tree节点左子树的右子树
                tree = LeftRightRotation(tree);
        }
    }
    else if (key > tree->key)
    {
        // 插入tree节点的右子树
        tree->right = Insert(tree->right, key);
        if (Height(tree->right) - Height(tree->left) > 1)
        {
            if (key < tree->right->key)
                // 插入tree节点右子树的左子树
                tree = RightLeftRotation(tree);
            else
                // 插入tree节点右子树的右子树
                tree = RightRightRotatin(tree);
        }
    }
    else // (key == tree->key)
    {
        cout << "添加失败: 不允许添加相同的节点! " << endl;
    }

    tree->height = Max(Height(tree->left), Height(tree->right)) + 1;
    return tree;
}

/**
 * 删除结点(z)
 * @param key
 */
template <class T>
void AVLTree<T>::Remove(T key)
{
    AVLTreeNode<T> * z;
    if (NULL != (z = Search(m_root, key)))
        m_root = Remove(m_root, z);
}

/**
 * 删除结点(z)
 * @param tree  AVL树的根结点
 * @param z     待删除的结点
 * @return      返回根节点
 */
template <class T>
AVLTreeNode<T> *AVLTree<T>::Remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z)
{
    // 根为空 或者 没有要删除的节点, 直接返回NULL
    if (NULL == tree || NULL == z)
        return NULL;
    if (z->key < tree->key) // 待删除的节点在"tree的左子树"中
    {
        tree->left = Remove(tree->left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (Height(tree->right) - Height(tree->left) > 1)
        {
            AVLTreeNode<T> * r = tree->right;
            if (Height(r->left) > Height(r->right))
                tree = RightLeftRotation(tree);
            else
                tree = RightRightRotatin(tree);
        }
    }
    else if (z->key > tree->key) // 待删除的节点在"tree的右子树"中
    {
        tree->right = Remove(tree->right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (Height(tree->left) - Height(tree->right) > 1)
        {
            AVLTreeNode<T> * l = tree->left;
            if (Height(l->right) > Height(l->left))
                tree = LeftRightRotation(tree);
            else
                tree = LeftLeftRotation(tree);
        }
    }
    else // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if (NULL != tree->left && NULL != tree->right)
        {
            if (Height(tree->left) > Height(tree->right))
            {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的
                AVLTreeNode<T> * max = Maximum(tree->left);
                tree->key = max->key;
                tree->left = Remove(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的
                AVLTreeNode<T>* min = Maximum(tree->right);
                tree->key = min->key;
                tree->right = Remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T> * temp = tree;
            tree = (NULL != tree->left) ? tree->left : tree->right;
            delete temp;
        }
    }
    return tree;
}

/**
 * 销毁AVL树
 */
template <class T>
void AVLTree<T>::Destroy()
{
    Destroy(m_root);
}

/**
 * 销毁AVL树
 * @param tree
 * @return 
 */
template <class T>
void AVLTree<T>::Destroy(AVLTreeNode<T>* &tree)
{
    if (NULL != tree)
    {
        return;
    }
    if (NULL != tree->left)
        Destroy(tree->left);
    if (NULL != tree->right)
        Destroy(tree->right);
    delete tree;
    return;
}

/**
 * 打印"二叉查找树"
 */
template <class T>
void AVLTree<T>::Print()
{
    if (NULL != m_root)
        Print(m_root, m_root->key, 0);
}

/**
 * 打印"二叉查找树"
 * @param tree      
 * @param key           节点的键值
 * @param direction     0，表示该节点是根节点;
 *                      -1，表示该节点是它的父结点的左孩子;
 *                       1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void AVLTree<T>::Print(AVLTreeNode<T> * tree, T key, int direction)
{
    if (NULL != tree)
    {
        if (0 == direction) // tree是根节点
            cout << setw(2) << tree->key << "is root" << endl;
        else
            // tree是分支节点
            cout << setw(2) << tree->key << "is " << setw(2) << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

        Print(tree->left, tree->key, -1);
        Print(tree->right, tree->key, 1);
    }
}

/**
 * LL：左左对应的情况(左单旋转)
 * @param k2
 * @return 旋转后的根节点
 */
template <class T>
AVLTreeNode<T> * AVLTree<T>::LeftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T> * k1 = NULL;
    if (NULL != k2 && NULL != k2->left)
    {
        k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
        k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
    }
    return k1;
}

/**
 * RR: 右右对应的情况(右单旋转)
 * @param k1
 * @return 旋转后的根节点
 */
template <class T>
AVLTreeNode<T> * AVLTree<T>::RightRightRotatin(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T> * k2 = NULL;
    if (NULL != k1 && NULL != k1->right)
    {
        k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        k1->height = Max(Height(k1->left), Height(k1->right)) + 1;
        k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
    }
    return k2;
}

/**
 * LR: 左右对应的情况(右左旋转) // 对根节点失衡的子树先旋转, 然后再对整个树进行旋转, 依次类推
 * @param k3
 * @return 旋转后的根节点
 */
template <class T>
AVLTreeNode<T> * AVLTree<T>::LeftRightRotation(AVLTreeNode<T>* k3)
{
    AVLTreeNode<T> * k1 = NULL;
    AVLTreeNode<T> * k2 = NULL;
    if (NULL != k3 && NULL != k3->left && NULL != k3->left->right)
    {
        k1 = k3->left;
        k2 = k1->right;
        k1 = RightRightRotatin(k1);
        k3 = LeftLeftRotation(k3);
    }
    return k3;
}

/**
 * RL: 右左对应的情况(左右旋转) // 对根节点失衡的子树先旋转, 然后再对整个树进行旋转, 依次类推
 * @param k1
 * @return 旋转后的根节点
 */
template <class T>
AVLTreeNode<T> * AVLTree<T>::RightLeftRotation(AVLTreeNode<T>* k1)
{
    if (NULL != k1 && NULL != k1->right && NULL != k1->right->left)
    {
        k1->right = LeftLeftRotation(k1->right);
        k1 = RightRightRotatin(k1);
        return k1;
    }
    return NULL;
}


#endif /* AVLTREE_HPP */

