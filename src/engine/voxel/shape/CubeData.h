#ifndef CUBEDATA_H
#define CUBEDATA_H

float leftFaceData[] = {
    -0.5, -0.5, -0.5,   -1, 0, 0,    0, 0,
    -0.5, -0.5, 0.5,    -1, 0, 0,    1, 0,
    -0.5, 0.5, -0.5,    -1, 0, 0,    0, 1,

    -0.5, -0.5, 0.5,    -1, 0, 0,    1, 0,
    -0.5, 0.5, 0.5,     -1, 0, 0,    1, 1,
    -0.5, 0.5, -0.5,    -1, 0, 0,    0, 1
};

float rightFaceData[] = {
    0.5, -0.5, -0.5,    1, 0, 0,     1, 0,
    0.5, 0.5, -0.5,     1, 0, 0,     1, 1,
    0.5, -0.5, 0.5,     1, 0, 0,     0, 0,

    0.5, -0.5, 0.5,     1, 0, 0,     0, 0,
    0.5, 0.5, -0.5,     1, 0, 0,     1, 1,
    0.5, 0.5, 0.5,      1, 0, 0,     0, 1
};

float botFaceData[] = {
    -0.5, -0.5, -0.5,   0, -1, 0,    0, 0,
    0.5, -0.5, -0.5,    0, -1, 0,    1, 0,
    -0.5, -0.5, 0.5,    0, -1, 0,    0, 1,

    0.5, -0.5, -0.5,    0, -1, 0,    1, 0,
    0.5, -0.5, 0.5,     0, -1, 0,    1, 1,
    -0.5, -0.5, 0.5,    0, -1, 0,    0, 1
};

float topFaceData[] = {
    -0.5, 0.5, -0.5,    0, 1, 0,     0, 1,
    -0.5, 0.5, 0.5,     0, 1, 0,     0, 0,
    0.5, 0.5, -0.5,     0, 1, 0,     1, 1,

    0.5, 0.5, -0.5,     0, 1, 0,     1, 1,
    -0.5, 0.5, 0.5,     0, 1, 0,     0, 0,
    0.5, 0.5, 0.5,      0, 1, 0,     1, 0
};

float backFaceData[] = {
    -0.5, -0.5, -0.5,   0, 0, 1,     1, 0,
    -0.5, 0.5, -0.5,    0, 0, 1,     1, 1,
    0.5, -0.5, -0.5,    0, 0, 1,     0, 0,

    0.5, -0.5, -0.5,    0, 0, 1,     0, 0,
    -0.5, 0.5, -0.5,    0, 0, 1,     1, 1,
    0.5, 0.5, -0.5,     0, 0, 1,     0, 1
};

float frontFaceData[] = {
    -0.5, -0.5, 0.5,    0, 0, 1,     0, 0,
    0.5, -0.5, 0.5,     0, 0, 1,     1, 0,
    -0.5, 0.5, 0.5,     0, 0, 1,     0, 1,

    0.5, -0.5, 0.5,     0, 0, 1,     1, 0,
    0.5, 0.5, 0.5,      0, 0, 1,     1, 1,
    -0.5, 0.5, 0.5,     0, 0, 1,     0, 1
};

#endif // CUBEDATA_H