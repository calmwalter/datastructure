#include<stdlib.h>
#include<stdio.h>

struct NODE{
    struct NODE *prev;
    struct NODE *next;
    int x;
};
struct LIST{
    struct NODE *head;
};

void INITIAL_LIST(struct LIST * L){
    L->head=NULL;
}
struct NODE * SEARCH(struct LIST *L,int x){
    struct NODE* node=L->head;
    while(node!=NULL){
        if(node->x==x){
            return node;
        }
        node=node->next;
    }
    return NULL;
}
void INSERT(struct LIST *L,int x){
    if(L->head==NULL){
        L->head=malloc(sizeof(struct NODE));
        L->head->x=x;
        L->head->next=NULL;
        L->head->prev=NULL;
        return;
    }
    struct NODE* node=malloc(sizeof(struct NODE));
    node->x=x;
    node->prev=NULL;
    node->next=L->head;
    L->head->prev=node;
    L->head=node;
}
void DELETE(struct LIST * L,int x){
    if(L->head==NULL)
        return ;
    struct NODE * node=SEARCH(L,x);
    if(node==NULL)
        return ;
    if(node->next==NULL){
        node->prev->next=NULL;
    }else if(node->prev==NULL){
        L->head=node->next;
    }else{
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }
    free(node);
}

void print(struct LIST *L){
    struct NODE* node=L->head;
    while(node!=NULL){
        printf("%d ",node->x);
        node=node->next;
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    struct LIST L;
    INITIAL_LIST(&L);
    for(int i=0;i<10;i++){
        INSERT(&L,i);
    }
    print(&L);
    DELETE(&L,5);
    DELETE(&L,8);
    DELETE(&L,4);
    DELETE(&L,8);
    DELETE(&L,19);
    print(&L);
    return 0;
}
