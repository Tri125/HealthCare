#include "biblio.h"

Citoyen::Citoyen() : nas(0), nom("N/A"), naissance("N/A"){}

Citoyen::Citoyen(int nas, string nom, string nais) : nas(nas), nom(nom), naissance(nais){}

int Citoyen::getNAS()
{
	return nas;
}

string Citoyen::getNom()
{
	return nom;
}
string Citoyen::getNaissance()
{
	return naissance;
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
	cout << "--------------------\n";
	cout << "Nom:\t\t" << nom << endl;
	cout << "Né(e) le:\t" << naissance << endl;
	cout << "--------------------\n";
	cout << "Historique:\n\t" << problemes.size() << " problèmes\n\t" << rendezvous.size() << " ressources utilisées\n\n";
	cout << "--------------------\n";
}


void Citoyen::AfficherMaladie()
{
	for (Probleme* prob : problemes)
	{
		if (Maladie* mal = dynamic_cast<Maladie*>(prob))
		{
			prob->Afficher();
		}
	}
}