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