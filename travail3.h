class VecteurEntiers {
	public:
		VecteurEntiers();
		~VecteurEntiers();
	
		bool EstVide();
		int NombreElements();
		bool ContientElement(int element);
		void AjouteElement(int element, int index = -1);
		void SupprimeElement(int index);
		int ElementA(int index);
	
	private:
		int nombreElements;
		int capacite;
		int* donnees;
};

struct NoeudEntier {
	int valeur;
	NoeudEntier* noeudSuivant;
};

class ListeEntiers {
	public:
		ListeEntiers();
		~ListeEntiers();
	
		bool EstVide();
		int NombreElements();
		bool ContientElement(int element);
		void AjouteElement(int element, int index = -1);
		void SupprimeElement(int index);
		int ElementA(int index);
	
	private:
		NoeudEntier* premierNoeud;
		NoeudEntier* dernierNoeud;
};
