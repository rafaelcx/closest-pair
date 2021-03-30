#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calculate_distance(float x, float y, float z, float w) {
   return sqrt(pow(z - x,2) + pow(w-y,2));
}

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

    double min_distance = 999999999999999;

    input_file = fopen(argv[1], "r");

    // Getting the quantity of points present in the input.txt file
    fscanf(input_file, "%d", &point_quantity);

    // Storing the file pointer position of the coordinates start
    coordinates_start = ftell(input_file);

    for (counter_i = 0; counter_i <= point_quantity; counter_i++) {
        fscanf(input_file, "%lf", &coordinate_x);
        fscanf(input_file, "%lf", &coordinate_y);

        // Storing the file pointer position for the next set of coordinates to compare
        next_check = ftell(input_file);

        printf("%.15f ", coordinate_x);
        printf("%.15f \n", coordinate_y);

        // Rewinding the file pointer to the start
        fseek(input_file, coordinates_start, SEEK_SET);

        for (counter_j = 0; counter_j <= point_quantity; counter_j++) {
            fscanf(input_file, "%lf", &coordinate_z);
            fscanf(input_file, "%lf", &coordinate_w);

            double this_distance = calculate_distance(coordinate_x, coordinate_y, coordinate_z, coordinate_w);

            if ((this_distance != 0) && (this_distance < min_distance)) {
                min_distance = this_distance;
            }

            printf("\t %.15f ", coordinate_z);
            printf("\t %.15f ", coordinate_w);
            printf("\t %.15f \n", min_distance);
        }

        // Setting the pointer to the next set of coordinates that we want to compare
        fseek(input_file, next_check, SEEK_SET);
    }

    // Closing the file pointer
    fclose(input_file);

    return 0;
}
