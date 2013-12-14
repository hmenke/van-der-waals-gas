#ifndef __STATISTICS_H
#define __STATISTICS_H

void centre_of_mass_motion(double *Q, double **q, simparams *X);

void kinetic_energy(double *EKin, double **p, simparams *X);

double mean_kinetic_energy(double *EKin, double te, simparams *X);

#endif
