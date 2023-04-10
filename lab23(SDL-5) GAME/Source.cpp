#define BALL_COUNT 5
#pragma comment(lib, "SDL2_mixer.lib")
#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>. 
#include "SDL_image.h"
#include <cmath>
#include "SDL_mixer.h"

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 130,140,50 };
	SDL_Color back_color = { 188,155,166 };
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}


void loadmusic()
{
	Mix_Music* fon = Mix_LoadMUS("1.wav");
	Mix_PlayMusic(fon, -1);

}
void sound(char* name)
{
	Mix_Chunk* Sound = NULL;
	Sound = Mix_LoadWAV(name);
	Mix_PlayChannel(-1, Sound, 0);
}


void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 0,0, 70, 200 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void init_balls(SDL_Rect balls[], int count)
{
	for (int i = 0; i < count; i++)
	{
		balls[i] = { i * 100 + 110,i * 100 + 10 ,50 + 10 * i ,50 + 10 * i };
	}
}

void draw_balls(SDL_Renderer*& renderer, SDL_Rect balls[],
	int count, SDL_Texture* texture)
{
	for (int i = 0; i < count; i++)
	{
		if (balls[i].w == 0) continue;
		SDL_RenderCopy(renderer, texture, NULL, &balls[i]);
	}
}

bool is_ball_hit(SDL_Rect ball, int x, int y)
{
	if (ball.w == 0) return false;
	int centerX = ball.x + ball.w / 2;
	int centerY = ball.y + ball.h / 2;
	int radius = ball.w / 2;
	return sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)) < radius;
}


int main(int argc, char** argv)
{
	
	Mix_Music* fon = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Click the balls",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Text.ttf", 100);
	SDL_Texture* textTexture;

	SDL_Rect balls[BALL_COUNT];
	init_balls(balls, BALL_COUNT);
	SDL_Surface* ballImage = IMG_Load("1.bmp");
	SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
	SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
	SDL_FreeSurface(ballImage);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	int k = 0;
	char text[10];
	_itoa_s(k, text, 10);
	textTexture = get_text_texture(renderer, text, my_font);

	SDL_Event event;
	bool quit = false;
	loadmusic();
	char name[] = "1.wav";
	while (!quit)
	{
		sound(name);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				for (int i = 0; i < BALL_COUNT; i++)
				{
					if (is_ball_hit(balls[i], event.button.x, event.button.y))
					{
						balls[i].w = balls[i].h = 0;
						k++;
						_itoa_s(k, text, 10);
						SDL_DestroyTexture(textTexture);
						textTexture = get_text_texture(renderer, text, my_font);
					}
				}
			}

		}
		/* Игровая логика */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		draw_balls(renderer, balls, BALL_COUNT, ballTexture);
		draw_text(renderer, textTexture);
		/* Отрисовка сцены */
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(ballTexture);
	TTF_CloseFont(my_font);
	TTF_Quit();

	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
