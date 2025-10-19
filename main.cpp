#include <stdio.h>
#include "pico/stdlib.h"
#include <bitset>

#include "InputHandler.h"
#include "main.h"

#include "usb_descriptors.h"

void app_setup()
{
    stdio_init_all();
    tusb_init();

    std::vector<int> rowADC = {0, 1};
    std::vector<int> colPins = {2, 3, 4};
    FSR = new FSRMatrix(rowADC, colPins);
}

void app_loop()
{
    update_hid();
}

int main()
{
    app_setup();

    while (true)
    {
        app_loop();
    }
}

float thresholds[] = {1.8, 1.8, 1.5, 1.7, 1.3};

hid_custom_report_t hid_task()
{
    hid_custom_report_t report = {
        .buttons = 0,
    }; 
    
    std::vector<float> data(FSR->updateFSR());

    // way to read from bitset
    for(int i = 0; i < BUTTON_COUNT; i++)
    {
        bool en = data[i] < thresholds[i];
        if(en) {
            report.buttons |= TU_BIT(i);
        }
    }

    return report;
}