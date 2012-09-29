#!/bin/sh


output () {

	echo `basename $1`$2

}


compile () {

	ls $2 | while read file

		do

		result=`output $file $3`

		echo "Compiling $file as $result using $1"

		$1 -c -o $result $file

	done

}


link () {

	echo "Linking $3 as $2 using $1"

	$1 -o $2 `ls $3`

}


clean () {

	echo "Deleting $@"

	rm $@ 2>/dev/null

}


options () {

	if [ "$1" == "clean" ]

	then
		clean msg '*.o'

		exit
	else
		compile c++ '*.cpp' '.o'

		link c++ msg '*.o'

		clean *.o
	fi

}


options $@
