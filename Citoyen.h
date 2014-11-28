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
   void RajoutRDV(list<RendezVous*>);
   void RajoutProb(list<Probleme*>);
};