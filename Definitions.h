#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WiFiSSID              "Richard"           //"WLAN_8086"
#define WiFiPSK               "20091990"          //"N2CAB25F08086"

#define FALSE                 0
#define TRUE                  1

#define LED_PIN               5
#define SL_RX                 13
#define SL_TX                 12
#define HTTP_PORT             80
#define TIME_TO_QUERY         1000
#define _15SECS               10000
#define NUM_STATES            5

#define IDLE                  0
#define STARTING              1
#define STOPPING              2
#define ON                    3

#define HOST                  "192.168.43.249"//"sofia.com"
#define HOST_PORT             5000

#define BIG_OVEN              0
#define SMALL_OVEN            1


typedef struct{
    int type_oven;
    int profile;
}struct_starting_cmd;

int Idle_handler(void);
int Starting_handler(void);
int Stopping_handler(void);
int On_handler(void);

typedef struct{
  int (*State_handler)(void);
}esp_state;

#endif
