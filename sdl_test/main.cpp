// main.cpp: 定义应用程序的入口点。
//
#include<SDL.h>
#include "main.h"



using namespace std;

int main(int argc, char* argv[])
{
    std::cout << "Test SDL" << std::endl;
	//初始化SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("can not init SDL:%s", SDL_GetError());
		return -1;
	}
	SDL_Window* window = SDL_CreateWindow("SDL SDL_Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
	


	bool quit = false;
	//循环窗口,不加循环窗口就咻的一下没了- -
	int offSet = 0;
	while (!quit)
	{
		//循环处理事件
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			std::cout << "event:" << event.type << std::endl;
			if (event.type == SDL_QUIT)
				quit = true;
			//这里可以其它事件处理了
		}
		SDL_Rect rect = { 200+offSet, 300, 100, 100 };
		SDL_RenderDrawRect(render, &rect);
		SDL_RenderPresent(render);
		//自己设置帧频的时候需要在这里计算delay的时间
		SDL_Delay(10);
		offSet++;
	}

	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
