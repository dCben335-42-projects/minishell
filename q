make -C ./libs/libft
make[1] : on entre dans le répertoire « /home/azall/Documents/m5/libs/libft »
make[1]: « libft.a » est à jour.
make[1] : on quitte le répertoire « /home/azall/Documents/m5/libs/libft »
valgrind --suppressions=./config/valgrind_ignore.conf --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes -q -s ./minishell 
