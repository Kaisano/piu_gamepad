#include "button.h"
#include "pico/time.h"

long Button::board_millis()
{
    return to_ms_since_boot(get_absolute_time());
}

void Button::update()
{
    switch(btnState) {
        case UP:
            if(enabled()) {
                isPressed = true;

                startTime = board_millis();
                btnState = DEBOUNCE;
            }
        break;

        case DEBOUNCE:
            if(board_millis() - startTime > debounceTime) {
                if(enabled()) { 
                    btnState = DOWN;
                } else {
                    isPressed = false;
                    btnState = UP;
                }
            }
        break;

        case DOWN:
            if(!enabled()){
                isPressed = false;
                btnState = UP;
            }
        break;
    }
}

bool Button::enabled()
{
    return *data < threshold;
}

bool Button::pressed()
{
    return isPressed;
}
