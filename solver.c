#include <math.h>
#include "simulation.h"

/*
 * Compute the right-hand-side of $\ddot{q}(t) = F(q(t),p(t))$
 */
double compute_forces(double **q, int i, int t, simparams *X) {
	double F;
	F = - X->n * X->gamma * pow(q[i][t],X->n-1);
	#pragma omp parallel for reduction (+:F)
	for (int j = 0; j < X->N; j++) {
		F += ( 6 * X->lambda * X->rho * pow(q[i][t] - q[j][t],5) )/pow(1 + X->rho * pow(q[i][t] - q[j][t], 6), 2);
	}
	return F;
}

/*
 * Do the velocity verlet integration (just one step)
 */
void velocity_verlet_step(double **q, double **p, int t, simparams *X) {
	#pragma omp parallel for
	for (int i = 0; i < X->N; i++) {
		q[i][t+1] = q[i][t] + p[i][t]/X->m * X->dt + compute_forces(q,i,t,X)/X->m/2. * X->dt * X->dt;
		p[i][t+1] = p[i][t] + (compute_forces(q,i,t,X) + compute_forces(q,i,t+1,X))/X->m*X->dt;
	}
}

