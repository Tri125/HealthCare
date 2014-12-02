class Professionnel : public Citoyen
{
private:
   string codeps;
   string titre;

public:
   Professionnel();
   Professionnel(int, string, string, string, string);
   string getCodePS();
};

