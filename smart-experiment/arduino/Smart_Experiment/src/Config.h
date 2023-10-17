#ifndef __CONFIG__
#define __CONFIG__

/* Smart Experiment */

/*Input & Output: */

#define BUTTON_START_PIN 3
#define BUTTON_STOP_PIN 6

#define LED_RED_PIN 9
#define LED_GREEN_PIN 4 

#define POT_PIN A0
#define TEMP_PIN A1

#define PIR_PIN 2

#define SONAR_TRIG_PIN 8
#define SONAR_ECHO_PIN 7

#define SERVO_PIN 5

/*Constants: */

#define SLEEP_TIME 5 // 5 secondi
#define MAX_TIME 20 // 20 secondi
#define ERROR_TIME 2 // 2 secondi
#define MINFREQ 1 // 1 Hz
#define MAXFREQ 50 // 50 Hz
#define MAXVEL 5 // m/s 
#define VCC ((float)5)
#define MAX_DISTANCE 0.5 // 0.5 metri

// Tasks
#define BLINK_TASK "blinkTask"
#define DETECT_PRESENCE_TASK "detectPresenceTask"
#define EXPERIMENT_TASK "experimentTask"
#define GREEN_LED_TASK "greenLedTask"
#define RED_LED_TASK "redLedTask"
#define START_BUTTON_TASK "startButtonTask"
#define STOP_BUTTON_TASK "stopButtonTask"

#endif
