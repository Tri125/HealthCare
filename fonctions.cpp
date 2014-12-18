#include "biblio.h"


Citoyen* Trouver(string id, typeVision vue)
{
	Index index;
	bool isFound = false;
	//const int NOMBRE_CHAMPS = 3;
	string nomFichier = FICHIER_POPULATION;
	string ligneCourante;
	ifstream ficIn;
	vector<string> human;
	stringstream ss;
	string data;
	ligneCourante = index.getIndexed(id, Index::IndexType::POPULATION);

	if (ligneCourante.length() == 0)
	{
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
					index.IndexData(id, ligneCourante, Index::IndexType::POPULATION);
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
						index.IndexData(id, ligneCourante, Index::IndexType::POPULATION);
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
	}
	else
	{
		isFound = true;
		ss << ligneCourante;
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			human.push_back(data);
		}
	}
	//Aucun resultat ou bon resultat ici
	if (!isFound)
	{
		throw runtime_error("Code non trouvé");
	}

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
	Index index;
	list<RendezVous*> liste;
	string ligneCourante;
	ifstream ficIn;
	vector<string> utilisation;
	stringstream ss;
	string data;
	list<string> results;
	results = index.getIndexedLines(id, Index::IndexType::UTILISATION);
	if (results.size() == 0)
	{
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
					index.IndexData(id, ligneCourante, Index::IndexType::UTILISATION);
					//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
					liste.push_back(new RendezVous(stoi(utilisation[0]), utilisation[1], utilisation[2], utilisation[3]));
					break;
				case 6:
					//Une Hospitalisation
					index.IndexData(id, ligneCourante, Index::IndexType::UTILISATION);
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
	}
	else
	{
		for (string ligne : results)
		{
			ss << ligne;
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
	}

	return liste;
}


list<Probleme*> ChargementProbleme(const string nomFichier, string id)
{
	list<Probleme*> liste;
	string ligneCourante;
	ifstream ficIn;
	vector<string> probleme;
	stringstream ss;
	string data;
	Index index;
	list<string> results;

	results = index.getIndexedLines(id, Index::IndexType::PROBLEME);

	if (results.size() == 0)
	{

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
					index.IndexData(id, ligneCourante, Index::IndexType::PROBLEME);
					//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
					liste.push_back(new Blessure(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4]));
					break;
				case 6:
					//Une Maladie
					index.IndexData(id, ligneCourante, Index::IndexType::PROBLEME);
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
	}
	else
	{
		for (string ligne : results)
		{
			ss << ligne;
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
					index.IndexData(id, ligneCourante, Index::IndexType::PROBLEME);
					//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
					liste.push_back(new Blessure(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4]));
					break;
				case 6:
					//Une Maladie
					index.IndexData(id, ligneCourante, Index::IndexType::PROBLEME);
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
	}
	return liste;
}

void ChargementPatient(const string nomFichier, Professionnel* pro, list<RendezVous*> rdvListe)
{
	Index index;
	ifstream ficIn;
	stringstream ss;
	vector<string> patient;
	string ligneCourante;
	string data;
	list<string> results;
	bool indexIncomplet = false;
	for (RendezVous* rdv : rdvListe)
	{
		pro->AugmenteIntervention(rdv->getNas());
		//La clée n'existe pas
		if (!pro->PatientExiste(rdv->getNas()))
		{
			if (!indexIncomplet)
			{
				ss << rdv->getNas();
				string line = (index.getIndexed(ss.str(), Index::IndexType::POPULATION));
				if (line.size() == 0)
					indexIncomplet = true;
				else
				{
					results.push_back(line);
				}
				ss.str(std::string());
				ss.clear();
			}
			pro->RajoutPatient(rdv->getNas(), nullptr);
		}
	}
	if (indexIncomplet)
	{
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
				continue;
			}
			int nas = atoi(patient[0].c_str());
			if (pro->PatientExiste(nas))
			{
				index.IndexData(patient[0], ligneCourante, Index::IndexType::POPULATION);
				pro->RajoutPatient(nas, ChargementCitoyen(patient, typeVision::CITOYEN));
			}
			ss.str(std::string());
			ss.clear();
			patient.clear();
		}
		ficIn.close();
	}
	else
	{
		for (string ligne : results)
		{
			ss << ligne;
			while (getline(ss, data, SEPARATING_SYMBOL))
			{
				patient.push_back(data);
			}
			if (patient.size() == 0)
			{
				ss.str(std::string());
				ss.clear();
				patient.clear();
				continue;
			}
			int nas = atoi(patient[0].c_str());
			if (pro->PatientExiste(nas))
			{
				pro->RajoutPatient(nas, ChargementCitoyen(patient, typeVision::CITOYEN));
			}
			ss.str(std::string());
			ss.clear();
			patient.clear();
		}
	}

}


bool compare_Nas(Citoyen* first, Citoyen* second)
{
	return (first->getNAS() > second->getNAS());
}

bool compare_nas(Citoyen* first, Citoyen* second)
{
	return (first->getNAS() < second->getNAS());
}

bool compare_nom(Citoyen* first, Citoyen* second)
{
	return (first->getNom() < second->getNom());
}

bool compare_Nom(Citoyen* first, Citoyen* second)
{
	return (first->getNom() > second->getNom());
}

bool compare_nais(Citoyen* first, Citoyen* second)
{
	string firstNais = first->getNaissance();
	string secondNais = second->getNaissance();


	DateEpoch firstEpoch = stringToEpoch(firstNais);

	DateEpoch secondEpoch = stringToEpoch(secondNais);


	return (firstEpoch.Epoch < secondEpoch.Epoch);
}

bool compare_Nais(Citoyen* first, Citoyen* second)
{
	string firstNais = first->getNaissance();
	string secondNais = second->getNaissance();

	DateEpoch firstEpoch = stringToEpoch(firstNais);

	DateEpoch secondEpoch = stringToEpoch(secondNais);


	return (firstEpoch.Epoch > secondEpoch.Epoch);
}

void TriePatient(Professionnel* pro, typeTriePatient type, bool croissant)
{
	list<Citoyen*>  li = pro->getListePatients();
	switch (type)
	{
	case typeTriePatient::NAS:
		if (croissant)
			li.sort(compare_nas);
		else
			li.sort(compare_Nas);
		break;
	case typeTriePatient::NOM:
		if (croissant)
			li.sort(compare_nom);
		else
			li.sort(compare_Nom);
		break;
	case typeTriePatient::NAISSANCE:
		if (croissant)
			li.sort(compare_nais);
		else
			li.sort(compare_Nais);
		break;
	default:
		break;
	}
	pro->setListePatients(li);
}


bool compare_date(RendezVous* first, RendezVous* second)
{

	string firstNais = first->getDate();
	string secondNais = second->getDate();


	DateEpoch firstEpoch = stringToEpoch(firstNais);

	DateEpoch secondEpoch = stringToEpoch(secondNais);


	return (firstEpoch.Epoch < secondEpoch.Epoch);
}

bool compare_Date(RendezVous* first, RendezVous* second)
{
	string firstNais = first->getDate();
	string secondNais = second->getDate();


	DateEpoch firstEpoch = stringToEpoch(firstNais);

	DateEpoch secondEpoch = stringToEpoch(secondNais);


	return (firstEpoch.Epoch > secondEpoch.Epoch);
}

bool compare_etab(RendezVous* first, RendezVous* second)
{
	return (first->getEtablissement() < second->getEtablissement());
}

bool compare_Etab(RendezVous* first, RendezVous* second)
{
	return (first->getEtablissement() > second->getEtablissement());
}

void TrieIntervention(Professionnel* pro, typeTrieIntervention type, bool croissant)
{
	list<RendezVous*> li = pro->getListRdv();
	switch (type)
	{
	case typeTrieIntervention::DATE:
		if (croissant)
			li.sort(compare_date);
		else
			li.sort(compare_Date);
		break;
	case typeTrieIntervention::ETABLISSEMENT:
		if (croissant)
			li.sort(compare_etab);
		else
			li.sort(compare_Etab);
		break;
	default:
		break;
	}
	pro->setListRdv(li);
}


DateEpoch stringToEpoch(string l)
{
	int annee = stoi(l.substr(0, 4));
	int mois = stoi(l.substr(5, 7));
	int jour = stoi(l.substr(8));
	return DateEpoch(annee, mois, jour);
}