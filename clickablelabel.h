/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

// Ce code provient de https://wiki.qt.io/Clickable_QLabel

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QMouseEvent>
#include "chessboard.h"

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();
    void setSquare(Square& s);
    Square* s_;
signals:
    void clicked();
    void released();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
};


#endif // CLICKABLELABEL_H
