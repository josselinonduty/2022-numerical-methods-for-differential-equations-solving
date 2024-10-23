#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main(int argc, char **argv)
{
	long double _v0[2];
	_v0[0] = 0;
	_v0[1] = 1;
	vector_t vpred = vector_create(_v0);

	for (int i = 0; i < 5; i++) {
		vector_t vi = van_der_pol(0, vpred);
		vector_free(&vpred);

		vpred = vi;
		vector_display(vi);
		printf("\n");
	}

	vector_free(&vpred);

	return 0;
}
