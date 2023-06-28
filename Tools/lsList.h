#ifndef LS_LIST_H
#define LS_LIST_H

struct list_node
{
    list_node *next;
    void      *item;
    
    b32        isAllocated;
};

// ------------------------
//NOTE: Singly Linked List
struct list
{
    list_node *head;
    s32        itemSize;
};

list       ls_listInit(s32 itemSize);
list_node *ls_listAppend(list *l, void *item);
list_node *ls_listAppendMem(list *l, void *item);
list_node *ls_listAppendAfter(list *l, list_node *node, void *item);
list_node *ls_listAppendAfterMem(list *l, list_node *node, void *item);
list_node *ls_listPrepend(list *l, void *item);
list_node *ls_listPrependMem(list *l, void *item);

void       ls_listRem(list *l, list_node *node);

void       ls_listFree(list *l);

//NOTE: Singly Linked List
// ------------------------


// ------------------------
//NOTE: Doubly Linked List
struct dlist_node
{
    dlist_node *next;
    dlist_node *prev;
    void       *item;
    
    b32         isAllocated;
};

struct dlist
{
    dlist_node *head;
    dlist_node *tail;
    
    s32        itemSize;
};

dlist       ls_dlistInit(s32 itemSize);
dlist_node *ls_dlistAppend(dlist *l, void *item);
dlist_node *ls_dlistAppendMem(dlist *l, void *item);
dlist_node *ls_dlistAppendAfter(dlist *l, dlist_node *node, void *item);
dlist_node *ls_dlistAppendAfterMem(dlist *l, dlist_node *node, void *item);
dlist_node *ls_dlistPrepend(list *l, void *item);
dlist_node *ls_dlistPrependMem(list *l, void *item);

void        ls_dlistRem(dlist *l, dlist_node *node);

void        ls_dlistFree(dlist *l);

//NOTE: Doubly Linked List
// ------------------------

#endif //LS_LIST_H


#ifdef LS_LIST_IMPLEMENTATION

// ------------------------
//NOTE: Singly Linked List
list ls_listInit(s32 itemSize)
{
    list result = {};
    result.itemSize = itemSize;
    
    return result;
}

list_node *ls_listAppend(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    list_node *curr = l->head;
    
    if(l->head == NULL)
    {
        l->head              = (list_node *)ls_alloc(sizeof(list_node));
        l->head->item        = ls_alloc(l->itemSize);
        l->head->isAllocated = TRUE;
        ls_memcpy(item, l->head->item, l->itemSize);
        return l->head;
    }
    
    while(curr->next != NULL) { curr = curr->next; }
    
    curr->next              = (list_node *)ls_alloc(sizeof(list_node));
    curr->next->item        = ls_alloc(l->itemSize);
    curr->next->isAllocated = TRUE;
    ls_memcpy(item, curr->next->item, l->itemSize);
    
    return curr->next;
}

list_node *ls_listAppendMem(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    list_node *curr = l->head;
    
    if(l->head == NULL)
    {
        l->head       = (list_node *)ls_alloc(sizeof(list_node));
        l->head->item = item;
        return l->head;
    }
    
    while(curr->next != NULL) { curr = curr->next; }
    
    curr->next       = (list_node *)ls_alloc(sizeof(list_node));
    curr->next->item = item;
    
    return curr->next;
}

list_node *ls_listAppendAfter(list *l, list_node *node, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    node->next              = (list_node *)ls_alloc(sizeof(list_node));
    node->next->item        = ls_alloc(l->itemSize);
    node->next->isAllocated = TRUE;
    ls_memcpy(item, node->next->item, l->itemSize);
    
    return node->next;
}

list_node *ls_listAppendAfterMem(list *l, list_node *node, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    node->next       = (list_node *)ls_alloc(sizeof(list_node));
    node->next->item = item;
    
    return node->next;
}

list_node *ls_listPrepend(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    list_node *newHead   = (list_node *)ls_alloc(sizeof(list_node));
    newHead->item        = ls_alloc(l->itemSize);
    newHead->isAllocated = TRUE;
    ls_memcpy(item, newHead->item, l->itemSize);
    
    newHead->next        = l->head;
    l->head              = newHead;
    
    return newHead;
}

list_node *ls_listPrependMem(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    list_node *newHead = (list_node *)ls_alloc(sizeof(list_node));
    newHead->next      = l->head;
    newHead->item      = item;
    l->head            = newHead;
    
    return newHead;
}

void ls_listRem(list *l, list_node *node)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    
    list_node *curr = l->head;
    
    if(curr == node)
    {
        l->head = node->next;
        
        if(node->isAllocated) { ls_free(node->item); }
        ls_free(node);
        return;
    }
    
    while(curr->next != node) { curr = curr->next; }
    
    curr->next = node->next;
    
    if(node->isAllocated) { ls_free(node->item); }
    ls_free(node);
}


void ls_listFree(list *l)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    
    list_node *curr = l->head;
    while(curr)
    {
        list_node *next = curr->next;
        
        if(curr->isAllocated) { ls_free(curr->item); }
        ls_free(curr);
        
        curr = next;
    }
    
    l->head = NULL;
    
    return;
}

//NOTE: Singly Linked List
// ------------------------

// ------------------------
//NOTE: Doubly Linked List

dlist ls_dlistInit(s32 itemSize)
{
    dlist result    = {};
    result.itemSize = itemSize;
    
    return result;
}

dlist_node *ls_dlistAppend(dlist *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    dlist_node *tail = l->tail;
    
    if(tail == NULL)
    {
        tail              = (dlist_node *)ls_alloc(sizeof(dlist_node));
        tail->item        = ls_alloc(l->itemSize);
        tail->isAllocated = TRUE;
        l->head           = tail;
        ls_memcpy(item, tail->item, l->itemSize);
        return tail;
    }
    
    tail->next              = (dlist_node *)ls_alloc(sizeof(dlist_node));
    tail->next->item        = ls_alloc(l->itemSize);
    tail->next->isAllocated = TRUE;
    tail->next->prev        = tail;
    ls_memcpy(item, tail->next->item, l->itemSize);
    tail = tail->next;
    return tail;
}

dlist_node *ls_dlistAppendMem(dlist *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    dlist_node *tail = l->tail;
    
    if(tail == NULL)
    {
        tail          = (dlist_node *)ls_alloc(sizeof(dlist_node));
        tail->item    = item;
        l->head       = tail;
        return tail;
    }
    
    tail->next       = (dlist_node *)ls_alloc(sizeof(dlist_node));
    tail->next->item = item;
    tail->next->prev = tail;
    tail             = tail->next;
    return tail;
}

dlist_node *ls_dlistAppendAfter(dlist *l, dlist_node *node, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    node->next              = (dlist_node *)ls_alloc(sizeof(dlist_node));
    node->next->item        = ls_alloc(l->itemSize);
    node->next->isAllocated = TRUE;
    node->next->prev        = node;
    ls_memcpy(item, node->next->item, l->itemSize);
    
    if(l->tail == node) { l->tail = node->next };
    
    return node->next;
}

dlist_node *ls_dlistAppendAfterMem(dlist *l, dlist_node *node, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    node->next       = (dlist_node *)ls_alloc(sizeof(dlist_node));
    node->next->prev = node;
    node->next->item = item;
    if(l->tail == node) { l->tail = node->next };
    
    return node->next;
}

dlist_node *ls_dlistPrepend(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    dlist_node *newHead  = (list_node *)ls_alloc(sizeof(list_node));
    newHead->item        = ls_alloc(l->itemSize);
    newHead->isAllocated = TRUE;
    ls_memcpy(item, newHead->item, l->itemSize);
    
    newHead->next        = l->head;
    l->head->prev        = newHead;
    l->head              = newHead;
    
    return newHead;
}

dlist_node *ls_dlistPrependMem(list *l, void *item)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(item != NULL, "Null item pointer\n");
    
    dlist_node *newHead = (list_node *)ls_alloc(sizeof(list_node));
    newHead->item       = item;
    
    newHead->next       = l->head;
    l->head->prev       = newHead;
    l->head             = newHead;
    
    return newHead;
}

void ls_dlistRem(dlist *l, dlist_node *node)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    AssertMsg(node != NULL, "Null node pointer\n");
    
    if(node->prev)        { node->prev->next = node->next; }
    if(node->next)        { node->next->prev = node->prev; }
    if(node->isAllocated) { ls_free(node->item); }
    
    if((node == head) && (node == tail))
    {
        l->head = NULL;
        l->tail = NULL;
    }
    
    ls_free(node);
}

void ls_dlistFree(dlist *l)
{
    AssertMsg(l != NULL, "Null list pointer\n");
    
    dlist_node *curr = l->head;
    while(curr)
    {
        dlist_node *next = curr->next;
        
        if(curr->isAllocated) { ls_free(curr->item); }
        ls_free(curr);
        
        curr = next;
    }
    
    l->head = NULL;
    l->tail = NULL;
    
    return;
}


//NOTE: Doubly Linked List
// ------------------------

#endif //LS_LIST_IMPLEMENTATION
