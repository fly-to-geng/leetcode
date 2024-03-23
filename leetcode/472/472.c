#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD 256 // 单词最大长度
#define MAX_CHAR 26 // 字母种类， 26个小写字母

typedef struct node{
    struct node* children[MAX_CHAR]; // 指向孩子们的指针数组
    char c; // 当前节点表示的字母
    bool isWord; // 记录单词结束标记
    bool isUsed; // 标记是否搜索过
} Trie;

Trie *groot = NULL;

void initChildren(Trie **children, int size) {
    for (int i = 0; i < size; i++) {
        children[i] = NULL;
    }
}

Trie* trieCreate() {
    Trie *root = (Trie*)malloc(sizeof(Trie));
    root->c = ' ';
    root->isWord = false;
    initChildren(root->children, MAX_CHAR);
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
            initChildren(newNode->children, MAX_CHAR);
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

int compare(const void *p, const void *q)
{
    char *a = *(char**)p;
    char *b = *(char**)q;
    if (strlen(a) != strlen(b)) {
        return strlen(a) - strlen(b);
    }
    return strcmp(a, b);
}

// 返回单词是否可拆分
bool dfs(char *word, int index, Trie *node, bool split)
{
    if (index >= strlen(word)) return false;

    char ic = word[index] - 'a';
    
    if (node->children[ic] == NULL && split == false) {
        // 前缀树中没有当前字母， 且没有拆分，加入前缀树
        Trie *newNode = (Trie*)malloc(sizeof(Trie));
        newNode->c = word[index];
        newNode->isWord = (index == strlen(word) - 1) ? true : false;
        initChildren(newNode->children, MAX_CHAR);
        node->children[ic] = newNode;
        return dfs(word, index + 1, newNode, split);
    } else if (node->children[ic] == NULL && split == true) {
        // 单词已经拆分，直接返回false
        return false;
    } else if (node->children[ic]->isWord && index == strlen(word) - 1 && split == true) {
        // 匹配到最后一个字母
        return true;
    }
    
    if (node->children[ic]->isWord) {
        // 拆分的时候设置该单词维已经使用，否则可能使用到重复的单词
        bool is = dfs(word, index + 1, groot, true);
        if (is) {
            return true;
        }
        
    }

    return dfs(word, index + 1, node->children[ic], split);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findAllConcatenatedWordsInADict(char ** words, int wordsSize, int* returnSize){
    *returnSize = 0;
    if (words == NULL || wordsSize <= 0) return NULL;

    char **ans = (char**)malloc(sizeof(char*) * wordsSize);
    int ansEnd = 0;

    qsort(words, wordsSize, sizeof(words[0]), compare);

    Trie *root = trieCreate();
    groot = root; // groot 保存全局的根节点
    for (int i = 0; i < wordsSize; i++) {
        bool is = dfs(words[i], 0, root, false);
        if (is) {
            ans[ansEnd++] = words[i];
        }
    }

    *returnSize = ansEnd;
    return ans;
}

int main()
{
    char *words[8] = {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    int wordsSize = 8;
    int returnSize = 0;
    char **ans = findAllConcatenatedWordsInADict(words, wordsSize, &returnSize);
    return 0;
}

/*
执行用时 :308 ms, 在所有 C 提交中击败了47.52%的用户
内存消耗 :211.8 MB, 在所有 C 提交中击败了100.00%的用户
*/