/*
 * Objeto.h
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <cstdlib>
#include "Ponto.h"

using namespace std;

// Classe que define um objeto generico que interage com a tela.
class Objeto
{
protected:
	Ponto *pontoCentral;
	int raio;
	float trajetoria;
	float velocidade;

public:
	Objeto();
	virtual ~Objeto();
	//Retorna o ponto central do objeto
	Ponto* getPontoCentral();
	//Define o ponto central do objeto
	void setPontoCentral(Ponto *p);
	//Retornar o raio do objeto
	int getRaio();
	//Define o raio do objeto
	void setRaio(int r);
	//Retornar a trajetoria do objeto
	float getTrajetoria();
	//Define a trajetoria do objeto
	void setTrajetoria(float t);
	//Retorna a velocidade do objeto
	float getVelocidade();
	//Define a velocidade do objeto
	void setVelocidade(float v);
};

#endif /* OBJECT_H_ */
