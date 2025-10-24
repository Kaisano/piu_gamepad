#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button {
    private:
        enum State{
            UP,
            DEBOUNCE,
            DOWN
        };

        float* data;
        bool isPressed;
        float threshold;
        State btnState;
        long long startTime;
        int debounceTime = 50;
        
        long board_millis();
    public:
        Button(float* data, float threshold):data(data), threshold(threshold), btnState(UP) {};
        void update();
        bool enabled();
        bool pressed();
};

#endif