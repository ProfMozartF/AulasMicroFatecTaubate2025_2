#ifndef SSD1306_H
#define SSD1306_H

#include "stm32f1xx_hal.h" // Ajuste conforme sua familia (f1xx, f4xx, etc)
#include <string.h>
#include <stdlib.h>

/* Definições de Hardware - Ajuste se mudar os pinos */
extern SPI_HandleTypeDef hspi1; // Handle do SPI definido no main.c
#define SSD1306_SPI_PORT hspi1

#define SSD1306_CS_Port  GPIOA
#define SSD1306_CS_Pin   GPIO_PIN_2
#define SSD1306_DC_Port  GPIOA
#define SSD1306_DC_Pin   GPIO_PIN_4
#define SSD1306_RES_Port GPIOA
#define SSD1306_RES_Pin  GPIO_PIN_3

/* Dimensões do Display */
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64

/* Cores */
typedef enum {
    Black = 0x00,
    White = 0x01
} SSD1306_COLOR;

/* Funções Públicas */
void SSD1306_Init(void);
void SSD1306_UpdateScreen(void);
void SSD1306_Fill(SSD1306_COLOR color);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
void SSD1306_WriteChar(char ch, SSD1306_COLOR color);
void SSD1306_WriteString(char* str, SSD1306_COLOR color);
void SSD1306_SetCursor(uint8_t x, uint8_t y);

#endif
