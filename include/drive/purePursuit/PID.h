#ifndef _PID
#define _PID

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include <cmath>

class PID {
    public:
        /**
         * @brief Construct a new PID controller
         * 
         * @param kP proportional gain
         * @param kI integral gain 
         * @param kD derivative gain
         * @param windupRange integral anti-windup range (set to 0 to disable)
         */
        PID(double kP, double kI, double kD, double windupRange = 0){
            this->kP = kP;
            this->kI = kI;
            this->kD = kD;
            this->windupRange = windupRange;
        };

        /**
         * @brief Update the PID controller
         * 
         * @param error target minus current position
         * @return double output value
         */
        double update(double error);

        /**
         * @brief Reset the PID controller's integral and previous error
         */
        void reset();

    protected:
        // PID gains
        double kP;
        double kI; 
        double kD;

        // Anti-windup range for integral
        double windupRange;

        // Runtime variables
        double integral = 0;
        double prevError = 0;
        
};

#endif // _PID_H