#ifndef TYPE_H_
#define TYPE_H_

#include <lcom/lcf.h>
#include <stdint.h>

char name[10];
uint8_t indexName=0;

/**
 * @brief Processes a scan code and appends the corresponding character to the name array.
 * 
 * @param scancode The scan code received from the keyboard.
 */
int processScanCode(uint8_t scancode);

#endif

