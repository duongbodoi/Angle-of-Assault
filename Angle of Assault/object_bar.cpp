#include"object_bar.h"
#include"Basetexture.h"
void draw_powerbar(SDL_Renderer* screen, int v0, int x, int y) {
    int width = v0;
    int height = 15;
    SDL_SetRenderDrawColor(screen, 50, 50, 50, 255);
    SDL_Rect background = { x - 2, y - 2, width + 4, height + 4 };
    SDL_RenderFillRect(screen, &background);

   
    SDL_SetRenderDrawColor(screen, 0, 255, 0, 100);
    SDL_Rect glow = { x - 1, y - 1, width + 2, height + 2 };
    SDL_RenderFillRect(screen, &glow);

    
    int startColor[3] = { 0, 127, 0 };
    int endColor[3] = { 0, 255, 0 };

    for (int i = 0; i < width; i++) {
        int r = startColor[0] + (endColor[0] - startColor[0]) * i / width;
        int g = startColor[1] + (endColor[1] - startColor[1]) * i / width;
        int b = startColor[2] + (endColor[2] - startColor[2]) * i / width;

        SDL_SetRenderDrawColor(screen, r, g, b, 255);
        SDL_Rect barSegment = { x + i, y, 1, height };
        SDL_RenderFillRect(screen, &barSegment);
    }

    
    SDL_SetRenderDrawColor(screen, 200, 255, 200, 255);
    SDL_Rect border = { x - 1, y - 1, width + 2, height + 2 };
    SDL_RenderDrawRect(screen, &border);
}
void draw_angle_control(SDL_Renderer* screen, int phi, int x, int y, Ltexture angle_, Ltexture arrow_) {
    if (!angle_.loadfromfile("img/angle.png", screen)) cout << "error angle";
    if (!arrow_.loadfromfile("img/arrow1.png", screen)) cout << "error arrow";
    angle_.set_rect(x, y);
    angle_.render(screen);
    
    SDL_Rect rect_angle = angle_.get_rect();
    
    SDL_Point centre = {0,0};
    arrow_.render360(screen, rect_angle.x, rect_angle.y+205, NULL, -phi, &centre, SDL_FLIP_NONE);
    

}