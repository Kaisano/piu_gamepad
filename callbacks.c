#include <tusb.h>
//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
    // // Fill buffer with your data  
    // uint8_t data[64] = {0};  
      
    // // Example: Fill with some data  
    // for (int i = 0; i < reqlen && i < 64; i++) {  
    //     data[i] = i;  
    // }  
      
    // // Copy to buffer  
    // memcpy(buffer, data, reqlen);  
      
    // // Return the actual length of data  
    // return reqlen;  
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    // (void) instance;
    // echo back anything we received from host
    tud_hid_report(0, buffer, bufsize);
}