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
//
