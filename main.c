#include <stdio.h>
#include "circular_buffer.h"
int main() {
    struct circular_buffer_t *buff = NULL;
    int buff_size;
    int result;
    printf("Input buffer size\n");
    if (scanf("%d", &buff_size) != 1){
        printf("Incorrect input\n");
        return 1;
    }

    if (buff_size <= 0){
        printf("Incorrect input data\n");
        return 2;
    }
    result = circular_buffer_create_struct(&buff, buff_size);

    if (result == 2){
        printf("Failed to allocate memory\n");
        return 8;
    }
    short int choice;
    int err_code;
    while (1){
        printf("Choose action\n0.End program\n1.Add element\n2.Read last element\n3.Read first element\n4.display buffer\n5.Check if buffer is empty ( return values: 1 - is empty, 0 - is not empty )\n6.Check if buffer is full ( return values: 1 - is full, 0 - is not full )\n\n");
        if(scanf("%hd", &choice) != 1){
            circular_buffer_destroy_struct(&buff);
            printf("Incorrect input\n");
            return 1;
        }else if (choice < 0 || choice > 6){
            printf("Incorrect input data\n");
            continue;
        }

        switch (choice) {
            case 0:{
                goto end;
            }
            case 1:{
                printf("Input number: ");
                int number;
                if(scanf("%d", &number) != 1){
                    circular_buffer_destroy_struct(&buff);
                    printf("Incorrect input");
                    return 1;
                } else {
                    result = circular_buffer_push_back(buff, number);
                    if (result == 1){
                        circular_buffer_destroy_struct(&buff);
                        printf("Incorrect input data");
                        return 2;
                    }
                }
                break;
            }
            case 2:{
                if (circular_buffer_empty(buff) == 1){
                    printf("Buffer is empty\n");
                    break;
                }
                printf("%d\n",circular_buffer_pop_back(buff, &err_code));
                break;
            }
            case 3:{
                result = circular_buffer_empty(buff);
                if (result == 1){
                    printf("Buffer is empty\n");
                    break;
                }
                else if (result == -1){
                    printf("Incorrect data input\n");
                    circular_buffer_destroy_struct(&buff);
                    break;
                }
                printf("%d\n", circular_buffer_pop_front(buff, &err_code));
                break;
            }
            case 4:{
                if (circular_buffer_empty(buff) == 1){
                    printf("Buffer is empty\n");
                    break;
                }
                circular_buffer_display(buff);
                break;
            }
            case 5:{
                if (circular_buffer_empty(buff) == 1){
                    printf("1\n");
                    break;
                } else
                    printf("0\n");
                break;
            }
            case 6:{
                if (circular_buffer_full(buff) == 1){
                    printf("1\n");
                    break;
                } else
                    printf("0\n");
                break;
            }
            default:{
                printf("Incorrect input data");
                break;
            }
        }
    }
    end:
    circular_buffer_destroy_struct(&buff);
    return 0;
}
