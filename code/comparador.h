#ifndef COMPARADOR_H
#define COMPARADOR_H

#include <string>
#include "crono.h"

class Comparador {
public:
    Comparador();
    void Novacasa(const std::string& casa); // Define a casa atual
    void Compara(const std::string& tentativa); // Compara e atualiza acertos/tempo
    int getAcertos() const; // Retorna número de acertos
    int getTempo() const; // Retorna o tempo armazenado

private:
    void Para(); // Para o cronômetro e armazena o tempo

    std::string casag;
    int tempo;
    int acertos;
    Crono& crono; // Referência ao cronômetro singleton
};

#endif // COMPARADOR_H
