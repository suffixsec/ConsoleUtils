#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

class ConsoleUtils {
private:
#ifdef _WIN32
    static HANDLE hConsole;
    static CONSOLE_CURSOR_INFO cci;
#else
    struct winsize {
        unsigned short ws_row;
        unsigned short ws_col;
        unsigned short ws_xpixel;
        unsigned short ws_ypixel;
    };
#endif
    static int cursorSize;
    static bool cursorVisibility;

    struct Dimensions {
        int Width;
        int Height;
    };

public:
    struct RGBColor {
        int r, g, b;
    };

    static void Initialize();

    class Print {
    public:
#undef RGB
        static void RGB(const std::string& text, const RGBColor& color);
        static void GradientRGB(const std::string& text, const RGBColor& startColor, const RGBColor& endColor);
    };

    class Text {
    public:
        static void SetTextColor(const RGBColor& color);
        static void ResetTextColor();
        static std::string CenterText(const std::string& text);
    };

    class Cursor {
    public:
        static void SetVisible(bool visible);
        static void SetSize(int size);
    private:
        static void updateCursor();
    };

    static Dimensions GetConsoleSize();
    static void SetConsoleSize(int width, int height);
};