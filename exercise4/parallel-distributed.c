#include "common.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define answer 1.64493406684822643647241516664602518921894990120679843773555
#include <mpi.h>

void singleIteration(int length);
int size,rank,processorName;
char processorNames[MPI_MAX_PROCESSOR_NAME];
MPI_Status status;


vector_t* createVector(int len){
	vector_t* vector = (vector_t*)calloc(1,sizeof(vector_t));
	vector->len = len;
	vector->data = calloc(len,sizeof(double));
	for(int i = 1; i < len + 1; i++)
		vector->data[i-1] = pow ( i , -2 );
	return vector;
}

double sumVector(vector_t* vector){
	double sum = 0;
	for(int i = 0; i < vector->len; i++)
		sum += vector->data[i];
	return sum;
}

void singleIteration(int length){

	int partitionSize = ( 1 <<length  ) / size;
	int offset = ( 1<< length) %  partitionSize;

	vector_t* vector;
	if ( rank == 0 ) {
		vector = createVector(1<<length);
		double * vectorDataOffset = vector->data+offset, sum = 0, temp ;
		for ( int i = 1;  i < size ; i++ ) {
			MPI_Send ( vectorDataOffset + i * partitionSize, partitionSize, MPI_DOUBLE, i , 0 , MPI_COMM_WORLD);
		}
		sum=sumVector(vector);
		for ( int i = 1;  i < size ; i++ ) {
			MPI_Recv ( &temp , 1 ,  MPI_DOUBLE , MPI_ANY_SOURCE , 1, MPI_COMM_WORLD, &status );
			sum+= temp;
		}

		printf("S - S(%.0f) \t %.16f \t Error: %.16f\n", pow(2,length), sum, answer-sum) ;
	}else {
		vector = createVector(partitionSize);
		MPI_Recv( vector->data , partitionSize , MPI_DOUBLE, 0 , 0 , MPI_COMM_WORLD , &status);
		double sum = sumVector(vector);
		MPI_Send(&sum ,1 ,MPI_DOUBLE , 0 , 1, MPI_COMM_WORLD );
	}

}

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processorNames, &processorName);
	for(int n = 4; n <= 14; n++){
		singleIteration(n);
	}
	MPI_Finalize();
	return 0;
}
