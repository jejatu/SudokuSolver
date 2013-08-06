#include "solver.h"
#include "utils.h"

void increment_move(int move[3]);
void copy_next_move(int mask[HEIGHT][WIDTH], int move[3], int next_move[3]);
void copy_first_move(int mask[HEIGHT][WIDTH], int first_move[3]);
int move_tried(int move[3], int move_mask[HEIGHT]);
void set_move_as_tried(int move[3], int move_mask[HEIGHT]);
int is_last_move(int move[3]);

void increment_move(int move[3]) {
    move[0]++;
    if (move[0] >= HEIGHT) {
        move[0] = 0;
        move[1]++;
    }
}

void copy_next_move(int mask[HEIGHT][WIDTH], int move[3], int next_move[3]) {
    next_move[0] = move[0];
    next_move[1] = move[1];
    next_move[2] = 1;
    increment_move(next_move);
    while (mask[next_move[0]][next_move[1]] == 1 && next_move[0] < HEIGHT && next_move[1] < WIDTH) {
        increment_move(next_move);
    }
}

void copy_first_move(int mask[HEIGHT][WIDTH], int first_move[3]) {
    first_move[0] = 0;
    first_move[1] = 0;
    first_move[2] = 1;
    if (mask[first_move[0]][first_move[1]] == 1)
        copy_next_move(mask, first_move, first_move);
}

int move_tried(int move[3], int move_mask[HEIGHT]) {
    return move_mask[move[2] - 1] == 1;
}

void set_move_as_tried(int move[3], int move_mask[HEIGHT]) {
    move_mask[move[2] - 1] = 1;
}

int is_last_move(int move[3]) {
    return move[1] >= WIDTH;
}

int recursive_solve(int unsolved[HEIGHT][WIDTH], int mask[HEIGHT][WIDTH], int move[3]) {
    int move_mask[HEIGHT] = { 0 };
    int solved = 0;
    while (!solved) {
        while (move_tried(move, move_mask) || !is_legal_after_move(unsolved, move)) {
            move[2]++;
            if (move[2] > HEIGHT)
                return 0;
        }
        set_move_as_tried(move, move_mask);
        make_move(unsolved, move);

        int next_move[3];
        copy_next_move(mask, move, next_move);
        if (is_last_move(next_move))
            break;
        solved = recursive_solve(unsolved, mask, next_move);
        if (!solved)
            clear_move(unsolved, move);
        move[2] = 1;
    }

    return 1;
}

void solve(int unsolved[HEIGHT][WIDTH]) {
    int mask[HEIGHT][WIDTH];
    create_mask(unsolved, mask);

    int move[3];
    copy_first_move(mask, move);
    recursive_solve(unsolved, mask, move);
}
