//
// Created by Once on 2019/9/1.
//

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list *list_new(){
    list *lt = (list*)malloc(sizeof(list));
    if(!lt){
        perror("alloc mem for list error");
        return NULL;
    }
    lt->size = 0;
    lt->head = NULL;
    return lt;
}

int list_is_full(list *list){
    ltnode *ltn = (ltnode*)malloc(sizeof(ltnode));
    if(!ltn)
        return 1;
    free(ltn);
    return 0;
}

int list_is_empty(list *list){
    if(list == NULL)
        return 0;
    return list->size == 0;
}

static ltnode *ltn_new(type_value value){
    ltnode *ltn = (ltnode*)malloc(sizeof(ltnode));
    if(!ltn){
        perror("alloc mem for ltn error");
        return NULL;
    }
    ltn->value = value;
    ltn->prev = ltn->next = NULL;
    return ltn;
}

int list_push_front(list *list, type_value value){
    if(list == NULL)
        return 0;
    ltnode *node = ltn_new(value);
    if(!node)
        return 0;
    if(list->size == 0){
        node->prev = node->next = node;
        list->head = node;
        list->size++;
        return 1;
    }
    ltnode *prev = list->head->prev;
    prev->next = node;
    node->prev = prev;
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    list->size++;
    return 1;
}

type_value list_pop_front(list *list){
    if(list == NULL || list->size == 0)
        return 0;
    ltnode *head = list->head;
    ltnode *tail = head->prev;
    tail->next = head->next;
    head->next->prev = tail;
    list->head = head->next;
    list->size--;
    type_value value = head->value;
    free(head);
    return value;
}

int list_push_back_soft(list *list, ltnode *node){
    if(list == NULL || node == NULL)
        return 0;
    if(list->size == 0){
        node->prev = node->next = node;
        list->head = node;
        list->size++;
        return 1;
    }
    ltnode *tail = list->head->prev;
    tail->next = node;
    node->prev = tail;
    node->next = list->head;
    list->head->prev = node;
    list->size++;
    return 1;
}

int list_push_back(list *list, type_value value){
    if(list == NULL)
        return 0;
    ltnode *node = ltn_new(value);
    if(!node)
        return 0;
    if(list->size == 0){
        node->prev = node->next = node;
        list->head = node;
        list->size++;
        return 1;
    }
    ltnode *tail = list->head->prev;
    tail->next = node;
    node->prev = tail;
    node->next = list->head;
    list->head->prev = node;
    list->size++;
    return 1;
}

type_value list_pop_back(list *list){
    if(list == NULL || list->size == 0)
        return 0;
    ltnode *head = list->head;
    ltnode *tail = head->prev;
    tail->prev->next = head;
    head->prev = tail->prev;
    list->size--;
    type_value value = tail->value;
    free(tail);
    return value;
}

int list_delete(list *list, type_value value){
    if(list == NULL || list->size == 0)
        return 0;
    ltnode *node = list->head, *next, *prev;
    do{
        next = node->next;
        prev = node->prev;
        if(node->value == value){
            prev->next = next;
            next->prev = prev;
            if(node == list->head)
                list->head = next;
            free(node);
            list->size--;
            if(list->size == 0)
                list->head = NULL;
            return 1;
        }
        node = next;
    }
    while (node != list->head);
    return 1;
}

int list_delete_soft(list *list, ltnode *n){
    if(list == NULL || list->size == 0)
        return 0;
    ltnode *node = list->head;
    do{
        if(node == n){
            node->prev->next = node->next;
            node->next->prev = node->prev;
            list->size--;
            if(list->size == 0)
                list->head = NULL;
            return 1;
        }
        node = node->next;
    }
    while (node != list->head);
    return 1;
}

ltnode *list_next(list *list, ltnode *node){
    if(list == NULL || list->size == 0 || node == NULL)
        return NULL;
    return node->next;
}

ltnode *list_begin(list *list){
    if(list == NULL || list->size == 0)
        return NULL;
    return list->head;
}

ltnode *list_end(list *list){
    if(list == NULL || list->size == 0)
        return NULL;
    return list->head->prev;
}

void list_traverse(list *list){
    if(list == NULL || list->size == 0)
        return;
    ltnode *node = list->head;
    do{
        printf("%d ", (int)node->value);
        node = node->next;
    }
    while (node != list->head);
    printf("\n");
}

int list_clear(list *list){
    if(list == NULL || list->size == 0)
        return 0;
    ltnode *node = list->head;
    while(list->size != 0){
        ltnode *temp = node->next;
        free(node);
        list->size--;
        if(list->size == 0)
            list->head = NULL;
        node = temp;
    }
    return 1;
}
