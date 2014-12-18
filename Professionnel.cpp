#include "biblio.h"


Professionnel::Professionnel() : codeps("N/A"), titre("N/A"){}

Professionnel::Professionnel(int nas, string nom, string nais, string cps, string t) :Citoyen(nas, nom, nais), codeps(cps), titre(t){}

string Professionnel::getCodePS()
{
	return codeps;
}

void Professionnel::RajoutPatient(int key, Citoyen* value)
{
	//mapPatients.insert(std::pair<int, Citoyen*>(key, value));
	mapPatients[key] = value;
}

map<int, Citoyen*>::iterator Professionnel::TrouverPatient(int key)
{
	return mapPatients.find(key);
}

bool Professionnel::PatientExiste(int key)
{
	return mapPatients.count(key) > 0;
}

void Professionnel::Afficher()
{
	cout << "--------------------\n";
	cout << "Nom:\t\t" << nom << ", " << titre << endl;
	cout << "Né(e) le:\t" << naissance << endl;
	cout << "--------------------\n";
	cout << "Historique:\n\t" << mapPatients.size() << " patients \n\t" << rendezvous.size() << " interventions\n\n";
	cout << "--------------------\n";
}

list<Citoyen*> Professionnel::getListePatients()
{
	if (listePatients.size() == 0)
	{
		for (pair<int, Citoyen*> paire : mapPatients)
		{
			listePatients.push_back(paire.second);
		}
	}
	return listePatients;
}

void Professionnel::AugmenteIntervention(int key)
{
	//La clée n'existe pas
	if (mapNbrIntervention.count(key) == 0)
	{
		mapNbrIntervention[key] = 1;
		return;
	}
	int pre = mapNbrIntervention[key];
	mapNbrIntervention[key] = ++pre;
		
}

void Professionnel::AfficherPatients()
{
	for (Citoyen* c : getListePatients())
	{
		cout << c->getNom() << "\t";
		if (c->getNom().length() < 24)
		{
			cout << "\t";
		}
		cout << c->getNAS() << "\t" << c->getNaissance() << "\t" << mapNbrIntervention[c->getNAS()] << endl;
	}
}

void Professionnel::setListePatients(list<Citoyen*> liste)
{
	listePatients = liste;
}

void Professionnel::AfficherInterventions()
{
	for (RendezVous* rdv : rendezvous)
	{
		string nom = mapPatients[rdv->getNas()]->getNom();
		cout << nom << "\t";
		if (nom.length() < 24)
		{
			cout << "\t";
		}
		cout << rdv->getNas() << "\t" << rdv->getDate() << "\t" << rdv->getEtablissement() << endl;
	}
}