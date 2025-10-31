#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
using namespace pros;
MotorGroup left_motors({10, -8, -5},
                       MotorGearset::blue); // left motors on ports 1, 2, 3
MotorGroup right_motors({-6, 9, 7},
                        MotorGearset::blue); // right motors on ports 4, 5, 6
MotorGroup intake({11, 17}, MotorGearset::blue);
lemlib::Drivetrain
    drivetrain(&left_motors,               // left motor group
               &right_motors,              // right motor group
               10,                         // 10 inch track width
               lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
               450,                        // drivetrain rpm is 450
               2                           // horizontal drift is 2 (for now)
    );
pros::Imu imu(10);
// horizontal tracking wheel encoderd
pros::Rotation horizontal_encoder(20);
// vertical tracking wheel encoder
pros::adi::Encoder vertical_encoder('C', 'D', true);
pros::adi::Pneumatics hood('A', false);
pros::adi::Pneumatics scraper('B', false);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder,
                                                lemlib::Omniwheel::NEW_275,
                                                -5.75);
// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                              lemlib::Omniwheel::NEW_275, -2.5);
lemlib::OdomSensors sensors(
    &vertical_tracking_wheel, // vertical tracking wheel 1, set to null
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    &horizontal_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a
             // second one
    &imu     // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings
    lateral_controller(10,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       3,   // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       20   // maximum acceleration (slew)
    );

// angular PID controller
lemlib::ControllerSettings
    angular_controller(2,   // proportional gain (kP)
                       0,   // integral gain (kI)
                       10,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );
lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors             // odometry sensors
);
