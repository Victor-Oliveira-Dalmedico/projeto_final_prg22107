#include "comparador.h"

Comparador::Comparador()
    : casag(""), tempo(0), acertos(0), crono(Crono::criaCrono()) {}

void Comparador::Novacasa(const std::string& casa) {
    casag = casa;
}

void Comparador::Compara(const std::string& tentativa) {
    if (tentativa == casag) {
        acertos++;
    } else {
        Para(); // Chama o método privado para parar e armazenar tempo
    }
}

void Comparador::Para() {
    crono.stop(); // Para o cronômetro
    tempo = crono.getTime(); // Armazena o tempo atual
}

int Comparador::getAcertos() const {
    return acertos;
}

int Comparador::getTempo() const {
    return tempo;
}
