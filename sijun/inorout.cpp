#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
using namespace std;

int main() {
	double zx = 0, zy = 0, z = 0;
	double cx, cy; 
	int iter;

	bool in;
	int count = 1;

	while (scanf("%lf %lf %d", &cx, &cy, &iter) != EOF) {
		in = true;
		zx = zy = z = 0;

		for (int i = 0; i < iter; i++) {
			z = zx*zx - zy*zy + cx;
			zy = 2 * zx * zy + cy;
			zx = z;
			if (zx*zx + zy*zy > 4) {
				in = false;
				break;
			}
		}
		
		if (in)
			printf("Case %d: In \n", count);
		else
			printf("Case %d: Out \n", count);

		count++;
	}
	return 0;
}
	/*
	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		exit(EXIT_FAILURE);
	}
	if (sscanf(buffer, "%f %f %d", &cx, &cy, &iter) == 3)
		n++;
	else{
		break;
	}
	*/