//filename : HashList.c

#include <stdio.h>
#include "HashList.h"

void HashKey(int Key,int *HValue)
/* �������:    ��� ���� Key ���� ��������. 
   ����������: ������� ��� ���� ��������������� HValue ��� �� ������ Key. 
   ����������: ��� ���� ��������������� HValue 
*/
{
	*HValue=Key%HMax + 1;
}

void CreateHashList(HashListType *HList)
/* ����������: ���������� ��� ���� HList. 
   ����������: ��� ���� HList 
*/
{
	int index;

	HList->Size=0;           //���������� ��� ���� �����
	HList->StackPtr=1;       //������� ��� ������ ��� ������� ��� ��������� ������
	
    /*����������� ��� ������ HashTable ��� ����� HList ���� ���� ��������� ��� 
        �� ���� �� ���� EndOfList (-1)*/
    index=1;
	while (index<=HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }
    
     //���������� ��� ������� ��� ��������� ������ ��� ����� HList
    index=1;
	while(index < VMax)
	{
		HList->List[index].Link=index+1;
		HList->List[index].Data=0;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
	
	for (index=1;index<=HMax;index++)
	   printf("%d, %d, \n",index,HList->HashTable[index]);
	
	for (index=1;index<=VMax;index++)
	   printf("%d, %d, \n",index,HList->List[index].Link);
}

boolean FullHashList(HashListType HList)
/* �������:    ��� ���� HList. 
   ����������: ������� �� � ����� List ��� ����� HList ����� ������. 
   ����������: TRUE �� � ����� List ����� ������, FALSE �����������. 
*/
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,int KeyArg,int *Loc,int *Pred)
/* �������:     ��� ���� HList ��� ��� ���� �������� KeyArg. 
    ����������: ������� ��� ������� �� ������ KeyArg ���� �������� ���������. 
    ����������: �� ���� Loc ��� �������� ��� �� ���� Pred ��� ������������ 
                �������� ���� �������� 
*/
{
	int Next;
	Next=HList.SubListPtr;
	int L1, P1;
	*Loc=0;
	*Pred=0;
	while(Next!=EndOfList)
	{
		if (HList.List[Next].RecKey==KeyArg)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;	
		}
	}
}
void SearchHashList(HashListType HList,int KeyArg,int *Loc,int *Pred)
/* �������:     ��� ���� HList ��� ��� ���� �������� KeyArg. 
    ����������: ������� ��� ������� �� ������ KeyArg ��� ���� HList. 
    ����������: �� ���� Loc ��� �������� ��� �� ���� Pred ��� 
                ������������ �������� ��� ��������� ���� ����� ������. 
                �� ��� ������� ������� �� ������ KeyArg ���� Loc=Pred=0 
*/
{
	int HVal;
	HashKey(KeyArg,&HVal);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=0;
		*Loc=0;
	}
	else 
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
/* �������:    ��� ���� HList ��� ��� ������� InRec. 
   ����������: ������� ��� ������� InRec ��� ����� List, �� ��� ����� ������, 
                ��� ���������� �� ���� HList. 
   ����������: ��� ������������� ���� HList. 
   ������:     ������ ������� ������, �� � List ����� ������, �����������, 
                �� ������� ��� ������� �� �� ���� ������, 
                �������� ����������� ��������� 
*/
{
	int Loc, Pred, New, HVal;
    
    New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=0;
		Pred=0;
		SearchHashList(*HList,InRec.RecKey,&Loc,&Pred);
		if(Loc==0) 
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==0)
			{
			    HashKey(InRec.RecKey,&HVal);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else 
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else 
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,int DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=0)
	{
		if(Pred!=0)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HashKey(DelKey,&HVal);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n",DelKey);
	}
}

