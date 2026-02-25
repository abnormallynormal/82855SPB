#include "devices.hpp"
#include "macros.hpp"
void index(){
  firstStage.move(127);
  secondStage.move(-127);
}

void score(int timeout){
  firstStage.move(127);
  secondStage.move(127);
  pros::delay(timeout);
  firstStage.move(0);
  secondStage.move(0);
}