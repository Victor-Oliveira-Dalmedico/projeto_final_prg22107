#ifndef GERADOR_H
#define GERADOR_H

#include <string>

class Gerador {
public:
    Gerador(int gridSize = 4);  // Construtor com tamanho da grade configurável
    void gerarNovaCasa();       // Gera uma nova casa alvo
    std::string getInstrucao() const;  // Retorna a instrução como string
    std::string getCasaAlvo() const;   // Retorna a casa alvo como string (ex: "1,2")
    int getTargetRow() const { return targetRow; }
    int getTargetCol() const { return targetCol; }

private:
    int gridSize;
    int targetRow;
    int targetCol;
};

#endif // GERADOR_H
