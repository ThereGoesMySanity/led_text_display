#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <math.h>
#include <unistd.h>
#include "led-matrix.h"
#include "graphics.h"
#include "canvas.h"
#include "threaded-canvas-manipulator.h"

using namespace rgb_matrix;

class Display : public ThreadedCanvasManipulator {
    public:
        Display(RGBMatrix *mat);
        void setStr(const char*);
        virtual void Run();
    private:
        Font font;
        struct Color color = Color(255,255,255);
        const char* text;
};
