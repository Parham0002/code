#ifndef FAKES_PREPROCESS_H
#define FAKES_PREPROCESS_H

#define low_level_getchar() fake_preprocess_getchar()
#define low_level_putchar(c) fake_preprocess_putchar(c)

#endif // FAKES_PREPROCESS_H
