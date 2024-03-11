
#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "MainObject.h"
#include <string.h>
#include "TextObject.h"
#include "dot.h"
BaseObject g_background;

TTF_Font* font_score = NULL;
TTF_Font* font_pause = NULL;

int coins = 0;
int init2 = Mix_Init(0);
int quack_time = 0;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);

    if (ret < 0) {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }

    if (TTF_Init() == -1)
    {
        success = false;
    }
    font_score = TTF_OpenFont("font//SuperMario256.ttf", 30);
    if (font_score == NULL)
    {
        success = false;
    }
    font_pause = TTF_OpenFont("font//SuperMario256.ttf", 50);
    if (font_pause == NULL) {
        success = false;
    }
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();

    
}



int main(int argc, char* argv[])
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    Mix_Chunk* sound = Mix_LoadWAV("sound//coins_sound.wav");
    if (!sound) {
        std::cout << "sound error: " << Mix_GetError() ;
    }
    Mix_Chunk* sound_10 = Mix_LoadWAV("sound//10diem.mp3");
    if (!sound_10)
    {
        std::cout << " sound error: " << Mix_GetError;
    }
    Mix_Chunk* sound_quack = Mix_LoadWAV("sound//quack.mp3");
    if (!sound_quack) {
        std::cout << "sound error: " << Mix_GetError;
    }
    Mix_Music* music = Mix_LoadMUS("sound//background_music.wav");
    if (!music)
    {
        std::cout << "music error: " << Mix_GetError();
    }
    
    

    ImpTimer fps_time;

    if (InitData() == false)
        return -1;

    if (LoadBackground() == false)
        return -1;

    GameMap game_map;

    game_map.LoadMap("map//map01.dat");
    game_map.LoadTiles(g_screen);
    

    MainObject p_player;
    p_player.LoadImg("img//player sprite//player_right.png", g_screen);
    p_player.set_clips();


    bool is_quit = false;
    bool is_pause = false;
   
    TextObject score;
    score.SetColor(TextObject::WHITE_TEXT);

    TextObject pause;
    pause.SetColor(TextObject::BLACK_TEXT);

    Mix_PlayMusic(music, -1);
   
    int diem = 0;

    while (!is_quit)
    {

        fps_time.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }
        if (g_event.type == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE) {
            is_pause = true;
            
        }
        while (is_pause && !is_quit)
        {   
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }
               p_player.HandelInputAction(g_event, g_screen);

               if (g_event.type == SDL_KEYDOWN ) {
                   if (g_event.key.keysym.sym == SDLK_RETURN)
                       is_pause = false;
               }
            }
          
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);

            pause.SetText("Press 'Enter' to continue");
            pause.LoadFromRenderText(font_score, g_screen);
            pause.RenderText(g_screen, 1280/4,480/2 );
            SDL_RenderPresent(g_screen);

            int real_imp_time = fps_time.get_ticks();
            int time_one_frame = 1000 / FRAME_PER_SECOND; // time_ ms

            if (real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                SDL_Delay(delay_time);
            }
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        // Do player
        Map map_data = game_map.getMap();

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);
        p_player.HandleBullet(g_screen);

        std::string str_score = "Score: ";

        if (p_player.return_coins() > coins) {
            Mix_PlayChannel(-1, sound, 0);
        }
        if (coins > 0 && coins % 10 == 0) {
            if (diem == 0) {
                Mix_PlayChannel(-1, sound_10, 0);
                diem = 1;
            }
        }
        else {
            diem = 0;
        }
        if (p_player.return_collision()) {
            if (quack_time == 0) {
                Mix_PlayChannel(-1, sound_quack, 0);
                quack_time = 1;
            }
        }
        else {
            quack_time = 0;
        }

        coins = p_player.return_coins();

        str_score += std::to_string(coins);
        score.SetText(str_score);
        score.LoadFromRenderText(font_score, g_screen);
        score.RenderText(g_screen, SCREEN_WIDTH - 200, 25);
        SDL_RenderPresent(g_screen);

        //reset coins
        if (coins >= max_coins) {
            coins = 0;
            game_map.LoadMap("map//map01.dat");

            //tra ve giatri coins trong ham mainObject ve 0
            p_player.exept_coins(0);
          
            // them am thanh khi an het coins
        }

        int real_imp_time = fps_time.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND; // time_ ms

        if (real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            SDL_Delay(delay_time);
        }
    }
    

    close();

    return 0;
}
