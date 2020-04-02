#ifndef LS_TREE_H
#define LS_TREE_H

#include "lsCRT.h"

typedef b32(*cmpFunc)(void *, void *);

struct BinaryTree
{
    void *data;
    
    BinaryTree *Left;
    BinaryTree *Right;
    
    BinaryTree *Parent;
};

extern "C"
{
    void ls_binaryTFree(BinaryTree *Root);
    
    void ls_binaryTAddLNode(BinaryTree *Root, void *data);
    void ls_binaryTAddRNode(BinaryTree *Root, void *data);
    
    void ls_binaryTRmvLTree(BinaryTree *Root, void *data);
    void ls_binaryTRmvRTree(BinaryTree *Root, void *data);
    
    BinaryTree *ls_binaryTSearch(BinaryTree *Root, void *target, cmpFunc F);
};
#endif

#ifdef LS_TREE_IMPLEMENTATION

void ls_binaryTFree(BinaryTree *Root)
{
    if(Root->Left) { ls_binaryTFree(Root->Left); }
    if(Root->Right) { ls_binaryTFree(Root->Right); }
    
    ls_free(Root->data);
    ls_free(Root);
}

void ls_binaryTAddLNode(BinaryTree *Root, void *data)
{
    Root->Left = (BinaryTree *)ls_alloc(sizeof(BinaryTree));
    Root->Left->data = data;
    
    Root->Left->Parent = Root;
}

void ls_binaryTAddRNode(BinaryTree *Root, void *data)
{
    Root->Right = (BinaryTree *)ls_alloc(sizeof(BinaryTree));
    Root->Right->data = data;
    
    Root->Right->Parent = Root;
}

void ls_binaryTRmvLTree(BinaryTree *Root, void *data)
{ ls_binaryTFree(Root->Left); }

void ls_binaryTRmvRTree(BinaryTree *Root, void *data)
{ ls_binaryTFree(Root->Right); }

BinaryTree *ls_binaryTSearch(BinaryTree *Root, void *target, cmpFunc F)
{
    // Traverse the binary tree and call the 
    // cmpFunc on every node's data
    
    b32 Result = FALSE;
    if(Root->data) 
    { Result = F(Root->data, target); }
    
    if(Result == TRUE) { return Root; }
    else 
    { 
        if((Root->Left == NULL) && (Root->Right == NULL))
        { return NULL; }
        
        else
        {
            if(Root->Right == NULL)
            { return ls_binaryTSearch(Root->Left, target, F); }
            
            if(Root->Left == NULL)
            { return ls_binaryTSearch(Root->Right, target, F); }
        }
    }
    
    return NULL;
}

#endif
