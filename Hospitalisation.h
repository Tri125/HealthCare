class Hospitalisation : public RendezVous
{

private:
   string dateFin;
   int chambre;

public:
   Hospitalisation();
   Hospitalisation(int, string, string, string, string, int);
   void Afficher();
};

