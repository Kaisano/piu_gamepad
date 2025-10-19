#include "InputHandler.h"

void send_report(hid_custom_report_t report)
{

    // Remote wakeup
    if (tud_suspended())
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }

    if ( tud_hid_ready() )
    {
        tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
    }

}

void update_hid()
{
    // Poll every 1ms
    static uint32_t start_ms = 0;
    if (board_millis() - start_ms >= POLL_RATE) // if time elapsed is greater than the polling rate
    {
        start_ms += POLL_RATE;
        send_report(hid_task());
    }

    tud_task();
}
