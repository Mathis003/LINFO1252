# Dans cet exercice, vous allez pratiquer la création de script bash.
# Le but de cet exercice est de produire un script bash capable de créer une archive propre et conforme à partir d'un projet donné.
# Ce script prend en argument un chemin vers un dossier de code source à archiver, p. ex. ~/Documents/mon_projet.

# L'exécution du script bash se déroule comme suit:

    # Si le dossier contenant le code contient également un fichier Makefile, le script utilise make clean pour le nettoyer.

    # Le script crée un fichier manifest.txt dans le répertoire courant. Ce fichier se compose de plusieurs lignes et adhère au format suivant:
        # La première ligne contient la date, avec une précision à la seconde, de génération de ce fichier au format RFC 3339. L'utilitaire date vous permet de formater de telles dates.
        # La deuxième ligne contient le nombre total de lignes se trouvant dans les fichiers source du dossier. Il ne faut considérer que les fichiers C (.h et .c) ainsi que les fichiers Python (.py).
        # Enfin, la troisième ligne contient l'identifiant UNIX et le nom de la machine hôte aillant exécuté le script. Ces deux informations doivent être séparées par le caractère @. Il existe des utilitaires à cet effet.

# Le script crée une archive au format tar avec compression xz dans dossier courant, contenant le dossier de code source et le fichier manifest.txt. Cette archive porte le nom du dossier et l'extension .tar.xz.
# Le script supprime le fichier manifest.txt dans le dossier courant.

# Exemple de fichier manifest.txt:
    # 2020-09-03 11:06:07+02:00
    # 4258
    # pirauxma@yoda.info.ucl.ac.be

# Une archive vous permettant de tester votre script sur votre machine se trouve dans ./code_source.


#!/usr/bin/bash

# Vérifie qu'il n'y ai qu'un seul argument passé en commande
if [ "$#" -ne 1 ]; then
    echo "Need one argument : <PATH_SOURCE_FOLDER>"
    exit 1
fi

CURRENT_DIRECTORY=$(pwd)
PATH_SOURCE_FOLDER=$1

# Exécute 'make clean' si il y a un Makefile dans le dossier source
if [ -e ${PATH_SOURCE_FOLDER}/Makefile ]; then
    $(cd ${PATH_SOURCE_FOLDER} && make clean && cd ${CURRENT_DIRECTORY})
fi

# Initialise toutes les variables nécessaires
DATE=$(date --rfc-3339=seconds)
MANIFEST_FILE="manifest.txt"
ARCHIVE_NAME=${PATH_SOURCE_FOLDER}.tar.xz
USER_ID=$(id -un)
HOSTNAME=$(hostname)

# -type f : précise que l'on cherche uniquement des fichiers
# -name "*.[ext]" : précise que l'on cherche l'extension [ext] dans le nom du fichier
# -o : opérateur logique signifiant le OU
# -exec cat {} : permet de concaténer toute la liste des fichiers trouvés
# awk '{$1=$1};1' : permet d'enlever les espaces inutile avant le nombre
NUMBER_LINES=$(find  ${PATH_SOURCE_FOLDER} -type f \( -name "*.py" -o -name "*.h" -o -name "*.c" \) -exec cat {} + | wc -l | awk '{$1=$1};1')

# Remplit le fichier avec les trois informations
echo ${DATE} > ${MANIFEST_FILE}
echo ${NUMBER_LINES} >> ${MANIFEST_FILE}
echo ${USER_ID}@${HOSTNAME} >> ${MANIFEST_FILE}

# Créer l'archive contenant le dossier source et le fichier manifest.txt (-J car archive .tar.xz)
tar -cvJf ${ARCHIVE_NAME} ${MANIFEST_FILE} ${PATH_SOURCE_FOLDER}

# Supprime le fichier manifest.txt du répértoire courant
rm ${MANIFEST_FILE}