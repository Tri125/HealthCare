#include "biblio.h"


RendezVous::RendezVous() :nas(0), codeps("N/A"), etablissement("N/A"), date("N/A"){}

RendezVous::RendezVous(int n, string code, string etab, string d) :nas(n), codeps(code), etablissement(etab), date(d){}

int RendezVous::getNas(){ return nas; }
string RendezVous::getCodePS(){ return codeps; }
string RendezVous::getEtablissement(){ return etablissement; }
string RendezVous::getDate(){ return date; }

void RendezVous::Afficher()
{
	cout << etablissement << "\t";
	if (etablissement.length() <= 14)
	{
		cout << "\t";
	}
	cout << date << "\t" << codeps;
}