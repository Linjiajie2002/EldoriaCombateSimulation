#include "SkillTreeSimulation.h"
#include <fstream>

SkillTreeSimulation::SkillTreeSimulation()
{

}

SkillTreeSimulation::~SkillTreeSimulation()
{
}

void SkillTreeSimulation::Mostrar()
{

	std::srand(static_cast<unsigned int>(std::time(0)));


	int numeroSimulaciones = 1;
	int numeroPasos = 100;
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



	st_guardias.rootsNode.push_back(treeNode("Mejora combate", false, 1));
	st_guardias.rootsNode.back().childs.push_back(treeNode("Curar", false, 2));
	st_guardias.rootsNode.back().childs.push_back(treeNode("Aumentar velocidad ataque", false, 3));
	st_guardias.rootsNode.back().childs.push_back(treeNode("Tacticas de combate", false, 4));
	st_guardias.rootsNode.push_back(treeNode("Forja", false, 5));
	st_guardias.rootsNode.back().childs.push_back(treeNode("Trampas", false, 6));
	st_guardias.rootsNode.push_back(treeNode("Recoleccion", false, 7));
	st_guardias.rootsNode.push_back(treeNode("Dominio del entorno", false, 8));
	st_guardias.rootsNode.back().childs.push_back(treeNode("Carisma", false, 9));



	st_eruditos.rootsNode.push_back(treeNode("Mejora arcana", false, 1));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Curacion", false, 2));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Vision arcana", false, 3));
	st_eruditos.rootsNode.push_back(treeNode("Alquimia", false, 4));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Control temporal", false, 5));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Clon de trabajo", false, 6));
	st_eruditos.rootsNode.push_back(treeNode("Analisis", false, 7));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Comunicacion con animales", false, 8));
	st_eruditos.rootsNode.back().childs.push_back(treeNode("Perspicacia", false, 9));








	/*printf("\n\n\n\n ---------- Model ---------- \n\n");

	MostrarStats();

	for (int i = 0; i < 1000; i++) {
		Step();
	}
	MostrarStats();


	printf("\n\n\n\n\n\n\n");*/



	std::ofstream file;

	std::string fileName = "SkillTreeSimulation_Sim" + std::to_string(numeroSimulaciones) + "_Step" + std::to_string(numeroPasos) + "_pred" + std::to_string(predileccion) + "_incr" + std::to_string(incremento) + ".csv";

	file.open(fileName);

	// Escribir encabezado del archivo CSV
	if (file.is_open()) {
		file << "Simulacion,Paso,Influencia,PH,Exp_Investigacion,Exp_Combate,Exp_Fabricacion\n";
	}
	else {
		std::cout << "No se pudo abrir el archivo CSV." << std::endl;
		return;
	}

	// Realizamos 100 simulaciones y guardamos los resultados
	for (int sim = 0; sim < numeroSimulaciones; ++sim) {
		// Resetear el estado inicial
		ResetSimulacion();
		printf("\n\n\n\n ---------- SIMULACION: %d ---------- \n", sim);
		MostrarStats();

		// Realizamos la simulación paso a paso
		for (int step = 0; step < numeroPasos; ++step) {
			// Guardar el progreso en este paso
			GuardarProgreso(file, sim + 1, step + 1);  // Se guarda el paso actual (step + 1) y la simulación (sim + 1)

			// Realizar el paso
			Step();
		}
		MostrarStats();
	}

	file.close();
	printf("\nSimulaciones completas. Resultados guardados en '%s'.\n", fileName.c_str());


}








void SkillTreeSimulation::SaveScene()
{




}

void SkillTreeSimulation::Cleanup()
{
}

void SkillTreeSimulation::MostrarStats()
{

	printf("\n ---------- Stats ---------- \n");

	printf("\n\n ---Influencia: %d, ", influencia);
	if (influencia == 0) {
		printf("Tienes una influencia neutral");
	}
	else if (influencia > 0) {
		printf("Tienes una influencia hacia los guardias");
	}
	else {
		printf("Tienes una influencia hacia los eruditos");
	}

	printf("\n\n ---PH: %d", ph);

	printf("\n\n ---Disciplinas: \n");
	printf("Investigacion: Puntos exp: %f, Puntos final: %f \n", inv.expActual, inv.expFinal);
	printf("Combate: Puntos exp: %f, Puntos final: %f \n", comb.expActual, comb.expFinal);
	printf("Fabricacion: Puntos exp: %f, Puntos final: %f \n", fab.expActual, fab.expFinal);

	printf("\n\n ---Arboles de habilidad: \n");
	printf("Arbol de guardias: \n");

	for (int i = 0; i < st_guardias.rootsNode.size(); i++) {
		if (st_guardias.rootsNode.at(i).comprado) {
			printf(" | ");
			printf(st_guardias.rootsNode.at(i).name.c_str());

			for (int j = 0; j < st_guardias.rootsNode.at(i).childs.size(); j++) {
				if (st_guardias.rootsNode.at(i).childs.at(j).comprado) {
					printf(" | ");
					printf(st_guardias.rootsNode.at(i).childs.at(j).name.c_str());
				}
			}
		}
	}

	printf("\nArbol de eruditos: \n");

	for (int i = 0; i < st_eruditos.rootsNode.size(); i++) {
		if (st_eruditos.rootsNode.at(i).comprado) {
			printf(" | ");
			printf(st_eruditos.rootsNode.at(i).name.c_str());

			for (int j = 0; j < st_eruditos.rootsNode.at(i).childs.size(); j++) {
				if (st_eruditos.rootsNode.at(i).childs.at(j).comprado) {
					printf(" | ");
					printf(st_eruditos.rootsNode.at(i).childs.at(j).name.c_str());
				}
			}
		}
	}

	printf("\n");


}

void SkillTreeSimulation::Step()
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

void SkillTreeSimulation::GuardarProgreso(std::ofstream& file, int sim_num, int step_num)
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


void SkillTreeSimulation::ResetSimulacion()
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

void SkillTreeSimulation::LimpiarArboles()
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
