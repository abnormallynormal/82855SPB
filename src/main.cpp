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
  // chassis.setPose(0, 0,/ 0);
  left_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
  right_motors.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
  chassis.calibrate();
  imu.set_data_rate(5);
  // pros::delay(2000);  // Wait for IMU calibration to complete
  chassis.setPose(24,48,90);
  pros::Task show_pos([&]()
                      {
    while(true) {
      pros::screen::print(TEXT_MEDIUM, 0, "X: %f", chassis.getPose().x);
      pros::screen::print(TEXT_MEDIUM, 1, "Y: %f", chassis.getPose().y);
      pros::screen::print(TEXT_MEDIUM, 2, "Theta: %f", chassis.getPose().theta);
      int32_t leftDist = left.get_distance();
      int32_t rightDist = right.get_distance();
      pros::screen::print(TEXT_MEDIUM, 3, "Left: %d mm", leftDist);
      pros::screen::print(TEXT_MEDIUM, 4, "Right: %d mm", rightDist);
      pros::screen::print(TEXT_MEDIUM, 5, "heading: %f ", imu.get_heading());
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
  pros::Controller controller(pros::E_CONTROLLER_MASTER);

  // Task to display pose on controller screen during auton
  pros::Task controller_display([&]()
                                {
    while (true) {
      lemlib::Pose pose = chassis.getPose();
      controller.print(0, 0, "X:%.1f Y:%.1f T:%.0f", pose.x, pose.y, pose.theta);
      pros::delay(50); // Update every 50ms (controller screen is slow)
    } });

  
  skills();
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
  
  pros::Task controller_display([&]()
                                {
    while (true) {
      lemlib::Pose pose = chassis.getPose();
      // controller.print(0, 0, "Voltage: %.1f", left_motors.get);
      pros::delay(50); // Update every 50ms (controller screen is slow)
    } });
  bool first = true;
  bool second = true;
  while (true)
  {
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    // move the robot
    chassis.arcade(leftY, rightX);
    // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    // {
    //   fast = !fast;
    // }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      if (midGoal.is_extended())
      {
        firstStage.move(127);
        secondStage.move(127);
      }
      else
      {
        if (first)
        {
          firstStage.move(127);
          secondStage.move(70);
          pros::delay(250);
          first = false;
        }
        else
        {
          firstStage.move(127);
          secondStage.move(40);
        }
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
      if (!intakeLift.is_extended())
      {
        firstStage.move(-127);
        secondStage.move(-127);
      }
      else
      {
        if (second)
        {
          firstStage.move(-80);
          secondStage.move(-127);
          pros::delay(250);
          first = false;
        }
        else
        {
          firstStage.move(-45);
          secondStage.move(-127);
        }
      }
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
      firstStage.move(127);
      secondStage.move(-127);
      // pros::delay(100);
      // if(firstStage.get_actual_velocity() < 100){
      //   firstStage.move(-127);

      //   pros::delay(50);
      // }
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
      firstStage.move(-127);
      secondStage.move(-127);
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
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
      midGoal.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
      intakeLift.toggle();
    }
    pros::delay(20);
  }
}