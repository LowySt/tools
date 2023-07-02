#ifndef LS_TREE_H
#define LS_TREE_H

#include "lsCRT.h"

//--------------------------
//NOTE: Binary Tree

struct TreeNode
{
    TreeNode *left;
    TreeNode *right;
    
    void *data;
};

struct BinaryTree
{
    TreeNode *root;
    s32       itemSize;
};

TreeNode   *__ls_binaryTCreateNode(BinaryTree *t, void *item);
BinaryTree  ls_binaryTInit(s32 itemSize, void *item);
TreeNode   *ls_binaryTInsertLeft(BinaryTree *t, TreeNode *root, void *item);
TreeNode   *ls_binaryTInsertRight(BinaryTree *t, TreeNode *root, void *item);
void        ls_binaryTPrint(BinaryTree *t, TreeNode *_root);

//NOTE: Binary Tree
//--------------------------


//--------------------------
//NOTE: Binary Search Tree

struct STreeNode
{
    STreeNode *left;
    STreeNode *right;
    
    s32 key;
    void *data;
};


struct BinarySTree
{
    STreeNode *root;
    s32        itemSize;
};


STreeNode   *__ls_binarySTCreateNode(BinarySTree *t, s32 key, void *item);
BinarySTree  ls_binarySTInit(s32 itemSize, s32 key, void *item);
STreeNode   *ls_binarySTInsert(BinarySTree *t, s32 key, void *item);
void         ls_binarySTPrint(BinarySTree *t, STreeNode *_root);

//NOTE: Binary Search Tree
//--------------------------

#endif //LS_TREE_H

#ifdef LS_TREE_IMPLEMENTATION

//--------------------------
//NOTE: Binary Tree

TreeNode *__ls_binaryTCreateNode(BinaryTree *t, void *item)
{
    AssertMsg(t != NULL, "Tree pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    TreeNode *node = (TreeNode *)ls_alloc(sizeof(TreeNode));
    node->data     = ls_alloc(t->itemSize);
    ls_memcpy(item, node->data, t->itemSize);
    return node;
}

BinaryTree ls_binaryTInit(s32 itemSize, void *item)
{
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    BinaryTree result = {};
    
    result.itemSize = itemSize;
    result.root     = __ls_binaryTCreateNode(&result, item);
    
    return result;
}

TreeNode *ls_binaryTInsertLeft(BinaryTree *t, TreeNode *root, void *item)
{
    AssertMsg(t != NULL, "Tree pointer is null\n");
    AssertMsg(root != NULL, "Root pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    AssertMsg(root->left == NULL, "Left node is not empty\n");
    
    root->left = __ls_binaryTCreateNode(t, item);
    return root->left;
}

TreeNode *ls_binaryTInsertRight(BinaryTree *t, TreeNode *root, void *item)
{
    AssertMsg(t != NULL, "Tree pointer is null\n");
    AssertMsg(root != NULL, "Root pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    AssertMsg(root->right == NULL, "Left node is not empty\n");
    
    root->right = __ls_binaryTCreateNode(t, item);
    return root->right;
}

void ls_binaryTPrint(BinaryTree *t, TreeNode *_root = NULL)
{
    TreeNode *root = _root; 
    if(root == NULL) { root = t->root; }
    
    s32 value = *(s32 *)root->data;
    ls_log("{s32} -> ", value);
    
    if(root->left)  { ls_binaryTPrint(t, root->left);  }
    if(root->right) { ls_binaryTPrint(t, root->right); }
}

//NOTE: Binary Tree
//--------------------------


//--------------------------
//NOTE: Binary Search Tree

STreeNode *__ls_binarySTCreateNode(BinarySTree *t, s32 key, void *item)
{
    AssertMsg(t != NULL, "Tree pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    STreeNode *node = (STreeNode *)ls_alloc(sizeof(STreeNode));
    node->key       = key;
    node->data      = ls_alloc(t->itemSize);
    ls_memcpy(item, node->data, t->itemSize);
    return node;
}

BinarySTree ls_binarySTInit(s32 itemSize, s32 key, void *item)
{
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    BinarySTree result = {};
    
    result.itemSize = itemSize;
    result.root     = __ls_binarySTCreateNode(&result, key, item);
    
    return result;
}

STreeNode *ls_binarySTInsert(BinarySTree *t, s32 key, void *item)
{
    AssertMsg(t != NULL, "Tree pointer is null\n");
    AssertMsg(item != NULL, "Item pointer is null\n");
    
    STreeNode *curr = t->root;
    STreeNode *next = curr;
    
    bool isLeft = FALSE;
    
    while(next != NULL)
    {
        curr = next;
        
        if(key < curr->key) { next = curr->left; isLeft = TRUE;   continue; }
        if(key > curr->key) { next = curr->right; isLeft = FALSE; continue; }
        
        if(key == curr->key) { return NULL; }
    }
    
    if(isLeft)  { curr->left  = __ls_binarySTCreateNode(t, key, item); return curr->left; }
    else        { curr->right = __ls_binarySTCreateNode(t, key, item); return curr->right; }
}

void ls_binarySTPrint(BinarySTree *t, STreeNode *_root = NULL)
{
    STreeNode *root = _root; 
    if(root == NULL) { root = t->root; }
    
    s32 value = *(s32 *)root->data;
    ls_log("Key: {s32}, Value: {s32} -> ", root->key, value);
    
    if(root->left)  { ls_log("left: "); ls_binarySTPrint(t, root->left);  }
    if(root->right) { ls_log("right: "); ls_binarySTPrint(t, root->right); }
}

//NOTE: Binary Search Tree
//--------------------------

#endif //LS_TREE_IMPLEMENTATION