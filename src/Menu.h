/*
 * Menu.h
 *
 *  Created on: 02/12/2012
 *      Author: Lucas
 */

#ifndef MENU_H_
#define MENU_H_

#include "VisualEngine.h"
#include "Imagem.h"

#define MENU_LARGURA 427
#define MENU_ALTURA 537

//Estrutura que define um botão
typedef struct {
	int x;
	int y;
	int largura;
	int altura;
} Botao;

//Delegate para o evento Abrir jogo
typedef void (*AbriJogoHandler)(void* ouvinte);

class Menu {
private:
	VisualEngine* engine;
	Imagem* opcoes;
	Imagem* instrucoes;
	Imagem* controles;
	Imagem* creditos;
	Botao* jogarBotao;
	Botao* instrucoesBotao;
	Botao* controlesBotao;
	Botao* creditosBotao;
	Botao* sairBotao;
	Botao* voltarBotao;
	int telaAtual;
	bool rodando;

	void* abriJogoOuvinte;
	AbriJogoHandler abriJogoHandler;

	bool botaoFoiClicado(Botao* botao, int x, int y);

public:
	Menu(VisualEngine* engine);
	virtual ~Menu();
	Imagem* getTelaAtual();
	void rodar();
	void sair();
	void clicar(int x, int y);
	void mudarTela(int tela);
	void setAbriJogoEvent(void* ouvinte, AbriJogoHandler handler);

	friend void Menu_OnSair(void* ouvinte);
	friend void Menu_OnMouseButtonDown(void* ouvinte, int botao, int x, int y);
};

void Menu_OnSair(void* ouvinte);
void Menu_OnMouseButtonDown(void* ouvinte, int botao, int x, int y);

#endif /* MENU_H_ */
