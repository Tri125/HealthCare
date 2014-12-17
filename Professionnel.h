class Professionnel : public Citoyen
{
private:
   string codeps;
   string titre;
   map<int, Citoyen*> mapPatients;

public:
   Professionnel();
   Professionnel(int, string, string, string, string);
   string getCodePS();
   void RajoutPatient(int, Citoyen*);
   map<int, Citoyen*>::iterator TrouverPatient(int);
   bool PatientExiste(int);
   void Afficher();
};

