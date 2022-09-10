#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 300000

void intercambiar(long long *a, long long *b) {
  long long temporal = *a;
  *a = *b;
  *b = temporal;
}



long long particion(long long arreglo[], long long izquierda, long long derecha) {
  // Elegimos el pivote, es el primero
  long long pivote = arreglo[izquierda];
  // Ciclo infinito
  while (1) {
    // Mientras cada elemento desde la izquierda esté en orden (sea menor que el
    // pivote) continúa avanzando el índice
    while (arreglo[izquierda] < pivote) {
      izquierda++;
    }
    // Mientras cada elemento desde la derecha esté en orden (sea mayor que el
    // pivote) continúa disminuyendo el índice
    while (arreglo[derecha] > pivote) {
      derecha--;
    }
    /*
    Si la izquierda es mayor o igual que la derecha significa que no
    necesitamos hacer ningún intercambio
    de variables, pues los elementos ya están en orden (al menos en esta
    iteración)
    */
    if (izquierda >= derecha) {
      // Indicar "en dónde nos quedamos" para poder dividir el arreglo de nuevo
      // y ordenar los demás elementos
      return derecha;
    } else {//Nota: yo sé que el else no hace falta por el return de arriba, pero así el algoritmo es más claro
      /*
      Si las variables quedaron "lejos" (es decir, la izquierda no superó ni
      alcanzó a la derecha)
      significa que se detuvieron porque encontraron un valor que no estaba
      en orden, así que lo intercambiamos
      */
      intercambiar(&arreglo[izquierda], &arreglo[derecha]);
      /*
      Ya intercambiamos, pero seguimos avanzando los índices
      */
      izquierda++;
      derecha--;
    }
    // El while se repite hasta que izquierda >= derecha
  }
}





void quicksort(long long arreglo[], long long izquierda, long long derecha) {
  if (izquierda < derecha) {
    long long indiceParticion = particion(arreglo, izquierda, derecha);
    quicksort(arreglo, izquierda, indiceParticion);
    quicksort(arreglo, indiceParticion + 1, derecha);
  }
}



void main()
{
    long long num[N];
    long long i;

    srand(time(NULL));

   for(i=0;i<N;i++)
   {
       num[i]=rand()%100000;
   }

    //for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}
    quicksort(num, 0, N - 1);
    printf("Ordenados %d elementos usando QuickSort\n",N);
    // for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}
}
