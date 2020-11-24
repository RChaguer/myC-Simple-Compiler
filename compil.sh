#!/bin/bash

# Global Declarations
tmp=tmp_file.text
fileExtension=.myc
testFolderPath=tst\/
buildFolderName=build
preC=$buildFolderName/Compiler_Files/lang


# Compiler make
if [ ! -f $preC ];then
echo "Compiler Make";
make cleanCp && make -s
fi


# Build Folder Creation
if [ ! -d $buildFolderName ];then
echo "Build Folder Creation";
mkdir $buildFolderName
mkdir $buildFolderName/H_C_Files
fi

while [ $# -gt 0 ] 
do 
    # Generate PreCompiled Temp File
    ( $preC < $1) > $tmp

    # File Name and Path Variables
    filePath=$(echo $1 | sed -e "s/$fileExtension//g")
    fileName=$(echo $filePath | sed -e "s/tst\///g")

    # Generate file.h
    echo "#ifndef TEST_H
    #define TEST_H
    " > $buildFolderName/H_C_Files/$fileName.h

    cat $tmp | head -n 4 >> $buildFolderName/H_C_Files/$fileName.h

    echo "
    #endif // TEST_H" >> $buildFolderName/H_C_Files/$fileName.h

    # Generate file.c
    echo "#include <stdio.h>
    #include \"$fileName.h\"
    " > $buildFolderName/H_C_Files/$fileName.c

    cat $tmp | tail -n +5 >> $buildFolderName/H_C_Files/$fileName.c

    rm $tmp
    gcc $buildFolderName/H_C_Files/$fileName.c -g -o $buildFolderName/$fileName

    shift
done
