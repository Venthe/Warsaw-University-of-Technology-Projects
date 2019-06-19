#!/bin/bash

###############################################################################
# Wykorzystuj�c programy find i sed,
# napisa� skrypt wywo�ywany w nast�puj�cy spos�b:
#
# skrypt  [-cs]  .roz  katalog  wzorzec
# np.:  szukaj  .h  /usr/include  sigaction
#
# Skrypt poszukuje plik�w zwyk�ych o nazwach zawieraj�cych rozszerzenie .roz w ga��zi drzewa katalog�w wskazanej przez katalog (rozszerzenie mo�e mie� dowoln� liczb� znak�w). Skrypt wypisuje na stdout tylko nazw� �cie�kow� ka�dego pliku, zawieraj�cego co najmniej jedn� lini� pasuj�c� do podanego wzorca.
#
# Zrealizowa� nast�puj�ce opcje:
#  -c - skrypt kopiuje do katalogu bie��cego ka�dy plik zawieraj�cy dopasowane linie;
#  -s - skrypt wypisuje na stdout nazw� pliku, a nast�pnie wszystkie dopasowane linie, poprzedzone ich numerami.
#
# Skrypt powinien:
#  - sygnalizowa� b��dy sk�adni (podaj�c poprawn� posta�),
#  - sygnalizowa� u�ycie niepoprawnego argumentu,
#  - sygnalizowa� brak odpowiednich praw dost�pu.
###############################################################################

USAGE() { echo -e "Usage: ${BOLD}$0 [-c] [-s] [-v] .ext directory pattern${NORM}"\\n; exit 1; } # Usage
HELP() { #Help function
  echo -e \\n"Help documentation for ${BOLD}$0.${NORM}"\\n
  echo -e "${REV}Basic usage:${NORM} ${BOLD}$0 .ext directory pattern${NORM}"\\n
  echo "Command line switches are optional. The following switches are recognized."
  echo "${REV}-c${NORM}  --Sets the copy switch ${BOLD}c${NORM}. Script copies to current directory every file with lines that have matched the pattern. Default is ${BOLD}$C_COPY_TO_DIRECTORY${NORM}."
  echo "${REV}-s${NORM}  --Sets the print switch ${BOLD}s${NORM}. Script prints filenames followed by all lines with matched patternms. Default is ${BOLD}$S_PRINT_FILE_AND_LINES${NORM}."
  echo -e "${REV}-h${NORM}  --Displays this help message. No further functions are performed."\\n
  echo -e "Example: ${BOLD}$0 [-c] [-s] .ext directory pattern${NORM}"\\n
  exit 1
}

#Set Variables
EXTENSION= # Set extension to be found
DIRECTORY= # Directory to search in
PATTERN= # Pattern to be matched by sed
FIND_ARRAY=() # Storing a result of a find. Needed for info
C_COPY_TO_DIRECTORY=false # Switches -c
S_PRINT_FILE_AND_LINES=false # Switches -s
DIR=$PWD # Lookup dir

# Set fonts for Help.
# Useful bit of code grabbed from 'net
NORM=$(tput sgr0)
BOLD=$(tput bold)
REV=$(tput smso)

# Check the number of arguments. If none are passed, print help and exit.
if [ $# -eq 0 ]; then HELP; fi

# Getopts
while getopts "csvh" VAR; do
  case $VAR in
    c) C_COPY_TO_DIRECTORY=true ;;
    s) S_PRINT_FILE_AND_LINES=true ;;
    h) HELP ;;
    \?) echo -e "Unrecognized argument"\\n; USAGE ;;
  esac
done; shift $((OPTIND-1)) # Done parsing GETOPTS; Moving to remaining arguments

# Check the number of arguments. If not equal to required 3, print usage and exit.
if [ $# -eq 3 ]; then
  PATTERN=$3
  DIRECTORY=$2
  EXTENSION=$1
else echo "Invalid number of arguments"; USAGE; fi

# Sanity checks of parameters
if ! [ -d $DIRECTORY ]; then echo "$DIRECTORY is not a valid directory!"; exit 1; fi
if ! [ ${EXTENSION:0:1} == '.' ]; then echo "$EXTENSION is not a valid extension!"; exit 1; fi

# Following method used because naiive approach lead to unexpected results with white spaces
while IFS=  read -r -d $'\0'; do FIND_ARRAY+=("$REPLY") ; done < <(find $DIRECTORY -type f -name "*$EXTENSION" -print0)

if [ ${#FIND_ARRAY[@]} -eq 0 ]; then echo "no files found with extension $EXTENSION with pattern $PATTERN"; exit 1
else
  for VAR in "${FIND_ARRAY[@]}"
  do
    if [[ -r ${VAR} ]]; then
	  cat "${VAR}" | sed -n "/${PATTERN}/{q100}"
	  if [ $? -eq 100 ]; then
	    echo "$BOLD${VAR}$NORM"
	    if [ $S_PRINT_FILE_AND_LINES == true ]; then sed -n "/${PATTERN}/{=;p}" "${VAR}" | sed '{N;s/\n/: /}'; echo -e; fi
	    if [ $C_COPY_TO_DIRECTORY == true ]; then cp "${VAR}" "$DIR" ;fi
	  fi
	else echo "You do not have permission to read ${VAR}"
	fi
  done
fi

exit 0