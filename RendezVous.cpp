#include "biblio.h"


RendezVous::RendezVous() :nas(0), codeps("N/A"), etablissement("N/A"), date("N/A"){}

RendezVous::RendezVous(int n, string code, string etab, string d) :nas(n), codeps(code), etablissement(etab), date(d){}

void RendezVous::Afficher()
{

}