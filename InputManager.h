#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
struct InputManager
{
   enum playerMode{
      DEFEND = 1,
      ATTACK = 2
   }mode;
   unsigned int width;
   unsigned int height;
   unsigned int iteration;
   unsigned int counter;
};
#endif