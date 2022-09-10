#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 50000

void intercambiar(int *a, int *b) {
  int temporal = *a;
  *a = *b;
  *b = temporal;
}



void burbuja(int arreglo[], int longitud) {
  for (int x = 0; x < longitud; x++) {
    // Recuerda que el -1 es porque no queremos llegar al final ya que hacemos
    // un indiceActual + 1 y si fuéramos hasta el final, intentaríamos acceder a un valor fuera de los límites
    // del arreglo
    for (int indiceActual = 0; indiceActual < longitud - 1;
         indiceActual++) {
      int indiceSiguienteElemento = indiceActual + 1;
      // Si el actual es mayor que el que le sigue a la derecha...
      if (arreglo[indiceActual] > arreglo[indiceSiguienteElemento]) {
        // ...intercambiarlos, es decir, mover el actual a la derecha y el de la derecha al actual
        intercambiar(&arreglo[indiceActual], &arreglo[indiceSiguienteElemento]);
      }
    }
  }
}



void main()
{
    int num[N];
    int i;

    srand(time(NULL));

   for(i=0;i<N;i++)
   {
       num[i]=rand()%100000;
   }

    //for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}
    burbuja(num,N);
    printf("Ordenados %d elementos con Burbuja\n",N);
    // for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}
}
