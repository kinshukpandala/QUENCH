// this is the script for generating a qr code only 
// changes that needs to be made is to make the amount section a variable based on the amount entered 





#include <LCDWIKI_GUI.h>  // Core graphics library
#include <LCDWIKI_SPI.h>  // SPI communication for TFT
#include "qrcode.h"       // QR code generation library

// TFT Display Configuration
#define MODEL ILI9341
#define CS    A5    
#define CD    A3
#define RST   A4
#define MOSI  11
#define MISO  12
#define SCK   13
#define LED   A0  

LCDWIKI_SPI mylcd(MODEL, CS, CD, MISO, MOSI, RST, SCK, LED);

// Colors
#define BLACK   0x0000
#define WHITE   0xFFFF

// Screen dimensions
#define SCREEN_WIDTH  240  // Adjust based on actual TFT display width
#define SCREEN_HEIGHT 320  // Adjust based on actual TFT display height

// UPI Payment String
const char* upi_link = "upi://pay?pa=kinshuk2005@okhdfcbank&pn=QUENCH&am=10&cu=INR";

// QR Code settings
QRCode qrcode;
const int qrVersion = 5;
const int scale = 6; // Adjust for larger QR visibility
uint8_t *qrcodeData;

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(BLACK);  // Set background to black

    mylcd.Set_Text_colour(WHITE);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String("Scan to Pay", (SCREEN_WIDTH - 120) / 2, 10); // Center text

    // Allocate memory dynamically for QR buffer
    qrcodeData = (uint8_t*)malloc(qrcode_getBufferSize(qrVersion));
    if (qrcodeData == NULL) {
        mylcd.Print_String("Memory Error!", (SCREEN_WIDTH - 120) / 2, SCREEN_HEIGHT - 50);
        return;
    }

    generateQRCode(); // Generate and display QR code
}

void loop() {
    // Static display
}

void generateQRCode() {
    // Initialize QR code
    if (qrcode_initText(&qrcode, qrcodeData, qrVersion, ECC_MEDIUM, upi_link) != 0) {
        mylcd.Print_String("QR Error!", (SCREEN_WIDTH - 80) / 2, SCREEN_HEIGHT - 50);
        return;
    }

    int qrSize = qrcode.size;  // QR code module size (e.g., 29x29 for version 5)
    int qrPixelSize = qrSize * scale; // QR code full size in pixels

    // **Calculate exact center position**
    int offsetX = (SCREEN_WIDTH - qrPixelSize) / 2;
    int offsetY = (SCREEN_HEIGHT - qrPixelSize) / 2;

    // Draw QR code
    for (int y = 0; y < qrSize; y++) {
        for (int x = 0; x < qrSize; x++) {
            if (qrcode_getModule(&qrcode, x, y)) {
                mylcd.Fill_Rect(offsetX + x * scale, offsetY + y * scale, scale, scale, WHITE);
            } else {
                mylcd.Fill_Rect(offsetX + x * scale, offsetY + y * scale, scale, scale, BLACK);
            }
        }
    }
}
