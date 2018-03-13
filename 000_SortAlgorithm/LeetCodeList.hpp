/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeList.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年3月7日, 下午4:05
 */

#ifndef LEETCODELIST_HPP
#define LEETCODELIST_HPP

#include "Common.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;

// list

// 2. Add Two Numbers 
// topics: linked list, math

/*
 * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 * Example
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 */

class AddTwoNumbers {
    // Definition for singly-linked list.

    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {
        }
    };


public:

    // first version. 
    // 1. push new code at front, then need reserve the list
    // 2. use preHead, push new node at end;

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int last1 = 0;
        ListNode preHead(0), *p = &preHead;
        while (l1 != NULL || l2 != NULL) {
            int value1 = 0;
            int value2 = 0;
            if (l1 != NULL) {
                value1 = l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                value2 = l2->val;
                l2 = l2->next;
            }
            int sum = value1 + value2 + last1;
            if (sum >= 10) {
                sum -= 10;
                last1 = 1;
            }
            else {
                last1 = 0;
            }
            p->next = new ListNode(sum);
            p = p->next;
        }
        if (1 == last1) {
            p->next = new ListNode(1);
            p = p->next;
        }
        return preHead.next;
    }

    ListNode* bettterAddTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode preHead(0), *p = &preHead;
        int extra = 0;
        while (l1 || l2 || extra) {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
            extra = sum / 10;
            p->next = new ListNode(sum % 10);
            p = p->next;
            l1 = l1 ? l1->next : l1;
            l2 = l2 ? l2->next : l2;
        }
        return preHead.next;
    }

    ListNode* reserveList(ListNode* head) {
        // 反转链表
        ListNode* last = NULL;
        ListNode* next = NULL;
        ListNode* temp = head;
        for (; temp != NULL;) {
            cout << temp->val << ", ";
            next = temp->next;
            temp->next = last;
            last = temp;
            temp = next;
        }
        return last;
    }

    void Test() {
        ListNode* l1 = NULL;
        for (int i = 4; i < 7; i++) {
            ListNode * temp = new ListNode(i);
            temp->next = l1;
            l1 = temp;
        }

        ListNode* l2 = NULL;
        for (int i = 5; i < 8; i++) {
            ListNode * temp = new ListNode(i);
            temp->next = l2;
            l2 = temp;
        }

        ListNode* result = addTwoNumbers(l1, l2);
        while (result != NULL) {
            cout << result->val;
            result = result->next;
        }
        cout << endl;

        ListNode* result2 = bettterAddTwoNumbers(l1, l2);
        while (result2 != NULL) {
            cout << result2->val;
            result2 = result2->next;
        }
        cout << endl;
    }

};



#endif /* LEETCODELIST_HPP */

