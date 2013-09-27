/*
 * Jogador.h
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#ifndef JOGADOR_H_
#define JOGADOR_H_

//Classe que define um jogador
class Jogador {
private:
	int pontos;
	int vidas;
public:
	Jogador();
	virtual ~Jogador();
	//Retorna a quantidade de pontos atual do jogador
	int getPontos();
	//Adiciona pontos para o jogador
	void adicionarPontos(int quantidade);
	//zera a pontução do jogodar
	void zerarPontos();
	//Retorna a quantidade de vida do usuario
	int getVidas();
	//Define as vidas do jogador
	void setVidas(int value);
};

#endif /* JOGADOR_H_ */
