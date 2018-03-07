/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeString.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年3月7日, 下午7:37
 */

#ifndef LEETCODESTRING_HPP
#define LEETCODESTRING_HPP

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


class LongestSubstring {
public:

    int lengthOfLongestSubstring(string s) {
        vector<int> dict(256, -1);
        int maxLen = 0, start = -1;
        for (int i = 0; i != s.length(); i++) {
            if (dict[s[i]] > start)
                start = dict[s[i]];
            dict[s[i]] = i;
            maxLen = std::max(maxLen, i - start);
        }
        return maxLen;
    }
};


#endif /* LEETCODESTRING_HPP */

