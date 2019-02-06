#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int maxWidth;
	while (true) {
		scanf("%d", &maxWidth);
		if (maxWidth == 0)
			break;
		int wOut = 0, hOut = 0, maxH = 0, currW = 0;
		
		while (true) {
			int w, h;
			scanf("%d %d", &w, &h);
			
			if (w == -1 && h == -1) {
				wOut = std::max(currW, wOut);
				hOut += maxH;
				printf("%d x %d \n", wOut, hOut);
				break;
			}

			if (currW + w > maxWidth) {
				hOut += maxH;
				wOut = std::max(currW, wOut);
				currW = 0;
				maxH = 0;
			}
			maxH = std::max(maxH, h);
			wOut = std::max(currW, wOut);
			currW += w;
		}
	}
}