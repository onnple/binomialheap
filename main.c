#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "binomialheap.h"

static void list_(void){
    list *lt = list_new();
    for (int i = 0; i < 20; ++i) {
        list_push_back(lt, i);
        list_push_front(lt, i*i + 4);
    }
    list_traverse(lt);

    list_delete(lt, 125);
    list_delete(lt, 200);
    list_traverse(lt);

    printf("%d\n", list_next(lt, lt->head)->value);

    for (int i = 0; i < 19; ++i){
        type_value v2 = list_pop_front(lt);
        printf("%d ", v2);
        type_value v1 = list_pop_back(lt);
        printf("%d ", v1);
    }
    printf("\n");
    list_clear(lt);
}

static void binomial_heap(void){
    BinomialHeap *heap = bheap_init();
    Area a;
    a.width = 10;
    a.height = 1010;

    bheap_push(heap, 7, &a);
    bheap_push(heap, 15, &a);
    bheap_push(heap, 52, &a);
    bheap_push(heap, 30, &a);
    bheap_push(heap, 26, &a);
    bheap_push(heap, 12, &a);
    bheap_push(heap, 3, &a);
    bheap_push(heap, 11, &a);
    bheap_push(heap, 9, &a);
    bheap_push(heap, 5, &a);
    bheap_push(heap, 6, &a);
    bheap_push(heap, 23, &a);
    bheap_push(heap, 17, &a);
    bheap_push(heap, 10, &a);
    bheap_push(heap, 94, &a);
    bheap_push(heap, 63, &a);
    bheap_push(heap, 72, &a);
    bheap_push(heap, 57, &a);

    bheap_traverse(heap);

    while(!bheap_is_empty(heap)){
        ANode *node = bheap_top(heap);
        printf("%d ", node->key);
        bheap_pop(heap);
    }
    printf("\n");

    bheap_clear(heap);
}

int main(void) {
    binomial_heap();
    return 0;
}
