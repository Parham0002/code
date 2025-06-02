#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include <stdbool.h>

#define BSP_LOW 0
#define BSP_HIGH 1
#define BSP_PULL_UP 0
#define BSP_MODE_INPUT 1

bool bsp_pin_config(int pin, int mode, int pull);

int bsp_pin_read(int pin);

// Helper functions
void bsp_test_set_pin_level(int level);

int bsp_test_get_last_configured_pin(void);

int bsp_test_get_last_pin_mode(void);

int bsp_test_get_last_pin_pull(void);

#endif /* BSP_H */
