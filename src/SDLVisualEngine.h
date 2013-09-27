/*
 * SDLVisualEngine.h
 *
 *  Created on: 10/11/2012
 *      Author: Lucas
 */

#ifndef SDLVISUALENGINE_H_
#define SDLVISUALENGINE_H_

#include <SDL/SDL.h>
// SDL_gfx
#include "SDL/SDL_rotozoom.h"		// SDL_gfx Rotozoom
#include "SDL/SDL_gfxPrimitives.h"	// SDL_gfx Primitives
#include "SDL/SDL_framerate.h"		// SDL_gfx Framerate Manager

#include "VisualEngine.h"

class SDLVisualEngine : public VisualEngine
{
private:
	SDL_Surface *screen;
	FPSmanager fpsm;
	bool _engineFoiInicializada;
	bool inicializar();
	void renderizarSurface(SDL_Surface *surface, SDL_Rect *rect);
	void desalocarSurface(SDL_Surface *surface);
	// Eventos
	void* quitOuvinte;
	QuitHandler quitHandler;
	void* keyDownOuvinte;
	KeyDownHandler keyDownHandler;
	void* keyUpOuvinte;
	KeyUpHandler keyUpHandler;
	void* mouseButtonDownOuvinte;
	MouseButtonDownHandler mouseButtonDownHandler;
public:
	SDLVisualEngine();
	virtual ~SDLVisualEngine();
	bool engineFoiInicializada();
	void setQuitEvent(void* ouvinte, QuitHandler handler);
	void setKeyDownEvent(void* ouvinte, KeyDownHandler handler);
	void setKeyUpEvent(void* ouvinte, KeyUpHandler handler);
	void setMouseButtonDownEvent(void* ouvinte, MouseButtonDownHandler handler);
	void ouvirEvento();
	bool criarScreen(int width, int height, int bpp);
	bool criarScreen(Tela *tela, int bpp);
	void setTituloJanela(const char *titulo);
	void inicializarFramerate();
	void setFramePerSecond(int fps);
	void framerateDelay();
	void limparScreen();
	void desenharImagem(Imagem *imagem, int x, int y);
	void desenharImagem(Imagem *imagem, Ponto *pontoCentral);
	void rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao);
	void rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao, double zoom);
	void atualizarScreen();
	void delay(int milessegundos);
	void desenharCirculo(int x, int y, int raio, int red, int green, int blue, int alpha);
	void desenharCirculo(Ponto *centroCirculo, int raio, RGBA *rgba);
	void desenharCircunferencia(int x, int y, int raio, int red, int green, int blue, int alpha);
	void desenharCircunferencia(Ponto *centroCirculo, int raio, RGBA *rgba);
	void escreverTexto(int x, int y, const char *texto, Uint32 cor);
};

#endif /* SDLVISUALENGINE_H_ */
