#include"mixer.h"
SoundEffect::SoundEffect() : sound(nullptr),  check(false), channel(-1) {}

SoundEffect::~SoundEffect() {
    if (sound) {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
}

bool SoundEffect::Load(const std::string& path) {
    sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        SDL_Log("Failed to load sound: %s", Mix_GetError());
        return false;
    }
    return true;
}

void SoundEffect::Play(int loop) {
    if (sound) {
        Stop();  // dừng âm trước nếu đang phát
        channel = Mix_PlayChannel(-1, sound, loop);
    }
}

void SoundEffect::Stop() {
    if (IsPlaying()) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}

bool SoundEffect::IsPlaying() const {
    return channel != -1 && Mix_Playing(channel) != 0;
}