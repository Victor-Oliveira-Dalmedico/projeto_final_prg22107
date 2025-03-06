#ifndef GERADOR_H
#define GERADOR_H

#include <string>

class Gerador {
public:
    Gerador(int gridSize = 4);
    void gerarNovaCasa();
    std::string getInstrucao() const;
    std::string getCasaAlvo() const;
    int getTargetRow() const { return targetRow; }
    int getTargetCol() const { return targetCol; }

private:
    int gridSize;
    int targetRow;
    int targetCol;
};

#endif // GERADOR_H
