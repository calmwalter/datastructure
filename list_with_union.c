#include<stdio.h>
#include<stdlib.h>
struct NODE{
    struct NODE *next;
    int x;
};
struct LIST{
    struct NODE *head;
};

void INITIALIZE_LIST(struct LIST *L){
    L->head=NULL;
}
struct NODE* SEARCH(struct LIST *L,int x){
    struct NODE *node=L->head;
    while(node!=NULL){
        if(node->x==x)
            return node;
        node=node->next;
    }
    return NULL;
}
void INSERT(struct LIST *L,int x){
    
    if(L->head==NULL){
        L->head=malloc(sizeof(struct NODE));
        L->head->x=x;
        L->head->next=NULL;
        return;
    }
    
    struct NODE *temp=malloc(sizeof(struct NODE));
    temp->x=x;
    temp->next=L->head;
    L->head=temp;
}
void print(struct LIST *L){
    struct NODE* node=L->head;
    while(node!=NULL){
        printf("%d ",node->x);
        node=node->next;
    }
    printf("\n");
}
void DELETE(struct LIST *L,int x){
    if(L->head==NULL){return ;}
    if(L->head->x==x){
        L->head=L->head->next;
        return ;
    }
    struct NODE *node=L->head;
    while(node->next!=NULL){
        if(node->next->x==x)
            break;
        node=node->next;
    }
    if(node->next!=NULL){
        struct NODE *temp=node->next;
        node->next=node->next->next;
        free(temp);
    }
}

void UNION(struct LIST *L1,struct LIST *L2){
    if(L1->head==NULL){
        L1->head=L2->head;
        return ;
    }
    struct NODE* node=L1->head;

    while(node->next!=NULL){
        node=node->next;
    }
    node->next=L2->head;
}
int main(){
    struct LIST L,L2;
    INITIALIZE_LIST(&L);
    for(int i=0;i<10;i++){
        INSERT(&L,i);
    }
    INITIALIZE_LIST(&L2);
    for(int i=100;i<120;i++){
        INSERT(&L2,i);
    }
    print(&L);
    DELETE(&L,5);
    DELETE(&L,8);
    DELETE(&L,4);
    DELETE(&L,8);
    DELETE(&L,19);
    print(&L);
    UNION(&L,&L2);
    print(&L);

    return 0;
}
