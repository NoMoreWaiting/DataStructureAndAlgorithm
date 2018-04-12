/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClassicAlgorithmAnalysis.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年4月12日, 下午3:37
 */

#ifndef CLASSICALGORITHMANALYSIS_HPP
#define CLASSICALGORITHMANALYSIS_HPP

#include "Common.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;


// 全排列算法
// https://blog.csdn.net/lemon_tree12138/article/details/50986990

/*
 * 对于一个给定的序列 a = [a1, a2, a3, … , an]，请设计一个算法，用于输出这个序列的全部排列方式。 
 * 例如：a = [1, 2, 3] 
 * 输出
 * 
 * [1, 2, 3]
 * [1, 3, 2]
 * [2, 1, 3]
 * [2, 3, 1]
 * [3, 2, 1]
 * [3, 1, 2]
 */

class FullRangeAlgorithm {
public:
    // 1. 全排列就是从第一个数字起每个数分别与它后面的数字交换. 也可以使用阶乘的组合概念, 设置栈, 递归添加

    // 2. 去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换

    // 3. 全排列的非递归就是由后向前找替换数和替换点，然后由后向前找第一个比替换数大的数与替换数交换，最后颠倒替换点后的所有数据。

    vector<vector<int> > FullRangeRecursion(vector<int> & vec) {
        vector<vector<int> > result;
        FullRangeReucrisionImpl(vec, 0, vec.size() - 1, result);
        return result;
    }

    void FullRangeReucrisionImpl(vector<int>& vec, int cursor, int end, vector<vector<int> > &result) {

        if (vec.empty())
            return;

        if (cursor == end) {
            result.push_back(vec);
        }
        else {
            // 固定第一个值, 然后递归剩余的数, 直到最后一个数.
            // 依次交换第一个值和后面的数得到所有的情况
            // 1 23  第一层交换
            // 1 32
            // 2 13  第一层交换
            // 2 31
            // 3 21  第一层交换
            // 3 12
            for (int i = cursor; i <= end; i++) {

                if (!IsSwap(vec, cursor, i))
                    continue;

                Swap(vec[cursor], vec[i]);
                // 注意: 这是 cursor + 1, 是不是 i+1. 浪费了3个小时, 真是sb了
                FullRangeReucrisionImpl(vec, cursor + 1, end, result);
                Swap(vec[cursor], vec[i]); // 保持原始序列

            }
        }
    }

    
    // 非递归实现, 字典序算法. 字典序不受重复元素的影响, 比较大小, 重复的不变就行
    vector<vector<int> > FullRangeNoRecu(vector<int> & vec) {
        vector<vector<int> > result;
        if (vec.empty())
            return result;
        std::sort(vec.begin(), vec.end());// 先排序找到最小的情况, 然后再找到最大的情况为止.

        do {
            result.push_back(vec);
        } while (NextPermutation(vec));
        return result;
    }

    bool NextPermutation(vector<int> & vec) {
        if (vec.empty())
            return false;
        int end = (int) vec.size() - 1;
        // 从后先前找相邻是递增数
        int p = end;
        int q = 0;
        int bigger = 0;
        while (p > 0) {
            q = p;
            p--;
            if (vec[p] < vec[q]) { // 找降序的相邻2数,前一个数即替换数  
                bigger = end;
                while (vec[bigger] <= vec[p]) // 后面都是逆序的, 那么第一个大于p的数据, 就是大于他的最小的数
                    bigger--;
                Swap(vec[bigger], vec[p]);
                // 替换点后的数全部反转  
                std::reverse(vec.begin() + q, vec.end());
                return true;
            }
        }
        std::reverse(vec.begin() + p, vec.end()); // 如果没有下一个排列,全部反转后返回false
        return false;
    }

    void Test() {
        int arr[] = {1, 2, 2, 2};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        vector<vector<int> > result = FullRangeRecursion(vec);
        cout << "FullRangeRecursion: " << endl;
        cout << "result.size(): " << result.size() << endl;
        for (int i = 0; i < (int) result.size(); i++) {
            ShowVector<int>(result[i]);
        }

        cout << "FullRangeNoRecu: " << endl;
        result.clear();
        result = FullRangeNoRecu(vec);
        cout << "result.size(): " << result.size() << endl;
        for (int i = 0; i < (int) result.size(); i++) {
            ShowVector<int>(result[i]);
        }

    }

private:

    void Swap(int & a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    bool IsSwap(vector<int>& vec, int cursor, int nowPos) {
        for (int i = cursor; i < nowPos; i++) {
            if (vec[i] == vec[nowPos])
                return false;
        }
        return true;
    }
};




#endif /* CLASSICALGORITHMANALYSIS_HPP */

