#!/bin/bash

preC=build/Compiler_Files/lang

if [ ! -f $preC ] || [ $# -ge 1 -a $1 == "-r" ];then
echo "PreCompiler Make";
make cleanCp && make -s
shift
fi

$preC $@ 