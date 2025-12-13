#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
using namespace pros;

inline Imu imu(6);
inline MotorGroup left_motors({9, -8, -10},
                       MotorGearset::blue); // left motors on ports 1, 2, 3
inline MotorGroup right_motors({-2, 1, 3},
                        MotorGearset::blue); // right motors on ports 4, 5, 6

inline Motor firstStage({7}, MotorGearset::blue);
inline Motor secondStage({4}, MotorGearset::blue);
inline lemlib::Drivetrain
    drivetrain(&left_motors,               // left motor group
               &right_motors,              // right motor group
               14,                      // 10 inch track width
               lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
               450,                        // drivetrain rpm is 450
               2                           // horizontal drift is 2 (for now)
    );
inline pros::Rotation vertical_encoder(-5);
inline pros::adi::Pneumatics bypass('C', false); //c
inline pros::adi::Pneumatics scraper('E', false); //e
inline pros::adi::Pneumatics park('B', false); //B
inline pros::adi::Pneumatics wing('D', true);
inline pros::adi::Pneumatics odomLift('A', false);
// vertical tracking wheel
inline lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                              lemlib::Omniwheel::NEW_2, 0);
inline lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to null`ptr as we don't have a
             // second one
    &imu     // inertial sensor
);

inline lemlib::ControllerSettings
    lateral_controller(6,  // proportional gain (kP) //5.7
                       0,   // integral gain (kI)
                       20,   // derivative gain (kD) //21.7
                       2,   // anti windup
                       0,   // small error range, in inches
                       0, // small error range timeout, in milliseconds
                       0,   // large error range, in inches
                       0, // large error range timeout, in milliseconds
                       0  // maximum acceleration (slew)
    );

// angular PID controller
inline lemlib::ControllerSettings
    angular_controller(2.8, // proportional gain (kP)
                       0.1, // integral gain (kI)
                       22, // derivative gain (kD)
                       5, // anti windup
                       0.01, // small error range, in inches
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
