/*
 * Tiro.h
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#ifndef TIRO_H_
#define TIRO_H_

#include "Objeto.h"
#include "RGBA.h"

//Classe que define um tiro
class Tiro : public Objeto {
private:
	RGBA *cor;
public:
	Tiro(int x, int y, float trajetoria, RGBA* cor);
	virtual ~Tiro();
	//Retorna a cor do tiro
	RGBA* getCor();
};

#endif /* TIRO_H_ */
