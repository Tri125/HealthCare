#include "biblio.h"




bool isIndexValid(const string root)
{
	int utili = obtenirDateFichier(FICHIER_UTILISATION);
	int pop = obtenirDateFichier(FICHIER_POPULATION);
	int prob = obtenirDateFichier(FICHIER_PROBLEME);
	int index = obtenirDateFichier(root);

	return (index > prob && index > pop && index > utili);

}


void DestroyIndex(const string root)
{
	//https://stackoverflow.com/questions/4180351/unable-to-delete-a-folder-with-shfileoperation
	//Quand même dangereux...
	SHFILEOPSTRUCT shfo = {
		NULL,
		FO_DELETE,
		"E:\\Users\\Tristan\\Documents\\Visual Studio 2013\\Projects\\Alain\\OOP_TP4\\Index",
		NULL,
		FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
		FALSE,
		NULL,
		NULL };
	SHFileOperation(&shfo);
}
bool isIndexed(string code)
{
	ifstream ficIn;
	string databasePath = IndexingPath(code);
	string absolutePath = INDEX_PATH + "\\" + databasePath;
	ficIn.open(absolutePath);
	return ficIn.is_open();
}

string IndexingPath(string code)
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

void Index()
{
	if (!isIndexValid(INDEX_PATH))
	{
		DestroyIndex(INDEX_PATH);
	}
	CreateDirectory(INDEX_PATH.c_str(), NULL);
	Indexing("12", "uN bon petit teste d'indexation");

}

void Indexing(string code, string ligne)
{
	string path = IndexingPath(code);
	string fullPath = INDEX_PATH + "\\" + path.substr(0,2);
	CreateDirectory(fullPath.c_str(),NULL);
	fullPath = INDEX_PATH + "\\" + path;

	ofstream ofFichierIndex(fullPath, ios::app);
	ofFichierIndex << ligne << endl;
	ofFichierIndex.close();
}

string getIndexed(string code)
{

}


int obtenirDateFichier(string sNomFichier)
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