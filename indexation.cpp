#include "biblio.h"




bool Index::isIndexValid(const string root)
{
	int utili = obtenirDateFichier(FICHIER_UTILISATION);
	int pop = obtenirDateFichier(FICHIER_POPULATION);
	int prob = obtenirDateFichier(FICHIER_PROBLEME);
	int index = obtenirDateFichier(root);

	return (index > prob && index > pop && index > utili);

}


void Index::DestroyIndex(const string root)
{
	//https://stackoverflow.com/questions/4180351/unable-to-delete-a-folder-with-shfileoperation
	//Quand même dangereux...
	SHFILEOPSTRUCT shfo = {
		NULL,
		FO_DELETE,
		"E:\\Users\\Tristan\\Documents\\Visual Studio 2013\\Projects\\Alain\\OOP_TP4\\index",
		NULL,
		FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
		FALSE,
		NULL,
		NULL };
	SHFileOperation(&shfo);
}
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

	ofstream ofFichierIndex(fullPath, ios::app);
	ofFichierIndex << ligne << endl;
	ofFichierIndex.close();
}

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


int Index::obtenirDateFichier(string sNomFichier)
{
	stringstream strTampon;
	WIN32_FILE_ATTRIBUTE_DATA fileATTR;
	GetFileAttributesExA(sNomFichier.c_str(), GetFileExInfoStandard, &fileATTR);
	FILETIME ft = fileATTR.ftLastWriteTime;
	SYSTEMTIME st;
	FileTimeToLocalFileTime(&ft, &ft); //Ajuste les fuseaux horaire
	FileTimeToSystemTime(&ft, &st);

	//strTampon << setfill('0');
	//strTampon << right;
	//strTampon << setw(4) << st.wYear << "-" << setw(2) << st.wMonth << "-" << setw(2) << st.wDay << ":" << setw(2) << st.wHour << ":" << setw(2) << st.wMinute << ":" << setw(2) << st.wSecond << ":" << setw(3) << st.wMilliseconds;
	//strTampon << setfill(' ');
	return DateEpoch(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond).Epoch;
}