#include"Basetexture.h"
Ltexture::Ltexture() {
	mTexture = NULL;
	mrect = { 0,0,0,0 };
}
Ltexture::~Ltexture() {
	free();
}
bool Ltexture::loadfromfile(string file, SDL_Renderer* screen) {
	
	free();

	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedsurface = IMG_Load(file.c_str());
	if (loadedsurface == NULL) {
		cout << "error loadsurface: " << IMG_GetError() << endl;
	}
	else {
		SDL_SetColorKey(loadedsurface, SDL_TRUE, SDL_MapRGB(loadedsurface->format, 125, 125, 125));
		newtexture = SDL_CreateTextureFromSurface(screen, loadedsurface);

		if (newtexture == NULL) {
			cout << "error loadtexture: " << SDL_GetError() << endl;
		}
		else {
			mrect.h = loadedsurface->h;
			mrect.w = loadedsurface->w;
		}
	}
	SDL_FreeSurface(loadedsurface);
	mTexture = newtexture;
	return mTexture != NULL;
}


bool Ltexture::loadfromtext(SDL_Renderer* screen,string text, SDL_Color color,string path_font) {
	SDL_Texture* newtexture = NULL;
	TTF_Font* gfont = TTF_OpenFont(path_font.c_str(), 50);
	if (gfont == NULL) cout << "error font";
	SDL_Surface* surfacetext = TTF_RenderText_Solid(gfont, text.c_str(), color);
	if (surfacetext == NULL) {
		cout << "error load surfacetext";
	}
	else {
		newtexture = SDL_CreateTextureFromSurface(screen, surfacetext);
		if (newtexture == NULL) {
			cout << "error texture";
		}
		else {
			mrect.w = surfacetext->w;
			mrect.h = surfacetext->h;
		}
	}
	SDL_FreeSurface(surfacetext);
	TTF_CloseFont(gfont); 
	mTexture = newtexture;
	return mTexture != NULL;
}
void Ltexture::render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect offset = { mrect.x,mrect.y,mrect.w,mrect.h };
	if (clip != NULL) {
		offset.w = clip->w;
		offset.h = clip->h;
	}
	SDL_RenderCopy(des, mTexture, clip, &offset);
}
void Ltexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mrect.w = 0;
		mrect.h = 0;
	}
}
void Ltexture::render360(SDL_Renderer* des, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	set_rect( x, y);
	SDL_RenderCopyEx(des, mTexture, clip, &mrect, angle, center, flip);
}