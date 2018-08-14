#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    int color;
    int key; //0代表红色，1代表黑色
    struct NODE *left;
    struct NODE *right;
    struct NODE *p;
};
struct RBTREE
{
    struct NODE *root;
    struct NODE *NIL;
};

void BUILD_TREE(struct RBTREE *T)
{

    T->NIL = (struct NODE *)malloc(sizeof(struct NODE));
    T->NIL->color = 1;
    T->NIL->left = NULL;
    T->NIL->right = NULL;
    T->NIL->p = NULL;
    T->NIL->key = -1;
    T->root = T->NIL;
}
//左旋
void LEFT_ROTATE(struct RBTREE *T, struct NODE *x)
{

    struct NODE *y = x->right;
    //第一层关系x与z
    //先把y的左边节点给x的右边节点
    x->right = y->left;
    //改变y左的父节点的指针
    if (y->left != T->NIL)
    {
        y->left->p = x;
    }
    //第二层关系y与x父节点
    //把y放到x原本的位置
    //y父为x父
    y->p = x->p;
    //x父子为y
    if (x->p == T->NIL)
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
    //第三层关系y与x
    //调整y的左子节点，和x的父节点
    y->left = x;
    x->p = y;
}
//右旋
void RIGHT_ROTATE(struct RBTREE *T, struct NODE *y)
{
    struct NODE *x = y->left;
    //第一层关系
    //先把x的右节点给y的左节点
    y->left = x->right;
    if (x->right != T->NIL)
    {
        x->right->p = y;
    }
    //第二层关系
    //再把x放到y原本的位置
    x->p = y->p;
    if (y->p == T->NIL)
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
    //第三层关系
    //再调整x的右子节点和y的父节点
    x->right = y;
    y->p = x;
}
void RB_INSERT_FIXUP(struct RBTREE *T, struct NODE *z)
{
    while (z->p->color == 0)
    {
        //如果这个节点在左边
        if (z->p == z->p->p->left)
        {
            struct NODE *y = z->p->p->right;
            //如果父节点的父节点的右孩子是红色的，那么进行以下操作（情况1）
            if (y->color == 0)
            {
                //将父节点和父节点的父节点的有孩子变成黑色，父节点的父节点变成黑色
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                //将z指针指向父节点的父节点
                z = z->p->p;
            }
            //如果父节点的父节点的右孩子是黑色的，那么判断z是其父节点的右孩子还是左孩子，若是右孩子
            else if (z == z->p->right)
            {
                //进行左旋，(情况3)
                z = z->p;
                LEFT_ROTATE(T, z);
            }
            else
            {
                //如果是左孩子，先把z的父节点变成黑色，再把z的父节点的父节点变成红色，再进行右旋，情况3
                z->p->color = 1;
                z->p->p->color = 0;
                RIGHT_ROTATE(T, z->p->p);
            }
        }
        //如果这个节点在右边
        else
        {
            struct NODE *y = z->p->p->left;
            if (y->color == 0)
            {
                z->p->color = 1;
                z->p->p->color = 0;
                y->color = 1;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                RIGHT_ROTATE(T, z);
            }
            z->p->color = 1;
            z->p->p->color = 0;
            LEFT_ROTATE(T, z->p->p);
        }
    }
    T->root->color = 1;
}

void RB_INSERT(struct RBTREE *T, struct NODE *z)
{
    struct NODE *y = T->NIL;
    struct NODE *x = T->root;
    while (x != T->NIL)
    {
        //把传递给y
        y = x;
        //把x的关键值与z的关键字比较
        if (x->key > z->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    //把y的指针传递给z的p属性
    z->p = y;
    //把z传递给y的左边或者右边
    if (y == T->NIL)
    {
        T->root = z;
    }
    else if (y->key > z->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->NIL;
    z->right = T->NIL;
    z->color = 0; //0代表红色
    RB_INSERT_FIXUP(T, z);
}
void TREE_WALK(struct RBTREE *T, struct NODE *node)
{
    if (node == T->NIL)
    {
        return;
    }
    TREE_WALK(T, node->left);
    printf("%d ", node->key);
    TREE_WALK(T, node->right);
}
int main(int argc, char const *argv[])
{
    struct RBTREE T;
    BUILD_TREE(&T);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        struct NODE *n = (struct NODE *)malloc(sizeof(struct NODE));
        n->color = 0;
        n->key = rand() % 100 + 1;
        n->left = T.NIL;
        n->right = T.NIL;
        n->p = T.NIL;
        RB_INSERT(&T, n);
    }
    TREE_WALK(&T, T.root);
    return 0;
}
