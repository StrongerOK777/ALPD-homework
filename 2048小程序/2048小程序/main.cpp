#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// 函数声明
void wait_for_enter();
void print_menu();
void print_help();
void print_exit();
void print_interface(int board[4][4], int score, int step);
void play_game();
bool move_left(int board[4][4], int& score);
bool move_right(int board[4][4], int& score);
bool move_up(int board[4][4], int& score);
bool move_down(int board[4][4], int& score);
void add_random_tile(int board[4][4]);
bool is_game_over(int board[4][4]);
bool has_2048(int board[4][4]);
void initialize_board(int board[4][4]);
void play_game()
{
    int board[4][4] = {},score = 0,step = 0; 
    bool game_won = false;
    initialize_board(board);
    print_interface(board, score, step);
    while (true){
        int ch = _getch();
        if (ch == 27) return; 
        else if (ch == 0 || ch == 224){
            ch = _getch();
            bool moved = false;
            switch (ch){
            case 75:
                moved = move_left(board, score);
                break;
            case 77: 
                moved = move_right(board, score);
                break;
            case 72:
                moved = move_up(board, score);
                break;
            case 80:
                moved = move_down(board, score);
                break;
            }
            if (moved){
                step++;
                add_random_tile(board);
                if (!game_won && has_2048(board)){
                    game_won = true;
                    print_interface(board, score, step);
                    cout << "恭喜！你达到了2048！" << endl;
                    cout << "是否继续游戏？(y/n): ";
                    char choice = _getch();
                    if (choice == 'n' || choice == 'N')
                    return;
                }
            }
            if (is_game_over(board)){
                print_interface(board, score, step);
                cout << "游戏结束！最终得分: " << score << "，步数: " << step << endl;
                wait_for_enter();
                return;
            }
            print_interface(board, score, step);
        }
    }
}
void initialize_board(int board[4][4]){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
    add_random_tile(board);
    add_random_tile(board);
}
bool move_left(int board[4][4], int& score){
    bool moved = false;
    for (int i = 0; i < 4; i++){
        int tot = 0, r = 0, tmp[10] = {}, row[10] = {};
        for (int j = 0; j < 4; j++)
            if (board[i][j] != 0)
                tmp[tot++]=board[i][j];
        tot = 0;
        for (int j = 0; j < 4; j++)
            if (tmp[r] == tmp[r+1]){
                row[tot++]=tmp[r] *2;
                r += 2;
                score += row[tot];
                moved = true;
            }
            else row[tot++] = tmp[r++];
        for (int j = 0; j < 4; j++){
            if (board[i][j] != row[j])
                moved = true;
            board[i][j] = row[j];
        }
    }
    return moved;
}
bool move_right(int board[4][4], int& score){
    bool moved = false;
    for (int i = 0; i < 4; i++){
        int tot = 0, r = 0, tmp[10] = {}, row[10] = {};
        for (int j = 3; j >= 0; j--)
            if (board[i][j] != 0)
                tmp[tot++] = board[i][j];
        tot = 0;
        for (int j = 0; j < 4; j++)
            if (tmp[r] == tmp[r + 1]) {
                row[tot++] = tmp[r] * 2;
                r += 2;
                score += row[tot];
                moved = true;
            }
            else row[tot++] = tmp[r++];
        for (int j = 0; j < 4; j++)
        {
            int new_value = row[3 - j];
            if (board[i][j] != new_value)moved = true;
            board[i][j] = new_value;
        }
    }
    return moved;
}
bool move_up(int board[4][4], int& score){
    bool moved = false;
    for (int j = 0; j < 4; j++){
        int tot = 0, r = 0, tmp[10] = {}, row[10] = {};
        for (int i = 0; i < 4; i++)
            if (board[i][j] != 0)
                tmp[tot++] = board[i][j];
        tot = 0;
        for (int i = 0; i < 4; i++)
            if (tmp[r] == tmp[r + 1]) {
                row[tot++] = tmp[r] * 2;
                r += 2;
                score += row[tot];
                moved = true;
            }
            else row[tot++] = tmp[r++];
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j] != row[i])
                moved = true;
            board[i][j] = row[i];
        }
    }
    return moved;
}
bool move_down(int board[4][4], int& score)
{
    bool moved = false;
    for (int j = 0; j < 4; j++){
        int tot = 0, r = 0, tmp[10] = {}, row[10] = {};
        for (int i = 3; i >=0; i--)
            if (board[i][j] != 0)
                tmp[tot++] = board[i][j];
        tot = 0;
        for (int i = 0; i < 4; i++)
            if (tmp[r] == tmp[r + 1]) {
                row[tot++] = tmp[r] * 2;
                r += 2;
                score += row[tot];
                moved = true;
            }
            else row[tot++] = tmp[r++];
        for (int i = 0; i < 4; i++)
        {
            int new_value = row[3 - i];
            if (board[i][j] != new_value)
                moved = true;
            board[i][j] = new_value;
        }
    }
    return moved;
}
void add_random_tile(int board[4][4]){
    struct node {
        int a, b;
    }empty_cells[20];
    int tot = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                empty_cells[tot].a = i, empty_cells[tot].b = j, tot++;
    if (tot==0)return;
    int index = rand() % tot;
    int i = empty_cells[index].a;
    int j = empty_cells[index].b;
    board[i][j] = (rand() % 10 == 0) ? 4 : 2;
}
bool is_game_over(int board[4][4]){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                return false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i < 3 && (board[i][j] == board[i + 1][j]|| board[i][j] == board[i][j + 1]))
                return false;
    return true;
}
bool has_2048(int board[4][4]){
    for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++)
        if (board[i][j] == 2048)
            return true;
    return false;
}
int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    char choice = '\0';
    SetConsoleTitle(TEXT("2048"));
    while (true){
        print_menu();
        choice = _getche();
        switch (choice){
        case 'a':
            play_game();
            break;
        case 'b':
            print_help();
            break;
        case 'c':
            print_exit();
            return 0;
        default:
            cout << "\n输入错误，请重新输入" << endl;
            wait_for_enter();
        }
    }
    return 0;
}
void wait_for_enter(){
    cout << endl << "按回车键继续";
    while (_getch() != '\r');
    cout << endl << endl;
}
void print_menu(){
    system("CLS");
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout << "--------------------------------------------\n";
    cout << "********************************************\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "                   2048\n";
    cout << "                a.经典模式\n";
    cout << "                b.游戏规则\n";
    cout << "                c.退出游戏\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout << "********************************************\n";
    cout << "--------------------------------------------\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n请输入你的选择(a-c):";
}
void print_help()
{
    system("CLS");
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout << "--------------------------------------------\n";
    cout << "********************************************\n\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "操作说明：\n\n";
    cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
    cout << "游戏介绍：\n\n";
    cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
    cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
    cout << "如果得到数字2048，则游戏胜利!\n";
    cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
    cout << "********************************************\n";
    cout << "--------------------------------------------\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    wait_for_enter();
}
void print_exit(){
    cout << "\n退出中";
    for (int i = 4; i > 0; --i){
        Sleep(200);
        cout << ".";
    }
}
void print_interface(int board[4][4], int score, int step){
    system("CLS");
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "            --------------------------------------------\n";
    cout << "            分数：" << setw(6) << score << "              步数：" << setw(6) << step << endl;
    cout << "            --------------------------------------------\n";
    cout << "            ********************************************\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "                       |----|----|----|----|\n";
    for (int i = 0; i < 4; i++){
        cout << "                       |";
        for (int j = 0; j < 4; j++)
            if (board[i][j] != 0)cout << setw(4) << board[i][j] << "|";
            else cout << "    |";
        cout << "\n                       |----|----|----|----|\n";
    }
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "            ********************************************\n";
    cout << "            --------------------------------------------\n";
    cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
    SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}