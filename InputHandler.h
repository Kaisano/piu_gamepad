#ifndef _DANCEINPUTHANDLER_H_
#define _DANCEINPUTHANDLER_H_

// includes
#include "tusb.h"
#include "tusb_config.h"
#include "usb_descriptors.h"

#include "bsp/board.h"

// defines
#define POLL_RATE 1                                 // poll rate in ms

// typedefs
typedef void (* vFunctionCall)();                   // function parameters

typedef struct
{
    uint32_t buttons;
} hid_custom_report_t;                              // report struct

// functions
void send_report(hid_custom_report_t report);       // send HID report
void update_hid();                                  // poll report tasks
hid_custom_report_t hid_task();                     // task to perform

#endif