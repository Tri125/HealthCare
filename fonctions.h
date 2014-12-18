enum class typeVision
{
   CITOYEN, PROFESSIONNEL
};

enum class typeTriePatient
{
	NAISSANCE, NAS, NOM
};

enum class typeTrieIntervention
{
	DATE, ETABLISSEMENT
};

//Un peu �trange de d�finir un attribut directement ici, mais n�cessaire pour l'utilisation de param�tre optionnelle avec valeur par d�fault.
Citoyen* Trouver(string, typeVision);
Citoyen* ChargementCitoyen(vector<string> citoyen, typeVision);
list<RendezVous*> ChargementUtilisation(const string, string, typeVision);
list<Probleme*> ChargementProbleme(const string, string);
void ChargementPatient(const string, Professionnel*, list<RendezVous*>);

void TrieIntervention(Professionnel*, typeTrieIntervention, bool);

void TriePatient(Professionnel*, typeTriePatient,bool);

DateEpoch stringToEpoch(string);



bool compare_date(RendezVous*, RendezVous*);
bool compare_Date(RendezVous*, RendezVous*);
bool compare_etab(RendezVous*, RendezVous*);
bool compare_Etab(RendezVous*, RendezVous*);


bool compare_Nas(Citoyen*, Citoyen*);
bool compare_nas(Citoyen*, Citoyen*);
bool compare_nom(Citoyen*, Citoyen*);
bool compare_Nom(Citoyen*, Citoyen*);
bool compare_nais(Citoyen*, Citoyen*);
bool compare_Nais(Citoyen*, Citoyen*);