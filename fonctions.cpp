#include "biblio.h"

/*
� partir d'un string repr�sentant le code (la cl�e) et de l'enum typeVision qui d�termine la vue soit Professionnelle ou Citoytenne,
recherche les fichiers pour instantier un objet Citoyen, ses utilisation et ces rendezvous pour ensuite retourner un pointeur.

Est la fonction principal d'entr�. De elle, les autres sont appel�es.
*/
Citoyen* Trouver(string id, typeVision vue)
{
	Index index;
	//Sert pour avertir si le code est invalide
	bool isFound = false;
	string nomFichier = FICHIER_POPULATION;
	string ligneCourante;
	ifstream ficIn;
	vector<string> human;
	stringstream ss;
	string data;
	//Recherche dans l'index le Citoyen � partir de son code.
	ligneCourante = index.getIndexed(id, Index::IndexType::POPULATION);
	//Si aucun r�sultat dans l'index, on recherche dans les fichiers non index�s
	if (ligneCourante.length() == 0)
	{
		ficIn.open(FICHIER_POPULATION);
		while (!ficIn.is_open())
		{
			//Petite gentillesse, si le fichier n'existe pas, quoique inutile, car n'est pas offert pour les autres fichiers.
			cout << "Erreur de lecture.\n";
			cout << "Veuillez entrer le nom du fichier contenant la population : ";
			cin >> nomFichier;
			ficIn.open(nomFichier);
		}
		while (ficIn.good())
		{
			getline(ficIn, ligneCourante);
			ss << ligneCourante;
			//S�pare la ligne par ces champs de donn�es avec un vector.
			while (getline(ss, data, SEPARATING_SYMBOL))
			{
				human.push_back(data);
			}
			//Si nous sommes en vue CITOYEN
			if (vue == typeVision::CITOYEN)
			{
				if (human.size() >= 3 && human.front() == id)
				{
					//On index la ligne avec id comme cl�e d'acc�s.
					index.IndexData(id, ligneCourante, Index::IndexType::POPULATION);
					isFound = true;
					break;
				}
			}
			//Si nous sommes en vue Professionnel
			else
			{
				if (vue == typeVision::PROFESSIONNEL)
				{
					if (human.size() == 5 && human[3] == id)
					{
						//On index la ligne avec id (le codePS) comme cl�e d'acc�s.
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
	//Si nous avons trouv� le Citoyen dans l'index.
	else
	{
		isFound = true;
		ss << ligneCourante;
		//S�pare la ligne par ces champs de donn�es avec un vector.
		while (getline(ss, data, SEPARATING_SYMBOL))
		{
			human.push_back(data);
		}
	}
	//Aucun resultat ou bon resultat ici
	if (!isFound)
	{
		throw runtime_error("Code non trouv�");
	}
	//Envois le vector et le type de vue.
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
		//Par l'ex�cution du code, nous savons d�j� que le pointeur citoyen n'est qu'en fait un objet Professionnel cr�� dynamiquement.
		//Nous pouvons utilis� un static_cast qui nous sauve quelques teste lors de l'ex�cution.
		Professionnel* pp = static_cast<Professionnel*>(citoyen);
		/*
		Puisque Professionnel h�rite de Citoyen, nous r�utilisons la list<RendezVous> pour ses Interventions qui sont en fait, que des objets RendezVous.
		*/
		list<RendezVous*> lu = ChargementUtilisation(FICHIER_UTILISATION, pp->getCodePS(), vue);
		//Rajoute les Interventions
		citoyen->RajoutUtilisation(lu);
		ChargementPatient(FICHIER_POPULATION, pp, lu);
		break;
	}
	default:
		throw runtime_error("Chargement: typeVision non impl�ment�");

	}
	ss.str(std::string());
	ss.clear();
	return citoyen;
}


/*
� partir d'un vector<string> et du typeVision, instancie dynamiquement soit un Citoyen, ou un Professionnel et retourne son pointeur.
*/
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
		throw runtime_error("Chargement: typeVision non impl�ment�");
	}
	return citoyen;
}

/*
� partir d'un string, recherche les Utilisations (objets RendezVous et Hospitalisation)
pour en faire une list et la retourner.

Dans le cas o� nous sommes en vus Professionnelle, Utilisation repr�sente les Interventions.
*/
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
	//Recherche dans l'index
	results = index.getIndexedLines(id, Index::IndexType::UTILISATION);
	//Aucun r�sultat
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
				index.IndexData(id, ligneCourante, Index::IndexType::UTILISATION);
				liste.push_back(InstantieUtilisation(utilisation));

			}
			ss.str(std::string());
			ss.clear();
			utilisation.clear();
		}
		ficIn.close();
	}
	//Trouv� dans l'index
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
				liste.push_back(InstantieUtilisation(utilisation));
			}
			ss.str(std::string());
			ss.clear();
			utilisation.clear();
		}
	}

	return liste;
}



/*
� partir d'un vector<string>, instantie dynamiquement soit un objet RendezVous ou Hospitalisation et retourne le pointeur.
*/
RendezVous* InstantieUtilisation(vector<string> utilisation)
{
	RendezVous* rdv;
	switch (utilisation.size())
	{
	case 4:
		//Un Rendez-vous
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		rdv = new RendezVous(stoi(utilisation[0]), utilisation[1], utilisation[2], utilisation[3]);
		break;
	case 6:
		//Une Hospitalisation
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		rdv = new Hospitalisation(stoi(utilisation[0]), utilisation[1], utilisation[2], utilisation[3], utilisation[4], stoi(utilisation[5]));
		break;
	default:
		//�tant donn� que les fichiers sont d�j� valid�, ne devrait pas ce produire, mais calme le compilateur sur la possibilit� de retourner un objet
		//non initialis�.
		rdv = nullptr;
		//Autre aka: une erreur
	}
	return rdv;
}

/*
� partir d'un code, recherche les "Probl�mes" (objet Maladie ou Blessure) et retourne une list<Probleme*>
*/
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
	//Recherche dans l'index
	results = index.getIndexedLines(id, Index::IndexType::PROBLEME);

	//Aucune r�sultat dans l'index, donc m�thode � l'aveugle.
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
				//On enregistre dans l'index.
				index.IndexData(id, ligneCourante, Index::IndexType::PROBLEME);
				liste.push_back(InstantieProbleme(probleme));
			}
			ss.str(std::string());
			ss.clear();
			probleme.clear();
		}
		ficIn.close();
	}
	//Trouv� dans l'index
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
				liste.push_back(InstantieProbleme(probleme));
			}
			ss.str(std::string());
			ss.clear();
			probleme.clear();
		}
	}
	return liste;
}


/*
� partir d'un vector<string>, instancie dynamiquement un objet Probleme (Blessure ou Maladie) et retourne son pointeur.
*/
Probleme* InstantieProbleme(vector<string> probleme)
{
	Probleme* pProb;
	switch (probleme.size())
	{
	case 5:
		//Une blessure
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		pProb = new Blessure(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4]);
		break;
	case 6:
		//Une Maladie
		//stoi: invalid_argument if conversion impossible, out_of_range exception if data can't fit into an int type.
		pProb = new Maladie(stoi(probleme[0]), probleme[1], probleme[2], probleme[3], probleme[4], stoi(probleme[5]));
		break;
	default:
		//�tant donn� que les fichiers sont d�j� valid�, ne devrait pas ce produire, mais calme le compilateur sur la possibilit� de retourner un objet
		//non initialis�.
		pProb = nullptr;
		//Autre aka: une erreur
	}

	return pProb;
}


/*
� partir d'un pointeur d'un objet Professionnel et d'une liste de pointeur sur des objets RendezVous (Intervention du Professionnel)
Recherche les patients du professionnel et les enregistre.
*/
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
		//Augmente un compteur qui compte le nombre d'intervention que le patient � subi avec le Professionnel.
		pro->AugmenteIntervention(rdv->getNas());
		//La cl�e n'existe pas
		if (!pro->PatientExiste(rdv->getNas()))
		{
			//Si l'index est incomplet, cela veux dire qu'il y a au moins un RendezVous non index�, nous allons
			//donc traiter le tout comme �tant non index� par simple simplicit�
			if (!indexIncomplet)
			{
				ss << rdv->getNas();
				//Recherche dans l'index le Patient associ� au RendezVous.
				string line = (index.getIndexed(ss.str(), Index::IndexType::POPULATION));
				//Aucun r�sultat, alors index incomplet.
				if (line.size() == 0)
					indexIncomplet = true;
				else
				{
					//Un Patient sortie de l'index, on le rajoute dans le vector results.
					results.push_back(line);
				}
				ss.str(std::string());
				ss.clear();
			}
			//Rajoute dans une map, la valeur n'est pas n�cessaire pour le moment d'o� le nullptr.
			//Va nous permettre te connaitre tout les NAS des patients.
			pro->RajoutPatient(rdv->getNas(), nullptr);
		}
	}
	//Index incomplet, donc lecture � l'aveugle dans les fichiers.
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
			//Si le patient est d�j� associ� au Professionnel
			if (pro->PatientExiste(nas))
			{
				//On l'indexe
				index.IndexData(patient[0], ligneCourante, Index::IndexType::POPULATION);
				//On va rechercher le Citoyen et le rajoute dans la map de Patient.
				//Le nullptr de tout � l'heure sera donc remplac�.
				pro->RajoutPatient(nas, ChargementCitoyen(patient, typeVision::CITOYEN));
			}
			ss.str(std::string());
			ss.clear();
			patient.clear();
		}
		ficIn.close();
	}
	//Index complet
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

/*
Trie la liste de Patient (Citoyen*) du Professionnel selon l'ordre croissant/d�croissant
et diff�rent crit�re de s�lection.

Utilise des comparators et list<T>.sort()
*/
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


/*
Trie la liste d'Intervention (RendezVous*) du Professionnel selon l'ordre croissant/d�croissant
et diff�rent crit�re de s�lection.

Utilise des comparators et list<T>.sort()
*/
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

/*
Utilis� pour compar� les Dates. Avec un string format� selon
YYYY-MM-DD, cr�e un objet DateEpoch et le retourne.
*/
DateEpoch stringToEpoch(string l)
{
	int annee = stoi(l.substr(0, 4));
	int mois = stoi(l.substr(5, 7));
	int jour = stoi(l.substr(8));
	return DateEpoch(annee, mois, jour);
}



#pragma region SortComparator

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

#pragma endregion