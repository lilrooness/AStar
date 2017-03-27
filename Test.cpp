#include <iostream>
#include <stdlib.h>

#include "Test.h"

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

    int pathLength  = FindPath(startx, starty, targetx, targety, map, mapWidth, mapHeight, outBuffer, outBufferSize);

    int mapSize = mapWidth * mapHeight;
    for(int i=0; i<mapSize; i++) {
        if(i%mapWidth == 0) {
            std::cout<<std::endl;
        }
        if(isIn(i, outBuffer, pathLength)) {
            std::cout<<"#"<< ",";
        } else {
            std::cout<<map[i] << ",";
        }
    }

    return 0;
}

bool isIn(int value, int *array, int arraySize) {
    for(int i=0; i<arraySize; i++) {
        if(array[i] == value) {
            return true;
        }
    }

    return false;
}
