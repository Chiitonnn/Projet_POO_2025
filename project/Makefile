CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = 
TARGET = projet_poo.exe

# Tous les fichiers source
SRCS = Core/Utilisateur.cpp Core/Tableau.cpp Core/Liste.cpp \
       Core/Carte.cpp Core/Etiquette.cpp Core/Commentaire.cpp \
       Patterns/Command/ICommande.cpp Patterns/Command/CommandeDeplacerCarte.cpp \
       Patterns/Observer/GestionnaireNotifications.cpp \
       Patterns/Factory/IFabriqueCarte.cpp Patterns/Factory/FabriqueCarteStandard.cpp \
       Patterns/Facade/SystemFacade.cpp \
       main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	del $(TARGET) 2>nul || true

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

.PHONY: all clean run rebuild