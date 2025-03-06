#ifndef CASA_H
#define CASA_H

#include <QtWidgets>

class Casa : public QPushButton {
    Q_OBJECT

public:
    Casa(int row, int col, QWidget *parent = nullptr);
    int getRow() const { return row; }
    int getCol() const { return col; }

signals:
    void clickedWithCoords(int row, int col);  // Sinal emitido com as coordenadas

private slots:
    void emitCoords();  // Slot interno para emitir o sinal com coordenadas

private:
    int row;
    int col;
};

#endif // CASA_H
