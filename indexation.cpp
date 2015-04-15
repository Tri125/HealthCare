#include "biblio.h"

/*
Utilise un principe d'indexation similaire à la base de donnée du logiciel git (sa base de donnée est un système de fichier).
À partir d'une clée (NAS ou CodePS dans notre cas), calcule le SHA-1.
Le checksum servira à faire un path dans le système de fichier, avec les 2 bytes plus significatif comme dossier, le reste du checksum
sera le nom du fichier. Le contenue du fichier sera l'information indexé.

En plus, séparation en trois "super-dossier" pour Utilisations, Problèmes et Population étant donnée que tout est indexé selon la même clée.
Je voulais garder cette séparation par respect à la structure non-indexé.

Comportement non-définie s'il y a une collision, très improbable, mais fera très mal.

Note: 
	-Par design, l'index sera difficilement lisible par un humain
	-Duplication de donnée pour l'indexation d'un Professionnel puisqu'il a deux clée (NAS et CodePS) pour les deux vues différentes.

*/


/*
Vérifie la validiter de l'index en comparant sa date de dernière modification avec les fichiers de données principaux.
Retourne un bool de la réponse
*/
bool Index::isIndexValid(const string root)
{
	int utili = obtenirDateFichier(FICHIER_UTILISATION);
	int pop = obtenirDateFichier(FICHIER_POPULATION);
	int prob = obtenirDateFichier(FICHIER_PROBLEME);
	int index = obtenirDateFichier(root);

	return (index > prob && index > pop && index > utili);

}

/*
Détruit l'intégralité de l'index.
*/
void Index::DestroyIndex(const string root)
{
	//https://stackoverflow.com/questions/4180351/unable-to-delete-a-folder-with-shfileoperation
	//Quand même dangereux...
	SHFILEOPSTRUCT shfo = {
		NULL,
		FO_DELETE,
		"index",
		NULL,
		FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
		FALSE,
		NULL,
		NULL };
	SHFileOperation(&shfo);
}

/*
Vérifie si la clée est déjà indexé en calculant le SHA-1
et en essayant d'ouvrir le fichier qui est créé lors de l'indexation.
*/
bool Index::isIndexed(string code, IndexType type)
{
	ifstream ficIn;
	string databasePath = IndexingPath(code);
	string pathType;
	switch (type)
	{
	case IndexType::POPULATION:
		pathType = "\\population";
		break;
	case IndexType::UTILISATION:
		pathType = "\\utilisations";
		break;
	case IndexType::PROBLEME:
		pathType = "\\problemes";
		break;
	default:
		//erreur
		break;
	}
	string absolutePath = INDEX_PATH + pathType + "\\" + databasePath;
	ficIn.open(absolutePath);
	if (ficIn.is_open())
	{
		ficIn.close();
		return true;
	}
	else
		return false;
}

/*
À partir de la clée, calcule le chemin du fichier qui sera créé à l'index.
Retourne le string du path.
*/
string Index::IndexingPath(string code)
{
	unsigned char hash[20];
	char hexstring[41];
	string path;

	sha1::calc(code.c_str(), code.length(), hash);
	sha1::toHexString(hash, hexstring);
	path = hexstring;
	path.insert(2, "\\");
	return path;
}


/*
Méthode publique pour indexé les données.
À partir d'une clée (string), de la ligne de donnée à indexé et du type de l'index,
créer les dossiers nécessaire à l'index
*/
void Index::IndexData(string code, string ligne, IndexType type)
{
	if (!isIndexValid(INDEX_PATH))
	{
		DestroyIndex(INDEX_PATH);
	}
	CreateDirectory(INDEX_PATH.c_str(), NULL);
	CreateDirectory((INDEX_PATH + "\\population").c_str(), NULL);
	CreateDirectory((INDEX_PATH + "\\utilisations").c_str(), NULL);
	CreateDirectory((INDEX_PATH + "\\problemes").c_str(), NULL);
	ToIndex(code, ligne, type);
}


/*
Méthode qui créer le fichier et écrit les données à l'intérieur.
Crée le dossier nécessaire à l'indexation de la ligne.
*/
void Index::ToIndex(string code, string ligne, IndexType type)
{
	string path = IndexingPath(code);
	string pathType;
	switch (type)
	{
	case IndexType::POPULATION:
		pathType = "\\population";
		break;
	case IndexType::UTILISATION:
		pathType = "\\utilisations";
		break;
	case IndexType::PROBLEME:
		pathType = "\\problemes";
		break;
	default:
		//erreur
		break;
	}
	string fullPath = INDEX_PATH + pathType + "\\" + path.substr(0, 2);
	CreateDirectory(fullPath.c_str(), NULL);
	fullPath = INDEX_PATH + pathType + "\\" + path;
	//Ne remplace pas le contenue du fichier, mais écrit à la fin
	ofstream ofFichierIndex(fullPath, ios::app);
	ofFichierIndex << ligne << endl;
	ofFichierIndex.close();
}

/*
Retourne la ligne de donnée indexé à partir de la clée et du type de l'index.
Plus pour Population que autre chose.
*/
string Index::getIndexed(string code, IndexType type)
{
	string ligneCourante;
	ifstream ficIn;
	string path = IndexingPath(code);
	string pathType;
	vector<string> vLigne;
	stringstream ss;
	string champs;
	if (!isIndexed(code, type))
		return ligneCourante;
	switch (type)
	{
	case IndexType::POPULATION:
		pathType = "\\population";
		break;
	case IndexType::UTILISATION:
		pathType = "\\utilisations";
		break;
	case IndexType::PROBLEME:
		pathType = "\\problemes";
		break;
	default:
		//erreur
		break;
	}
	string fullPath = INDEX_PATH + pathType + "\\" + path;
	ficIn.open(fullPath);
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		getline(ss, champs, SEPARATING_SYMBOL);
		vLigne.push_back(champs);
		if (vLigne.size() == 0)
		{
			ss.str(std::string());
			ss.clear();
			vLigne.clear();
			continue;
		}
		//if (vLigne[0] != code)
		//{
		//	ligneCourante.clear();
		//}
		//else
		//{
		//	break;
		//}
		ss.str(std::string());
		ss.clear();
		vLigne.clear();
		break;
	}
	ficIn.close();
	return ligneCourante;
}

/*
Retourne une list<string> du contenu complet du fichier de l'index pointé par la clée.
Comme getIndexed, mais Problèmes et Utilisations n'ont pas des résultats unique pour chaque clée, alors il faut tout prendre.
*/
list<string> Index::getIndexedLines(string code, IndexType type)
{
	list<string> results;
	string ligneCourante;
	ifstream ficIn;
	string path = IndexingPath(code);
	string pathType;
	vector<string> vLigne;
	stringstream ss;
	string champs;
	if (!isIndexed(code, type))
		return results;
	switch (type)
	{
	case IndexType::POPULATION:
		pathType = "\\population";
		break;
	case IndexType::UTILISATION:
		pathType = "\\utilisations";
		break;
	case IndexType::PROBLEME:
		pathType = "\\problemes";
		break;
	default:
		//erreur
		break;
	}
	string fullPath = INDEX_PATH + pathType + "\\" + path;
	ficIn.open(fullPath);
	while (ficIn.good())
	{
		getline(ficIn, ligneCourante);
		ss << ligneCourante;
		getline(ss, champs, SEPARATING_SYMBOL);
		vLigne.push_back(champs);
		if (vLigne.size() == 0)
		{
			ss.str(std::string());
			ss.clear();
			vLigne.clear();
			continue;
		}
		results.push_back(ligneCourante);
		ss.str(std::string());
		ss.clear();
		vLigne.clear();
	}
	ficIn.close();
	return results;
}

/*
Méthode pour obtenir la date d'un fichier.
*/
int Index::obtenirDateFichier(string sNomFichier)
{
	stringstream strTampon;
	WIN32_FILE_ATTRIBUTE_DATA fileATTR;
	GetFileAttributesExA(sNomFichier.c_str(), GetFileExInfoStandard, &fileATTR);
	FILETIME ft = fileATTR.ftLastWriteTime;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(&ft, &ft); //Ajuste les fuseaux horaire
	FileTimeToSystemTime(&ft, &st);

	return DateEpoch(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond).Epoch;
}