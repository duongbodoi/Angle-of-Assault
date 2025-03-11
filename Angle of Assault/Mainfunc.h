#pragma once
#include<iostream>
#include <SDL.h> 
#include <SDL_image.h> 
#include <SDL_ttf.h> 
#include <stdio.h> 
#include <string> 
#include <sstream>
#include<cmath>
#define PI 3.14159265358979323846

using namespace std;
//
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event e;
// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
// move
typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
	int jumb;
	int reload;
	int shot;
};
// map
#define TILE_SIZE 64;
const int MAX_MAP_X = 50;
const int MAX_MAP_Y = 30;
typedef struct Map {
	int start_x; // kich thuoc thuc trong map to
	int start_y;

	int max_x;
	int max_y;

	std::string tile[MAX_MAP_Y][MAX_MAP_X];
	char* filename;
};
