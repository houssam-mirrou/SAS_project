#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <math.h>

// ---------------- Utility Functions ----------------
void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen() {
    system("cls");
}

void clear_area(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++) printf(" ");
    }
}

void draw_sprite(const char* sprite[], int lines, int x, int y) {
    for (int i = 0; i < lines; i++) {
        gotoxy(x, y + i);
        printf("%s", sprite[i]);
    }
}

// ---------------- Enhanced Field ----------------
void drawField() {
    // Stadium banner
    gotoxy(15, 0);
    printf("================== PENALTY KICK ANIMATION ==================");
    
    // Grass texture
    for (int y = 2; y < 28; y++) {
        gotoxy(0, y);
        for (int x = 0; x < 120; x++) {
            if ((x + y) % 6 == 0) printf(".");
            else if ((x + y) % 9 == 0) printf(",");
            else printf(" ");
        }
    }
    
    // Grass line
    gotoxy(0, 28);
    for (int i = 0; i < 120; i++) printf("_");
    
    // Midfield line
    for (int y = 2; y < 28; y++) {
        gotoxy(60, y);
        printf("|");
    }
    
    // Penalty area
    for (int y = 12; y < 24; y++) {
        gotoxy(85, y);
        printf("|");
    }
    for (int x = 85; x < 102; x++) {
        gotoxy(x, 12);
        printf("-");
        gotoxy(x, 23);
        printf("-");
    }
    
    // Penalty spot
    gotoxy(93, 18);
    printf("X");
}

// ---------------- Enhanced Goal with Net ----------------
const char* enhanced_goal[] = {
    "############################################################",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "#  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #",
    "#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #",
    "############################################################"
};

// ---------------- Enhanced Player Sprites ----------------
const char* player_idle[] = {
    "         @@@@@           ",
    "       @@@@@@@@@         ",
    "      @@@@@@@@@@@        ",
    "      @@@@@@@@@@@        ",
    "       @@@@@@@@@         ",
    "         @@@@@           ",
    "           @@            ",
    "           @@            ",
    "       @@@@@@@@@@        ",
    "   @@@@@@@@@@@@@@@@      ",
    " @@@@@@@@@@@@@@@@@@@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    "  @@  @@@@@@@@@@  @@     ",
    "      @@@@@@@@@@         ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "       @@      @@        "
};

const char* player_windup[] = {
    "         @@@@@           ",
    "       @@@@@@@@@         ",
    "      @@@@@@@@@@@        ",
    "      @@@@@@@@@@@        ",
    "       @@@@@@@@@         ",
    "         @@@@@           ",
    "           @@            ",
    "           @@            ",
    "    @@@@@@@@@@@@         ",
    " @@@@@@@@@@@@@@@@@@      ",
    "@@@@@@@@@@@@@@@@@@@@     ",
    "@@@@  @@@@@@@@@@  @@@    ",
    "@@@@  @@@@@@@@@@  @@@    ",
    "@@@@  @@@@@@@@@@  @@@    ",
    "@@@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@     ",
    "      @@@@@@@@@@         ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "      @@@@               ",
    "      @@@@               ",
    "       @@                "
};

const char* player_kick[] = {
    "         @@@@@           ",
    "       @@@@@@@@@         ",
    "      @@@@@@@@@@@        ",
    "      @@@@@@@@@@@        ",
    "       @@@@@@@@@         ",
    "         @@@@@           ",
    "           @@            ",
    "           @@            ",
    "       @@@@@@@@@@        ",
    "   @@@@@@@@@@@@@@@@      ",
    " @@@@@@@@@@@@@@@@@@@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    " @@@  @@@@@@@@@@  @@@    ",
    "  @@  @@@@@@@@@@  @@     ",
    "      @@@@@@@@@@         ",
    "      @@@@     @@@@      ",
    "      @@@@      @@@      ",
    "      @@@@       @@@     ",
    "      @@@@        @@@    ",
    "       @@          @@    "
};

const char* player_celebrate[] = {
    "         @@@@@           ",
    "       @@@@@@@@@         ",
    "      @@@@@@@@@@@        ",
    "      @@@@@@@@@@@        ",
    "       @@@@@@@@@         ",
    "         @@@@@           ",
    "           @@            ",
    "           @@            ",
    " @@@@  @@@@@@@@@@  @@@@  ",
    "@@@@@@@@@@@@@@@@@@@@@@@@ ",
    "@@@@@@@@@@@@@@@@@@@@@@   ",
    "@@@   @@@@@@@@@@   @@@   ",
    "@@@   @@@@@@@@@@   @@@   ",
    "@@@   @@@@@@@@@@   @@@   ",
    "@@@   @@@@@@@@@@   @@@   ",
    " @@   @@@@@@@@@@    @@   ",
    "      @@@@@@@@@@         ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "      @@@@    @@@@       ",
    "       @@      @@        "
};

// ---------------- Goalkeeper ----------------
const char* keeper_idle[] = {
    "         #####           ",
    "       #########         ",
    "      ###########        ",
    "      ###########        ",
    "       #########         ",
    "         #####           ",
    "           ##            ",
    "           ##            ",
    "       ##########        ",
    "   ##################    ",
    " ####################    ",
    " ###  ############  ###  ",
    " ###  ############  ###  ",
    " ###  ############  ###  ",
    " ###  ############  ###  ",
    "  ##  ############   ##  ",
    "      ############       ",
    "      ####    ####       "
};

const char* keeper_dive[] = {
    "                     #####       ##  ",
    "                   #########    ###  ",
    "                  ###########  ####  ",
    "                  ########### ####   ",
    "                   ######### ####    ",
    "                     ##### ####      ",
    "                       ## ####       ",
    "              ##############         ",
    "           #################         ",
    "          ##################         ",
    "          ###  #############         ",
    "         ###  #############          ",
    "         ###  ############           ",
    "         ###  ###########            ",
    "          ##  ###########            ",
    "             ###  #####              ",
    "            ###  #####               ",
    "           ###  #####                "
};

// ---------------- Enhanced Ball Animation ----------------
const char* ball_frames[8][8] = {
    {
        "   @@@   ","  @@@@@  "," @@@@@@@ "," @@@@@@@ ",
        " @@@@@@@ "," @@@@@@@ ","  @@@@@  ","   @@@   "
    },
    {
        "   @@@   ","  @   @  "," @ @@@ @ "," @ @@@ @ ",
        " @ @@@ @ "," @ @@@ @ ","  @   @  ","   @@@   "
    },
    {
        "   @@@   ","  @@@@@  "," @     @ "," @ @@@ @ ",
        " @ @@@ @ "," @     @ ","  @@@@@  ","   @@@   "
    },
    {
        "   @@@   ","  @ @ @  "," @@@ @@@ "," @  @  @ ",
        " @  @  @ "," @@@ @@@ ","  @ @ @  ","   @@@   "
    },
    {
        "   @@@   ","  @@@@@  "," @ @ @ @ "," @@@ @@@ ",
        " @@@ @@@ "," @ @ @ @ ","  @@@@@  ","   @@@   "
    },
    {
        "   @@@   ","  @@ @@  "," @@@@@@@ "," @@   @@ ",
        " @@   @@ "," @@@@@@@ ","  @@ @@  ","   @@@   "
    },
    {
        "   @@@   ","  @   @  "," @@@ @@@ "," @@@ @@@ ",
        " @@@ @@@ "," @@@ @@@ ","  @   @  ","   @@@   "
    },
    {
        "   @@@   ","  @@@@@  "," @ @@@ @ "," @@@@@@@ ",
        " @@@@@@@ "," @ @@@ @ ","  @@@@@  ","   @@@   "
    }
};

// Ball motion trail
const char* ball_trail[] = {
    "  . .    ",
    " .   .   ",
    ".  .  .  ",
    " .   .   ",
    "  . .    "
};

// ---------------- Title Screen ----------------
void showTitle() {
    clearScreen();
    gotoxy(30, 6);
    printf("################################################");
    gotoxy(30, 7);
    printf("#                                              #");
    gotoxy(30, 8);
    printf("#     ENHANCED PENALTY KICK ANIMATION         #");
    gotoxy(30, 9);
    printf("#                                              #");
    gotoxy(30, 10);
    printf("#          A Beautiful Goal Animation         #");
    gotoxy(30, 11);
    printf("#                                              #");
    gotoxy(30, 12);
    printf("#         Press ENTER to watch...             #");
    gotoxy(30, 13);
    printf("#                                              #");
    gotoxy(30, 14);
    printf("################################################");
    getchar();
}

// ---------------- Goal Celebration ----------------
void showGoalAnimation() {
    // Big GOAL text
    gotoxy(35, 8);
    printf("  #####    #####     ####    #          ###");
    gotoxy(35, 9);
    printf(" #        #     #   #    #   #          ###");
    gotoxy(35, 10);
    printf(" #  ###   #     #  #      #  #          ###");
    gotoxy(35, 11);
    printf(" #    #   #     #  ########  #             ");
    gotoxy(35, 12);
    printf("  #####    #####   #      #  ######     ###");
    
    gotoxy(28, 15);
    printf("*** THE BALL FINDS THE BACK OF THE NET! ***");
    
    // Simple celebration effects
    gotoxy(20, 17);
    printf("*     *     *     *     *     *     *     *");
    gotoxy(20, 18);
    printf("  *     *     *     *     *     *     *   ");
    gotoxy(20, 19);
    printf("*     *     *     *     *     *     *     *");
}

// Net ripple effect when ball hits
void animateNetRipple(int goal_x, int goal_y, int ball_x, int ball_y) {
    // Show ball hitting net
    for (int ripple = 0; ripple < 3; ripple++) {
        // Modify net around ball impact point
        for (int i = 0; i < 15; i++) {
            gotoxy(goal_x, goal_y + i);
            if (i >= (ball_y - goal_y - 2) && i <= (ball_y - goal_y + 2)) {
                if (ripple == 0) printf("#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  #");
                else if (ripple == 1) printf("#  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  #");
                else printf("#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #");
            } else {
                printf("#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #");
            }
        }
        Sleep(200);
    }
}

// ---------------- Main Animation ----------------
int main_3() {
    hideCursor();
    showTitle();
    clearScreen();

    // Animation setup
    int player_x = 5, player_y = 4;
    int ball_x = 30, ball_y = player_y + 14;
    int goal_x = 60, goal_y = player_y + 6;
    int keeper_x = goal_x + 12, keeper_y = goal_y + 3;
    int floor_y = player_y + 22;

    // Draw the scene
    drawField();
    draw_sprite(enhanced_goal, 15, goal_x, goal_y);

    // Step 1: Initial setup
    gotoxy(5, 30);
    printf("The player steps up to the penalty spot...");
    
    draw_sprite(player_idle, 22, player_x, player_y);
    draw_sprite(ball_frames[0], 8, ball_x, ball_y);
    draw_sprite(keeper_idle, 18, keeper_x, keeper_y);
    Sleep(2000);

    // Step 2: Concentration phase
    gotoxy(5, 31);
    printf("Taking a deep breath, focusing on the target...");
    Sleep(1500);

    // Step 3: The run-up begins
    gotoxy(5, 32);
    printf("The run-up begins...");
    
    clear_area(player_x, player_y, 26, 22);
    draw_sprite(player_windup, 22, player_x, player_y);
    Sleep(1000);

    // Step 4: The strike!
    gotoxy(5, 33);
    printf("AND THE SHOT IS AWAY!");
    
    clear_area(player_x, player_y, 26, 22);
    draw_sprite(player_kick, 22, player_x, player_y);

    // Enhanced ball physics for perfect goal
    double vy = -4.2;  // Perfect trajectory
    double gravity = 0.28;
    double air_resistance = 0.98;
    double y = ball_y;
    double x = ball_x;
    int frame_counter = 0;
    int keeper_dived = 0;

    // Ball animation with perfect trajectory
    while (x < goal_x + 35) {
        // Safe clearing with boundary checks
        int clear_x = (int)x - 8;
        int clear_y = (int)y - 3;
        if (clear_x < 0) clear_x = 0;
        if (clear_y < 1) clear_y = 1;
        if (clear_x + 18 > 119) clear_x = 119 - 18;
        if (clear_y + 12 > 27) clear_y = 27 - 12;
        
        clear_area(clear_x, clear_y, 18, 12);
        
        // Add motion trail with bounds check
        if (frame_counter > 2) {
            int trail_x = (int)x - 12;
            int trail_y = (int)y - 1;
            if (trail_x >= 0 && trail_x < 110 && trail_y >= 1 && trail_y < 25) {
                draw_sprite(ball_trail, 5, trail_x, trail_y);
            }
        }

        // Physics
        x += 2.8;
        y += vy;
        vy += gravity;
        vy *= air_resistance;

        // Keeper reaction (too late!)
        if (x > goal_x - 15 && !keeper_dived) {
            clear_area(keeper_x - 8, keeper_y - 1, 40, 18);
            draw_sprite(keeper_dive, 18, keeper_x - 8, keeper_y - 1);
            keeper_dived = 1;
            
            gotoxy(5, 34);
            printf("The keeper dives but it's too late!");
        }

        // Draw spinning ball with bounds check
        if ((int)x >= 0 && (int)x < 112 && (int)y >= 1 && (int)y < 20) {
            draw_sprite(ball_frames[frame_counter % 8], 8, (int)x, (int)y);
        }

        frame_counter++;
        Sleep(85);

        // Ball enters goal
        if (x >= goal_x + 5 && x <= goal_x + 50) {
            if (y >= goal_y + 3 && y <= goal_y + 12) {
                // GOAL! Animate net ripple
                animateNetRipple(goal_x, goal_y, (int)x, (int)y);
                break;
            }
        }
    }

    // Victory celebration
    Sleep(500);
    clear_area(player_x, player_y, 26, 22);
    draw_sprite(player_celebrate, 22, player_x, player_y);
    
    showGoalAnimation();
    
    gotoxy(5, 35);
    printf("What a magnificent strike! The crowd erupts!");

    Sleep(3000);
    
    gotoxy(5, 37);
    printf("Press any key to exit...");
    getchar();
    
    clearScreen();
    return 0;
}