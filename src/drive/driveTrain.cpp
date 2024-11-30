#include "drive/driveTrain.h"

// Physical constants
#define TRACK_WIDTH 11.625f
#define HORZ_OFFSET -3.0f // CHANGE THIS BETWEEN SKILLS AND MATCH

// Practical adjustments
#define HORZ_MULTIPLIER 1.0f
#define VERT_MULTIPLIER 1.0f

// Drivetrain, Don't use for now
lemlib::Drivetrain drivetrain(
    &driveLeft,                                  // Left drivetrain motor group
    &driveRight,                                            // Right drivetrain motor group
    TRACK_WIDTH,                                 // Track width
    lemlib::Omniwheel::NEW_325 *VERT_MULTIPLIER, // Wheel diameter
    400,                                         // Wheel rpm
    2                                            // Chase power is higher with traction wheels, lower without
);

// lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275 * HORZ_MULTIPLIER, HORZ_OFFSET);

lemlib::OdomSensors sensors{
    nullptr, // Vertical 1
    nullptr, // Vertical 2
    nullptr, // Horizontal 1
    nullptr, // Horizontal 2
    &imu     // IMU
};

// PID
lemlib::ControllerSettings lateralController{
    10,  // kP
    0,   // kI
    3,   // kD
    3,   // antiWindup
    1,   // smallErrorRange
    100, // smallErrorTimeout
    3,   // largeErrorRange
    500, // largeErrorTimeout
    150  // slew rate
};

lemlib::ControllerSettings angularController{
    2,   // kP
    0,   // kI
    10,  // kD
    3,   // antiWindup
    1,   // smallErrorRange
    100, // smallErrorTimeout
    3,   // largeErrorRange
    500, // largeErrorTimeout
    0    // slew rate
};

// Refer to this drive curve I found: https://www.desmos.com/calculator/9loqd3rbsb
//  float customDriveCurve(float input, float scale) {
//      float normalizedInput = input / 127;
//      float normalizedOutput = 0;

//     if (scale == 0) {
//         normalizedOutput = normalizedInput;
//     }
//     else {
//         if (input >= 0) {
//             normalizedOutput = (1 - pow(M_E, scale * normalizedInput)) / (1 - pow(M_E, scale));
//         }
//         else {
//             normalizedOutput = (pow(M_E, scale * -normalizedInput) - 1) / (1 - pow(M_E, scale));
//         }
//     }

//     return normalizedOutput * 127;
// }

// Refer to this drive curve I found: https://www.desmos.com/calculator/9loqd3rbsb
//  float customDriveCurve(float input, float scale) {
//      float normalizedInput = input / 127;
//      float normalizedOutput = 0;

//     if (scale == 0) {
//         normalizedOutput = normalizedInput;
//     }
//     else {
//         if (input >= 0) {
//             normalizedOutput = (1 - pow(M_E, scale * normalizedInput)) / (1 - pow(M_E, scale));
//         }
//         else {
//             normalizedOutput = (pow(M_E, scale * -normalizedInput) - 1) / (1 - pow(M_E, scale));
//         }
//     }

//     return normalizedOutput * 127;
// }

// Putting it all together
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);