#define BALL_COUNT 10
#pragma comment(lib, "SDL2_mixer.lib")
#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>. 
#include "SDL_image.h"
#include <cmath>
#include "SDL_mixer.h"
#include <time.h>
#include <iostream>
#include<malloc.h>
#include <locale.h>
#include <locale.h>


struct descriptionBall
{
	SDL_Texture* Ball;
	SDL_Texture* TextOnBall;
	SDL_Rect size;
};
SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 130,140,50 };
	SDL_Color back_color = { 188,0,200};
	textSurface = TTF_RenderText_Shaded(font, text, fore_color, back_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}

SDL_Texture* get_text_texture_balls(SDL_Renderer*& renderer, char* text, TTF_Font* font, SDL_Rect* rect)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = { 130,140,50 };
	textSurface = TTF_RenderText_Blended(font, text, fore_color);
	rect->w = textSurface->w;
	rect->h = textSurface->h;
	SDL_Texture* texture;
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return texture;
}


void loadmusic()
{
	Mix_Music* fon = Mix_LoadMUS("1.wav");
	Mix_PlayMusic(fon, -1);

}

void loadmusic2()
{
	Mix_Music* fon = Mix_LoadMUS("salam-meloboom.wav");
	Mix_PlayMusic(fon, 0);
	
	
}



void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 0,0, 70, 150 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_text2(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 100,75, 70, 150 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void draw_text_ball(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect balls[], int count, int index)
{
	for(int i =0;i<BALL_COUNT;++i)
	{
	SDL_Rect rect = { balls[index].x, balls[index].y, balls[index].w, balls[index].h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
}

void init_balls(SDL_Rect balls[], int count)
{
	int a, b;
	srand(time(NULL));
	for (int i = 0; i < count; i++)
	{
		a = rand() % 800;
		b = rand() % 600;
		balls[i] = { a,b ,50 + 10 * i ,50 + 10 * i };
	}
}

void move_on_sin(SDL_Rect balls[], int count)
{
	double x = 0; double y = 0;
	for (int i = 0; i < count; ++i)
	{
		for (double x = 0; x < 800; x += 0.1)
		{
			y = sin(x);
			balls[i].x = x;
			balls[i].y = y;
		}
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

bool is_star_hit(SDL_Rect True_Star, int x, int y)
{


		int centerX = True_Star.x + True_Star.w / 2;
		int centerY = True_Star.y + True_Star.h / 2;
		int radius = True_Star.w / 2;
		if (sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y)) < radius) return 1;
	

	return 0;
}






int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RUS");
	int choose = -2;
	float h = 600, w = 800;
	Mix_Music* fon = NULL;
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Click the balls",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
		SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("Text.ttf", 30);
	SDL_Texture* textTexture;
	SDL_Rect balls[BALL_COUNT];

	std::cout << " Choose ex:\n1 - 1\n2 - 2\n3 - 3\n";
	std::cin >> choose;
	switch (choose)
	{
	case 1:
	{
		
		SDL_Surface* ballImage = IMG_Load("1.bmp");
		SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
		init_balls(balls, BALL_COUNT);

		Mix_Init(0);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

		int k = 0;
		char text[10];
		char text1[10];

		_itoa_s(k, text, 10);
		textTexture = get_text_texture(renderer, text, my_font);
		SDL_Event event;
		bool quit = false;
		int randval[BALL_COUNT];
		srand(time(NULL));
		char name[] = "1.wav";
		char textballs[10];
		descriptionBall test[BALL_COUNT];
		int randnum[BALL_COUNT];
		for (int i = 0; i < BALL_COUNT; ++i)
		{
			randnum[i] = rand() % 10;
		}
		loadmusic();
		int gcount = 0;
		while (!quit)
		{

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					quit = true;

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < BALL_COUNT; i++)
					{
						if (is_ball_hit(balls[i], event.button.x, event.button.y))
						{
							 Mix_Chunk* fireMusic = Mix_LoadWAV("salam-meloboom.wav");
							 Mix_PlayChannel(-1, fireMusic, 0);
							balls[i].w = balls[i].h = 0;
							k += randnum[i];
							_itoa_s(k, text, 10);
							textTexture = get_text_texture(renderer, text, my_font);
							
						}
					}
				}

			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			gcount = 0;
			for (int i = 0; i < BALL_COUNT; ++i)
			{
				
				_itoa_s(randnum[i], text1, 10);
				SDL_Rect textRect;
			
				test[i].Ball = SDL_CreateTextureFromSurface(renderer, ballImage);
				test[i].TextOnBall = get_text_texture_balls(renderer, text1, my_font, &textRect);

				if (balls[i].w == 0)
				{
					gcount++;
					if (gcount == BALL_COUNT) return 0;
					continue;
				};
				SDL_Rect ballrect = { balls[i].x,balls[i].y,balls[i].w,balls[i].h };
				SDL_RenderCopy(renderer, test[i].Ball, NULL, &ballrect);

				textRect.x = (balls[i].x + int(w / 100.f));
				textRect.y = balls[i].y + balls[i].h / 4;
				SDL_RenderCopy(renderer, test[i].TextOnBall, NULL, &textRect);
				SDL_DestroyTexture(test[i].Ball);
				SDL_DestroyTexture(test[i].TextOnBall);

			}
			/* Игровая логика */
			draw_text(renderer, textTexture);
			/* Отрисовка сцены */
			SDL_RenderPresent(renderer);
			SDL_Delay(500);
		}

		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(my_font);
		TTF_Quit();
		SDL_FreeSurface(ballImage);
		Mix_CloseAudio();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	case 2:
	{
		
		Mix_Init(0);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
		descriptionBall test[BALL_COUNT];
		SDL_Surface* ballImage = IMG_Load("1.bmp");
		SDL_SetColorKey(ballImage, SDL_TRUE, SDL_MapRGB(ballImage->format, 255, 255, 255));
		int randnum[BALL_COUNT];
		for (int i = 0; i < BALL_COUNT; ++i)
		{
			randnum[i] = rand() % 10;
		}
		SDL_Rect ballrect[BALL_COUNT];
		SDL_Rect textRect;
		double x = 0; double y = 0;
		const double AMPLITUDE = 100.0;
		const double PERIOD = 600.0;
		const double STEP = 5.0;
		double time = 0.5;
		char text1[10];

		bool quit = false;


		int k = 0;
		char text[10];
		

		_itoa_s(k, text, 10);
		textTexture = get_text_texture(renderer, text, my_font);
		SDL_Event event;
		
		int randval[BALL_COUNT];
		
		char name[] = "1.wav";
		char textballs[10];
		double hh = 0;
		loadmusic();
		for (int i = 0; i < BALL_COUNT; ++i)
		{
			_itoa_s(randnum[i], text1, 10);
			test[i].Ball = SDL_CreateTextureFromSurface(renderer, ballImage);
			test[i].TextOnBall = get_text_texture_balls(renderer, text1, my_font, &textRect);
			x = (i) * ((w / (double)BALL_COUNT));
			y = AMPLITUDE * sin(2 * M_PI * (x / PERIOD + time));
			test[i].size.x = x;
			ballrect[i] = { int(x) ,int(y + 300),50,50 };
			textRect.x = (ballrect[i].x + int(w / 100.f));
			textRect.y = ballrect[i].y + ballrect[i].h / 4;

			
		}

		while (!quit)
		{
			
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					quit = true;

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < BALL_COUNT; i++)
					{
						if (is_ball_hit(ballrect[i], event.button.x, event.button.y))
						{
							 Mix_Chunk* fireMusic = Mix_LoadWAV("salam-meloboom.wav");
							 Mix_PlayChannel(-1, fireMusic, 0);loadmusic2();
							 ballrect[i].w = ballrect[i].h = 0;
							 k += randnum[i];
							_itoa_s(k, text, 10);
							textTexture = get_text_texture(renderer, text, my_font);

						}
					}
				}

			}
			hh += 0.5;
			for (int i = 0; i < BALL_COUNT; ++i)
			{
				
				if (ballrect[i].w == 0) continue;
				test[i].size.x += STEP;
				
				y = AMPLITUDE * sin(2 * M_PI * (x / PERIOD + time));
				if (ballrect[i].x >= 820)
				{
					ballrect[i].x = 0;
					
					test[i].size.x = 0;
					y = 300;
			
				}
				
			x = (i) * ((w / (double)BALL_COUNT));
				
				
				ballrect[i] = {test[i].size.x ,int(y + 300),rand() %(70- 40) + 40,50};
				
			

				SDL_RenderCopy(renderer, test[i].Ball, NULL, &ballrect[i]); // рисуем шарик в новом мест
				
			
				textRect.x = (ballrect[i].x + int(w / 100.f));
				textRect.y = ballrect[i].y + ballrect[i].h / 4;
				
				SDL_RenderCopy(renderer, test[i].TextOnBall, NULL, &textRect);
				

			}
			

			draw_text(renderer, textTexture);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
			time += STEP;
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
		}



	}break;
	case 3:
	{
		Mix_Init(0);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
		loadmusic();
		SDL_Surface* starImage = IMG_Load("star.bmp");
		SDL_Surface* Fon = IMG_Load("2.bmp");
		SDL_Texture* TextureForFon = SDL_CreateTextureFromSurface(renderer, Fon);
		SDL_Rect FullScreen = { 0,0,800,600 };
		SDL_RenderCopy(renderer, TextureForFon, NULL, &FullScreen);
		SDL_RenderPresent(renderer);
		SDL_SetColorKey(starImage, SDL_TRUE, SDL_MapRGB(starImage->format, 255, 255, 255));
		SDL_Event event;
		SDL_Texture** start_texture = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 5);
		SDL_Rect* stars = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 5);
		int a[5], b[5];

		char text[100] = {0};
		int count = 0;
		_itoa_s(count, text, 10);
		textTexture = get_text_texture(renderer, text, my_font);
		int n = 0;
		int nowx = 0,nowy = 0;
		int k = 0;
		int h = 0;
		SDL_Rect TrueStar;


		int try1 = 0;

		for (int i = 0; i <= 4; i++)
		{
			int c = rand() % (800 - 50); int m = rand() % (600 - 50);
			int j = 0;
			start_texture[i] = SDL_CreateTextureFromSurface(renderer, starImage);
			stars[i] = { c,m,50,50 };
			bool isOverlapping;
			do {
				c = rand() % (800 - 50);
				m = rand() % (600 - 50);
				isOverlapping = false;
				for (int j = 0; j < 4 + n; ++j) {
					if (j == 4 + n) continue;
					if ((abs(stars[j].x - c) <= 60 && abs(stars[j].y - m) <= 60) || (c < 100 && m < 200))
					{
						isOverlapping = true;
						break;
					}
				}
			} while (isOverlapping);
			SDL_RenderCopy(renderer, start_texture[i], NULL, &stars[i]);
			SDL_RenderPresent(renderer);
		}
		bool quit = false;
		while (!quit)
		{
			try1 = 0;

			while (SDL_PollEvent(&event))
			{
				
				if (event.type == SDL_QUIT)
					quit = true;
				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
				{

					if (k == 0)
					{
						n++;
						TrueStar = { event.button.x, event.button.y ,50,50 };
						start_texture[4 + n] = SDL_CreateTextureFromSurface(renderer, starImage);
						SDL_RenderCopy(renderer, start_texture[4+n], NULL, &TrueStar);
						k++;
						
					}
					if (is_star_hit(TrueStar, event.button.x, event.button.y))
					{
						k++;
						
						n++;
						stars = (SDL_Rect*)realloc(stars, sizeof(SDL_Rect) * 5 + sizeof(SDL_Rect) * n);
						int c = rand() % (800 - 50); int m = rand() % (600 - 50);
						start_texture[4 + n] = SDL_CreateTextureFromSurface(renderer, starImage);
						bool isOverlapping;
						do {
							try1++;
							c = rand() % (800 - 50);
							m = rand() % (600 - 50);
							isOverlapping = false;
							for (int j = 0; j < 4 + n; ++j) {
								if (j == 4 + n) continue;
								if ((abs(stars[j].x - c) <= 60 && abs(stars[j].y - m) <= 60) || (c < 100 && m < 200)) 
								{
									isOverlapping = true;
									break;
								}
							}
							if (count >= 15)
							{
								setlocale(LC_ALL, "RUS");
								SDL_DestroyWindow(window);
								SDL_Window* window = SDL_CreateWindow("End",
									SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300,
									SDL_WINDOW_SHOWN);
								SDL_Renderer* renderer2 = SDL_CreateRenderer(window, -1, 0);


								char text[100] = {0};
								_itoa_s(count, text, 10);
								SDL_DestroyTexture(textTexture);


								SDL_Texture* end = get_text_texture(renderer2, text, my_font);
								draw_text(renderer2, end);
								SDL_RenderPresent(renderer2);
								SDL_Delay(5000);
								return 0;
							}

						} while (isOverlapping);

						stars[4 + n] = { c,m,50,50 };
						SDL_RenderCopy(renderer, start_texture[4 + n], NULL, &stars[4 + n]);
						TrueStar = { c,m,50,50 };
						count += 1;
						_itoa_s(count, text, 10);
						if(text != "'\0'") textTexture = get_text_texture(renderer, text, my_font);

					}
					else
					{
						if(k>1)
						{
							
								SDL_DestroyWindow(window);
								SDL_Window* window = SDL_CreateWindow("End",
									SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300,
									SDL_WINDOW_SHOWN);
								SDL_Renderer* renderer1 = SDL_CreateRenderer(window, -1, 0);
								
								
								char text[100] = {0};
								SDL_DestroyTexture(textTexture);
								
								_itoa_s(count, text, 10);
								SDL_Texture *end = get_text_texture(renderer1, text, my_font);
								draw_text(renderer1, end);
								SDL_RenderPresent(renderer1);
								SDL_Delay(5000);
								return 0;

						}
				
					}
					
				}


			}

			draw_text(renderer, textTexture);
			SDL_RenderPresent(renderer);

		}
		std::cout << "Количество набранных очков:" << n;


		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(my_font);
		TTF_Quit();
		SDL_FreeSurface(starImage);
		Mix_CloseAudio();
		SDL_DestroyRenderer(renderer);
		
		SDL_Quit();

		return 0;
	}
	}
}
