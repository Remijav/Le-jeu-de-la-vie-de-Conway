/*
    Ce programme est écrit en C++14
    Il implémente le jeu de la vie de Conway
    A éxécuter dans un terminal
    Il faut appuyer sur Entrée pour faire évoluer la grille
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "grille.hh"
#include "grille.cc"

int main()
{
    unsigned int _colonnes(20), _lignes(20);

    std::cout << "Jeu de la vie de Conway : " << std::endl;
    std::cout << "Le jeu génère des structures aléatoires sur une grille de taille " << _colonnes << " * " << _lignes << "." << std::endl;
    std::cout << "Ces structures peuvent être : un oscillateurligne, une floraison, un planeur, un oscillateurcroix." << std::endl;
    std::cout << "Appuyez sur entrée pour démarrer le programme et afficher la grille puis appuyez sur entrée pour la faire évoluer et l'afficher à nouveau." << std::endl;
    std::cout << "Pour arrêter le programme, entrez 0." << std::endl << std::endl;

    std::string str; // Cette variable servira pour démarrer le programme puis faire évoluer la grille quand l'utilisateur saisir Entrée
    std::getline(std::cin, str);
    if(str == "0") return 0;

    grille G(_colonnes,_lignes); // On initialise une grille de taille 20*20

    // On ajoute une structure de chaque type à des coordonnées aléatoires sur la grille
    srand(time(NULL));
    unsigned int x,y;

    x = (rand()%_colonnes);
    y = (rand()%_lignes);
    G.ajouterStructure(structure::oscillateurLigne,x,y);

    x = (rand()%_colonnes);
    y = (rand()%_lignes);
    G.ajouterStructure(structure::floraison,x,y);

    x = (rand()%_colonnes);
    y = (rand()%_lignes);
    G.ajouterStructure(structure::planeur,x,y);

    x = (rand()%_colonnes);
    y = (rand()%_lignes);
    G.ajouterStructure(structure::oscillateurCroix,x,y);

    G.afficher(); // On affiche l'état de départ de la grille

    /*
        La boucle while permet à la grille d'évoluer selon les règles définies
        L'évolution a lieu à chaque fois que l'utilisateur tape Entrée
        Pour arrêter la boucle, l'utilisateur doit saisir "0"
    */
    while(1){
        std::getline(std::cin, str);
        if(str == "0") break;
        G.evolution(G);
        G.afficher();
    }
}
