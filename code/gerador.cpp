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
    char colLetter = 'A' + targetCol;  // Converte a coluna para letra (A, B, C, ...)
    return "Clique no quadrado " + std::string(1, colLetter) + std::to_string(targetRow + 1) + "!";
}

std::string Gerador::getCasaAlvo() const {
    char colLetter = 'A' + targetCol;  // Converte a coluna para letra
    return std::to_string(targetRow) + "," + std::to_string(targetCol);  // Mantém o formato interno como números
}
