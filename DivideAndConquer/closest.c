#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <cmath>
using namespace std;
 
//Estrutua do ponto
struct Point
{
    float x, y;
};

struct ClosestPoints{
    Point primeiro_ponto, segundo_ponto;
    float distancia_euclidiana;
};

void imprime_pontos(Point *lista_pontos, int tamanho){
  for(int i = 0; i < tamanho; i++){
    printf("%f %f\n ", lista_pontos[i].x, lista_pontos[i].y);
  }
}

//Calculo da distancia Euclidiana
float distancia_euclidiana(Point primeiroPonto, Point segundoPonto){
    return sqrt((primeiroPonto.x - segundoPonto.x) * (primeiroPonto.x - segundoPonto.x) + (primeiroPonto.y - segundoPonto.y) * (primeiroPonto.y - segundoPonto.y));
}

// Calculo da menor distancia
float forca_bruta(Point P[], int tamanho)
{
    float min = 100000000000000;
    ClosestPoints pontos;
    
    for (int i = 0; i < tamanho; ++i){
        for (int j = i + 1; j < tamanho; ++j){
            printf("x %d y %d \n", i, j);
            // printf("Ponto1 x %f Ponto1 y %f Ponto2 x %f Ponto2 y %f \n", P[i].x, P[i].y, P[j].x, P[j].y);
            // if (distancia_euclidiana(P[i], P[j]) < min)
            //     min = distancia_euclidiana(P[i], P[j]);
            //     printf("Respostsdasdasda %f \n", min);
            //     pontos.primeiro_ponto = P[i];
            //     pontos.segundo_ponto = P[j];
            //     pontos.distancia_euclidiana = min;
        }       
    }
    // printf("Resposta %f \n", pontos.distancia_euclidiana);
    return min;
}


// Ponto forca_bruta(Ponto *pontos, int linhas){
//   printf("ooo");
//   ClosestPoints pontos;

//   float distancia = 100000000;
//   float tempo_execucao = 0;
//   Ponto pFinal;

//   for (int i = 0; i < linhas; i++){
//     for(int j = i+1; j < linhas; j++){
//       if(euclidiana(pontos[i].x,pontos[i].coordenada_y, pontos[j].coordenada_x, pontos[j].coordenada_y) < resposta.distancia_euclidiana){
//         resposta.primeiro_ponto = pontos[i];
//         resposta.segundo_ponto = pontos[j];
//         resposta.distancia_euclidiana = euclidiana(pontos[i].coordenada_x,pontos[i].coordenada_y, pontos[j].coordenada_x, pontos[j].coordenada_y);
//       }else if(euclidiana(pontos[i].coordenada_x,pontos[i].coordenada_y, pontos[j].coordenada_x, pontos[j].coordenada_y) == resposta.distancia_euclidiana){
//         printf("b %f \n", resposta.distancia_euclidiana);
//       }
//     }
//    }


//Olha o strip
float stripClosest(Point strip[], int size, float d){
    float min = d;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
        {
            if (distancia_euclidiana(strip[i],strip[j]) < min)
                min = distancia_euclidiana(strip[i], strip[j]);
        }
    }
    return min;
}

//Encontra a menor distancia
float closestUtil(Point Px[], Point Py[], int n){
    if (n <= 3)
        return forca_bruta(Px, n);
    
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
    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n-mid);
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

Point *mergeSort(Point *lista_pontos, int esquerda, int direita, int eixo){
    Point *pontos_ordenados;
    if (esquerda < direita){
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(lista_pontos, esquerda, meio, eixo);
        mergeSort(lista_pontos, meio+1, direita, eixo);
        pontos_ordenados = merge(lista_pontos, esquerda, meio, direita, eixo);
    }

    return pontos_ordenados;
}

float closest(Point P[], int n){
    Point *Px = (Point*) calloc(n, sizeof(Point));
    Point *Py =  (Point*) calloc(n, sizeof(Point));
    
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }
    Point *lista_x = mergeSort(Px, 0, n -1, 0);
    Point *lista_y = mergeSort(Py, 0, n -1, 1);

    return closestUtil(lista_x, lista_y, n);
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

    printf("The smallest distance of %d is %f \n", coordinates_quantity, closest(coordinate_list, coordinates_quantity));

    return 0;
}
