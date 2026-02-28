#include "autons.hpp"
#include "devices.hpp"
#include "macros.hpp"
#include <cmath>
void skills()
{
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  chassis.setPose(-48, 15, 64);
  index();
  // get 1 ball to score in mid goal
  chassis.moveToPoint(-25, 21.5, 700);
  chassis.turnToHeading(300, 500);
  chassis.moveToPoint(-12, 5.2, 800, {.forwards = false});
  pros::delay(400);
  firstStage.move(127);
  secondStage.move(50);
  pros::delay(600);
  // go to matchload 1
  chassis.moveToPoint(-43, 41.5, 1000);
  index();
  pros::delay(200);
  scraper.toggle();
  midGoal.toggle();
  wing.toggle();
  chassis.turnToHeading(270, 400);
  //matchload
  chassis.moveToPoint(-70, 41.5, 2000, {.maxSpeed = 55});
  chassis.waitUntilDone();
  // cross to other side
  chassis.moveToPoint(-44, 41.5, 600, {.forwards = false});
  chassis.turnToHeading(245, 1000);
  chassis.moveToPoint(-22, 54, 600, {.forwards = false});
  scraper.toggle();

  chassis.turnToHeading(275, 500);
  lemlib::Pose temp = chassis.getPose();
  
  chassis.moveToPoint(38, 51, 1800, {.forwards = false, .maxSpeed = 80});
  firstStage.move(0);
  secondStage.move(0);
  //begin aligning to long goal
  chassis.turnToHeading(315, 1000);
  chassis.moveToPoint(46, 42, 650, {.forwards = false}); //was 42
  chassis.turnToHeading(90, 800);
  chassis.moveToPoint(22, 46, 800, {.forwards = false});
  chassis.waitUntilDone();
  scraper.toggle();
  // score on long goal
  score(2000);
  temp = chassis.getPose();
  // matchload 2
  chassis.setPose(24, 48, temp.theta);
  chassis.moveToPoint(30, 48, 400);
  chassis.turnToHeading(100, 200);
  chassis.moveToPoint(72, 44.5, 2500, {.maxSpeed = 55});
  index();
  // score on long goal
  chassis.moveToPoint(22, 47, 1000, {.forwards = false});
  chassis.waitUntilDone();
  score(2000);
  // align to park
  temp = chassis.getPose();
  chassis.setPose(26, 48, temp.theta);
  firstStage.move(127);
  secondStage.move(127);
  scraper.toggle();
  chassis.moveToPoint(34, 48, 500);
  chassis.turnToHeading(180, 500);
  chassis.moveToPoint(34, -2.5, 1000);
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
  chassis.tank(55,55);
  pros::delay(1000); // was 2000
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
  for (int i = 0; i < 5; i++) // was 6
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

//get one ball to score in mid goal
  chassis.setPose(48, y_position, currentPose.theta);
  pros::delay(100);
  chassis.turnToHeading(215, 700);
  chassis.moveToPoint(31, -20.3, 1000);
  chassis.turnToHeading(90, 400);
  //align with mid goal
  chassis.moveToPoint(22, -23, 400, {.forwards = false});
  chassis.turnToHeading(135, 500);
  //score the 7 balls
  pros::delay(300);
  midGoal.toggle();

  chassis.moveToPoint(13.5, -7, 750, {.forwards = false});
  // chassis.waitUntil(2); // was 12
  // pros::delay(300);
  // chassis.waitUntilDone();
  pros::delay(300);
  firstStage.move(100);
  secondStage.move(35);
  pros::delay(3000);
  // chassis.moveToPoint(20, -12, 500);
  // chassis.moveToPoint(15, -8, 500, {.forwards = false});
  index();
  chassis.turnToHeading(140, 200);
  //go to matchload 3
  chassis.moveToPoint(46, -42, 1000);
  chassis.waitUntil(8);
  firstStage.move(127);
  secondStage.move(127);
  chassis.turnToHeading(90, 300);
  midGoal.toggle();
  scraper.toggle();
  //matchload
  index();
  chassis.moveToPoint(66, -42, 2500, {.maxSpeed = 55});
  //prepare to cross
  chassis.moveToPoint(46, -44, 700, {.forwards = false});
  chassis.turnToHeading(60, 800);
  scraper.toggle();
  chassis.moveToPoint(26, -62, 600, {.forwards = false});
  chassis.turnToHeading(90, 500);
  //cross
  chassis.moveToPoint(-30, -60, 1500, {.forwards = false});
  //begin aligning to long goal 2
  chassis.turnToHeading(225, 600);
  chassis.moveToPoint(-36, -50, 750, {.forwards = false});
  chassis.turnToHeading(270, 500);
  chassis.moveToPoint(-22, -52, 700, {.forwards = false});
  chassis.waitUntilDone();
  //score on long goal
  scraper.toggle();
  score(1600);
  currentPose = chassis.getPose();
  chassis.setPose(-24, -48, currentPose.theta);
  index();
  //matchload 4
  chassis.moveToPoint(-30, -48, 600);
  chassis.turnToHeading(276, 200);
  chassis.moveToPoint(-70, -46, 2500, {.maxSpeed = 50});
  chassis.moveToPoint(-20, -48, 700, {.forwards = false});
  // chassis.waitUntilDone();
  pros::delay(500);
  //score on long goal
  score(1600);
  scraper.toggle();
  currentPose = chassis.getPose();
  index();
  chassis.setPose(-24, -48, currentPose.theta);
  //align to park
  chassis.swingToHeading(305, lemlib::DriveSide::RIGHT, 500);
  chassis.moveToPoint(-52, -24, 1000);
  index();
  chassis.swingToHeading(348, lemlib::DriveSide::RIGHT, 600);
  chassis.waitUntilDone();
  //clear park and end
  chassis.tank(90, 90);
  scraper.toggle();
  pros::delay(400);
  while (std::abs(left_motors.get_actual_velocity()) > 600 * 60 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 60 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(67, 67);
  pros::delay(550);
  chassis.tank(0, 0);
}