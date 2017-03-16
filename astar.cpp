#include <iostream>
#include <stdlib.h>

#include "AStar.h"

int main(int argc, const char **argv) {
	
	return 0;
}

int FindPath(const int nStartX, const int nStartY,
        const int nTargetX, const int nTargetY,
        const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
        int *pOutBuffer, const int nOutBufferSize) {

	int mapLength = nMapWidth * nMapHeight;

	// opened and closed nodes
	bool open[mapLength];
	bool closed[mapLength];

	int hVals[mapLength];
	int gVals[mapLength];
	int fVals[mapLength];
	int parents[mapLength];

	int currX;
	int currY;

	for(int i=0; i<mapLength; i++) {
		open[i] = false;
		closed[i] = false;

		parents[i] = -1;
		hVals[i] = 0;
		gVals[i] = 0;
		fVals[i] = 0;
	}

	while(currX != nTargetX or currY != nTargetY) {
		int currNode = toIndex(currX, currY, nMapWidth);
	}

    return 0;
}

int ManhattenDist(int sx, int sy, int tx, int ty) {
    return abs(sx - tx) + abs(sy - ty);
}

int indexToX(int i, int xMax) {
	return i % xMax;
}

int indexToY(int i, int xMax) {
	return i / xMax;
}

int toIndex(int x, int y, int xMax) {
	return x + (y * xMax);
}
