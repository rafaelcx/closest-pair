#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float calculate_distance(float x, float y, float z, float w) {
   return sqrt(pow(z - x, 2) + pow(w - y, 2));
}

int main(int argc, char **argv) {
    
    FILE *input_file;

    clock_t t;
    double time_taken;
    
    int coordinates_start;
    int coordinates_next_check;

    int point_quantity;
    int counter_i;
    int counter_j;

    double coordinate_x;
    double coordinate_y;

    double coordinate_z;
    double coordinate_w;

    double min_distance = 999999999999999;
    double final_coordinate_x;
    double final_coordinate_y;
    double final_coordinate_z;
    double final_coordinate_w;

    input_file = fopen(argv[1], "r");

    // Getting the quantity of points present in the input.txt file
    fscanf(input_file, "%d", &point_quantity);

    // Storing the file pointer position of the coordinates start
    coordinates_start = ftell(input_file);

    // Starting the clock count
    t = clock();

    for (counter_i = 0; counter_i < point_quantity; counter_i++) {
        fscanf(input_file, "%lf", &coordinate_x);
        fscanf(input_file, "%lf", &coordinate_y);

        // Storing the file pointer position for the next set of coordinates to compare
        coordinates_next_check = ftell(input_file);

        // printf("\n%.15f ", coordinate_x);
        // printf("%.15f \n", coordinate_y);

        // Rewinding the file pointer to the start
        fseek(input_file, coordinates_start, SEEK_SET);

        for (counter_j = 0; counter_j < point_quantity; counter_j++) {
            fscanf(input_file, "%lf", &coordinate_z);
            fscanf(input_file, "%lf", &coordinate_w);

            double this_distance = calculate_distance(coordinate_x, coordinate_y, coordinate_z, coordinate_w);

            if ((this_distance != 0) && (this_distance < min_distance)) {
                min_distance = this_distance;
                final_coordinate_x = coordinate_x;
                final_coordinate_y = coordinate_y;
                final_coordinate_z = coordinate_z;
                final_coordinate_w = coordinate_w;
            }

            // printf("\t %.15f ", coordinate_z);
            // printf("\t %.15f ", coordinate_w);
            // printf("\t %.15f \n", min_distance);
        }

        // Setting the pointer to the next set of coordinates that we want to compare
        fseek(input_file, coordinates_next_check, SEEK_SET);
    }

    // Getting the clock quantity that the algorithm took to run
    t = clock() -t;

    // Closing the file pointer
    fclose(input_file);

    // Printing the results
    time_taken = ((double) t) / CLOCKS_PER_SEC;

    printf("\n Brute force took %.4f seconds\n", time_taken);
    printf("\n Brute force found %.4f to be the min distance between two points\n", min_distance);
    printf("\n Brute force found %.4f to be the first point x coordinate\n", final_coordinate_x);
    printf("\n Brute force found %.4f to be the first point y coordinate\n", final_coordinate_y);
    printf("\n Brute force found %.4f to be the second point x coordinate\n", final_coordinate_z);
    printf("\n Brute force found %.4f to be the second point y coordinate\n", final_coordinate_w);

    return 0;
}


