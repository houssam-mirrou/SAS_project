// ------------------------------------------------------------
// Program gestion d'equipe — Penalty Kick (idle → DIVE → DOWN)
// Player stands before kick; celebration raises hands up
// ------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <string.h>

// ================= Colors / Sound =================
static HANDLE HOUT;
static void setColor(WORD attr){ SetConsoleTextAttribute(HOUT, attr); }
static void kickSfx(){ Beep(1200,60); Beep(1500,60); }
static void goalSfx(){ Beep(900,80); Beep(1200,120); Beep(1500,160); }

// ================= Utilities ======================
static void gotoxy(int x,int y){ COORD c={(SHORT)x,(SHORT)y}; SetConsoleCursorPosition(HOUT,c); }
static void hideCursor(){ CONSOLE_CURSOR_INFO ci; GetConsoleCursorInfo(HOUT,&ci); ci.bVisible=0; SetConsoleCursorInfo(HOUT,&ci); }
static void clearScreen(){ system("cls"); }

static void clear_area(int x,int y,int w,int h){
    if(w<=0||h<=0) return;
    for(int i=0;i<h;i++){ gotoxy(x,y+i); for(int j=0;j<w;j++) putchar(' '); }
}
static void safe_clear_area(int x,int y,int w,int h){
    int minY=2, maxW=120, maxH=29; // rows 0..28
    if(x<0){ w+=x; x=0; }
    if(y<minY){ h+=y-minY; y=minY; }
    if(x+w>maxW) w=maxW-x;
    if(y+h>(maxH-1)) h=(maxH-1)-y;
    if(w>0&&h>0) clear_area(x,y,w,h);
}
static void draw_sprite(const char* spr[], int lines, int x, int y){
    for(int i=0;i<lines;i++){ gotoxy(x,y+i); printf("%s", spr[i]); }
}

// Quadratic Bézier helper (top-right finish)
static double qbez(double p0,double p1,double p2,double t){
    double u=1.0-t; return u*u*p0 + 2*u*t*p1 + t*t*p2;
}

// ================= HUD / Title ====================
static void drawHUD(const char* rightText){
    setColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    gotoxy(0,0); printf(" Program gestion d'equipe ");
    setColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    for(int i=26;i<119;i++) putchar(' ');
    if(rightText){ int len=(int)strlen(rightText); if(len>0){ gotoxy(119-len,0); printf("%s",rightText); } }
    gotoxy(0,1); for(int i=0;i<120;i++) putchar('=');
}
static void showTitleScreen(){
    clearScreen(); drawHUD("Penalty Demo");
    setColor(FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    gotoxy(20,7);  printf("##################################################################################");
    gotoxy(20,8);  printf("#                                                                                #");
    gotoxy(20,9);  printf("#                        Program gestion d'equipe                                #");
    gotoxy(20,10); printf("#                                                                                #");
    gotoxy(20,11); printf("##################################################################################");
    setColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    getchar(); clearScreen(); drawHUD("Kick!");
}

// ================= Field / Goal ===================
static void drawField(){
    for(int y=2;y<28;y++){
        gotoxy(0,y);
        for(int x=0;x<120;x++){
            if(((x+y)%11)==0) putchar('.');
            else if(((x*y)%37)==0) putchar(',');
            else putchar(' ');
        }
    }
    gotoxy(0,28); for(int i=0;i<120;i++) putchar('_');
}
static const char* goal_net[]={
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

// ================= Sprites =======================
// Player idle (stands before kick)
static const char* player_idle[]={
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
// Player kick
static const char* player_kick[]={
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
// Celebration (hands raising animation: mid → up)
static const char* player_celebrate_mid[]={
"         @@@@@           ",
"       @@@@@@@@@         ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"       @@@@@@@@@         ",
"         @@@@@           ",
"  @@@      @@       @@   ",
"  @@@@@    @@     @@@@   ",
"  @@@@@@@@@@@@@@@@@@@    ",
"   @@@@@@@@@@@@@@@@@     ",
"    @@@@@@@@@@@@@@@      ",
"     @@@@@@@@@@@@@       ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"       @@      @@        "
};
static const char* player_celebrate_up[]={
"         @@@@@           ",
"       @@@@@@@@@         ",
"      @@@@@@@@@@@        ",
" @@   @@@@@@@@@@@    @@  ",
" @@@   @@@@@@@@@    @@@  ",
" @@@@    @@@@@     @@@@  ",
" @@@@      @@      @@@@   ",
"  @@@@@    @@     @@@@   ",
"  @@@@@@@@@@@@@@@@@@@    ",
"   @@@@@@@@@@@@@@@@@     ",
"    @@@@@@@@@@@@@@@      ",
"     @@@@@@@@@@@@@       ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@@@@@@@@        ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"      @@@@    @@@@       ",
"       @@      @@        "
};

// Keeper: idle, dive, ground
static const char* keeper_idle[]={
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
static const char* keeper_dive[]={
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
static const char* keeper_ground[]={
"              #############################        ",
"          #####################################    ",
"        ########################################   ",
"       ######### ############### ###############   ",
"       ########  ###############  #############    ",
"        #####     #############     ##########     ",
"         ####       #########        #######       ",
"           ################################        ",
"               ############################        "
};

// Ball (9x8) + trail
static const char* ball_frames[8][8]={
 { "   @@@   ","  @@@@@  "," @@@@@@@ "," @@@@@@@ "," @@@@@@@ "," @@@@@@@ ","  @@@@@  ","   @@@   " },
 { "   @@@   ","  @   @  "," @ @@@ @ "," @ @@@ @ "," @ @@@ @ "," @ @@@ @ ","  @   @  ","   @@@   " },
 { "   @@@   ","  @@@@@  "," @     @ "," @ @@@ @ "," @ @@@ @ "," @     @ ","  @@@@@  ","   @@@   " },
 { "   @@@   ","  @ @ @  "," @@@ @@@ "," @  @  @ "," @  @  @ "," @@@ @@@ ","  @ @ @  ","   @@@   " },
 { "   @@@   ","  @@@@@  "," @ @ @ @ "," @@@ @@@ "," @@@ @@@ "," @ @ @ @ ","  @@@@@  ","   @@@   " },
 { "   @@@   ","  @@ @@  "," @@@@@@@ "," @@   @@ "," @@   @@ "," @@@@@@@ ","  @@ @@  ","   @@@   " },
 { "   @@@   ","  @   @  "," @@@ @@@ "," @@@ @@@ "," @@@ @@@ "," @@@ @@@ ","  @   @  ","   @@@   " },
 { "   @@@   ","  @@@@@  "," @ @@@ @ "," @@@@@@@ "," @@@@@@@ "," @ @@@ @ ","  @@@@@  ","   @@@   " }
};
static const char* ball_trail[]={
"  . .    ",
" .   .   ",
".  .  .  ",
" .   .   ",
"  . .    "
};

// ================= Net Ripple =====================
static void animateNetRipple(int gx,int gy,int bx,int by){
    for(int r=0;r<3;r++){
        for(int i=0;i<15;i++){
            gotoxy(gx,gy+i);
            if(i>=(by-gy-2) && i<=(by-gy+2)){
                if(r==0) printf("#  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  #");
                else if(r==1) printf("#  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  #");
                else printf("#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #");
            }else{
                printf("#  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+  #");
            }
        }
        Sleep(140);
    }
}

// ================= Keeper state & scene ===========
typedef enum { KEEPER_IDLE=0, KEEPER_DIVE=1, KEEPER_DOWN=2 } KeeperState;

static void drawBaseScene(int goal_x,int goal_y,int keeper_x,int keeper_y, KeeperState ks){
    draw_sprite(goal_net,15,goal_x,goal_y);
    if(ks==KEEPER_IDLE){
        draw_sprite(keeper_idle,18, keeper_x, keeper_y);
    }else if(ks==KEEPER_DIVE){
        draw_sprite(keeper_dive,18, keeper_x-8, keeper_y-1);
    }else{ // DOWN
        draw_sprite(keeper_ground,9, keeper_x-10, keeper_y+8);
    }
}

// ================= Main ===========================
int main_3(){
    HOUT=GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
    showTitleScreen();

    // Layout
    int player_x=5,  player_y=4;
    int floor_y = player_y + 22;
    int goal_x  = 60, goal_y = floor_y - 14;
    int keeper_x= goal_x + 12, keeper_y = goal_y + 3;
    int ball_x  = 30, ball_y = player_y + 14;

    // Initial scene: goal + standing keeper + PLAYER IDLE + BALL
    drawField();
    KeeperState ks = KEEPER_IDLE;
    drawBaseScene(goal_x,goal_y,keeper_x,keeper_y, ks);
    draw_sprite(player_idle,22,player_x,player_y);           // stand normally
    draw_sprite(ball_frames[0],8,ball_x,ball_y);             // ball at foot
    Sleep(450);

    // Kick pose + tiny dust
    const char* dust[]={"  .."," ....","  .."};
    safe_clear_area(player_x,player_y,26,22);
    draw_sprite(player_kick,22,player_x,player_y);
    draw_sprite(dust,3, ball_x-2, ball_y+7);
    kickSfx(); Sleep(120);
    safe_clear_area(ball_x,ball_y,9,8);                      // clear the still ball
    safe_clear_area(ball_x-2, ball_y+7, 6, 3);               // clear dust

    // ===== Ball path to TOP-RIGHT (Bezier) =====
    double x=ball_x, y=ball_y;
    int frame=0;
    int prev_bx=-1000, prev_by=-1000, prev_tx=-1000, prev_ty=-1000;

    int total_frames=28;               // flight duration
    double x0=ball_x, y0=ball_y;
    double tx_goal = goal_x + 48;      // top-right inside net
    double ty_goal = goal_y + 3;       // just below crossbar
    double cx_mid  = (x0 + tx_goal)*0.5 + 2; // slight bend to the right
    double cy_mid  = goal_y - 1;       // just above bar

    for(int f=0; f<=total_frames; ++f){
        if(prev_tx>-500) safe_clear_area(prev_tx,prev_ty,9,5);
        if(prev_bx>-500) safe_clear_area(prev_bx,prev_by,9,8);

        double t = (double)f / total_frames;        // 0 → 1
        x = qbez(x0,cx_mid, tx_goal,t);
        y = qbez(y0,cy_mid, ty_goal,t);

        // Keeper timings: idle → dive → down just before impact
        if(ks==KEEPER_IDLE && t>=0.65) ks = KEEPER_DIVE;
        if(ks==KEEPER_DIVE && t>=0.92) ks = KEEPER_DOWN;

        drawBaseScene(goal_x,goal_y,keeper_x,keeper_y, ks);

        int tx=(int)x-12, ty=(int)y-1;
        if(tx>=0 && tx<=111 && ty>=2 && ty<=26){ draw_sprite(ball_trail,5,tx,ty); prev_tx=tx; prev_ty=ty; }
        else { prev_tx=prev_ty=-9999; }

        int bx=(int)x, by=(int)y;
        if(bx>=0 && bx<=111 && by>=2 && by<=26){ draw_sprite(ball_frames[frame%8],8,bx,by); prev_bx=bx; prev_by=by; }
        else { prev_bx=prev_by=-9999; }

        frame++; Sleep(65);
    }

    // Impact → ripple + keeper down (safety) + celebration
    ks = KEEPER_DOWN;
    goalSfx();
    animateNetRipple(goal_x,goal_y,(int)x,(int)y);
    drawBaseScene(goal_x,goal_y,keeper_x,keeper_y, ks);

    // Celebration: hands raise animation (mid ↔ up)
    for(int i=0;i<6;i++){
        safe_clear_area(player_x,player_y,26,22);
        if(i%2==0) draw_sprite(player_celebrate_mid,22,player_x,player_y);
        else       draw_sprite(player_celebrate_up, 22,player_x,player_y);
        Sleep(180);
    }

    setColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    gotoxy(36,7);  printf("  #####    #####     ####    #          ###");
    gotoxy(36,8);  printf(" #        #     #   #    #   #          ###");
    gotoxy(36,9);  printf(" #  ###   #     #  #      #  #          ###");
    gotoxy(36,10); printf(" #    #   #     #  ########  #             ");
    gotoxy(36,11); printf("  #####    #####   #      #  ######     ###");
    setColor(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

    Sleep(1800);
    clearScreen();
    drawHUD("Thanks!");
    gotoxy(45,12); printf("Appuyer sur entrer pour lancer le program");
    getchar();
    system("cls");
    main_2();
}
