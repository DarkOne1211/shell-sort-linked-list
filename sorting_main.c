#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main(int argc, char **argv)
{
    clock_t IOStart, IOStop, SortStart, SortStop;
    int NodesCopied = 0;
    IOStart = clock();
    
    Node *head = Load_From_File(argv[1]);
    
    if(head == NULL)
    {
        return EXIT_FAILURE;
    }
    
    SortStart = clock();
    
    Node* sorted = Shell_Sort(head);

    //----------------------------------------------
    // Tests if the array is sorted 
    /*printf("Unsorted Elements:\n");
    Node *SortedCopy = sorted;
    while(SortedCopy->next!= NULL)
    {
        if(SortedCopy->value > SortedCopy->next->value)
        {
            printf("%ld\n",SortedCopy->value);
        }
        SortedCopy = SortedCopy->next;
    }
    printf("----------------------\n");
    */
    //----------------------------------------------

    if(sorted == NULL)
    {
        return EXIT_FAILURE;
    }

    SortStop = clock();
    
    NodesCopied = Save_To_File(argv[2],sorted);
    //--------------------------------------------------
    // TEST IF ALL THE NODES WERE COPIED
    // printf("Nodes Copied: %d\n", NodesCopied);   
    //--------------------------------------------------
    if(NodesCopied = 0)
    {
        return EXIT_FAILURE;
    }

    IOStop = clock();
    printf("I/O Time: %le\n", (float)((IOStop-IOStop)-(SortStop - SortStop))/CLOCKS_PER_SEC);
    printf("Sorting Time: %le\n", (float)(SortStop - SortStart)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}