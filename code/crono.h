#ifndef CRONO_H
#define CRONO_H

#include <QElapsedTimer>

class Crono {
public:
    static Crono& criaCrono();  // Método estático para criar/obter a instância única

    void start();               // Inicia o cronômetro
    void stop();                // Para o cronômetro
    qint64 getTime() const;     // Retorna o tempo atual em milissegundos
    void reset();               // Reseta o cronômetro

private:
    Crono();  // Construtor privado para garantir que a classe seja um singleton
    QElapsedTimer elapsedTimer; // Medidor de tempo decorrido
    qint64 tempoa;              // Tempo atual em milissegundos
    bool running;               // Indica se o cronômetro está em execução

    static Crono* instance;     // Ponteiro para a instância única
};

#endif // CRONO_H
