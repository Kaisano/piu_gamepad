#include "FSR.h"
#include <iostream>
#include "pico/stdlib.h"
FSRMatrix::FSRMatrix(std::vector<int> rowPins, std::vector<int> colPins)
{
    this->rowPins = rowPins;
    this->colPins = colPins;
    
    int dataSize = this->rowPins.size() * this->colPins.size();
    data = std::vector<float>(dataSize, 0);

    ROWS = rowPins.size();
    COLS = colPins.size();

    this->setup();
}

std::vector<float> FSRMatrix::updateFSR()
{
    for(int row = 0; row < ROWS; row++) {
        adc_select_input(row);
        for(int col = 0; col < COLS; col++) {
            int gpio = colPins[col];
            gpio_put(gpio, 0);
            sleep_us(1);

            int index = (row * COLS) + col;
            float Vo = adc_read() * conversion_factor;
            data[index] = Vo;

            gpio_put(gpio, 1);
        }
    } 
    return data;
}

void FSRMatrix::setup()
{
    adc_init();
    adc_gpio_init(ADC0_GPIO);
    adc_gpio_init(ADC1_GPIO);
    adc_gpio_init(ADC2_GPIO);

    for(int i = 0; i < colPins.size(); i++)
    {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_OUT);
        gpio_put(colPins[i], 0);
    }
}
