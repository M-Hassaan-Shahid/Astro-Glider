#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

void drawMaze1();
void drawMaze2();
void drawMaze3();
void loseGame();
void livesEnded();
void endGame();
void movePlayer();
void moveFinishPoint();
void drawEnemies();
void moveEnemies(int level);
void shootProjectile();
void moveProjectile() ;
void checkCollision();
void updateGame();
void gravity();
void fuel();
void resizeConsole();
void cursorHide();
void cursorShow();
void resetGame();
bool containsOnlyIntegers(string integer);
void instruction();
bool containsOnlyAlphabets(string word);
void saveScore();
void viewScore();
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
char getCharAtxy(short int x, short int y)
{
CHAR_INFO ci;
COORD xy = {0, 0};
SMALL_RECT rect = {x, y, x, y};
COORD coordBufSize;
coordBufSize.X = 1;
coordBufSize.Y = 1;
return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar
: ' ';
}

string setcolor(int color);
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
void startGame();

const int HEIGHT = 40;
const int WIDTH = 22;

int pX = 11, pY = 1; // Player position
int lives = 3; // lives count
int score = 0; // score count
bool gameOver = false;
int level;
int speed;

int enemy1X = WIDTH - 3, enemy1Y = 10; // Enemy 1 position
int enemy2X = WIDTH - 3, enemy2Y = 18; // Enemy 2 position
int enemy3X = WIDTH - 3, enemy3Y = 30; // Enemy 3 position
int enemySpeed = 1; // enemy speed

int endY = HEIGHT -2, endX = WIDTH - 2; // Finish point 
int deadY = HEIGHT -1, deadX = WIDTH - 2; // dead point

char maze[HEIGHT][WIDTH]; // Maze array to hold maze layout

int FinishPointX = 16, FinishPointY = 37; // Finish Point positions
int FinishPointSpeed = 1; // Speed at which the FinishPoint moves

int health = 100; // The initial health level
int healthX = 5;   // The X position of the health level display in the maze
int healthY = 5;   // The Y position of the health level display in the maze

int projectileX = pX, projectileY = pY+1;
bool projectileActive = false;
string name;


int main() {

    system("cls");
    resizeConsole();
    gameOver = false;
    string input;
    int option;
    
    cursorHide();
    setcolor(lightgreen);
    gotoxy(1,1);cout << " _____                                 _____ "<<endl;
    gotoxy(1,2);cout << "( ___ )-------------------------------( ___ )"<<endl;   
    gotoxy(1,3);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,4);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,5);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,6);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,7);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,8);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,9);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,10);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,11);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,12);cout << " |   |                                 |   | "<<endl;
    gotoxy(1,13);cout << " |___|                                 |___| "<<endl;
    gotoxy(1,14);cout << "(_____)-------------------------------(_____)"<<endl;
    gotoxy(1,15);cout << "                                             "<<endl;
    
    setcolor(white);
    setcolor(red);
    gotoxy(7,3);Sleep(200);cout<<"    _          _             "<<endl; 
    gotoxy(7,4);Sleep(200);cout<<"   / \\    ___ | |_  _ __  ___ "<<endl;
    gotoxy(7,5);Sleep(200);cout<<"  / _ \\  / __|| __|| '__|/ _ \\ "<<endl;
    gotoxy(7,6);Sleep(200);cout<<" / ___ \\ \\__ \\| |_ | |  | (_) |"<<endl;
    gotoxy(7,7);Sleep(200);cout<<"/_/   \\_\\|___/ \\__||_|   \\___/"<<endl;
    gotoxy(7,8);Sleep(200);cout<<"   ____  _  _      _  "<<endl;
    gotoxy(7,9);Sleep(200);cout<<"  / ___|| |(_)  __| |  ___  _ __ "<<endl;
    gotoxy(7,10);Sleep(200);cout<<" | |  _ | || | / _` | / _ \\| '__|"<<endl;
    gotoxy(7,11);Sleep(200);cout<<" | |_| || || || (_| ||  __/| |   "<<endl;
    gotoxy(7,12);Sleep(200);cout<<"  \\____||_||_| \\__,_| \\___||_|"<<endl;
    setcolor(white);
    Sleep(200);
    setcolor(green);
    gotoxy(1,16);cout << "__| |__________________________________| |__"<<endl;
    gotoxy(1,17);cout << "__| |________                   _______| |__"<<endl;
    gotoxy(1,18);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,19);cout << "  | |       |   SELECT OPTION  |       | |  "<<endl;
    gotoxy(1,20);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,21);cout << "  | |       | 1.  START GAME   |       | |  "<<endl;
    gotoxy(1,22);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,23);cout << "  | |       | 2. INSTRUCTIONS  |       | |  "<<endl;
    gotoxy(1,24);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,25);cout << "  | |       | 3. VIEW HISTORY  |       | |  "<<endl;
    gotoxy(1,26);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,27);cout << "  | |       | 4.     EXIT      |       | |  "<<endl;
    gotoxy(1,28);cout << "  | |        -------------------       | |  "<<endl;
    gotoxy(1,29);cout << "  | |       |                  |       | |  "<<endl;
    gotoxy(1,30);cout << "__| |________-------------------_______| |__"<<endl;
    gotoxy(1,31);cout << "__   __________________________________   __"<<endl;
    gotoxy(1,32);cout << "  | |                                  | |  "<<endl;
    gotoxy(1,33);cout << "                                            "<<endl;
    gotoxy(18,29);cout << char(26);
    cursorShow();
    gotoxy(23,29); getline(cin, input);

        while(input.empty() || !containsOnlyIntegers(input)) {
            
            gotoxy(18,29);cout << char(26);
            cursorShow();
            gotoxy(23,29); getline(cin, input);
        

        }
    setcolor(white);

    option = stoi(input); //conversion
    while(option<5 && option > 0){
    if(option == 1){
        startGame();
    }
    else if(option == 2){
        instruction();
    }
    else if(option == 3){
        viewScore();
    }
    else if(option == 4){
        exit(0);
    }
    else
    setcolor(green);
    gotoxy(18,29);cout << char(26);
    cursorShow();
    gotoxy(23,29); getline(cin, input);
    setcolor(white);
    }

}
void resetGame() {
    pX = 11;
    pY = 1;
    health = 100;
    lives = 3;
    score = 0;
    // Reset other game variables as needed
}

void startGame(){
    
    system("cls");
    string in;
    string inn;

    setcolor(green);
    cout << "Enter Player name: ";
    getline(cin,name);
    while(name.empty() ||!containsOnlyAlphabets(name)) {

            cout << "Invalid input! Please enter a valid option." << endl;
            Sleep(400);
            getline(cin, name);
        

        }
    cout << "Select level(1-EASY, 2-MED, 3-HARD): ";
    getline(cin,in);

        while(in.empty() ||!containsOnlyIntegers(in)) {

            cout << "Invalid input! Please enter a valid option." << endl;
            Sleep(400);
            getline(cin, in);
        
        }
        
        level = stoi(in); //conversion
    cout << "Speed(100-150 recommended): ";
    getline(cin,inn);

        while(in.empty() ||!containsOnlyIntegers(inn)) {

            cout << "Invalid input! Please enter a valid option." << endl;
            Sleep(400);
            getline(cin, inn);
        

        }
        setcolor(white);
        speed = stoi(inn);
    system("cls");
    if(level ==1){
    cursorHide();
    drawMaze1(); // Redraw the maze
    }
    else if(level ==2){
    cursorHide();
    drawMaze2(); // Redraw the maze
    }
    else if(level ==3){
    cursorHide();
    drawMaze3(); // Redraw the maze
    }
    movePlayer();
    Sleep(1000);
    setcolor(blue);
    gotoxy(WIDTH +2,6);
    cout << "Press any key to";
    gotoxy(WIDTH +2,7);
    cout << "start the game...";
    setcolor(white);
    getch();
    system("cls");
    if(level ==1){
    cursorHide();
    drawMaze1(); // Redraw the maze
    }
    else if(level ==2){
    cursorHide();
    drawMaze2(); // Redraw the maze
    }
    else if(level ==3){
    cursorHide();
    drawMaze3(); // Redraw the maze
    }
    movePlayer();
    setcolor(blue);
    gotoxy(WIDTH +2,6);
    cout << "Use "<< char(26) << " key to hold...";
    gotoxy(WIDTH +2,7);
    cout << "Arrow keys to move...";
    setcolor(white);
    
    
    while (!gameOver)
    {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
    shootProjectile();
    }
    moveProjectile();
    updateGame();
    Sleep(speed);
 
    }
    system("cls");
    setcolor(brown);
    cout << "Player Name: ";
    cout << name <<endl;
    cout << "Your Health is: ";
    cout << health <<endl;
    cout << "Your score is: ";
    cout << score <<endl;
    cout << "Your Level was: ";
    cout << level <<endl;
    cout << "Your Speed was: ";
    cout << speed <<endl;
    cout << endl;
    Sleep(1000);
    saveScore();
    cout << "Press any key to continue...";
    setcolor(white);
    getch();
    main();
   
}

void drawMaze1() {
    cursorHide();
    const char mazeLayout[HEIGHT][WIDTH + 1] = {
    "@@@@@@@@@@@@@@@@@@@@@@",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#%%%%%%%%%%%         #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#      %%%%%%%%%     #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#         %%%%%%%%%%%#",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#____________________#",
    "######################"
};

    // Copy maze layout to maze array
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = mazeLayout[i][j];
        }
    }

    

    // Draw the maze on the console
    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
           gotoxy(j,i); 
            if (maze[i][j] =='#')
            {   setcolor(brown);
                cout << char(219);
                setcolor(white);            
            }
            else if (maze[i][j] == '_' || maze[i][j] == '%')
            {   setcolor(red);
                cout << char(30);
                setcolor(white);
            }
            
            else if (maze[i][j] == '@')
            {   setcolor(brown);
                cout << char(220);
                setcolor(white);
            }
            else if (maze[i][j] == '.')
            {   setcolor(green);
                cout << char(250);
                setcolor(white);
            }
           
            else cout <<maze[i][j];
    
    }   
       
}

}
void drawMaze2() {
    cursorHide();
    const char mazeLayout[HEIGHT][WIDTH + 1] = {
    "@@@@@@@@@@@@@@@@@@@@@@",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#%%%%%%%%%%%         #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          %%%%%%%%%%#",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#%%%%%%%%%%%         #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          %%%%%%%%%%#",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#____________________#",
    "######################"
};

    // Copy maze layout to maze array
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = mazeLayout[i][j];
        }
    }

    

    // Draw the maze on the console
    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
           gotoxy(j,i); 
            if (maze[i][j] =='#')
            {   setcolor(brown);
                cout << char(219);
                setcolor(white);            
            }
            else if (maze[i][j] == '_' || maze[i][j] == '%')
            {   setcolor(red);
                cout << char(30);
                setcolor(white);
            }
            
            else if (maze[i][j] == '@')
            {   setcolor(brown);
                cout << char(220);
                setcolor(white);
            }
            else if (maze[i][j] == '.')
            {   setcolor(green);
                cout << char(250);
                setcolor(white);
            }
           
            else cout <<maze[i][j];
    
    }   
       
}
}
void drawMaze3() {
    cursorHide();
    const char mazeLayout[HEIGHT][WIDTH + 1] = {
    "@@@@@@@@@@@@@@@@@@@@@@",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#      %%%%%%%%      #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#%%%%%%        %%%%%%#",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#      %%%%%%%%%     #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#%%%%%%        %%%%%%#",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#          .         #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#                    #",
    "#____________________#",
    "######################"
};

    // Copy maze layout to maze array
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = mazeLayout[i][j];
        }
    }

    

    // Draw the maze on the console
    for (int i = 0; i < HEIGHT; i++) 
    {
        for (int j = 0; j < WIDTH; j++) 
        {
           gotoxy(j,i); 
            if (maze[i][j] =='#')
            {   setcolor(brown);
                cout << char(219);
                setcolor(white);            
            }
            else if (maze[i][j] == '_' || maze[i][j] == '%')
            {   setcolor(red);
                cout << char(30);
                setcolor(white);
            }
            
            else if (maze[i][j] == '@')
            {   setcolor(brown);
                cout << char(220);
                setcolor(white);
            }
            else if (maze[i][j] == '.')
            {   setcolor(green);
                cout << char(250);
                setcolor(white);
            }
           
            else cout <<maze[i][j];
    
    }   
       
}

}

void instruction(){
    system("cls");
    setcolor(brown);
    cout << " Welcome to Spacecraft Landing Game!"<<endl<<endl;
    setcolor(white);
    setcolor(cyan);
    cout << char(26)<<" Use Restore Down button for best experience."<<endl;
    cout << char(26)<<" Select a level (EASY, MEDIUM, HARD)."<<endl;
    cout << char(26)<<" Note: Speed input is in descending order."<<endl;
    cout << char(26)<<" Use arrow keys to move the spacecraft."<<endl;
    cout << char(26)<<" The spacecraft will contanly move downward."<<endl;
    cout << char(26)<<" Use Up key "<<char(24)<<" to hold the spacecraft."<<endl;
    cout << char(26)<<" Avoid obstacles."<<endl;
    cout << char(26)<<" Land on the finish point precisely to win."<<endl;
    cout << char(26)<<" Shoot enemies with SPACE key."<<endl;
    cout << char(26)<<" Watch your health, lives!"<<endl;
    cout << char(26)<<" Health will reduce on each move of the player."<<endl;
    cout << char(26)<<" Good luck and enjoy the game!"<<endl<<endl;
    setcolor(white);
    setcolor(brown);
    cout << char(26)<<" Press any key to continue..."<<endl;
    setcolor(white);
    getch();
    main();


}

void loseGame()
{   cursorHide();
    system("cls");
    resetGame();
   setcolor(red);
    cout << " __  __ ___ ____ ____ ___ ___  _   _ " << endl;
    cout << "|  \\/  |_ _/ ___/ ___|_ _/ _ \\| \\ | |" << endl;
    cout << "| |\\/| || |\\___ \\___ \\| | | | |  \\| |" << endl;
    cout << "| |  | || | ___) |__) | | |_| | |\\  |" << endl;
    cout << "|_|  |_|___|____/____/___\\___/|_| \\_|" << endl;
    cout << " _____ _    ___ _     _____ ____    _" << endl;
    cout << "|  ___/ \\  |_ _| |   | ____|  _ \\ | |    " << endl;
    cout << "| |_ / _ \\  | || |   |  _| | | | || |   " << endl;
    cout << "|  _/ ___ \\ | || |___| |___| |_| || | " << endl;
    cout << "|_|/_/   \\_\\___|_____|_____|____/ (_) " << endl << endl;
    Sleep(1000);
    setcolor(white);
    setcolor(brown);
    cout << char(26)<<" Press any key to continue..."<<endl;
    setcolor(white);
    getch();


}

void endGame()
{
   cursorHide();
       system("cls");
       resetGame();
   setcolor(blue);
    cout << "__        _____ _   _ _   _ _____ ____  " << endl;
    cout << "\\ \\      / /_ _| \\ | | \\ | | ____|  _ \\ " << endl;
    cout << " \\ \\ /\\ / / | ||  \\| |  \\| |  _| | |_) |" << endl;
    cout << "  \\ V  V /  | || |\\  | |\\  | |___|  _ < " << endl;
    cout << "   \\_/\\_/  |___|_| \\_|_| \\_|_____|_| \\_\\" << endl;
    cout << "__        _____ _   _ _   _ _____ ____  " << endl;
    cout << "\\ \\      / /_ _| \\ | | \\ | | ____|  _ \\ " << endl;
    cout << " \\ \\ /\\ / / | ||  \\| |  \\| |  _| | |_) |" << endl;
    cout << "  \\ V  V /  | || |\\  | |\\  | |___|  _ < " << endl;
    cout << "   \\_/\\_/  |___|_| \\_|_| \\_|_____|_| \\_\\ " << endl;
    cout << "  ____ _   _ ___ ____ _  _______ _   _  " << endl;
    cout << " / ___| | | |_ _/ ___| |/ / ____| \\ | | " << endl;
    cout << "| |   | |_| || | |   | ' /|  _| |  \\| | " << endl;
    cout << "| |___|  _  || | |___| . \\| |___| |\\  | " << endl;
    cout << " \\____|_| |_|___\\____|_|\\_\\_____|_| \\_| " << endl;
    cout << "   ____ ___ _   _ _   _ _____ ____  _     " << endl;
    cout << "  |  _ \\_ _| \\ | | \\ | | ____|  _ \\| |    " << endl;
    cout << "  | | | | ||  \\| |  \\| |  _| | |_) | |    " << endl;
    cout << "  | |_| | || |\\  | |\\  | |___|  _ <|_|    " << endl;
    cout << "  |____/___|_| \\_|_| \\_|_____|_| \\_(_)    " << endl<<endl;
    Sleep(1000);
    setcolor(white);
    setcolor(brown);
    cout << char(26)<<" Press any key to continue..."<<endl;
    setcolor(white);
    getch();
}

void livesEnded()
{
   resetGame();
setcolor(lightred);
    cout << " ____  _____ _____ _____ _____ ____  " << endl;
    cout << "| __ )| ____|_   _|_   _| ____|  _ \\ " << endl;
    cout << "|  _ \\|  _|   | |   | | |  _| | |_) |" << endl;
    cout << "| |_) | |___  | |   | | | |___|  _ < " << endl;
    cout << "|____/|_____| |_|   |_| |_____|_| \\_\\" << endl;
    cout << "       _    _   _  ____ _  __        " << endl;
    cout << "      | |  | | | |/ ___| |/ /" << endl;
    cout << "      | |  | | | | |   | ' /  " << endl;
    cout << "      | |__| |_| | |___| . \\    " << endl;
    cout << "      |____\\___/ \\____ |_|\\_\\  " << endl;
    cout << "       _   _ _______  _______      " << endl;
    cout << "      | \\ | | ____\\ \\/ /_   _|  " << endl;
    cout << "      |  \\| |  _|  \\  /  | |    " << endl;
    cout << "      | |\\  | |___ /  \\  | |    " << endl;
    cout << "      |_| \\_|_____/_/\\_\\ |_|    " << endl;
    cout << "      _____ ___ __  __ _____  " << endl;
    cout << "     |_   _|_ _|  \\/  | ____| " << endl;
    cout << "       | |  | || |\\/| |  _|   " << endl;
    cout << "       | |  | || |  | | |___  " << endl;
    cout << "       |_| |___|_|  |_|_____| " << endl;
    setcolor(white);
    Sleep(1000);
    setcolor(brown);
    cout << char(26)<<" Press any key to continue..."<<endl;
    setcolor(white);
    getch();
  

}
void shootProjectile() {
    if (!projectileActive) {
        projectileX = pX;
        projectileY = pY + 1;
        projectileActive = true;
    }
}

void moveProjectile() {
    if (projectileActive) {
        gotoxy(projectileX, projectileY);
        cout << " ";

        projectileY++;

        if (projectileY >= HEIGHT - 2 || maze[projectileY][projectileX] == '#' || maze[projectileY][projectileX] == '%' || maze[projectileY][projectileX] == char(219)) {
            projectileActive = false;
        } else {
            gotoxy(projectileX, projectileY);
            cout << char(248); // Symbol representing the projectile 
        }
    }
}


void moveFinishPoint() {
    cursorHide();
    setcolor(green);

    gotoxy(FinishPointX, FinishPointY);
    cout << "  ";
    FinishPointX += FinishPointSpeed;

    if (FinishPointX <= 1 || FinishPointX >= WIDTH - 3 || maze[HEIGHT][WIDTH] == char(220)) {
        FinishPointSpeed = -FinishPointSpeed; // Change direction
    }

    // Display the FinishPoint at its new position
    gotoxy(FinishPointX, FinishPointY);

    cout << char(127)<<char(127); // You can change this character to represent the FinishPoint
    setcolor(white);

    if(pX == FinishPointX && pY == FinishPointY){
        gameOver = true;
        system("cls"); 
        endGame();
        
    }
}

void movePlayer() {
    cursorHide();
    setcolor(blue);
    gotoxy(pX, pY);
    cout << " ";
    // Apply gravity to the player
    gravity();

    if (GetAsyncKeyState(VK_UP) & 0x8000 && pY > 1) {
        pY--; // Move up
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && pY < HEIGHT - 2) {
        pY++; // Move down
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && pX > 1) {
        pX--; // Move left
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && pX < WIDTH - 2) {
        pX++; // Move right
    }

    gotoxy(pX, pY);
    cout << char(202);
    setcolor(white);
    
}

void gravity()
{
    if (pY < HEIGHT - 1 && (pY == HEIGHT - 2 || (pY < HEIGHT - 2 ))) {
        pY++; 
    }
}

void drawEnemies() {
    setcolor(lightred);
     gotoxy(enemy1X, 10);
    cout << char(12);
    gotoxy(enemy2X, 20);
    cout << char(12);
    gotoxy(enemy3X, 30);
    cout << char(12);
    setcolor(white);
}


// Function to move enemies using gotoxy
void moveEnemies(int level) {
    
    // Update enemy positions based on the level
    
        setcolor(lightred);
    // Clear previous positions of enemies
    
    gotoxy(enemy1X, 10);
    cout << ' ';
    gotoxy(enemy2X, 18);
    cout << ' ';
    gotoxy(enemy3X, 33);
    cout << ' ';
// At level 1, make enemies move predictably
        enemy1X = (enemy1X + 1) % (WIDTH - 3) + 1;
        enemy2X = (enemy2X + 2) % (WIDTH - 3) + 1;
        enemy3X = (enemy3X + 3) % (WIDTH - 3) + 1;

        gotoxy(enemy1X, 10);
        cout << char(12);
        gotoxy(enemy2X, 18);
        cout << char(12);
        gotoxy(enemy3X, 33);
        cout << char(12);
        setcolor(white);


}






void checkCollision() 
{   cursorHide();
    // Check for collision between the player and an enemy
    if (pX == enemy1X && pY == enemy1Y) {
        lives--;
            if (lives <= 0) {
                gameOver = true;
                livesEnded();
            } else {
                lives = 3;
            }
        
        pX = 11; // return to upper position
        pY = 1;
    } else if (pX == enemy2X && pY == enemy2Y) {
        
            lives--;
            if (lives <= 0) {
                gameOver = true;
                livesEnded();
            } else {
                lives = 3;
            }
        
        pX = 11;// return to upper position
        pY = 1;
    } else if (pX == enemy3X && pY == enemy3Y) {
        
            lives--;
            if (lives <= 0) {
                gameOver = true;
                livesEnded();
            } else {
                lives = 3;
            }
        
        pX = 11;// return to upper position
        pY = 1;
    }

    // Check for collision between the projectile and an enemy
   
        if (maze[pY][pX] == '.') {
            score += 10;
        }
    
    
    if(maze[pY][pX]=='_' ){
        gameOver = true;
        system("cls");
        loseGame();
        
    }
    if(maze[pY][pX]=='%' ){
        gameOver = true;
        system("cls");
        loseGame();
        
    }
     cursorHide();
    gotoxy(WIDTH +2, 1);
    cout << "PLayer name: "<<name;
    gotoxy(WIDTH +2, 2);

    gotoxy(WIDTH +2, 3);
    cout << "Lives: ";
    for (int i = 0; i < lives; i++) {
        cout << char(220);
    }

    gotoxy(WIDTH +2, 4);
    cout << "Score: " << score;
    
    gotoxy(WIDTH +2,5);
    cout << "Health :";
    fuel();
   
}
void fuel()
{   setcolor(cyan);
     for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            if (i < health / 10)
            {
                gotoxy(31 + i, 5+ j);
                cout << char(220);
            }
            else
            {
                gotoxy(31 + i, 5+ j);
                cout << " ";
            }
        }
    }
    health -= 1; // Reduce the health level by 5 units for each move
    setcolor(white);
    if (health <= 0)
    {
        gameOver = true;
        livesEnded(); // The player has run out of health
        
    }
}
void updateGame() {
       
    cursorHide();
    movePlayer();
    moveFinishPoint(); // Update FinishPoint position
    moveEnemies(level);// Update enemies to random positions
    checkCollision();
}

void saveScore() {
    ofstream scoreFile("scores.txt", ios::app); // Open a file to append scores

    if (scoreFile.is_open()) {
        scoreFile << "Player: " << name << ", Score: " << score << ", Lives: " << lives << ", Health: " << health << ", Level: " << level << ", Speed: " << speed << endl;
        scoreFile.close();
        cout << "Score saved successfully." << endl;
    } else {
        cout << "Unable to save the score." << endl;
    }
}
void viewScore() {
    system("cls");
   
    ifstream scoreFile("scores.txt");

    if (scoreFile.is_open()) {
        string line;
         setcolor(brown);
        cout << "----- Saved Scores -----" << endl;
         setcolor(white);
         setcolor(cyan);
        while (getline(scoreFile, line)) {
            cout << line << endl;
        }
        scoreFile.close();
    } else {
        cout << "Unable to open the scores file." << endl;
    }
     setcolor(brown);
    cout << "Press any key to continue...";
    getch();
    setcolor(white);
    main();
    
}
string setcolor(int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
void cursorHide()
{
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}
void cursorShow()
{
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hStdOut, &curInfo);
}
void resizeConsole() {
    COORD coord;
    SMALL_RECT rect;
    HWND console = GetConsoleWindow();

    coord.X = 46; 
    coord.Y = 40; 

    rect.Left = 0;
    rect.Top = 0;
    rect.Right = 46; 
    rect.Bottom = 40;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
}
bool containsOnlyAlphabets(string word) // It validates if the required input are alphabets
{
    bool result = true;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int asciiCode = word[i];

        if (asciiCode < 65 || asciiCode > 122)
        {
            result = false;

            break;
        }
    }

    return result;
}
bool containsOnlyIntegers(string integer) // It validates if the required input are integers
{
    bool result = true;

    for (int i = 0; integer[i] != '\0'; i++)
    {
        int asciiCode = integer[i];

        if (asciiCode < 48 || asciiCode > 57)
        {
            result = false;

            break;
        }
    }

    return result;
}