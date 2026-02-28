#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#pragma once

#include "main.h"
#include "pros/imu.hpp"
#include <cmath>
using namespace pros;
class MockIMU : public Imu
{
public:
    MockIMU(int port, double gain)
        : Imu(port), imu_gain(gain) {}

    double get_rotation() const override
    {
        double raw = Imu::get_rotation();
        if (raw == PROS_ERR_F)
            return NAN;
        return raw * imu_gain;
    }

private:
    double imu_gain;
};

inline double scale = 24 / 25.646;

inline MockIMU imu(15, 363.5 / 360.0);
inline MotorGroup left_motors({11, -12, -13},      // 11 -12 -13
                              MotorGearset::blue); // left motors on ports 1, 2, 3
inline MotorGroup right_motors({-16, 17, 18},
                               MotorGearset::blue); // right motors on ports 4, 5, 6

inline Motor firstStage({7}, MotorGearset::blue);
inline Motor secondStage({-1}, MotorGearset::blue);
inline lemlib::Drivetrain
    drivetrain(&left_motors,               // left motor group
               &right_motors,              // right motor group
               13.5,                       // 10 inch track width
               lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
               450,                        // drivetrain rpm is 450
               2                           // horizontal drift is 2 (for now)
    );
inline pros::Rotation vertical_encoder(14);
inline pros::Distance left(2);
inline pros::Distance right(9);
inline pros::adi::Pneumatics midGoal('A', false); // c
inline pros::adi::Pneumatics scraper('D', false); // e
inline pros::adi::Pneumatics wing('B', false);
inline pros::adi::Pneumatics intakeLift('C', false);
// vertical tracking wheel
inline lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder,
                                                     scale *lemlib::Omniwheel::NEW_2, 3);
inline lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,
    nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2, set to null`ptr as we don't have a
             // second one
    &imu     // inertial sensor
);

inline lemlib::ControllerSettings
    lateral_controller(5.76, // proportional gain (kP) //5.7
                       0.25, // integral gain (kI)
                       28,   // derivative gain (kD) //21.7
                       2,    // anti windup
                       0,    // small error range, in inches
                       0,    // small error range timeout, in milliseconds
                       0,    // large error range, in inches
                       0,    // large error range timeout, in milliseconds
                       0     // maximum acceleration (slew)
    );

// angular PID controller
inline lemlib::ControllerSettings
    angular_controller(2.85, // proportional gain (kP)
                       0.1,  // integral gain (kI)
                       24,   // derivative gain (kD)
                       5,    // anti windup
                       0.01, // small error range, in inches
                       0,    // small error range timeout, in milliseconds
                       0,    // large error range, in inches
                       0,    // large error range timeout, in milliseconds
                       0     // maximum acceleration (slew)
    );
inline lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                               lateral_controller, // lateral PID settings
                               angular_controller, // angular PID settings
                               sensors             // odometry sensors
);
