#include "common.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define answer 1.64493406684822643647241516664602518921894990120679843773555
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

int main(int argc, char** argv){
	int k;
	double sum;
	vector_t* vector;
	for(int n = 4; n <= 14; n++){
		k = pow(2,n);
		vector = createVector(k);
		sum = sumVector(vector);
		printf("S - S(%.0f) \t %.16f \t Error: %.16f\n", pow(2,n), sum, answer-sum) ;
	}
	return 0;
}
