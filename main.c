#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW(i) (i/9)
#define COL(i) (i%9)
#define SQR(i) (3*(i/27)+(i%9)/3)
int main() {
    clock_t begin = clock();
    int problem[81] = {
//            0,0,0,0,0,0,8,0,9,0,0,0,9,0,0,0,7,3,0,5,0,3,0,6,0,4,0,0,1,8,0,0,4,0,0,0,6,0,0,0,0,0,0,0,8,0,0,0,7,0,0,5,6,0,0,7,0,5,0,3,0,1,0,4,3,0,0,0,9,0,0,0,2,0,1,0,0,0,0,0,0
            0, 0, 0,  0, 0, 2,  0, 0, 3,
            0, 4, 0,  0, 0, 1,  6, 0, 7,
            0, 0, 1,  0, 0, 0,  0, 0, 4,

            0, 8, 0,  1, 0, 0,  0, 0, 0,
            4, 3, 0,  0, 0, 0,  0, 6, 2,
            0, 0, 0,  7, 0, 0,  0, 0, 0,

            0, 0, 0,  0, 0, 0,  0, 0, 0,
            6, 0, 9,  8, 0, 7,  3, 0, 0,
            0, 0, 0,  3, 0, 4,  7, 0, 0
    };
    int knowns[81] = {0};
    unsigned int rows[9] = {0};
    unsigned int cols[9] = {0};
    unsigned int sqrs[9] = {0};
    unsigned int bits[10] = {0};

    for (int i = 1; i < 10; i++) {
        bits[i] = 1 << i;
    }

    for (int i = 0 ; i < 81; i++) {
        if (problem[i] !=0) {
            knowns[i] = 1;
            rows[ROW(i)] |= bits[problem[i]];
            cols[COL(i)] |= bits[problem[i]];
            sqrs[SQR(i)] |= bits[problem[i]];
        }
    }
    int index = 0;
    int value;
    int success;
    while(1) {
       for(; index < 81; index++) {
           if (knowns[index] == 0) {
               break;
           }
       }
       if (index == 81) {
           success = 1;
           break;
       }
       value = problem[index];
       problem[index] = 0;
        rows[ROW(index)] &= ~bits[value];
        cols[COL(index)] &= ~bits[value];
        sqrs[SQR(index)] &= ~bits[value];
        for (value++; value <= 9; value++) {
           if ((rows[ROW(index)]&bits[value])==0 && (cols[COL(index)]&bits[value])==0 && (sqrs[SQR(index)]&bits[value])==0) {
               problem[index] = value;
               rows[ROW(index)] |= bits[value];
               cols[COL(index)] |= bits[value];
               sqrs[SQR(index)] |= bits[value];
               index++;
               break;
           }
       }
       if (value == 10) {
           for(index--; index >= 0; index--) {
               if (knowns[index] == 0) {
                   break;
               }
           }
           if (index == -1) {
               success = 0;
               break;
           }
       }
    }

//    clock_t end = clock();
//    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
//    printf("elapsed: %f\n", time_spent);
//    printf("success : %d\n", success);
//    if (success == 1) {
        for (int i = 0; i < 81; i++) {
            printf("%d, ", problem[i]);
            if (i % 9 == 8) {
                printf("\n");
            }
        }
//    }
    return 0;
}
