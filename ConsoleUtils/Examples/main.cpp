#include "console_utils/console_utils.h"

int main() {
    ConsoleUtils::Initialize();

    printf("You can change the console size.\n");

    ConsoleUtils::SetConsoleSize(100, 28);

    printf("\nConsole Height: %d\nConsole Width: %d\n", ConsoleUtils::GetConsoleSize().Height, ConsoleUtils::GetConsoleSize().Width);

    printf("\nAnd return it.\n");

    ConsoleUtils::Print::RGB("\nCustom RGB", { 0,255,255 });
    ConsoleUtils::Print::RGB(ConsoleUtils::Text::CenterText("Centered Text"), { 255,0,255 });
    ConsoleUtils::Print::GradientRGB("Gradient Text Also Works Vertically", { 155, 125, 175 }, { 96, 81, 112 });

    ConsoleUtils::Cursor::SetVisible(false);

    printf("\nI just set the cursor visibility to false and now back to true.\n");

    ConsoleUtils::Cursor::SetVisible(true);
    ConsoleUtils::Cursor::SetSize(50);

    printf("\nYou can also change the size of the cursor.\n");

    ConsoleUtils::Text::SetTextColor({0, 155, 166});

    printf("\nI just set the text color.\n");
    printf("The text color will stay like this until its reset or changed to a different color.\n");

    ConsoleUtils::Text::ResetTextColor();

    printf("The text color has been reset.\n");

    return 0;
}