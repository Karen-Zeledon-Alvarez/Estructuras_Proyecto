#pragma once
class ColaPiezas
{

private:

	char elementos[100];
	int frente;
	int final;
	int cantidad;

public:

	ColaPiezas();
	~ColaPiezas();

	bool estaVacia();

	bool estaLlena();

	void encolar(char tipo);

	char desencolar();

	char frenteCola();

};

