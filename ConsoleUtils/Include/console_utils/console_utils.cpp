#include "console_utils.h"

HANDLE ConsoleUtils::hConsole;
CONSOLE_CURSOR_INFO ConsoleUtils::cci;
int ConsoleUtils::cursorSize;
bool ConsoleUtils::cursorVisibility;

void ConsoleUtils::Initialize() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorSize = 20;
    cursorVisibility = true;
    cci = { static_cast<DWORD>(cursorSize), cursorVisibility };
}

void ConsoleUtils::Print::RGB(const std::string& text, const RGBColor& color) {
    ConsoleUtils::Text::SetTextColor(color);
    std::cout << text;
    ConsoleUtils::Text::ResetTextColor();
}

void ConsoleUtils::Print::GradientRGB(const std::string& text, const RGBColor& startColor, const RGBColor& endColor) {
    double step = 1.0 / (text.length() - 1);

    for (size_t i = 0; i < text.length(); ++i) {
        int currentR = static_cast<int>(startColor.r * (1.0 - step * i) + endColor.r * (step * i));
        int currentG = static_cast<int>(startColor.g * (1.0 - step * i) + endColor.g * (step * i));
        int currentB = static_cast<int>(startColor.b * (1.0 - step * i) + endColor.b * (step * i));

        RGBColor currentColor = { currentR, currentG, currentB };
        ConsoleUtils::Text::SetTextColor(currentColor);

        std::cout << text[i];
    }

    ConsoleUtils::Text::ResetTextColor();
}

void ConsoleUtils::Text::SetTextColor(const RGBColor& color) {
    printf("\033[38;2;%d;%d;%dm", color.r, color.g, color.b);
}

void ConsoleUtils::Text::ResetTextColor() {
    printf("\033[0m");
    std::cout << std::endl;
}

std::string ConsoleUtils::Text::CenterText(const std::string& text) {
    int consoleWidth = GetConsoleSize().Width;
    int textLength = static_cast<int>(text.length());
    int space = (consoleWidth - textLength) / 2;
    return std::string(space, ' ') + text;
}

void ConsoleUtils::Cursor::SetVisible(bool visible) {
    cci.bVisible = visible;
    cursorVisibility = visible;
    cci.dwSize = cursorSize;
    updateCursor();
}

void ConsoleUtils::Cursor::SetSize(int size) {
    cursorSize = size;
    cci.dwSize = size;
    updateCursor();
}

void ConsoleUtils::Cursor::updateCursor() {
    if (!SetConsoleCursorInfo(hConsole, &cci))
        std::cerr << "Failed to update cursor settings." << std::endl;
}

ConsoleUtils::Dimensions ConsoleUtils::GetConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    Dimensions size;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        size.Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        size.Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else {
        size.Width = 80;
        size.Height = 25;
    }
    return size;
}

void ConsoleUtils::SetConsoleSize(int width, int height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        std::cerr << "Failed to get buffer info." << std::endl;

#undef max
    COORD newBufferSize = { std::max(csbi.dwSize.X, static_cast<SHORT>(width)), std::max(csbi.dwSize.Y, static_cast<SHORT>(height)) };
    if (!SetConsoleScreenBufferSize(hConsole, newBufferSize))
        std::cerr << "Failed to set initial buffer size." << std::endl;

    SMALL_RECT newWindowSize = { 0, 0, width - 1, height - 1 };
    if (!SetConsoleWindowInfo(hConsole, TRUE, &newWindowSize)) {
        std::cerr << "Failed to set window size." << std::endl;
        SetConsoleScreenBufferSize(hConsole, csbi.dwSize);
    }

    if (!SetConsoleScreenBufferSize(hConsole, { static_cast<SHORT>(width), static_cast<SHORT>(height) }))
        std::cerr << "Failed to set final buffer size." << std::endl;
}