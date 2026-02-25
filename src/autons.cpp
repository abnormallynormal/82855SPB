#include "autons.hpp"
#include "devices.hpp"
#include "macros.hpp"
void skills()
{
  // pros::Controller controller(pros::E_CONTROLLER_MASTER);

  chassis.setPose(-48, 15, 64);
  index();
  chassis.moveToPoint(-25, 22.67, 700);
  chassis.turnToHeading(290, 500);
  chassis.moveToPoint(-10, 5, 1000, {.forwards = false});
  chassis.waitUntilDone();
  firstStage.move(127);
  secondStage.move(100);
  pros::delay(1000);
  chassis.moveToPoint(-43, 44, 1000);
  index();
  scraper.toggle();
  midGoal.toggle();
  wing.toggle();
  chassis.turnToHeading(270, 400);
  chassis.moveToPoint(-70, 44, 3000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  chassis.moveToPoint(-44, 45, 1000, {.forwards = false});
  chassis.turnToHeading(180, 750);
  chassis.moveToPoint(-40, 56.23, 1000, {.forwards = false});
  scraper.toggle();

  chassis.turnToHeading(270, 1000);
  // chassis.moveToPoint(-48, 60, 3000);
  lemlib::Pose temp = chassis.getPose();
  // // chassis.setPose(-64, 47, temp.theta);
  // // pros::delay(10);
  // // chassis.moveToPoint(-40, 60, 1000, {.forwards = false});
  // chassis.turnToHeading(260, 500);
  chassis.moveToPoint(44, 51.2, 2000, {.forwards = false});
  firstStage.move(0);
  secondStage.move(0);
  chassis.turnToHeading(0, 500);
  chassis.moveToPoint(44, 40, 1000, {.forwards = false});
  chassis.turnToHeading(102, 500);
  chassis.moveToPoint(22, 40, 1000, {.forwards = false});
  chassis.waitUntilDone();
  scraper.toggle();
  score(2400);
  temp = chassis.getPose();
  chassis.setPose(24,48,temp.theta);
  chassis.moveToPoint(72, 45.67, 4000, {.maxSpeed = 55});
  index();
  chassis.moveToPoint(22, 47.2, 1000, {.forwards = false});
  // chassis.waitUntil(48);
  chassis.waitUntilDone();
  score(2500);



  temp = chassis.getPose();
  chassis.setPose(26, 48, temp.theta);
  scraper.toggle();
  chassis.moveToPoint(34, 48, 500);
  chassis.turnToHeading(180, 500);
  chassis.moveToPoint(38, -0.5, 1000);
  chassis.turnToHeading(90, 500);
  chassis.waitUntilDone();
  index();
  chassis.tank(67, 67);
  pros::delay(1000);
  chassis.tank(42,42);
  // while (std::abs(left_motors.get_actual_velocity()) > 600 * 100 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 100 / 127)
  // {
  //   pros::delay(10);
  // }
  // while (std::abs(left_motors.get_actual_velocity()) > 600 * 100 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 100 / 127)
  // {
  //   pros::delay(10);
  // }
  pros::delay(2000);
  chassis.tank(-90, -90);
  pros::delay(300);
  chassis.tank(0,0);
  pros::delay(150);
  while (std::abs(left_motors.get_actual_velocity()) < 600 * 95 / 127 && std::abs(right_motors.get_actual_velocity()) < 600 * 95 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(67, 67);
  pros::delay(700);
  for(int i = 0;i<7;i++){
    chassis.tank(80,30);
    pros::delay(150);
    chassis.tank(30,80);
    pros::delay(150);
    chassis.tank(-80,-80);
    pros::delay(150);
  }
  chassis.tank(-90, -90);
  pros::delay(400);
  while (std::abs(left_motors.get_actual_velocity()) < 600 * 65 / 127 && std::abs(right_motors.get_actual_velocity()) < 600 * 65 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(0,0);
}