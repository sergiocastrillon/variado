#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define TAM 512000 // Con tamaños superiores a 500000, valgrind da fallos si no cambias el tamaño del stack
typedef struct {
int vector[TAM];
int ultimo;
} monticulo;

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
		srand(time(NULL));
		/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
	}
void aleatorio(int v [], int n) {
		int i, m=2*n+1;
		for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
	/* se generan números pseudoaleatorio entre -n y +n */
}
void ascendente(int v [], int n) {
   int i;
   for (i=0; i < n; i++)
      v[i] = i;
}

void descendente(int v [], int n) {
   int i,j;
   j = 1;
   
   for (i=n;i>0;i--){
      v[i-1] = j;
      j++;
   }
}

void listar_vector (int v[],int n) {
	int i;
	for(i=0;i<n;i++){
		printf("%3d",v[i]);
	}
}
/**********************************************************************/

void ini_monticulo(monticulo *m){
	m->ultimo=-1;
}   

void hundir(monticulo *m, int i){
	int hijoder,hijoizq,j=0,aux;
	do{
		hijoizq=2*i+1;
		hijoder=2*i+2;
		j=i;
		if (hijoder<=m->ultimo && m->vector[hijoder]>m->vector[i]) i=hijoder;
		if (hijoizq<=m->ultimo && m->vector[hijoizq]>m->vector[i]) i=hijoizq;
		aux=m->vector[i];
		m->vector[i]=m->vector[j];
		m->vector[j]=aux;
	}while (j!=i);
}

void crear_monticulo(int n[], int g, monticulo *m){
	int i=0;
	for (i=0;i<g;i++) m->vector[i]=n[i];
	m->ultimo=g-1;
	for (i=(g / 2); i>=0 ;i--) hundir(m,i);
}

int eliminar_mayor(monticulo *m){
	int x;
	if (m->ultimo==-1) printf ("Error: Monticulo vacío\n");
	else{
		x=m->vector[0];
		m->vector[0]=m->vector[m->ultimo];
		m->ultimo=m->ultimo-1;
		if (m->ultimo>=0) hundir(m,0);
	return x;   
	}
}
void ord_monticulo(int v[],int n){
	monticulo m;
	int i;
	ini_monticulo(&m);
	crear_monticulo(v,n,&m);
	for (i=n-1;i>=0;i--) v[i]=eliminar_mayor(&m);
}
/**********************************************************************/
float tempo_baixo_quentar(int v[], int i, monticulo m){
	int n;
	double t1, t2, td, tan, tdes;
	tan=microsegundos();
	for (n=0; n<1000; n++){ //facemos un n<10 xa que n ten que ser unha potencia de 10>500, neste caso
		ascendente(v,i);
		crear_monticulo(v,i,&m);
	}
	tdes=microsegundos();
	t1=tdes-tan;
	tan=microsegundos();
	for(n=0; n<1000; n++) ascendente(v,i);
	tdes=microsegundos();
	t2=tdes-tan;
	td=(t1-t2)/n;
	return td;
}		

void quentar_procesador(){
	int i=500;
	double tsub,taj,tsob, td, tan, tdes;
	int v[32000];
	monticulo m;
	ini_monticulo(&m);
	for (i=500; i<32001; i*=2){
		ascendente(v, i);
		tan=microsegundos();
		crear_monticulo(v,i,&m);
		tdes=microsegundos();
		td=tdes-tan;
		if (td<500) tempo_baixo_quentar(v, i, m);
		else printf("   ");
		tsub=td/pow(i,0.8);
		taj=td/pow(i,1);
		tsob=td/pow(i,1.2);
	}
}
/**********************************************************************/

float tempo_baixo_crear(int v[], int i, monticulo m){
	int n;
	double t1, t2, td, tan, tdes;
	tan=microsegundos();
	for (n=0; n<1000; n++){ //facemos un n<10 xa que n ten que ser unha potencia de 10>500, neste caso
		ascendente(v,i);
		crear_monticulo(v,i,&m);
	}
	tdes=microsegundos();
	t1=tdes-tan;
	tan=microsegundos();
	for(n=0; n<1000; n++) ascendente(v,i);
	tdes=microsegundos();
	t2=tdes-tan;
	td=(t1-t2)/n;
	printf("*  ");
	return td;
}		

void timcrear(){
	int i=500;
	double tsub,taj,tsob, td, tan, tdes;
	int v[32000];
	monticulo m;
	ini_monticulo(&m);
	printf("Medicion de tempos de crear monticulos con un array ordenado ascendente \n");
	printf("%5s%20s%20s%20s%20s \n", "n", "t(n)", "t(n)/n^0.8", "t(n)/n", "t(n)/n^1.2");
	for (i=500; i<32001; i*=2){
		ascendente(v, i);
		tan=microsegundos();
		crear_monticulo(v,i,&m);
		tdes=microsegundos();
		td=tdes-tan;
		if (td<500) tempo_baixo_crear(v, i, m);
		else printf("   ");
		tsub=td/pow(i,0.8);
		taj=td/pow(i,1);
		tsob=td/pow(i,1.2);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", i, td, tsub, taj, tsob);
	}
	printf("\n\n\n");
}
/**********************************************************************/
void vali_crear(){
	int v[16];
	printf("Ordenacion por  seleccion con inicializacion aleatoria\n");
	aleatorio(v,16);
	listar_vector(v,16);
	printf("\n");
	printf("ordenado? 0\n");
	printf("ordenando \n");
	ord_monticulo(v,16);
	listar_vector(v,16);
	printf("\n");
	printf("esta ordenado \n");
	printf("\n\n\n");
}	
/**********************************************************************/
float tempo_baixo_desc(int v[], int i, monticulo m){
	int n;
	double t1, t2, td, tan, tdes;
	tan=microsegundos();
	for (n=0; n<1000; n++){ //facemos un n<10 xa que n ten que ser unha potencia de 10>500, neste caso
		descendente(v,i);
		ord_monticulo(v,i);
	}
	tdes=microsegundos();
	t1=tdes-tan;
	tan=microsegundos();
	for(n=0; n<1000; n++) descendente(v,i);
	tdes=microsegundos();
	t2=tdes-tan;
	td=(t1-t2)/1000;
	printf("*  ");
	return td;
}		
void timdesc(){
	int i=500;
	double tsub,taj,tsob, td, tan, tdes;
	int v[32000];
	monticulo m;
	
	printf("Medicion de tempos con ordenacion por monticulos en un array ordenado descendente \n");
	printf("%5s%20s%20s%20s%20s \n", "n", "t(n)", "t(n)/(n^1)", "t(n)/(n*log(n))", "t(n)/(n^1.2)");
	for (i=500; i<32001; i*=2){
		descendente(v, i);
		tan=microsegundos();
		ord_monticulo(v,i);
		tdes=microsegundos();
		td=tdes-tan;
		if (td<500) td=tempo_baixo_desc(v, i, m);
		else printf("   ");
		tsub=td/pow(i, 1.0);
		taj=td/(i*log(i));
		tsob=td/pow(i, 1.2);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", i, td, tsub, taj, tsob);
	}
	printf("\n\n\n");
}	
/**********************************************************************/
float tempo_baixo_asc(int v[], int i, monticulo m){
	int n;
	double t1, t2, td, tan, tdes;
	tan=microsegundos();
	for (n=0; n<1000; n++){ //facemos un n<10 xa que n ten que ser unha potencia de 10>500, neste caso
		ascendente(v,i);
		ord_monticulo(v,i);
	}
	tdes=microsegundos();
	t1=tdes-tan;
	tan=microsegundos();
	for(n=0; n<1000; n++) ascendente(v,i);
	tdes=microsegundos();
	t2=tdes-tan;
	td=(t1-t2)/1000;
	printf("*  ");
	return td;
}		

void timasc(){
	int i=500;
	double tsub,taj,tsob, td, tan, tdes;
	int v[32000];
	monticulo m;
	
	printf("Medicion de tempos con ordenacion por monticulos en un array ordenado ascendente \n");
	printf("%5s%20s%20s%20s%20s \n", "n", "t(n)", "t(n)/(n^1)", "t(n)/(n*log(n))", "t(n)/(n^1.2)");
	for (i=500; i<32001; i*=2){
		ascendente(v, i);
		tan=microsegundos();
		ord_monticulo(v,i);
		tdes=microsegundos();
		td=tdes-tan;
		if (td<500) td=tempo_baixo_asc(v, i, m);
		else printf("   ");
		tsub=td/pow(i, 1.0);
		taj=td/(i*log(i));
		tsob=td/pow(i, 1.2);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", i, td, tsub, taj, tsob);
	}
	printf("\n\n\n");
}	
/**********************************************************************/
float tempo_baixo_alea(int v[], int i, monticulo m){
	int n;
	double t1, t2, td, tan, tdes;
	tan=microsegundos();
	for (n=0; n<1000; n++){ //facemos un n<10 xa que n ten que ser unha potencia de 10>500, neste caso
		aleatorio(v,i);
		ord_monticulo(v,i);
	}
	tdes=microsegundos();
	t1=tdes-tan;
	tan=microsegundos();
	for(n=0; n<1000; n++) aleatorio(v,i);
	tdes=microsegundos();
	t2=tdes-tan;
	td=(t1-t2)/1000;
	printf("*  ");
	return td;
}		

void timalea(){
	int i=500;
	double tsub,taj,tsob, td, tan, tdes;
	int v[32000];
	monticulo m;
	
	printf("Medicion de tempos con ordenacion por monticulos en un array aleatorio \n");
	printf("%5s%20s%20s%20s%20s \n", "n", "t(n)", "t(n)/(n^1)", "t(n)/(n*log(n))", "t(n)/(n^1.2)");
	for (i=500; i<32001; i*=2){
		aleatorio(v, i);
		tan=microsegundos();
		ord_monticulo(v,i);
		tdes=microsegundos();
		td=tdes-tan;
		if (td<500) td=tempo_baixo_alea(v, i, m);
		else printf("   ");
		tsub=td/pow(i, 1.0);
		taj=td/(i*log(i));
		tsob=td/pow(i, 1.2);
		printf("%5d%17.2f%18.6f%22.6f%18.6f\n", i, td, tsub, taj, tsob);
	}
	printf("\n\n\n");
}
/**********************************************************************/	
int main() {
	inicializar_semilla();
	microsegundos();
	quentar_procesador();
	timcrear();
	vali_crear();
	timdesc();
	timasc();
	timalea();
return 0;
}
