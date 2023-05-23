#pragma once
#include <iostream>
#include<SDL.h>
class Test {
public:
    Test(SDL_Renderer* render, int w, int h):render(render), w(w), h(h){
        std::cout << "construct Test..." << std::endl;
    };

    ~Test() {
        std::cout << "destruct Test..." << std::endl;
    }
public:
    int testRtsp();
private:
    int h;
    int w;
    SDL_Renderer* render = nullptr;
};