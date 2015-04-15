


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

DateEpoch::DateEpoch(int A, int M, int J)
{
	An = A;
	Mois = M;
	Jour = J;
	Heure = 0;
	Minute = 0;
	Seconde = 0;
	ConvertFormatToEpoch();
}

DateEpoch::DateEpoch(int E)
{
	Epoch = E;
	ConvertEpochToFormat();
}

void DateEpoch::ConvertEpochToFormat()
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	//https://stackoverflow.com/questions/119578/disabling-warnings-generated-via-crt-secure-no-deprecate
#pragma warning(push)
#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
	// deprecated code here
	timeinfo = localtime(&rawtime);
#pragma warning(pop)
	//struct tm* timeinfo = new struct tm;
	//localtime_s(timeinfo, &Epoch);
	An = timeinfo->tm_year + 1900;
	Mois = timeinfo->tm_mon + 1;
	Jour = timeinfo->tm_mday;
	Heure = timeinfo->tm_hour;
	Minute = timeinfo->tm_min;
	Seconde = timeinfo->tm_sec;
}

void DateEpoch::ConvertFormatToEpoch()
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	//https://stackoverflow.com/questions/119578/disabling-warnings-generated-via-crt-secure-no-deprecate
#pragma warning(push)
#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
	// deprecated code here
	timeinfo = localtime(&rawtime);
#pragma warning(pop)

	//struct tm* timeinfo = new struct tm;
	//localtime_s(timeinfo, &Epoch);
	timeinfo->tm_year = An - 1900;
	timeinfo->tm_mon = Mois + 1;
	timeinfo->tm_mday = Jour;
	timeinfo->tm_hour = Heure;
	timeinfo->tm_min = Minute;
	timeinfo->tm_sec = Seconde;
	Epoch = mktime(timeinfo);
}

//Définission des opérateurs de comparaisons
bool DateEpoch::operator< (const DateEpoch& rh)
{
	//Epoch étant le nombre de seconde écoulé depuis 1970, on peut le comparé directement
	return this->Epoch < rh.Epoch;
}

bool DateEpoch::operator== (const DateEpoch& rh)
{

	return this->Epoch == rh.Epoch;
}

bool DateEpoch::operator<= (const DateEpoch& rh)
{
	return this->Epoch <= rh.Epoch;
}

bool DateEpoch::operator!= (const DateEpoch& rh)
{
	return this->Epoch != rh.Epoch;
}

bool DateEpoch::operator>= (const DateEpoch& rh)
{
	return this->Epoch >= rh.Epoch;
}

bool DateEpoch::operator> (const DateEpoch& rh)
{
	return this->Epoch > rh.Epoch;
}