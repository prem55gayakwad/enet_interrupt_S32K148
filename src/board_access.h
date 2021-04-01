/*
 * bsp.h
 */

#include "sdk_project_config.h"

typedef struct{
uint32_t err_Mask;
uint32_t time_stamp;
}tx_info;

typedef struct{
uint32_t header;
uint32_t time_stamp_rx;
}rx_info;

typedef struct {
  uint8_t destAddr[6];
  uint8_t srcAddr[6];
  uint16_t etherType;
  uint16_t length;
  uint8_t payload[1500];
} mac_frame_t;


// LPIT timers to get timer-callbacks for 1 and 100 ms
void lpit_isr_1(void);
void lpit_isr_100(void);

// GPIO Trigger-In on Port E
void isr_port_e(void);


// callback-functions foe timer interrupts
typedef void (*cb_fast_t)(void);
typedef void (*cb_slow_t)(void);

void config_fast_cb(cb_fast_t cb);
void config_slow_cb(cb_slow_t cb);

typedef void (*cb_trigger_in_t)(void);
void config_trigger_in_cb(cb_trigger_in_t);


// trigger_out functions
void release_trigger_out(void);
void activate_trigger_out(void);

// toggle REG-LED with given mask

#define MASK_LED_RED	(1<<0)
#define MASK_LED_GREEN	(1<<1)
#define MASK_LED_BLUE	(1<<2)

void toggle_led(int mask);
void set_led(int mask);
void clear_led(int mask);

int32_t enet_send(mac_frame_t *pframe,tx_info *txinf);
