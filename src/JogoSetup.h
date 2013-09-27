/*
 * JogoSetup.h
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#ifndef JOGOSETUP_H_
#define JOGOSETUP_H_

#include "Tela.h"
#include "Lista.h"

//Estrutura com as configurações do jogo
typedef struct {
	Tela tela;
	int passoTemporal;
	int vidas;
	Lista *asteroides;
} JogoSetup;

#endif /* JOGOSETUP_H_ */
