#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
using namespace pros;

inline Imu imu(12);
inline MotorGroup left_motors({10, -8, -5},
                       MotorGearset::blue); // left motors on ports 1, 2, 3
inline MotorGroup right_motors({-6, 9, 7},
                        MotorGearset::blue); // right motors on ports 4, 5, 6
inline MotorGroup intake({-20, -17}, MotorGearset::blue);
inline lemlib::Drivetrain
    drivetrain(&left_motors,               // left motor group
               &right_motors,              // right motor group
               10,                         // 10 inch track width
               lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
               450,                        // drivetrain rpm is 450
               2                           // horizontal drift is 2 (for now)
    );
inline pros::Rotation vertical_encoder(11);
inline pros::adi::Pneumatics hood('A', false);
inline pros::adi::Pneumatics scraper('B', false);
// vertical tracking wheel
inline lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                              lemlib::Omniwheel::NEW_2, 0);
inline lemlib::OdomSensors sensors(
    &vertical_tracking_wheel, // vertical tracking wheel 1, set to null
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to null`ptr as we don't have a
             // second one
    &imu     // inertial sensor
);

// lateral PID controller
inline lemlib::ControllerSettings
    lateral_controller(5.45,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       2.2,   // derivative gain (kD)
                       0,   // anti windup
                       0,   // small error range, in inches
                       0, // small error range timeout, in milliseconds
                       0,   // large error range, in inches
                       0, // large error range timeout, in milliseconds
                       0   // maximum acceleration (slew)
    );

// angular PID controller
inline lemlib::ControllerSettings
    angular_controller(1.01, // proportional gain (kP)
                       0, // integral gain (kI)
                       6.40875, // derivative gain (kD)
                       0, // anti windup
                       0, // small error range, in inches
                       0, // small error range timeout, in milliseconds
                       0, // large error range, in inches
                       0, // large error range timeout, in milliseconds
                       0  // maximum acceleration (slew)
    );
inline lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors             // odometry sensors
);
