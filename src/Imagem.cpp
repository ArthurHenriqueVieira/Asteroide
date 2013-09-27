/*
 * Imagem.cpp
 *
 *  Created on: 10/11/2012
 *      Author: Lucas
 */

#include "Imagem.h"

Imagem::Imagem() {
	surfaceImagem = NULL;
}

Imagem* Imagem::CriarImagemBMP(const char *arquivo) {
	Imagem* imagem = new Imagem;
	imagem->surfaceImagem = SDL_LoadBMP(arquivo);
	if (imagem->surfaceImagem == NULL)
		fprintf(stderr, "Não foi possivel carregar a imagem: %s\n", SDL_GetError());

	return imagem;
}

SDL_Surface* Imagem::getSurface() {
	return surfaceImagem;
}

Imagem::~Imagem() {
	SDL_FreeSurface(surfaceImagem);
}

