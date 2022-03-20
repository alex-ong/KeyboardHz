#include "mouse.h"
void setup() {
  // put your setup code here, to run once:

}

static elapsedMicros burst_timer  = 0;
static elapsedMicros polling_rate = 0;
static elapsedMillis scroll_timer = 0;
static elapsedMillis button_timer = 0;

static int16_t  x                       = 0;
static int16_t  y                       = 0;
static uint8_t  scroll                  = 0;
static int8_t   buttons                 = 0;
static int8_t   buttons_old             = 0;
static uint16_t cpi[6]                  = {400, 800, 1600, 2000, 3200, 6400};
static uint8_t  cpi_index               = 5;
static bool     cpi_pressed             = false;
static uint16_t set_rate                = 125;

// Passes the button, scroll and mouse movment information to the USB bus for the next poll
void update_usb()
{
  int8_t scroll           = (buttons & 0b10000000) ? scroll =  1 : (buttons & 0b01000000) ? scroll = -1 : scroll = 0;
  usb_mouse_buttons_state =  buttons;
  buttons_old             =  buttons;
  // This function is blocking if its buffers fill up and blocks until the next USB poll (125uS at USB 2.0 HIGH speed and 1mS below that speed)
  // usb_mouse_move only accepts 8 bit data by default it still works with 8 bit values but at lower polling speeds (1000Hz and lower)
  // maximum control speed is limited due to the integers overflowing. Recommended to make this function 16 bit for lower polling speeds (see my github)
  usb_mouse_move(x, y, scroll, 0);
  x = 0;
  y = 0;
}

int counter = 0;
// Gathers mouse data and sends it over the USB
void loop()
{  
  if (counter % 4 == 0)
  {
    x = 1;
    y = 1;
  } 
  else if (counter % 4 == 1)
  {
    x = -1;
    y = -1;
  }
  else if (counter % 4 == 2)
  {
    x = 1;
    y = -1;
  }
  else if (counter % 4 == 3)
  {
    x = -1;
    y = 1;
  }
    
  else x = -1;
  
  update_usb();
  counter += 1;
  counter %= 4;  
}
