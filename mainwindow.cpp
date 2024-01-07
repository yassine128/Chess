/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#include <QLabel>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImageReader>
#include <QFile>
#include "kingError.h"
#include "Roi.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

affichage::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chessboard = std::make_shared<LogiqueGame::Chessboard>();
    //chessboard->creationPieces();
    drawSidePanel();
    drawBoard();
}


void affichage::MainWindow::drawSidePanel() {
    QFont font;
    font.setFamily("Roboto");
    font.setPointSize(10);
    font.setWeight(QFont::Bold);

    QLabel* background = new QLabel(this);
    background->setGeometry(600, 0, 300, 600);
    background->setStyleSheet("background-color: rgb(48, 46, 43)");


    QWidget* container = new QWidget(this);
    container->setGeometry(600, 50, 200, 300);
    setCentralWidget(container);

    QPushButton* button = new QPushButton("PLAY", container);
    connect(button, SIGNAL(clicked()), this, SLOT(startGame()));
    button->setGeometry(650, 200, 200, 50);
    button->setFont(font);
    button->setStyleSheet(" \
    QPushButton { \
        background-color: #87a55b; \
        border-radius: 5px; \
        border: none; \
        color: #feeeee; \
        font-family: sans-serif; \
        font-size: 20px; \
        padding: 5px 15px; \
        text-align: center; \
        text-decoration: none; \
        } \
        QPushButton:hover { \
            background-color: #a0c075; \
        } \
        QPushButton:pressed { \
            background-color: #6b8a42; \
        } \
    ");

    comboBox = new QComboBox(container);
    comboBox->addItem("Topalov vs. J. Polgar, 2008");
    comboBox->addItem("Philidor, 1749");
    comboBox->setGeometry(650, 300, 200, 50);
    comboBox->setFont(font);
    comboBox->setStyleSheet(" \
    QComboBox { \
        background-color: #87a55b; \
        border: 1px solid #5b7d3a; \
        border-radius: 5px; \
        color: #feeeee; \
        font-family: sans-serif; \
        font-size: 20px; \
        padding: 5px 15px; \
    } \
    QComboBox::drop-down { \
        border: none; \
    } \
    QComboBox::down-arrow { \
        image: url(./Images/arrow.png); \
        width: 30px; \
        right: 10px; \
        height: 30px; \
    } \
    QComboBox QAbstractItemView { \
        background-color: #a0c075; \
        selection-background-color: #6b8a42; \
        color: #feeeee; \
        font-family: sans-serif; \
        font-size: 20px; \
    } \
");

    tourText = new QLabel(container);
    QString tour = "Turn: " + QString::fromStdString(chessboard->getTours());
    tourText->setText(tour);
    font.setPointSize(20);
    tourText->setFont(font);
    tourText->setStyleSheet("color: rgb(255, 255, 255);");
    tourText->setGeometry(680, 100, 150, 30);
}

void affichage::MainWindow::startGame() {
    chessboard->clearBoard();
    chessboard->creationPieces(comboBox->currentText().toStdString());
    updateLabels();
}

void affichage::MainWindow::erasePrediction() {
    // On efface le overlay
    for (int i = 0; i < labels.size(); i++) {
        for (int j = 0; j < labels[i].size(); j++) {
            ClickableLabel* label = qobject_cast<ClickableLabel*>(labels[i][j]);
            if (label) {
                QWidget* overlay = label->findChild<QWidget*>("overlay");
                if (overlay) {
                    overlay->deleteLater();
                }
            }
        }
    }
}

void affichage::MainWindow::displayPrediction(ClickableLabel& label) {
    // On rajoute le overlay sur le dessus de la case pour montrer les choix disponibles
    // Montre les deux cases selectionne
    this->setWindowTitle(QString::fromStdString(chessboard->getTours()));

    if (!m_selectedLabel) {
        //if (label.s_->getPiece()->getCouleur() == chessboard->getTours()) { 
        std::vector<std::pair<int, int>> choix = chessboard->mouvementsPossibles(label.s_->getPiece());
        chessboard->prevChoix = choix;
        //choix.push_back(std::make_pair(label.s_->getPos().first, label.s_->getPos().second));
        //choix.push_back(std::make_pair(label.s_->getPos().first, label.s_->getPos().second + 1));
        // Affiche un overlay

        for (int i = 0; i < choix.size(); i++) {
        //std::cout << choix[i].first << std::endl;
        QWidget *overlay = new QWidget(labels[choix[i].first][choix[i].second]);
        overlay->setObjectName("overlay"); 
        overlay->setGeometry(0, 0, 75, 75);
        overlay->setStyleSheet("background-color: rgba(51, 153, 255, 75);");
        overlay->show();
    }

        m_selectedLabel = &label;
    } else {
        erasePrediction();
        chessboard->changePosition(m_selectedLabel->s_->getPiece(), label.s_->getPos(), chessboard->prevChoix); // On change la position de la piece

        updateLabels(); // On doit update le text des labels
        m_selectedLabel = nullptr;
        //chessboard->findAllEnemyMoves(chessboard->getTours());
    }
}

void affichage::MainWindow::updateLabels() {
        tourText->setText("Turn: " + QString::fromStdString(chessboard->getTours()));
        for (int i = 0; i < labels.size(); i++) {
            for (int j = 0; j < labels[i].size(); j++) {
                if (chessboard->getBoardSquare(i, j).getPiece() != nullptr) {
                    //std::cout << chessboard->getBoardSquare(i, j).getPiece()->getUrlImage() << std::endl;
                    QPixmap pixmap(QString::fromStdString(chessboard->getBoardSquare(i, j).getPiece()->getUrlImage()));
                    labels[i][j]->setPixmap(pixmap.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
                else {
                    QPixmap pixmap(QPixmap(QString::fromStdString("./Images/empty.png")));
                    labels[i][j]->setPixmap(pixmap.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
            }
        }
    }

void affichage::MainWindow::drawBoard() {
        for (int i = 0; i < 8; i++) {
            std::vector<ClickableLabel*> tempLabels;
            for (int j = 0; j < 8; j++) {
                // Dessiner la case pour le point
                Square& s = chessboard->getBoardSquare(i, j);
                ClickableLabel* label = new ClickableLabel(this);
                label->setSquare(s);

                if (chessboard->getBoardSquare(i, j).getPiece() != nullptr) {
                    QPixmap pixmap(QPixmap(QString::fromStdString(chessboard->getBoardSquare(i, j).getPiece()->getUrlImage())));
                    label->setPixmap(pixmap.scaled(75, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }

                tempLabels.push_back(label);
                if ((label->s_->getPos().first + label->s_->getPos().second) % 2 == 0)
                    label->setStyleSheet("background-color: rgb(125, 148, 93);");
                else
                    label->setStyleSheet("background-color: rgb(235, 236, 211)");
                label->setGeometry(label->s_->getPos().first * 75, label->s_->getPos().second * 75, 75, 75);
                connect(label, &ClickableLabel::clicked, this, [this, label]() {
                    displayPrediction(*label);
                    });
                //connect(label, &ClickableLabel::released, this, &MainWindow::erasePrediction);
            }
            labels.push_back(tempLabels);
        }
    }

affichage::MainWindow::~MainWindow()
{
    delete ui;
}


