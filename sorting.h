// Strcuture data type definition 

typedef struct _Node
{
    long value;
    struct _Node *next;
} Node;

// Function declaration

 Node *Load_From_File(char *Filename);
 int Save_To_File(char *Filename, Node *list);
 Node *Shell_Sort(Node *list);