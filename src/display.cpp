#include "display.h"
#define SPEED 10

Display::Display(RGBMatrix *mat) : ThreadedCanvasManipulator(mat) {
    font.LoadFont("rpi-rgb-led-matrix/fonts/6x4.bdf");
}
void Display::Run() {
    while(running()) {
        long int i = clock()/1000;
        canvas()->Fill(0,0,0);
        printf("%s\n", text);
        DrawText(canvas(), font, 10, 10, color, NULL, text);
        i = clock()/1000-i;
        usleep(std::max(SPEED-i, 0l)*1000);
    }
}
void Display::setStr(const char* str) {
    text = str;
}
