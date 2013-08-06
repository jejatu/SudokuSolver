#include <stdio.h>
#include "file.h"
#include "tests.h"
#include "solver.h"
#include "utils.h"

void read_from_file(char* filename) {
    int matrix[HEIGHT][WIDTH];
    read_matrix_from_file(filename, matrix);
    print_matrix(matrix);
    solve(matrix);
    puts("---------");
    print_matrix(matrix);
}

int main(int argc, char** argv) {
    if (argc <= 1)
        run_tests();
    else
        read_from_file(argv[1]);
        
	return 0;
}
