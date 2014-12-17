#include "biblio.h"


Maladie::Maladie() : pathologie("N/A"), stade(0){}

Maladie::Maladie(int nas, string patho, string debut, string fin, string desc, int stad) :Probleme(nas, debut, fin, desc)
{
	pathologie = patho;
	stade = stad;
}


void Maladie::Afficher()
{
	cout << pathologie << "\t" << stade << "\t" << dateDebut << "\t" << dateFin << "\t";
	if (dateFin.length() == 0)
	{
		cout << "\t";
	}
	cout << description << endl;
}
