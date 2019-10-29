#include <iostream>
#include <vector>
#include "grille.hh"

// Implémentation des méthodes de la classe grille

// Constructeur :
grille::grille(coordonnee colonnes, coordonnee lignes): _colonnes(colonnes), _lignes(lignes) {
    initialiser();
}


// Initialiser : redimensionne la _matrice et initialise une grille en définissant toutes les cellules à l'état "mort"
void grille::initialiser(){
    _matrice.resize(_matrice.size() + _colonnes*_lignes);
    for(unsigned int i = 0; i<_matrice.size(); i++){
            _matrice[i] = etatCellule::mort;
    }
}

// Défini l'état de chaque celulles sur "mort"
void grille::vider(){
    for(auto &cellule : _matrice)
        cellule = etatCellule::mort;
}


// Retourne l'indice de la cellule dans la matrice si celle-ci est contenu dedans.
coordonnee grille::numCellule(coordonnee colonne, coordonnee ligne){
    if (colonne <= _colonnes && ligne <= _lignes) return colonne+ligne*_colonnes;
    else return -1;
}


// Retourne True si la cellule passée en paramètre est vivnte, False sinon
bool grille::vivante(coordonnee colonne, coordonnee ligne){
    if(_matrice[numCellule(colonne,ligne)] == etatCellule::vivant) return true;
    else return false;
}


// Génère une cellule vivante aux coordonnées passées en paramètre
void grille::generer(coordonnee colonne, coordonnee ligne){
    // On vérifie que la cellule passée en paramètre est bien dans la grille

    if(colonne < _colonnes && ligne < _lignes && colonne > 0 && ligne > 0)
        _matrice[numCellule(colonne,ligne)] = etatCellule::vivant;
}

// Tue une cellule située aux coordonnées passées en paramètre
void grille::tuer(coordonnee colonne, coordonnee ligne){
    _matrice[numCellule(colonne,ligne)] = etatCellule::mort;
}


/*
    Affiche la grille
    Les cellules vivantes sont représentées par : *
    Les cellules mortes sont représentées par : -
*/
void grille::afficher(){
    for(coordonnee i = 0; i<_colonnes; i++){
        for(coordonnee j = 0; j < _lignes; j++){
          //  std::cout << j << " " ;
            if(vivante(i,j)) std::cout << "*";
            else std::cout << "-";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/*
    Ajoute une structure passée en paramètre à une celulle dont les coordonnées sont passées en paramètre
    Conformément à l'affichage, le schéma d'un OscilateurLigne est :
    ***

    Conformément à l'affichage, le schéma d'une floraison est :
    -***
    * * *
     ***

    Conformément à l'affichage, le schéma d'un planeur est :
    ***
      *
     *  
    
    Conformément à l'affichage, le schéma d'un OscilateurLigneCroix est :
    -*
    ***
     *
    
    Le couple de coordonnées passées en paramètre correspond à la cellule la plus à gauche de la première ligne du schéma de la structure
*/
void grille::ajouterStructure(structure structur, coordonnee colonne, coordonnee ligne){
    switch(structur) {
        // Ajoute une structure de type OscilateurLigne
        case structure::oscillateurLigne:
            generer(colonne,ligne);
            generer(colonne,ligne+1);
            generer(colonne,ligne+2);
            break;

        // Ajoute une structure de type floraison
        case structure::floraison:
            tuer(colonne,ligne);
            generer(colonne,ligne+1);
            generer(colonne,ligne+2);
            generer(colonne,ligne+3);
            generer(colonne+1,ligne);
            generer(colonne+1,ligne+2);
            generer(colonne+1,ligne+4);
            generer(colonne+2,ligne+1);
            generer(colonne+2,ligne+2);
            generer(colonne+2,ligne+3);
            break;

        // Ajoute une structure de type planeur
        case structure::planeur:
            generer(colonne,ligne);
            generer(colonne,ligne+1);
            generer(colonne,ligne+2);
            generer(colonne+1,ligne+2);
            generer(colonne+2,ligne+1);
            break;

        // Ajoute une structure de type OscilateurCroix
        case structure::oscillateurCroix:
            tuer(colonne,ligne);
            generer(colonne,ligne+1);
            generer(colonne+1,ligne);
            generer(colonne+1,ligne+1);
            generer(colonne+1,ligne+2);
            generer(colonne+2,ligne+1);
            break;
    }
}



// Compte le nombre de cellules vivantes dans les 8 cases entourant la case de la cellule passée en paramètre
unsigned int grille::vivantes(coordonnee colonne, coordonnee ligne){
    // Cas où la cellule (colonne,ligne) n'appartient pas à la grille
    if(colonne > _colonnes || ligne > _lignes || colonne < 0 || ligne < 0) return 0;
    // Cas où la cellule (colonne,ligne) appartient à la grille
    else{
        unsigned int nbCellulesVivantes = 0;
        for (coordonnee i = -1; i <= 1; ++i) {
            for (coordonnee j = -1; j <= 1; ++j) {
                if (colonne != colonne+i || ligne != ligne+j){
                    // Si la cellule testée est égale à la cellule passe en paremètre, alors on ne la teste pas car on ne compte que les cellules vivantes voisines
                    if(vivante(colonne+i, ligne+j))
                        ++nbCellulesVivantes;
                }
            }
        }
        return nbCellulesVivantes;
    }
}



/*
    Calcule l'évolution de la grille sur laquelle la méthode est appelée dans la grille passée en paramètre
    1) Une cellule morte prend vie si elle est entourée de 3 cellules vivantes (exactement).
    2) Une cellule vivante meurt d’isolement si elle est entourée de 0 ou 1 cellule vivante, et meurt d’étouffement si elle est entourée de 4 (ou plus) cellules vivantes.
*/
grille& grille::evolution(grille & G) {
    for(coordonnee col = 0; col<_colonnes; ++col){
        for(coordonnee lig = 0; lig<_lignes; ++lig){
            unsigned int nbVivantes = vivantes(col,lig);

            if(vivante(col,lig)){ // Si la cellule testée est vivante
                // On test si elle est entourée de 0 ou 1 cellul vivante ou de plus de 4
                // Si oui, on la définit comme "viant" dans G, sinon on la définit comme "mort" dans G
                if(nbVivantes <= 1 || nbVivantes >= 4) G.tuer(col,lig);
                else G.generer(col,lig);
            }
            else{ // Si la cellule testée est morte
                // On test si elle est entourée de 3 cellules vivantes
                // Si oui, alors elle prend vie, sinon il ne se passe rien
                if(nbVivantes == 3) G.generer(col,lig);
            }
        }
    }
    return G;
}
