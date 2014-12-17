#include "biblio.h"

Citoyen* Trouver(string id, typeVision vue, bool modePatient)
{
	const char SEPARATING_SYMBOL = ';';
	const string FICHIER_POPULATION = "population.txt";
	const string FICHIER_PROBLEME = "problèmes.txt";
	const string FICHIER_UTILISATION = "utilisations.txt";
	bool isFound = false;
	//const int NOMBRE_CHAMPS = 3;
	string nomFichier = FICHIER_POPULATION;
	string ligneCourante;
	ifstream ficIn;
	vector<string> human;
	stringstream ss;
	string data;

	ficIn.open(FICHIER_POPULATION);
	while (!ficIn.is_open())
	{
		cout << "Erreur de lecture.\n";
		cout << "Veuillez entrer le nom du fichier contenant la population : ";
		cin >> nomFichier;
		ficIn.open(nomFichier);
	}
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			human.push_back(data);
		}
		if (vue == typeVision::CITOYEN)
		{
			if (human.size() >= 3 && human.front() == id)
			{
				isFound = true;
				break;
			}
		}
		else
		{
			if (vue == typeVision::PROFESSIONNEL)
			{
				if (human.size() == 5 && human[3] == id)
				{
					isFound = true;
					break;
				}
			}
		}
		human.clear();
		ss.str(std::string());
		ss.clear();
	}
	ficIn.close();
	//Aucun resultat ou bon resultat ici
	/*cout << endl;*/
	//system("pause");
	if (!isFound)
	{
		throw runtime_error("Code non trouvé");
	}
	//cout << isFound << endl;
	//for (string s : human)
	//{
	//	cout << s << ";";
	//}
	Citoyen* citoyen = ChargementCitoyen(human, vue);
	human.clear();
	ss.str(std::string());
	ss.clear();
	switch (vue)
	{
	case typeVision::CITOYEN:

		ss << citoyen->getNAS();
		citoyen->RajoutProbleme(ChargementProbleme(FICHIER_PROBLEME, ss.str()));
		citoyen->RajoutUtilisation(ChargementUtilisation(FICHIER_UTILISATION, ss.str(), vue));
		break;
	case typeVision::PROFESSIONNEL:
	{
		//Par l'exécution du code, nous savons déjà que le pointeur citoyen n'est qu'en fait un objet Professionnel créé dynamiquement.
		//Nous pouvons utilisé un static_cast qui nous sauve quelques teste lors de l'exécution.
		Professionnel* pp = static_cast<Professionnel*>(citoyen);
		list<RendezVous*> lu = ChargementUtilisation(FICHIER_UTILISATION, pp->getCodePS(), vue);
		citoyen->RajoutUtilisation(lu);
		ChargementPatient(FICHIER_POPULATION, pp, lu);
		//system("pause");
		break;
	}
	default:
		throw runtime_error("Chargement: typeVision non implémenté");

	}
	ss.str(std::string());
	ss.clear();
	return citoyen;
}


Citoyen* ChargementCitoyen(vector<string> data, typeVision vue)
{
	Citoyen* citoyen;
	switch (vue)
	{
	case typeVision::CITOYEN:
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		citoyen = new Citoyen(stoi(data[0]), data[1], data[2]);
		break;

	case typeVision::PROFESSIONNEL:
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		citoyen = new Professionnel(stoi(data[0]), data[1], data[2], data[3], data[4]);
		break;
	default:
		throw runtime_error("Chargement: typeVision non implémenté");
	}
	return citoyen;
}


list<RendezVous*> ChargementUtilisation(const string nomFichier, string id, typeVision type)
{
	const char SEPARATING_SYMBOL = ';';
	list<RendezVous*> liste;
	string ligneCourante;
	ifstream ficIn;
	vector<string> utilisation;
	stringstream ss;
	string data;

	ficIn.open(nomFichier);
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			utilisation.push_back(data);
		}

		if (utilisation.size() > 0 && (type == typeVision::CITOYEN && utilisation.front() == id || type == typeVision::PROFESSIONNEL && utilisation[1] == id))
		{
			switch (utilisation.size())
			{
			case 4:
				//Un Rendez-vous
				//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
				liste.push_back(new RendezVous(stoi(utilisation[0]), utilisation[1], utilisation[2], utilisation[3]));
				break;
			case 6:
				//Une Hospitalisation
				//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
				liste.push_back(new Hospitalisation(stoi(utilisation[0]), utilisation[1], utilisation[2], utilisation[3], utilisation[4], stoi(utilisation[5])));
				break;
			default:
				break;
				//Autre aka: une erreur
			}
		}
		ss.str(std::string());
		ss.clear();
		utilisation.clear();
	}
	ficIn.close();

	return liste;
}


list<Probleme*> ChargementProbleme(const string nomFichier, string id)
{
	const char SEPARATING_SYMBOL = ';';
	list<Probleme*> liste;
	string ligneCourante;
	ifstream ficIn;
	vector<string> probleme;
	stringstream ss;
	string data;

	ficIn.open(nomFichier);
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			probleme.push_back(data);
		}
		if (probleme.size() > 0 && probleme.front() == id)
		{
			switch (probleme.size())
			{
			case 5:
				//Une blessure
				//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
				liste.push_back(new Blessure(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4]));
				break;
			case 6:
				//Une Maladie
				//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
				liste.push_back(new Maladie(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4], stoi(probleme[5])));
				break;
			default:
				break;
				//Autre aka: une erreur
			}
		}
		ss.str(std::string());
		ss.clear();
		probleme.clear();
	}
	ficIn.close();
	return liste;
}

void ChargementPatient(const string nomFichier, Professionnel* pro, list<RendezVous*> rdvListe)
{
	const char SEPARATING_SYMBOL = ';';
	ifstream ficIn;
	stringstream ss;
	vector<string> patient;
	string ligneCourante;
	string data;
	for (RendezVous* rdv : rdvListe)
	{
		ss << rdv->getNas();
		//La clée n'existe pas
		if (!pro->PatientExiste(rdv->getNas()))
		{
			//Peut lancer une exception runtime_error si getNas est un NAS qui n'existe pas.
			//Citoyen* ci = Trouver(ss.str(), typeVision::CITOYEN, true);
			pro->RajoutPatient(rdv->getNas(), nullptr);
		}
		ss.str(std::string());
		ss.clear();
	}

	ficIn.open(nomFichier);
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			patient.push_back(data);
		}
		if (patient.size() == 0)
		{
			ss.str(std::string());
			ss.clear();
			patient.clear();
			break;
		}
		int nas = atoi(patient[0].c_str());
		if (pro->PatientExiste(nas))
		{
			pro->RajoutPatient(nas,ChargementCitoyen(patient, typeVision::CITOYEN));
		}
		ss.str(std::string());
		ss.clear();
		patient.clear();
	}
	ficIn.close();

}