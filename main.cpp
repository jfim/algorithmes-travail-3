#include "travail3.h"

#include <iostream>
#include <malloc.h>

namespace {
	int score = 0;
	int objetsAlloues = 0;
	int objetsAllouesDebut = 0;
	int nombreAllocations = 0;
	int nombreAllocationsDebut = 0;
}

void debuteQuestion(const char* question) {
	std::cout << question << std::endl;
}

bool verifie(const char* message, bool correct) {
	std::cout << "  " << message;
	if(correct)
		std::cout << ": correct" << std::endl;
	else
		std::cout << ": incorrect" << std::endl;
	return correct;
}

void valideQuestion(int scoreQuestion, bool correct) {
	if(correct) {
		std::cout << scoreQuestion << " points" << std::endl << std::endl;
		score += scoreQuestion;
	}
	else
		std::cout << 0 << " points" << std::endl << std::endl;
}

void* operator new(size_t size) {
	nombreAllocations++;
	objetsAlloues++;
	return malloc(size);
}

void* operator new[](size_t size) {
	nombreAllocations++;
	objetsAlloues++;
	return malloc(size);
}

void operator delete(void* ptr) {
	free(ptr);
	objetsAlloues--;
}

void operator delete[](void* ptr) {
	free(ptr);
	objetsAlloues--;
}

void resetAllocation() {
	objetsAllouesDebut = objetsAlloues;
	nombreAllocationsDebut = nombreAllocations;
}

int deltaAllocation() {
	return objetsAlloues - objetsAllouesDebut;
}

int deltaNombreAllocations() {
	return nombreAllocations - nombreAllocationsDebut;
}

int main(int argc, char** argv) {
	{
		VecteurEntiers vecteur;

		debuteQuestion("Un vecteur vide");
		valideQuestion(1,
			verifie("est vide", vecteur.EstVide()) &&
			verifie("contient 0 elements", vecteur.NombreElements() == 0)
		);
	}

	{
		VecteurEntiers vecteur;
		vecteur.AjouteElement(1);
		vecteur.AjouteElement(2);
		vecteur.AjouteElement(3);

		debuteQuestion("Un vecteur contenant 1, 2, 3");
		valideQuestion(1,
			verifie("n'est pas vide", !vecteur.EstVide()) &&
			verifie("contient 3 elements", vecteur.NombreElements() == 3) &&
			verifie("contient 1", vecteur.ElementA(0) == 1) &&
			verifie("contient 2", vecteur.ElementA(1) == 2) &&
			verifie("contient 3", vecteur.ElementA(2) == 3)
		);

		debuteQuestion("Et si on ajoute 4 au debut");
		vecteur.AjouteElement(4, 0);
		valideQuestion(1,
			verifie("n'est pas vide", !vecteur.EstVide()) &&
			verifie("contient 4 elements", vecteur.NombreElements() == 4) &&
			verifie("contient 4", vecteur.ElementA(0) == 4) &&
			verifie("contient 1", vecteur.ElementA(1) == 1) &&
			verifie("contient 2", vecteur.ElementA(2) == 2) &&
			verifie("contient 3", vecteur.ElementA(3) == 3)
		);

		debuteQuestion("Et si on ote l'element a l'index 1");
		vecteur.SupprimeElement(1);
		valideQuestion(1,
			verifie("n'est pas vide", !vecteur.EstVide()) &&
			verifie("contient 3 elements", vecteur.NombreElements() == 3) &&
			verifie("contient 4", vecteur.ElementA(0) == 4) &&
			verifie("contient 2", vecteur.ElementA(1) == 2) &&
			verifie("contient 3", vecteur.ElementA(2) == 3) &&
			verifie("ne contient pas 1", !vecteur.ContientElement(1))
		);
	}

	{
		VecteurEntiers vecteur;
		debuteQuestion("Un vecteur auquel on ajoute 25 millions d'elements");

		resetAllocation();

		for(int i = 0; i < 25000000; ++i)
			vecteur.AjouteElement(i - 42);

		bool elementsSontCorrects = true;
		for(int i = 0; i < 25000000; ++i)
			elementsSontCorrects = elementsSontCorrects && vecteur.ElementA(i) == i - 42;

		valideQuestion(1,
			verifie("possede une performance O(1) amortie", deltaNombreAllocations() < 1000) &&
			verifie("contient les bons elements", elementsSontCorrects)
		);
	}

	{
		ListeEntiers listeChainee;

		debuteQuestion("Une liste chainee vide");
		valideQuestion(1,
			verifie("est vide", listeChainee.EstVide()) &&
			verifie("contient 0 elements", listeChainee.NombreElements() == 0)
		);
	}

	{
		ListeEntiers listeChainee;
		listeChainee.AjouteElement(1);
		listeChainee.AjouteElement(2);
		listeChainee.AjouteElement(3);

		debuteQuestion("Une liste chainee contenant 1, 2, 3");
		valideQuestion(1,
			verifie("n'est pas vide", !listeChainee.EstVide()) &&
			verifie("contient 3 elements", listeChainee.NombreElements() == 3) &&
			verifie("contient 1", listeChainee.ElementA(0) == 1) &&
			verifie("contient 2", listeChainee.ElementA(1) == 2) &&
			verifie("contient 3", listeChainee.ElementA(2) == 3)
		);

		debuteQuestion("Et si on ajoute 4 au debut");
		listeChainee.AjouteElement(4, 0);
		valideQuestion(1,
			verifie("n'est pas vide", !listeChainee.EstVide()) &&
			verifie("contient 4 elements", listeChainee.NombreElements() == 4) &&
			verifie("contient 4", listeChainee.ElementA(0) == 4) &&
			verifie("contient 1", listeChainee.ElementA(1) == 1) &&
			verifie("contient 2", listeChainee.ElementA(2) == 2) &&
			verifie("contient 3", listeChainee.ElementA(3) == 3)
		);

		debuteQuestion("Et si on ote l'element a l'index 1");
		listeChainee.SupprimeElement(1);
		valideQuestion(1,
			verifie("n'est pas vide", !listeChainee.EstVide()) &&
			verifie("contient 3 elements", listeChainee.NombreElements() == 3) &&
			verifie("contient 4", listeChainee.ElementA(0) == 4) &&
			verifie("contient 2", listeChainee.ElementA(1) == 2) &&
			verifie("contient 3", listeChainee.ElementA(2) == 3) &&
			verifie("ne contient pas 1", !listeChainee.ContientElement(1))
		);
	}

	{
		ListeEntiers listeChainee;
		debuteQuestion("Une liste chainee auquel on ajoute 25 millions d'elements");

		for(int i = 0; i < 25000000; ++i)
			listeChainee.AjouteElement(i - 42);

		bool elementsSontCorrects = true;
		for(int i = 24999990; i < 25000000; ++i)
			elementsSontCorrects = elementsSontCorrects && listeChainee.ElementA(i) == i - 42;

		valideQuestion(1,
			verifie("contient les bons elements", elementsSontCorrects)
		);

		resetAllocation();

		debuteQuestion("Et si on lui ote le premier million d'elements");

		elementsSontCorrects = true;
		for(int i = 0; i < 1000000; ++i)
			listeChainee.SupprimeElement(0);
		for(int i = 0; i < 250; ++i)
			elementsSontCorrects = elementsSontCorrects && listeChainee.ElementA(i) == i - 42 + 1000000;

		valideQuestion(1,
			verifie("contient les bons elements", elementsSontCorrects) &&
			verifie("libere correctement sa memoire", deltaAllocation() == -1000000)
		);
	}

	debuteQuestion("Et apres tout avoir execute");
	valideQuestion(1,
		verifie("il n'y a pas de fuite de memoire", objetsAlloues == 0)
	);

	std::cout << "Score " << score << "/12" << std::endl;
}
