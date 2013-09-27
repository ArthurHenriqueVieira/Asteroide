/*
 * Imagem.h
 *
 *  Created on: 10/11/2012
 *      Author: Lucas
 */

#ifndef IMAGEM_H_
#define IMAGEM_H_

#include "Objeto.h"
#include <SDL/SDL.h>

//Classe que define uma imagem
class Imagem
{
private:
	SDL_Surface	*surfaceImagem;
	Imagem();
public:
	//Cria uma imagem apartir de uma arquivo fisico
	static Imagem* CriarImagemBMP(const char *arquivo);
	//Retorna uma Surface
	SDL_Surface* getSurface();
	virtual ~Imagem();
};

#endif /* IMAGEM_H_ */
