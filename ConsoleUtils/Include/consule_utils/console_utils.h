#include <iostream>
#include <windows.h>
#include <string>

class ConsoleUtils {
private:
    static HANDLE hConsole;
    static CONSOLE_CURSOR_INFO cci;
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