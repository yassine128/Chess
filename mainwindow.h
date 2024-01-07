/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chessboard.h"
#include "clickablelabel.h"
#include <vector>
#include <QComboBox>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace affichage {
    class MainWindow : public QMainWindow

    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();
        void drawBoard();
        void updateLabels();
        void drawSidePanel(); 
    public slots:
        void displayPrediction(ClickableLabel& label);
        void erasePrediction();
        void startGame();
    private:
        QComboBox* comboBox;
        QLabel* tourText; 
        Ui::MainWindow* ui;
        std::shared_ptr<LogiqueGame::Chessboard> chessboard;
        ClickableLabel* m_selectedLabel;
        std::vector<std::vector<ClickableLabel*>> labels;
    };
}

#endif // MAINWINDOW_H
