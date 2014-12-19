#include "biblio.h"


Professionnel::Professionnel() : codeps("N/A"), titre("N/A"){}

Professionnel::Professionnel(int nas, string nom, string nais, string cps, string t) :Citoyen(nas, nom, nais), codeps(cps), titre(t){}

Professionnel::~Professionnel()
{
	for (pair<int, Citoyen*> paire : mapPatients)
	{
		delete paire.second;
	}
	mapNbrIntervention.clear();
	mapPatients.clear();
	//Objet déjà deleted avec la mapPatients
	listePatients.clear();
}

string Professionnel::getCodePS()
{
	return codeps;
}

//Remplace la valeur de la clée dans la map mapPatients<int,Citoyen*>
void Professionnel::RajoutPatient(int key, Citoyen* value)
{
	//mapPatients.insert(std::pair<int, Citoyen*>(key, value));
	mapPatients[key] = value;
}

/*
Avec la clée, utilise mapPatients pour retourner un iterator pointant à la valeur.
null si non existante.
*/
map<int, Citoyen*>::iterator Professionnel::TrouverPatient(int key)
{
	return mapPatients.find(key);
}

//Avec la clée, utilise mapPatients pour connaitre si la clée existe déjà dans la map mapPatients
bool Professionnel::PatientExiste(int key)
{
	//C'est une map, donc c'est juste 0 ou 1 comme retour possible.
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

//Retourne la liste de patient (Citoyen*) du Professionnel
list<Citoyen*> Professionnel::getListePatients()
{
	//Si la liste n'est déjà pas populer, la popule avec mapPatients.
	if (listePatients.size() == 0)
	{
		for (pair<int, Citoyen*> paire : mapPatients)
		{
			//"second" étant la valeur.
			//"first" serait la clée
			listePatients.push_back(paire.second);
		}
	}
	return listePatients;
}

/*
Pour compter le nombre d'intervention que le Professionnel a fait a un patient.
Avec une clée (le NAS du patient), augmente un compteur dans mapNbrIntervention.
*/
void Professionnel::AugmenteIntervention(int key)
{
	//La clée n'existe pas
	if (mapNbrIntervention.count(key) == 0)
	{
		//C'est donc sa première intervention
		mapNbrIntervention[key] = 1;
		return;
	}
	//Retrouve le dernier compte et l'augmente
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