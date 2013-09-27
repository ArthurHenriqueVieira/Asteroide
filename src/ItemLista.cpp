/*
 * ItemLista.cpp
 *
 *  Created on: 03/11/2012
 *      Author: Lucas
 */

#include "ItemLista.h"

ItemLista::ItemLista() {
	valor = NULL;
	proximo = NULL;
}

ItemLista::ItemLista(Objeto *value) {
	valor = value;
	proximo = NULL;
}

ItemLista::ItemLista(Objeto *value, ItemLista *next) {
	valor = value;
	proximo = next;
}

ItemLista::~ItemLista() {

}

Objeto* ItemLista::getValor() {
	return valor;
}

void ItemLista::setValor(Objeto *value) {
	valor = value;
}

ItemLista* ItemLista::getProximo() {
	return proximo;
}

void ItemLista::setProximo(ItemLista *next) {
	proximo = next;
}
