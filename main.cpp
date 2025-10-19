#include <stdio.h>
#include "pico/stdlib.h"
#include <bitset>

#include "InputHandler.h"
#include "main.h"

#include "tusb.h"
#include "tusb_config.h"

std::bitset<5> enabled = 0b10111;

void app_setup()
{
    stdio_init_all();
    tusb_init();
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


hid_custom_report_t hid_task()
{
    hid_custom_report_t report = {
        .buttons = 0,
    }; 
    
    // way to read from bitset
    for(int i = 0; i < enabled.size(); i++)
    {
        if(enabled[i])
        {
            report.buttons |= TU_BIT(i);
        }
    }

    // unsigned long long endTime = board_millis();
    // static int button = 0;
    // if(board_millis() - endTime > 100)
    // {
    //     endTime = board_millis();

    //     button++;
    //     button %= 10;
    // }
    
    // report.buttons |= TU_BIT(button);

    return report;
}