#include <iostream>
#include <stdlib.h>

#include "AStar.h"

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

    bool toCheck[mapLength];

    int currX = nStartX;
    int currY = nStartY;

    for(int i=0; i<mapLength; i++) {
        open[i] = false;
        closed[i] = false;

        parents[i] = -1;
        hVals[i] = 0;
        gVals[i] = 0;
        fVals[i] = 0;
        toCheck[i] = false;
    }

    int currNode = toIndex(currX, currY, nMapWidth);
    hVals[currNode] = ManhattenDist(nStartX, nStartY, nTargetX, nTargetY);
    gVals[currNode] = 0;

    int counter = 0;

    while(currX != nTargetX or currY != nTargetY) {
        // currNode = toIndex(currX, currY, nMapWidth);
        getNewOpenNodes(currX, currY, parents, open, closed, nMapWidth, nMapHeight, pMap, toCheck);

        // for each open node, recalculate/calculate parent value
        for(int i=0; i<nMapHeight * nMapWidth; i++) {
            int openx = indexToX(i, nMapWidth);
            int openy = indexToY(i, nMapWidth);
            if(open[i] == true && closed[i] == false) {
                // new open nodes automatically get parented to current node
                // gets new gVal & hVal
                if(parents[i] == -1 && toCheck[i] == true) {
                    toCheck[i] = false;
                    parents[i] = currNode;
                    hVals[i] = ManhattenDist(openx, openy, nTargetX, nTargetY);
                    gVals[i] = gVals[currNode] + 10;
                    fVals[i] = gVals[i] + hVals[i];
                } else if(toCheck[i] == true) {
                    toCheck[i] = false;
                    // revisited old open nodes get checked for new parent value
                    int newGVal = gVals[currNode] + 10;
                    if(newGVal < gVals[i]) {
                        parents[i] = currNode;
                        gVals[i] = newGVal;
                        fVals[i] = gVals[i] + hVals[i];
                    }
                }
            }
        }

        currNode = getBestOpenNodeIndex(open, fVals, nMapWidth * nMapHeight);
        open[currNode] = false;
        closed[currNode] = true;
        currX = indexToX(currNode, nMapWidth);
        currY = indexToY(currNode, nMapWidth);
        counter ++;
    }

    int pathLength = 0;
    int startNode = toIndex(nStartX, nStartY, nMapWidth);
    int targetNode = toIndex(nTargetX, nTargetY, nMapWidth);
    currNode = targetNode;

    while(currNode != startNode) {
        pathLength ++;
        currNode = parents[currNode];
    }

    int reversePath[pathLength];

    //place in reverse order array
    currNode = targetNode;
    for(int i=0; i<pathLength ; i++) {
        reversePath[i] = currNode;
        currNode = parents[currNode];
    }

    //place in proper order in pOutBuffer
    for(int i=0; i<pathLength; i++) {
        if(nOutBufferSize > i) {
            pOutBuffer[i] = reversePath[pathLength - 1 - i];
        }
    }

    return pathLength;
}

int getBestOpenNodeIndex(bool *open, int *fVals, int length) {

    int minIndex = -1;
    int minValue;


    for(int i=0; i<length; i++) {
        if(open[i] == true) {
            if(minIndex == -1) {
                minIndex = i;
                minValue = fVals[i];
            } else {
                if(minValue > fVals[i]) {
                    minIndex = i;
                    minValue = fVals[i];
                }
            }
        }
    }

    return minIndex;
}

void getNewOpenNodes(int x, int y, int *parents, bool *open, bool *closed, int xMax, int yMax, const unsigned char *map, bool *toCheck) {

    int maxLength = xMax * yMax;

    int nodeRight = toIndex(x + 1, y, yMax);
    if(nodeRight < maxLength && x + 1 < xMax && map[nodeRight] == '0' && !closed[nodeRight]) {
        toCheck[nodeRight] = true;
        open[nodeRight] = true;
    }

    int nodeLeft = toIndex(x - 1, y, yMax);
    if(nodeLeft > -1 && x - 1 > -1 && map[nodeLeft] == '0' && !closed[nodeLeft]) {
        toCheck[nodeLeft] = true;
        open[nodeLeft] = true;
    }

    int nodeUp = toIndex(x, y - 1, yMax);
    if(nodeUp > -1 && y - 1 > -1 && map[nodeUp] == '0' && !closed[nodeUp]) {
        toCheck[nodeUp] = true;
        open[nodeUp] = true;
    }

    int nodeDown = toIndex(x, y + 1, yMax);
    if(nodeDown < maxLength && y + 1 > -1 && map[nodeDown] == '0' && !closed[nodeDown]) {
        toCheck[nodeDown] = true;
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
