#ifndef COMPARADOR_H
#define COMPARADOR_H

#include <string>
#include "crono.h"

class Comparador {
public:
    Comparador();
    void Novacasa(const std::string& casa);
    void Compara(const std::string& tentativa);
    int getAcertos() const;
    int getTempo() const;
    float getMedia() const;    // Novo getter para média
    float getRecorde() const;  // Novo getter para recorde
    void resetAcertos();

private:
    void Para();
    void CalculaMedia();  // Novo método para calcular média e atualizar recorde

    std::string casag;
    int tempo;
    int acertos;
    float media;    // Média de tempo por acerto (ms/acerto)
    float recorde;  // Melhor média (menor tempo por acerto)
    Crono& crono;
};

#endif // COMPARADOR_H
