/*
 * Tiro.cpp
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#include "Tiro.h"

Tiro::Tiro(int x, int y, float trajetoria, RGBA* cor) {
	pontoCentral = new Ponto;
	pontoCentral->x = x;
	pontoCentral->y = y;

	this->trajetoria = trajetoria;

	raio = 1;

	velocidade = 1;

	this->cor = cor;

}

Tiro::~Tiro() {
}

RGBA* Tiro::getCor() {
	return cor;
}

