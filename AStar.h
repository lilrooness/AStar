#ifndef ASTAR_H
#define ASTAR_H

int FindPath(const int nStartX, const int nStartY,
        const int nTargetX, const int nTargetY,
        const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
        int *pOutBuffer, const int nOutBufferSize);

int ManhattenDist(int sx, int sy, int tx, int ty);

int indexToX(int i, int xMax);

int indexToY(int i, int xMax);

int toIndex(int x, int y, int xMax);

void getNewOpenNodes(int x, int y, int *parents, bool *open, bool *closed, int xMax, int yMax, const unsigned char *map);

#endif
