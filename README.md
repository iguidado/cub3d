## Description
Cub3D est un projet de l'école 42 qui consiste à créer un moteur de jeu 3D basique en utilisant la technique de raycasting. Le projet s'inspire du jeu Wolfenstein 3D et a pour objectif de renforcer les compétences en programmation graphique, en gestion des événements, et en mathématiques appliquées à la 3D.

## Fonctionnalités
- Rendu 3D basé sur le raycasting
- Navigation à la première personne
- Gestion des collisions avec les murs
- Affichage des textures sur les murs
- Support des déplacements (avant, arrière, gauche, droite) et des rotations de la caméra

## Technologies Utilisées
- Langage : C
- Bibliothèque graphique : MiniLibX
- OS : Linux (peut fonctionner sur macOS avec des modifications mineures)
- Compilation : Makefile

## Installation et Exécution

### Prérequis
- Avoir `gcc` et `make` installés
- Installer la bibliothèque MiniLibX (instructions spécifiques à votre OS)

### Instructions
Clonez le repository :
```bash
git clone https://github.com/iguidado/cub3d.git
cd cub3d
```

Installer les prerequis et clonez le repository:
```bash
make install && make
```

## Exemples d'Utilisation
### Contrôle du Jeu
- *W *: Avancer
- *S *: Reculer
- *A *: Déplacer à gauche
- *D *: Déplacer à droite
- *Flèche Gauche *: Tourner la caméra à gauche
- *Flèche Droite *: Tourner la caméra à droite
- *ESC *: Quitter le jeu
