class RendezVous
{

protected:
   int nas;
   string codeps;
   string etablissement;
   string date;

public:
   RendezVous();
   RendezVous(int, string, string, string);
   int getNas();
   string getCodePS();
   string getEtablissement();
   string getDate();
   virtual void Afficher();
};

