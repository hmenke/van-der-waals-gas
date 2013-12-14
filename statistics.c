#include <math.h>
#include "simulation.h"

/*
 * Calculate the centre of mass motion $Q(t) = \frac{1}{N} \sum_i q_i(t)$
 */
void centre_of_mass_motion(double *Q, double **q, simparams *X) {
	#pragma omp parallel for
	for (int t = 0; t < X->steps; t++) {
		double Q_TMP = 0;
		#pragma omp parallel for reduction (+:Q_TMP)
		for (int i = 0; i < X->N; i++) {
			Q_TMP += q[i][t]/X->N;
		}
		Q[t] = Q_TMP;
	}
}

/*
 * Calculate the kinetic energy $T(t) = \frac{1}{N} \sum_i \frac{p_i(t)^2){2 m}$
 */
void kinetic_energy(double *EKin, double **p, simparams *X) {
	#pragma omp parallel for
	for (int t = 0; t < X->steps; t++) {
		double EKin_TMP = 0;
		#pragma omp parallel for reduction (+:EKin_TMP)
		for (int i = 0; i < X->N; i++) {
			EKin_TMP += p[i][t]*p[i][t]/(X->m*2.0*X->N);
		}
		EKin[t] = EKin_TMP;
	}
}

/*
 * Calculate the sigma thing $\sqrt{N} \sigma_E (\bar{E}_\text{kin})^{-1)$
 */
double mean_kinetic_energy(double *EKin, double te, simparams *X) {
	double EKinBar = 0;
	#pragma omp parallel for reduction (+:EKinBar)
	for (int t = floor(te/X->dt); t < X->steps; t++) {
		 EKinBar += EKin[t]/(X->steps-floor(te/X->dt));
	}
	
	double VarEBar = 0;
	#pragma omp parallel for reduction (+:VarEBar)
	for (int t = floor(te/X->dt); t < X->steps; t++) {
		 VarEBar += pow(EKin[t]-EKinBar,2)/(X->steps-floor(te/X->dt));
	}

	return sqrt(X->N) * sqrt(VarEBar) / EKinBar;
}
