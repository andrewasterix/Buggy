#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define DESC_SIZE 8

typedef struct node_t *pNode;
typedef struct node_t {
    char* desc;
    pNode prev;
    pNode next;
} Node;


typedef struct queue_t *pQueue;
typedef struct queue_t {
    pNode first;
    pNode last;
} Queue;


void print_queue(pQueue p)
{
    int i = 0;
    
    printf("v~~top\n");
    pNode tmp = p->first;
   
    while (NULL != tmp) { // TOP->END
        printf("%d: %s\n", i++, tmp->desc);
        tmp = tmp->next;
    }

    printf("---bottom\n");
    
    i = 0;
    tmp = p->last;
    
    while (NULL!= tmp) { // END->TOP
        printf("%d: %s\n", i++, tmp->desc);
        tmp = tmp->prev;
    }
    printf("^~~top\n\n");
}


void insert_bottom(pQueue p, pNode n)
{
  
    if (p->first == NULL) { // HEAD
        p->first = n;
        p->last = n;
        return;
    }else{  // NOT HEAD
        n->prev = p->last;
        p->last->next = n;
        p->last = n;
        n->next = NULL;
    }
}


pNode search_node_by_desc(pQueue p, char* desc)
{
    pNode tmp = (pNode)malloc(sizeof(pNode));
    tmp->desc = (char*)malloc(sizeof(char));
    tmp = p->first;
    
    while (tmp!=NULL) {
        if (strcmp(desc, tmp->desc) == 0) {
            return tmp;
        }
        
        tmp = tmp->next;
    }

  return NULL;
}


void delete_node(pQueue p, char* desc)
{
    pNode del = search_node_by_desc(p, desc);
    
    if (del == NULL)
            return;

    if (del == p->first) 
        p->first = del->next;

    if (del == p->last)
        p->last = del->prev;

    if (del->next!=NULL)
        del->next->prev = del->prev;

    if (p->first!= p->last){
        p->first->prev = NULL;
        p->last->next = NULL;
    }

    free(del->desc);
    free(del);

}


pNode create_node(char* desc)
{
    pNode new_node = (pNode)malloc(sizeof(Node));
    new_node->desc = (char*)malloc(sizeof(char)*DESC_SIZE);
    
    strcpy(new_node->desc, desc);
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}


int main()
{
    pQueue queue = (pQueue)malloc(sizeof(pQueue));
    
    insert_bottom(queue, create_node("a1"));
    insert_bottom(queue, create_node("b2"));
    insert_bottom(queue, create_node("c3"));
    insert_bottom(queue, create_node("d4"));
    insert_bottom(queue, create_node("e5"));
    
    print_queue(queue);

    delete_node(queue, "e5");
    delete_node(queue, "a1");
    print_queue(queue);

    delete_node(queue, "b2");
    delete_node(queue, "c3");
    print_queue(queue);

    delete_node(queue, "d4");
    print_queue(queue);
    free(queue);

    return 0;   
}