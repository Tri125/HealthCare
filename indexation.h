
class Index{
public:

	enum class IndexType{
		POPULATION, UTILISATION, PROBLEME
	};
	bool isIndexed(string, IndexType);
	string getIndexed(string, IndexType);
	void IndexData(string, string, IndexType);
	list<string> getIndexedLines(string, IndexType);

private:
	bool isIndexValid(const string);
	void DestroyIndex(const string);
	string IndexingPath(string);
	void ToIndex(string, string, IndexType);
	int convertToEpoch(string);
	int obtenirDateFichier(string);


};