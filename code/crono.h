#ifndef CRONO_H
#define CRONO_H

#include <QElapsedTimer>

class Comparador;  // Declaração forward para evitar dependência circular

class Crono {
public:
    static Crono& criaCrono(Comparador& comparador);  // Método estático ajustado para receber Comparador
    void start();
    void stop();
    qint64 getTime() const;
    void reset();

private:
    Crono(Comparador& comparador);  // Construtor privado ajustado
    QElapsedTimer elapsedTimer;
    qint64 tempoa;
    bool running;
    Comparador& comparador;  // Referência ao Comparador para chamar resetAcertos

    static Crono* instance;
};

#endif // CRONO_H
