#ifndef LS_MULTITHREADING_HEADER
#define LS_MULTITHREADING_HEADER

#include "lsCRT.h"

extern "C"
{
	void *CreateWorker(void *params, b32 createSuspended, b32 isStackReserved);
	u64 ThreadProc(void *params);

	//void *asmCall(void *fnPtr, void **params, u32 *sizes, u32 numOfParams);
};



struct Thread
{
	void *Handle;
	u64	ID;
};

typedef void (*voidFunc)();
typedef void(*voidFunc8)(u8);
typedef void(*voidFunc16)(u16);
typedef void(*voidFunc32)(u32);
typedef void(*voidFunc64)(u64);

typedef void(*voidFuncF32)(f32);
typedef void(*voidFuncF64)(f64);

struct FnQueue
{
	void *FnPtr;
	void **paramList;
	u32  *sizeList;
	u32	 listSize;
	u32	 returnSize;

	FnQueue *nextFn;
};

struct ThreadManager
{
	Thread *Threads;
	u32		maxNumOfThreads;
	u32		currNumOfThreads;

	FnQueue	*workQueueHead;
	FnQueue	*workQueueLast;
	u32		queueMaxSize;
	u32		queueCurrSize;

	b32 addToQueue(FnQueue fn)
	{
		if (queueCurrSize == queueMaxSize)
		{ return FALSE; }

		workQueueLast->nextFn = &fn;
		workQueueLast = &fn;
		return TRUE;
	}

	void *execute()
	{
		FnQueue *Element = workQueueHead;
		workQueueHead = Element->nextFn;

		if (Element->returnSize == 0)
		{
			switch (Element->listSize)
			{
			case 0:
				voidFunc(Element->FnPtr)();
				return 0;
			case 1:
				switch (*Element->sizeList)
				{
					case 1:
						voidFunc8(Element->FnPtr)(*(u8 *)Element->paramList);
						break;
					case 2:
						voidFunc16(Element->FnPtr)(*(u16 *)Element->paramList);
						break;
					case 4:
						voidFunc32(Element->FnPtr)(*(u32 *)Element->paramList);
						break;
					case 8:
						voidFunc64(Element->FnPtr)(*(u64 *)Element->paramList);
						break;
				}
				return 0;
			}
		}

		ls_heapFree(Element);
		return 0;
	}
};

#endif

#ifdef LS_MULTITHREADING_IMPLEMENTATION

u64 ThreadProc(void *params)
{
	ThreadManager TM = *(ThreadManager *)params;

	if (TM.queueCurrSize == 0)
	{ return 0; }
	
	TM.execute();

	return 1;
}

b32 CreateWorker(ThreadManager *TM, void *params, b32 createSuspended, b32 isStackReserved = 0)
{
	Thread Result = { 0 };
	//In windows we do:
	size_t stackSize = NULL;	//Default stack size
	u64 CreationFlags = 0;		//Thread Starts Immediately

	if (createSuspended)	
	{ CreationFlags = CREATE_SUSPENDED; }

	if (isStackReserved)
	{ CreationFlags |= STACK_SIZE_PARAM_IS_A_RESERVATION; }

	Result.Handle = CreateThread(NULL, stackSize, (LPTHREAD_START_ROUTINE)ThreadProc, params, CreationFlags, LPDWORD(&Result.ID));
	
	if (Result.Handle == NULL) { return FALSE; }

	if (TM->currNumOfThreads == TM->maxNumOfThreads) { return FALSE; }
	TM->Threads[TM->currNumOfThreads++] = Result;

	return TRUE;
}

#endif