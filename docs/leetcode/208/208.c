#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHAR_MAX 26

typedef struct node{
    struct node* children[CHAR_MAX]; // 指向孩子们的指针数组
    char c; // 当前节点表示的字母
    bool isWord; // 记录单词结束标记
} Trie;

void initChildren(Trie **children, int size) {
    for (int i = 0; i < size; i++) {
        children[i] = NULL;
    }
}
/** Initialize your data structure here. */
Trie* trieCreate() {
    Trie *root = (Trie*)malloc(sizeof(Trie));
    root->c = ' ';
    root->isWord = false;
    initChildren(root->children, CHAR_MAX);
    return root;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
    if (word == NULL) return;
    const int n = strlen(word);
    if (n == 0) return;

    Trie *curr = obj;
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a'; // 转换成索引
        if (curr->children[index] == NULL) {
            // 该字符还不存在，插入一个新的节点
            Trie *newNode = (Trie*)malloc(sizeof(Trie));
            newNode->c = word[i];
            newNode->isWord = (i == n - 1) ? true : false;
            initChildren(newNode->children, CHAR_MAX);
            curr->children[index] = newNode;
            curr = newNode;
        } else {
            // 如果存在，判断是否到了最后一个
            if (i == n - 1) {
                curr->children[index]->isWord = true;
            }
            curr = curr->children[index];
        }
    }
    return;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
    if (obj == NULL || word == NULL) return false;
    const int n = strlen(word);
    Trie *curr = obj;
    for (int i = 0; i < n; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return false;
        } else if (i == n - 1 && curr->children[index]->isWord == true) {
            return true;
        } else {
            curr = curr->children[index];
        }
    }
    return false;
}

/* 真前缀才返回 true */
bool trieStartsWithTrue(Trie* obj, char * prefix) {
     if (obj == NULL || prefix == NULL) return false;
     const int n = strlen(prefix);
     Trie *curr = obj;
     for (int i = 0; i < n; i++) {
         int index = prefix[i] - 'a';
         if (curr->children[index] == NULL) {
             return false;
         } else if (i == n - 1) {
             // 如果检查到最后一个字母，
             // 没有单词结束标志，直接返回 true
             // 有单词结束标记，判断是否有孩子，没有孩子，说明不是真前缀
             // 有孩子，说明是某个单词的真前缀
             if (curr->children[index]->isWord == false) return true;
             bool ans = false;
             Trie *next = curr->children[index];
             for (int j = 0; j < CHAR_MAX; j++) {
                 if (next->children[j] != NULL) {
                     ans = true;
                     break;
                 }
             }
             return ans;
         } else {
             curr = curr->children[index];
         }
     }
     return false;
}

// 等于单词也认为是前缀
bool trieStartsWith(Trie* obj, char * prefix) {
     if (obj == NULL || prefix == NULL) return false;
     const int n = strlen(prefix);
     Trie *curr = obj;
     for (int i = 0; i < n; i++) {
         int index = prefix[i] - 'a';
         if (curr->children[index] == NULL) {
             return false;
         } else if (i == n - 1) {
             return true;
         } else {
             curr = curr->children[index];
         }
     }
     return false;
}

void trieFree(Trie* obj) {
    if (obj == NULL) return;
    for (int i = 0; i < CHAR_MAX; i++) {
        if (obj->children[i] != NULL) {
            free(obj->children[i]);
        }
    }
    free(obj);
}

int main()
{
    Trie *obj = trieCreate();
    
    trieInsert(obj, "apple");
    bool ans_1 = trieSearch(obj, "apple");   // 返回 true
    trieSearch(obj, "app");     // 返回 false
    bool ans_2 = trieStartsWith(obj, "app"); // 返回 true
    trieInsert(obj, "app");   
    bool ans_3 = trieSearch(obj, "app");     // 返回 true
    bool ans_4 = trieStartsWithTrue(obj, "app"); // 返回true
    bool ans_5 = trieStartsWithTrue(obj, "apple"); // 返回false

    trieFree(obj);
    return 0;
}
/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/