#include "utils.h"
#include <stdio.h>
#include <string.h>

void copy_row(int matrix[HEIGHT][WIDTH], int row_index, int row[WIDTH]) {
    int i;
    for (i = 0; i < WIDTH; ++i) {
       row[i] = matrix[row_index][i];
    }
}

void copy_column(int matrix[HEIGHT][WIDTH], int column_index, int column[HEIGHT]) {
    int i;
    for (i = 0; i < HEIGHT; ++i) {
       column[i] = matrix[i][column_index];
    }
}

void copy_sub(int matrix[HEIGHT][WIDTH], int sub_x, int sub_y, int sub[SUB_HEIGHT][SUB_WIDTH]) {
    int i, j;
    for (i = 0; i < SUB_HEIGHT; ++i) {
        for (j = 0; j < SUB_WIDTH; ++j) {
            sub[i][j] = matrix[i + sub_y * SUB_HEIGHT][j + sub_x * SUB_WIDTH];
        }
    }
}

void copy_matrix(int src[HEIGHT][WIDTH], int dst[HEIGHT][WIDTH]) {
    int i, j;
    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            dst[i][j] = src[i][j];
        }
    }
}

int check_line(int* line, int size) {
    int sum = 0;
    int i;
    for (i = 0; i < size; ++i) {
        sum += line[i];
    }
    return sum == 45;
}

int check_row(int row[WIDTH]) {
    return check_line(row, WIDTH);
}

int check_column(int column[HEIGHT]) {
    return check_line(column, HEIGHT);
}

int check_sub(int sub[SUB_HEIGHT][SUB_WIDTH]) {
    int sum = 0;
    int i, j;
    for (i = 0; i < SUB_HEIGHT; ++i) {
        for (j = 0; j < SUB_WIDTH; ++j) {
            sum += sub[i][j];
        }
    }
    return sum == 45;
}

int check_rows(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i;
    for (i = 0; i < HEIGHT; ++i) {
        sum += check_row(matrix[i]);
    }
    return sum == HEIGHT;
}

int check_columns(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i;
    for (i = 0; i < WIDTH; ++i) {
        int column[HEIGHT];
        copy_column(matrix, i, column);
        sum += check_column(column);
    }
    return sum == HEIGHT;
}

int check_subs(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i, j;
    for (i = 0; i < HEIGHT / SUB_HEIGHT; ++i) {
        for (j = 0; j < WIDTH / SUB_WIDTH; ++j) {
            int sub[SUB_HEIGHT][SUB_WIDTH];
            copy_sub(matrix, i, j, sub);
            sum += check_sub(sub);
        }
    }
    return sum == SUB_WIDTH * SUB_HEIGHT;
}

int is_line_legal(int* line, int size) {
    int mask[size + 1];
    memset(mask, 0, sizeof mask);
    int i;
    for (i = 0; i < size; ++i) {
        if (line[i] > 0 && line[i] < size + 1 && mask[line[i]] == 0)
            mask[line[i]] = 1;
        else if (line[i] == 0)
            continue;
        else
            return 0;
    }
    return 1;
}

int is_row_legal(int row[WIDTH]) {
    return is_line_legal(row, WIDTH);
}

int is_column_legal(int column[HEIGHT]) {
    return is_line_legal(column, HEIGHT);
}

int is_sub_legal(int sub[SUB_HEIGHT][SUB_WIDTH]) {
    int size = SUB_HEIGHT * SUB_WIDTH;
    int mask[size + 1];
    memset(mask, 0, sizeof mask);
    int i, j;
    for (i = 0; i < SUB_HEIGHT; ++i) {
        for (j = 0; j < SUB_WIDTH; ++j) {
            if (sub[i][j] > 0 && sub[i][j] < size + 1 && mask[sub[i][j]] == 0)
                mask[sub[i][j]] = 1;
            else if (sub[i][j] == 0)
                continue;
            else
                return 0;
        }
    }
    return 1;
}

int are_rows_legal(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i;
    for (i = 0; i < HEIGHT; ++i) {
        int row[WIDTH];
        copy_row(matrix, i, row);
        sum += is_row_legal(row);
    }
    return sum == HEIGHT;
}

int are_columns_legal(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i;
    for (i = 0; i < WIDTH; ++i) {
        int column[HEIGHT];
        copy_column(matrix, i, column);
        sum += is_column_legal(column);
    }
    return sum == WIDTH;
}

int are_subs_legal(int matrix[HEIGHT][WIDTH]) {
    int sum = 0;
    int i, j;
    for (i = 0; i < HEIGHT / SUB_HEIGHT; ++i) {
        for (j = 0; j < WIDTH / SUB_WIDTH; ++j) {
            int sub[SUB_HEIGHT][SUB_WIDTH];
            copy_sub(matrix, i, j, sub);
            sum += is_sub_legal(sub);
        }
    }
    return sum == SUB_WIDTH * SUB_HEIGHT;
}

int is_legal(int matrix[HEIGHT][WIDTH]) {
    return are_rows_legal(matrix) && are_columns_legal(matrix) && are_subs_legal(matrix);
}

int is_row_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int row[WIDTH];
    copy_row(matrix, move[0], row);
    row[move[1]] = move[2];
    return is_row_legal(row);
}

int is_column_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int column[WIDTH];
    copy_column(matrix, move[1], column);
    column[move[0]] = move[2];
    return is_column_legal(column);
}

int is_sub_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int sub_x = move[0] / SUB_WIDTH;
    int sub_y = move[1] / SUB_HEIGHT;
    int sub[SUB_HEIGHT][SUB_WIDTH];
    copy_sub(matrix, sub_x, sub_y, sub);
    return is_sub_legal(sub);
}

int is_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int matrix_after_move[HEIGHT][WIDTH] = { { 0 } };
    copy_matrix(matrix, matrix_after_move);
    matrix_after_move[move[0]][move[1]] = move[2];
    return is_legal(matrix_after_move);
}

int is_solved(int matrix[HEIGHT][WIDTH]) {
    return check_rows(matrix) && check_columns(matrix) && check_subs(matrix);
}

int is_row_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int row[WIDTH];
    copy_row(matrix, move[0], row);
    row[move[1]] = move[2];
    return check_row(row);
}

int is_column_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int column[WIDTH];
    copy_column(matrix, move[1], column);
    column[move[0]] = move[2];
    return check_column(column);
}

int is_sub_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int sub_x = move[0] / SUB_WIDTH;
    int sub_y = move[1] / SUB_HEIGHT;
    int sub[SUB_HEIGHT][SUB_WIDTH];
    copy_sub(matrix, sub_x, sub_y, sub);
    return check_sub(sub);
}

int is_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    int matrix_after_move[HEIGHT][WIDTH] = { { 0 } };
    copy_matrix(matrix, matrix_after_move);
    matrix_after_move[move[0]][move[1]] = move[2];
    return is_solved(matrix_after_move);
}

void make_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    matrix[move[0]][move[1]] = move[2];
}

void clear_move(int matrix[HEIGHT][WIDTH], int move[3]) {
    matrix[move[0]][move[1]] = 0;
}

void create_mask(int matrix[HEIGHT][WIDTH], int mask[HEIGHT][WIDTH]) {
    int i, j;
    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            if (matrix[i][j] == 0)
                mask[i][j] = 0;
            else
                mask[i][j] = 1;
        }
    }
}

void print_matrix(int matrix[HEIGHT][WIDTH]) {
    int i, j;
    for (i = 0; i < HEIGHT; ++i) {
        for (j = 0; j < WIDTH; ++j) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_move(int move[3]) {
    printf("%d, %d: %d\n", move[0], move[1], move[2]);
}
