//
// Created by Once on 2019/9/1.
//

#include "binomialheap.h"
#include <stdio.h>
#include <stdlib.h>

BinomialHeap *bheap_init(){
    BinomialHeap *heap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
    if(!heap){
        perror("alloc memory for heap error");
        return NULL;
    }
    heap->list = NULL;
    heap->size = 0;
    return heap;
}

int bheap_is_full(BinomialHeap *bheap){
    ANode *node = (ANode*)malloc(sizeof(ANode));
    if(!node)
        return 1;
    free(node);
    return 0;
}

int bheap_is_empty(BinomialHeap *bheap){
    if(bheap == NULL)
        return 1;
    return bheap->size == 0;
}

// 合并两个阶数相同的二项树
static ltnode *merge_tree(ltnode *n1, ltnode *n2){
    if(n1 == NULL || n2 == NULL)
        return NULL;
    if(n1->value->key > n2->value->key){
        ANode *temp = n1->value;
        n1->value = n2->value;
        n2->value = temp;
    }
    ANode *t1 = n1->value, *t2 = n2->value;
    t2->parent = t1;
    t2->sibling = t1->child;
    t1->child = t2;
    t1->degree++;
    return n1;
}

// 初步合并两个堆
static list *union_heap(list *h1, list *h2){
    if(h1 == NULL)
        return h2;
    if(h2 == NULL)
        return h1;
    list *h = list_new();
    if(!h)
        return NULL;
    ltnode *n1 = h1->head, *n2 = h2->head, *t;
    while(!list_is_empty(h1) && !list_is_empty(h2)){
        if(n1->value->degree <= n2->value->degree){
            t = n1->next;
            list_push_back(h, n1->value);
            list_delete(h1, n1->value);
            n1 = t;
        }
        else{
            t = n2->next;
            list_push_back(h, n2->value);
            list_delete(h2, n2->value);
            n2 = t;
        }
    }
    while(!list_is_empty(h1)){
        t = n1->next;
        list_push_back(h, n1->value);
        list_delete(h1, n1->value);
        n1 = t;
    }
    while(!list_is_empty(h2)){
        t = n2->next;
        list_push_back(h, n2->value);
        list_delete(h2, n2->value);
        n2 = t;
    }
    list_clear(h1);
    list_clear(h2);
    return h;
}

// 调整堆以符合二项堆性质
static int just_heap(list *h){
    if(h == NULL)
        return 0;
    if(h->size <= 1)
        return 1;
    ltnode *n1, *n2, *n3;
    if(h->size == 2){
        n1 = list_begin(h);
        n2 = n1->next;
        n3 = list_begin(h);
    }
    else{
        n1 = list_begin(h);
        n2 = n1->next;
        n3 = n2->next;
    }
    do{
        if(n2 == list_begin(h))
            n1 = n1->next;
        else if(n1->value->degree < n2->value->degree){
            n1 = n1->next;
            n2 = n2->next;
            if(n3 != list_begin(h))
                n3 = n3->next;
        }
        else if(n3 != list_begin(h) && n1->value->degree == n2->value->degree &&
                n2->value->degree == n3->value->degree){
            n1 = n1->next;
            n2 = n2->next;
            n3 = n3->next;
        }
        else if(n1->value->degree == n2->value->degree){
            ANode *value = NULL;
            ltnode *t = merge_tree(n1, n2);
            if(t == n2)
                value = n1->value;
            else
                value = n2->value;
            ltnode *temp = n2->next;
            list_delete(h, value);
            n2 = temp;
            if(n3 != list_begin(h))
                n3 = n3->next;
        }
    }
    while(n1 != list_end(h));
    return 1;
}

// 将一个结点和一个二项堆合并
static int merge_with_node(BinomialHeap *bheap, list *h, ANode *node){
    if(bheap == NULL || node == NULL)
        return 0;
    list *heap = list_new();
    if(!heap)
        return 0;
    list_push_back(heap, node);
    h = union_heap(h, heap);
    bheap->list = h;
    bheap->size++;
    return just_heap(h);
}

int bheap_push(BinomialHeap *bheap, int key, Area *value){
    if(bheap == NULL || value == NULL)
        return 0;
    ANode *node = (ANode*)malloc(sizeof(ANode));
    if(!node){
        perror("alloc memory for node error");
        return 0;
    }
    node->key = key;
    node->value.width = value->width;
    node->value.height = value->height;
    node->degree = 0;
    node->parent = node->child = node->sibling = NULL;
    return merge_with_node(bheap, bheap->list, node);
}

ANode *bheap_top(BinomialHeap *bheap){
    if(bheap == NULL || bheap->size == 0)
        return NULL;
    list *lt = bheap->list;
    ltnode *temp = lt->head, *min = lt->head;
    do{
        if(temp->value->key < min->value->key)
            min = temp;
        temp = temp->next;
    }
    while(temp != list_begin(lt));
    return min->value;
}

static list *heap_from_tree(ANode *tree){
    if(tree == NULL)
        return NULL;
    list *h = list_new();
    if(!h)
        return NULL;
    ANode *temp = tree->child, *t;
    while(temp){
        t = temp;
        temp = temp->sibling;
        t->sibling = NULL;
        list_push_front(h, t);
    }
    return h;
}

void bheap_pop(BinomialHeap *bheap){
    if(bheap == NULL || bheap->size == 0)
        return;
    ANode *min = bheap_top(bheap);
    list *new_heap = heap_from_tree(min);
    list_delete(bheap->list, min);
    bheap->list = union_heap(bheap->list, new_heap);
    just_heap(bheap->list);
    bheap->size--;
}

static void traverse_node(ANode *node){
    if(!node)
        return;
    printf("%d ", node->key);
    traverse_node(node->sibling);
    traverse_node(node->child);
}

void bheap_traverse(BinomialHeap *bheap){
    if(bheap == NULL || bheap->size == 0)
        return;
    ltnode *node = bheap->list->head;
    do{
        traverse_node(node->value);
        node = node->next;
        printf("--- ");
    }
    while(node != list_begin(bheap->list));
    printf("\n");
}

static void clear_node(ANode *node){
    if(!node)
        return;
    clear_node(node->child);
    clear_node(node->sibling);
    free(node);
}

int bheap_clear(BinomialHeap *bheap){
    if(bheap == NULL || bheap->size == 0)
        return 0;
    ltnode *node = bheap->list->head;
    do{
        clear_node(node->value);
        node = node->next;
    }
    while(node != list_begin(bheap->list));
    list_clear(bheap->list);
    free(bheap);
    return 1;
}
