#include "biblio.h"


Blessure::Blessure(int n, string debut, string fin, string desc, string typ) :Probleme(n, debut, fin, desc), type(typ){}

Blessure::Blessure() : type("N/A"){}

void Blessure::Afficher()
{
	return;
}