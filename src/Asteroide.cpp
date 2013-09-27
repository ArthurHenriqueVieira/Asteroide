/*
 * Asteroide.cpp
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#include "Asteroide.h"

Asteroide::Asteroide(float x, float y, int raio) {
	this->pontoCentral = new Ponto;
	this->pontoCentral->x = x;
	this->pontoCentral->y = y;

	this->trajetoria = rand() % 360;  // gera trajetoria aleatoria
	this->velocidade = VELOCIDADE_ASTEROID;
	this->raio = raio;
	this->level = 1;

	imagem = Imagem::CriarImagemBMP("Asteroid_1_Branco.bmp");
}

Asteroide::Asteroide(float x, float y, int raio, int level) {
	this->pontoCentral = new Ponto;
	this->pontoCentral->x = x;
	this->pontoCentral->y = y;

	this->trajetoria = rand() % 360;  // gera trajetoria aleatoria
	this->velocidade = VELOCIDADE_ASTEROID * level;
	this->raio = raio;
	this->level = level;

	imagem = Imagem::CriarImagemBMP("Asteroid_2_Branco.bmp");
}

Asteroide::~Asteroide() {
	delete imagem;
}

int Asteroide::getLevel() {
	return level;
}

Imagem* Asteroide::getImagem() {
	return imagem;
}

