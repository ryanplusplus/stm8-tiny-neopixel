/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include <stddef.h>
#include "interrupts.h"
#include "clock.h"
#include "tim4_system_tick.h"
#include "tiny_timer.h"
#include "pb5_heartbeat.h"
#include "watchdog.h"
#include "pc6_neopixel.h"

static tiny_timer_group_t timer_group;

void main(void)
{
  interrupts_disable();
  {
    clock_init();
    tiny_timer_group_init(&timer_group, tim4_system_tick_init());
    watchdog_init(&timer_group);
    pb5_heartbeat_init(&timer_group);
  }
  interrupts_enable();

  pc6_neopixel_init();
  pc6_neopixel_color_t color[] = {
    { 5, 0, 5 },
    { 4, 0, 5 },
    { 3, 0, 5 },
    { 2, 1, 5 },
    { 1, 2, 5 },
    { 0, 3, 5 },
    { 0, 4, 5 },
    { 0, 5, 5 }
  };
  pc6_neopixel_write(color, 8);

  while(true) {
    if(!tiny_timer_group_run(&timer_group)) {
      interrupts_wait_for_interrupt();
    }
  }
}
