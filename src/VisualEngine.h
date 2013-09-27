/*
 * VisualEngine.h
 *
 *  Created on: 08/11/2012
 *      Author: Lucas
 */

#ifndef VISUALENGINE_H_
#define VISUALENGINE_H_

#include "Tela.h"
#include "Imagem.h"
#include "Ponto.h"
#include "RGBA.h"

//Delegate do evento OnQuit
typedef void (*QuitHandler)(void* ouvinte);
//Delegate do evento OnKeyDown
typedef void (*KeyDownHandler)(void* ouvinte, int tecla);
//Delegate do evento OnKeyUp
typedef void (*KeyUpHandler)(void* ouvinte, int tecla);
//Delegate OnMouseButtonDown
typedef void (*MouseButtonDownHandler)(void* ouvinte, int botao, int x, int y);

//Classe abstrata que define a interface de uso para uma visual engine
class VisualEngine
{
public:
	virtual ~VisualEngine() { }
	virtual bool engineFoiInicializada() = 0;
	virtual void setQuitEvent(void* ouvinte, QuitHandler handler) = 0;
	virtual void setKeyDownEvent(void* ouvinte, KeyDownHandler handler) = 0;
	virtual void setKeyUpEvent(void* ouvinte, KeyUpHandler handler) = 0;
	virtual void setMouseButtonDownEvent(void* ouvinte, MouseButtonDownHandler handler) = 0;
	virtual void ouvirEvento() = 0;
	virtual bool criarScreen(int width, int height, int bpp) = 0;
	virtual bool criarScreen(Tela *tela, int bpp) = 0;
	virtual void setTituloJanela(const char *titulo) = 0;
	virtual void inicializarFramerate() = 0;
	virtual void setFramePerSecond(int fps) = 0;
	virtual void framerateDelay() = 0;
	virtual void limparScreen() = 0;
	virtual void desenharImagem(Imagem *imagem, int x, int y) = 0;
	virtual void desenharImagem(Imagem *imagem, Ponto *pontoCentral) = 0;
	virtual void rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao) = 0;
	virtual void rotacionarImagem(Imagem *imagem, Ponto *pontoCentral, double anguloRotacao, double zoom) = 0;
	virtual void atualizarScreen() = 0;
	virtual void delay(int milessegundos) = 0;
	virtual void desenharCirculo(int x, int y, int raio, int red, int green, int blue, int alpha) = 0;
	virtual void desenharCirculo(Ponto *centroCirculo, int raio, RGBA *rgba) = 0;
	virtual void desenharCircunferencia(int x, int y, int raio, int red, int green, int blue, int alpha) = 0;
	virtual void desenharCircunferencia(Ponto *centroCirculo, int raio, RGBA *rgba) = 0;
	virtual void escreverTexto(int x, int y, const char *texto, Uint32 cor) = 0;
};


#endif /* VISUALENGINE_H_ */
