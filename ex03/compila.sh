#!/bin/bash

echo "Quieres compilar o limpiar?"
echo "	1: compilar"
echo "	2: limpiar"
echo "	3: compilar y limpiar"
echo " "
read -p "Respuesta: " Respuesta

case $Respuesta in
	"1") 
		make -C ../mylibft/ > /dev/null 2>&1
		gcc -Wall -Werror -Wextra -g ex03.c ../mylibft/libft.a > /dev/null 2>&1
		echo " "
		./a.out
		exit 0
		;;
	"2")
		make fclean -C ../mylibft > /dev/null 2>&1
		rm a.out> /dev/null 2>&1
		echo " "
		echo "Directorio limpio"
		exit 0
		;;
	"3")
		make -C mylibft/ > /dev/null 2>&1
		gcc -Wall -Werror -Wextra -g ex03.c ../mylibft/libft.a > /dev/null 2>&1
		echo " "
		./a.out
		make fclean -C ../mylibft > /dev/null 2>&1
		rm a.out> /dev/null 2>&1
		echo " "
		echo "Directorio limpio"
		;;

	*)
		echo "Respuesta incorrecta"
		exit 1
		;;
esac
