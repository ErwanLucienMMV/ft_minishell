*This project has been created as part of the 42 curriculum by abarthes, emaigne*

# Description

Le but de minishell comme son nom l'indique est de reproduire le comportement de shell
Ainsi en cas de doute selon le sujet il faudra se referer a bash
```
bash
```
pour les machines sous unbuntu ou si vous avez installer un shell custom (type OmZSH)

Our shell should:

-Display a prompt when waiting for a new command. \n
-Have a working history. \n
-Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path). \n
-Use at most one global variable to indicate a received signal. \n
-Not interpret unclosed quotes or special characters which are not required by the
subject such as \ or ; \n
-Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence. \n
-Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign). \n
-Implement the following redirections: \n
	< should redirect input. \n
	> should redirect output. \n
	<< should be given a delimiter, then read the input until a line containing the delimiter is seen \n
	>> should redirect output in append mode. \n
-Implement pipes | \n
-Handle environnement variables \n
-Handle $? \n
-Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash \n
-Your shell must implement the following built-in commands: \n
	echo with option -n \n
	cd with only a relative or absolute path \n
	pwd with no options \n
	export with no options \n
	unset with no options \n
	env with no options or arguments \n
	exit with no options \n

Do not forget readline() might leak and it is not our concerns, to ignore it with valgrind we can use the following:

temp.supp
```
{
   readline_reachable
   Memcheck:Leak
   match-leak-kinds: reachable
   ...
   obj:*libreadline.so*
}
```

```
valgrind -s --track-fds=yes --trace-children=yes  --leak-check=full --show-leak-kinds=all --suppressions=temp.supp --trace-children-skip-by-arg="*ls,*cat,*grep" ./minishell
```

# Instructions
```
git clone git@vogsphere.42paris.fr:vogsphere intra-uuid-72d15799-a9fd-4915-94cd-8117e74edd29-7288579-abarthes
```

Deux modes de compilations sont possibles:
Le mode normal (a evaluer):
```
make
```

le mode debug (qui print des donnees supplementaires mais n'est pas a evaluer):
```
make debug
```

pour nettoyer les fichiers objets:
```
make clean
```

pour tout nettoyer executable inclus:
```
make fclean
```

# Resources

![Mes conseils si je devais recommencer minishell](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)
![Mes conseils si je devais recommencer minishell (avant que central ne le ferme)](https://42-cursus.gitbook.io/guide/3-rank-03/minishell)

### IA

Chat gpt et github copilot pour nous assister dans le debuggage majoritairement