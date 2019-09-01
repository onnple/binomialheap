//
// Created by Once on 2019/9/1.
//

#ifndef DATALGORITHM_LIST_H
#define DATALGORITHM_LIST_H

// list双向循环链表


typedef struct anode* type_value;

typedef struct ltn{
    type_value value;
    struct ltn *prev;
    struct ltn *next;
} ltnode;

typedef struct lt{
    ltnode *head;
    int size;
} list;

extern list *list_new();
extern int list_is_full(list *list);
extern int list_is_empty(list *list);
extern int list_push_front(list *list, type_value value);
extern type_value list_pop_front(list *list);
extern int list_push_back(list *list, type_value value);
extern int list_push_back_soft(list *list, ltnode *node);
extern type_value list_pop_back(list *list);
extern int list_delete(list *list, type_value value);
extern int list_delete_soft(list *list, ltnode *node);
extern ltnode *list_next(list *list, ltnode *node);
extern ltnode *list_begin(list *list);
extern ltnode *list_end(list *list);
extern void list_traverse(list *list);
extern int list_clear(list *list);

#endif //DATALGORITHM_LIST_H
