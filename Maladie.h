
class Maladie :
	public Probleme
{
private:
	string pathologie;
	int stade;
public:
	Maladie();
	Maladie(int, string, string, string, string, int);
	void Afficher();
};

