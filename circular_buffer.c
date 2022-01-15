#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"
/*struct circular_buffer_t {
    int *ptr;
    int begin;
    int end;
    int capacity;
    unsigned char full: 1;
};*/
int circular_buffer_create(struct circular_buffer_t *a, int N){
    if (a == NULL || N <= 0)
        return 1;
    a->ptr = malloc(sizeof(int) * N);
    if (a->ptr == NULL)
        return 2;
    a->end = 0;
    a->begin = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if (cb == NULL || N <= 0)
        return 1;
    *cb = malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL)
        return 2;
    if (circular_buffer_create(*cb, N) == 2) {
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a){
    if (a != NULL && a->ptr != NULL)
        free(a->ptr);
}
void circular_buffer_destroy_struct(struct circular_buffer_t **a){
    if (a == NULL)
        return;
    circular_buffer_destroy(*a);
    free(*a);
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if (cb == NULL || cb->ptr == NULL || cb->capacity <= 0 || cb->end < 0 || cb->begin < 0
    || cb->end > cb->capacity || cb->begin > cb->capacity)
        return 1;

    *(cb->ptr + (cb->end)) = value;
    cb->end++;
                            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (cb->end == cb->capacity)//  NIE ZMIENIAC BEGINA NIGDZIE W FUNKCJI
        cb->end = 0;                   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    if (cb->end == cb->begin) {
        cb->full = 1;
    }
    if (cb->full == 1)
        cb->begin = cb->end;
    return 0;
}
int circular_buffer_empty(const struct circular_buffer_t *a){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0
        || a->end > a->capacity || a->begin > a->capacity || a->capacity <= 0 )
        return -1;//if head is equal to tail -> the buffer is empty
    if (a->begin == a->end && a->full == 0)
        return 1;
    return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0
        || a->end > a->capacity || a->begin > a->capacity || a->capacity <= 0 )
        return -1;

    if (a->end == a->begin && a->full == 1)
        return 1;

    //if (head + 1) is equal to tail -> the buffer is full
    /*if (a->full == 0)
        return 0;
    if (a->begin + 1 == a->end || a->full == 1)
        return 1;*/
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0
    || a->end > a->capacity || a->begin > a->capacity || a->capacity <= 0 ) {
        if (err_code != NULL)
            *err_code = 1;
        return 1;
    }
    if (circular_buffer_empty(a) == 1){
        if (err_code != NULL)
            *err_code = 2;
        return 2;
    }
    if (err_code != NULL)
        *err_code = 0;
    a->begin++;
    if (a->begin == a->capacity)
        a->begin = 0;
    a->full = 0;
    if (a->begin == 0)
        return *(a->ptr + a->capacity -1);
    return *(a->ptr + a->begin - 1);
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0
        || a->end > a->capacity || a->begin > a->capacity || a->capacity <= 0 ) {
        if (err_code != NULL)
            *err_code = 1;
        return 1;
    }
    if (circular_buffer_empty(a) == 1){
        if (err_code != NULL)
            *err_code = 2;
        return 2;
    }
    if (err_code != NULL)
        *err_code = 0;
    //*(a->ptr + a->end) = 0;
    a->end--;
    if (a->end < 0)
        a->end = a->capacity -1;
    a->full = 0;
    //if (a->begin == a->end)
        //return 0;
    return *(a->ptr + a->end);
}


void circular_buffer_display(const struct circular_buffer_t *a){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0
        || a->end > a->capacity || a->begin > a->capacity || a->capacity <= 0 ||
        circular_buffer_empty(a) == 1)
        return;
    int begin = a->begin;
    do{
        if (a->begin == a->end && a->full == 0) {
            printf("\n");
            return;
        }
        printf("%d ", *(a->ptr + begin));
        begin++;
        if (begin == a->capacity)
            begin = 0;
    }while (begin != a->end);
    printf("\n");
}