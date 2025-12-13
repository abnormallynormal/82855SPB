#include "autons.hpp"
#include "devices.hpp"
void right_side_22()
{
  chassis.setPose(-46, -13, 180);
  chassis.moveToPoint(-45.5, -48.5, 1200, {.maxSpeed = 60});
  chassis.turnToHeading(270, 500);
  scraper.toggle();
  firstStage.move(127);
  chassis.moveToPoint(-70, -48.5, 1200, {.maxSpeed = 70});
  chassis.tank(127, 127);
  pros::delay(700);
  chassis.tank(0, 0);
  chassis.moveToPoint(-24, -48, 1500, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  for (int i = 0; i < 50; i++)
  {
    
    firstStage.move(127);
    secondStage.move(127);
    pros::delay(50);
    if (secondStage.get_actual_velocity() < 100 || firstStage.get_actual_velocity() < 100)
    {
      secondStage.move(-127);
      firstStage.move(-127);
      pros::delay(50);
    }
    
  }
  chassis.tank(-30,-30);
  pros::delay(250);
  chassis.tank(0,0);
  chassis.setPose(-24, -48, 270);
  chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 1000);
  chassis.moveToPoint(-24, -37.5, 1200, {.maxSpeed = 60});
  chassis.turnToHeading(270, 1000);
  wing.toggle();
  chassis.moveToPoint(-4, -37.5, 1200, {.forwards = false, .maxSpeed = 60});
}
void left_side_22()
{
  chassis.setPose(-46, 13, 0);
  chassis.moveToPoint(-45.5, 46, 1200, {.maxSpeed = 60});
  chassis.turnToHeading(270, 500);
  scraper.toggle();
  firstStage.move(127);
  pros::delay(750);
  chassis.moveToPoint(-90, 46, 1000, {.maxSpeed = 70});
  chassis.tank(127, 127);
  pros::delay(700);
  chassis.tank(0, 0);
  chassis.moveToPoint(-20, 48, 1500, {.forwards = false, .maxSpeed = 60});
  chassis.waitUntilDone();
  chassis.tank(-127,-127);
  secondStage.move(127);
  pros::delay(600);
  firstStage.move(-127);
  secondStage.move(-127);
  pros::delay(200);
  firstStage.move(127);
  secondStage.move(127);
  pros::delay(3000);
  
  chassis.tank(30,30);
  pros::delay(300);
  chassis.tank(0,0);
  chassis.setPose(-24, 48, 270);
  scraper.toggle();
  // chassis.swingToHeading(180, lemlib::DriveSide::LEFT, 1000);
  // chassis.moveToPoint(-26, 36, 1200, {.maxSpeed = 60});
  // chassis.turnToHeading(105, 1000);
  // wing.toggle();
  // chassis.moveToPoint(-1, 33, 1200, { .maxSpeed = 60});
  chassis.turnToHeading(300, 500);
  chassis.moveToPoint(-48, 60, 1000, {.maxSpeed = 60});
  chassis.turnToHeading(270, 500);
  chassis.moveToPoint(-26, 63, 1000, {.forwards = false, .maxSpeed = 60});
  wing.toggle();
  chassis.turnToHeading(290, 1000);
  chassis.moveToPoint(-2, 58, 1000, {.forwards = false});
}
// void centre_long_29(){
//   chassis.setPose(-51.703, 11, 90);
//   chassis.turnToHeading(85, 300);
//   firstStage.move(127);
//   chassis.moveToPoint(-4, 22, 1600, {.maxSpeed = 40});
//   chassis.moveToPoint(-30,22, 1000, {.forwards = false, .maxSpeed = 60});
//   chassis.turnToHeading(315,1000);
//   chassis.moveToPoint(-2,-2, 1000, {.forwards = false, .maxSpeed = 60});
//   chassis.waitUntilDone();
//   bypass.toggle();
//   // chassis.tank(-20,-20);
//   pros::delay(2000);
//   // chassis.tank(0,0);
//   bypass.toggle();
//   chassis.tank(30,30);
//   pros::delay(250);
//   chassis.tank(0, 0);
//   chassis.setPose(-2, 2, 315);
//   chassis.moveToPoint(-38,48, 1500, {.maxSpeed  = 70});
//   chassis.turnToHeading(300, 500);
//   scraper.toggle();
//   chassis.moveToPoint(-70, 48, 1500, {.maxSpeed = 70});
//   chassis.tank(127, 127);
//   pros::delay(1200);
//   chassis.tank(0, 0);
//   chassis.moveToPoint(-12, 48, 1500, {.forwards = false, .maxSpeed = 60});
//   chassis.waitUntilDone();
//   for (int i = 0; i < 50; i++)
//   {

//     firstStage.move(127);
//     secondStage.move(127);
//     pros::delay(50);
//     if (secondStage.get_actual_velocity() < 100 || firstStage.get_actual_velocity() < 100)
//     {
//       secondStage.move(-127);
//       firstStage.move(-127);
//       pros::delay(50);
//     }
//   }
// }