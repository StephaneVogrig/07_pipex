# tests pour pipex
valgrind --track-fds=yes 
valgrind --track-children=yes 


executer les commanes en parallele
pas de waitpid entre chaque commande

## test 1
```
./pipex infile "grep Makefile" "wc -w" outfile
```
``` bash
<infile "grep Makefile" | "wc -w" >outfile
```

## test 2
```
./pipex infile ls "wc -w" outfile
```
``` bash
<infile ls | wc -w >outfile
```
## test 3
```
./pipex noexist ls "wc -w" outfile
```
``` bash
<noexist ls | wc -w >outfile
```
<span style="color:green">expected :</span>
``` bash
noexist: No such file or directory

cat outfile
0
```
## test 4
```
./pipex noperm ls "wc -w" outfile
```
``` bash
bash : <noperm ls | wc -w >outfile
```
<span style="color:green">expected :</span>
```
bash: noperm: Permission denied

cat outfile
0
```
## test 5
```
./pipex noperm ls "wc -w" noperm
```
``` bash
bash : <noperm ls | wc -w >noperm
```
<span style="color:green">expected :</span>
```
bash: noperm: Permission denied
bash: noperm: Permission denied
```
## test 6
```
./pipex infile ls "wc -w" noperm
```
``` bash
bash : <infile ls | wc -w >noperm
```
<span style="color:green">expected :</span>
```
bash: noperm: Permission denied
```
## test 7
```
./pipex "" "" "" ""
```
``` bash
bash : <"" "" | "" >""
```
<span style="color:green">expected :</span>
```
bash: : No such file or directory
bash: : No such file or directory
```
## test 8
```
./pipex "   " "   " "   " "   "
```
``` bash
<"   " "   " | "   " >"   "
```
<span style="color:green">expected :</span>
```
bash: :: No such file or directory
   : command not found

```

## test 9
```
./pipex in "./print\ coucou" cat out
```
``` bash
<in ./print\ coucou | cat >out
```

## test 10
```
./pipex in "./\"print coucou\"" cat out
```
``` bash
<in ./"print coucou" | cat >out
```
## test 11
```
./pipex in "./'print coucou'" cat out
```
``` bash
<in ./'print coucou' | cat >out
```


sleep 5 | sleep 5 | sleep 5" doit prendre 5s pas 15s
infile cat | cat | cat | ls outfile  => sigpipe dans bash  doit s'excuter de suite car ne prends pas d'entree std

utilisation de la commande ss peut mettre en evidence l'efficacite de waitpid

here_doc end
here_doc "end"

cat urandom

"blabla" "rm pipex" "

valgrind --track-fds=yes ./pipex Makelol "make re" "valgrind --track-fds=yes ./pipex Makelol make make swepps" swepps

infile "            cat" "      cat" outfile


./pipex /dev/urandon cat "head -n1" outfile
Tu ne dois pas tourner en boucle



Si jamais tu fais < infile cat | xargs > outfile 

## test
```
unset PATH
./pipex infile cat cat outfile
```

<span style="color:yellow">bash :</span>
```
<infile cat | cat >outfile
```
``` bash
bash: infile: No such file or directory
bash: cat: No such file or directory
```
env -i 

valgrind --trace-children=yes --track-fds=yes ./pipex in "./pipex in ls 'cat -e' /dev/stdout" './pipex /dev/stdin cat "wc" out3' out