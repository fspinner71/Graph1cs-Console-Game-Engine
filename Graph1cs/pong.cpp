//wuzard#4530

#include "graphics.h"

int p1score = 0;
int p2score = 0;
int velx = 1;
int vely = 1;

void gamehandler(rect &ball, rect &lplr, rect &rplr)
{
    int x = ball.position.X;
    int y = ball.position.Y;

    ball.position.X = x + velx;
    ball.position.Y = y + vely;

    if((x < 3 && y > lplr.position.Y && y < lplr.position.Y + lplr.size.Y)||(x > globalsize.X-4 && y > rplr.position.Y && y < rplr.position.Y + lplr.size.Y))
    {
        velx = -velx;
        ball.position.X = x + velx;

    }

    if(x <= 0)
    {
        p2score += 1;
        ball.position.X = globalsize.X/2;
        ball.position.Y = globalsize.Y/2;
        velx = -1;
        vely = -1;

        lplr.position.Y = (globalsize.Y/2)-((lplr.size.Y - lplr.size.Y%2)/2);
        rplr.position.Y = (globalsize.Y/2)-((rplr.size.Y - rplr.size.Y%2)/2);

    }else if(x >= globalsize.X-1)
    {
        p1score += 1;
        ball.position.X = globalsize.X/2;
        ball.position.Y = globalsize.Y/2;
        velx = 1;
        vely = 1;

        lplr.position.Y = (globalsize.Y/2)-((lplr.size.Y - lplr.size.Y%2)/2);
        rplr.position.Y = (globalsize.Y/2)-((rplr.size.Y - rplr.size.Y%2)/2);
    }
    if(y <= 0 || y >= globalsize.Y-1)
    {
        vely = -vely;
        ball.position.Y = y + vely;
    }
}

int main()
{
    COORD size = {50, 50};
    init(size, {16, 16}, "2 player pong");
    rect lplr;
    lplr.size = {1, 9};
    lplr.position.X = 1;
    lplr.position.Y = (globalsize.Y/2)-((lplr.size.Y - lplr.size.Y%2)/2);
    lplr.property = FOREGROUND_BLUE;
    lplr.construct();
    rect rplr;
    rplr.size = {1, 9};
    rplr.position.X = globalsize.X-2;
    rplr.position.Y = (globalsize.Y/2)-((rplr.size.Y - rplr.size.Y%2)/2);
    rplr.property = FOREGROUND_RED;
    rplr.construct();
    rect ball;
    ball.position.X = globalsize.X/2;
    ball.position.Y = globalsize.Y/2;
    ball.size = {1,1};
    ball.property = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    ball.construct();
    rect winnerscreen;
    winnerscreen.position = {0,0};
    winnerscreen.size.X = globalsize.X;
    winnerscreen.size.Y = globalsize.Y;
    bool playerwon = false;
    keypress keys;
    while (true)
    {
        gamehandler(ball, lplr, rplr);
        pollkeypresses(keys);
        if (keys.S)
        {
            if(lplr.position.Y+lplr.size.Y < globalsize.Y)
            {
                ++lplr.position.Y;
            }
        }
        if (keys.W)
        {
            if(lplr.position.Y > 0)
            {
                --lplr.position.Y;
            }
        }
        if (keys.DOWN)
        {
            if(rplr.position.Y+rplr.size.Y < globalsize.Y)
            {
                ++rplr.position.Y;
            }
        }
        if (keys.UP)
        {
            if(rplr.position.Y > 0)
            {
                --rplr.position.Y;
            }
        }
        clear();
        if(p1score == 3)
        {
            winnerscreen.property = BACKGROUND_BLUE | FOREGROUND_BLUE;
            winnerscreen.construct();
            playerwon = true;
        }
        if(p2score == 3)
        {
            winnerscreen.property = BACKGROUND_RED | FOREGROUND_RED;
            winnerscreen.construct();
            playerwon = true;
        }
        if(!playerwon)
        {
            draw(lplr);
            draw(rplr);
            draw(ball);
        }else
        {
            draw(winnerscreen);
            Sleep(3000);
            break;
        }
        Sleep(50);
    }
    return 0;
}