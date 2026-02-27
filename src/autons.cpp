#include "autons.hpp"
#include "devices.hpp"
#include "macros.hpp"
#include <cmath>
void skills()
{
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  chassis.setPose(-48, 15, 64);
  index();
  // get mid goal
  chassis.moveToPoint(-25, 21.5, 700);
  chassis.turnToHeading(290, 500);
  chassis.moveToPoint(-10, 4, 1000, {.forwards = false});
  chassis.waitUntilDone();
  firstStage.move(127);
  secondStage.move(100);
  pros::delay(1000);
  // matchload 1
  chassis.moveToPoint(-43, 44.4, 1000);
  index();
  scraper.toggle();
  midGoal.toggle();
  wing.toggle();
  chassis.turnToHeading(270, 400);
  chassis.moveToPoint(-70, 44.4, 3000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  chassis.moveToPoint(-44, 45, 800, {.forwards = false});
  chassis.turnToHeading(180, 700);
  chassis.moveToPoint(-40, 60, 800, {.forwards = false});
  scraper.toggle();

  chassis.turnToHeading(270, 750);
  lemlib::Pose temp = chassis.getPose();
  // cross
  chassis.moveToPoint(39, 49, 2000, {.forwards = false});
  firstStage.move(0);
  secondStage.move(0);
  chassis.turnToHeading(0, 500);
  chassis.moveToPoint(39, 41.67, 1000, {.forwards = false});
  chassis.turnToHeading(95, 500);
  chassis.moveToPoint(22, 43, 1000, {.forwards = false});
  chassis.waitUntilDone();
  scraper.toggle();
  // score
  score(2400);
  temp = chassis.getPose();
  // matchload
  chassis.setPose(24, 48, temp.theta);
  chassis.moveToPoint(30, 48, 400);
  chassis.turnToHeading(90, 200);
  chassis.moveToPoint(72, 46, 4000, {.maxSpeed = 55});
  index();
  // score
  chassis.moveToPoint(22, 48, 1000, {.forwards = false});
  chassis.waitUntilDone();
  score(2500);
  // align to park
  temp = chassis.getPose();
  chassis.setPose(26, 48, temp.theta);
  scraper.toggle();
  chassis.moveToPoint(34, 48, 500);
  chassis.turnToHeading(180, 500);
  chassis.moveToPoint(38, -2, 1000);
  chassis.turnToHeading(90, 400);
  chassis.waitUntilDone();
  index();
  // go in park
  chassis.tank(67, 67);
  pros::delay(400);
  while (std::abs(left_motors.get_actual_velocity()) > 250 && std::abs(right_motors.get_actual_velocity()) > 250)
  {
    pros::delay(10);
  }
  chassis.tank(50, 50);
  pros::delay(2000);
  chassis.tank(-35, -35);
  pros::delay(500);
  chassis.tank(35, 35);
  pros::delay(500);
  chassis.tank(-90, -90);

  pros::delay(300);

  while (std::abs(left_motors.get_actual_velocity()) < 600 * 88 / 127 && std::abs(right_motors.get_actual_velocity()) < 600 * 88 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(0, 0);
  pros::delay(250);
  chassis.tank(85, 85);
  // rape mech
  pros::delay(700);
  for (int i = 0; i < 6; i++)
  {
    chassis.tank(80, 30);
    pros::delay(150);
    chassis.tank(30, 80);
    pros::delay(150);
    chassis.tank(-80, -80);
    pros::delay(150);
  }
  chassis.tank(-90, -90);
  pros::delay(300);
  while (std::abs(left_motors.get_actual_velocity()) < 600 * 80 / 127 && std::abs(right_motors.get_actual_velocity()) < 600 * 80 / 127)
  {
    pros::delay(10);
  }
  controller.print(0, 0, "resetting");
  pros::delay(200);
  chassis.tank(0, 0);
  pros::delay(400);
  // align for pose reset
  chassis.tank(25, 25);
  pros::delay(300);
  while (std::abs(left_motors.get_actual_velocity()) > 600 * 5 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 5 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(0, 0);
  pros::delay(100); // Let robot settle
  lemlib::Pose currentPose = chassis.getPose();

  // dsr
  int32_t leftDist = left.get_distance();
  int32_t rightDist = right.get_distance();
  double leftDistance = leftDist * 0.0393701 + 3.1875;
  double rightDistance = rightDist * 0.0393701 + 5.6314;
  double heading = currentPose.theta;
  pros::screen::print(TEXT_MEDIUM, 6, "temp heading: %f", heading);
  double heading_rad = heading * M_PI / 180.0;
  double angle_error = heading_rad - M_PI / 2;
  double perpendicular_left = leftDistance * cos(angle_error);
  double perpendicular_right = rightDistance * cos(angle_error);
  double y_from_left = 72.0 - perpendicular_left;
  double y_from_right = -72.0 + perpendicular_right;
  double y_position = (y_from_left + y_from_right) / 2.0;

  controller.print(0, 0, "L:%d R:%d H:%.0f", leftDist, rightDist, heading);
  controller.print(1, 0, "Y:%.1f (%.1f,%.1f)", y_position, y_from_left, y_from_right);

//get one ball
  chassis.setPose(48, y_position, currentPose.theta);
  pros::delay(100);
  chassis.turnToHeading(215, 1000);
  chassis.moveToPoint(34, -23, 1000);
  chassis.turnToHeading(90, 400);
  chassis.moveToPoint(24, -21, 400, {.forwards = false});
  chassis.turnToHeading(135, 1000);
  //score the 7 balls
  chassis.moveToPoint(15, -8, 750, {.forwards = false});
  chassis.waitUntil(12);
  midGoal.toggle();
  chassis.waitUntilDone();
  pros::delay(100);
  firstStage.move(100);
  secondStage.move(35);
  pros::delay(2500);
  index();
  chassis.turnToHeading(140, 200);
  //matchload 3
  chassis.moveToPoint(46, -45.5, 1000);
  chassis.turnToHeading(90, 300);
  midGoal.toggle();
  scraper.toggle();
  chassis.moveToPoint(66, -45, 2500, {.maxSpeed = 55});
  chassis.moveToPoint(42, -45, 1000, {.forwards = false});
  chassis.turnToHeading(0, 500);
  chassis.moveToPoint(42, -60, 750, {.forwards = false});
  chassis.turnToHeading(90, 500);
  //cross
  chassis.moveToPoint(-40, -61, 2500, {.forwards = false});
  chassis.turnToHeading(0, 600);
  chassis.moveToPoint(-40, -51, 750);
  chassis.turnToHeading(270, 500);
  chassis.moveToPoint(-22, -54.5, 1000, {.forwards = false});
  chassis.waitUntilDone();
  //score
  score(2400);
  currentPose = chassis.getPose();
  chassis.setPose(-24, -48, currentPose.theta);
  index();
  //matchload 4
  chassis.moveToPoint(-30, -48, 600);
  chassis.turnToHeading(276, 200);
  chassis.moveToPoint(-70, -44.5, 2500, {.maxSpeed = 55});
  chassis.moveToPoint(-20, -48, 1000, {.forwards = false});
  chassis.waitUntilDone();
  //score
  score(2400);
  scraper.toggle();
  currentPose = chassis.getPose();
  index();
  chassis.setPose(-24, -48, currentPose.theta);
  //get 4 low goal
  chassis.swingToHeading(5, lemlib::DriveSide::RIGHT, 1000);
  chassis.moveToPoint(-18, -20, 2000);
  chassis.waitUntil(8);
  scraper.toggle();
  chassis.waitUntilDone();
  chassis.turnToHeading(50, 400);
  scraper.toggle();
  //score low goal
  chassis.moveToPoint(-2, -4, 1000);
  chassis.waitUntilDone();
  intakeLift.toggle();
  firstStage.move(-60);
  secondStage.move(-127);
  pros::delay(1000);
  intakeLift.toggle();
  //park align
  chassis.turnToHeading(50, 400);
  chassis.moveToPoint(-40, -18, 1000, {.forwards = false});
  index();
  chassis.waitUntilDone();
  pros::delay(2000);
  chassis.swingToHeading(350, lemlib::DriveSide::RIGHT, 600);
  chassis.waitUntilDone();
  pros::delay(1000);
  //clear park and end
  chassis.tank(80, 80);
  pros::delay(100);
  scraper.toggle();
  while (std::abs(left_motors.get_actual_velocity()) > 600 * 70 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 70 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(67, 67);
  pros::delay(400);
  chassis.tank(0, 0);
}