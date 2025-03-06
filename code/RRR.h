#ifndef RRR_H
#define RRR_H

#include <QtWidgets>
#include <QTimer>
#include <QVector>
#include "crono.h"
#include "comparador.h"
#include "casa.h"
#include "gerador.h"

class RRR : public QWidget
{
    Q_OBJECT

public:
    RRR(QWidget *parent = nullptr);
    ~RRR();

public slots:
    void toggleTimer();  // Slot para iniciar/parar o cronômetro
    void updateTimer();  // Slot para atualizar o tempo decorrido
    void handleSquareClick(int row, int col);  // Slot para cliques nos quadrados

private:
    void setupGameGrid(int size);  // Configura a grade com tamanho dinâmico
    void startNewRound();          // Inicia uma nova rodada
    void showSizeInputDialog();    // Exibe diálogo para entrada do tamanho

    QLabel *label;
    QLabel *instructionLabel;
    QPushButton *timerButton;
    QLabel *timerLabel;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;

    QTimer *timer;
    Crono& crono;
    Comparador comparador;
    Gerador *gerador;  // Ponteiro para permitir inicialização posterior

    int gridSize;  // Tamanho da grade definido pelo usuário
    QVector<QVector<Casa*>> gridButtons;  // Matriz dinâmica de botões
};

#endif // RRR_H
