#include "tests.h"
#include "utils.h"
#include "solver.h"
#include <stdio.h>
#include <string.h>

void test(char* result);
void test_row(int row[WIDTH], int expected_value);
void test_column(int column[HEIGHT], int expected_value);
void test_sub(int sub[SUB_HEIGHT][SUB_WIDTH], int expected_value);
void test_rows(int matrix[HEIGHT][WIDTH], int expected_value);
void test_columns(int matrix[HEIGHT][WIDTH], int expected_value);
void test_subs(int matrix[HEIGHT][WIDTH], int expected_value);
void test_whole(int matrix[HEIGHT][WIDTH], int expected_value);
void test_row_legality(int row[WIDTH], int expected_value);
void test_column_legality(int column[HEIGHT], int expected_value);
void test_sub_legality(int sub[SUB_HEIGHT][SUB_WIDTH], int expected_value);
void test_legality(int matrix[HEIGHT][WIDTH], int expected_value);
void test_legality_after_move(int matrix[HEIGHT][WIDTH], int move[3], int expected_value);
void print_test_results(void);

int test_index = 0;
int failed = 0;

void test(char* result) {
    test_index++;
    printf("Test %d: %s\n", test_index, result);
    if (strcmp(result, "Fail") == 0)
        failed++;
}

void test_row(int row[WIDTH], int expected_value) {
    test( check_row(row) == expected_value ? "Pass" : "Fail" );
}

void test_column(int column[HEIGHT], int expected_value) {
    test( check_column(column) == expected_value ? "Pass" : "Fail" );
}

void test_sub(int sub[SUB_HEIGHT][SUB_WIDTH], int expected_value) {
    test( check_sub(sub) == expected_value ? "Pass" : "Fail" );
}

void test_rows(int matrix[HEIGHT][WIDTH], int expected_value) {
    test( check_rows(matrix) == expected_value ? "Pass" : "Fail" );
}

void test_columns(int matrix[HEIGHT][WIDTH], int expected_value) {
    test( check_columns(matrix) == expected_value ? "Pass" : "Fail" );
}

void test_subs(int matrix[HEIGHT][WIDTH], int expected_value) {
    test( check_subs(matrix) == expected_value ? "Pass" : "Fail" );
}

void test_whole(int matrix[HEIGHT][WIDTH], int expected_value) {
    test( is_solved(matrix) == expected_value ? "Pass" : "Fail" );
}

void test_row_legality(int row[WIDTH], int expected_value) {
    test ( is_row_legal(row) == expected_value ? "Pass" : "Fail" );
}

void test_column_legality(int column[HEIGHT], int expected_value) {
    test ( is_column_legal(column) == expected_value ? "Pass" : "Fail" );
}

void test_sub_legality(int sub[SUB_HEIGHT][SUB_WIDTH], int expected_value) {
    test ( is_sub_legal(sub) == expected_value ? "Pass" : "Fail" );
}

void test_legality(int matrix[HEIGHT][WIDTH], int expected_value) {
    test ( is_legal(matrix) == expected_value ? "Pass" : "Fail" );
}

void test_legality_after_move(int matrix[HEIGHT][WIDTH], int move[3], int expected_value) {
    test ( is_legal_after_move(matrix, move) == expected_value ? "Pass" : "Fail" );
}

void print_test_results(void) {
    if (failed > 1)
        printf("%d tests failed!\n", failed);
    else if (failed == 1) {
        printf("%d test failed!\n", failed);
    }
    else
        printf("All tests passed!\n");
}

void run_tests(void) {
    int unsolved[HEIGHT][WIDTH] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                                    { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                                    { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                                    { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                                    { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                                    { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                                    { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                                    { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                                    { 0, 0, 0, 0, 8, 0, 0, 7, 9 } };

    int illegal[HEIGHT][WIDTH] = { { 5, 3, 5, 2, 7, 6, 7, 8, 9 },
                                   { 6, 1, 0, 1, 9, 5, 0, 0, 0 },
                                   { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                                   { 8, 2, 2, 0, 6, 0, 0, 0, 3 },
                                   { 4, 4, 0, 8, 0, 3, 6, 0, 1 },
                                   { 7, 0, 5, 0, 2, 0, 0, 0, 6 },
                                   { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                                   { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                                   { 4, 0, 0, 0, 8, 0, 0, 7, 9 } };

    int solved[HEIGHT][WIDTH] = { { 5, 3, 4, 6, 7, 8, 9, 1, 2 },
                                  { 6, 7, 2, 1, 9, 5, 3, 4, 8 },
                                  { 1, 9, 8, 3, 4, 2, 5, 6, 7 },
                                  { 8, 5, 9, 7, 6, 1, 4, 2, 3 },
                                  { 4, 2, 6, 8, 5, 3, 7, 9, 1 },
                                  { 7, 1, 3, 9, 2, 4, 8, 5, 6 },
                                  { 9, 6, 1, 5, 3, 7, 2, 8, 4 },
                                  { 2, 8, 7, 4, 1, 9, 6, 3, 5 },
                                  { 3, 4, 5, 2, 8, 6, 1, 7, 9 } };

    int row[WIDTH];
    int column[HEIGHT];
    int sub[SUB_HEIGHT][SUB_WIDTH];

    puts("Unsolved tests");
    test_rows(unsolved, 0);
    test_columns(unsolved, 0);
    test_subs(unsolved, 0);
    test_whole(unsolved, 0);

    copy_row(unsolved, 0, row);
    test_row_legality(row, 1);

    copy_column(unsolved, 0, column);
    test_column_legality(column, 1);

    copy_sub(unsolved, 0, 0, sub);
    test_sub_legality(sub, 1);

    test_legality(unsolved, 1);

    int illegal_move[3] = {0, 2, 5};
    test_legality_after_move(unsolved, illegal_move, 0);

    int legal_move[3] = {0, 2, 4};
    test_legality_after_move(unsolved, legal_move, 1);

    puts("Illegal tests");
    test_rows(illegal, 0);
    test_columns(illegal, 0);
    test_subs(illegal, 0);
    test_whole(illegal, 0);

    copy_row(illegal, 0, row);
    test_row_legality(row, 0);

    copy_column(illegal, 0, column);
    test_column_legality(column, 0);

    copy_sub(illegal, 0, 0, sub);
    test_sub_legality(sub, 0);

    test_legality(illegal, 0);

    puts("Presolved tests");
    test_rows(solved, 1);
    test_columns(solved, 1);
    test_subs(solved, 1);
    test_whole(solved, 1);

    solve(unsolved);

    puts("Solved tests");
    test_rows(unsolved, 1);
    test_columns(unsolved, 1);
    test_subs(unsolved, 1);
    test_whole(unsolved, 1);

    print_test_results();
}
