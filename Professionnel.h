class Professionnel : public Citoyen
{
private:
   string codeps;
   string titre;
   //key: NAS  value: Citoyen*
   //Pour associé les Patients du Professionnel
   map<int, Citoyen*> mapPatients;
   //Key: NAS value: nombre d'intervention
   //Pour associé le nombre d'intervention que le patient a eu avec le Professionnel
   map<int, int> mapNbrIntervention;
   //Créé à partir de la map, plus facile avec les sorts.
   list<Citoyen*> listePatients;

public:
   Professionnel();
   ~Professionnel();
   Professionnel(int, string, string, string, string);
   string getCodePS();
   void RajoutPatient(int, Citoyen*);
   map<int, Citoyen*>::iterator TrouverPatient(int);
   bool PatientExiste(int);
   void Afficher();
   list<Citoyen*> getListePatients();
   void setListePatients(list<Citoyen*>);
   void AfficherPatients();
   void AugmenteIntervention(int);
   void AfficherInterventions();
};

