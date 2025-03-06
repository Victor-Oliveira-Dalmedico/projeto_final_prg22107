#include "RRR.h"

RRR::RRR(QWidget *parent)
    : QWidget(parent), crono(Crono::criaCrono()), gerador(nullptr), gridSize(0)
{
    label = new QLabel("<h2>RRR</h2>");
    instructionLabel = new QLabel("Aguardando tamanho da grade...");
    instructionLabel->setAlignment(Qt::AlignCenter);

    timerButton = new QPushButton("Start Timer");
    timerButton->setEnabled(false);  // Desativado até a grade ser criada
    QObject::connect(timerButton, &QPushButton::clicked, this, &RRR::toggleTimer);

    timerLabel = new QLabel("00:00:000");
    timerLabel->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &RRR::updateTimer);

    gridLayout = new QGridLayout();

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(timerButton);
    mainLayout->addWidget(timerLabel);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);

    showSizeInputDialog();
}

RRR::~RRR() {
    delete gerador;
}

void RRR::showSizeInputDialog() {
    bool ok;
    int size = QInputDialog::getInt(this, "Tamanho da Grade",
                                    "Digite o tamanho da grade (ex.: 4 para 4x4):",
                                    4, 2, 10, 1, &ok);
    if (ok) {
        gridSize = size;
        gerador = new Gerador(gridSize);
        setupGameGrid(gridSize);
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

void RRR::startNewRound() {
    gerador->gerarNovaCasa();
    instructionLabel->setText(QString::fromStdString(gerador->getInstrucao()));
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
        instructionLabel->setText("Errado! Jogo terminado.");
        timer->stop();  // Para o timer da interface
        timerButton->setEnabled(false);  // Desativa o botão até reiniciar
    }
}

void RRR::toggleTimer() {
    if (crono.getTime() > 0 && !timer->isActive()) {
        crono.reset();
        crono.start();
        timer->start(10);
        timerButton->setText("Stop Timer");
        startNewRound();  // Reinicia o jogo ao reiniciar o timer
        timerButton->setEnabled(true);
    } else if (timer->isActive()) {
        timer->stop();  // Apenas para o timer da interface
        timerButton->setText("Start Timer");
    } else {
        crono.start();
        timer->start(10);
        timerButton->setText("Stop Timer");
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
