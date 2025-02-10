# Bloom
A distributed version control system. An alternative to git and github

1. [Objectif](#Objectif)
    - [Objectif personnel](#Objectif-personnel)
    - [Objectif du projet](#Objectif-du-projet)
2. [Exigence fonctionnel](#Exigence-fonctionnel)
3. [Ssytèmes](#Systèmes)

## Objectif

### Objectif personel

#### Aprentissage

Git est un outil utilisee à travers l’industrie, nous pensons qu’une bonne manière de comprendre cet outil est de la recreer. 
À travers ce projet, nous esperons apprendre et integrer plusieurs nouveaux concepts qui dans autre projet ne pourrait pas etre reproduit.  

De nos recherches nous pensons que ce projets necissitent 3 structures de donne : 
- Hash 
- Dictionnaire (hash set) 
- Abre (tree) plus precisement un Hash tree

#### Travail d'équipe

- Le travaille d’equipe pour un projet complex requiert de l’organisation et de la communication. 
- Devoir ecrire du bon code et lire du bon code, pour assurer une bonne comprehension de nos intentions.

### Objectif du projet

#### Système VCS non distrubué (Phase 1)

Creation d’un VCS personnelle :
- Creation du sous-systeme de hashage 
- Creation d’un hash tree pour gerer le versionnage 

Bonus :
* Permettre a l’utilisateur de decider quelle commit deviens le nouveau root du projet.

#### Système VCS distribué (Phase 2)

Ajout de fonctionnalite pour permettre une distribution. 
- Site internet pour permettre le partage de se fichier 
- Base de donne pour enregistrer les fichiers. 
- Creation d’un ui intuitif 

#### Défis 

1. Alors que nous implimentons des systèmes comme un CAS pour ameliorer la vitesse et reduire la mémoire requit. 
2. Nous nous obligons de créer un produit modulaire, afin de pouvoir rajouter des features dans le futur.

--------------------------------------------------------------------------------------------------------------------

## Exigence fonctionnelle

## Cas d'usage

Enregistrer des versions d’un projet peut s’averer lourde. Et imaginez si nous allons dans la mauvaise direction, 
nous voudrions reculer a une version precedente. Mon collegue et moi creeons un logiciel pour adresser ces deux problemes. 

Fonctionnalités :
|Enregistrement dans un CAS, afin de juste enregistrer les modifications necessaires.|
| :--------------------------------------------------------------------------------: |
 
|Avoir un système de versionnage afin de pouvoir reculer dans des anciennes versions.|
| :--------------------------------------------------------------------------------: |
 

> __Un produit alternatif :__  
> Git l’outil utiliser par github concu et coder en seulement 2 semaines par le seul et unique ***Linus Thorvald*** (createur de linux). 
> L’outil auras 2 grande fonctionnalite commit et revert. 

## Systèmes

### Enregistrement

La manière que nous representerons le CAS[^CAS] (content adressable storage) seras a travers un hash tree (AKA merkle tree).  

Avantage : 
- Chaque node du hash tree est unique (c’est un hash de leur contenu) 
- Les donner etant stocker sous leur hash garanti l’immuabilite 
- Une Deduplication auras lieu car les fichiers qui contiennent le meme contenu auront le meme hash.
  En consequence il n’aura aucun stockage double.

![Diagrame de classe du hashset](./doc/diagrams/images/enregistrements.jpeg)

### Versionnage

versionnage 

On garde les pointeurs a des commits dans un json ou xml ou text file donc nous pourons iterer a travers les commits. 

### Bouturage

Pointe vers le root et tu créer ta propre version 

## Technologie et outils

### Language

  __PHASE 1__

L'implementation se fera en C/C++. Nous voulons avoir le plus de contrôle afin d’optimiser la performance.  
Nous utiliserons la lib openssl pour utiliser SHA-1 afin de hasher notre contenu.  
Tout les autres fonctionnalités seront implémenter par nous afin de maximer notre apprentissage.

  __PHASE 2__

Cette phase est optionionnel et requiert l'implémentation de peu de structure.  
Le backend de cette plateforme sera implémenté en GO, en utilisant les librairies standard
net/http et database/sql pour afin d'implémenter les le serveur HTTP et l'accès à la base de donnée.

La base de donnée utilisera le service posgresSQL.

### Plan de développement 

   __Partie 1__

1. Construction du diagramme de classe. 
2. Construction du diagramme de usecase 
3. Construction de diagramme de sequence 
4. Conception de comment on call les fonctionnalite dans le cli 

  __Partie 2__

1. Creation du système CAS (hashtree, documentReader, SHA-1) 
2. Implimentation du commit(plant) 
3. Implimentation du revert(regrow) 
4. Implimentation du branch(bouturage) 

  __Partie 3__

1. Creation du CLI  

  __Partie 4__

1. unit testing de chacune des fonctions 

--------------------------------------------------------------------------------------------------
**[Réference](./doc/path/to/refeence.md)**

[^CAS]: CAS: Content Adressable Storage
