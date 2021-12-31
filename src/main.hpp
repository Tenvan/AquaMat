#define VERSION "1.2.211230"

#define WIFI_SSID "Vodafone-49BE"
#define WIFI_PW "KjkZ4trvM4nm7m"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2
#define PIN_PUMP1 26
#define PIN_PUMP2 17
#define PIN_PUMP3 27

#define PIN_BUTTON1 25
#define PIN_BUTTON2 16
#define PIN_BUTTON3 14

#define ON true
#define OFF false

#define PUMP_ACTIVE "pumpe_aktiv"

// Funktions Definitionen
void setPump(int led, bool status);
