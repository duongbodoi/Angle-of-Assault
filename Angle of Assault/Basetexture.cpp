#include"Basetexture.h"
Ltexture::Ltexture() {
	mTexture = NULL;
	mrect = { 0,0,0,0 };
}
Ltexture::~Ltexture() {
	free();
}
bool Ltexture::loadfromfile(string file, SDL_Renderer* screen) {
	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedsurface = IMG_Load(file.c_str());
	if (loadedsurface == NULL) cout << "error loadsurface";
	else {
		newtexture = SDL_CreateTextureFromSurface(screen, loadedsurface);

		if (newtexture == NULL) cout << "error loadtexture";
		else {
			mrect.h = loadedsurface->h;
			mrect.w = loadedsurface->w;
		}
	}
	SDL_FreeSurface(loadedsurface);
	mTexture = newtexture;
	return mTexture != NULL;
}
void Ltexture::render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect offset = { mrect.x,mrect.y,mrect.w,mrect.h };
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