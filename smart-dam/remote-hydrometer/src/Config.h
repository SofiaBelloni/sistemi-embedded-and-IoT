#ifndef __CONFIG__
#define __CONFIG__

/*Input & Output: */
#define LED_ALARM D2
#define TEMP_PIN A0
#define SONAR_TRIG_PIN D0
#define SONAR_ECHO_PIN D1

/*Constants: */ 
#define VCC ((float)3)
// IN cm
#define PREALARM_THRESHOLD 100
#define ALARM_THRESHOLD 40
#define MAX_LEVEL 500
// IN s
#define PREALARM_FREQ 10
#define ALARM_FREQ 5

// IN ms
#define HYDROMETER_PERIOD 500
#define BLINKING_PERIOD 100

/* wifi network name */
#define SSID_NAME "TP-LINK_2_4"
/* WPA2 PSK password */
#define PASSWORD "via25aprile_396"
/* service IP address */
#define ADDRESS "http://8f2069dba4d8.ngrok.io"

#endif
