R-Type
======

R-Type is a third year EPITECH project. It's a Shoot'Em Up kind of game inspired by R-type obviously, plus online gaming.

A Team Bicycle Project (c)
- Lois Burg
- Thibault Carpentier
- Thomas Duplomb
- Geoffroy Lafontaine
- Romain Sylvian

Compiler sur windows
--------------------

1. Telechargez les sources de la SFML [ici](https://github.com/LaurentGomila/SFML/tarball/master). Extrayez-les ou vous
voulez, mais sachez qu'elles vont devoir y rester.
Suivez [ce tuto](http://www.sfml-dev.org/tutorials/2.0/compile-with-cmake.php) pour compiler les sources. Pensez a
compiler en Release ET aussi en Debug. Vous devriez avoir maintenant dans le dossier de build un dossier `./lib/Release/`
et un `./lib/Debug/`. Prenez tout les `.lib` dans ces dossiers et balancez les dans 
`C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\lib` ainsi que a la racine du dossier de la SFML dans un dossier
`lib/`. Prenez aussi tout les `.dll` des dossiers Release/Debug pour le mettre dans un dossier `bin/` a la racine du projet
SFML aussi.

2. Avec CMake-gui, ajoutez le dossier ou vous avez cloner R-Type. Pour le repertoire de build, le mieux est d'en creer
un dedie dans le dossier du clone.
Ajoutez une variable via CMake-GUI nomee `SFML_ROOT` qui contient le path vers le dossier de la SFML. Apres : Configure+Generate.
![ScreenShot](https://github.com/tomahh/R-Type/raw/master/CMakeRType.png)

3. Une solution visual studio doit maintenant se trouver dans le votre dossier de build. Ouvrez la, et normalement, ca
**compile**. Faites une compile en Debug et une autre en Release, vous devriez maintenant avoir a la racine du projet un
dossier `./bin/` avec `Release` et `Debug` dedans. Collez-y respectivement les `.dll` qui se trouvent dans `*dossier-de-build-sfml*/lib/Release` et `*dossier-de-build-sfml*/lib/Debug`.

ET VOILA, C'EST BLEU !
======================
