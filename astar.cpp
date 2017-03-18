#include <iostream>
#include <stdlib.h>

#include "AStar.h"

int main(int argc, const char **argv) {

    const unsigned char map[] = {
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','1','1','1','0','0','0','0','0','0',
        '0','1','0','0','1','0','0','0','0','0',
        '0','1','0','0','0','1','0','0','0','0',
        '0','0','0','0','0','0','1','0','0','0',
        '0','0','0','1','1','1','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0',
        '0','0','0','0','0','0','0','0','0','0'
    };

    const int startx  = 2;
    const int starty = 4;

    const int targetx = 5;
    const int targety = 3;

    const int mapWidth = 10;
    const int mapHeight = 10;

    int outBuffer[50] = {};

    const int outBufferSize = 50;

    FindPath(startx, starty, targetx, targety, map, mapWidth, mapHeight, outBuffer, outBufferSize);

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
        getNewOpenNodes(currX, currY, parents, open, closed, nMapWidth, nMapHeight, pMap);
    }

    return 0;
}

void getNewOpenNodes(int x, int y, int *parents, bool *open, bool *closed, int xMax, int yMax, const unsigned char *map) {

    int maxLength = xMax * yMax;

    int nodeRight = toIndex(x + 1, y, yMax);
    if(nodeRight <= maxLength && x + 1 < xMax && map[nodeRight] == 0 && !closed[nodeRight]) {
        open[nodeRight] = true;
    }

    int nodeLeft = toIndex(x - 1, y, yMax);
    if(nodeLeft > -1 && x - 1 > -1 && map[nodeLeft] == 0 && !closed[nodeLeft]) {
        open[nodeLeft] = true;
    }

    int nodeUp = toIndex(x, y - 1, yMax);
    if(nodeUp > -1 && y - 1 > -1 && map[nodeUp] == 0 && !closed[nodeUp]) {
        open[nodeUp] = true;
    }

    int nodeDown = toIndex(x, y + 1, yMax);
    if(y <= maxLength && y + 1 > -1 && map[nodeDown] == 0 && !closed[nodeDown]) {
        open[nodeDown] = true;
    }
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