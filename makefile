TITLE = tournament
CPP = Creature.cpp
CPP += Tournament.cpp
CPP += Barbarian.cpp
CPP += Bluemen.cpp
CPP += Harrypotter.cpp
CPP += Medusa.cpp
CPP += Vampire.cpp
CPP += Fighterlineup.cpp
CPP += Loserpile.cpp
CPP += main.cpp
DELETE = *.gch
DELETE += *.o

all:
	g++ ${CPP} -o ${TITLE}

clean:
	${RM} ${DELETE} ${TITLE}
