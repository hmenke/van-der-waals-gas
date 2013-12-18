#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"
#include "solver.h"
#include "statistics.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	simparams X;

	X.m = 1;
	X.lambda = 1./6.;
	X.n = 4;
	X.gamma = 1./X.n;
	X.rho = 100;
	X.N = 10; // default
	X.tmax = 100;
	X.steps = 1e6;
	X.dt = X.tmax*1.0/X.steps;

	double te = 14; // ?
	if ( argc != 4 ) {
		printf("Too few arguments. 3 required, %d given\n", argc-1);
		printf("Usage: %s {N_min} {N_max} {N_step}\n", argv[0]); 
		return 1;
	}
	int N_min = abs(atoi(argv[1]));
	int N_max = abs(atoi(argv[2]));
	int N_step = abs(atoi(argv[3]));
	if (N_min == 0) {
		printf("You can't run the simulation for 0 particles\n");
		printf("I'm going to ignore this and start at %d\n",N_step);
		N_min = N_step;
	}

	double **q = (double**) malloc(N_max * sizeof(double));
	for (int i = 0; i < N_max; i++)
		q[i] = (double*) malloc(X.steps * sizeof(double));

	double **p = (double**) malloc(N_max * sizeof(double));
	for (int i = 0; i < N_max; i++)
		p[i] = (double*) malloc(X.steps * sizeof(double));

	double *Q = (double*) malloc(X.steps * sizeof(double));

	double *EKin = (double*) malloc(X.steps * sizeof(double));

	double *var = (double*) malloc(N_max * sizeof(double));
	time_t integration_time;
	double *times = (double*) malloc(N_max * sizeof(double));

        FILE* fp;
        if ((fp = fopen("Var.dat","w")) == NULL) return 1;

	for (int n = N_min; n <= N_max; n += N_step) {
		X.N = n;
		printf("### N = %d ###\n", X.N);

		printf("Setting up the simulation\n");
		setup_simulation(q, p, X.N);

		printf("Integrating differential equation\n");
		integration_time = time(NULL);
		for (int t = 0; t < X.steps-1; t++) {
			velocity_verlet_step(q, p, t, &X);
		}
		times[X.N-1] = time(NULL) - integration_time;
		printf("Total time taken: %.2f seconds\n", times[X.N-1]);

		printf("Calculating COM motion and kinetic energy\n");
		centre_of_mass_motion(Q, q, &X);
		kinetic_energy(EKin, p, &X);
		var[X.N-1] = mean_kinetic_energy(EKin, te, &X);
		fprintf(fp, "%d\t%e\t%e\n", X.N, var[X.N-1],times[X.N-1]);
		fflush(fp);

		//if ( n+N_step > N_max ) {
		printf("Writing results to disk\n");
		write_single_pointer("Q.dat", Q, X.steps, X.dt);
		write_single_pointer("EKin.dat", EKin, X.steps, X.dt);
		//}
	}

        fclose(fp);

	free(q);
	free(p);
	free(Q);
	free(EKin);
	free(var);
	free(times);

	return 0;
}
