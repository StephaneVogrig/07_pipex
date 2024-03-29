# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_toaster_mandatory.sh                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 19:18:29 by svogrig           #+#    #+#              #
#    Updated: 2024/03/22 02:57:29 by svogrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

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
printf "\n                                   Mandatory\n"
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
printf "${PURPLE}\nTest 01${RESET}"
printf "${WHITE} < infile cat | cat outfile                                                ${RESET}"
./pipex infile cat cat out_pipex
EXITCODE_PIPEX=$?
< infile cat | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 02${RESET}"
printf "${WHITE} < noperm cat | cat > outfile                                              ${RESET}"
2> outerr_pipex ./pipex noperm cat cat out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < noperm cat | 2>> outerr_bash cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 03${RESET}"
printf "${WHITE} < infile cat | cat > noperm                                               ${RESET}"
2> outerr_pipex ./pipex infile cat cat noperm
EXITCODE_PIPEX=$?
2>> outerr_bash < infile cat | 2>> outerr_bash cat > noperm
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 04${RESET}"
printf "${WHITE} < noperm cat | cat > noperm                                               ${RESET}"
2> outerr_pipex ./pipex noperm cat cat noperm
EXITCODE_PIPEX=$?
2>> outerr_bash < noperm cat | 2>> outerr_bash cat > noperm
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 05${RESET}"
printf "${WHITE} < infile ./printcoucou | cat > outfile                                    ${RESET}"
./pipex infile ./printcoucou cat out_pipex
EXITCODE_PIPEX=$?
< infile ./printcoucou | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 06${RESET}"
printf "${WHITE} < infile ./printcoucou | ./printcoucou > outfile                          ${RESET}"
./pipex infile ./printcoucou ./printcoucou out_pipex
EXITCODE_PIPEX=$?
< infile ./printcoucou | ./printcoucou > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 07${RESET}"
printf "${WHITE} < infile ./'print coucou' | cat > outfile                                 ${RESET}"
./pipex infile "./'print coucou'" cat out_pipex
EXITCODE_PIPEX=$?
< infile ./'print coucou' | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 08${RESET}"
printf "${WHITE} < infile cat | wc -cl > outfile                                           ${RESET}"
./pipex infile cat "wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile cat | wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 09${RESET}"
printf "${WHITE} < infile /bin/cat | wc -cl > outfile                                      ${RESET}"
./pipex infile /bin/cat "wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile /bin/cat | wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 10${RESET}"
printf "${WHITE} < infile cat | /bin/wc -cl > outfile                                      ${RESET}"
./pipex infile cat "/bin/wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile cat | /bin/wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 11${RESET}"
printf "${WHITE} < infile /bin/cat | /bin/wc -cl > outfile                                 ${RESET}"
./pipex infile /bin/cat "/bin/wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile /bin/cat | /bin/wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 12${RESET}"
printf "${WHITE} < infile ls -l | wc -cl > outfile                                         ${RESET}"
./pipex infile "ls -l" "wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile ls -l | wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 13${RESET}"
printf "${WHITE} < infile grep Hello | awk '{count++} END {print count}' > outfile         ${RESET}"
./pipex infile "grep Hello" "awk '{count++} END {print count}'" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 14${RESET}"
printf "${WHITE} < infile grep Hello | awk \"{count++} END {print count}\" > outfile         ${RESET}"
./pipex infile "grep Hello" "awk \"{count++} END {print count}\"" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 15${RESET}"
printf "${WHITE} < infile grep Hello | awk \"{count++} END {print count}\" > outfile         ${RESET}"
./pipex infile "grep Hello" "awk \"{count++} END {print count}\"" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 16${RESET}"
printf "${WHITE} < /dev/urandom cat | head -n1 > outfile                                   ${RESET}"
./pipex /dev/urandom cat "head -n1" out_pipex
EXITCODE_PIPEX=$?
< /dev/urandom cat | head -n1 > out_bash 
EXITCODE_BASH=$?
< /dev/null cat >out_pipex
< /dev/null cat >out_bash
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 17${RESET}"
printf "${WHITE} < \"\" \"\" | \"\" > \"\"                                                         ${RESET}"
2> outerr_pipex ./pipex "" "" "" ""
EXITCODE_PIPEX=$?
2>> outerr_bash < "" "" | 2>> outerr_bash "" > "" 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 18${RESET}"
printf "${WHITE} < \"\" cat | cat > \"\"                                                       ${RESET}"
2> outerr_pipex ./pipex "" cat cat ""
EXITCODE_PIPEX=$?
2>> outerr_bash < "" cat | 2>> outerr_bash cat > "" 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 19${RESET}"
printf "${WHITE} < infile \"\" | \"\" > outfile                                                ${RESET}"
2> outerr_pipex ./pipex infile "" "" out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < infile "" | 2>> outerr_bash "" > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 20${RESET}"
printf "${WHITE} < ./libft cat | cat > ./libft                                             ${RESET}"
2> outerr_pipex ./pipex ./libft cat cat ./libft
EXITCODE_PIPEX=$?
2>> outerr_bash < ./libft cat | 2>> outerr_bash cat > ./libft 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 21${RESET}"
printf "${WHITE} < infile noexist | noexist > outfile                                      ${RESET}"
2> outerr_pipex ./pipex infile noexist noexist out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < infile noexist | 2>> outerr_bash noexist > out_bash 
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