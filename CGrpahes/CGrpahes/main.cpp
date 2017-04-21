#include "CException.h"
#include "CGraphe.h"
#include "CParse.h"

#include <vld.h>
void main() {

	// TEST 1 - Constructeur par d�faut
		// Configuration
			// Creation d'un graphe vide
	CGraphe * GRANewGraphe1 = new CGraphe();
			// Test du graphe initialise
				// Test si le graphe existe et si NbSommets et NbArcs du graphe = 0
	if(GRANewGraphe1 != nullptr && GRANewGraphe1->GRAGetNbSommets() != 0 && GRANewGraphe1->GRAGetNbArcs() != 0)
		throw CException(ECHECNONTROUVE, "Erreur du test");

			// Affichage du graphe
	cout << "Test du graphe 1 -> Vide : " << endl;
	GRANewGraphe1->GRAAfficherGraphe();

			// Lib�ration m�moire du graphe
	delete(GRANewGraphe1);

	// TEST 2 - Constructeur de confort
		// Cr�ation d'un arc de sommet 1 vers 2
	CArc * ARCSommet1Vers2 = new CArc(2);
		// Cr�ation d'un arc de sommet 1 vers 3
	CArc * ARCSommet1Vers3 = new CArc(3);
		// Cr�ation d'un arc de sommet 3 vers 1
	CArc * ARCSommet3Vers1 = new CArc(1);
		// Cr�ation d'un arc de sommet 3 vers 2
	CArc * ARCSommet3Vers2 = new CArc(2);
	

		// Cr�ation du graphe
	CGraphe * GRANewGraphe2 = new CGraphe();
		// Affectation des 3 sommets au graphe
	GRANewGraphe2->GRAAjoutSommet(1, nullptr, nullptr);
	GRANewGraphe2->GRAAjoutSommet(2, nullptr, nullptr);
	GRANewGraphe2->GRAAjoutSommet(3, nullptr, nullptr);
		// V�rification du compteur g�n�ral du nombre de sommet dans le graphe
	if(GRANewGraphe2->GRAGetNbSommets() != 3)
		throw CException(ERREURTEST, "Erreur du test, il n'y a pas 3 sommets");



}