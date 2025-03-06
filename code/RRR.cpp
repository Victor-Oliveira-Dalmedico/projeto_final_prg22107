#include "RRR.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

RRR::RRR(QWidget *parent)
    : QWidget(parent), crono(Crono::criaCrono(comparador)), gerador(nullptr), gridSize(0)
{
    label = new QLabel("<h2>RRR</h2>");
    instructionLabel = new QLabel("Aguardando tamanho da grade...");
    instructionLabel->setAlignment(Qt::AlignCenter);

    timerButton = new QPushButton("Start Timer");
    timerButton->setEnabled(false);
    QObject::connect(timerButton, &QPushButton::clicked, this, &RRR::toggleTimer);

    timerLabel = new QLabel("00:00:000");
    timerLabel->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &RRR::updateTimer);

    leftLayout = new QVBoxLayout();
    bottomLayout = new QHBoxLayout();
    gridLayout = new QGridLayout();
    gridWithLabelsLayout = new QHBoxLayout();
    gridAndBottomLayout = new QVBoxLayout();

    gridWithLabelsLayout->addLayout(leftLayout);
    gridWithLabelsLayout->addLayout(gridLayout);
    gridAndBottomLayout->addLayout(gridWithLabelsLayout);
    gridAndBottomLayout->addLayout(bottomLayout);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(timerButton);
    mainLayout->addWidget(timerLabel);
    mainLayout->addLayout(gridAndBottomLayout);

    setLayout(mainLayout);

    showSizeInputDialog();
}

RRR::~RRR() {
    delete gerador;
}

void RRR::showSizeInputDialog() {
    bool ok;
    int size = QInputDialog::getInt(this, "Tamanho da Grade",
                                    "Digite o tamanho da grade (ex.: 8 para 8x8):",
                                    8, 2, 10, 1, &ok);
    if (ok) {
        gridSize = size;
        gerador = new Gerador(gridSize);
        setupGameGrid(gridSize);
        setupCoordinateLabels(gridSize);
        instructionLabel->setText(QString::fromStdString(gerador->getInstrucao()));
        timerButton->setEnabled(true);
        startNewRound();
    } else {
        close();
    }
}

void RRR::setupGameGrid(int size) {
    gridButtons.resize(size);
    for (int i = 0; i < size; i++) {
        gridButtons[i].resize(size);
        for (int j = 0; j < size; j++) {
            gridButtons[i][j] = new Casa(i, j, this);
            gridLayout->addWidget(gridButtons[i][j], i, j);
            QObject::connect(gridButtons[i][j], &Casa::clickedWithCoords, this, &RRR::handleSquareClick);
        }
    }
}

void RRR::setupCoordinateLabels(int size) {
    for (QLabel* label : rowLabels) delete label;
    for (QLabel* label : colLabels) delete label;
    rowLabels.clear();
    colLabels.clear();

    for (int i = 0; i < size; i++) {
        QLabel *rowLabel = new QLabel(QString::number(size - i));
        rowLabel->setAlignment(Qt::AlignCenter);
        rowLabel->setFixedSize(30, 50);
        rowLabels.append(rowLabel);
        leftLayout->addWidget(rowLabel);
    }

    QLabel *emptyLabel = new QLabel("");
    emptyLabel->setFixedSize(30, 30);
    bottomLayout->addWidget(emptyLabel);

    for (int j = 0; j < size; j++) {
        QLabel *colLabel = new QLabel(QChar('A' + j));
        colLabel->setAlignment(Qt::AlignCenter);
        colLabel->setFixedSize(50, 30);
        colLabels.append(colLabel);
        bottomLayout->addWidget(colLabel);
    }
}

void RRR::startNewRound() {
    gerador->gerarNovaCasa();
    int displayRow = gridSize - gerador->getTargetRow();
    char colLetter = 'A' + gerador->getTargetCol();
    instructionLabel->setText(QString("Clique no quadrado %1%2!").arg(colLetter).arg(displayRow));
    comparador.Novacasa(gerador->getCasaAlvo());
}

void RRR::handleSquareClick(int row, int col) {
    if (!timer->isActive()) return;

    std::string attempt = std::to_string(row) + "," + std::to_string(col);
    comparador.Compara(attempt);

    if (row == gerador->getTargetRow() && col == gerador->getTargetCol()) {
        instructionLabel->setText("Correto! Nova rodada...");
        label->setText(QString("<h2>RRR - Acertos: %1</h2>").arg(comparador.getAcertos()));
        startNewRound();
    } else {
        instructionLabel->setText("Errado! Resultados em nova janela...");
        timer->stop();
        timerButton->setEnabled(true);
        timerButton->setText("Start Timer");

        // Criar uma nova janela de diálogo para resultados
        QDialog *resultDialog = new QDialog(this);
        resultDialog->setWindowTitle("Resultados");
        QVBoxLayout *dialogLayout = new QVBoxLayout(resultDialog);

        QLabel *acertosLabel = new QLabel(QString("Número de Acertos: %1").arg(comparador.getAcertos()));
        QLabel *tempoLabel = new QLabel(QString("Tempo Decorrido: %1 s").arg((comparador.getTempo()/1000)));
        QLabel *mediaLabel = new QLabel(QString("Média: %1 s/acerto").arg(comparador.getMedia(), 0, 'f', 2));
        QLabel *recordeLabel = new QLabel(QString("Recorde: %1 s/acerto").arg(comparador.getRecorde(), 0, 'f', 2));

        QPushButton *closeButton = new QPushButton("Fechar");
        QObject::connect(closeButton, &QPushButton::clicked, resultDialog, &QDialog::accept);

        dialogLayout->addWidget(acertosLabel);
        dialogLayout->addWidget(tempoLabel);
        dialogLayout->addWidget(mediaLabel);
        dialogLayout->addWidget(recordeLabel);
        dialogLayout->addWidget(closeButton);

        resultDialog->setLayout(dialogLayout);
        resultDialog->exec();  // Exibe a janela modal
    }
}

void RRR::toggleTimer() {
    if (crono.getTime() > 0 && !timer->isActive()) {
        crono.reset();
        crono.start();
        timer->start(10);
        timerButton->setText("Stop Timer");
        timerButton->setEnabled(false);
        label->setText(QString("<h2>RRR - Acertos: %1</h2>").arg(comparador.getAcertos()));
        startNewRound();
    } else if (timer->isActive()) {
        // Não permite parar manualmente
    } else {
        crono.start();
        timer->start(10);
        timerButton->setText("Stop Timer");
        timerButton->setEnabled(false);
        label->setText(QString("<h2>RRR - Acertos: %1</h2>").arg(comparador.getAcertos()));
    }
}

void RRR::updateTimer() {
    qint64 elapsed = crono.getTime();
    int minutes = (elapsed / 60000) % 60;
    int seconds = (elapsed / 1000) % 60;
    int milliseconds = elapsed % 1000;

    QString timeString = QString("%1:%2:%3")
                             .arg(minutes, 2, 10, QLatin1Char('0'))
                             .arg(seconds, 2, 10, QLatin1Char('0'))
                             .arg(milliseconds, 3, 10, QLatin1Char('0'));
    timerLabel->setText(timeString);
}
