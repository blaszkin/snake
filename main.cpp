#include <iostream>
#include <random>
#include <chrono>
#include <windows.h>

using namespace std;

pair<int8_t, int8_t>generate_fruit()
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist1(1, 70);
    std::uniform_int_distribution<int> dist2(1, 25);
    int fruit_x=dist1(rng);
    int fruit_y=dist2(rng);
    return {fruit_x, fruit_y};
}
void new_snake_position(vector<pair<int8_t, int8_t>>& old_snake_position, int8_t& snake_direction, bool& is_fruit_eaten)
{
    if(snake_direction==1) //up
    {
        old_snake_position.insert(old_snake_position.begin(), {old_snake_position[0].first, old_snake_position[0].second-1});
    }
    else if(snake_direction==2) //down
    {
        old_snake_position.insert(old_snake_position.begin(), {old_snake_position[0].first, old_snake_position[0].second+1});
    }
    else if(snake_direction==3) //left
    {
        old_snake_position.insert(old_snake_position.begin(), {old_snake_position[0].first-1, old_snake_position[0].second});
    }
    else if(snake_direction==4) //right
    {
        old_snake_position.insert(old_snake_position.begin(), {old_snake_position[0].first+1, old_snake_position[0].second});
    }
    if(is_fruit_eaten==0)
        {
            old_snake_position.pop_back();
        }
}
void write(vector<pair<int8_t, int8_t>>& snake_position, pair<int8_t, int8_t>&fruit)
{
    cout << "Your points:  "<< (snake_position.size()-1) *10 << "\n";
    int8_t screen[72][27]; //lenght and width walls included
    for(int i=0; i<72; i++)
    {
        screen[i][0]=219;
        screen[i][26]=219;
    }
    for(int i=0; i<27; i++)
    {
        screen[0][i]=219;
        screen[71][i]=219;
    }
    for(int i=1; i<71; i++)
        {
            for(int j=1; j<26; j++)
                {
                    screen[i][j]=32;
                }
        }
    screen[fruit.first][fruit.second]=248;
    for(auto i : snake_position)
        {
            screen[i.first][i.second]=254;
        }
    for(int j=0; j<27; j++)
        {
            for(int i=0; i<72; i++)
                {
                    cout <<screen[i][j];
                }
            cout <<"\n";
        }
}
bool is_alive(vector<pair<int8_t, int8_t>>& snake_position)
{
    if(snake_position[0].first == 0 || snake_position[0].first == 71)
    {
        return 0;
    }
    if(snake_position[0].second == 0 || snake_position[0].second == 26)
    {
        return 0;
    }
    for(int i=1; i<snake_position.size(); i++)
        {
            if(snake_position[i]==snake_position[0])
                return 0;
        }
    return 1;
}
bool is_fruit_eaten(vector<pair<int8_t, int8_t>>& snake_position, pair<int8_t, int8_t>&fruit_position)
{
    if(fruit_position==snake_position[0])
        return 1;
    return 0;
}
void setup()
{
    vector<pair<int8_t, int8_t>>snake;
    pair<int8_t, int8_t>starting_point={35,12};
    snake.push_back(starting_point);
    bool is_eaten=0;
    int8_t snake_direction=-1;
    pair<int8_t, int8_t>fruit_position=generate_fruit();
    cout << "Press any arrow to continue:" << endl;
    while(snake_direction==-1)
        {
            if(GetKeyState(VK_UP) & 0x8000)
            {
                snake_direction=1;
            }
            else if(GetKeyState(VK_DOWN) & 0x8000)
            {
                snake_direction=2;
            }
            else if(GetKeyState(VK_LEFT) & 0x8000)
            {
                snake_direction=3;
            }
            else if(GetKeyState(VK_RIGHT) & 0x8000)
            {
                snake_direction=4;
            }
        }
    while(is_alive(snake))
        {
            is_eaten=is_fruit_eaten(snake, fruit_position);
            new_snake_position(snake, snake_direction, is_eaten);
            if(is_eaten==true)
                {
                        is_eaten=false;
                        fruit_position=generate_fruit();
                }
            if(GetKeyState(VK_UP) & 0x8000)
            {
                if(snake_direction!=2)
                    snake_direction=1;
            }
            else if(GetKeyState(VK_DOWN) & 0x8000)
            {
                if(snake_direction!=1)
                    snake_direction=2;
            }
            else if(GetKeyState(VK_LEFT) & 0x8000)
            {
                if(snake_direction!=4)
                    snake_direction=3;
            }
            else if(GetKeyState(VK_RIGHT) & 0x8000)
            {
                if(snake_direction!=3)
                snake_direction=4;
            }
            Sleep(40);
            system("cls");
            write(snake,fruit_position);
        }
    cout << "Congratulations! You have scored " << (snake.size()-1)*10 << " points";
}

int main()
{
    char cont='x';
    while(cont!='n' and cont!='N')
        {
            setup();
            cout << endl << "Do you want to continue? [y/n]";
            cin >> cont;
        }

    return 0;
}
