#include "autons.hpp"
#include "devices.hpp"
void right_side(){
  chassis.setPose(-50, -10, 120);
  chassis.moveToPoint(-12,-30,1200);
  firstStage.move(127);
  chassis.waitUntil(15);
  scraper.toggle();
  chassis.turnToHeading(245,750);
  chassis.moveToPoint(-44,-49.5,1000);
  chassis.turnToHeading(280,500);
  chassis.moveToPoint(-74, -49.25, 1400, {.maxSpeed=55});
  chassis.moveToPoint(-24,-50.5, 1200, {.forwards = false});
  chassis.waitUntilDone();
  secondStage.move(127);
  pros::delay(400);
  firstStage.move(-127);
  secondStage.move(-127);
  pros::delay(200);
  scraper.toggle();
  firstStage.move(127);
  secondStage.move(127);
  pros::delay(1750);
  chassis.tank(60,60);
  pros::delay(200);
  chassis.tank(0,0);
  chassis.turnToHeading(345, 400);
  chassis.moveToPoint(-27,-33.75, 600);
  chassis.turnToHeading(310,500);
  chassis.moveToPoint(-10,-41,400, {.forwards = false});
  wing.toggle();
  chassis.moveToPoint(-10,-40.5,500, {.forwards= false, .maxSpeed=80});
  
}
void right_side_fucked()
{
  chassis.setPose(-50, -10, 120);
  chassis.moveToPoint(-12, -32, 1200);
  firstStage.move(127);
  chassis.waitUntil(15);
  scraper.toggle();
  chassis.turnToHeading(245, 750);
  chassis.moveToPoint(-44, -49.5, 1000);
  chassis.turnToHeading(280, 500);
  chassis.moveToPoint(-74, -50, 1400, {.maxSpeed = 55});
  chassis.moveToPoint(-24, -52.5, 1200, {.forwards = false});
  chassis.waitUntilDone();
  secondStage.move(127);
  pros::delay(400);
  firstStage.move(-127);
  secondStage.move(-127);
  pros::delay(200);
  scraper.toggle();
  firstStage.move(127);
  secondStage.move(127);
  pros::delay(1750);
  chassis.tank(60, 60);
  pros::delay(200);
  chassis.tank(0, 0);
  chassis.turnToHeading(345, 400);
  chassis.moveToPoint(-27, -36, 600);
  chassis.turnToHeading(310, 500);
  chassis.moveToPoint(-10, -43.5, 400, {.forwards = false});
  wing.toggle();
  chassis.moveToPoint(-10, -42.5, 500, {.forwards = false, .maxSpeed = 80});
}
void left_side(){
  chassis.setPose(-50, 10, 60);
  chassis.moveToPoint(-12,30,1200);
  firstStage.move(127);
  chassis.waitUntil(15);
  scraper.toggle();
  chassis.turnToHeading(300,750);
  chassis.moveToPoint(-44,49.5,1000);
  chassis.turnToHeading(270,250);
  chassis.moveToPoint(-75, 49.5, 1400, {.maxSpeed=60});
  chassis.moveToPoint(-24,56, 1200, {.forwards = false});
  chassis.waitUntilDone();
  secondStage.move(127);
  pros::delay(400);
  firstStage.move(-127);
  secondStage.move(-127);
  pros::delay(200);
  scraper.toggle();
  firstStage.move(127);
  secondStage.move(127);
  pros::delay(1750);
  chassis.tank(60,60);
  pros::delay(200);
  chassis.tank(0,0);
  chassis.turnToHeading(350, 400);
  chassis.moveToPoint(-40,72, 600);
  chassis.turnToHeading(260,500);
  chassis.moveToPoint(-10,68,400, {.forwards = false});
  wing.toggle();
  chassis.moveToPoint(-7.5,69,500, {.forwards= false, .maxSpeed=80});
  
}