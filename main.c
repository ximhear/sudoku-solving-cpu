#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Cell {
    u_int16_t candidate;
};

int backtracking(u_int16_t* orgProblem, struct Cell* orgCells, int index, u_int16_t* result) {

    int next = -1;
    for (int i = index; i < 81; i++) {
        if (orgProblem[i] == 0) {
            next = i;
            break;
        }
    }
    if (next == -1) {
        memcpy(result, orgProblem, sizeof(u_int16_t) * 81);
        return 1;
    }
    struct Cell cells[81];
    u_int16_t problem[81];
    memcpy(cells, orgCells, sizeof(struct Cell) * 81);
    memcpy(problem, orgProblem, sizeof(u_int16_t) * 81);
    for (int shift = 1; shift <= 9; shift++) {
        if (cells[next].candidate &(1 << shift)) {
            problem[next] = shift;
            cells[next].candidate = 0;

            u_int16_t row_filled[9];
            u_int16_t col_filled[9];
            u_int16_t sub_filled[9];
            while(1) {
                for (int i = 0 ; i < 9 ; i++) {
                    row_filled[i] =
                            (1<<problem[i*9+0])|(1<<problem[i*9+1])|(1<<problem[i*9+2])|
                            (1<<problem[i*9+3])|(1<<problem[i*9+4])|(1<<problem[i*9+5])|
                            (1<<problem[i*9+6])|(1<<problem[i*9+7])|(1<<problem[i*9+8]);
                }
                for (int i = 0 ; i < 9 ; i++) {
                    col_filled[i] =
                            (1<<problem[0*9+i])|(1<<problem[1*9+i])|(1<<problem[2*9+i])|
                            (1<<problem[3*9+i])|(1<<problem[4*9+i])|(1<<problem[5*9+i])|
                            (1<<problem[6*9+i])|(1<<problem[7*9+i])|(1<<problem[8*9+i]);
                }
                for (int i = 0 ; i < 9 ; i++) {
                    sub_filled[i] =
                            (1<<problem[(i/3)*27+0*9+(i%3)*3+0])|(1<<problem[(i/3)*27+0*9+(i%3)*3+1])|(1<<problem[(i/3)*27+0*9+(i%3)*3+2])|
                            (1<<problem[(i/3)*27+1*9+(i%3)*3+0])|(1<<problem[(i/3)*27+1*9+(i%3)*3+1])|(1<<problem[(i/3)*27+1*9+(i%3)*3+2])|
                            (1<<problem[(i/3)*27+2*9+(i%3)*3+0])|(1<<problem[(i/3)*27+2*9+(i%3)*3+1])|(1<<problem[(i/3)*27+2*9+(i%3)*3+2]);
                }

                int found = 0;
                for (int i = 0 ; i < 81; i++) {
                    if (problem[i] == 0) {
                        cells[i].candidate = 0x03ff ^ (row_filled[i/9] | col_filled[i%9] | sub_filled[3*(i/27)+(i%9)/3]);
//                        if (cells[i].candidate == 0) {
//                            printf("next: %d, c==0,  return 0\n", next);
//                            return 0;
//                        }
//                        for (int j = 1; j <= 9; j++) {
//                            if (cells[i].candidate == (1<<j)) {
//                                problem[i] = j;
//                                cells[i].value = ((u_int16_t)1) << problem[i];
//                                cells[i].temp = cells[i].value;
//                                found++;
//                                break;
//                            }
//                        }
                    }
                }
                if (found == 0) {
                    break;
                }
            }
            if (backtracking(problem, cells, next + 1, result) == 1) {
                return 1;
            }
            memcpy(cells, orgCells, sizeof(struct Cell) * 81);
            memcpy(problem, orgProblem, sizeof(u_int16_t) * 81);
            if (next == 0) {
//                printf("next 0, candidate: 0x%x\n", cells[next].candidate);
//                printf("next 0, shift: %d\n", shift);
            }
        }
    }
//    printf("next: %d, return 0\n", next);
    return 0;
}

int main() {
    clock_t begin = clock();
    u_int16_t problem[81] = {
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
    struct Cell cells[81];
    for (int i = 0 ; i < 81; i++) {
        if (problem[i] == 0) {
        }
        else {
            cells[i].candidate = 0;
        }
    }
    u_int16_t row_filled[9];
    u_int16_t col_filled[9];
    u_int16_t sub_filled[9];
    while(1) {
        for (int i = 0 ; i < 9 ; i++) {
            row_filled[i] =
                    (1<<problem[i*9+0])|(1<<problem[i*9+1])|(1<<problem[i*9+2])|
                    (1<<problem[i*9+3])|(1<<problem[i*9+4])|(1<<problem[i*9+5])|
                    (1<<problem[i*9+6])|(1<<problem[i*9+7])|(1<<problem[i*9+8]);
        }
        for (int i = 0 ; i < 9 ; i++) {
            col_filled[i] =
                    (1<<problem[0*9+i])|(1<<problem[1*9+i])|(1<<problem[2*9+i])|
                    (1<<problem[3*9+i])|(1<<problem[4*9+i])|(1<<problem[5*9+i])|
                    (1<<problem[6*9+i])|(1<<problem[7*9+i])|(1<<problem[8*9+i]);
        }
        for (int i = 0 ; i < 9 ; i++) {
            sub_filled[i] =
                    (1<<problem[(i/3)*27+0*9+(i%3)*3+0])|(1<<problem[(i/3)*27+0*9+(i%3)*3+1])|(1<<problem[(i/3)*27+0*9+(i%3)*3+2])|
                    (1<<problem[(i/3)*27+1*9+(i%3)*3+0])|(1<<problem[(i/3)*27+1*9+(i%3)*3+1])|(1<<problem[(i/3)*27+1*9+(i%3)*3+2])|
                    (1<<problem[(i/3)*27+2*9+(i%3)*3+0])|(1<<problem[(i/3)*27+2*9+(i%3)*3+1])|(1<<problem[(i/3)*27+2*9+(i%3)*3+2]);
        }

        int found = 0;
        for (int i = 0 ; i < 81; i++) {
            if (problem[i] == 0) {
                cells[i].candidate = 0x03ff ^ (row_filled[i/9] | col_filled[i%9] | sub_filled[3*(i/27)+(i%9)/3]);
                for (int j = 1; j <= 9; j++) {
                    if (cells[i].candidate == (1<<j)) {
                        problem[i] = j;
                        found++;
                        break;
                    }
                }
            }
        }
        if (found == 0) {
           break;
        }
    }
//    for (int i = 0; i < 81; i++) {
//        printf("%d, ", problem[i]);
//        if (i % 9 == 8) {
//            printf("\n");
//        }
//    }

    int solved = 1;
    for (int i = 0; i < 81; i++) {
        if (problem[i] == 0) {
            solved = 0;
            break;
        }
    }
//    printf("solved: %d\n", solved);
    if (solved == 1) {
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("elapsed: %f\n", time_spent);
        return 0;
    }
//    printf("===== backtracking =====\n");

    u_int16_t result[81];
    int success = backtracking(problem, cells, 0, result);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("elapsed: %f\n", time_spent);
    printf("success : %d\n", success);
    if (success == 1) {
        for (int i = 0; i < 81; i++) {
            printf("%d, ", result[i]);
            if (i % 9 == 8) {
                printf("\n");
            }
        }
    }
    return 0;
}
