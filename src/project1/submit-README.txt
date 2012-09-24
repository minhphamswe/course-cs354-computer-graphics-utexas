turnin
--------------------------------------------------
./submit: line 20: turnin: command not found
./submit: line 21: turnin: command not found

code check 
--------------------------------------------------
Done processing color.cpp
Ignoring color.cpp~; not a .cc or .h file
Done processing color.cpp~
Done processing command.cpp
Done processing main.cpp
Ignoring main.cpp~; not a .cc or .h file
Done processing main.cpp~
Done processing point.cpp
Ignoring point.cpp~; not a .cc or .h file
Done processing point.cpp~
Done processing turtle.cpp
Ignoring turtle.cpp~; not a .cc or .h file
Done processing turtle.cpp~
Done processing vector.cpp
Ignoring vector.cpp~; not a .cc or .h file
Done processing vector.cpp~
Done processing color.h
Done processing command.h
Done processing common.h
Done processing geometry.h
Done processing point.h
Done processing turtle.h
Done processing vector.h
Total errors found: 0

compile 
--------------------------------------------------
g++    -c -o main.o main.cpp
g++    -c -o command.o command.cpp
g++    -c -o point.o point.cpp
g++    -c -o vector.o vector.cpp
g++    -c -o color.o color.cpp
g++    -c -o turtle.o turtle.cpp
g++   -o turtle main.o command.o point.o vector.o color.o turtle.o  -lglut -lGLU -lGL -lm

run 
--------------------------------------------------
successful run
successful run
ERROR: design.png does not exist

cleanup 
--------------------------------------------------
removing directory minh
