#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <cmath>
#include <time.h>

using namespace std;
 
// ============================================== //
// === Structs ================================== //
// ============================================== //

struct Point {
    float x, y;
};

struct ClosestPoints {
    Point primeiro_ponto, segundo_ponto;
    float distancia_euclidiana;
};

// ============================================== //
// ============================================== //


float calculateEuclidianDistance(Point first_point, Point second_point) {
    return sqrt((first_point.x - second_point.x) * (first_point.x - second_point.x) + (first_point.y - second_point.y) * (first_point.y - second_point.y));
}

// Calculo da menor distancia
float bruteForceResult(Point P[], int tamanho) {
    float min = 100000000000000;
    ClosestPoints pontos;
    
    for (int i = 0; i < tamanho; ++i){
        for (int j = i + 1; j < tamanho; ++j){
            
        }       
    }

    return min;
}

float stripClosest(Point strip[], int size, float d){
    float min = d;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; (j < size) && ((strip[j].y - strip[i].y) < min); ++j) {

            float this_min_distance = calculateEuclidianDistance(strip[i], strip[j]);
            
            if (this_min_distance < min) {
                min = this_min_distance;
            }
        }
    }

    return min;
}

float findClosestDistance(Point Px[], Point Py[], int n){
    if (n <= 3)
        return bruteForceResult(Px, n);
    
    int mid = n / 2;

    Point midPoint = Px[mid];
    Point pyl[mid + 1];
    Point pyr[n - mid - 1];
    
    int li = 0, ri = 0;
    
    for (int i = 0; i < n; i++) {
        if (Py[i].x <= midPoint.x) {
            pyl[li++] = Py[i];
        } else {
            pyr[ri++] = Py[i];
        }
    }

    float dl = findClosestDistance(Px, pyl, mid);
    float dr = findClosestDistance(Px + mid, pyr, n-mid);


    float d = min(dl, dr);
    
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;
    }

    return min(d, stripClosest(strip, j, d));
}

Point *merge(Point *coordinate_list, int left, int middle, int right, int axis) {
    
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    Point *left_points = (Point *) calloc (n1, sizeof(Point *));
    Point *right_points = (Point *) calloc (n2, sizeof(Point *));
    
    int index_left, index_right;

    for (index_left = 0; index_left < n1; index_left++)
        left_points[index_left] = coordinate_list[left + index_left];

    for (index_right = 0; index_right < n2; index_right++)
        right_points[index_right] = coordinate_list[middle + 1 + index_right];

    int i = 0; 
    int j = 0; 
    int k = left;

    while (i < n1 && j < n2) {
        
        if(axis == 0 ) {

          if (left_points[i].x <= right_points[j].x) {
              coordinate_list[k] = left_points[i];
              i++;
          } else {
              coordinate_list[k] = right_points[j];
              j++;
          }

        } else {
          if (left_points[i].y <= right_points[j].y) {
              coordinate_list[k] = left_points[i];
              i++;
          } else {
              coordinate_list[k] = right_points[j];
              j++;
          }
        }

        k++;
    }
 
    while (i < n1) {
        coordinate_list[k] = left_points[i];
        i++;
        k++;
    }

    while (j < n2) {
        coordinate_list[k] = right_points[j];
        j++;
        k++;
    }

    return coordinate_list;
}

Point *mergeSort(Point *coordinate_list, int left, int right, int axis) {
    
    Point *sorted_coordinate_list;

    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(coordinate_list, left, middle, axis);
        mergeSort(coordinate_list, middle + 1, right, axis);

        sorted_coordinate_list = merge(coordinate_list, left, middle, right, axis);
    }

    return sorted_coordinate_list;
}

void DivideAndConquer(Point unsorted_coordinate_list[], int n) {

    clock_t t = clock();

    Point *aux_list_x = (Point*) calloc(n, sizeof(Point));
    Point *aux_list_y = (Point*) calloc(n, sizeof(Point));
    
    for (int i = 0; i < n; i++) {
        aux_list_x[i] = unsorted_coordinate_list[i];
        aux_list_y[i] = unsorted_coordinate_list[i];
    }

    Point *coordinate_list_sorted_by_x = mergeSort(aux_list_x, 0, n -1, 0);
    Point *coordinate_list_sorted_by_y = mergeSort(aux_list_y, 0, n -1, 1);

    float closest_distance = findClosestDistance(coordinate_list_sorted_by_x, coordinate_list_sorted_by_y, n);

    // Getting the clock quantity that the algorithm took to run
    t = clock() -t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC;

    printf("\n DivideAndConquer took %.4f seconds\n", time_taken);
    printf("\n DivideAndConquer %.4f to be the min distance between two points\n", closest_distance);
    printf("\n DivideAndConquer %.4f to be the first point x coordinate\n", 0.00);
    printf("\n DivideAndConquer %.4f to be the first point y coordinate\n", 0.00);
    printf("\n DivideAndConquer %.4f to be the second point x coordinate\n", 0.00);
    printf("\n DivideAndConquer %.4f to be the second point y coordinate\n", 0.00);
}
 
int main() {

    FILE *input_file;
    
    int i;
    int coordinates_quantity;

    // Reading input file
    input_file = fopen("input.txt", "rt");
    
    // Checks that an input.txt file was indeed provided
    if(input_file == NULL) {
        printf("You must provide an input.txt file correctly formatted.\n");
        return(-1);
    }

    // Creating an array of points with size equals to the coordinates quantity provided on input.txt file
    fscanf(input_file, "%d", &coordinates_quantity);
    Point coordinate_list[coordinates_quantity];

    // Populating the Points array with the coordinates from the input.txt file
    for (int i = 0; i < coordinates_quantity; i++) {
        Point point;
        double x;
        double y;

        fscanf(input_file, "%lf", &x);
        fscanf(input_file, "%lf", &y);

        point.x = x;
        point.y = y;

        coordinate_list[i] = point;
    }

    DivideAndConquer(coordinate_list, coordinates_quantity);

    return 0;
}
