#include <stdio.h>
#include <windows.h>
#include <string.h>

// Console width (adjust if needed)
#define CONSOLE_WIDTH 80

// Player ASCII art
const char* player_lines[] = {
    "         ******           ",
    "       **********         ",
    "      ************        ",
    "      ************        ",
    "       **********         ",
    "         ******           ",
    "           **             ",
    "           **             ",
    "       **********         ",
    "   ******************     ",
    " **********************   ",
    " ***  ************  ***   ",
    " ***  ************  ***   ",
    " ***  ************  ***   ",
    " ***  ************  ***   ",
    "  *   ************   *    ",
    "      ************        ",
    "      ****    ****        ",
    "      ****    ****        ",
    "      ****    ****        ",
    "      ****    ****        ",
    "       **      **         "
};
const int player_height = sizeof(player_lines) / sizeof(player_lines[0]);

// Ball ASCII art
const char* ball_lines[] = {
    "   ***   ",
    "  *****  ",
    " ******* ",
    " ******* ",
    " ******* ",
    " ******* ",
    "  *****  ",
    "   ***   "
};
const int ball_height = sizeof(ball_lines) / sizeof(ball_lines[0]);

// Goal ASCII art
const char* goal_lines[] = {
    "  |-------|----------+",
    "  |       |          |",
    "  |       |          |",
    "  |       |          |",
    "  |       |          |",
    "  |       |          |",
    "  |       |          |",
    "  |_______|----------+  "
};

// Move cursor to x,y position in console
void gotoxy(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Draw the entire scene: player, ball at ball_x, and goal on right
void draw_scene(int ball_x) {
    system("cls"); // clear screen (cleaner than messing with gotoxy)

    int ball_start_y = player_height - ball_height; // ball next to player's feet
    
    // Print player with ball next to feet
    for (int i = 0; i < player_height; i++) {
        printf("%s", player_lines[i]);

        // Print ball if this line is within ball vertical range
        if (i >= ball_start_y && i < ball_start_y + ball_height) {
            int ball_line_idx = i - ball_start_y;
            // print spaces equal to ball_x then ball line
            printf("%*s%s", ball_x, "", ball_lines[ball_line_idx]);
        }
        printf("\n");
    }

    // Print goal on the right side (fixed position)
    int goal_x = CONSOLE_WIDTH - 15;
    for (int i = 0; i < ball_height; i++) {
        gotoxy(goal_x, ball_start_y + i);
        printf("%s", goal_lines[i]);
    }
}

// Print GOAL message centered on screen
void print_goal_message() {
    int msg_x = CONSOLE_WIDTH / 2 - 3;
    int msg_y = 2;
    gotoxy(msg_x, msg_y);
    printf(">>> GOAL!!! <<<");
}

// Animate ball moving from player to goal
void animation_kick() {
    // Hide cursor for cleaner animation
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    int max_ball_x = CONSOLE_WIDTH - 25; // Stop near goal

    for (int x = 0; x <= max_ball_x; x += 2) {
        draw_scene(x);
        Sleep(70);
    }

    print_goal_message();

    // Show cursor again
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

