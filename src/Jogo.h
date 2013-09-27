/*
 * Jogo.h
 *
 *  Created on: 23/11/2012
 *      Author: Lucas
 */

#ifndef JOGO_H_
#define JOGO_H_

#include <sstream>
#include "Objeto.h"
#include "Lista.h"
#include "Asteroide.h"
#include "GeometriaAnalitica.h"
#include "VisualEngine.h"
#include "Ponto.h"
#include "Nave.h"
#include "Tiro.h"
#include "Jogador.h"
#include "Imagem.h"
#include "JogoSetup.h"

//Delegate do evento OnSairJogo
typedef void (*SairJogoHandler)(void* ouvinte);

class Jogo {
private:
	VisualEngine* engine;
	JogoSetup* setup;

	Tela tela;
	bool rodando;
	Lista* listaAsteroide;
	Lista* listaTiro;
	Nave* nave;
	Jogador jogador;
	Imagem* marcadorVida;
	Imagem* gameOver;
	int fps;

	//Evento Sair do jogo
	SairJogoHandler sairJogoHandler;
	void* sairJogoOuvinte;

	void carregandoSetup();
	void moverObjeto(Objeto *obj);
	void desenharAsteroide(Asteroide *asteroide);
	void desenharNave(Nave *nave);
	void desenharTiro(Tiro *tiro);
	void desenharContadorVidas();
	void desenharGameOver();
	void desenharPontuacao();
	Tiro* criarTiro(Nave *n);
	void colisaoAsteroide(Asteroide* asteroide);
	void colisaoNaveAsteroide(Asteroide* asteroide);
	void colisaoTiroAsteroide(Asteroide* asteroide, Tiro* tiro);
	void validarEspacoCiclico(Objeto *a);
	bool saiuLimite(Objeto *a);
	bool isGameOver();
	Nave* criarNave();
	void validarColisao();
	bool finalizouLevel();
	void reiniciarLevel();
	void moverDesenharAsteroides();
	void moverDesenharNave();
	void moverDesenharTiros();
public:
	Jogo(VisualEngine* engine, JogoSetup* setup);
	virtual ~Jogo();
	void rodar();
	void sair();
	void setSairJogoEvent(void* ouvinte, SairJogoHandler handler);

	friend void Jogo_onSair(void* ouvinte);
	friend void Jogo_onKeyDown(void* ouvinte, int key);
	friend void Jogo_onKeyUp(void* ouvinte, int key);
	friend void Jogo_onNaveAtirar(void* ouvinte, Nave *n);
};

void Jogo_onSair(void* ouvinte);
void Jogo_onKeyDown(void* ouvinte, int key);
void Jogo_onKeyUp(void* ouvinte, int key);
void Jogo_onNaveAtirar(void* ouvinte, Nave *n);

#endif /* JOGO_H_ */
