#!/bin/bash -e
CC=clang++
CFLAGS="-Wall -Werror -Wextra -std=c++98 -g -fsanitize=address"
FDEF="-D NS=ft"
INCLUDE=./include
CMD_DATE=gdate

vector="./main/vector_main.cpp"
map="./main/map_main.cpp"
#LEN=1000


# 1 : file / 2 : output / 3 : define
function compile
{
	echo "$CC $CFLAGS $3 "-D SEED=$SEED" "-D LEN=$LEN" $1  -I $INCLUDE -o $2 2> ko" >> cmd
	$CC $CFLAGS $3 "-D SEED=$SEED" "-D LEN=$LEN" $1  -I $INCLUDE -o $2 2> ko
}

#1 -> prog
#2 -> out
function execution
{
	start=$($CMD_DATE +%s.%N)
	$1 > $2
	dur=$(echo "$($CMD_DATE +%s.%N) - $start" | bc)
	echo $dur
}

#1 file
#2 name_prog
#3 define
function start_ft
{
	compile $1 $2 "$3"

	if [[ $? -ne 0 ]]
	then
		echo "KO"
		return
	fi
	local out="$2"
	out+="_out"
	local ret=$(execution ./$2 $out)
	
	echo $ret
}

function main
{
	SEED=$($CMD_DATE +%s);
	#ft
	local ft_time=0
	local ft_cmpl="OK"
	local ft_ret=$(start_ft ./main/vector_main.cpp ft "$FDEF")
	if [[ "$ft_ret" = "KO" ]]
	then
		ft_cmpl="KO"
	else
		ft_time=$ft_ret
	fi
	#std
	local std_time=0
	local std_cmpl="OK"
	local std_ret=$(start_ft ./main/vector_main.cpp std "")
	if [[ "$std_out" = "KO" ]]
	then
		std_cmpl="KO"
	else
		std_time=$std_ret
	fi


	#result

	echo "Seed is : $SEED"
	echo "compile : ft[$ft_cmpl] std[$std_cmpl]"
	echo "time : ft[$ft_time] std[$std_time]"
	
	diff ft_out std_out > result

	if [[ $? -eq 0 ]]
	then 
		echo "diff : OK"
	else
		echo "diff : KO"
	fi
	

}

LEN=$1
main