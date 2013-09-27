/*
 * Nave.h
 *
 *  Created on: 01/12/2012
 *      Author: Lucas
 */

#ifndef NAVE_H_
#define NAVE_H_

#include "Objeto.h"
#include "Imagem.h"
#include "RGBA.h"

#define ANGULO_VIRADA 0.5
#define VELOCIDADE_MAXIMA 0.3
#define ACELERACAO 0.001
#define DESACELERACAO 0.0001
#define RECARGA_TIRO 100

//Classe que define a nave do jogador
class Nave : public Objeto {
private:
	Imagem* normalImagem;
	Imagem* acelerandoImagem;
	RGBA* corTiro;
	bool acelerando;
	bool virandoDireita;
	bool virandoEsquerda;
	bool atirando;
	int carregandoTiro;
	//Delegate para o evento Disparar Tiros
	typedef void (*DispararTiroHandler)(void* ouvinte, Nave *nave);
	//Evento
	void* ouvinteDispararTiro;
	DispararTiroHandler dispararTiroHandler;

	void dispararTiro();
public:
	//Nave();
	Nave(int x, int y);
	virtual ~Nave();
	//Retorna a imagem da nave
	Imagem* getImagem();
	//Retorna a cor dos tiros disparados pela nave
	RGBA* getCorTiro();
	//Define o ouvinte para o evento Disparar Tiro
	void setDispararTiroEvent(void* ouvinte, DispararTiroHandler handler);
	//Define a ação de acelerar
	void acelerar(bool value);
	//Define a ação de virar para direita
	void virarDireita(bool value);
	//Define a ação de virar para esquerda
	void virarEsquerda(bool value);
	//Define a ação de atirar
	void atirar(bool value);
	//Executa a ação da nave naquele turno
	void acao();
};



#endif /* NAVE_H_ */
