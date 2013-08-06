#ifndef UTILS_H_
#define UTILS_H_
#include "consts.h"

void copy_row(int matrix[HEIGHT][WIDTH], int row_index, int row[HEIGHT]);
void copy_column(int matrix[HEIGHT][WIDTH], int column_index, int column[HEIGHT]);
void copy_sub(int matrix[HEIGHT][WIDTH], int sub_x, int sub_y, int sub[SUB_HEIGHT][SUB_WIDTH]);
void copy_matrix(int src[HEIGHT][WIDTH], int dst[HEIGHT][WIDTH]);

int check_line(int* line, int size);
int check_row(int row[WIDTH]);
int check_column(int column[HEIGHT]);
int check_sub(int sub[SUB_HEIGHT][SUB_WIDTH]);

int check_rows(int matrix[HEIGHT][WIDTH]);
int check_columns(int matrix[HEIGHT][WIDTH]);
int check_subs(int matrix[HEIGHT][WIDTH]);

int is_line_legal(int* line, int size);
int is_row_legal(int row[WIDTH]);
int is_column_legal(int column[HEIGHT]);
int is_sub_legal(int sub[SUB_HEIGHT][SUB_WIDTH]);

int are_rows_legal(int matrix[HEIGHT][WIDTH]);
int are_columns_legal(int matrix[HEIGHT][WIDTH]);
int are_subs_legal(int matrix[HEIGHT][WIDTH]);

int is_legal(int matrix[HEIGHT][WIDTH]);
int is_row_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_column_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_sub_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_legal_after_move(int matrix[HEIGHT][WIDTH], int move[3]);

int is_solved(int matrix[HEIGHT][WIDTH]);
int is_row_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_column_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_sub_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]);
int is_solved_after_move(int matrix[HEIGHT][WIDTH], int move[3]);

void make_move(int matrix[HEIGHT][WIDTH], int move[3]);
void clear_move(int matrix[HEIGHT][WIDTH], int move[3]);

void create_mask(int matrix[HEIGHT][WIDTH], int mask[HEIGHT][WIDTH]);

void print_matrix(int matrix[HEIGHT][WIDTH]);
void print_move(int move[3]);

#endif /* UTILS_H_ */
