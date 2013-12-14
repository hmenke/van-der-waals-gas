#include <stdlib.h>
#include <time.h>

/*
 * Setting the initial state of the vectors to a random noise in a given range
 */
void setup_simulation(double **q, double **p, int N) {
	srand(time(NULL));
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		q[i][0] = rand()/5./RAND_MAX + 1.9;
		p[i][0] = rand()/50./RAND_MAX - 0.01;
	}
}
