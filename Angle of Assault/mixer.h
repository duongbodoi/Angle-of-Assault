#pragma once
#include"Mainfunc.h"
#include"Basetexture.h"
class SoundEffect {
public:
    SoundEffect();
    ~SoundEffect();
    bool Load(const std::string& path);
    void Play(int loop = 0);     // loop = 0: 1 lần, -1: lặp vô hạn
    void Stop();
    bool IsPlaying() const;
    void setcheck(bool set) { check = set; }
    bool getcheck() { return check; }
 private:
    Mix_Chunk* sound;
    int channel;  // kênh đang phát
    bool check;
};
