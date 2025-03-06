#include "comparador.h"

Comparador::Comparador()
    : casag(""), tempo(0), acertos(0), media(0.0f), recorde(0.0f), crono(Crono::criaCrono(*this)) {}

void Comparador::Novacasa(const std::string& casa) {
    casag = casa;
}

void Comparador::Compara(const std::string& tentativa) {
    if (tentativa == casag) {
        acertos++;
    } else {
        Para();
    }
}

void Comparador::Para() {
    crono.stop();
    tempo = crono.getTime();
    CalculaMedia();
}

void Comparador::CalculaMedia() {
    if (acertos > 0) {
        media = static_cast<float>(tempo) / acertos / 1000.0f;  // Tempo em segundos por acerto
        if (media > 0 && (recorde == 0 || media < recorde)) {
            recorde = media;  // Atualiza o recorde se a média for válida e menor
        }
    } else {
        media = 0.0f;  // Caso não haja acertos, a média é 0
        // Não alteramos o recorde, mantemos o valor anterior (0 inicialmente)
    }
}

int Comparador::getAcertos() const {
    return acertos;
}

int Comparador::getTempo() const {
    return tempo;
}

float Comparador::getMedia() const {
    return media;
}

float Comparador::getRecorde() const {
    return recorde;
}

void Comparador::resetAcertos() {
    acertos = 0;
}
