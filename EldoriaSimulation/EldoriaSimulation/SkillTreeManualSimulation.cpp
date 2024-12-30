#include "SkillTreeManualSimulation.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <fstream>

SkillTreeManualSimulation::SkillTreeManualSimulation()
{


	std::srand(static_cast<unsigned int>(std::time(0)));
	int step = 0;
	predileccion = 0; //1 guardas, 2 eruditos, 0 none
	incremento = 1.4f;

	inv = Disciplina();
	inv.tipo = Dtipo::INVESTICACION;
	inv.expActual = 0;
	inv.expFinal = 100;

	comb = Disciplina();
	comb.tipo = Dtipo::COMBATE;
	comb.expActual = 0;
	comb.expFinal = 100;

	fab = Disciplina();
	fab.tipo = Dtipo::FABRICACION;
	fab.expActual = 0;
	fab.expFinal = 100;

	st_guardias.rootsNode.push_back(treeNode(u8"Mejora combate", false, 1));
	st_guardias.rootsNode.back().childs.push_back(treeNode(u8"Curar", false, 2));
	st_guardias.rootsNode.back().childs.push_back(treeNode(u8"Aumentar velocidad ataque", false, 3));
	st_guardias.rootsNode.back().childs.push_back(treeNode(u8"Tacticas de combate", false, 4));
	st_guardias.rootsNode.push_back(treeNode(u8"Forja", false, 5));
	st_guardias.rootsNode.back().childs.push_back(treeNode(u8"Trampas", false, 6));
	st_guardias.rootsNode.push_back(treeNode(u8"Recoleccion", false, 7));
	st_guardias.rootsNode.push_back(treeNode(u8"Dominio del entorno", false, 8));
	st_guardias.rootsNode.back().childs.push_back(treeNode(u8"Carisma", false, 9));



	st_eruditos.rootsNode.push_back(treeNode(u8"Mejora arcana", false,1));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Curacion", false,2));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Vision arcana", false,3));
	st_eruditos.rootsNode.push_back(treeNode(u8"Alquimia", false,4));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Control temporal", false,5));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Clon de trabajo", false,6));
	st_eruditos.rootsNode.push_back(treeNode(u8"Analisis", false,7));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Comunicacion con animales", false,8));
	st_eruditos.rootsNode.back().childs.push_back(treeNode(u8"Perspicacia", false,9));

}

SkillTreeManualSimulation::~SkillTreeManualSimulation()
{
}



void SkillTreeManualSimulation::MostrarStats()
{

	printf(u8"\n ---------- Stats ---------- \n");

	printf(u8"\n\n ---Influencia: %d, ", influencia);
	if (influencia == 0) {
		printf(u8"Tienes una influencia neutral");
	}
	else if (influencia > 0) {
		printf(u8"Tienes una influencia hacia los guardias");
	}
	else {
		printf(u8"Tienes una influencia hacia los eruditos");
	}

	printf(u8"\n\n ---PH: %d", ph);

	printf(u8"\n\n ---Disciplinas: \n");
	printf(u8"Investigacion: Puntos exp: %f, Puntos final: %f \n", inv.expActual, inv.expFinal);
	printf(u8"Combate: Puntos exp: %f, Puntos final: %f \n", comb.expActual, comb.expFinal);
	printf(u8"Fabricacion: Puntos exp: %f, Puntos final: %f \n", fab.expActual, fab.expFinal);



	printf(u8"\n");


}

void SkillTreeManualSimulation::Step()
{
	int randomNumber = std::rand() % 101; // 0-100
	if (randomNumber < 50) {
		inv.expActual += std::rand() % 31;
		if (inv.expActual > inv.expFinal) {
			ph++;
			inv.vecesMejorada++;
			inv.expActual = inv.expActual - inv.expFinal;
			inv.expFinal = 100 * (incremento * inv.vecesMejorada);
		}
	}

	randomNumber = std::rand() % 101; // 0-100
	if (randomNumber < 50) {
		comb.expActual += std::rand() % 31;
		if (comb.expActual > comb.expFinal) {
			ph++;
			comb.vecesMejorada++;
			comb.expActual = comb.expActual - comb.expFinal;
			comb.expFinal = 100 * (incremento * comb.vecesMejorada);
		}
	}

	randomNumber = std::rand() % 101; // 0-100
	if (randomNumber < 50) {
		fab.expActual += std::rand() % 31;
		if (fab.expActual > fab.expFinal) {
			ph++;
			fab.vecesMejorada++;
			fab.expActual = fab.expActual - fab.expFinal;
			fab.expFinal = 100 * (incremento * fab.vecesMejorada);
		}
	}



	//Comprar ph
	int pasadas = 0;
	while (ph > 0 && pasadas < 20) {
		pasadas++;


		randomNumber = std::rand() % 101; // 0-100

		if (randomNumber < 50 && (predileccion == 1 || predileccion == 0)) {
			//Arbol guardias
			for (int i = 0; i < st_guardias.rootsNode.size(); i++) {
				if (!st_guardias.rootsNode.at(i).comprado) {
					randomNumber = std::rand() % 101; // 0-100
					if (randomNumber < 50 && ph > 0) {
						st_guardias.rootsNode.at(i).comprado = true;
						ph--;
						influencia++;
						if (ph <= 0) {
							break;
						}
					}
				}
				else {

					for (int j = 0; j < st_guardias.rootsNode.at(i).childs.size(); j++) {
						if (!st_guardias.rootsNode.at(i).childs.at(j).comprado) {
							randomNumber = std::rand() % 101; // 0-100
							if (randomNumber < 50 && ph > 0) {
								st_guardias.rootsNode.at(i).childs.at(j).comprado = true;
								ph--;
								influencia++;
								if (ph <= 0) {
									break;
								}
							}
						}
					}

				}
			}
		}
		else {
			if ((predileccion == 2 || predileccion == 0)) {
				//Arbol eruditos
				for (int i = 0; i < st_eruditos.rootsNode.size(); i++) {
					if (!st_eruditos.rootsNode.at(i).comprado) {
						randomNumber = std::rand() % 101; // 0-100
						if (randomNumber < 50 && ph > 0) {
							st_eruditos.rootsNode.at(i).comprado = true;
							ph--;
							influencia--;
							if (ph <= 0) {
								break;
							}
						}
					}
					else {

						for (int j = 0; j < st_eruditos.rootsNode.at(i).childs.size(); j++) {
							if (!st_eruditos.rootsNode.at(i).childs.at(j).comprado) {
								randomNumber = std::rand() % 101; // 0-100
								if (randomNumber < 50 && ph > 0) {
									st_eruditos.rootsNode.at(i).childs.at(j).comprado = true;
									ph--;
									influencia--;
									if (ph <= 0) {
										break;
									}
								}
							}
						}

					}
				}
			}
		}
	}
}

void SkillTreeManualSimulation::GuardarProgreso(std::ofstream& file, int sim_num, int step_num)
{
	// Guardar el estado de la simulación en este paso en el archivo CSV
	file << sim_num << ",";              // Número de simulación
	file << step_num << ",";             // Número de paso
	file << influencia << ",";           // Valor de influencia
	file << ph << ",";                   // Valor de PH
	file << inv.expActual << ",";        // Puntos de experiencia en Investigación
	file << comb.expActual << ",";       // Puntos de experiencia en Combate
	file << fab.expActual << "\n";       // Puntos de experiencia en Fabricación
}


void SkillTreeManualSimulation::ResetSimulacion()
{
	inv = Disciplina();
	inv.tipo = Dtipo::INVESTICACION;
	inv.expActual = 0;
	inv.expFinal = 100;

	comb = Disciplina();
	comb.tipo = Dtipo::COMBATE;
	comb.expActual = 0;
	comb.expFinal = 100;

	fab = Disciplina();
	fab.tipo = Dtipo::FABRICACION;
	fab.expActual = 0;
	fab.expFinal = 100;

	influencia = 0;
	ph = 0;

	// Limpiar los árboles de habilidades (si es necesario)
	LimpiarArboles();
}

void SkillTreeManualSimulation::LimpiarArboles()
{
	// Aquí puedes reiniciar el estado de los árboles de habilidades, si es necesario.
	for (auto& node : st_guardias.rootsNode) {
		node.comprado = false;
		for (auto& child : node.childs) {
			child.comprado = false;
		}
	}

	for (auto& node : st_eruditos.rootsNode) {
		node.comprado = false;
		for (auto& child : node.childs) {
			child.comprado = false;
		}
	}
}


void SkillTreeManualSimulation::PrintTree(treeNode node, int depth = 0) {
	// Imprimir sangría según la profundidad
	for (int i = 0; i < depth; ++i) {
		printf(u8"  "); // Dos espacios por nivel de profundidad
	}
	// Imprimir el nombre del nodo
	printf(u8"- %s\n", node.name.c_str());

	// Llamar recursivamente a los hijos
	for (const auto& child : node.childs) {
		PrintTree(child, depth + 1);
	}
}

void SkillTreeManualSimulation::PrintTreeVisual(const treeNode& node, const std::string& prefix) {
	// Inicializar el contador si no se pasó


	// Mostrar el número, el nombre del nodo y su estado
	std::string status = node.comprado ? " (Comprado)" : " (No Comprado)";
	printf(u8"%s%d. %s%s\n", prefix.c_str(), node.id, node.name.c_str(), status.c_str());

	// Llamar recursivamente a los hijos con un prefijo adecuado
	for (size_t i = 0; i < node.childs.size(); ++i) {
		// Si no es el último hijo, usamos una línea continua, si es el último, no ponemos línea extra
		std::string newPrefix = prefix + (i + 1 == node.childs.size() ? "    " : "|   ");
		PrintTreeVisual(node.childs[i], newPrefix);
	}
}

void SkillTreeManualSimulation::SetColor(int color) {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
	std::cout << "\033[1;" << color << "m"; // ANSI escape code
#endif
}


void SkillTreeManualSimulation::EntrenarDisciplina() {
	int opcion = 0;
	do {
		std::cout << "¿Qué disciplina deseas entrenar?" << std::endl;
		std::cout << "1. Investigación" << std::endl;
		std::cout << "2. Combate" << std::endl;
		std::cout << "3. Fabricación" << std::endl;
		std::cout << "Selecciona una opción (1-3): ";
		std::cin >> opcion;

		if (opcion < 1 || opcion > 3) {
			std::cout << "Opción inválida. Por favor, intenta de nuevo." << std::endl;
			opcion = 0;
		}
	} while (opcion < 1 || opcion > 3);

	// Continúa el entrenamiento...
	int puntosEntrenamiento = std::rand() % 61 + 20;
	if (opcion == 1) {
		inv.expActual += puntosEntrenamiento;
		std::cout << "Entrenaste Investigación, ganando " << puntosEntrenamiento << " exp.\n";
	}
	else if (opcion == 2) {
		comb.expActual += puntosEntrenamiento;
		std::cout << "Entrenaste Combate, ganando " << puntosEntrenamiento << " exp.\n";
	}
	else {
		fab.expActual += puntosEntrenamiento;
		std::cout << "Entrenaste Fabricación, ganando " << puntosEntrenamiento << " exp.\n";
	}
	VerificarMaxExp(inv);
	VerificarMaxExp(comb);
	VerificarMaxExp(fab);
}

void SkillTreeManualSimulation::VerificarMaxExp(Disciplina& disciplina) {
	if (disciplina.expActual >= disciplina.expFinal) {
		ph++; // Aumentar los puntos de habilidad (PH)


		if (disciplina.tipo == Dtipo::COMBATE) {
			printf(u8"¡Has superado el límite de experiencia de COMBATE y ahora tienes un punto de habilidad!");
		}
		else if (disciplina.tipo == Dtipo::FABRICACION) {
			printf(u8"¡Has superado el límite de experiencia de FABRICACION y ahora tienes un punto de habilidad!");
		}
		else {
			printf(u8"¡Has superado el límite de experiencia de INVESTIGACION y ahora tienes un punto de habilidad!");
		}

		// Reiniciar la experiencia
		disciplina.expActual -= disciplina.expFinal;
		disciplina.vecesMejorada++;
		disciplina.expFinal = 100 * (incremento * disciplina.vecesMejorada); // Aumentar el límite de experiencia
	}
}

void SkillTreeManualSimulation::GastarPuntoHabilidad() {


	int arbol;

	do {
		std::cout << "¿En qué árbol deseas gastar tu punto de habilidad?" << std::endl;
		std::cout << "1. Guardias" << std::endl;
		std::cout << "2. Eruditos" << std::endl;

		std::cin >> arbol;

		if (arbol == 1) {
			// Mostrar árbol de Guardias
			for (const auto& root : st_guardias.rootsNode) {
				//PrintTree(root, 0);
				PrintTreeVisual(root, "");
			}

			std::cout << "¿En qué nodo deseas invertir tu punto de habilidad?" << std::endl;
			int nodoGuardia;
			std::cin >> nodoGuardia;

			if (nodoGuardia < 1 || nodoGuardia > 9) {
				std::cout << "Nodo no válido, vuelve a intentar." << std::endl;
				return;
			}

			// Gastar punto en el nodo elegido
			GastarPuntoEnNodo(1, nodoGuardia);
		}
		else if (arbol == 2) {
			// Mostrar árbol de Eruditos
			for (const auto& root : st_eruditos.rootsNode) {
				//PrintTree(root, 0);
				PrintTreeVisual(root, "");
			}

			std::cout << "¿En qué nodo deseas invertir tu punto de habilidad?" << std::endl;
			int nodoErudito;
			std::cin >> nodoErudito;

			if (nodoErudito < 1 || nodoErudito > 9) {
				std::cout << "Nodo no válido, vuelve a intentar." << std::endl;
				return;
			}

			// Gastar punto en el nodo elegido
			if (!GastarPuntoEnNodo(2, nodoErudito)) {

			}
			
		}
		else {
			std::cout << "Opción no válida, vuelve a intentar." << std::endl;
		}
	} while (arbol != 1 && arbol != 2);

	
}

bool SkillTreeManualSimulation::GastarPuntoEnNodo(int arbol, int id) {

	if (arbol == 1) {
		if (id == 1) {
			if (!st_guardias.rootsNode[0].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 2) {
			if (!st_guardias.rootsNode[0].childs[0].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[0].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 3) {
			if (!st_guardias.rootsNode[0].childs[1].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[0].childs[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 4) {
			if (!st_guardias.rootsNode[0].childs[2].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[0].childs[2].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 5) {
			if (!st_guardias.rootsNode[1].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 6) {
			if (!st_guardias.rootsNode[1].childs[0].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[1].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 7) {
			if (!st_guardias.rootsNode[2].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[2].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 8) {
			if (!st_guardias.rootsNode[3].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[3].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 9) {
			if (!st_guardias.rootsNode[3].childs[0].comprado) {
				ph--;
				influencia++;
				st_guardias.rootsNode[3].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
	}
	else if (arbol == 2) {
		if (id == 1) {
			if (!st_eruditos.rootsNode[0].comprado) {
				ph--;
				influencia--;
				st_eruditos.rootsNode[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 2) {
			if (!st_eruditos.rootsNode[0].childs[0].comprado) {
				ph--;
				influencia--;
				st_eruditos.rootsNode[0].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 3) {
			if (!st_eruditos.rootsNode[0].childs[1].comprado) {
				ph--;
				influencia--;;
				st_eruditos.rootsNode[0].childs[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 4) {
			if (!st_eruditos.rootsNode[1].comprado) {
				ph--;
				influencia--;;
				st_eruditos.rootsNode[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 5) {
			if (!st_eruditos.rootsNode[1].childs[0].comprado) {
				ph--;
				influencia--;;
				st_eruditos.rootsNode[1].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 6) {
			if (!st_eruditos.rootsNode[1].childs[1].comprado) {
				ph--;
				influencia--;;
				st_eruditos.rootsNode[1].childs[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 7) {
			if (!st_eruditos.rootsNode[2].comprado) {
				ph--;
				influencia--;;
				st_eruditos.rootsNode[2].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 8) {
			if (!st_eruditos.rootsNode[2].childs[0].comprado) {
				ph--;
				influencia--;
				st_eruditos.rootsNode[2].childs[0].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
		else if (id == 9) {
			if (!st_eruditos.rootsNode[2].childs[1].comprado) {
				ph--;
				influencia--;
				st_eruditos.rootsNode[2].childs[1].comprado = true;
				printf(u8"Comprando...");
				return true;
			}
			else {
				printf(u8"Este nodo ya habia sido comprado...");
				return false;
			}
		}
	}
	return false;


}





treeNode* SkillTreeManualSimulation::GetNode(int arbol, int numeroNodo)
{
	if (arbol == 1) {

	}
	else if (arbol == 2) {

	}

	return nullptr;
}

void SkillTreeManualSimulation::Mostrar() {
	std::srand(static_cast<unsigned int>(std::time(0)));  // Inicializa la semilla aleatoria
	int step = 0;
	predileccion = 0; // 1 para Guardias, 2 para Eruditos, 0 ninguno
	incremento = 1.4f;

	// Reiniciar simulación
	ResetSimulacion();

	// Simulaciones
	for (int i = 0; i < 10; i++) {  // Ejemplo de 10 pasos
		EntrenarDisciplina();  // El jugador elige y entrena
		MostrarStats();         // Mostrar las estadísticas actuales
		if (ph > 0) {
			GastarPuntoHabilidad();  // Gastar puntos de habilidad si tiene PH
		}
		step++;
	}

	// Guardar resultados
	std::ofstream file(u8"SkillTreeManualSimulation_Sim.csv");
	if (file.is_open()) {
		GuardarProgreso(file, 1, step);
		file.close();
	}
}