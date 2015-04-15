#include "biblio.h"

/*
Utilise un principe d'indexation similaire � la base de donn�e du logiciel git (sa base de donn�e est un syst�me de fichier).
� partir d'une cl�e (NAS ou CodePS dans notre cas), calcule le SHA-1.
Le checksum servira � faire un path dans le syst�me de fichier, avec les 2 bytes plus significatif comme dossier, le reste du checksum
sera le nom du fichier. Le contenue du fichier sera l'information index�.

En plus, s�paration en trois "super-dossier" pour Utilisations, Probl�mes et Population �tant donn�e que tout est index� selon la m�me cl�e.
Je voulais garder cette s�paration par respect � la structure non-index�.

Comportement non-d�finie s'il y a une collision, tr�s improbable, mais fera tr�s mal.

Note: 
	-Par design, l'index sera difficilement lisible par un humain
	-Duplication de donn�e pour l'indexation d'un Professionnel puisqu'il a deux cl�e (NAS et CodePS) pour les deux vues diff�rentes.

*/


/*
V�rifie la validiter de l'index en comparant sa date de derni�re modification avec les fichiers de donn�es principaux.
Retourne un bool de la r�ponse
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
D�truit l'int�gralit� de l'index.
*/
void Index::DestroyIndex(const string root)
{
	//https://stackoverflow.com/questions/4180351/unable-to-delete-a-folder-with-shfileoperation
	//Quand m�me dangereux...
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
V�rifie si la cl�e est d�j� index� en calculant le SHA-1
et en essayant d'ouvrir le fichier qui est cr�� lors de l'indexation.
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
� partir de la cl�e, calcule le chemin du fichier qui sera cr�� � l'index.
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
M�thode publique pour index� les donn�es.
� partir d'une cl�e (string), de la ligne de donn�e � index� et du type de l'index,
cr�er les dossiers n�cessaire � l'index
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
M�thode qui cr�er le fichier et �crit les donn�es � l'int�rieur.
Cr�e le dossier n�cessaire � l'indexation de la ligne.
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
	//Ne remplace pas le contenue du fichier, mais �crit � la fin
	ofstream ofFichierIndex(fullPath, ios::app);
	ofFichierIndex << ligne << endl;
	ofFichierIndex.close();
}

/*
Retourne la ligne de donn�e index� � partir de la cl�e et du type de l'index.
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
Retourne une list<string> du contenu complet du fichier de l'index point� par la cl�e.
Comme getIndexed, mais Probl�mes et Utilisations n'ont pas des r�sultats unique pour chaque cl�e, alors il faut tout prendre.
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
M�thode pour obtenir la date d'un fichier.
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