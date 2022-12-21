#include "paint.h"
#include "ui_paint.h"
#include <QToolBar>
#include <QPainter>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>


Paint::Paint(QWidget *parent)
    : QMainWindow(parent)
{
                    //TOOLBAR
    QToolBar *toolbar = addToolBar("main");

    QAction *quit = new QAction("Выход", this);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    toolbar->addAction(quit);

    QAction *colorbutton = new QAction("Выберите цвет", this);
    connect(colorbutton, &QAction::triggered, this, &Paint::penColor);
    toolbar->addAction(colorbutton);

    trace = new QAction("Сплошная линия", this);
    toolbar->addAction(trace);
    trace->setCheckable(true);

    clear = new QAction("Очистить", this);
    connect(clear, &QAction::triggered, this, &Paint::clearvector);
    toolbar->addAction(clear);


                    //WIDGET
    setWindowTitle("PAINT");
    area = new QWidget;
    setCentralWidget(area);

                //PEN SETTINGS
    current_color = QColor(0,0,0,255);
    pen = new QPen;
    pen->setColor(QColor(0,0,0,255));
    pen->setWidth(7);
    pen->setStyle(Qt::DashLine);
    pen->setCapStyle(Qt::RoundCap);
    pen->setJoinStyle(Qt::RoundJoin);
}

void Paint::clearvector()
{
    vector.clear();
    repaint();
}

void Paint::penColor()
{
    QColor newcol = QColorDialog::getColor();
    pen->setColor(newcol);
    current_color = newcol;
}


void Paint::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    pen->setColor(current_color);
    painter.setPen(*pen);

    if (vector.size()>1)
        for (size_t i = 0;i < vector.size()-1;i++)
        {
            if (vector[i] != QPoint(0,0)&&vector[i+1] != QPoint(0,0))
                painter.drawLine(vector[i],vector[i+1]);
            else
                continue;
        }

}




void Paint::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {

            if(trace->isChecked())
            {
                if (vector.size() != 0)
                if (vector[vector.size()-1] != QPoint(0,0))
                   vector.push_back(QPoint(0,0));
            }

        lastPoint = event->pos();
        vector.push_back(lastPoint);
        repaint();
    }
    else if(event->button() == Qt::RightButton)
    {
       vector.pop_back();
       repaint();
    }


}

void Paint::mouseMoveEvent(QMouseEvent *event)
{
    if (trace->isChecked())
    {
        vector.push_back(event->pos());
    }
    else
    {
       vector[vector.size() -1] = event->pos();
    }

    repaint();

}
void Paint::mouseReleaseEvent(QMouseEvent *event)
{

    if (trace->isChecked() && event->button() != Qt::RightButton)
        vector.push_back(QPoint(0,0));

}



Paint::~Paint()
{
    delete ui;
}

