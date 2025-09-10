#include <stdio.h>
#include <windows.h>  // for Sleep and system("cls")

void printTitle() {
    printf("=======================================\n");
    printf("         FOOTBALL TEAM MANAGER          \n");
    printf("=======================================\n\n");
}

void animation() {
    int width = 40;
    int ballPos = 0;

    for (ballPos = 0; ballPos < width; ballPos++) {
        system("cls");
        printTitle();

        // Print player on the left (simple ASCII)
        printf("  O\n /|\\\n / \\\n\n");

        // Print spaces before ball to move it
        for (int i = 0; i < ballPos; i++) {
            printf(" ");
        }
        printf("@\n"); // Unicode soccer ball emoji (if console supports it)
        
        Sleep(100); // 100 milliseconds pause
    }

    // Player kicks the ball (just a simple pause and a text)
    system("cls");
    printTitle();
    printf("  O\n /|\\  --> KICK!\n / \\\n\n");
    for (int i = 0; i < width; i++) printf(" ");
    printf("@\n");
    Sleep(500);
}

int main() {
    animation();

    system("cls");
    printTitle();
    printf("Welcome to the Football Team Manager!\n");
    // Show your menu here...
    
    return 0;
}