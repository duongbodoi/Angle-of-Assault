#pragma once
#include"Mainfunc.h"
#include"Basetexture.h"
void draw_powerbar(SDL_Renderer* screen, int v0,int x,int y,int last_v0);
void draw_angle_control_L(SDL_Renderer* screen, int phi, int x, int y, Ltexture angle_, Ltexture arrow_);
void draw_angle_control_R(SDL_Renderer* screen, int phi, int x, int y, Ltexture angle_, Ltexture arrow_);
void draw_HP(SDL_Renderer* screen, int hp, int max_hp, int x, int y);