#include "mouse.h"
void setup() {
  // put your setup code here, to run once:

}

static int16_t  x                       = 0;
static int16_t  y                       = 0;

static int8_t   buttons                 = 0;
static int8_t   buttons_old             = 0;


// Passes the button, scroll and mouse movment information to the USB bus for the next poll
void update_usb()
{
  int8_t scroll           =  0;
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
  if (counter < 100)
  {
    x = 1;
  } 
  else if (counter < 200)
  {
    y = 1;
  }
  else if (counter < 300)
  {
    x = -1;
  }
  else if (counter < 400)
  {
    y = -1;
  }
  
  update_usb();
  counter += 1;
  counter %= 400;  
}
