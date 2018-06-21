#include "connection.h"
#include "led-matrix.h"
#include "graphics.h"
#include "canvas.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <json.hpp>

#define ___TEST___ 290

using json=nlohmann::json;
using namespace rgb_matrix;

int main(int argc, char** argv) {

    RGBMatrix::Options defaults;
    defaults.chain_length = 2;
    defaults.led_rgb_sequence = "RBG";
    RuntimeOptions runtime_opt;
    runtime_opt.drop_privileges = 0;
    RGBMatrix *mat = CreateMatrixFromFlags(&argc, &argv, &defaults, &runtime_opt);

    std::unordered_map<std::string, Font*> fonts;

    std::ifstream fontFile;
    fontFile.open("fonts.txt");
    std::string font;
    while(!fontFile.eof()) {
        std::getline(fontFile, font);
        std::stringstream ss;
        ss << "rpi-rgb-led-matrix/fonts/" << font << ".bdf";
        Font *f = new Font();
        f->LoadFont(ss.str().c_str());
        fonts[font] = f;
    }
    fontFile.close();

    Connection c;
    bool connected = c.connect();

    const char *ptr;
    struct Color col(255, 255, 255);
    std::string str("");
    font = "";

    while(connected) {
        if((ptr = c.getData()) != nullptr) {
            printf("%s\n", ptr);
            auto js = json::parse(ptr);
            int w, h;
            for(auto it = js.begin(); it != js.end(); ++it) {
                if(it.key() == "text" && !it.value().empty()) {
                    str = it.value();
                } else if(it.key() == "color" && !it.value().empty()) {
                    sscanf(it.key().c_str(), "#%02x%02x%02x", &col.r, &col.g, &col.b);
                } else if(it.key() == "font" && !it.value().empty()) {
                    font = it.value();
                }
            }
            if(font.empty()) {
                font = "6x10";
            }
            Font *currentFont = fonts[font];
            printf("%s, %d %d %d, %s %d\n", str.c_str(), col.r, col.g, col.b, font.c_str(), currentFont->height());
            int y = 32/currentFont->height();

            mat->Clear();
            int offX = 0, offY = 0;

            //TODO: split at spaces
            for(int i = 0; i < str.length(); i++) {
                if(offX + currentFont->CharacterWidth(str[i]) >= 64) {
                    offX = 0;
                    offY += currentFont->height();
                }
                offX += currentFont->DrawGlyph(mat, offX, offY + currentFont->baseline(), col, NULL, str[i]);
            }
        }
        c.close();
        printf("Connection lost, reconnecting...\n");
        connected = c.connect();
    }
    delete mat;
}
