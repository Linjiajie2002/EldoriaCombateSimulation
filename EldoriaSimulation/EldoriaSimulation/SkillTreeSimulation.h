#ifndef SkillTreeSimulation_H
#define SkillTreeSimulation_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Declaración de las clases y estructuras usadas en el código

enum class Dtipo { INVESTICACION, COMBATE, FABRICACION };

struct treeNode {
    std::string name;
    bool comprado;
    std::vector<treeNode> childs;
    int id = 0;
    treeNode(std::string n, bool c, int i) : name(n), comprado(c), id(i) {}
};

struct Disciplina {
    Dtipo tipo;
    float expActual;
    float expFinal;
    int vecesMejorada = 0;
};

class SkillTreeSimulation {
public:
    SkillTreeSimulation();
    ~SkillTreeSimulation();

    void Mostrar();
    void SaveScene();
    void Cleanup();
    void MostrarStats();
    void Step();
    void GuardarCSV(const std::vector<std::vector<int>>& results_step_by_step, int sim_num);
    void GuardarProgreso(std::ofstream& file, int sim_num, int step_num);
    void ResetSimulacion();
    void LimpiarArboles();

private:
    int influencia = 0;
    int ph = 0;
    float incremento = 1.2f;
    int predileccion; //1 guardas, 2 eruditos, 0 none

    Disciplina inv;
    Disciplina comb;
    Disciplina fab;

    struct {
        std::vector<treeNode> rootsNode;
    } st_guardias, st_eruditos;
};

#endif // SkillTreeSimulation_H
