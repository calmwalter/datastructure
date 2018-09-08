#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct NODE
{
    struct NODE *left;
    struct NODE *right;
    struct NODE *p;
    int v;
    char color;
} node;

typedef struct
{
    node *root;
    node *nil;
} rbtree;

void initial(rbtree *t)
{

    t->nil = (node *)malloc(sizeof(node));
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->p = NULL;
    t->nil->color = 'b';
    t->nil->v = -1;
    t->root = t->nil;
}
void insert(rbtree *t, node *x);
void delete (rbtree *t, node *x);
void insert_fixup(rbtree *t, node *x);
void delete_fixup(rbtree *t, node *x);
void transplant(rbtree *t, node *u, node *v);
void left_rotate(rbtree *t, node *x);
void right_rotate(rbtree *t, node *x);
node *tree_minimun(rbtree *t, node *x);

void left_rotate(rbtree *t, node *x)
{
    node *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == t->nil)
    {
        t->root = y;
    }
    else
    {
        if (x->p->left == x)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }
    }
    y->left = x;
    x->p = y;
}
void right_rotate(rbtree *t, node *x)
{
    node *y = x->left;
    y->p = x->p;
    if (x->p == t->nil)
    {
        t->root = y;
    }
    else
    {
        if (x->p->left == x)
        {
            x->p->left = y;
        }
        else
        {
            x->p->right = y;
        }
    }

    x->left = y->right;
    if (y->right != t->nil)
    {
        y->right->p = x;
    }

    y->right = x;
    x->p = y;
}

void insert(rbtree *t, node *x)
{
    node *y = t->root;
    node *z = t->nil;
    while (y != t->nil)
    {
        z = y;
        if (y->v > x->v)
        {
            y = y->left;
        }
        else
        {
            y = y->right;
        }
    }
    x->p = z;
    if (z == t->nil)
    {
        t->root = x;
    }
    else if (z->v > x->v)
    {
        z->left = x;
    }
    else
    {
        z->right = x;
    }
    x->left = t->nil;
    x->right = t->nil;
    x->color = 'r';
    insert_fixup(t, x);
}

void insert_fixup(rbtree *t, node *x)
{
    while (x->p->color == 'r')
    {
        if (x->p == x->p->p->left)
        {
            node *y = x->p->p->right;
            if (y->color == 'r')
            {
                x->p->p->color = 'r';
                y->color = 'b';
                x->p->color = 'b';
                x = x->p->p;
            }
            else
            {
                if (x == x->p->right)
                {
                    x = x->p;
                    left_rotate(t, x);
                }
                x->p->color = 'b';
                x->p->p->color = 'r';
                right_rotate(t, x->p->p);
            }
        }
        else
        {
            node *y = x->p->p->left;
            if (y->color == 'r')
            {
                y->color = 'b';
                x->p->color = 'b';
                x->p->p->color = 'r';
                x = x->p->p;
            }
            else
            {
                if (x == x->p->left)
                {
                    x = x->p;
                    right_rotate(t, x);
                }
                x->p->color = 'b';
                x->p->p->color = 'r';
                left_rotate(t, x->p->p);
            }
        }
    }
    t->root->color = 'b';
}

void print(rbtree *t, node *x)
{
    if (x == t->nil)
    {
        return;
    }
    print(t, x->left);
    printf("%d ", x->v);
    print(t, x->right);
}
void transplant(rbtree *t, node *u, node *v)
{
    if (u->p == t->nil)
    {
        t->root = v;
        v->p = t->nil;
    }
    else
    {
        v->p = u->p;
        if (u == u->p->left)
        {
            u->p->left = v;
        }
        else
        {
            u->p->right = v;
        }
    }
}
void node_delete(rbtree *t, node *x)
{
    //x要删除的节点，y指向要删除的节点，z指向要删除的节点的右边子节点
    node *y = x;
    node *z = t->nil;
    char y_orign_color = y->color;
    if (x->left == t->nil)
    {
        z = x->right;
        transplant(t, x, z);
    }
    else if (x->right == t->nil)
    {
        z = x->left;
        transplant(t, x, z);
    }
    else
    {
        y = tree_minimun(t, x->right);
        y_orign_color = y->color;
        z = y->right;
        if (y->p == x)
        {
            z->p = y;
        }
        else
        {
            transplant(t, y, y->right);
            y->right = x->right;
            x->right->p = y;
        }
        transplant(t, x, y);
        y->left = x->left;
        x->left->p = y;
        y->color = x->color;
    }

    if (y_orign_color == 'b')
    {
        delete_fixup(t, z);
    }
}
node *tree_minimun(rbtree *t, node *x)
{
    node *y = t->nil;
    while (x != t->nil)
    {
        y = x;
        x = x->left;
    }
    return y;
}
void delete_fixup(rbtree *t, node *x)
{
    while (x != t->root && x->color == 'b')
    {
        if (x == x->p->left)
        {
            node *y = x->p->right;
            if (y->color == 'r')
            {
                y->color = 'b';
                x->p->color = 'r';
                left_rotate(t, x->p);
                y = x->p->right;
            }
            if (y->left->color == 'b' && y->right->color == 'b')
            {
                y->color = 'r';
                x = x->p;
            }
            else
            {
                if (y->right->color == 'b')
                {
                    y->left->color = 'b';
                    y->color = 'r';
                    right_rotate(t, y);
                    y = x->p->right;
                }
                y->color = x->p->color;
                y->p->color = 'b';
                y->right->color = 'b';
                left_rotate(t, x->p);
                x = t->root;
            }
        }
        else
        {
            node *y = x->p->left;
            if (y->color == 'r')
            {
                x->p->color = 'r';
                y->color = 'b';
                right_rotate(t, x->p);
                y = x->p->left;
            }
            if (y->left->color == 'b' && y->right->color == 'b')
            {
                y->color = 'r';
                x = x->p;
            }
            else
            {
                if (y->left->color = 'b')
                {
                    y->right->color = 'b';
                    y->color = 'r';
                    left_rotate(t, y);
                    y = x->p->left;
                }
                y->color = x->p->color;
                x->p->color = 'b';
                y->left->color = 'b';
                right_rotate(t, x->p);
            }
        }
    }
    x->color = 'b';
}
int main()
{
    rbtree t;
    initial(&t);
    /*     srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        node *n = (node *)malloc(sizeof(node));
        n->color = 'r';
        n->v = rand() % 100 + 1;
        n->left = t.nil;
        n->right = t.nil;
        n->p = t.nil;
        insert(&t, n);
    }

    print(&t, t.root);
    printf("\n");
    node *n = (node *)malloc(sizeof(node));
    n->color = 'r';
    n->v = rand() % 100 + 1;
    n->left = t.nil;
    n->right = t.nil;
    n->p = t.nil;
    insert(&t, n);
    print(&t, t.root);
    printf("\n");
    node_delete(&t, n);
    print(&t, t.root);
    printf("\n"); */

    int num[] = {41, 38, 31, 12, 19, 8};
    int ad[] = {5, 3, 4, 2, 1, 0};
    node *n[6];
    for (int i = 0; i < 6; i++)
    {
        n[i] = (node *)malloc(sizeof(node));
        n[i]->color = 'r';
        n[i]->v = num[i];
        n[i]->left = t.nil;
        n[i]->right = t.nil;
        n[i]->p = t.nil;
        insert(&t, n[i]);
    }
    print(&t, t.root);
    printf("\n");

    for (int i = 0; i < 6; i++)
    {
        node_delete(&t, n[ad[i]]);
        print(&t, t.root);
        printf("\n");
    }
    return 0;
}
