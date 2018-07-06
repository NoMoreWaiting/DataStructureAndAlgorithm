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
#include "LeetCodeString.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::multiset;
using std::set;
using std::string;
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


// 19. Remove Nth Node From End of List
// Topics: linked list, two pointers

/*
 * Given a linked list, remove the nth node from the end of list and return its head.
 * 
 * For example,
 *    Given linked list: 1->2->3->4->5, and n = 2.
 *    After removing the second node from the end, the linked list becomes 1->2->3->5.
 * Note:
 * Given n will always be valid.
 * Try to do this in one pass.
 */

class RemoveNthNodeFromEnd {
public:
    // Definition for singly-linked list.

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 改变值, 使用指针; 改变指针, 使用指针的指针
        ListNode* preHead = new ListNode(0);
        preHead->next = head;
        ListNode* fast = head;
        ListNode* slow = preHead;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while (NULL != fast) {
            fast = fast->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;

        return preHead->next;
    }

    ListNode* removeNthFromEnd2LevelPointer(ListNode* head, int n) {
        ListNode** t1 = &head, *t2 = head; // 改变值, 使用指针; 改变指针, 使用指针的指针
        for (int i = 1; i < n; ++i) {
            t2 = t2->next;
        }
        while (t2->next != NULL) {
            t1 = &((*t1)->next);
            t2 = t2->next;
        }
        *t1 = (*t1)->next;
        return head;
    }

    void Test() {
        std::string str = "12";
        ListNode* head = string2ListNode(str);
        head = removeNthFromEnd2LevelPointer(head, 1);
        cout << "removeNthFromEnd: " << endl;
        ShowListNode(head);
        head = removeNthFromEnd(head, 1);
        cout << "removeNthFromEnd: " << endl;
        ShowListNode(head);
    }

};


// 21. Merge Two Sorted Lists
// Topics: linked list

/*
 * Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
 * 
 * Example:
 * 
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 */

class MergeTwoSortedLists {
public:

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (NULL == l1 || NULL == l2) {
            return NULL == l1 ? l2 : l1;
        }
        ListNode * head = new ListNode(0);
        ListNode * temp = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                temp->next = l1;
                l1 = l1->next;
            }
            else {
                temp->next = l2;
                l2 = l2->next;
            }
            temp = temp->next;
        }

        temp->next = l1 ? l1 : l2;

        return head->next;
    }

    void Test() {
        std::string str1 = "1245";
        std::string str2 = "3589";

        ListNode * l1 = string2ListNode(str1);
        ListNode * l2 = string2ListNode(str2);

        cout << "MergeTwoSortedLists: " << endl;
        ShowListNode(mergeTwoLists(l1, l2));
    }

};


// 23. Merge k Sorted Lists
// Topics: linked list, divide and conquer, heap

/*
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity
 */

class MergeKSortedLists {
public:

    struct compare {

        bool operator()(const ListNode * a, const ListNode * b) {
            return a->val < b->val;
        }
    };

    // 使用优先队列. 每次选出最小值, 下一个入队, 继续排序, 选出最小

    ListNode* mergeKListsQueue(vector<ListNode*>& lists) {
        if (lists.empty())
            return NULL;

        multiset<ListNode*, compare> queue;

        ListNode * dummy = new ListNode(0);
        ListNode * tail = dummy;

        for (ListNode * node : lists) {
            if (NULL != node)
                queue.insert(node);
        }

        while (!queue.empty()) {
            tail->next = *queue.begin();
            queue.erase(queue.begin());
            tail = tail->next;
            if (NULL != tail->next)
                queue.insert(tail->next);
        }
        return dummy->next;
    }

    // 使用递归分治, 两两合并

    ListNode* mergeKListsDAC(vector<ListNode*>& lists) {
        if (lists.empty())
            return NULL;
        int len = lists.size();
        while (len > 1) {
            // 头尾合并. 也可以遍历的时候取前两个合并, 比较耗时间
            for (int i = 0; i < len / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[len - 1 - i]);
            }
            len = (len + 1) / 2;
        }

        return lists.front();
    }

    ListNode *mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (NULL == l1)
            return l2;
        else if (NULL == l2)
            return l1;

        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    void Test() {
        std::string str1 = "1356";
        std::string str2 = "02469";
        std::string str3 = "1289";
        vector<ListNode*> lists;
        lists.push_back(string2ListNode(str1));
        lists.push_back(string2ListNode(str2));
        lists.push_back(string2ListNode(str3));


        cout << "mergeKListsQueue: ";
        ListNode * result = mergeKListsQueue(lists);
        ShowListNode(result);

        str1 = "1356789";
        str2 = "02469";
        str3 = "12589";
        vector<ListNode*> lists_back;
        lists_back.push_back(string2ListNode(str1));
        lists_back.push_back(string2ListNode(str2));
        lists_back.push_back(string2ListNode(str3));

        cout << "mergeKListsDAC: ";
        result = mergeKListsDAC(lists_back);
        ShowListNode(result);
    }
};


// 24. Swap Nodes in Pairs
// Topics: linked lists

/*
 * Given a linked list, swap every two adjacent nodes and return its head.
 * 
 * Example:
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 * 
 * Note:
 * Your algorithm should use only constant extra space.
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 */


class SwapNodesInPairs {
public:

    ListNode* swapPairs(ListNode* head) {
        // first, check the param
        if (NULL == head || NULL == head->next)
            return head;

        ListNode* pre = new ListNode(0);
        pre->next = head;
        // notice here: ListNode* first, second; then first is different from second, the pre is ListNode * type, and next is ListNode.
        ListNode* first = NULL;
        ListNode* second = NULL;
        ListNode* origin = pre;
        while (pre->next && pre->next->next) {
            first = pre->next;
            second = pre->next->next;

            first->next = second->next;
            second->next = first;
            pre->next = second;

            pre = pre->next->next;
        }
        return origin->next;
    }

    void Test() {
        std::string str = "12345";
        ListNode * node = string2ListNode(str);
        node = swapPairs(node);
        cout << "swapPairs: ";
        ShowListNode(node);
    }

};


// 25. Reverse Nodes in k-Group
// Topics: linked list

/*
 * Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
 * k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
 * 
 * Example:
 * Given this linked list: 1->2->3->4->5
 * For k = 2, you should return: 2->1->4->3->5
 * For k = 3, you should return: 3->2->1->4->5
 * 
 * Note:
 * Only constant extra memory is allowed.
 * You may not alter the values in the list's nodes, only nodes itself may be changed.
 */

class ReverseNodesInkGroup {
public:

    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) return head;
        ListNode* origin = new ListNode(0);
        origin->next = head;
        ListNode* left = origin, *right = NULL;
        ListNode* tempHead = origin;

        ListNode * arr[k];
        int i = 0;
        while (true) {
            tempHead = left; // 数组的前一位, 链接下一个循环的数组

            for (i = 0; i < k && tempHead->next; i++) {
                *(arr + i) = tempHead->next;
                tempHead = tempHead->next;
            }
            if (i < k) {
                head = origin->next;
                delete origin;
                break;
            }

            // 此时tempHead是数组的最后一位
            right = tempHead->next; // 数组后的一位, 下一次循环的开头

            for (int num = k - 1; num > 0; num--) {
                (*(arr + num))->next = *(arr + num - 1);
            }
            // 数组元素的第一位指向数组的后一位
            (*(arr))->next = right;
            // left指向数组首元素, 其next指向下一个数组未倒序前的首元素
            left->next = *(arr + k - 1);
            left = *arr;
        }
        return head;
    }

    // 记住链表的2端位置, 就是记住了整个链表, 后续返回直接当插入就行

    ListNode *anotherReverseKGroup(ListNode *head, int k) {
        if (head == NULL || k == 1) return head;
        int num = 0;
        ListNode *preheader = new ListNode(-1);
        preheader->next = head;
        ListNode *cur = preheader, *nex, *pre = preheader;
        while ((cur = cur->next))
            num++;
        while (num >= k) {
            cur = pre->next;
            nex = cur->next;
            for (int i = 1; i < k; ++i) {
                cur->next = nex->next;
                nex->next = pre->next;
                pre->next = nex;
                nex = cur->next;
                ShowListNode(preheader);
            }
            pre = cur; // 只要记住链表的首尾两端, 那么移动的时候链表就会整体移动(相当于在已反转过的链表中插入剩余的反转节点)
            num -= k;
        }
        return preheader->next;
    }

    void Test() {
        std::string str = "1234567890";
        ListNode * head = string2ListNode(str);
        head = reverseKGroup(head, 4);
        cout << "reverseKGroup: ";
        ShowListNode(head);
        head = anotherReverseKGroup(head, 4);
        cout << "anotherReverseKGroup: ";
        ShowListNode(head);
    }
};


#endif /* LEETCODELIST_HPP */

