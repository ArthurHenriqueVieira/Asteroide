/*
 * Asteroide.h
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#ifndef ASTEROIDE_H_
#define ASTEROIDE_H_

#include <cstdlib>
#include "Objeto.h"
#include "Ponto.h"
#include "RGBA.h"
#include "Imagem.h"

#define VELOCIDADE_ASTEROID 0.1

//Classe que define os asteroides
class Asteroide : public Objeto
{
private:
	int level;
	Imagem* imagem;
public:
	 Asteroide(float x, float y, int raio);
	 Asteroide(float x, float y, int raio, int level);
	 virtual ~Asteroide();
	 int getLevel();
	 Imagem* getImagem();
};

#endif /* ASTEROIDE_H_ */
