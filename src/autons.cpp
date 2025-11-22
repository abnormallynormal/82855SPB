#include "autons.hpp"
#include "devices.hpp"

void right_centre()
{
  chassis.setPose(-51.703, -11.825, 90);
  chassis.turnToHeading(95, 300);

  chassis.moveToPoint(-17, -24.5, 1600, {.maxSpeed = 45});
  pros::delay(350);
  intake.move(120);
  chassis.waitUntilDone();
  pros::delay(300);
  intake.move(0);

  chassis.moveToPoint(-28, -21.5, 600, {.forwards = false, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 5});

  chassis.turnToHeading(62, 500, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 5});
  chassis.moveToPoint(-14, -9, 1000, {.maxSpeed = 80});

  chassis.waitUntilDone();
  chassis.tank(-30, -30);
  pros::delay(80);
  chassis.tank(0, 0);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
  intake.move(-90);
  pros::delay(1250);
  intake.move(100);
  pros::delay(250);
}
void left_centre()
{
  chassis.setPose(-51.703, 11.825, 90);
  chassis.turnToHeading(85, 300);

  chassis.moveToPoint(-16, 24, 1600, {.maxSpeed = 45});
  pros::delay(300);
  intake.move(120);
  chassis.waitUntilDone();
  pros::delay(300);
  intake.move(0);

  chassis.moveToPoint(-27, 23, 600, {.forwards = false, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 5});

  chassis.turnToHeading(115, 500, {.direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 80, .minSpeed = 60, .earlyExitRange = 5});
  chassis.moveToPoint(-13, 10, 1000, {.maxSpeed = 80});
  hood.toggle();
  scraper.toggle();
  chassis.waitUntilDone();
  chassis.tank(-40, -40);
  pros::delay(100);
  chassis.tank(0, 0);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
  intake.move(105);
  pros::delay(1250);
  intake.move(-100);
  pros::delay(250);
}