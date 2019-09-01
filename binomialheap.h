//
// Created by Once on 2019/9/1.
//

#ifndef DATALGORITHM_BINOMIALHEAP_H
#define DATALGORITHM_BINOMIALHEAP_H

#include "list.h"

// 二项堆实现优先队列BinomialHeap

// 数据项
typedef struct area{
    int width;
    int height;
} Area;

// 结点
typedef struct anode{
    int key;
    Area value;
    int degree;
    struct anode *parent, *sibling, *child;
} ANode;

// 二项堆对外ADT
typedef struct binomialheap{
    list *list;
    int size;
} BinomialHeap;

// 二项堆优先队列操作函数声明
extern BinomialHeap *bheap_init();
extern int bheap_is_full(BinomialHeap *bheap);
extern int bheap_is_empty(BinomialHeap *bheap);
extern int bheap_push(BinomialHeap *bheap, int key, Area *value);
extern ANode *bheap_top(BinomialHeap *bheap);
extern void bheap_pop(BinomialHeap *bheap);
extern void bheap_traverse(BinomialHeap *bheap);
extern int bheap_clear(BinomialHeap *bheap);

#endif //DATALGORITHM_BINOMIALHEAP_H
