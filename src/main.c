#include <Arduino.h>

#define DIGITS 2
#define NUM_PINS_PER_DIGIT 7
#define NC 9

//pins noted in order: upper part starting at middle line clockwise, then lower part starting at bottom line clockwise
const unsigned int PINS_DIGIT_0[] = {1, 2, 3, 4, 6, 5, 7};
const unsigned int PINS_DIGIT_1[] = {PIN_A0, PIN_A1, PIN_A2, PIN_A3, PIN_A5, PIN_A4, 8};

const unsigned int* PINS_DIGITS[DIGITS] = {PINS_DIGIT_1, PINS_DIGIT_0};


//NC=9 is the fill value for not used pins as a 7 segment display has at most 8 pins
const unsigned int NUM_TO_SEGMENT[10][7] = {{1, 2, 3, 4, 5, 6, NC},
                                            {3, 6, NC, NC, NC, NC, NC},
                                            {2, 3, 0, 5, 4, NC, NC},
                                            {2, 3, 0, 6, 4, NC, NC},
                                            {1, 0, 3, 6, NC, NC, NC},
                                            {2, 1, 0, 6, 4, NC, NC},
                                            {2, 1, 0, 6, 4, 5, NC},
                                            {2, 3, 6, NC, NC, NC, NC},
                                            {0, 1, 2, 3, 4, 5, 6},
                                            {0, 1, 2, 3, 4, 6, NC}};


void setup() {
    for(unsigned int digit=0; digit<DIGITS; digit++){
        for(unsigned int pin_idx=0; pin_idx < NUM_PINS_PER_DIGIT; pin_idx++){
            pinMode(PINS_DIGITS[digit][pin_idx], OUTPUT);
            digitalWrite(PINS_DIGITS[digit][pin_idx], HIGH);
        }
    }

}

void turn_all_segments_off(){
    for(unsigned int digit=0; digit<DIGITS; digit++){
        for(unsigned int pin_idx = 0; pin_idx < NUM_PINS_PER_DIGIT; pin_idx++){
            digitalWrite(PINS_DIGITS[digit][pin_idx], HIGH);
        }
    }
}

void print_number(unsigned int number){
    if(number>pow(10, DIGITS)){
        return;
    }
    turn_all_segments_off();

    for(unsigned int current_digit_idx = 0; current_digit_idx<DIGITS; current_digit_idx++){
        unsigned int current_digit = number % 10;
        for(unsigned int pin_idx = 0; pin_idx < NUM_PINS_PER_DIGIT; pin_idx++){
            unsigned int segment_number = NUM_TO_SEGMENT[current_digit][pin_idx];
            if(segment_number != NC){
                digitalWrite(PINS_DIGITS[current_digit_idx][segment_number], LOW);
            }
        }
        number = number/10;
    }

}

void sleep_frames_120fps(unsigned int frames){
    for(unsigned int i=0;i<frames;i++){
        delayMicroseconds(8333);
    }
}

void loop() {
    unsigned long time = millis();
    print_number(time%100);
    sleep_frames_120fps(10);
}