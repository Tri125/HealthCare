


#include "biblio.h"

void DateEpoch::Affiche()
{
	cout << An << "-";
	//Pour s'assurer d'afficher deux digit pour respecter le format de date de 10 caractères
	if (Mois < 10)
		cout << 0;

	cout << Mois << "-";
	if (Jour < 10)
		cout << 0;
	cout << Jour << endl;
}

string DateEpoch::ToString()
{
	stringstream ss;
	ss.str(std::string());

	ss << An << "-";
	if (Mois < 10)
		ss << 0;

	ss << Mois << "-";
	if (Jour < 10)
		ss << 0;
	ss << Jour;
	return ss.str();
}


DateEpoch::DateEpoch()
{
	Epoch = time(NULL);
	ConvertEpochToFormat();
}

DateEpoch::DateEpoch(int A, int M, int J, int H, int Min, int Sec)
{
	An = A;
	Mois = M;
	Jour = J;
	Heure = H;
	Minute = Min;
	Seconde = Sec;
	ConvertFormatToEpoch();
}

DateEpoch::DateEpoch(int E)
{
	Epoch = E;
	ConvertEpochToFormat();
}

void DateEpoch::ConvertEpochToFormat()
{
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &Epoch);
	An = ptm->tm_year + 1900;
	Mois = ptm->tm_mon + 1;
	Jour = ptm->tm_mday;
	Heure = ptm->tm_hour;
	Minute = ptm->tm_min;
	Seconde = ptm->tm_sec;
}

void DateEpoch::ConvertFormatToEpoch()
{
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &Epoch);

	ptm->tm_year = An - 1900;
	ptm->tm_mon = Mois + 1;
	ptm->tm_mday = Jour;
	ptm->tm_hour = Heure;
	ptm->tm_min = Minute;
	ptm->tm_sec = Seconde;
	Epoch = mktime(ptm);
}

//Définission des opérateurs de comparaisons
bool DateEpoch::operator< (DateEpoch& rh)
{
	//Epoch étant le nombre de seconde écoulé depuis 1970, on peut le comparé directement
	return this->Epoch < rh.Epoch;
}

bool DateEpoch::operator== (DateEpoch& rh)
{

	return this->Epoch == rh.Epoch;
}

bool DateEpoch::operator<= (DateEpoch& rh)
{
	return this->Epoch <= rh.Epoch;
}

bool DateEpoch::operator!= (DateEpoch& rh)
{
	return this->Epoch != rh.Epoch;
}

bool DateEpoch::operator>= (DateEpoch& rh)
{
	return this->Epoch >= rh.Epoch;
}

bool DateEpoch::operator> (DateEpoch& rh)
{
	return this->Epoch > rh.Epoch;
}