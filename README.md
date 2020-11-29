# Résumé

Le projet de compilation a pour but la réalisation d'un compilateur d'un mini langage appelé pour l'occasion myC vers du code C à 3 adresses. Le langage source proposé, un mini langage C, devra donc être compilé en C à 3 adresses.

Il a été réalisé par Reda CHAGUER et Houssam BAHHOU, élèves à l'Enseirb-Matmeca en deuxième année informatique. (Groupe 1)

# Pré-requis

Afin de faire fonctionner ce projet vous devez posséder les packages suivants :
- make
- gcc
- flex
- bison

# Dossiers et contenu

Le projet s'organise de la sorte :
  - `src/` : sources générant le compilateur `lang`
    * `Attribute.c` et `Attribute.h` : permet de gérer les attributs dans l'analyse de types et noms.
    * `Table_des_chaines.c` et `Table_des_chaines.h` : permet de récupérer les noms lors de l'analyse de noms
    * `Table_des_symboles.c` et `Table_des_symboles.h` : permet de générer des éléments dans la table des symboles regroupant toutes les variables attributs créés et garder en mémoire leur valeur, type, ... sous forme de liste chaînée
    * `lang.y` : syntaxe du compilateur `lang`
    * `lang.l` : lexique de compilateur `lang`
  - `tst/` : fichiers tests du compilateur `lang`
    * `funct_without_params.myc` : fichier pour tester la définition et l'appel aux fonctions sans paramètres
    * `func_with_params.myc` : fichier pour tester la définition et l'appel aux fonctions avec paramètres
    * `fibo.myc` : fichier pour tester la définition et l'appel aux fonctions récursives
    * `if_else.myc / while.myc / while_if.myc`  : fichiers pour tester les structures de contrôles classiques (conditionelles et boucles)
    * `z_affect_pointer.myc` : fichier pour tester l'affectation pointeur (Le code est correct mais le grammaire ne permet pas d'initialiser des pointeurs, on obtient un fichier.c qui donne un seg fault pendant son éxecution ce qui est normal), le répértoire  `/affect_pointer_avec_malloc` contient les fichiers `.c/h` corréspendants avec une intialisation avec malloc. 
    * `MOINS_pointer.myc / PLUS_pointer.myc` : fichier pour tester les opérations arithmétiques sur les pointeurs
    * A l'intérieur de ces fichiers on teste aussi le mécanisme de déclarations explicite des variables, les expresssions arithmétiques arbitraires de type calculatrice et lectures ou écritures mémoires via des affectations avec variables utilisateurs
  - `Makefile`
  - `compil.sh` : script shell permettant de générer le compilateur s'il n'éxiste pas et compiler le fichier `.myc` donné en argument en `.c` et `.h`
  - `preC.sh` : script shell permettant de générer le code précompilé. (lang)
  - `README.md`

# Compilation et exécution

Afin de pouvoir compiler notre programme et l'utiliser, plusieurs règles du `Makefile` peuvent être utiles :
  - `make clean` : permet de nettoyer avant de compiler tous les fichiers produits durant la compilation
  - `make` : compiler tous les sources permettant de créer le compilateur `lang`
  - `make test` : compiler les fichier `tst/*.myc` avec notre compilateur et générer les fichiers `.c` et `.h` correspondants, et ensuite éxecuter tous les fichiers `.c` générés. 
  - `make working_affec` : permet de compiler les fichiers `.c/h` contenus dans le répértoire `/affect_pointer_avec_malloc`  
Cependant, nous avons mis en place un script permettant d'automatiser toutes ces étapes, le script `compil.sh`. En exécutant ce script avec la commande `./compil.sh <fichier.myc>`, il va effectuer les actions suivantes :
  - compiler les sources avec `make ` si elles ne sont pas déjà compilées 
  - vérifier que le dossier `build` a bien été crée
  - compiler avec notre compilateur `lang` le fichier donné en paramètre
  - compiler avec `gcc` les fichiers `.h` et `.c` qui ont été générés par notre compilateur `lang`

Si on veut forcer la recompilation des fichiers sources, on peut utiliser l'option `-r` avec le script `preC.sh`.


# Travail demandé

Le projet devra assurer :
  - l'analyse des noms : les variables (et fonctions) utilisées sont-elles déclarées
  - l'analyse des types : les opérations effectués sont-elles bien typées
  - la production de code à trois addresses

Le compilateur `lang` produit vise à couvrir quelques éléments clès de la compilation. Il comprend notamment:
  - un mécanisme de déclarations explicites de variables
  - des expressions arithmétiques arbitraire de type calculatrice
  - des lectures ou écritures mémoires via des affectations avec variable utilisateur
  - des structures de contrôles classiques (conditionelles et boucles)
  - un mécanisme de typage comprenant notamment `int` et `int *`
  - des lectures ou écritures mémoires via des pointeurs
  - définitions et appels de fonctions récursives
  - `N.B.` une pile sera utilisée pour gérer les variables locales et les arguments des fonctions.

# Travail effectué

Nous avons réussi à effectuer toutes les fonctionnalités du projet:
  - un mécanisme de déclarations explicites de variables **FONCTIONNEL**
  - des expressions arithmétiques arbitraire de type calculatrice **FONCTIONNEL**
  - des lectures ou écritures mémoires via des affectations avec variable utilisateur ou pointeurs **FONCTIONNEL**
  - des structures de contrôles classiques (conditionelles et boucles) **FONCTIONNEL**
  - un mécanisme de typage comprenant notamment `int` et `int *` **FONCTIONNEL**
  - des lectures ou écritures mémoires via des pointeurs **FONCTIONNEL**
  - définitions et appels de fonctions récursives **FONCTIONNEL**
  - `une pile pour la géstion des variables locales et les arguments des fonctions. **FONCTIONNEL**


