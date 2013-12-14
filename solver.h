#ifndef __SOLVER_H
#define __SOLVER_H

double compute_forces(double **q, int i, int t, simparams *X);

void velocity_verlet_step(double **q, double **p, int t, simparams *X);

#endif
