wolf: game.o map.o tile.o camera.o raycast.o main.o Gun.o AmmoPickup.o Player.o enemy.o
	g++ game.o map.o main.o tile.o camera.o raycast.o Gun.o AmmoPickup.o Player.o enemy.o -w -lSDL2 -o wolf
main.o: main.cpp game.h
	g++ -c main.cpp
game.o: game.cpp game.h map.o camera.o Player.o
	g++ -c game.cpp
map.o: map.cpp map.h tile.h enemy.h
	g++ -c map.cpp
tile.o: tile.cpp tile.h
	g++ -c tile.cpp
raycast.o: raycast.cpp raycast.h map.h
	g++ -c raycast.cpp
camera.o: camera.cpp camera.h raycast.h map.h
	g++ -c camera.cpp
Gun.o: Gun.cpp Gun.h
	g++ -c Gun.cpp
AmmoPickup.o: AmmoPickup.cpp AmmoPickup.h Gun.h
	g++ -c AmmoPickup.cpp
Player.o: Player.cpp Player.h map.o AmmoPickup.h
	g++ -c Player.cpp
enemy.o: enemy.h enemy.cpp raycast.h map.o Player.o
	g++ -c enemy.cpp
clean:
	rm -f *.o
	rm wolf
