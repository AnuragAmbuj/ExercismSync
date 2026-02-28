#include "linked_list.h"
#include <mm_malloc.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};

struct list *list_create(void) {
    struct list *list = malloc(sizeof(struct list));
    list->first = NULL;
    list->last = NULL;
    return list;
}

void list_destroy(struct list *list) {
    struct list_node *node = list->first;
    while (node != NULL) {
        struct list_node *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}

void list_push(struct list *list, ll_data_t data) {
    struct list_node *node = malloc(sizeof(struct list_node));
    node->data = data;
    node->prev = list->last;
    node->next = NULL;
    if (list->last != NULL) {
        list->last->next = node;
    }
    list->last = node;
    if (list->first == NULL) {
        list->first = node;
    }
}

ll_data_t list_pop(struct list *list) {
    struct list_node *node = list->last;
    if (node == NULL) {
        return 0;
    }
    ll_data_t data = node->data;
    list->last = node->prev;
    if (list->last != NULL) {
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }
    free(node);
    return data;
}

ll_data_t list_shift(struct list *list) {
    struct list_node *node = list->first;
    if (node == NULL) {
        return 0;
    }
    ll_data_t data = node->data;
    list->first = node->next;
    if (list->first != NULL) {
        list->first->prev = NULL;
    } else {
        list->last = NULL;
    }
    free(node);
    return data;
}

void list_unshift(struct list *list, ll_data_t data) {
    struct list_node *node = malloc(sizeof(struct list_node));
    node->data = data;
    node->prev = NULL;
    node->next = list->first;
    if (list->first != NULL) {
        list->first->prev = node;
    }
    list->first = node;
    if (list->last == NULL) {
        list->last = node;
    }
}

size_t list_count(const struct list *list){
    size_t count = 0;
    struct list_node *node = list->first;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void list_delete(struct list *list, ll_data_t data){
    struct list_node *node = list->first;
    while (node != NULL) {
        if (node->data == data) {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            } else {
                list->first = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            } else {
                list->last = node->prev;
            }
            free(node);
            return;
        }
        node = node->next;
    }
}
