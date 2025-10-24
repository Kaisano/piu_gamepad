#include <stdio.h>
#include "pico/stdlib.h"
#include <bitset>

#include "button.h"
#include "InputHandler.h"
#include "main.h"

#include "usb_descriptors.h"

#define BUTTON_COUNT  5

std::vector<Button> buttons;
float thresholds[] = {1.12, 1.2, 1.2, 1.2, 1.2};
std::vector<float> data;

void app_setup()
{
    stdio_init_all();
    tusb_init();

    std::vector<int> rowADC = {0, 1};
    std::vector<int> colPins = {2, 3, 4};
    FSR = new FSRMatrix(rowADC, colPins);
    data = std::vector<float>(FSR->updateFSR());

    buttons.reserve(BUTTON_COUNT);
    for(int i = 0 ; i < BUTTON_COUNT; i++) {
        buttons.emplace_back(&data[i], thresholds[i]);
    }
}

void app_loop()
{
    update_hid();
}

int main()
{
    app_setup();
    while(true) app_loop();
}


hid_custom_report_t hid_task()
{
    hid_custom_report_t report = {
        .buttons = 0,
    }; 
    
    std::vector<float> tempData = FSR->updateFSR();
    for(int i = 0; i < BUTTON_COUNT; i++) {
        data[i] = tempData[i];
        printf("%.3f V | ", data[i]);
    }    

    for(int i = 0; i < BUTTON_COUNT; i++)
    {
        buttons[i].update();
        if(buttons[i].pressed()) {
            report.buttons |= TU_BIT(i);
        }
    }

    return report;
}