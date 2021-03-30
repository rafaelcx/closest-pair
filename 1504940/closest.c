#include <stdio.h>

int main(int argc, char **argv) {
    
    FILE *input_file;

    int point_quantity;
   	int counter;
    double coordinate_x;
    double coordinate_y;

    input_file = fopen(argv[1], "r");

    // Getting the quantity of points present in the input.txt file
    fscanf(input_file, "%d", &point_quantity);

    // Printing all points coordinates from input.txt file
    counter = 0;
    while(counter != point_quantity) {

    	fscanf(input_file, "%lf", &coordinate_x);
    	fscanf(input_file, "%lf", &coordinate_y);

    	printf("%.15f ", coordinate_x);
    	printf("%.15f \n", coordinate_y);

    	counter++;
    }

    // Closing the file pointer
    fclose(input_file);

    return 0;
}
