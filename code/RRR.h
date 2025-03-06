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
    void toggleTimer();
    void updateTimer();
    void handleSquareClick(int row, int col);

private:
    void setupGameGrid(int size);
    void startNewRound();
    void showSizeInputDialog();
    void setupCoordinateLabels(int size);

    QLabel *label;
    QLabel *instructionLabel;
    QPushButton *timerButton;
    QLabel *timerLabel;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *gridWithLabelsLayout;
    QVBoxLayout *gridAndBottomLayout;
    QVBoxLayout *leftLayout;
    QHBoxLayout *bottomLayout;

    QTimer *timer;
    Crono& crono;
    Comparador comparador;
    Gerador *gerador;

    int gridSize;
    QVector<QVector<Casa*>> gridButtons;
    QVector<QLabel*> rowLabels;
    QVector<QLabel*> colLabels;
};

#endif // RRR_H
