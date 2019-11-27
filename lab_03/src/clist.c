#include "clist.h"
#include <stdlib.h>

void init_list(struct intrusive_list *list){
    list->head.prev = NULL;
    list->head.next = NULL;
}

void add_node(struct intrusive_list *list,struct intrusive_node *new_node){
    if (list->head.next == NULL) {
        new_node->prev = &(list->head);
        new_node->next = NULL;
        list->head.next = new_node;
    } else {
    new_node->next = list->head.next;
    list->head.next->prev = new_node;
    new_node->prev = &(list->head);
    list->head.next = new_node;
    }
}

void remove_node(struct intrusive_list *list,struct intrusive_node *del_node){
    if (del_node->next != NULL && del_node->prev != &(list->head)) { 
        del_node->next->prev = del_node->prev;
        del_node->prev->next = del_node->next;
    }
    else if (del_node->next == NULL && del_node->prev != &(list->head)){
        del_node->prev->next = NULL;
    }
    else if (del_node->next != NULL && del_node->prev == &(list->head)){
        del_node->next->prev = &(list->head);
        list->head.next = del_node->next;
    }
    else {
        list->head.next = NULL;
    }
}

int get_length(struct intrusive_list *head) {
    int counter = 0;
    for (struct intrusive_node *cur = head->head.next;cur != NULL;cur = cur->next){
        counter++;
    }
    return counter;
}