typedef struct {
	double* data;
	int len;
} vector_t;

vector_t* createVector(int len);
double sumVector(vector_t* vector);
double sumLastElementsInVector(vector_t* vector, int n);
double Time();
