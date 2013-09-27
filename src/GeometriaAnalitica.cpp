/*
 * GeometriaAnalitica.cpp
 *
 *  Created on: 16/11/2012
 *      Author: Lucas
 */

#include "GeometriaAnalitica.h"

float GeometriaAnalitica::convertGrausToRadiano(float graus) {
	return (graus * PI / 180);
}

float GeometriaAnalitica::distanciaEntrePontos(Ponto *a, Ponto *b) {
	return sqrt((pow((a->x - b->x), 2) + pow((a->y - b->y), 2)));
}

void GeometriaAnalitica::moverPonto(Ponto* ponto, float angulo, float distancia) {
	float radiano = convertGrausToRadiano(angulo);

	ponto->x = (sin(radiano) * distancia) + ponto->x;
	ponto->y = (cos(radiano) * distancia) + ponto->y;

}
