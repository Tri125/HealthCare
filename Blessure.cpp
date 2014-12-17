#include "biblio.h"


Blessure::Blessure(int n, string type, string debut, string fin, string description) :Probleme(n, debut, fin, description), type(type){}

Blessure::Blessure() : type("N/A"){}

void Blessure::Afficher()
{
	cout << type << "\t" << dateDebut << "\t" << dateFin << "\t";
	if (dateFin.length() == 0)
	{
		cout << "\t";
	}
	cout << description << endl;
}