#pragma once
class PiloHold
{

private:

	char elementos[7];
	int tope;

public:

	PiloHold();

	bool Vacia();

	bool Llena();

	void apilar(char tipo);

	char desapilar();

	char verTope();
};

