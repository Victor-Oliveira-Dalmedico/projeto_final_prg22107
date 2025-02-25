#include "helloqt.h"

HelloQT::HelloQT(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("<h2>HelloQT</h2>");

    // Botão do cronômetro
    timerButton = new QPushButton("Start Timer");
    QObject::connect(timerButton, SIGNAL(clicked()),
                     this, SLOT(toggleTimer()));

    // Label do cronômetro
    timerLabel = new QLabel("00:00:000");
    timerLabel->setAlignment(Qt::AlignCenter);

    // Timer para atualizar a interface
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()),
                     this, SLOT(updateTimer()));

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);

    // Adiciona o botão e o label do cronômetro ao layout
    mainLayout->addWidget(timerButton);
    mainLayout->addWidget(timerLabel);

    setLayout(mainLayout);
}

HelloQT::~HelloQT() {}

void HelloQT::toggleTimer() {
    if (timer->isActive()) {
        timer->stop();  // Para o timer
        timerButton->setText("Start Timer");
        // Não reseta o label aqui, o tempo permanece visível
    } else {
        elapsedTimer.start();  // Inicia a medição do tempo
        timer->start(10);  // Atualiza a interface a cada 10 ms
        timerButton->setText("Stop Timer");
    }
}

void HelloQT::updateTimer() {
    // Obtém o tempo decorrido em milissegundos
    qint64 elapsed = elapsedTimer.elapsed();

    int minutes = (elapsed / 60000) % 60;  // 1 minuto = 60000 ms
    int seconds = (elapsed / 1000) % 60;   // 1 segundo = 1000 ms
    int milliseconds = elapsed % 1000;     // Milissegundos restantes

    // Formata a string como MM:SS:mmm
    QString timeString = QString("%1:%2:%3")
                             .arg(minutes, 2, 10, QLatin1Char('0'))  // Minutos (2 dígitos)
                             .arg(seconds, 2, 10, QLatin1Char('0'))  // Segundos (2 dígitos)
                             .arg(milliseconds, 3, 10, QLatin1Char('0'));  // Milissegundos (3 dígitos)

    timerLabel->setText(timeString);
}
