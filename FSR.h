#ifndef _FSR_H
#define _FSR_H

#include "hardware/adc.h"
#include "hardware/gpio.h"
#include <vector>

#define ADC0_GPIO 26
#define ADC1_GPIO 27
#define ADC2_GPIO 28

class FSRMatrix {
    public:

        FSRMatrix(std::vector<int> rowPins, std::vector<int> colPins);
        std::vector<float> updateFSR();
        
        private:
            std::vector<int> rowPins;
            std::vector<int> colPins;
            int ROWS;
            int COLS;
            std::vector<float> data;
            const float conversion_factor = (3.3f / (1 << 12));
            
            void setup();
};

#endif