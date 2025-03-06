#include "crono.h"
#include "comparador.h"

Crono* Crono::instance = nullptr;

Crono& Crono::criaCrono(Comparador& comparador) {
    if (!instance) {
        instance = new Crono(comparador);
    }
    return *instance;
}

Crono::Crono(Comparador& comparador) : tempoa(0), running(false), comparador(comparador) {}

void Crono::start() {
    if (!running) {
        elapsedTimer.start();
        running = true;
        comparador.resetAcertos();  // Reseta os acertos ao iniciar o cronômetro
    }
}

void Crono::stop() {
    if (running) {
        tempoa += elapsedTimer.elapsed();
        running = false;
    }
}

void Crono::reset() {
    tempoa = 0;
    running = false;
}

qint64 Crono::getTime() const {
    if (running) {
        return tempoa + elapsedTimer.elapsed();
    }
    return tempoa;
}
