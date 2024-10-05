.PHONY: test clean
FLAGS = -pedantic-errors -std=c++11
AllyData.o: AllyData.cpp structDec.h
	g++ $(FLAGS) -c AllyData.cpp
AllyFunction.o: AllyFunction.cpp structDec.h
	g++ $(FLAGS) -c AllyFunction.cpp
fileIO.o: fileIO.cpp structDec.h
	g++ $(FLAGS) -c fileIO.cpp
game.o: game.cpp structDec.h
	g++ $(FLAGS) -c game.cpp 
EnemyData.o: EnemyData.cpp structDec.h
	g++ $(FLAGS) -c EnemyData.cpp
EnemyFunc.o: EnemyFunc.cpp structDec.h
	g++ $(FLAGS) -c EnemyFunc.cpp 
TerrFunc.o: TerrFunc.cpp structDec.h
	g++ $(FLAGS) -c TerrFunc.cpp
mech.o: mech.cpp structDec.h
	g++ $(FLAGS) -c mech.cpp
shop.o: shop.cpp structDec.h
	g++ $(FLAGS) -c shop.cpp 
Stat.o: Stat.cpp structDec.h
	g++ $(FLAGS) -c Stat.cpp
TerrainData.o: TerrainData.cpp structDec.h
	g++ $(FLAGS) -c TerrainData.cpp
print.o: print.cpp structDec.h
	g++ $(FLAGS) -c print.cpp
main.o: main.cpp structDec.h
	g++ $(FLAGS) -c main.cpp
main: AllyData.o AllyFunction.o fileIO.o EnemyData.o EnemyFunc.o TerrFunc.o mech.o shop.o Stat.o TerrainData.o game.o print.o main.o
	g++ $(FLAGS) $^ -o $@
test: main
	./main
clean: 
	rm -f AllyData.o AllyFunction.o fileIO.o EnemyData.o EnemyFunc.o TerrFunc.o mech.o shop.o Stat.o TerrainData.o game.o print.o main.o main