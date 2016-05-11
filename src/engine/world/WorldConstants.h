#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

const float MU_GROUND = 20.5;
const float MU_AIR = 2.5;

const float JUMP_HEIGHT = 0.0009;
const float JUMP_TIME = 0.8;
const float G = -(2 * JUMP_HEIGHT) / (JUMP_TIME * JUMP_TIME);
const float JUMP_SPEED = (JUMP_HEIGHT - 0.5 * G * JUMP_TIME * JUMP_TIME) / JUMP_TIME;

#endif // WORLDCONSTANTS_H
