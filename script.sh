#!/bin/bash


#	A.P. EXAM PROJECT: IMPLEMENTATION OF BINARY SEARCH TREE

#	@file script.sh
#	@author Thomas Deponte, Victor Alexandrovic Plesco, Pietro Morichetti
#	@date 03/11/2020
#	@version 1.1 

# BST AND BENCHMARK MANAGER
# This script takes in input the MAKEFILE command needed to compile the
# right, moreover it takes in input another string to decide which execution
# mode have to be done.
# The output of this script is the output of the specified exe file.

make_command=${1} # first arg is the makefile command
exe=${2} # second arg is the execution mode: standad, valgrind

echo "------------------- START MAKEFILE -------------------"
echo ""
make ${make_command}
make clean
echo ""
echo "-------------------- END MAKEFILE --------------------"

echo ""
echo ""

if [[ "${make_command}" == "main_test" ]]  ; then
    echo "----------------- EXECUTING MAIN_TEST -----------------"
    if [[ "${exe}" == "standard" ]] ; then
        ./main_test
    elif [[ "${exe}" == "valgrind" ]] ; then
        valgrind --leak-check=full --show-leak-kinds=all -v ./main_test
    else
        echo "ERROR: file exe unknown"
    fi
    echo "-------------------- END MAIN_TEST --------------------"
elif [[ "${make_command}" == "main_benck" ]] ; then
    echo "----------------- EXECUTING MAIN_BENCK -----------------"
    if [[ "${exe}" == "standard" ]] ; then
        ./main_benck
    elif [[ "${exe}" == "valgrind" ]] ; then
        valgrind --leak-check=full --show-leak-kinds=all -v ./main_benck
    else 
        echo "ERROR: file exe unknown"
    fi
    echo "-------------------- END MAIN_BENCK --------------------"
fi
