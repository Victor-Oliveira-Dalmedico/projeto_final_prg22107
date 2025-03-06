#include "gerador.h"
#include <QRandomGenerator>

Gerador::Gerador(int gridSize) : gridSize(gridSize), targetRow(0), targetCol(0) {
    gerarNovaCasa();
}

void Gerador::gerarNovaCasa() {
    targetRow = QRandomGenerator::global()->bounded(gridSize);
    targetCol = QRandomGenerator::global()->bounded(gridSize);
}

std::string Gerador::getInstrucao() const {
    return "Clique no quadrado (" + std::to_string(targetRow + 1) + ", " +
           std::to_string(targetCol + 1) + ")!";
}

std::string Gerador::getCasaAlvo() const {
    return std::to_string(targetRow) + "," + std::to_string(targetCol);
}
