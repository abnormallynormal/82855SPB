#include "main.h"
#include "devices.hpp"
#include "autons.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
  pros::lcd::initialize();
  chassis.setPose(0, 0, 0);
  left_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
  right_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
  chassis.calibrate();
  pros::delay(10);
  pros::Task show_pos([&]()
                      {
    while(true) {
      pros::screen::print(TEXT_MEDIUM, 0, "X: %f", chassis.getPose().x);
      pros::screen::print(TEXT_MEDIUM, 1, "Y: %f", chassis.getPose().y);
      pros::screen::print(TEXT_MEDIUM, 2, "Theta: %f", chassis.getPose().theta);
      pros::screen::print(TEXT_MEDIUM, 3, "Left motor 1: %f ", left_motors.get_position_all()[0]);
      pros::screen::print(TEXT_MEDIUM, 4, "Left motor 2: %f ", left_motors.get_position_all()[1]);
      pros::screen::print(TEXT_MEDIUM, 5, "Left motor 3: %f ", left_motors.get_position_all()[2]);
      pros::screen::print(TEXT_MEDIUM, 6, "right motor 1: %f ", right_motors.get_position_all()[0]);
      pros::screen::print(TEXT_MEDIUM, 7, "right motor 2: %f ", right_motors.get_position_all()[1]);
      pros::screen::print(TEXT_MEDIUM, 8, "right motor 3: %f ", right_motors.get_position_all()[2]);
      pros::delay(20);
    } });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  chassis.setPose(0,0,0);
  chassis.moveToPoint(0,24,2500);
  chassis.moveToPoint(0,0, 2500, {.forwards = false});
  chassis.moveToPoint(0,24,2500);
  chassis.moveToPoint(0,0, 2500, {.forwards = false});
  // solo_awp();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
  pros::Controller controller(pros::E_CONTROLLER_MASTER);
  odomLift.toggle();
  bool bypassDown = false;
  while (true)
  {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    // move the robot
    chassis.arcade(leftY, rightX);
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      firstStage.move(127);
      if (bypassDown)
      {
        secondStage.move(-127);
      }
      else
      {
        secondStage.move(127);
      }
      // pros::delay(100);
      // if (firstStage.get_actual_velocity() < 100 || secondStage.get_actual_velocity() < 100)
      // {
      //   firstStage.move(-127);
      //   secondStage.move(-127);
      //   pros::delay(50);
      // }
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
      firstStage.move(-127);
      secondStage.move(-127);
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
      firstStage.move(127);
      // pros::delay(100);
      // if(firstStage.get_actual_velocity() < 100){
      //   firstStage.move(-127);

      //   pros::delay(50);
      // }
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
      firstStage.move(-127);
    }
    else
    {
      firstStage.move(0);
      secondStage.move(0);
    }

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    {
      wing.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    {
      scraper.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
      odomLift.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
      bypass.toggle();
      bypassDown = !bypassDown;
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
      park.toggle();
    }
    pros::delay(20);
  }
}