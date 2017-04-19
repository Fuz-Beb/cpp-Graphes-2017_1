#include "CArc.h"

/*****************************
Constructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CArc::CArc() 
{
	uiARCDestination = NULL;
}

/*****************************
Constructeur de recopie
******************************
Entr�e : unsigned int uiDestination
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en param�tre est recopi� et initialis� dans un nouvel objet
*****************************/
CArc::CArc(CArc & arc)
{
	uiARCDestination = arc.uiARCDestination;
}

/*****************************
Constructeur de confort
******************************
Entr�e : unsigned int uiDestination
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet en cours est initialis�
*****************************/
CArc::CArc(unsigned int uiNumSommet)
{
	uiARCDestination = uiNumSommet;
}

/*****************************
Destructeur par d�faut
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : n�ant
Entraine : l'objet est d�truit
*****************************/
CArc::~CArc()
{
}

/*****************************
Methode : Lire Destination
******************************
Entr�e : n�ant
Necessit� : n�ant
Sortie : unsigned int uiDestination
Entraine : retourne le chemin de l'attribut
*****************************/
unsigned int CArc::ARCGetDestination()
{
	return uiARCDestination;
}

/*****************************
Methode : Modifier Destination
******************************
Entr�e : unsigned int uiDestination
Necessit� : n�ant
Sortie : n�ant
Entraine : affecte le param�tre � l'attribut
*****************************/
void CArc::ARCSetDestination(unsigned int uiDestination) 
{
	uiARCDestination = uiDestination;
}