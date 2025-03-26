#include"object_bar.h"
#include"Basetexture.h"

void draw_powerbar(SDL_Renderer* screen, int v0, int x, int y, int last_v0) {
    int last_width = last_v0;
    int width = v0;
    int height = 12;
    int l_thickness = 6; 
    int l_height = height+10 ; 
    int l_width = 200+40; 

    SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND);

    
    SDL_SetRenderDrawColor(screen, 55, 70,55, 255);
    SDL_Rect l_vertical = { x - l_thickness, y, l_thickness, l_height };
    SDL_RenderFillRect(screen, &l_vertical);

    
    SDL_SetRenderDrawColor(screen, 55, 70, 55, 255);
    SDL_Rect l_horizontal = { x - l_thickness, y + l_height , l_width, l_thickness };
    SDL_RenderFillRect(screen, &l_horizontal);

    SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND);  
    SDL_SetRenderDrawColor(screen, 255, 0, 0, 120);  
    SDL_Rect lastpower = { x - 2, y + l_height - height - 2, last_width, height+5 };
    SDL_RenderFillRect(screen, &lastpower);

    
    SDL_SetRenderDrawColor(screen, 10, 10, 30, 255);
    SDL_Rect background = { x - 4, y + l_height - height - 4, v0 + 8, height + 8 };
    SDL_RenderFillRect(screen, &background);

    
    SDL_SetRenderDrawColor(screen, 0, 80, 220, 200);
    SDL_Rect glow = { x - 2, y + l_height - height - 2, width + 4, height + 4 };
    SDL_RenderFillRect(screen, &glow);

    int startColor[3] = { 0, 80, 200 };
    int endColor[3] = { 0, 220, 255 };
    int timeOffset = (SDL_GetTicks() / 15);

    for (int i = 0; i < width; i++) {
        int r = startColor[0] + (endColor[0] - startColor[0]) * i / width;
        int g = startColor[1] + (endColor[1] - startColor[1]) * i / width;
        int b = startColor[2] + (endColor[2] - startColor[2]) * i / width;
        int alpha = 220 + 35 * sin(SDL_GetTicks() * 0.03);

        if (sin((SDL_GetTicks() + i * 30) * 0.005) > 0.85) {
            r = 255;
            g = 255;
            b = 255;
            alpha = 255;
        }

        int waveOffset = (int)(2.5 * sin((SDL_GetTicks() * 0.03) + i * 0.4));
        int brightFactor = 255 - (abs(waveOffset) * 25);
        r = std::min(r + brightFactor, 255);
        g = std::min(g + brightFactor, 255);
        b = std::min(b + brightFactor, 255);

        SDL_SetRenderDrawColor(screen, r, g, b, alpha);
        SDL_Rect barSegment = { x + i, y + l_height - height + waveOffset, 1, height };
        SDL_RenderFillRect(screen, &barSegment);
    }
}


void draw_angle_control_L(SDL_Renderer* screen, int phi, int x, int y, Ltexture angle_, Ltexture arrow_) {
    if (!angle_.loadfromfile("img/angle.png", screen)) cout << "error angle";
    if (!arrow_.loadfromfile("img/arrow1.png", screen)) cout << "error arrow";
    angle_.set_rect(x, y);
    angle_.render(screen);
    
    SDL_Rect rect_angle = angle_.get_rect();
    
    SDL_Point centre = {3,7};
    arrow_.render360(screen, rect_angle.x, rect_angle.y+205, NULL, -phi, &centre, SDL_FLIP_NONE);
    

}
void draw_angle_control_R(SDL_Renderer* screen, int phi, int x, int y, Ltexture angle_, Ltexture arrow_) {
    if (!angle_.loadfromfile("img/angle2.png", screen)) cout << "error angle";
    if (!arrow_.loadfromfile("img/arrow2.png", screen)) cout << "error arrow";
    angle_.set_rect(x, y);
    angle_.render(screen);

    SDL_Rect rect_angle = angle_.get_rect();

    SDL_Point centre = {253,9};
    arrow_.render360(screen, rect_angle.x-33, rect_angle.y + 205, NULL, phi, &centre, SDL_FLIP_NONE);


}
void draw_HP(SDL_Renderer* screen, int hp, int max_hp, int x, int y) {
    const int HP_BAR_WIDTH = 50;  
    const int HP_BAR_HEIGHT = 8;  

    
    SDL_SetRenderDrawColor(screen, 50, 50, 50, 255);
    SDL_Rect hp_background = { x, y, HP_BAR_WIDTH, HP_BAR_HEIGHT };
    SDL_RenderFillRect(screen, &hp_background);

    
    float hp_ratio = (float)hp / max_hp;  
    int hp_width = (int)(HP_BAR_WIDTH * hp_ratio); 

    SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
    SDL_Rect hp_bar = { x, y, hp_width, HP_BAR_HEIGHT };
    SDL_RenderFillRect(screen, &hp_bar);
}

