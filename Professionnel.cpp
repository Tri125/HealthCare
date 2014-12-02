#include "biblio.h"


Professionnel::Professionnel() : codeps("N/A"), titre("N/A"){}

Professionnel::Professionnel(int nas, string nom, string nais, string cps, string t) :Citoyen(nas, nom, nais), codeps(cps), titre(t){}

string Professionnel::getCodePS()
{
	return codeps;
}