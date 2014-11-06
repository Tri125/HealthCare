#include "biblio.h"


Professionnel::Professionnel() :Citoyen()
{
}

Professionnel::Professionnel(int nas, string nom, string nais, string cps, string t) :Citoyen(nas, nom, nais), codeps(cps), titre(t){}