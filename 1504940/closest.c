#include <stdio.h>

int main(int argc, char **argv) {
    
    FILE *input_file;
    
    int coordinates_start;
    int next_check;

    int point_quantity;
   	int counter_i;
    int counter_j;

    double coordinate_x;
    double coordinate_y;

    double coordinate_z;
    double coordinate_w;

    double min_distance;

    input_file = fopen(argv[1], "r");

    // Getting the quantity of points present in the input.txt file
    fscanf(input_file, "%d", &point_quantity);

    // Printing all points coordinates from input.txt file
    coordinates_start = ftell(input_file);

    for (counter_i = 0; counter_i <= point_quantity; counter_i++) {
        fscanf(input_file, "%lf", &coordinate_x);
        fscanf(input_file, "%lf", &coordinate_y);

        next_check = ftell(input_file);

        printf("%.15f ", coordinate_x);
        printf("%.15f \n", coordinate_y);

        fseek(input_file, coordinates_start, SEEK_SET);

        for (counter_j = 0; counter_j <= point_quantity; counter_j++) {
            fscanf(input_file, "%lf", &coordinate_z);
            fscanf(input_file, "%lf", &coordinate_w);

            printf("\t %.15f ", coordinate_z);
            printf("\t %.15f \n", coordinate_w);
        }

        fseek(input_file, next_check, SEEK_SET);
    }

    // Closing the file pointer
    fclose(input_file);

    return 0;
}
