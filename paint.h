#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QApplication>
#include <QColor>
#include <QPen>

QT_BEGIN_NAMESPACE
namespace Ui { class Paint; }
QT_END_NAMESPACE
class Paint : public QMainWindow
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint(); 
    Ui::Paint *ui;

private:
    QToolBar *toolbar;
    QAction *action, *trace, *clear;
    QWidget *area;
    QPen *pen;
    QPoint lastPoint;
    QColor current_color;
    QVector <QPoint> vector;



private slots:
    void penColor();
    void clearvector();

protected:
    void mousePressEvent(QMouseEvent *event) ;
    void mouseMoveEvent(QMouseEvent *event) ;
    void mouseReleaseEvent (QMouseEvent *event);
    void paintEvent(QPaintEvent *event) ;




};
#endif // PAINT_H
