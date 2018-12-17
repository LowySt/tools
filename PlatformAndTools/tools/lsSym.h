#ifndef LS_SYM_H
#define LS_SYM_H

#ifndef LS_CRT_H
#include "lsCRT.h"
#endif

#ifndef LS_MATH_H
#include "Maths\Maths.h"
#endif

#define LIST_STYLE 0
#define STACK_STYLE !LIST_STYLE

enum sym_exprType
{
	SYM_EXPR_CONSTANT = 1,
	SYM_EXPR_POLYNOMIAL,
    
	SYM_EXPR_INDEFINITE
};

enum sym_nodeType
{
	SYM_NODE_CONSTANT = 1,
	SYM_NODE_VARIABLE,
	SYM_NODE_OP,
    SYM_NODE_SUBEXPR,
    
	SYM_NODE_INDEFINITE
};

enum sym_op
{
	SYM_OP_ADD = 1,
	SYM_OP_SUB,
	SYM_OP_MUL,
	SYM_OP_DIV,
    
	SYM_OP_INDEFINITE
};
#if LIST_STYLE
struct sym_node
{
	sym_op op;
	sym_nodeType nodeType;
	f32 val;
    
	sym_node *next;
	sym_node *prev;
    
    struct sym_expr *subExpr;
};

struct sym_expr
{
	sym_node *head;
    sym_node *tail;
    
    sym_exprType type;
    
	char variable;
};

struct sym_rootExpr
{
    sym_expr lhs;
    u32 leftNodes;
    
    sym_expr rhs;
    u32 rightNodes;
};

struct sym_result
{
	char variable;
	f32 val;
};

extern "C"
{
	sym_rootExpr sym_load(char *path);
	sym_result sym_solve(sym_rootExpr e);
}

#elif STACK_STYLE

struct sym_node
{
	sym_nodeType nodeType;
	f32 val;
    
    sym_op op;
};

struct sym_expr
{
    stack<sym_node> lhs;
    stack<sym_node> rhs;
};

struct sym_result
{
	char variable;
	f32 val;
};

extern "C"
{
	sym_expr sym_load(char *path);
	sym_result sym_solve(sym_expr e);
}

#endif

#endif

#ifdef LS_SYM_IMPLEMENTATION

#if LIST_STYLE
/* @TODO: @NOTE: Should I make variable coefficients 
 * a separate thing instead of using the value field? */
void sym_doOps(sym_node *n)
{
	sym_node *curr = n;
	sym_node *cp = 0;
	sym_node *cn = 0;
	sym_node *p = 0;
    
	f32 newVal = 0;
	while (curr)
	{
		cn = curr->next;
		cp = curr->prev;
		p = curr;
        
		switch (curr->op)
		{
			case SYM_OP_ADD:
			case SYM_OP_SUB:
			{
				if (isZero(cn->val))
				{
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
					curr = cn->next;
                    
					ls_free(cn);
					ls_free(p);
					continue;
				}
                
				if (cp->nodeType == SYM_NODE_VARIABLE)
				{
					curr = curr->next;
					continue;
				}
                
				if (curr->op == SYM_OP_SUB) { cn->val = -cn->val; }
				newVal = cp->val + cn->val;
				cp->val = newVal;
                
				cp->next = cn->next;
				if (cn->next) { (cn->next)->prev = cp; }
				curr = cn->next;
                
				ls_free(cn);
				ls_free(p);
				continue;
			}
            
			case SYM_OP_MUL:
			{
				if (isVal(cn->val, 1.0f))
				{
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
					curr = cn->next;
                    
					ls_free(cn);
					ls_free(p);
					continue;
				}
                
				if (isZero(cn->val))
				{
					cp->nodeType = SYM_NODE_CONSTANT;
					cp->val = 0.0f;
					
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
					curr = cn->next;
                    
					ls_free(cn);
					ls_free(p);
					continue;
				}
                
				if (cp->nodeType == SYM_NODE_VARIABLE)
				{
					cp->val = cn->val;
                    
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
					curr = cn->next;
                    
					ls_free(cn);
					ls_free(p);
					continue;
				}
                
				newVal = cp->val * cn->val;
				cp->val = newVal;
                
				cp->next = cn->next;
				if (cn->next) { (cn->next)->prev = cp; }
				curr = cn->next;
                
				ls_free(cn);
				ls_free(p);
				continue;
			}
			case SYM_OP_DIV:
			{
				if (isVal(cn->val, 1.0f))
				{
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
					curr = cn->next;
                    
					ls_free(cn);
					ls_free(p);
					continue;
				}
                
				if (isZero(cn->val))
				{
					ls_printf("ERROR! Can't divide by zero!");
					Assert(FALSE);
				}
                
				/* @TODO: @NOTE: Won't handle coefficients for now, 
     * because I'm not doing them well... */
                
				newVal = cp->val / cn->val;
				cp->val = newVal;
                
				cp->next = cn->next;
				if (cn->next) { (cn->next)->prev = cp; }
				curr = cn->next;
                
				ls_free(cn);
				ls_free(p);
				continue;
                
				continue;
			}
            
			default:
			{
				curr = curr->next;
				break;
			}
		}
	}
#if 0
	do
	{
		if (curr->nodeType == SYM_NODE_OP)
		{
			if (((curr->op == SYM_OP_ADD) || (curr->op == SYM_OP_SUB) )&& (isZero(curr->next->val)))
			{
				sym_node *op, *zero;
				op = curr;
				zero = curr->next;
				curr = zero->next;
                
				if (zero->next)
				{ 
					(op->prev)->next = zero->next;
					(zero->next)->prev = op->prev;
				}
				else
				{ (op->prev)->next = 0; }
                
				ls_free(op);
				ls_free(zero);
                
				continue;
			}
			else if(((curr->prev)->nodeType == SYM_NODE_CONSTANT) && ( (curr->next)->nodeType == SYM_NODE_CONSTANT))
			{
				sym_node *cp = curr->prev;
				sym_node *cn = curr->next;
				sym_node *op = curr;
                
				f32 newVal = 0;
                
				switch (curr->op)
				{
                    case SYM_OP_ADD:
					newVal = cp->val + cn->val;
					cp->val = newVal;
                    
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
                    
					curr = cn->next;
                    
					ls_free(op);
					ls_free(cn);
					continue;
                    
                    case SYM_OP_SUB:
					newVal = cp->val - cn->val;
					cp->val = newVal;
                    
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
                    
                    
					curr = cn->next;
                    
					ls_free(op);
					ls_free(cn);
					continue;
                    
                    case SYM_OP_DIV:
					newVal = cp->val / cn->val;
					cp->val = newVal;
                    
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
                    
					curr = cn->next;
                    
					ls_free(op);
					ls_free(cn);
					continue;
                    
                    case SYM_OP_MUL:
					newVal = cp->val * cn->val;
					cp->val = newVal;
                    
					cp->next = cn->next;
					if (cn->next) { (cn->next)->prev = cp; }
                    
					curr = cn->next;
                    
					ls_free(op);
					ls_free(cn);
					continue;
                    
                    default:
					ls_printf("Unkown operation: %d\n", curr->op);
					break;
				}
			}
		}
        
		if(curr) { curr = curr->next; }
        
	} while (curr);
#endif
}

u32 sym_parseExpr(string *e, u32 idx, sym_expr *expr)
{
	sym_node *curr = expr->head;
	f32 val = 0.0f;
	b32 Found = FALSE;
    
    u32 y = 0;
    u32 subElem = 0;
    
    u64 oldSize, newSize;
    
    u32 numOfNodesInRoot = 0;
    
	for (u32 i = 0; i < idx; i++)
	{
		if (e[i].size == 1)
		{
			switch (*e[i].data)
			{
                case 'x':
				expr->variable = 'x';
				curr->nodeType = SYM_NODE_VARIABLE;
				break;
                case '+':
				curr->nodeType = SYM_NODE_OP;
				curr->op = SYM_OP_ADD;
				break;
                case '-':
				curr->nodeType = SYM_NODE_OP;
				curr->op = SYM_OP_SUB;
				break;
                case '/':
				curr->nodeType = SYM_NODE_OP;
				curr->op = SYM_OP_DIV;
				break;
                case '*':
				curr->nodeType = SYM_NODE_OP;
				curr->op = SYM_OP_MUL;
				break;
                case '(':
                y = i + 1;
                subElem = 0;
                while(*e[y].data != ')')
                {
                    subElem++; y++; 
                    if (y >= idx)
                    { ls_printf("Malformed Expression, no closing bracket\n"); }
                }
                
                curr->subExpr = (sym_expr *)ls_alloc(sizeof(sym_expr));
                curr->subExpr->head = (sym_node *)ls_alloc(sizeof(sym_node));
                curr->nodeType = SYM_NODE_SUBEXPR;
                
                
                
                sym_parseExpr(&e[i + 1], subElem, curr->subExpr);
                
                i += subElem + 1; // Advance by Sub Elements + Closing Brace
				break;
                default:
				val = ls_atof(e[i].data, 1);
				curr->nodeType = SYM_NODE_CONSTANT;
				curr->val = val;
				break;
			}
		}
		else
		{
			val = ls_atof(e[i].data, e[i].size);
			curr->nodeType = SYM_NODE_CONSTANT;
			curr->val = val;
		}
        
        numOfNodesInRoot++;
        
		if ((!curr->next) && (i < idx - 1))
		{
			curr->next = (sym_node *)ls_alloc(sizeof(sym_node));
			(curr->next)->prev = curr;
			curr = curr->next;
		}
	}
    
    expr->tail = curr;
    
	if (expr->variable != 0)
	{ expr->type = SYM_EXPR_POLYNOMIAL; }
	else
	{ expr->type = SYM_EXPR_CONSTANT; }
    
    return numOfNodesInRoot;
}

sym_rootExpr sym_load(char *path)
{
	sym_rootExpr Result = {};
    sym_expr *lhs = &Result.lhs;
    sym_expr *rhs = &Result.rhs;
    
    lhs->head = (sym_node *)ls_alloc(sizeof(sym_node));
    rhs->head = (sym_node *)ls_alloc(sizeof(sym_node));
    
    
	/* ---------------
   |	READ THE FILE |
    ---------------  */
    
	char *f;
	u64 size = ls_readFile(path, &f, 0);
    
	/* ---------------
   | SEPARATE NODES |
    ---------------  */
    
	u32 lnum = 0, rnum = 0, lchars = 0;
	string *lstring, *rstring;
    lstring = ls_breakBySpaceDelimiter(f, '=', &lnum, &lchars);
    rstring = ls_breakBySpace(f + lchars, &rnum, 0);
    
	/* --------
   | NODIFY |
    --------  */
    
    Result.leftNodes = sym_parseExpr(lstring, lnum, lhs);
    Result.rightNodes = sym_parseExpr(rstring, rnum, rhs);
    
	return Result;
}

void sym_untangle(sym_expr *e)
{
    sym_node *curr = e->head;
    
    while(curr)
    {
        if(curr->subExpr)
        {
            
        }
        
        curr = curr->next;
    }
}

sym_result sym_solve(sym_rootExpr e)
{
	sym_result Result = {};
    
    sym_expr *currExpr = &e.lhs;
    sym_node *currNode = e.lhs.head;
    
    
	/* ----------------------
   | UNTAGLE SUBEXPRESSIONS |
------------------------  */
    
    sym_untangle(currExpr);
#if 0
	/* -------------------
| ORDER THE POLYNOMIAL |
----------------------  */
    
    // Variables on the left, constants on the right
    
	sym_node *newTail = 0;
	sym_node *p = 0;
    
    for(u32 i = 0; i < e.leftNodes; i++)
    {
        switch(currNode->nodeType)
        {
            case SYM_NODE_CONSTANT:
            {
                sym_node val = *currNode;
                sym_node *nn = currExpr->tail;
                // The node needs to bring the previous operation with it.
                if(currNode->prev->type == SYM_NODE_OP)
                {
                    sys_node op = *currNode->prev;
                    
                    nn->next = (sys_node *)ls_alloc(sizeof(sys_node));
                    nn = nn->next;
                    *nn = op;
                    
                    currExpr->tail = nn;
                }
                
                nn->next = (sys_node *)ls_alloc(sizeof(sys_node));
                nn = nn->next;
                *nn = val;
                
                ls_memcpy(currNode, currExpr->tail->next, sizeof(sys_node));
                currExpr->tail->next->next = 0;
                currExpr->tail->next->prev = currExpr->tail;
                currExpr->tail = currExpr->tail->next;
                
                currNode->prev->next = currNode->next;
                currNode->next->prev = currNode->prev;
                
                void *p = (void *)currNode;
                currNode = currNode->next;
                
                ls_free(p);
            }
            break;
            case SYM_NODE_SUBEXPR:
            {
                if(currNode.subExpr->type == SYM_EXPR_CONSTANT)
                {
                    
                }
            }
        }
    }
    
    currNode = e.rhs.head;
    
    for(u32 i = 0; i < e.rightNodes; i++)
    {
        
    }
    
	/* ---------------------
    | MULS AND DIVS FIRST |
    ---------------------   */
    
	f32 newVal = 0.0f;
    
	sym_doOps(curr);
    
	do
	{
        if (curr->nodeType == SYM_NODE_CONSTANT)
        {
            if(curr->prev->op == SYM_OP_SUB) 
            {
                curr->prev->op = SYM_OP_ADD;
                curr->val = -curr->val;
            }
            
            e.rhsTail->next = (sym_node *)ls_alloc(sizeof(sym_node));
            newTail = e.rhsTail->next;
            newTail->nodeType = SYM_NODE_OP;
            newTail->op = SYM_OP_ADD;
            
            newTail->prev = e.rhsTail;
            newTail->next = 0;
            e.rhsTail = newTail;
            
            e.rhsTail->next = (sym_node *)ls_alloc(sizeof(sym_node));
            newTail = e.rhsTail->next;
            *newTail = *curr;
            
            newTail->prev = e.rhsTail;
            newTail->next = 0;
            e.rhsTail = newTail;
            e.rhsTail->val = -e.rhsTail->val;
            
            curr->val = 0.0f;
        }
        
        curr = curr->next;
	} while (curr);
    
	curr = e.rhsHead;
    
	//@INCOMPLETE
	do
	{
        if (curr->nodeType == SYM_NODE_VARIABLE)
        {
            e.lhsTail->next = (sym_node *)ls_alloc(sizeof(sym_node));
            *e.lhsTail->next = *curr;
            
            p = curr;
            curr = curr->next;
            
            (p->prev)->next = p->next;
            (p->next)->prev = p->prev;
            
            ls_free(p);
        }
        
        curr = curr->next;
	} while (curr);
    
	/* ---------------------------
    | PERFORM OPS WHERE POSSIBLE |
    ---------------------------   */
    
	/*@TODO: @NOTE: Need to update the tail. sym_doOps doesn't do that!!*/
    
	sym_doOps(e.lhsHead);
	sym_doOps(e.rhsHead);
    
	if ((e.lhsHead->next == 0) && (e.rhsHead->next == 0))
	{
        Result.variable = e.variable;
        Result.val = e.rhsHead->val;
	}
    
#endif
	return Result;
}

#elif STACK_STYLE

b32 sym_isOperator(string *e)
{
    if(e->size > 1) { return FALSE; }
    
    switch(*e->data)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        return TRUE;
        
        default:
        return FALSE;
    }
    
    return FALSE;
}

void sym_parseExpr(string *e, u32 n, stack<sym_node> *expr)
{
    u32 level = 0;
    
    struct tuple {sym_node node; u32 level;};
    stack<sym_node> stackedOps;
    stack<sym_node> tempStack;
    
    for (u32 i = 0; i < n; i++)
    {
        sym_node curr = {};
        
        if(!sym_isOperator(&e[i]) && 
           ((*e[i+1].data == '*') || (*e[i+1].data == '/')))
        { level++; }
        
        if (e[i].size == 1)
        {
            switch (*e[i].data)
            {
                case '+':
                {
                    curr.nodeType = SYM_NODE_OP;
                    curr.op = SYM_OP_ADD;
                    stackedOps.push(curr);
                }
                break;
                
                case '-':
                {
                    curr.nodeType = SYM_NODE_OP;
                    curr.op = SYM_OP_SUB;
                    stackedOps.push(curr);
                }
                break;
                
                case '/':
                {
                    curr.nodeType = SYM_NODE_OP;
                    curr.op = SYM_OP_DIV;
                    stackedOps.push(curr);
                }
                break;
                
                case '*':
                {
                    curr.nodeType = SYM_NODE_OP;
                    curr.op = SYM_OP_MUL;
                    stackedOps.push(curr);
                }
                break;
                
                case '(':
                { level++; }
                break;
                
                case ')':
                {
                    level--;
                    
                    // Dump operators in inverse order
                    expr->push(&tempStack);
                    expr->pushInv(&stackedOps);
                }
                
                default:
                {
                    curr.nodeType = *e[i].data == 'x' ? SYM_NODE_VARIABLE : SYM_NODE_CONSTANT;
                    
                    if(curr.nodeType == SYM_NODE_CONSTANT)
                    { curr.val = ls_atof(e[i].data, e[i].size); }
                    
                    tempStack.push(curr);
                }
                break;
            }
        }
        else
        {
            curr.val = ls_atof(e[i].data, e[i].size);
            curr.nodeType = SYM_NODE_CONSTANT;
            tempStack.push(curr);
        }
    }
    
    return;
}

sym_expr sym_load(char *path)
{
    sym_expr Result = {};
    
    /* ---------------
    |	READ THE FILE |
    ---------------  */
    
    char *f;
    u64 size = ls_readFile(path, &f, 0);
    
    /* ---------------
    | SEPARATE NODES |
    ---------------  */
    
    u32 lnum = 0, rnum = 0, lchars = 0;
    string *lstring, *rstring;
    lstring = ls_breakBySpaceDelimiter(f, '=', &lnum, &lchars);
    rstring = ls_breakBySpace(f + lchars, &rnum, 0);
    
    /* --------
    | NODIFY |
    --------  */
    
    sym_parseExpr(lstring, lnum, &Result.lhs);
    sym_parseExpr(rstring, rnum, &Result.rhs);
    
    return Result;
}

sym_result sym_solve(sym_expr e)
{
    sym_result result = {};
    
    return result;
}

#endif


#endif