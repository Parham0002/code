/*#include <assert.h>
#include "terminal.h"

void app_main(void)
{
    assert(terminal_init());

    while (1)
    {
        assert(terminal_run());
    }
}*/

#include <stdio.h>
#include "terminal.h"

void app_main(void)
{
    // Initialize the terminal (you may want to check if it succeeded)
    if (!terminal_init())
    {
        printf("Terminal initialization failed.\n");
        return; // Exit the app if initialization fails
    }

    // Main loop to handle terminal commands
    while (1)
    {
        if (!terminal_run())
        {
            // If no input or failure, print a message and continue
            printf("No input detected or terminal run failed. Retrying...\n");
        }
    }
}