/*
 * SDLVisualEngine.cpp
 *
 *  Created on: 10/11/2012
 *      Author: Lucas
 */

#include "SDLVisualEngine.h"

SDLVisualEngine::SDLVisualEngine() {
	screen = NULL;

	quitOuvinte = NULL;
	quitHandler = NULL;
	keyDownHandler = NULL;
	keyDownOuvinte = NULL;
	keyUpHandler = NULL;
	keyUpOuvinte = NULL;
	mouseButtonDownHandler = NULL;
	mouseButtonDownOuvinte = NULL;

	_engineFoiInicializada = inicializar();
}

SDLVisualEngine::~SDLVisualEngine() {
	desalocarSurface(screen);

	SDL_Quit();
}

bool SDLVisualEngine::inicializar() {
	if(SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Falha ao inicializar o SDL: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void SDLVisualEngine::renderizarSurface(SDL_Surface *surface, SDL_Rect *rect) {
	SDL_BlitSurface(surface, NULL, screen, rect);
}

void SDLVisualEngine::desalocarSurface(SDL_Surface *surface) {
	SDL_FreeSurface(surface);
}

bool SDLVisualEngine::engineFoiInicializada() {
	return _engineFoiInicializada;
}

void SDLVisualEngine::ouvirEvento() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				if (quitHandler != NULL)
					quitHandler(quitOuvinte);
				break;

			case SDL_KEYDOWN:
				if (keyDownHandler != NULL)
					keyDownHandler(keyDownOuvinte, event.key.keysym.sym);
				break;

			case SDL_KEYUP:
				if (keyUpHandler != NULL)
					keyUpHandler(keyUpOuvinte, event.key.keysym.sym);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (mouseButtonDownHandler != NULL)
					mouseButtonDownHandler(mouseButtonDownOuvinte, event.button.button, event.button.x, event.button.y);
				break;
		}
	}
}

bool SDLVisualEngine::criarScreen(int width, int height, int bpp) {
	bool retorno = false;

	if (_engineFoiInicializada)
	{
		if (screen != NULL)
			desalocarSurface(screen);

		screen = SDL_SetVideoMode(width, height, bpp, SDL_HWSURFACE|SDL_DOUBLEBUF);
		if(screen == NULL) {
			fprintf(stderr, "Não foi possivel inicializar a tela: %s\n", SDL_GetError());

			retorno = false;
		}
		else
		{
			inicializarFramerate();
			retorno = true;
		}
	}
	else
		fprintf(stderr, "Impossivel criar uma tela sem antes inicializar a engine.");

	return retorno;
}

bool SDLVisualEngine::criarScreen(Tela *tela, int bpp) {
	return criarScreen(tela->Largura, tela->Altura, bpp);
}

void SDLVisualEngine::setTituloJanela(const char *titulo) {
	 SDL_WM_SetCaption(titulo, NULL); // segundo parametro é o icone da tela
}

void SDLVisualEngine::inicializarFramerate() {
	SDL_initFramerate(&fpsm);
}

void SDLVisualEngine::setFramePerSecond(int fps) {
	SDL_setFramerate(&fpsm, fps);
}

void SDLVisualEngine::framerateDelay() {
	SDL_framerateDelay(&fpsm);
}

void SDLVisualEngine::limparScreen() {
	SDL_FillRect(screen, NULL, 0);
}

void SDLVisualEngine::desenharImagem(Imagem *imagem, int x, int y) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	renderizarSurface(imagem->getSurface(), &rect);
}

void SDLVisualEngine::desenharImagem(Imagem *imagem, Ponto *pontoCentral) {
	SDL_Rect rect;
	rect.x = (int)pontoCentral->x - (int)(imagem->getSurface()->w / 2);
	rect.y = (int)pontoCentral->y - (int)(imagem->getSurface()->h / 2);
	renderizarSurface(imagem->getSurface(), &rect);
}

void SDLVisualEngine::rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao) {
	SDL_Surface* imagemRotacionada = rotozoomSurface(imagem->getSurface(), anguloRotacao, 1, SMOOTHING_ON);
	SDL_Rect rect;
	rect.x = (int)pontoCentral->x - (int)(imagemRotacionada->w / 2);
	rect.y = (int)pontoCentral->y - (int)(imagemRotacionada->h / 2);
	renderizarSurface(imagemRotacionada, &rect);

	desalocarSurface(imagemRotacionada);
}

void SDLVisualEngine::rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao, double zoom) {
	SDL_Surface* imagemRotacionada = rotozoomSurface(imagem->getSurface(), anguloRotacao, zoom, SMOOTHING_ON);
	SDL_Rect rect;
	rect.x = (int)pontoCentral->x - (int)(imagemRotacionada->w / 2);
	rect.y = (int)pontoCentral->y - (int)(imagemRotacionada->h / 2);
	renderizarSurface(imagemRotacionada, &rect);

	desalocarSurface(imagemRotacionada);
}

void SDLVisualEngine::atualizarScreen() {
	SDL_Flip(screen);
}

void SDLVisualEngine::delay(int milessegundos) {
	SDL_Delay(milessegundos);
}

void SDLVisualEngine::desenharCirculo(int x, int y, int raio, int red, int green, int blue, int alpha) {
	filledCircleRGBA(screen, x, y, raio, red, green, blue, alpha);
}

void SDLVisualEngine::desenharCirculo(Ponto *centroCirculo, int raio, RGBA *rgba) {
	desenharCirculo(centroCirculo->x, centroCirculo->y, raio, rgba->red, rgba->green, rgba->blue, rgba->alpha);
}

void SDLVisualEngine::desenharCircunferencia(int x, int y, int raio, int red, int green, int blue, int alpha) {
	circleRGBA(screen, x, y, raio, red, green, blue, alpha);
}

void SDLVisualEngine::desenharCircunferencia(Ponto *centroCirculo, int raio, RGBA *rgba) {
	desenharCircunferencia(centroCirculo->x, centroCirculo->y, raio, rgba->red, rgba->green, rgba->blue, rgba->alpha);
}

void SDLVisualEngine::setQuitEvent(void* ouvinte, QuitHandler handler) {
	quitOuvinte = ouvinte;
	quitHandler = handler;
}

void SDLVisualEngine::setKeyDownEvent(void* ouvinte, KeyDownHandler handler) {
	keyDownOuvinte = ouvinte;
	keyDownHandler = handler;
}

void SDLVisualEngine::setKeyUpEvent(void* ouvinte, KeyUpHandler handler) {
	keyUpOuvinte = ouvinte;
	keyUpHandler = handler;
}

void SDLVisualEngine::setMouseButtonDownEvent(void* ouvinte, MouseButtonDownHandler handler) {
	mouseButtonDownOuvinte = ouvinte;
	mouseButtonDownHandler = handler;
}

void SDLVisualEngine::escreverTexto(int x, int y, const char *texto, Uint32 cor) {
	stringColor(screen, x, y, texto, cor);
}
