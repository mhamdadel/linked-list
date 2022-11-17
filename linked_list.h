#ifndef LINKED_LIST_HEADER_INCLUDED
#define LINKED_LIST_HEADER_INCLUDED
// make double direction linked list
typedef struct Node Node;
struct Node
{
    int index;
    int data;
    Node *prev, *next;
};
typedef struct LinkedList
{
    Node *head;
    Node *tail;
} LinkedList;

void Add(LinkedList * ls, int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    if(ls->head == NULL)
    {
        newNode->index = 0;
        ls->head = ls->tail = newNode;
        ls->head->index = ls->tail->index = 0;
    }
    else
    {
        ls->tail->next = newNode;
        newNode->prev = ls->tail;
        ls->tail = newNode;
        newNode->index = ls->tail->index + 1;
    }
}

void Display(LinkedList * ls)
{
    Node *current = ls->head;
    while (current != NULL)
    {
        printf("%d\t", current->data);
        current = current->next;
    }
}

Node *GetNodeByData(LinkedList * ls, int data)
{
    Node *current = ls->head;
    while (current != NULL)
    {
        if(data == current->data)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void DeleteNode(LinkedList * ls, int data)
{
    Node *node = GetNodeByData(ls, data);
    if(node == NULL)
    {
        return;
    }
    else
    {
        if(node == ls->head)
        {
            if(node == ls->tail)
            {
                ls->head = ls->tail = NULL;
            }
            else
            {
                ls->head = ls->head->next;
                ls->head->prev = NULL;
            }
        }
        else if(node == ls->tail)
        {
            ls->tail = ls->tail->prev;
            ls->tail->next = NULL;
        }
        else
        {
            Node *prev = node->prev;
            Node *next = node->next;
            prev->next = next;
            next->prev = prev;
        }
        free(node);
    }
}
void InsertAfter(LinkedList * ls, int data, int AfterData)
{
    Node *node = GetNodeByData(ls, AfterData);
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    if(node == NULL)
    {
        return;
    }
    else
    {
        if(node == ls->head)
        {
            if(node == ls->tail)
            {
                Add(ls, data);
                node->next->index = node->index + 1;
            }
            else
            {
                Node *prev = node->prev;
                Node *next = node->next;

                node->next = newNode;
                node->next->index = node->index + 1;

                newNode->prev = node;
                newNode->next = next;

                next->prev = newNode;

                newNode->index = node->index+1;

                int isAfterEdit = 0;
                Node *current = newNode;
                while (current != NULL)
                {
                    if(isAfterEdit == 1)
                    {
                        current->index++;
                    }
                    if(newNode->data == current->data)
                    {
                        isAfterEdit = 1;
                    }
                    current = current->next;
                }
            }
        }
        else if(node == ls->tail)
        {
            Add(ls, data);
            node->next->index = node->index + 1;
        }
        else
        {
            Node *prev = node->prev;
            Node *next = node->next;

            node->next = newNode;
            newNode->prev = node;
            newNode->next = next;
            next->prev = newNode;

            node->next->index = node->index + 1;

            int isAfterEdit = 0;
            Node *current = newNode;
            while (current != NULL)
            {
                if(isAfterEdit == 1)
                {
                    current->index++;
                }
                if(newNode->data == current->data)
                {
                    isAfterEdit = 1;
                }
                current = current->next;
            }
        }
    }
}
int GetCount(LinkedList * ls)
{
    //return ls->tail->index+1;
    Node *current = ls->head;
    int counter = 0;
    while (current != NULL)
    {
        current = current->next;
        counter++;
    }
    return counter;
}
int *GetDataByIndex(LinkedList * ls, int index)
{
    Node *current = ls->head;
    /*
    while (current != NULL)
    {
        if(index == current->index)
        {
            return current->data;
        }
        current = current->next;
    }
    */
    if(index + 1 < GetCount(ls))
    {
        for(int i =0; i<GetCount(ls); i++)
        {
            if(index == i)
            {
                return current->data;
            }
            current = current->next;
        }
    }
    else
    {
        return -1;
    }
}


#endif // LINKED_LIST_HEADER_INCLUDED
