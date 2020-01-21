#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cell {
    u_int16_t value;
    u_int16_t temp;
    u_int16_t shiftCount;
    u_int16_t candidate;
};

int backtracking(u_int16_t* orgProblem, struct Cell* orgCells, int index) {

    int next = -1;
    for (int i = index; i < 81; i++) {
        if (orgCells[i].value == 0) {
            next = i;
            break;
        }
    }
    if (next == -1) {
        printf("return 1\n");
        for (int i = 0; i < 81; i++) {
            printf("%d, ", orgProblem[i]);
            if (i % 9 == 8) {
                printf("\n");
            }
        }
        return 1;
    }
    struct Cell cells[81];
    u_int16_t problem[81];
    memcpy(cells, orgCells, sizeof(struct Cell) * 81);
    memcpy(problem, orgProblem, sizeof(u_int16_t) * 81);
    for (int shift = 1; shift <= 9; shift++) {
        if (cells[next].candidate &(1 << shift)) {
            if (next == 0) {
                printf("%d, %d, 0x%x\n", next, shift, cells[next].candidate);
            }
            problem[next] = shift;
            cells[next].value = ((u_int16_t)1) << problem[next];
            cells[next].temp = cells[next].value;
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
                    if (cells[i].value == 0) {
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
            if (backtracking(problem, cells, next + 1) == 1) {
                return 1;
            }
            memcpy(cells, orgCells, sizeof(struct Cell) * 81);
            memcpy(problem, orgProblem, sizeof(u_int16_t) * 81);
            if (next == 0) {
                printf("next 0, candidate: 0x%x\n", cells[next].candidate);
                printf("next 0, shift: %d\n", shift);
            }
        }
    }
    printf("next: %d, return 0\n", next);
    return 0;
}

int main() {
    u_int16_t problem[81] = {
            9, 0, 0,  0, 0, 8,  4, 0, 0,
            0, 0, 5,  9, 0, 3,  0, 0, 6,
            4, 0, 0,  0, 0, 0,  0, 0, 0,

            0, 0, 0,  0, 0, 6,  0, 2, 0,
            0, 0, 0,  0, 1, 9,  0, 0, 7,
            0, 8, 0,  0, 0, 0,  1, 0, 0,

            6, 0, 8,  0, 0, 1,  0, 0, 9,
            0, 0, 3,  0, 0, 0,  0, 0, 0,
            2, 0, 0,  4, 0, 0,  0, 5, 0
    };
    struct Cell cells[81];
    for (int i = 0 ; i < 81; i++) {
        if (problem[i] == 0) {
            cells[i].value = 0;
            cells[i].temp = 0;
            cells[i].shiftCount = 0;
        }
        else {
            cells[i].value = ((u_int16_t)1) << problem[i];
            cells[i].temp = cells[i].value;
            cells[i].shiftCount = 0;
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
            if (cells[i].value == 0) {
                cells[i].candidate = 0x03ff ^ (row_filled[i/9] | col_filled[i%9] | sub_filled[3*(i/27)+(i%9)/3]);
                for (int j = 1; j <= 9; j++) {
                    if (cells[i].candidate == (1<<j)) {
                        problem[i] = j;
                        cells[i].value = ((u_int16_t)1) << problem[i];
                        cells[i].temp = cells[i].value;
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
    for (int i = 0; i < 81; i++) {
        printf("%d, ", problem[i]);
        if (i % 9 == 8) {
            printf("\n");
        }
    }

    int solved = 1;
    for (int i = 0; i < 81; i++) {
        if (problem[i] == 0) {
            solved = 0;
            break;
        }
    }
    printf("solved: %d\n", solved);
    if (solved == 1) {
        return 0;
    }
    printf("===== backtracking =====\n");

    backtracking(problem, cells, 0);
    return 0;
}
