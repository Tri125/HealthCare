#include "biblio.h"

Citoyen::Citoyen() : nas(0), nom("N/A"), naissance("N/A"){}

Citoyen::Citoyen(int nas, string nom, string nais) : nas(nas), nom(nom), naissance(nais){}

Citoyen::~Citoyen()
{
	for (Probleme* p : problemes)
	{
		delete p;
	}
	problemes.clear();

	for (RendezVous* rdv : rendezvous)
	{
		delete rdv;
	}
	rendezvous.clear();
}

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

//Rajoute les pointeurs sur un objet RendezVous d'une list à la list rendezvous.
void Citoyen::RajoutUtilisation(list<RendezVous*> liste)
{
	for (RendezVous* p : liste)
	{
		this->rendezvous.push_back(p);
	}
}

//Rajoute les pointeurs sur un objet Probleme d'une list à la list problemes.
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
		/*
		dynamic_cast puisque nous voulons afficher seulement les pointeurs objets de la classe enfant "Maladie"
		d'une liste de pointeur de la classe mère "Probleme".
		Peut ensuite tester si objet est valide, null si invalide.
		*/
		if (Maladie* mal = dynamic_cast<Maladie*>(prob))
		{
			prob->Afficher();
			cout << endl;
		}
	}
}

void Citoyen::AfficherBlessure()
{
	for (Probleme* prob : problemes)
	{
		/*
		dynamic_cast puisque nous voulons afficher seulement les pointeurs objets de la classe enfant "Blessure"
		d'une liste de pointeur de la classe mère "Probleme".
		Peut ensuite tester si objet est valide, null si invalide.
		*/
		if (Blessure* bles = dynamic_cast<Blessure*>(prob))
		{
			bles->Afficher();
			cout << endl;
		}
	}
}

void Citoyen::AfficherRendezVous()
{
	for (RendezVous* rdv : rendezvous)
	{
		/*
		dynamic_cast puisque nous voulons afficher seulement les pointeurs objets de la classe mère "RendezVous"
		d'une liste de pointeur qui contient des objets RendezVous et Hospitalisation. Nous voulons exclure les objets
		Hospitalisation et étant donné que RendezVous est la classe de base, le upcast va toujours réussir de toute manière.
		Downcast, teste la négativité. De cette manière on les excluts.
		*/
		if (!dynamic_cast<Hospitalisation*>(rdv))
		{
			rdv->Afficher();
			cout << endl;
		}
	}
}

void Citoyen::AfficherHospitalisation()
{
	for (RendezVous* rdv : rendezvous)
	{
		/*
		dynamic_cast puisque nous voulons afficher seulement les pointeurs objets de la classe enfant "Hospitalisation"
		d'une liste de pointeur de la classe mère RendezVous.
		Peut ensuite tester si objet est valide, null si invalide.
		*/
		if (Hospitalisation* hosp = dynamic_cast<Hospitalisation*>(rdv))
		{
			hosp->Afficher();
			cout << endl;
		}
	}
}

void Citoyen::setListRdv(list<RendezVous*> li)
{
	rendezvous = li;
}

list<RendezVous*> Citoyen::getListRdv()
{
	return rendezvous;
}