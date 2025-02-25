#include "crono.h"

Crono* Crono::instance = nullptr;

Crono& Crono::criaCrono() {
    if (!instance) {
        instance = new Crono();
    }
    return *instance;
}

Crono::Crono() : tempoa(0), running(false) {}

void Crono::start() {
    if (!running) {
        elapsedTimer.start();
        running = true;
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
