#include "clist.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct point{
    int x,y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x,int y){
    struct point *a = malloc(sizeof(struct point));
    a->x = x;
    a->y = y;
    add_node(list,&(a->node));
}

void remove_point(struct intrusive_list *list,int x,int y){
    struct intrusive_node *current = list->head.next;
    while (current)
    {
        int offset = offsetof(struct point,node);
        struct point *p = (struct point*)((char *)current - offset);
            if (p->x == x && p->y == y){
            remove_node(list,&(p->node));
            current = current->next;
            free(p);
            continue;
        }
            current = current->next;
    }
}

void show_all_points(struct intrusive_list *list){
    struct intrusive_node *current = list->head.next;
    while (current)
    {
        int offset = offsetof(struct point,node);
        struct point *p = (struct point*)((char *)current - offset);
        printf("%c",'(');
        printf("%d",p->x);
        printf("%c",' ');
        printf("%d",p->y);
        printf("%c",')');
        printf("%c",' ');
        current = current->next;
    }
}

void remove_all_points(struct intrusive_list *list){
    struct intrusive_node *current = list->head.next;
    while (current)
    {
        int offset = offsetof(struct point,node);
        struct point *p = (struct point*)((char *)current - offset);
        remove_node(list,&(p->node));
        current = current->next;
        free(p);
    }
}

int x,y;
char buff[128];

int main(){
    struct intrusive_list my_list;
    init_list(&my_list);
    while (1)
    {
        scanf("%127s",buff);
        if (strcmp(buff , "add") == 0) {
            scanf("%d",&x);
            scanf("%d",&y);
            add_point(&my_list,x,y);
        } else if (strcmp(buff,"rm") == 0) {
            scanf("%d",&x);
            scanf("%d",&y);
            remove_point(&my_list,x,y);
        } else if (strcmp(buff,"print")== 0) {
            show_all_points(&my_list);
            printf("\n");
        } else if (strcmp(buff,"rma") == 0) {
            remove_all_points(&my_list);
        }
        else if (strcmp(buff,"len") == 0) {
            printf("%d",get_length(&my_list));
            printf("\n");
        } else if (strcmp(buff,"exit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }
    remove_all_points(&my_list);
    return 0;
}
