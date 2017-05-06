#include <QApplication>
#include <QTime>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "gameboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("PacMan");
    a.setApplicationDisplayName("PacMan");

    qsrand((uint) QTime::currentTime().msec());
    GameBoard* gameBoard = new GameBoard(0, 0, 800, 600);
    QGraphicsView* view = new QGraphicsView(gameBoard);
//    QGraphicsView::fitInView(gameBoard);
    view->setMinimumWidth(800);
    view->setMinimumHeight(600);
    view->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();

    /* main ->
     * new GameBoard : QGraphicsScene
     * new QGraphicsView(scene)
     */

    // GameBoard : QGraphicsScene (mozna jako Rect w scenie, jesli planuje sie zeby bylo cos poza plansza)
    // sciana - podejscie z marginesem (niewidoczny obiekt i wykrywanie kolizji)
    // pacman - wycinek kola - musi ruszac pyszczkiem
    // duszki - wielokaty o zmieniajacej sie liczbie katow
    // skalowanie okienka -> wspolrzedne logiczne + QGraphicsView::fitInView()
    // zamiast timera lepiej uzyc animacji (konieczne dopiero w drugim projekcie)
    // animacje musza byc plynne -> wobec tego jak wykryc koniecznosc zmiany ruchu przy natrafieniu sciany? wykrywanie kolizji
    // okno musi sie skalowac (ale scena juz nie)
    // zawijanie - zaimplementowac
    return a.exec();
}
