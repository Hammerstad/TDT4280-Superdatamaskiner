#include "serial.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define answer 1.64493406684822643647241516664602518921894990120679843773555
#ifdef HAVE_OPENMP
#include <omp.h>
#endif
#include <sys/time.h>


vector_t* createVector(int len){
	vector_t* vector = (vector_t*)calloc(1,sizeof(vector_t));
	vector->len = len;
	vector->data = calloc(len,sizeof(double));
	for(int i = 1; i < len + 1; i++)
		vector->data[i-1] = pow ( i , -2 );
	return vector;
}

double sumVector(vector_t* vector){
	if(vector == NULL || vector->len==0 || vector->data == NULL)
		return 0;
	if(vector->len == 1)
		return vector->data[0];
	double sum = 0;
	for(int i = 0; i < vector->len; i++)
		sum += vector->data[i];
	return sum;
}

double sumLastElementsInVector(vector_t* vector, int n){
	if(vector == NULL || vector->len==0 || (vector->len-n)<=0 || vector->data == NULL)
		return 0;
	if(vector->len-n == 1)
		return vector->data[0];
	double sum = 0;
	for(int i = n; i < vector->len; i++)
		sum += vector->data[i];
	return sum;
}

double Time(){
#ifdef HAVE_OPENMP
	return omp_get_wtime();
#else
	struct timeval tmpTime;
	gettimeofday(&tmpTime,NULL);
	return tmpTime.tv_sec + tmpTime.tv_usec/1.0e6;
#endif
}

int main(int argc, char** argv){
	int k;
	double sum;
	vector_t* vector;
	double time = Time();
	for(int n = 4; n <= 14; n++){
		k = pow(2,n);
		vector = createVector(k);
		sum = sumVector(vector);
		printf("S - S(%.0f) \t %.16f \t Error: %.16f\n", pow(2,n), sum, answer-sum) ;
	}
	printf("%f\n",Time() - time);
	return 0;
}
