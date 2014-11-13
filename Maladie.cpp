#include "biblio.h"


Maladie::Maladie() : pathologie("N/A"), stade(0){}

Maladie::Maladie(int nas, string debut, string fin, string desc, string patho, int stad) :Probleme(nas, debut, fin, desc)
{
	pathologie = patho;
	stade = stad;
}

