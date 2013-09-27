/*
 * GeometriaAnalitica.h
 *
 *  Created on: 16/11/2012
 *      Author: Lucas
 */

#ifndef GEOMETRIAANALITICA_H_
#define GEOMETRIAANALITICA_H_

#include <math.h>
#include "Ponto.h"

#define PI 3.14159

//Classe que reune as calculos matematicos
class GeometriaAnalitica {
private:
	//Converte graus to radianos
	static float convertGrausToRadiano(float graus);
public:
	//Retorna a distancia entre dois pontos
	static float distanciaEntrePontos(Ponto *a, Ponto *b);
	//Move um ponto de lugar no plano
	static void moverPonto(Ponto* pontoInicial, float angulo, float distancia);
};

#endif /* GEOMETRIAANALITICA_H_ */
