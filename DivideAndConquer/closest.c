#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <cmath>

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
            printf("x %d y %d \n", i, j);
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
    Point Pyl[mid + 1];
    Point Pyr[n - mid - 1];
    int li = 0, ri = 0;
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }
    float dl = findClosestDistance(Px, Pyl, mid);
    float dr = findClosestDistance(Px + mid, Pyr, n-mid);
    float d = min(dl, dr);
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;
    }
    return min(d, stripClosest(strip, j, d));
}


Point *merge(Point *lista_pontos, int esquerda, int meio, int direita, int eixo){
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    Point *pontos_esq = (Point *) calloc (n1, sizeof(Point *));
    Point *pontos_dir = (Point *) calloc (n2, sizeof(Point *));
    
    int index_esquerda, index_direita;

    for ( index_esquerda = 0; index_esquerda < n1; index_esquerda++)
        pontos_esq[index_esquerda] = lista_pontos[esquerda + index_esquerda];

    for ( index_direita = 0; index_direita < n2; index_direita++)
        pontos_dir[index_direita] = lista_pontos[meio + 1 + index_direita];

    int i = 0; 
    int j = 0; 
    int k = esquerda; 
    while (i < n1 && j < n2) {
        
        if(eixo == 0 ){
          if (pontos_esq[i].x <= pontos_dir[j].x) {
              lista_pontos[k] = pontos_esq[i];
              i++;
          }
          else {
              lista_pontos[k] = pontos_dir[j];
              j++;
          }
        }else{
          if (pontos_esq[i].y <= pontos_dir[j].y) {
              lista_pontos[k] = pontos_esq[i];
              i++;
          }
          else {
              lista_pontos[k] = pontos_dir[j];
              j++;
          }
        }

        k++;
    }
 
    while (i < n1) {
        lista_pontos[k] = pontos_esq[i];
        i++;
        k++;
    }

    while (j < n2) {
        lista_pontos[k] = pontos_dir[j];
        j++;
        k++;
    }

    return lista_pontos;
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

    Point *sorted_by_x_coordinates = (Point*) calloc(n, sizeof(Point));
    Point *sorted_by_y_coordinates = (Point*) calloc(n, sizeof(Point));
    
    for (int i = 0; i < n; i++) {
        sorted_by_x_coordinates[i] = unsorted_coordinate_list[i];
        sorted_by_y_coordinates[i] = unsorted_coordinate_list[i];
    }

    Point *lista_x = mergeSort(sorted_by_x_coordinates, 0, n -1, 0);
    Point *lista_y = mergeSort(sorted_by_y_coordinates, 0, n -1, 1);

    printf("The smallest distance between %d coordinates is %f \n", n, findClosestDistance(lista_x, lista_y, n));
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
