/*
 * Jogador.cpp
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#include "Jogador.h"

Jogador::Jogador() {
	pontos = 0;
	vidas = 3;
}

Jogador::~Jogador() {
	// TODO Auto-generated destructor stub
}

int Jogador::getPontos() {
	return pontos;
}

void Jogador::adicionarPontos(int quantidade) {
	pontos += quantidade;
}

void Jogador::zerarPontos() {
	pontos = 0;
}

int Jogador::getVidas() {
	return vidas;
}

void Jogador::setVidas(int value) {
	vidas = value;
}

