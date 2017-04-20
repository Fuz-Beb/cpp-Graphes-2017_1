<<<<<<< HEAD
#include "CGraphe.h"
#include "CException.h"

/*****************************
Constructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CGraphe::CGraphe()
{
	ppqGRASommets = nullptr;
	uiGRANbSommets = 0;
	uiGRANbArcs = 0;
}

/*****************************
Constructeur de recopie
******************************
Entr�e : CSommet & sommet);
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en param�tre est recopi� et initialis� dans un nouvel objet
*****************************/
CGraphe::CGraphe(CGraphe & graphe)
{
	if(ppqGRASommets != nullptr) {
		ppqGRASommets = nullptr;
		delete(ppqGRASommets);
	}

	// Allocation de la liste sommet
	ppqGRASommets = (CSommet **)malloc(sizeof(CSommet*) * graphe.uiGRANbSommets);
	
	if(ppqGRASommets == nullptr)
		throw CException(ECHECALLOCATION, "Echec de l'allocation");

	ppqGRASommets = graphe.ppqGRASommets;
	uiGRANbSommets = graphe.uiGRANbSommets;
	uiGRANbArcs = graphe.uiGRANbArcs;
}

/*****************************
Constructeur de confort
******************************
Entr�e : unsigned int uiNbSommets, unsigned int uiNbArcs, CSommet ** sommets
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CGraphe::CGraphe(unsigned int uiNbSommets, unsigned int uiNbArcs, CSommet ** sommets)
{
	if(ppqGRASommets != nullptr) {
		ppqGRASommets = nullptr;
		delete(ppqGRASommets);
	}

	// Allocation de la liste sommet
	ppqGRASommets = (CSommet **)malloc(sizeof(CSommet*) * uiNbSommets);
	
	if(ppqGRASommets == nullptr)
		throw CException(ECHECALLOCATION, "Echec de l'allocation");

	ppqGRASommets = sommets;
	uiGRANbSommets = uiNbSommets;
	uiGRANbArcs = uiNbArcs;
}

/*****************************
Destructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet est d�truit
*****************************/
CGraphe::~CGraphe()
{
	unsigned int uiBoucle = 0;

	// Boucle pour liberer la liste des sommets
	while(uiBoucle != uiGRANbSommets) {
		ppqGRASommets[uiBoucle] = nullptr;
		delete[] ppqGRASommets[uiBoucle];
		uiBoucle++;
	}

	ppqGRASommets = nullptr;
	delete[] ppqGRASommets;
}

// Accesseurs

/*****************************
Methode : Lire Nombre Sommets
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : unsigned int uiGRANbSommets
Entraine : retourne l'attribut
*****************************/
unsigned int CGraphe::GRAGetNbSommets()
{
	return uiGRANbSommets;
}

/*****************************
Methode : Modifier Nombre Sommets
******************************
Entr�e : unsigned int uiNbSommets
Necessit� : n�ant
Sortie : n�ant
Entraine : affecte le param�tre � l'attribut
*****************************/
void CGraphe::GRASetNbSommets(unsigned int uiNbSommets)
{
	uiGRANbSommets = uiNbSommets;
}

/*****************************
Methode : Lire Nombre Arcs
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : unsigned int uiGRANbArcs
Entraine : retourne l'attribut
*****************************/
unsigned int CGraphe::GRAGetNbArcs()
{
	return uiGRANbArcs;
}

/*****************************
Methode : Modifier Nombre Arcs
******************************
Entr�e : unsigned int uiNbArcs
Necessit� : n�ant
Sortie : n�ant
Entraine : affecte le param�tre � l'attribut
*****************************/
void CGraphe::GRASetNbArcs(unsigned int uiNbArcs)
{
	uiGRANbArcs = uiNbArcs;
}

/*****************************
Methode : Ajouter Sommet
******************************
Entr�e : unsigned int uiSommet, CArc * ppqArrivant, CArc * ppqPartant
Necessit� : n�ant
Sortie : n�ant
Entraine : ajoute un nouveau sommet au graphe
*****************************/
void CGraphe::GRAAjoutSommet(unsigned int uiSommet, CArc * ppqArrivant, CArc * ppqPartant)
{
	// Unicit� avant cr�ation d'un sommet
	CSommet * SOMlistSommets = GRATrouverSommet(uiSommet);
	if(SOMlistSommets != nullptr)
		throw CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");

	// Cr�ation d'un nouveau sommet
	CSommet * SOMnewSommet = new CSommet(uiSommet, ppqArrivant, ppqPartant);

	// V�rification de la bonne cr�ation
	if(SOMnewSommet == nullptr)
		throw CException(ECHECNEWSOMMET, "Echec de la cr�ation d'un nouveau sommet");

	// V�rification d'une pr�sence de liste
	if(ppqGRASommets == nullptr) {
		// Cr�ation d'une liste avec comme taille 1 sommet
		ppqGRASommets = (CSommet **)malloc(sizeof(CSommet *));
		// V�rification de la bonne cr�ation
		if(ppqGRASommets == nullptr)
			throw CException(ECHECALLOCATION, "Echec de l'allocation");
	}
	// Dans le cas o� la liste est d�j� existante
	else {
		// R�allocation + 1 sommet
		(CSommet **)realloc(ppqGRASommets, sizeof(ppqGRASommets) + sizeof(CSommet *));
		// V�rification de la bonne r�allocation
		if(ppqGRASommets == nullptr)
			throw CException(ECHECALLOCATION, "Echec de l'allocation");
	}

	// Ajout � la liste du graphe le sommet et incr�ment son nombre
	ppqGRASommets[uiGRANbSommets] = SOMnewSommet;
	uiGRANbSommets++;

	if(ppqArrivant != nullptr && ppqPartant != nullptr)
		uiGRANbArcs++;
}

/*****************************
Methode : Supprimer Sommet
******************************
Entr�e : CSommet * sommet
Necessit� / Pr�conditions : fournir un objet en param�tre non nul
Sortie : n�ant
Entraine : supprime un sommet au graphe
*****************************/
void CGraphe::GRASupprimerSommet(CSommet * sommet)
{
	unsigned int uiBoucle = 0;

	// Permet de supprimer les arcs li�s � ce sommet
	sommet->SOMViderSommet();

	// V�rification de la pr�sence d'une liste non nul
	if(ppqGRASommets == nullptr)
		throw CException(ECHECNONTROUVE, "Echec la liste des sommets est nul");

	// Realloc de la bonne taille - 1 sommet
	(CSommet **)realloc(ppqGRASommets, sizeof(ppqGRASommets) - sizeof(CSommet *));
	if(ppqGRASommets == nullptr)
		throw CException(ECHECALLOCATION, "Echec de l'allocation");

	// Suppression � la liste du graphe le sommet et d�cr�mentant son nombre
	delete(ppqGRASommets[uiGRANbSommets]);
	uiGRANbSommets--;
}

/*****************************
Methode : Modifier Sommet
******************************
Entr�e : unsigned int uiNum, CSommet * SOMSommet
Necessit� / Pr�conditions : fournir un objet en param�tre non nul
Sortie : n�ant
Entraine : modifie un sommet au graphe
*****************************/
void CGraphe::GRAModifierSommet(unsigned int uiNum, CSommet * SOMSommet)
{
	// Unicit� avant modification d'un sommet
	CSommet * SOMlistSommets = GRATrouverSommet(uiNum);
	if(SOMlistSommets != nullptr)
		throw CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");

	// FAIRE ICI UNE MODIF DE TOUT LES ARCS EN RELATION AVEC SOMSommet num actuel avant chang
	unsigned int uiBoucle = 0;

	// Permet d'actualiser le nouveau num�ro du sommet aux arcs pr�c�dant
	while(uiBoucle != SOMSommet->SOMGetNbrArcArrivant) {
		SOMSommet->SOMGetListArcArrivant[uiBoucle]->ARCSetDestination(uiNum);
		uiBoucle++;
	}
	// Permet de changer le num�ro du sommet
	SOMSommet->SOMSetNum(uiNum);
}

/*****************************
Methode : R�cup�rer Sommet
******************************
Entr�e : unsigned int uiSommet
Necessit� : GRATrouverSommet
Sortie : n�ant
Entraine : r�cup�re un sommet du graphe
*****************************/
CSommet * CGraphe::GRAGetSommet(unsigned int uiSommet)
{
	return GRATrouverSommet(uiSommet);
}

/*****************************
Methode : Ajouter Arc
******************************
Entr�e : unsigned int uiDestination, CSommet * sommet
Necessit� : n�ant
Sortie : n�ant
Entraine : ajoute un nouvel arc au graphe
*****************************/
void CGraphe::GRAAjoutArc(unsigned int uiDestination, CSommet * SOMSommet)
{

	CSommet * SOMDestination = GRATrouverSommet(uiDestination);
	CArc * ARCNewArc = nullptr;

	if(SOMDestination == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur la uiDestination n'a pas �t� trouv�e");
	else {
		// Verification d'unicite dans le lien / Impossible d'avoir 1 -> 2 et 1 -> 2
		if(GRATrouverArc(sommet, SOMDestination) != nullptr)
			throw CException(ECHECDOUBLONARC, "Erreur doublon d'arc");

		// Creation d'un nouvel arc et affectation
		ARCNewArc = new CArc(uiDestination);
		sommet->SOMAddArcPartant(ARCNewArc);
		SOMDestination->SOMAddArcArrivant(ARCNewArc);
	}
}

/*****************************
Methode : Supprimer Arc
******************************
Entr�e : CArc ** ARCarc
Necessit� : n�ant
Sortie : n�ant
Entraine : supprime un arc au graphe
*****************************/
void CGraphe::GRASupprimerArc(CArc ** ARCarc)
{
	unsigned int uiNumSource = 0, uiNumDestination = 0;
	CSommet * SOMSource = nullptr, * SOMDestination = nullptr;
	CArc * ARCarc = nullptr;

	if(ARCarc == nullptr && ARCarc[0] == nullptr && ARCarc[1] == nullptr)
		throw CException(ERREURARGS, "Erreur l'argument n'est pas correcte");

	uiNumSource = ARCarc[0]->ARCGetDestination;
	uiNumDestination = ARCarc[1]->ARCGetDestination;


	// Rercherche et affectation des sommets
	SOMSource = GRATrouverSommet(uiNumSource);
	if(SOMSource == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur sommet non trouv�");

	SOMDestination = GRATrouverSommet(uiNumDestination);
	if(SOMDestination == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur sommet non trouv�");

	// Suppression des informations de l'arc dans le sommet source en question
	ARCarc = GRATrouverArc(SOMSource->SOMGetListArcPartant, SOMDestination);
	if(ARCarc == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur arc non trouv�");

	delete[] ARCarc;

	// Suppression des informations de l'arc dans le sommet destination en question
	ARCarc = GRATrouverArc(SOMDestination->SOMGetListArcPartant, SOMDestination);
	if(ARCarc == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur arc non trouv�");

	delete[] ARCarc;
}

/*****************************
Methode : Afficher Arc
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : affichage du graphe
Entraine : affichage du graphe dans la console
*****************************/
void CGraphe::GRAAfficherGraphe()
{

}

/*****************************
Methode : Trouver Sommet
******************************
Entr�e : unsigned int uiSommet
Necessit� : n�ant
Sortie : CSommet * 
Entraine : cherche et renvoi le sommet
*****************************/
CSommet * CGraphe::GRATrouverSommet(unsigned int uiSommet)
{
	for(unsigned int uiBoucleSommet = 0 ; uiBoucleSommet < uiGRANbSommets ; uiBoucleSommet++) {
		if(ppqGRASommets[uiBoucleSommet]->SOMGetNum == uiSommet)
			return ppqGRASommets[uiBoucleSommet];

		uiBoucleSommet++;
	}

	return nullptr;
}

/*****************************
Methode : Trouver Arc
******************************
Entr�e : CSommet * SOMSource, CSommet * SOMDestination
Necessit� : n�ant
Sortie : CArc **
Entraine : cherche et renvoi l'arc
*****************************/
CArc ** CGraphe::GRATrouverArc(CSommet * SOMSource, CSommet * SOMDestination)
{
	CArc * ARCArcActuelArrivant = nullptr, * ARCArcActuelPartant = nullptr;
	CArc ** ARCSourceDestination = nullptr;

	for(unsigned int uiBoucleSommet = 0 ; uiBoucleSommet < uiGRANbSommets ; uiBoucleSommet++) {
		for(unsigned int uiBoucleArcs = 0 ; uiBoucleArcs < uiGRANbArcs ; uiBoucleArcs++) {
			
			ARCArcActuelArrivant = ppqGRASommets[uiBoucleSommet]->SOMGetListArcArrivant[uiBoucleArcs];
			ARCArcActuelPartant = ppqGRASommets[uiBoucleSommet]->SOMGetListArcPartant[uiBoucleArcs];
			
			if(ARCArcActuelArrivant->ARCGetDestination ==  SOMSource->SOMGetNum && ARCArcActuelPartant->ARCGetDestination == SOMDestination->SOMGetNum) {
				ARCSourceDestination = (CArc **)malloc(sizeof(CArc *) * 2);
				
				if(ARCSourceDestination == nullptr)
					throw CException(ECHECALLOCATION, "Echec de l'allocation");

				ARCSourceDestination[0] = ARCArcActuelArrivant;
				ARCSourceDestination[1]= ARCArcActuelPartant;

				return ARCSourceDestination;
			}

			uiBoucleArcs++;
		}

		uiBoucleSommet++;
	}
	
	return ARCSourceDestination;
}
=======
=======
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
#include "CGraphe.h"
#include "CException.h"

/*****************************
Constructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CGraphe::CGraphe()
{
	ppqGRASommets = nullptr;
	uiGRANbSommets = 0;
	uiGRANbArcs = 0;
}

/*****************************
Constructeur de recopie
******************************
Entr�e : CSommet & sommet);
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en param�tre est recopi� et initialis� dans un nouvel objet
*****************************/
CGraphe::CGraphe(CGraphe & graphe)
{
	if(ppqGRASommets != nullptr) {
		ppqGRASommets = nullptr;
		delete(ppqGRASommets);
	}

	// Allocation de la liste sommet
	ppqGRASommets = (CSommet **)malloc(sizeof(CSommet*) * graphe.uiGRANbSommets);
	
	if(ppqGRASommets == nullptr)
<<<<<<< HEAD
		throw new CException(ECHECALLOCATION, "Echec de l'allocation");
=======
		throw CException(ECHECALLOCATION, "Echec de l'allocation");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	ppqGRASommets = graphe.ppqGRASommets;
	uiGRANbSommets = graphe.uiGRANbSommets;
	uiGRANbArcs = graphe.uiGRANbArcs;
}

/*****************************
Constructeur de confort
******************************
Entr�e : unsigned int uiNbSommets, unsigned int uiNbArcs, CSommet ** sommets
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CGraphe::CGraphe(unsigned int uiNbSommets, unsigned int uiNbArcs, CSommet ** sommets)
{
	if(ppqGRASommets != nullptr) {
		ppqGRASommets = nullptr;
		delete(ppqGRASommets);
	}

	// Allocation de la liste sommet
	ppqGRASommets = (CSommet **)malloc(sizeof(CSommet*) * uiNbSommets);
	
	if(ppqGRASommets == nullptr)
<<<<<<< HEAD
		throw new CException(ECHECALLOCATION, "Echec de l'allocation");
=======
		throw CException(ECHECALLOCATION, "Echec de l'allocation");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	ppqGRASommets = sommets;
	uiGRANbSommets = uiNbSommets;
	uiGRANbArcs = uiNbArcs;
}

/*****************************
Destructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet est d�truit
*****************************/
CGraphe::~CGraphe()
{
	unsigned int uiBoucle = 0;

	// Boucle pour liberer la liste des sommets
	while(uiBoucle != uiGRANbSommets) {
		ppqGRASommets[uiBoucle] = nullptr;
		delete[] ppqGRASommets[uiBoucle];
		uiBoucle++;
	}

	ppqGRASommets = nullptr;
	delete[] ppqGRASommets;
}

// Accesseurs

/*****************************
Methode : Lire Nombre Sommets
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : unsigned int uiGRANbSommets
Entraine : retourne l'attribut
*****************************/
unsigned int CGraphe::GRAGetNbSommets()
{
	return uiGRANbSommets;
}

/*****************************
Methode : Modifier Nombre Sommets
******************************
Entr�e : unsigned int uiNbSommets
Necessit� : n�ant
Sortie : n�ant
Entraine : affecte le param�tre � l'attribut
*****************************/
void CGraphe::GRASetNbSommets(unsigned int uiNbSommets)
{
	uiGRANbSommets = uiNbSommets;
}

/*****************************
Methode : Lire Nombre Arcs
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : unsigned int uiGRANbArcs
Entraine : retourne l'attribut
*****************************/
unsigned int CGraphe::GRAGetNbArcs()
{
	return uiGRANbArcs;
}

/*****************************
Methode : Modifier Nombre Arcs
******************************
Entr�e : unsigned int uiNbArcs
Necessit� : n�ant
Sortie : n�ant
Entraine : affecte le param�tre � l'attribut
*****************************/
void CGraphe::GRASetNbArcs(unsigned int uiNbArcs)
{
	uiGRANbArcs = uiNbArcs;
}

/*****************************
Methode : Ajouter Sommet
******************************
Entr�e : unsigned int uiSommet, CArc * ppqArrivant, CArc * ppqPartant
Necessit� : n�ant
Sortie : n�ant
Entraine : ajoute un nouveau sommet au graphe
*****************************/
void CGraphe::GRAAjoutSommet(unsigned int uiSommet, CArc * ppqArrivant, CArc * ppqPartant)
{
	// Unicit� avant cr�ation d'un sommet
	CSommet * SOMlistSommets = GRATrouverSommet(uiSommet);
	if(SOMlistSommets != nullptr)
<<<<<<< HEAD
		throw new CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");
=======
		throw CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	// Cr�ation d'un nouveau sommet
	CSommet * SOMnewSommet = new CSommet(uiSommet, ppqArrivant, ppqPartant);

	// V�rification de la bonne cr�ation
	if(SOMnewSommet == nullptr)
<<<<<<< HEAD
		throw new CException(ECHECNEWSOMMET, "Echec de la cr�ation d'un nouveau sommet");
=======
		throw CException(ECHECNEWSOMMET, "Echec de la cr�ation d'un nouveau sommet");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	// V�rification d'une pr�sence de liste
	if(ppqGRASommets == nullptr) {
		// Cr�ation d'une liste avec comme taille 1 sommet
		ppqGRASommets = (CSommet **)malloc(sizeof(CSommet *));
		// V�rification de la bonne cr�ation
		if(ppqGRASommets == nullptr)
<<<<<<< HEAD
			throw new CException(ECHECALLOCATION, "Echec de l'allocation");
=======
			throw CException(ECHECALLOCATION, "Echec de l'allocation");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
	}
	// Dans le cas o� la liste est d�j� existante
	else {
		// R�allocation + 1 sommet
		(CSommet **)realloc(ppqGRASommets, sizeof(ppqGRASommets) + sizeof(CSommet *));
		// V�rification de la bonne r�allocation
		if(ppqGRASommets == nullptr)
<<<<<<< HEAD
			throw new CException(ECHECALLOCATION, "Echec de l'allocation");
=======
			throw CException(ECHECALLOCATION, "Echec de l'allocation");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
	}

	// Ajout � la liste du graphe le sommet et incr�ment son nombre
	ppqGRASommets[uiGRANbSommets] = SOMnewSommet;
	uiGRANbSommets++;

	if(ppqArrivant != nullptr && ppqPartant != nullptr)
		uiGRANbArcs++;
}

/*****************************
Methode : Supprimer Sommet
******************************
<<<<<<< HEAD
Entr�e : CSommet & sommet
=======
Entr�e : CSommet * sommet
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
Necessit� / Pr�conditions : fournir un objet en param�tre non nul
Sortie : n�ant
Entraine : supprime un sommet au graphe
*****************************/
<<<<<<< HEAD
void CGraphe::GRASupprimerSommet(CSommet & sommet)
=======
void CGraphe::GRASupprimerSommet(CSommet * sommet)
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
{
	unsigned int uiBoucle = 0;

	// Permet de supprimer les arcs li�s � ce sommet
<<<<<<< HEAD
	sommet.SOMViderSommet();

	// V�rification de la pr�sence d'une liste non nul
	if(ppqGRASommets == nullptr)
		throw new CException(ECHECNONTROUVE, "Echec la liste des sommets est nul");
=======
	sommet->SOMViderSommet();

	// V�rification de la pr�sence d'une liste non nul
	if(ppqGRASommets == nullptr)
		throw CException(ECHECNONTROUVE, "Echec la liste des sommets est nul");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	// Realloc de la bonne taille - 1 sommet
	(CSommet **)realloc(ppqGRASommets, sizeof(ppqGRASommets) - sizeof(CSommet *));
	if(ppqGRASommets == nullptr)
<<<<<<< HEAD
		throw new CException(ECHECALLOCATION, "Echec de l'allocation");
=======
		throw CException(ECHECALLOCATION, "Echec de l'allocation");
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984

	// Suppression � la liste du graphe le sommet et d�cr�mentant son nombre
	delete(ppqGRASommets[uiGRANbSommets]);
	uiGRANbSommets--;
}

/*****************************
Methode : Modifier Sommet
******************************
<<<<<<< HEAD
Entr�e : unsigned int uiNum, CSommet & SOMSommet
=======
Entr�e : unsigned int uiNum, CSommet * SOMSommet
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
Necessit� / Pr�conditions : fournir un objet en param�tre non nul
Sortie : n�ant
Entraine : modifie un sommet au graphe
*****************************/
<<<<<<< HEAD
void CGraphe::GRAModifierSommet(unsigned int uiNum, CSommet & SOMSommet)
{
	/*
	// Unicit� avant modification d'un sommet
	CSommet * SOMlistSommets = GRATrouverSommet(uiNum);
	if(SOMlistSommets != nullptr)
		throw new CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");

	// FAIRE ICI UNE MODIF DE TOUT LES ARCS EN RELATION AVEC SOMSommet num actuel avant chang
	unsigned int uiBoucle = 0, uiAncienNum = SOMSommet.SOMGetNum;

	GRAAjoutArc(SOMSommet.SOMGetListArcArrivant



	CSommet * SOMSommet = nullptr, *SOMSommetBoucle = 0;


	while(uiBoucle != uiGRANbSommets) {
		SOMSommetBoucle = new CSommet(ppqGRASommets[uiBoucle]);
		
		if(SOMSommetBoucle == 

		SOMSommetBoucle = GRAGetSommet(SOMSommet.SOMGetNum);
		SOMSommet =
		uiBoucle ++;
	}

	SOMSommet.SOMSetNum(uiNum);
	*/
=======
void CGraphe::GRAModifierSommet(unsigned int uiNum, CSommet * SOMSommet)
{
	// Unicit� avant modification d'un sommet
	CSommet * SOMlistSommets = GRATrouverSommet(uiNum);
	if(SOMlistSommets != nullptr)
		throw CException(ECHECNEWSOMMET, "Echec il existe deja un sommet avec ce numero");

	// FAIRE ICI UNE MODIF DE TOUT LES ARCS EN RELATION AVEC SOMSommet num actuel avant chang
	unsigned int uiBoucle = 0;

	// Permet d'actualiser le nouveau num�ro du sommet aux arcs pr�c�dant
	while(uiBoucle != SOMSommet->SOMGetNbrArcArrivant) {
		SOMSommet->SOMGetListArcArrivant[uiBoucle]->ARCSetDestination(uiNum);
		uiBoucle++;
	}
	// Permet de changer le num�ro du sommet
	SOMSommet->SOMSetNum(uiNum);
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
}

/*****************************
Methode : R�cup�rer Sommet
******************************
Entr�e : unsigned int uiSommet
<<<<<<< HEAD
Necessit� : n�ant
=======
Necessit� : GRATrouverSommet
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
Sortie : n�ant
Entraine : r�cup�re un sommet du graphe
*****************************/
CSommet * CGraphe::GRAGetSommet(unsigned int uiSommet)
{
<<<<<<< HEAD
	
=======
	return GRATrouverSommet(uiSommet);
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
}

/*****************************
Methode : Ajouter Arc
******************************
Entr�e : unsigned int uiDestination, CSommet * sommet
Necessit� : n�ant
Sortie : n�ant
Entraine : ajoute un nouvel arc au graphe
*****************************/
<<<<<<< HEAD
void CGraphe::GRAAjoutArc(unsigned int uiDestination, CSommet * sommet)
{

=======
void CGraphe::GRAAjoutArc(unsigned int uiDestination, CSommet * SOMSommet)
{

	CSommet * SOMDestination = GRATrouverSommet(uiDestination);
	CArc * ARCNewArc = nullptr;

	if(SOMDestination == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur la uiDestination n'a pas �t� trouv�e");
	else {
		// Verification d'unicite dans le lien / Impossible d'avoir 1 -> 2 et 1 -> 2
		if(GRATrouverArc(sommet, SOMDestination) != nullptr)
			throw CException(ECHECDOUBLONARC, "Erreur doublon d'arc");

		// Creation d'un nouvel arc et affectation
		ARCNewArc = new CArc(uiDestination);
		sommet->SOMAddArcPartant(ARCNewArc);
		SOMDestination->SOMAddArcArrivant(ARCNewArc);
	}
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
}

/*****************************
Methode : Supprimer Arc
******************************
<<<<<<< HEAD
Entr�e : CArc * arc
=======
Entr�e : CArc ** ARCarc
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
Necessit� : n�ant
Sortie : n�ant
Entraine : supprime un arc au graphe
*****************************/
<<<<<<< HEAD
void CGraphe::GRASupprimerArc(CArc * arc)
{

}

/*****************************
Methode : Modifier Arc
******************************
Entr�e : unsigned int uiDestination, CSommet * sommet
Necessit� : n�ant
Sortie : n�ant
Entraine : modifie un arc au graphe
*****************************/
void CGraphe::GRAModifierArc(unsigned int uiDestination, CSommet * sommet)
{

}

/*****************************
Methode : R�cup�rer Arc
******************************
Entr�e : unsigned int uiDestination
Necessit� : n�ant
Sortie : n�ant
Entraine : r�cup�re un arc du graphe
*****************************/
CSommet * CGraphe::GRAGetArc(unsigned int uiDestination)
{

=======
void CGraphe::GRASupprimerArc(CArc ** ARCarc)
{
	unsigned int uiNumSource = 0, uiNumDestination = 0;
	CSommet * SOMSource = nullptr, * SOMDestination = nullptr;
	CArc * ARCarc = nullptr;

	if(ARCarc == nullptr && ARCarc[0] == nullptr && ARCarc[1] == nullptr)
		throw CException(ERREURARGS, "Erreur l'argument n'est pas correcte");

	uiNumSource = ARCarc[0]->ARCGetDestination;
	uiNumDestination = ARCarc[1]->ARCGetDestination;


	// Rercherche et affectation des sommets
	SOMSource = GRATrouverSommet(uiNumSource);
	if(SOMSource == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur sommet non trouv�");

	SOMDestination = GRATrouverSommet(uiNumDestination);
	if(SOMDestination == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur sommet non trouv�");

	// Suppression des informations de l'arc dans le sommet source en question
	ARCarc = GRATrouverArc(SOMSource->SOMGetListArcPartant, SOMDestination);
	if(ARCarc == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur arc non trouv�");

	delete[] ARCarc;

	// Suppression des informations de l'arc dans le sommet destination en question
	ARCarc = GRATrouverArc(SOMDestination->SOMGetListArcPartant, SOMDestination);
	if(ARCarc == nullptr)
		throw CException(ECHECNONTROUVE, "Erreur arc non trouv�");

	delete[] ARCarc;
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
}

/*****************************
Methode : Afficher Arc
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : affichage du graphe
Entraine : affichage du graphe dans la console
*****************************/
void CGraphe::GRAAfficherGraphe()
{

}

/*****************************
Methode : Trouver Sommet
******************************
<<<<<<< HEAD
Entr�e : n�ant
Necessit� : n�ant
Sortie : liste de sommets trouv�s
Entraine : cherche et renvoi la liste des sommets trouv�s
*****************************/
CSommet * CGraphe::GRATrouverSommet(unsigned int uiSommet)
{

=======
Entr�e : unsigned int uiSommet
Necessit� : n�ant
Sortie : CSommet * 
Entraine : cherche et renvoi le sommet
*****************************/
CSommet * CGraphe::GRATrouverSommet(unsigned int uiSommet)
{
	for(unsigned int uiBoucleSommet = 0 ; uiBoucleSommet < uiGRANbSommets ; uiBoucleSommet++) {
		if(ppqGRASommets[uiBoucleSommet]->SOMGetNum == uiSommet)
			return ppqGRASommets[uiBoucleSommet];

		uiBoucleSommet++;
	}

	return nullptr;
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
}

/*****************************
Methode : Trouver Arc
******************************
<<<<<<< HEAD
Entr�e : n�ant
Necessit� : n�ant
Sortie : liste d'arcs trouv�s
Entraine : cherche et renvoi la liste des arcs trouv�s
*****************************/
CArc ** CGraphe::GRATrouverArc(unsigned int uiDestination)
{

}
=======
Entr�e : CSommet * SOMSource, CSommet * SOMDestination
Necessit� : n�ant
Sortie : CArc **
Entraine : cherche et renvoi l'arc
*****************************/
CArc ** CGraphe::GRATrouverArc(CSommet * SOMSource, CSommet * SOMDestination)
{
	CArc * ARCArcActuelArrivant = nullptr, * ARCArcActuelPartant = nullptr;
	CArc ** ARCSourceDestination = nullptr;

	for(unsigned int uiBoucleSommet = 0 ; uiBoucleSommet < uiGRANbSommets ; uiBoucleSommet++) {
		for(unsigned int uiBoucleArcs = 0 ; uiBoucleArcs < uiGRANbArcs ; uiBoucleArcs++) {
			
			ARCArcActuelArrivant = ppqGRASommets[uiBoucleSommet]->SOMGetListArcArrivant[uiBoucleArcs];
			ARCArcActuelPartant = ppqGRASommets[uiBoucleSommet]->SOMGetListArcPartant[uiBoucleArcs];
			
			if(ARCArcActuelArrivant->ARCGetDestination ==  SOMSource->SOMGetNum && ARCArcActuelPartant->ARCGetDestination == SOMDestination->SOMGetNum) {
				ARCSourceDestination = (CArc **)malloc(sizeof(CArc *) * 2);
				
				if(ARCSourceDestination == nullptr)
					throw CException(ECHECALLOCATION, "Echec de l'allocation");

				ARCSourceDestination[0] = ARCArcActuelArrivant;
				ARCSourceDestination[1]= ARCArcActuelPartant;

				return ARCSourceDestination;
			}

			uiBoucleArcs++;
		}

		uiBoucleSommet++;
	}
	
	return ARCSourceDestination;
}
>>>>>>> a20c00fa848d3e97a3e3e38f13d43131a1031984
