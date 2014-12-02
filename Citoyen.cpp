#include "biblio.h"

Citoyen::Citoyen() : nas(0), nom("N/A"), naissance("N/A"){}

Citoyen::Citoyen(int nas, string nom, string nais) :nas(nas), nom(nom), naissance(nais){}

int Citoyen::getNAS()
{
	return nas;
}

void Citoyen::RajoutUtilisation(list<RendezVous*> liste)
{
	for (RendezVous* p : liste)
	{
		this->rendezvous.push_back(p);
	}
}

void Citoyen::RajoutProbleme(list<Probleme*> liste)
{
	for (Probleme* p : liste)
	{
		this->problemes.push_back(p);
	}
}

void Citoyen::Afficher()
{

}