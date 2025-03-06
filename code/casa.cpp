#include "casa.h"

Casa::Casa(int row, int col, QWidget *parent)
    : QPushButton(parent), row(row), col(col)
{
    setFixedSize(50, 50);  // Tamanho fixo para o botão
    connect(this, &QPushButton::clicked, this, &Casa::emitCoords);
}

void Casa::emitCoords() {
    emit clickedWithCoords(row, col);
}
