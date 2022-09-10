void main()
{
    long long num[N];
    long long i;

    srand(time(NULL));

   for(i=0;i<N;i++)
   {
       num[i]=rand()%100000; // Cuantos numeros se pueden generar
   }

    //for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}


    // Introducir aquí la función con el algoritmo de ordenación (o búsqueda!)
    printf("Ordenados %d elementos usando x\n",N);



    // for(i=0;i<N;i++)
    //{
    //    printf("%d ", num[i]);
    //}
}
