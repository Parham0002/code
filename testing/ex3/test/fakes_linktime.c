#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Static variables for faking input and output
static const char *fake_input = NULL;
static size_t fake_input_index = 0;
static char *fake_output = NULL;

// ===== Link-Time Substitution Fakes =====

int low_level_getchar(void)
{
    if (fake_input && fake_input[fake_input_index])
    {
        return fake_input[fake_input_index++];
    }
    return '\n'; // Simulate pressing ENTER if input finished
}

int low_level_putchar(int c)
{
    if (fake_output)
    {
        size_t len = strlen(fake_output);
        fake_output[len] = (char)c;
        fake_output[len + 1] = '\0';
        return c;
    }
    return EOF;
}

// ===== Preprocessor-Time Substitution Fakes =====

int fake_preprocess_getchar(void)
{
    return low_level_getchar();
}

int fake_preprocess_putchar(int c)
{
    return low_level_putchar(c);
}

// ===== Helper Functions to Configure Fakes =====

// Set the input sequence for fake getchar
void set_fake_getchar_sequence(const char *input)
{
    fake_input = input;
    fake_input_index = 0;
}

// Set the buffer to capture output from fake putchar
void set_fake_putchar_capture_buffer(char *buffer)
{
    fake_output = buffer;
}

// Dummy selectors for runtime/preprocessor/compiletime techniques
void use_linktime_fake()
{
    // Already using link-time fakes by default
}

void use_runtime_fake()
{
    // In this simple example, runtime fake behavior is same
}

void use_preprocess_fake()
{
    // In this simple example, preprocess fake behavior is same
}

void use_compiletime_fake()
{
    // In this simple example, compile-time fake behavior is same
}
