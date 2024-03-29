#include "audio.hpp"

Audio::~Audio()
{
    SDL_CloseAudioDevice(deviceID);    
}

void Audio::load(const char* filename)
{
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play()
{
    SDL_ClearQueuedAudio(deviceID);
    SDL_QueueAudio(deviceID, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceID, 0);
}