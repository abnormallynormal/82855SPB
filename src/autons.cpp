#include "autons.hpp"
#include "devices.hpp"
#include "macros.hpp"
#include <cmath>
void skills()
{
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  // chassis.setPose(-48, 15, 64);
  // index();
  // chassis.moveToPoint(-25, 22.67, 700);
  // chassis.turnToHeading(290, 500);
  // chassis.moveToPoint(-10, 5, 1000, {.forwards = false});
  // chassis.waitUntilDone();
  // firstStage.move(127);
  // secondStage.move(100);
  // pros::delay(1000);
  // chassis.moveToPoint(-43, 44, 1000);
  // index();
  // scraper.toggle();
  // midGoal.toggle();
  // wing.toggle();
  // chassis.turnToHeading(270, 400);
  // chassis.moveToPoint(-70, 44, 3000, {.maxSpeed = 55});
  // chassis.waitUntilDone();
  // chassis.moveToPoint(-44, 45, 1000, {.forwards = false});
  // chassis.turnToHeading(180, 750);
  // chassis.moveToPoint(-40, 58, 1000, {.forwards = false});
  // scraper.toggle();

  // chassis.turnToHeading(270, 1000);
  // // chassis.moveToPoint(-48, 60, 3000);
  // lemlib::Pose temp = chassis.getPose();
  // // // chassis.setPose(-64, 47, temp.theta);
  // // // pros::delay(10);
  // // // chassis.moveToPoint(-40, 60, 1000, {.forwards = false});
  // // chassis.turnToHeading(260, 500);
  // chassis.moveToPoint(44, 53, 2000, {.forwards = false});
  // firstStage.move(0);
  // secondStage.move(0);
  // chassis.turnToHeading(0, 500);
  // chassis.moveToPoint(44, 41.5, 1000, {.forwards = false});
  // chassis.turnToHeading(102, 500);
  // chassis.moveToPoint(22, 41.5, 1000, {.forwards = false});
  // chassis.waitUntilDone();
  // scraper.toggle();
  // score(2400);
  // temp = chassis.getPose();
  // chassis.setPose(24,48,temp.theta);
  // chassis.moveToPoint(72, 45.67, 4000, {.maxSpeed = 55});
  // index();
  // chassis.moveToPoint(22, 47.2, 1000, {.forwards = false});
  // // chassis.waitUntil(48);
  // chassis.waitUntilDone();
  // score(2500);

  // temp = chassis.getPose();
  chassis.setPose(26, 48, 90);
  // scraper.toggle();
  midGoal.toggle();
  chassis.moveToPoint(34, 48, 500);
  chassis.turnToHeading(180, 500);
  chassis.moveToPoint(38, 0, 1000);
  chassis.turnToHeading(90, 400);
  chassis.waitUntilDone();
  index();
  chassis.tank(67, 67);
  pros::delay(400);
  while (std::abs(left_motors.get_actual_velocity()) > 250 && std::abs(right_motors.get_actual_velocity()) > 250)
  {
    pros::delay(10);
  }
  // while (std::abs(left_motors.get_actual_velocity()) < 250 && std::abs(right_motors.get_actual_velocity()) < 250)
  // {
  //   pros::delay(10);
  // }
  chassis.tank(50, 50);
  pros::delay(2000);
  chassis.tank(-35, -35);
  pros::delay(500);
  chassis.tank(35, 35);
  pros::delay(500);
  chassis.tank(-90, -90);
  // controller.print(0, 0, "backing out");

  pros::delay(300);

  while (std::abs(left_motors.get_actual_velocity()) < 600 * 88 / 127 && std::abs(right_motors.get_actual_velocity()) < 600 * 88 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(0, 0);
  pros::delay(250);
  chassis.tank(85, 85);
  // controller.print(0, 0, "going in");

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
  pros::delay(200);
  chassis.tank(25,25);
  pros::delay(300); // Wait for motors to spin up
  while (std::abs(left_motors.get_actual_velocity()) > 600 * 5 / 127 && std::abs(right_motors.get_actual_velocity()) > 600 * 5 / 127)
  {
    pros::delay(10);
  }
  chassis.tank(0, 0);
  pros::delay(100); // Let robot settle
  lemlib::Pose currentPose = chassis.getPose();

  // Read sensors and calculate position
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

  // Use current odometry theta, only correct X and Y from sensors
  chassis.setPose(48, y_position, currentPose.theta);
  pros::delay(100);
  chassis.turnToHeading(215, 1000);
  chassis.moveToPoint(36, -20.67, 1000);
  chassis.turnToHeading(135,500);
  chassis.moveToPoint(14, -8, 1000, {.forwards = false});
  midGoal.toggle();
  chassis.waitUntilDone();
  firstStage.move(127);
  secondStage.move(35);
}