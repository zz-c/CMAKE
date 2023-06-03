#include <SDL.h>
#include "PcmPlayer.h"
#include "AacPlayer.h"
#include "AacDecode.h"
#define SDL_MAIN_HANDLED

int main(int argc, char* argv[]) {
    PcmPlayer pcmPlayer;
    pcmPlayer.play();

    //runAac();

    //runDecode();

    return 0;
}