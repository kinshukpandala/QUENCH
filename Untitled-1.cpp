// The QUENCH display related script 
// works good need more changes 


#include <LCDWIKI_GUI.h>  // Core graphics library
#include <LCDWIKI_SPI.h>  // SPI communication for TFT
#include <Keypad.h>
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
#define BLUE    0x001F
#define GREEN   0x07E0
#define RED     0xF800

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;

// Custom key mapping
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // A → Select ML
  {'4', '5', '6', 'B'},  // B → Select ₹
  {'7', '8', '9', 'C'},  // C → Generate QR
  {'*', '0', '#', 'D'}   // D → Confirm Payment
};

// Define row and column pins
byte rowPins[ROWS] = {9, 8, 7, 6};  
byte colPins[COLS] = {5, 4, 3, 2};  

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// QR Code settings
QRCode qrcode;
const int qrVersion = 5;
uint8_t qrcodeData[200];

// Variables to store input values
int selectedML = 0;
float selectedRupees = 0;
float pricePerML = 0.05;  // Example: ₹0.05 per ml
String upiID = "kinshuk2005@okhdfcbank";

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(BLACK);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_Size(2);

    mylcd.Set_Text_colour(WHITE);
    mylcd.Print_String("QUENCH Ready!", 40, 20);
}

void loop() {
    char key = myKeypad.getKey();  

    if (key) {  
        mylcd.Fill_Rect(40, 50, 240, 40, BLACK);  // Clear previous message

        switch (key) {
            case 'A':  
                selectedML = getUserInput("Enter ML: ");
                selectedRupees = selectedML * pricePerML;
                displayMessage("Water: " + String(selectedML) + "ml");
                break;

            case 'B':  
                selectedRupees = getUserInput("Enter Rs: ");
                selectedML = selectedRupees / pricePerML;
                displayMessage("₹" + String(selectedRupees) + " -> " + String(selectedML) + "ml");
                break;

            case 'C':  
                if (selectedRupees > 0) {
                    generateQRCode(selectedRupees);
                    displayMessage("QR Generated!");
                } else {
                    displayMessage("Error! Set Amount");
                }
                break;

            case 'D':  
                displayMessage("Payment Verified!");
                mylcd.Set_Text_colour(GREEN);
                mylcd.Print_String("✅ Dispensing...", 40, 100);
                break;

            default:
                mylcd.Set_Text_colour(RED);
                mylcd.Print_String("Invalid Key", 40, 50);
                break;
        }
    }
}

int getUserInput(String prompt) {
    mylcd.Fill_Rect(40, 80, 240, 40, BLACK);  // Clear space
    mylcd.Set_Text_colour(BLUE);
    mylcd.Print_String(prompt.c_str(), 40, 80);

    String input = "";
    while (true) {
        char key = myKeypad.getKey();
        if (key && key != 'A' && key != 'B' && key != 'C' && key != 'D') {
            if (key == '#') break;  // End input when '#' is pressed
            input += key;
            mylcd.Print_String(String(key).c_str(), 40 + (input.length() * 12), 110);
        }
    }
    return input.toInt();
}

void generateQRCode(float amount) {
    String qrString = "upi://pay?pa=" + upiID + "&pn=QUENCH&am=" + String(amount) + "&cu=INR";

    if (qrcode_initText(&qrcode, qrcodeData, qrVersion, ECC_MEDIUM, qrString.c_str()) != 0) {
        displayMessage("QR Error!");
        return;
    }

    int scale = 5;
    int offsetX = (mylcd.Get_Display_Width() - (qrcode.size * scale)) / 2;
    int offsetY = 60;

    for (int y = 0; y < qrcode.size; y++) {
        for (int x = 0; x < qrcode.size; x++) {
            mylcd.Fill_Rect(offsetX + x * scale, offsetY + y * scale, scale, scale, 
                qrcode_getModule(&qrcode, x, y) ? WHITE : BLACK);
        }
    }
}

void displayMessage(String msg) {
    mylcd.Fill_Rect(40, 150, 240, 40, BLACK);
    mylcd.Set_Text_colour(WHITE);
    mylcd.Print_String(msg.c_str(), 40, 150);
}