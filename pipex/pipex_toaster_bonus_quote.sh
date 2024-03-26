# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_toaster_bonus_quote.sh                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 21:15:42 by svogrig           #+#    #+#              #
#    Updated: 2024/03/26 19:52:52 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


l1="================================================================================================"
l2="---------------------------------------------------------------------------------------\n"
GREEN="\033[38;2;57;181;74m"
RED="\033[38;2;222;56;43m"
BLUE="\033[38;2;34;183;235m"
YELLOW="\033[38;2;255;176;0m"
PURPLE="\033[38;2;255;105;180m"
WHITE="\033[1;37m"
RESET="\033[0m"

printf "$RED$l1\n\n"
printf " ██████╗ ██╗██████╗ ██████╗██╗  ██╗    ████████╗ █████╗  ████╗ ██████╗████████╗██████╗██████╗\n"
printf " ██╔══██╗██║██╔══██╗██╔═══╝╚██╗██╔╝       ██╔══╝██╔══██╗██╔═██╗██╔═══╝   ██╔══╝██╔═══╝██╔══██╗\n"
printf " ██████╔╝██║██████╔╝█████╗  ╚███╔╝        ██║   ██║  ██║██████║██████╗   ██║   █████╗ ██████╔╝\n"
printf " ██╔═══╝ ██║██╔═══╝ ██╔══╝  ██╔██╗        ██║   ██║  ██║██╔═██║╚═══██║   ██║   ██╔══╝ ██╔══██╗\n"
printf " ██║     ██║██║     ██████╗██╔╝ ██╗       ██║    █████╔╝██║ ██║██████║   ██║   ██████╗██║   ██╗\n"
printf " ╚═╝     ╚═╝╚═╝     ╚═════╝╚═╝  ╚═╝        ╚╝    ╚════╝  ╚╝  ╚╝╚═════╝    ╚╝   ╚═════╝╚═╝   ╚═╝\n"
printf "\n                                   Bonus quotes\n"
printf "\n$l1$RESET\n"

printresult () {
	different=`diff out_pipex out_bash`
	if [ "$different" = "" ] && [ "$1" = "$2" ] 
		then
    	printf "${GREEN}[OK]${RESET}\n"
	else
    	printf "${RED}[KO]${RESET}\n"
		if [ "$$different" != "" ]
			then
			printf "outfile pipex: ${RED}"
			cat out_pipex
			printf "${RESET}outfile bash : ${GREEN}"
			cat out_bash
			printf "${RESET}"
		fi
		if [ "$1" != "$2" ]
			then
			printf "exitcode pipex: ${RED}$1${RESET}\n"
			printf "exitcode bash : ${GREEN}$2${RESET}\n"
		fi
	fi
	if [ -s outerr_pipex ]
		then
		printf "${YELLOW}------------------- pipex error:${RESET}\n"
		cat outerr_pipex
		rm outerr_pipex
		touch outerr_pipex
	fi
	if [ -s outerr_bash ]
		then
		printf "${YELLOW}------------------- bash error:${RESET}\n"
		cut -d':' -f 3- outerr_bash
		rm outerr_bash
		touch outerr_bash
	fi
	rm out_pipex
	touch out_pipex
	rm out_bash
	touch out_bash

}

echo "#include <stdio.h>" > printcoucou.c
printf 'int main(void){printf("coucou\\n");return (0);}' >> printcoucou.c
clang printcoucou.c -o printcoucou
cp printcoucou 'print coucou'

printf > infile "Hello World!\nHello World!\n"
touch noperm
chmod 000 noperm
if [ -f out_pipex ]
	then
	rm out_pipex
fi
touch out_pipex
if [ -f out_bash ]
	then
	rm out_bash
fi
touch out_bash
if [ -f outerr_pipex ]
	then
	rm outerr_pipex
fi
touch outerr_pipex
if [ -f outerr_bash ]
	then
	rm outerr_bash
fi
touch outerr_bash

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 1${RESET}"
printf "${WHITE} < infile echo 'Bonjour le monde' | wc | cat > outfile                            ${RESET}"
./pipex infile "echo 'Bonjour le monde'" wc cat out_pipex
EXITCODE_PIPEX=$?
< infile echo 'Bonjour le monde' | wc | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 2${RESET}"
printf "${WHITE} < infile cat | echo 'Bonjour le monde' | wc | cat > outfile                      ${RESET}"
./pipex infile cat "echo 'Bonjour le monde'" wc cat out_pipex
EXITCODE_PIPEX=$?
< infile cat | echo 'Bonjour le monde' | wc | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 3${RESET}"
printf "${WHITE} < infile cat | cat | echo 'Bonjour le monde' > outfile                           ${RESET}"
./pipex infile cat cat "echo 'Bonjour le monde'" out_pipex
EXITCODE_PIPEX=$?
< infile cat | cat | echo 'Bonjour le monde' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 4${RESET}"
printf "${WHITE} < infile grep Hello | awk '{count++} END {print count}' | cat > outfile          ${RESET}"
./pipex infile "grep Hello" "awk '{count++} END {print count}'" cat out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 5${RESET}"
printf "${WHITE} < infile grep Hello | awk \"{count++} END {print count}\" > outfile                ${RESET}"
./pipex infile "grep Hello" "awk \"{count++} END {print count}\"" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk "{count++} END {print count}" > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "\n$YELLOW$l1$RESET\n"

rm infile
rm out_pipex
rm out_bash
rm outerr_pipex
rm outerr_bash
rm -f noperm
rm printcoucou.c
rm printcoucou
rm 'print coucou'