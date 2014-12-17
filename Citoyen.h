class Citoyen
{
protected:
   int nas;
   string nom;
   string naissance;
   list<Probleme*> problemes;
   list<RendezVous*> rendezvous;
public:
   Citoyen();
   Citoyen(int, string, string);
   void RajoutUtilisation(list<RendezVous*>);
   void RajoutProbleme(list<Probleme*>);
   int getNAS();
   string getNom();
   string getNaissance();
   virtual void Afficher();
   void AfficherMaladie();
   void AfficherBlessure();
   void AfficherRendezVous();
   void AfficherHospitalisation();
};