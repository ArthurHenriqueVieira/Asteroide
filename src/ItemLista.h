/*
 * ItemLista.h
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#ifndef ITEMLISTA_H_
#define ITEMLISTA_H_

#include <iostream>
#include "Objeto.h"

//Classe que define um item de uma lista
class ItemLista
{
private:
	Objeto *valor;
	ItemLista *proximo;
public:
	ItemLista();
	ItemLista(Objeto *value);
	ItemLista(Objeto *value, ItemLista *next);
	virtual ~ItemLista();
	//Retorna o valor do item;
	Objeto* getValor();
	//Define o valor do item
	void setValor(Objeto *value);
	//Retorna o proximo
	ItemLista* getProximo();
	//Define o proximo
	void setProximo(ItemLista *next);
};

#endif /* ITEMLISTA_H_ */
