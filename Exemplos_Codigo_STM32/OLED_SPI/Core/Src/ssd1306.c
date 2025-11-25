#include "ssd1306.h"
#include "fonts.h"

/* Buffer de Tela (128 * 64 / 8 = 1024 bytes) */
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

/* Posição atual do cursor */
static struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
} SSD1306;

/* Funções Privadas de Baixo Nível */
static void ssd1306_WriteCommand(uint8_t command) {
    HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_RESET); // Select
    HAL_GPIO_WritePin(SSD1306_DC_Port, SSD1306_DC_Pin, GPIO_PIN_RESET); // Command Mode
    HAL_SPI_Transmit(&SSD1306_SPI_PORT, &command, 1, 10);
    HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_SET);   // Deselect
}

static void ssd1306_WriteData(uint8_t* data, uint16_t size) {
    HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_RESET); // Select
    HAL_GPIO_WritePin(SSD1306_DC_Port, SSD1306_DC_Pin, GPIO_PIN_SET);   // Data Mode
    HAL_SPI_Transmit(&SSD1306_SPI_PORT, data, size, 100);
    HAL_GPIO_WritePin(SSD1306_CS_Port, SSD1306_CS_Pin, GPIO_PIN_SET);   // Deselect
}

/* Inicialização */
void SSD1306_Init(void) {
    // Reset do Hardware
    HAL_GPIO_WritePin(SSD1306_RES_Port, SSD1306_RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(SSD1306_RES_Port, SSD1306_RES_Pin, GPIO_PIN_SET);
    HAL_Delay(10);

    // Sequência de Inicialização Padrão SSD1306
    ssd1306_WriteCommand(0xAE); // Display OFF
    ssd1306_WriteCommand(0x20); // Set Memory Addressing Mode
    ssd1306_WriteCommand(0x00); // Horizontal Addressing Mode
    ssd1306_WriteCommand(0xB0); // Set Page Start Address for Page Addressing Mode
    ssd1306_WriteCommand(0xC8); // Set COM Output Scan Direction
    ssd1306_WriteCommand(0x00); // Set Low Column Address
    ssd1306_WriteCommand(0x10); // Set High Column Address
    ssd1306_WriteCommand(0x40); // Set Start Line Address
    ssd1306_WriteCommand(0x81); // Set Contrast Control
    ssd1306_WriteCommand(0xFF); // Máximo contraste
    ssd1306_WriteCommand(0xA1); // Set Segment Re-map
    ssd1306_WriteCommand(0xA6); // Set Normal Display
    ssd1306_WriteCommand(0xA8); // Set Multiplex Ratio
    ssd1306_WriteCommand(0x3F);
    ssd1306_WriteCommand(0xA4); // Output follows RAM content
    ssd1306_WriteCommand(0xD3); // Set Display Offset
    ssd1306_WriteCommand(0x00);
    ssd1306_WriteCommand(0xD5); // Set Display Clock Divide Ratio
    ssd1306_WriteCommand(0xF0);
    ssd1306_WriteCommand(0xD9); // Set Pre-charge Period
    ssd1306_WriteCommand(0x22);
    ssd1306_WriteCommand(0xDA); // Set COM Pins Hardware Configuration
    ssd1306_WriteCommand(0x12);
    ssd1306_WriteCommand(0xDB); // Set VCOMH Deselect Level
    ssd1306_WriteCommand(0x20);
    ssd1306_WriteCommand(0x8D); // Charge Pump Setting
    ssd1306_WriteCommand(0x14); // Enable Charge Pump
    ssd1306_WriteCommand(0xAF); // Display ON

    SSD1306_Fill(Black);
    SSD1306_UpdateScreen();
}

void SSD1306_Fill(SSD1306_COLOR color) {
    memset(SSD1306_Buffer, (color == Black) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void SSD1306_UpdateScreen(void) {
    // No modo de endereçamento horizontal, podemos enviar o buffer inteiro de uma vez
    ssd1306_WriteData(SSD1306_Buffer, sizeof(SSD1306_Buffer));
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;

    // Lógica para mapear pixel X,Y para o byte correto no buffer
    if(color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
    } else {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

void SSD1306_SetCursor(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}

void SSD1306_WriteChar(char ch, SSD1306_COLOR color) {
    /* Verifica se o caractere está dentro da tabela ASCII imprimível */
    if (ch < 32 || ch > 126) {
        return;
    }

    /* Loop pelas 5 colunas da fonte */
    for (uint8_t i = 0; i < FONT5X7_WIDTH; i++) {
        /* Busca o byte correspondente na tabela (Offset de -32) */
        uint8_t b = Font5x7[ch - 32][i];

        /* Loop pelos bits (altura) */
        for (uint8_t j = 0; j < FONT5X7_HEIGHT; j++) {
            if ((b >> j) & 0x01) {
                SSD1306_DrawPixel(SSD1306.CurrentX + i, SSD1306.CurrentY + j, color);
            } else {
                // Opcional: desenha o fundo da letra (importante se escrever sobre algo)
                SSD1306_DrawPixel(SSD1306.CurrentX + i, SSD1306.CurrentY + j, !color);
            }
        }
    }

    /* Avança o cursor (Largura da fonte + 1 pixel de espaçamento) */
    SSD1306.CurrentX += (FONT5X7_WIDTH + 1);
}

void SSD1306_WriteString(char* str, SSD1306_COLOR color) {
    while (*str) {
        SSD1306_WriteChar(*str, color);
        str++;
    }
}


