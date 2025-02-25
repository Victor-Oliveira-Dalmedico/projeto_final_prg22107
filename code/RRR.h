#ifndef RRR_H
#define RRR_H

#include <QtWidgets>
#include <QTimer>
#include "crono.h"  // Inclui a classe Crono

class RRR : public QWidget
{
    Q_OBJECT

public:
    HelloQT(QWidget *parent = nullptr);
    ~HelloQT();

public slots:
    void toggleTimer();  // Slot para iniciar/parar o cronômetro
    void updateTimer();  // Slot para atualizar o tempo decorrido

private:
    QLabel *label;
    QPushButton *timerButton;  // Botão para iniciar/parar o cronômetro
    QLabel *timerLabel;        // Label para exibir o tempo decorrido

    QVBoxLayout *mainLayout;

    QTimer *timer;             // Timer para atualizar a interface
    Crono& crono;              // Referência para o cronômetro
};

#endif // RRR_H
