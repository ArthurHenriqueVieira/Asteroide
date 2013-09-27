/*
 * Nave.cpp
 *
 *  Created on: 01/12/2012
 *      Author: Lucas
 */

#include "Nave.h"

Nave::Nave(int x, int y) {
	normalImagem = Imagem::CriarImagemBMP("Nave.bmp");
	acelerandoImagem = Imagem::CriarImagemBMP("Nave_acelerando.bmp");

	corTiro = new RGBA;
	corTiro->red = 0;
	corTiro->green = 0;
	corTiro->blue = 255;
	corTiro->alpha = 255;

	pontoCentral = new Ponto;
	pontoCentral->x = x;
	pontoCentral->y = y;

	raio = 15;
	trajetoria = 0;
	velocidade = 0;
	acelerando = false;
	virandoDireita = false;
	virandoEsquerda = false;
	atirando = false;
	carregandoTiro = 0;
	ouvinteDispararTiro = NULL;
	dispararTiroHandler = NULL;
}

Nave::~Nave() {
	delete normalImagem;
	delete acelerandoImagem;
	delete corTiro;
}

Imagem* Nave::getImagem() {
	if (acelerando)
		return acelerandoImagem;
	else
		return normalImagem;
}

RGBA* Nave::getCorTiro() {
	return corTiro;
}

void Nave::acelerar(bool value) {
	acelerando = value;
}

void Nave::virarDireita(bool value) {
	virandoDireita = value;
}

void Nave::virarEsquerda(bool value) {
	virandoEsquerda = value;
}

void Nave::atirar(bool value) {
	atirando = value;
}

void Nave::dispararTiro() {
	carregandoTiro = RECARGA_TIRO;
	if (dispararTiroHandler != NULL)
		dispararTiroHandler(ouvinteDispararTiro, this);
}

void Nave::setDispararTiroEvent(void* ouvinte, DispararTiroHandler handler) {
	ouvinteDispararTiro = ouvinte;
	dispararTiroHandler = handler;
}

void Nave::acao() {
	if (virandoDireita)
		trajetoria -= ANGULO_VIRADA;

	if (virandoEsquerda)
		trajetoria += ANGULO_VIRADA;

	if (acelerando) {
		if (velocidade < VELOCIDADE_MAXIMA)
			velocidade += ACELERACAO;
	}
	else
		if (velocidade > 0)
			velocidade -= DESACELERACAO;

	if (carregandoTiro > 0)
		carregandoTiro--;

	if (atirando && carregandoTiro == 0)
		dispararTiro();
}

