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
struct NDOE *TREE_MINIMUM(struct RBTREE *T, struct NODE *x)
{
    struct NODE *y = T->NIL;
    while (x != T->NIL)
    {
        y = x;
        x = x->left;
    }
    return y;
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
            else
            {
                if (z == z->p->right)
                {
                    //进行左旋，(情况3)
                    z = z->p;
                    LEFT_ROTATE(T, z);
                }
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
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    RIGHT_ROTATE(T, z);
                }

                z->p->color = 1;
                z->p->p->color = 0;
                LEFT_ROTATE(T, z->p->p);
            }
        }
    }
    //调整最后的根节点颜色
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
    if (node->color == 0 && (node->left == 0 || node->right == 0))
    {
        printf("error\n");
    }
    TREE_WALK(T, node->left);
    printf("%d ", node->key);
    TREE_WALK(T, node->right);
}
//用v子树代替u子树
void RB_TRANSPLANT(struct RBTREE *T, struct NODE *u, struct NODE *v)
{
    //如果u是根节点，直接让根节点指向v
    if (u->p == T->NIL)
    {
        T->root = v;
    }
    else
    {
        //如果u是其父节点的左子节点，则将v赋值给他
        if (u == u->p->left)
        {
            u->p->left = v;
        }
        //否则
        else
        {
            u->p->right = v;
        }
    }
}
//删除节点后的修复
void RB_DELETE_FIXUP(struct RBTREE *T, struct NODE *x)
{
    //当x指向的不是根节点并且x的颜色为黑色
    while (x != T->root && x->color == 1)
    {
        //如果x是x的父节点的左子节点
        if (x == x->p->left)
        {
            //定义w指向x
            struct NODE *w = x->p->left;
            //若w的颜色为红色
            if (w->color == 0)
            {
                //先将w的颜色变为黑色
                w->color = 1;
                //再将x的父节点的颜色变为红色，此时性质未改变
                w->p->color = 0;
                //进行左旋
                LEFT_ROTATE(T, x->p);
                //让w指向x的父节点的右边节点
                w = x->p->right;
            }
            //如果w的左边节点的颜色为黑色并且w的右边节点的颜色也为黑色
            if (w->left->color == 1 && w->right->color == 1)
            {
                //将w节点变成红色
                w->color = 0;
                //x指向他的父节点
                x = x->p;
            }
            else
            {
                //情况3------------->将其转换为情况四
                //如果w的右节点是黑色的
                if (w->right->color == 1)
                {
                    //w的左边的颜色变为黑色
                    w->left->color = 1;
                    //w的颜色变为红色
                    w->color = 0;
                    //进行右旋（不改变节点的性质）
                    RIGHT_ROTATE(T, w);
                    //将w重新指向x的父节点的右子节点
                    w = x->p->right;
                }
                //情况四
                //w的颜色变为x的父节点的颜色
                w->color = x->p->color;
                //x的父节点的颜色变为黑色
                x->p->color = 1;
                //w的右节点的颜色变为黑色
                w->right->color = 1;
                //进行左旋
                LEFT_ROTATE(T, x->p);
                //x指向根节点
                x = T->root;
            }
        }
        else
        {
            struct NODE *w = x->p->right;
            if (w->color == 0)
            {
                w->color = 1;
                w->p->color = 0;
                RIGHT_ROTATE(T, x->p);
                w = x->p->left;
            }
            if (w->right->color == 1 && w->left->color == 1)
            {
                w->color = 0;
                x = x->p;
            }
            else
            {
                if (w->left->color == 1)
                {
                    w->right->color = 1;
                    w->color = 0;
                    RIGHT_ROTATE(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = 1;
                w->left->color = 1;
                LEFT_ROTATE(T, x->p);
                x = T->root;
            }
        }
    }
    //将x指向的节点的颜色变为黑色
    x->color = 1;
}
void RB_DELETE(struct RBTREE *T, struct NODE *z)
{
    //y指向需要被删除的节点或者用来代替这点删除点的节点
    struct NODE *y = z;
    //x记录可能会被破坏的分支
    struct NODE *x;
    //y原先指向的颜色
    int y_original_color = y->color;
    //若删除点的左子节点为空
    if (z->left == T->NIL)
    {
        //记录x为z的右子树
        x = z->right;
        //用z的右子树直接替换z
        RB_TRANSPLANT(T, z, z->right);
    }
    //若z的右子树为空
    else if (z->right == T->NIL)
    {
        //记录z的左子树
        x = z->left;
        //用z的左子树直接替换z
        RB_TRANSPLANT(T, z, z->left);
    }
    //若z的子节点都不为空
    else
    {
        //让y指向z的后继
        y = TREE_MINIMUM(T, z->right);
        //更新y的原先颜色为新的节点颜色
        y_original_color = y->color;
        //用x记录y的右子树
        x = y->right;
        //如果y的父节点就是z
        if (y->p == z)
        {
            //让x的父节点指向y（这里有疑问我不太懂有什么用，感觉毫无用处）
            x->p = y;
        }
        //如果y的父节点不是z
        else
        {
            //用y的右子树代替y
            RB_TRANSPLANT(T, y, y->right);
            //将y插入到z的位置上，并进行关联
            y->right = z->right;
            y->right->p = y;
        }
        //用y子树代替z子树
        RB_TRANSPLANT(T, z, y);
        //并将z原先的左子树关联到y上
        y->left = z->left;
        y->left->p = y;
        //将z的颜色给y
        y->color = z->color;
    }
    //如果原先的y的颜色为黑色，则性质被破坏，调用修复函数修复函数的性质
    if (y_original_color == 1)
    {
        RB_DELETE_FIXUP(T, x);
    }
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

    struct NODE *n = (struct NODE *)malloc(sizeof(struct NODE));
    n->color = 0;
    n->key = 72;
    n->left = T.NIL;
    n->right = T.NIL;
    n->p = T.NIL;
    RB_INSERT(&T, n);
    TREE_WALK(&T, T.root);
    printf("\n");
    RB_DELETE(&T, n);
    TREE_WALK(&T, T.root);
    return 0;
}
