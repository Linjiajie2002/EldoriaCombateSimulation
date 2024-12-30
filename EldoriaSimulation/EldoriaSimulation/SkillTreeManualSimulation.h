#ifndef SkillTreeManualSimulation_H
#define SkillTreeManualSimulation_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "SkillTreeSimulation.h"

// Declaración de las clases y estructuras usadas en el código

//enum class Dtipo { INVESTICACION, COMBATE, FABRICACION };
//
//struct treeNode {
//    std::string name;
//    bool comprado;
//    std::vector<treeNode> childs;
//    treeNode(std::string n, bool c) : name(n), comprado(c) {}
//};
//
//struct Disciplina {
//    Dtipo tipo;
//    float expActual;
//    float expFinal;
//    int vecesMejorada = 0;
//};

class SkillTreeManualSimulation {
public:
    SkillTreeManualSimulation();
    ~SkillTreeManualSimulation();

    void InicializarArboles();

    void Mostrar();
    void SaveScene();
    void Cleanup();
    void MostrarStats();
    void Step();
    void AumentarExp(Disciplina& disciplina);
    void ComprarPH();
    void GuardarCSV(const std::vector<std::vector<int>>& results_step_by_step, int sim_num);
    void GuardarProgreso(std::ofstream& file, int sim_num, int step_num);
    void ResetSimulacion();
    void LimpiarArboles();

    void PrintTree(treeNode node, int depth);

    void PrintTreeVisual(const treeNode& node, const std::string& prefix = "");

    void SetColor(int color);

    void EntrenarDisciplina();

    void VerificarMaxExp(Disciplina& disciplina);

    void GastarPuntoHabilidad();
    

    //void MostrarArbol(const treeNode& tree);

    bool GastarPuntoEnNodo(int arbol, int id);
    treeNode* GetNode(int arbol, int numeroNodo);

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

#endif // SkillTreeManualSimulation_H
