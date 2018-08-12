#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    int color;
    int key;//0代表红色，1代表黑色
    struct NODE *left;
    struct NODE *right;
    struct NODE *p;
};
struct RBTREE
{
    struct NODE *root;
};

void BUILD_TREE(struct RBTREE *rbtree)
{
    rbtree->root = NULL;
}
//左旋
void LEFT_ROTATE(struct RBTREE *T, struct NODE *x)
{
    struct NODE *y = x->right;
    //先把y的左边节点给x的右边节点
    x->right = y->left;
    //改变它的父节点的指针
    if (y->left != NULL)
    {
        y->left->p = x;
    }

    //把y放到x原本的位置
    y->p = x->p;
    if (x->p == NULL)
    {
        T->root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    //调整y的左子节点，和x的父节点
    y->left = x;
    x->p = y;
}
//右旋
void RIGHT_ROTATE(struct RBTREE *T, struct NODE *y)
{
    struct NODE *x = y->left;
    //先把x的右节点给y的左节点
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->p = y;
    }

    //再把x放到y原本的位置
    x->p = y->p;
    if (y->p == NULL)
    {
        T->root = x;
    }
    else if (y == y->p->left)
    {
        y->p->left = x;
    }
    else
    {
        y->p->right = x;
    }
    //再调整x的右子节点和y的父节点
    x->right = y;
    y->p = x;
}
void RB_INSERT_FIXUP(struct RBTREE * T,struct NODE * z){
    
}

void RB_INSERT(struct RBTREE *T, struct NODE *z)
{
    struct NODE * y=NULL;
    struct NODE * x=T->root;
    while(x!=NULL){
        //把传递给y
        y=x;
        //把x的关键值与z的关键字比较
        if(x->key<z->key){
            x=x->left;
        }else {
            x=x->right;
        }
    }
    //把y的指针传递给z的p属性
    z->p=y;
    //把z传递给y的左边或者右边
    if(y==NULL){
        T->root=z;
    }
    else if(y->key>z->key){
        y->left=z;
    }else{
        y->right=z;
    }
    z->left=NULL;
    z->right=NULL;
    z->color=0;//0代表红色
    void RB_INSERT_FIXUP(T,z);
}
int main(int argc, char const *argv[])
{
    printf("hello world!");
    return 0;
}
