# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_toaster.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 19:18:29 by svogrig           #+#    #+#              #
#    Updated: 2024/03/29 23:48:21 by svogrig          ###   ########.fr        #
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
printf "\n$RESET\n"

printresult () {
	different=`diff out_pipex out_bash`
	if [ "$different" = "" ] && [ "$1" = "$2" ] && [ "$3" = "$4" ]
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

mandatory () {

printf "\n$YELLOW                                   Mandatory\n"
printf "\n$YELLOW$l1$RESET\n"
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
printf "${PURPLE}\nTest 22${RESET}"
printf "${WHITE} < infile echo 'Bonjour le monde' | cat > outfile                          ${RESET}"
./pipex infile "echo 'Bonjour le monde'" cat out_pipex
EXITCODE_PIPEX=$?
< infile echo 'Bonjour le monde' | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 23${RESET}"     
printf "${WHITE} < infile echo 'Bonjour le monde' | cat > outfile                          ${RESET}"
./pipex infile "echo 'Bonjour le monde'" cat out_pipex
EXITCODE_PIPEX=$?
< infile echo 'Bonjour le monde' | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 24${RESET}"
printf "${WHITE} < infile cat | echo 'Bonjour le monde' > outfile                          ${RESET}"
./pipex infile cat "echo 'Bonjour le monde'" out_pipex
EXITCODE_PIPEX=$?
< infile cat | echo 'Bonjour le monde' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 25${RESET}"
printf "${WHITE} < infile grep Hello | awk '{count++} END {print count}' > outfile         ${RESET}"
./pipex infile "grep Hello" "awk '{count++} END {print count}'" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 26${RESET}"
printf "${WHITE} < infile grep Hello | awk \"{count++} END {print count}\" > outfile         ${RESET}"
./pipex infile "grep Hello" "awk \"{count++} END {print count}\"" out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk "{count++} END {print count}" > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

}

multi () {

printf "\n$YELLOW                                   Multipipe\n"
printf "\n$YELLOW$l1$RESET\n"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 01${RESET}"
printf "${WHITE} < infile cat | cat | cat outfile                                                 ${RESET}"
./pipex_bonus infile cat cat cat out_pipex
EXITCODE_PIPEX=$?
< infile cat | cat | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 02${RESET}"
printf "${WHITE} < noperm cat | ls | cat > outfile                                                ${RESET}"
2> outerr_pipex ./pipex_bonus noperm cat ls cat out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < noperm cat | ls | 2>> outerr_bash cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 03${RESET}"
printf "${WHITE} < infile cat | ls | cat > noperm                                                 ${RESET}"
2> outerr_pipex ./pipex_bonus infile cat ls cat noperm
EXITCODE_PIPEX=$?
2>> outerr_bash < infile cat | ls | 2>> outerr_bash cat > noperm
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 04${RESET}"
printf "${WHITE} < noperm cat | ls | cat > noperm                                                 ${RESET}"
2> outerr_pipex ./pipex_bonus noperm cat ls cat noperm
EXITCODE_PIPEX=$?
2>> outerr_bash < noperm cat | ls | 2>> outerr_bash cat > noperm
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 05${RESET}"
printf "${WHITE} < infile ./printcoucou | wc -l | cat > outfile                                   ${RESET}"
./pipex_bonus infile ./printcoucou "wc -l" cat out_pipex
EXITCODE_PIPEX=$?
< infile ./printcoucou | wc -l | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 06${RESET}"
printf "${WHITE} < infile ./printcoucou | cat | cat | ./printcoucou > outfile                     ${RESET}"
./pipex_bonus infile ./printcoucou cat cat ./printcoucou out_pipex
EXITCODE_PIPEX=$?
< infile ./printcoucou | cat | cat | ./printcoucou > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 07${RESET}"
printf "${WHITE} < infile ls | wc -cl | grep 0 | ./'print coucou' | cat > outfile                 ${RESET}"
./pipex_bonus infile ls "wc -cl" "grep 0" "./'print coucou'" cat out_pipex
EXITCODE_PIPEX=$?
< infile ls | wc -cl | grep 0 | ./'print coucou' | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 08${RESET}"
printf "${WHITE} < infile sleep 1 | sleep 1 | sleep 1 | sleep 1 | sleep 1 | ls > outfile          ${RESET}"
SECONDS=0
./pipex_bonus infile cat "sleep 1" "sleep 1" "sleep 1" "sleep 1" "sleep 1" ls out_pipex
EXITCODE_PIPEX=$?
TIMEEXECPIPE=$SECONDS
SECONDS=0
< infile sleep 1 | sleep 1 | sleep 1 | sleep 1 | sleep 1 | ls > out_bash 
EXITCODE_BASH=$?
TIMEEXECBASH=$SECONDS
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH" "$TIMEEXECPIPE" "$TIMEEXECBASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 09${RESET}"
printf "${WHITE} < infile cat | /bin/cat | wc -cl > outfile                                       ${RESET}"
./pipex_bonus infile cat /bin/cat "wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile cat | /bin/cat | wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 10${RESET}"
printf "${WHITE} < infile cat | /bin/cat | /bin/wc -cl > outfile                                  ${RESET}"
./pipex_bonus infile cat /bin/cat "/bin/wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile cat | /bin/cat | /bin/wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 11${RESET}"
printf "${WHITE} < infile /bin/cat | /bin/cat | /bin/wc -cl > outfile                             ${RESET}"
./pipex_bonus infile /bin/cat /bin/cat "/bin/wc -cl" out_pipex
EXITCODE_PIPEX=$?
< infile /bin/cat | /bin/cat | /bin/wc -cl > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 12${RESET}"
printf "${WHITE} < infile ls -l | wc -cl | cat > outfile                                          ${RESET}"
./pipex_bonus infile "ls -l" "wc -cl" cat out_pipex
EXITCODE_PIPEX=$?
< infile ls -l | wc -cl | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 13${RESET}"
printf "${WHITE} < infile ls -l infile | wc -cl | cat > outfile                                   ${RESET}"
./pipex_bonus infile "ls -l infile" "wc -cl" cat out_pipex
EXITCODE_PIPEX=$?
< infile ls -l infile | wc -cl | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 14${RESET}"
printf "${WHITE} < /dev/urandom cat | head -n1 > outfile                                          ${RESET}"
./pipex_bonus /dev/urandom cat "head -n1" out_pipex
EXITCODE_PIPEX=$?
< /dev/urandom cat | head -n1 > out_bash 
EXITCODE_BASH=$?
< /dev/null cat >out_pipex
< /dev/null cat >out_bash
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 15${RESET}"
printf "${WHITE} < \"\" \"\" | \"\" | \"\" | \"\" > \"\"                                                      ${RESET}"
2> outerr_pipex ./pipex_bonus "" "" "" "" "" ""
EXITCODE_PIPEX=$?
2>> outerr_bash < "" "" | 2>> outerr_bash "" | 2>> outerr_bash "" | 2>> outerr_bash "" > "" 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 16${RESET}"
printf "${WHITE} < \"\" cat | cat | cat | cat > \"\"                                                  ${RESET}"
2> outerr_pipex ./pipex_bonus "" cat cat cat cat ""
EXITCODE_PIPEX=$?
2>> outerr_bash < "" cat | cat | cat | 2>> outerr_bash cat > "" 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 17${RESET}"
printf "${WHITE} < infile \"\" | \"\" | \"\" | \"\" > outfile                                             ${RESET}"
2> outerr_pipex ./pipex_bonus infile "" "" "" "" out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < infile "" | 2>> outerr_bash "" | 2>> outerr_bash "" | 2>> outerr_bash "" > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 18${RESET}"
printf "${WHITE} < ./libft cat | cat | cat | cat > ./libft                                        ${RESET}"
2> outerr_pipex ./pipex_bonus ./libft cat cat cat cat ./libft
EXITCODE_PIPEX=$?
2>> outerr_bash < ./libft cat | cat | cat | 2>> outerr_bash cat > ./libft 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 19${RESET}"
printf "${WHITE} < infile noexist | noexist | noexist > outfile                                   ${RESET}"
2> outerr_pipex ./pipex_bonus infile noexist noexist noexist out_pipex
EXITCODE_PIPEX=$?
2>> outerr_bash < infile noexist | 2>> outerr_bash noexist | 2>> outerr_bash noexist > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 20${RESET}"
printf "${WHITE} < infile echo 'Bonjour le monde' | wc | cat > outfile                            ${RESET}"
./pipex_bonus infile "echo 'Bonjour le monde'" wc cat out_pipex
EXITCODE_PIPEX=$?
< infile echo 'Bonjour le monde' | wc | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 21${RESET}"
printf "${WHITE} < infile cat | echo 'Bonjour le monde' | wc | cat > outfile                      ${RESET}"
./pipex_bonus infile cat "echo 'Bonjour le monde'" wc cat out_pipex
EXITCODE_PIPEX=$?
< infile cat | echo 'Bonjour le monde' | wc | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 22${RESET}"
printf "${WHITE} < infile cat | cat | echo 'Bonjour le monde' > outfile                           ${RESET}"
./pipex_bonus infile cat cat "echo 'Bonjour le monde'" out_pipex
EXITCODE_PIPEX=$?
< infile cat | cat | echo 'Bonjour le monde' > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 23${RESET}"
printf "${WHITE} < infile grep Hello | awk '{count++} END {print count}' | cat > outfile          ${RESET}"
./pipex_bonus infile "grep Hello" "awk '{count++} END {print count}'" cat out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk '{count++} END {print count}' | cat > out_bash 
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

# -----------------------------------------------------------------------------------------------
printf "${PURPLE}\nTest 24${RESET}"
printf "${WHITE} < infile grep Hello | awk \"{count++} END {print count}\" | cat > outfile                ${RESET}"
./pipex_bonus infile "grep Hello" "awk \"{count++} END {print count}\"" cat out_pipex
EXITCODE_PIPEX=$?
< infile grep Hello | awk "{count++} END {print count}" | cat > out_bash
EXITCODE_BASH=$?
printresult "$EXITCODE_PIPEX" "$EXITCODE_BASH"

}

help () {
printf "$YELLOW./pipex_toaster$RESET           run madatory tests\n"
printf "$YELLOW./pipex_toaster mandatory$RESET run madatory tests\n"
printf "$YELLOW./pipex_toaster multi$RESET     run multipipe tests\n"
#printf "$YELLOW./pipex_toaster heredoc$RESET   run heredoc tests\n"
#printf "$YELLOW./pipex_toaster bonus$RESET     run multipipe and heredoc tests\n"
}

echo "#include <stdio.h>" > printcoucou.c
printf 'int main(void){printf("coucou\\n");return (0);}' >> printcoucou.c
clang printcoucou.c -o printcoucou
cp printcoucou 'print coucou'

printf > infile "Hello World!\nHello World!\n"
touch noperm
chmod 000 noperm
if [ -f out_pipex ]; then
	rm out_pipex
fi
touch out_pipex
if [ -f out_bash ]; then
	rm out_bash
fi
touch out_bash
if [ -f outerr_pipex ]; then
	rm outerr_pipex
fi
touch outerr_pipex
if [ -f outerr_bash ]; then
	rm outerr_bash
fi
touch outerr_bash

if [ "$1" == "" ]; then
	mandatory
elif [ "$1" == "all" ]; then
	mandatory
	multi
	#heredoc
elif [ "$1" == "bonus" ]; then
	multi
	#heredoc
elif [ "$1" == "multi" ]; then
	multi
#elif [ "$1" == "heredoc" ]; then
	#heredoc
elif [ "$1" == "help" ]; then
	help
else
	help
fi

printf "\n$RED$l1$RESET\n\n"

rm infile
rm out_pipex
rm out_bash
rm outerr_pipex
rm outerr_bash
rm -f noperm
rm printcoucou.c
rm printcoucou
rm 'print coucou'