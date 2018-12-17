struct list
{
	list *next;
	list *prev;

	void *data;
	u32 sizeOfData;
};

#define list_init(plist, pdata, sizeofData) \
				plist->next = NULL; \
				plist->prev = NULL; \
				plist->data = data; \
				plist->sizeOfData = sizeofData;

//void list_init(list *l, void *data, u32 sizeOfData)
//{
//	l->next = NULL;
//	l->prev = NULL;
//
//	l->data = data;
//	l->sizeOfData = sizeOfData;
//}

/* Inserts "newNode" after the passed list "l" */
void list_insertNode(list *l, list *newNode)
{
	list *tmp = l->next;
	l->next = newNode;
	newNode->prev = l;
	newNode->next = tmp;
}

void list_removeNode(list *node)
{
	(node->prev)->next = node->next;
	(node->next)->prev = node->prev;
}

void list_addTail(list *l, list *newNode)
{
	list *curr = l;

	while(curr->next)
	{ curr = curr->next; }

	curr->next = newNode;
	newNode->prev = curr;
}
