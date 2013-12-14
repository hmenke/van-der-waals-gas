#include <stdio.h>

/*
 * Helper function to write data
 */
int write_single_pointer(char *filename, double *q, int N, double dN) {
        FILE* fp;
        if ((fp = fopen(filename,"w")) == NULL) return 1;

	for( int t = 0; t < N; t++) {
		fprintf( fp, "%e\t%e\n", t*dN, q[t]);
        }

        fclose( fp );
	return 0;
}

/*
 * Helper function to write data (yet unused)
 */
int write_double_pointer(char *filename, double **q, int N1, int N2) {
	// For q: N1 = X.steps, N2 = X.N
        FILE* fp;
        if ((fp = fopen(filename,"w")) == NULL) return 1;

	for( int t = 0; t < N1; t++) {
			for( int i = 0; i < N2; i++ ) {
				fprintf( fp, "%e\t", q[i][t]);
			}
			fprintf( fp, "\n");
        }

        fclose( fp );
	return 0;
}
