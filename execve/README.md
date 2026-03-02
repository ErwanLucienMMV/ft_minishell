*This project has been created as part of the 42 curriculum by abarthes, emaigne*

# Description

Le but de minishell comme son nom l'indique est de reproduire le comportement de shell
Ainsi en cas de doute selon le sujet il faudra se referer a bash
```
bash
```
pour les machines sous unbuntu ou si vous avez installer un shell custom (type OmZSH)

Our shell should:

-Display a prompt when waiting for a new command.
-Have a working history.
-Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
-Use at most one global variable to indicate a received signal.
-Not interpret unclosed quotes or special characters which are not required by the
subject such as \ or ;
-Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
-Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
-Implement the following redirections:
	< should redirect input.
	> should redirect output.
	<< should be given a delimiter, then read the input until a line containing the delimiter is seen
	>> should redirect output in append mode.
-Implement pipes |
-Handle environnement variables
-Handle $?
-Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash
-Your shell must implement the following built-in commands:
	echo with option -n
	cd with only a relative or absolute path
	pwd with no options
	export with no options
	unset with no options
	env with no options or arguments
	exit with no options

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