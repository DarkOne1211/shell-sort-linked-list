#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

Node* Load_From_File(char *Filename)
{
    // Variable Declaration

    FILE *readptr;
    long value = 0;
    Node *dummy = NULL;
    Node *Array = NULL;
    Node *Pnode = NULL;

    // Opening the file 

    readptr = fopen(Filename, "rb");

    if(readptr == NULL)
    {
        fprintf(stderr, "The file is empty or doesnot exist\n");
        return NULL;
    }

    // Copying the elements in to a linked list

    // Array points to the first element of the List

    Array = malloc(sizeof(Node));

    if(Array == NULL)
    {
        fclose(readptr);
        fprintf(stderr,"Malloc Fail\n");
        return NULL;
    }

    if(fread(&value,sizeof(value),1,readptr))
    {   
        Array->value = value;
        Array->next = NULL;
    }
    
    else 
    {
        fclose(readptr);
        free(Array);
        fprintf(stderr, "Error reading file\n");
        return NULL;
    }


    // Dummy points to the last element on the List

    dummy = malloc(sizeof(Node));
    
    if(dummy == NULL)
    {
        fprintf(stderr,"Malloc Fail\n");
        free(Array);
        fclose(readptr);
        return NULL;
    }

    if(fread(&value,sizeof(value),1,readptr))
    {   
        dummy->value = value;
        dummy->next = NULL;
        Array->next = dummy;
    }

    else 
    {
        free(dummy);
        fclose(readptr);
        return Array;
    }

    // Creating the linked list 
    
    while(fread(&value,sizeof(value),1,readptr))
    {
        Pnode = malloc(sizeof(Node));
        
        if(Pnode == NULL)
        {
            free(Array);
            free(dummy);
            fprintf(stderr,"Malloc Fail\n");
            fclose(readptr);
            return NULL;
        }

        Pnode->value = value;
        Pnode->next = NULL;
        dummy->next = Pnode;
        dummy = dummy->next;
    }
    fclose(readptr);
    return Array;
}

int Save_To_File(char *Filename, Node *list)
{   
    // Opening the write location and variable declaration
    
    FILE *writeptr = fopen(Filename,"wb");
    if(writeptr == NULL)
    {
        fprintf(stderr,"Error Opening File\n");
        return 0;
    }
    Node *write = NULL;
    int NodesWritten = 0;
    long value = 0;

    // Copying into the file
    
    while(list != NULL)
    {
        write = list;
        value = list->value;
        //-----------------------------------------------------------
        // PRTINTS THE SORTED AS THE VALUES ARE BEING COPIED
        // printf("%ld\n",value);
        //-----------------------------------------------------------
        fwrite(&value,sizeof(value),1,writeptr);
        list = list->next;
        free(write);
        NodesWritten++;
    }
    fclose(writeptr);
    return NodesWritten;
}

// Function to calculate Power

int power(int base, int power)
{
	if(power == 0)
	{
		return 1;
	}
	int counter = 0;
	int number = base;
	for(counter = 0; counter < power - 1; counter++)
	{
		number *= base;
	}
	return number;
}

// Function to reverse a linked list

Node *revList(Node* Head)
{
    Node *newHead = Head;
    Node *nextNode = NULL;
    Node *prevNode = NULL; 
    while(newHead != NULL)
    {
        nextNode = newHead->next;
        newHead->next = prevNode;
        prevNode = newHead;
        newHead = nextNode;
    }
    return prevNode;
}

// Function to generate the pratt sequence

Node* GenSeq(int size)
{
    int p = 0;				// Power of 2 in the sequence 
	int q = 0;				// Power of 3 in the sequence 
	int endPower = 0;		// Power of the last row the number is in
	int numberofelements;   // Number of elements to be allocated
	int lastnumber = 0;
	
	// Calculating the last rows maxuimum power
	
	while (power(3,endPower) < size)
	{
		endPower++;
	}
	numberofelements = endPower * (endPower + 1) / 2;
	p = endPower;
	
	// Calculating the last element
	
	while ((power(2,p) * power(3,q)) < size)
	{
		lastnumber = (int)(power(2,p) * power(3,q));
		if(p > 0)
		{
			p--; 			// P cannot fall below 0
		}
		q++;
		numberofelements++;
	}

	//Allocating space for the array sequence
	
    Node *prattHeader = NULL;
    Node *prattTail = NULL;
	Node *prattSeq = NULL;
	// Calculating the sequence
	
	int highestPower = 0;
	int i;					  // Element number in the sequence
	p = 0;

    // Storing the pratt sequence in a list 
	for(i = 0; i < numberofelements; i++)
	{
		if(p == -1)
		{
			highestPower++;
			p = highestPower;
		}

        if(prattHeader == NULL)
        {
            prattHeader = malloc(sizeof(Node));
            prattHeader->value = (long)(power(2,p) * power(3,highestPower - p));
            prattHeader->next = NULL;
            prattTail = prattHeader;
            p--;
        }
        else
        {
            prattSeq = malloc(sizeof(Node));
		    prattSeq->value = (long)(power(2,p) * power(3,highestPower - p));
            prattSeq->next = NULL;
            prattTail->next = prattSeq;
            prattTail = prattTail->next;
		    p--;
        }
	}
    prattHeader = revList(prattHeader);
	return prattHeader;
}

// Calculates the length of the array
int calcSize(Node *list)
{
    int Size = 0;
    Node *curr = list;
    while(curr)
    {
        Size++;
        curr = curr->next;
    }
    return Size;
}

// Performing shell sorting

Node *Shell_Sort(Node *list)
{
    // Variable initialization
    
    int listSize = calcSize(list);
    Node *prattVector = GenSeq(listSize);
    //------------------------------------------------------------
    // PRINTS THE PRATT SEQUENCE (AKA GAP VALUES)
    /*Node *prattCopy = prattVector;
    while(prattCopy != NULL)
    {
        printf("%ld\n",prattCopy->value);
        prattCopy = prattCopy->next;
    }*/
    //------------------------------------------------------------
    Node *temp = NULL;
    Node *psuedo = list;
    Node *outer = list;
    Node *inner = list;
    Node *dummy = NULL;
    Node *innerDummy = NULL;
    int gap = 0;
    int traversalCounter = 0;
    int count = 0;

    // Checks if the list is empty
    
    if(list == NULL)
    {
        fprintf(stderr,"No elements in the given list");
        return NULL;
    }

    // Returns the list of it only has one element
    
    if(list->next == NULL)
    {
        return list;
    }

    // Performs one interation of insertion sorting
    
    while(traversalCounter < listSize - 1)
    {
        psuedo = outer;
        outer = psuedo->next;
        if(inner->value > outer->value)
        {   
            list = outer;
            psuedo->next = outer->next;
            outer->next = inner;
            outer = psuedo;
            inner = list;
        }
        traversalCounter++;
    }

    if(inner->value > outer->value)
    {   
        list = outer;
        psuedo->next = NULL;
        outer->next = inner;
        inner = list;
        psuedo = outer;
    }

    //Performs one interation of bubble sort

    dummy = outer;
    psuedo = list;
    inner = list->next;
    while(inner != dummy)
    {    
        if(outer->value < inner->value)
        {
            outer->next = inner;
            outer = inner;
            psuedo->next = inner->next;
            outer->next = NULL;
            inner = psuedo->next;
        }
        else
        {
            inner = inner->next;
            psuedo = psuedo->next;
        }
    }


    // Performing the shell sort by address manipulation
    
    Node *first = list;
    Node *last = outer;
    inner = list->next;
    outer = inner->next;
    while(prattVector != NULL)
    {
        temp = prattVector;
        gap = temp->value;
        inner = list->next;
        outer = inner->next;
        for(count = 0; count < gap - 1; count++)
        {
            outer = outer->next;
        }
        dummy = outer->next;
        psuedo = list;
        while(dummy != last)
        {
            if(inner->value > dummy->value)
            {
                outer->next = dummy->next;
                dummy->next = inner;
                psuedo->next = dummy;
                psuedo = psuedo->next;
                dummy = outer->next;
            }
            else
            {
                dummy = dummy->next;
                outer = outer->next;
                inner = inner->next;
                psuedo = psuedo->next;
            }
        }
        prattVector = prattVector->next;
        free (temp);
    }

    // Shell Sort when gap is of width 1 
    
    inner = list->next;
    psuedo = list;
    dummy = inner;
    outer = inner->next;
    while(inner->next != last)
    {
        while(outer != NULL)
        {
            if(inner->value >= outer->value)
            {
                while(psuedo != inner)
                {
                    if(psuedo->next->value >= outer->value)
                    {
                        dummy->next = outer->next;
                        outer->next = psuedo->next;
                        psuedo->next = outer;
                        outer = dummy->next;
                        psuedo = list;
                    }
                    psuedo = psuedo->next;
                }
            }
            else
            {
                dummy = dummy->next;
                outer = outer->next;
            }
            psuedo = list;
        }   
        inner = inner->next;
        dummy = inner;
        outer = inner->next;
    }
    return list;
}
