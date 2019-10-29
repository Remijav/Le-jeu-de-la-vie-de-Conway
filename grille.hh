#ifndef GRILLE_HH
#define GRILLE_HH
#include <vector>

// On utilise un type coordonnee qui est un entier signé pour simplifier le code
using coordonnee = int;

// Type énuméré décrivant l'état d'une cellule
// Une cellule est soit dans l'état "mort" soit dans l'état "vivant"
enum class etatCellule { mort , vivant };

// Type énuméré structure décrivant le nom d'une structure de cellules 
// Les structures existantes du jeu de la vie ne sont pas toutes implémentées dans ce code
enum class structure { oscillateurLigne , floraison , planeur , oscillateurCroix };

/*
    Déclaration de la classe grille
    Une grille est représentée par deux dimensions de type coordonnee: _colonnes et _lignes
    On suppose que l'origine d'une grille est le point de coordonnées (0,0)
    Une grille contient une _matrice de type std::vector<etatCellule> pour représenté l'état des cellules de la grille
    Une grille contient une structure _structure pour permettre d'ajouter des structure de cellules dans la grille
*/

class grille {
private:
    coordonnee _colonnes, _lignes;
    std::vector<etatCellule> _matrice;
    structure _structure;

// Déclaration des méthodes de la classe grille
public:
    // Constructeurs
    grille() = default;
    grille(const grille & ) = default; 
    grille(coordonnee colonnes, coordonnee lignes);

    // Supprime toute les cellules vivantes de la grille
    void vider(); 

    // Retourne l'indice auquel se trouve une cellule dont les coordonnées sont passées en paramètre
    coordonnee numCellule(coordonnee colonne, coordonnee ligne);

    // Vérifie si l'état de la cellule passée en paramètre est "vivant"
    bool vivante(coordonnee colonne , coordonnee ligne);

    // Génère une cellule aux coordonnées passées en paramètre
    void generer(coordonnee colonne, coordonnee ligne);

    // Définit l'état d'une cellule passée en paramètre sur "mort"
    void tuer(coordonnee colonne, coordonnee ligne);

    // Affiche la grille
    void afficher();

    // Initialise la taille de la grille et définit l'état des cellules sur "mort" 
    void initialiser();

    // Ajoute une structure de cellules passée en paramètre à des coordonnées également passées en paramètre à la grille
    void ajouterStructure(structure structur, coordonnee colonne, coordonnee ligne);

    // Compte le nombre de cellules vivantes dans les 8 cases entourant la case de la cellule passée en paramètre
    unsigned int vivantes(coordonnee colonne, coordonnee ligne);

    // Calcule l'évolution de la grille sur laquelle la méthode est appelée
    grille& evolution(grille &);


};










#endif // GRILLE_HH
