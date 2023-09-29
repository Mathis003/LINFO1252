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