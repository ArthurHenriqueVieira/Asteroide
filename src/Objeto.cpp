/*
 * Objeto.cpp
 *
 *  Created on: 16/11/2012
 *      Author: Lucas
 */

#include "Objeto.h"

Objeto::Objeto() {
	pontoCentral = NULL;
	raio = 0;
	trajetoria = 0;
	velocidade = 0;
}

Objeto::~Objeto() {
	delete pontoCentral;
}

Ponto* Objeto::getPontoCentral() {
	return pontoCentral;
}

int Objeto::getRaio() {
	return raio;
}

float Objeto::getTrajetoria() {
	return trajetoria;
}

void Objeto::setTrajetoria(float t) {
	trajetoria = t;
}

float Objeto::getVelocidade() {
	return velocidade;
}

void Objeto::setVelocidade(float v) {
	velocidade = v;
}
