#ifndef SKETCH_WINDOW_H
#define SKETCH_WINDOW_H

#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QDebug>

#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <algorithm>

class SketchWindow : public QWidget
{
    Q_OBJECT
    QImage image;

    QPoint from;
    bool draw = false;

    int pen_width = 5;
    QColor pen_color = Qt::black;

    QAction* ac_color1;
    QAction* ac_color2;
    QAction* ac_color3;

    QAction* ac_width5;
    QAction* ac_width10;
    QAction* ac_width20;

signals:
    void childEventSignal();

public:
    SketchWindow(QWidget *parent = nullptr)
        : QWidget(parent), image(300, 300, QImage::Format_RGB32)
    {
        image.fill(qRgb(255, 255, 255));

        ac_color1 = new QAction("빨강");
        ac_color2 = new QAction("파란");
        ac_color3 = new QAction("녹색");

        ac_width5 = new QAction("두께 5");
        ac_width10 = new QAction("두께 10");
        ac_width20 = new QAction("두께 20");

        //        QAction* ac2 = new QAction("Exit");


        // 2. connect signal-slot
        connect( ac_color1, &QAction::triggered, this, &SketchWindow::slot_action_red);
        connect( ac_color2, &QAction::triggered, this, &SketchWindow::slot_action_blue);
        connect( ac_color3, &QAction::triggered, this, &SketchWindow::slot_action_green);

        connect( ac_width5, &QAction::triggered, this, &SketchWindow::slot_action_width5);
        connect( ac_width10, &QAction::triggered, this, &SketchWindow::slot_action_width10);
        connect( ac_width20, &QAction::triggered, this, &SketchWindow::slot_action_width20);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter g(this);

        QRect rc = event->rect();


        g.drawImage(rc, image, rc);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        qDebug() << __func__;
        if ( event->button() == Qt::LeftButton)
        {
            draw = true;
            from = event->pos();
        }

    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if ( draw )
        {
            QPoint to = event->pos();

            QPainter g(&image);

            g.setPen(QPen(pen_color, pen_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            g.drawLine(from, to);

            // update();


            int rad = (pen_width / 2) + 2;
            update(QRect(from, to).normalized().adjusted(-rad, -rad, +rad, +rad));

            from = to;
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if ( event->button() == Qt::LeftButton)
        {
            draw = false;
        }
    }



    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        if (width() > image.width() || height() > image.height()) {
            int newWidth = qMax(width() + 128, image.width());
            int newHeight = qMax(height() + 128, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
        }
    }

    void resizeImage(QImage *image, const QSize &newSize)
    {
        if (image->size() == newSize)
            return;

        QImage newImage(newSize, QImage::Format_RGB32);
        newImage.fill(qRgb(255, 255, 255));

        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), *image);
        *image = newImage;
    }

    //User Interface
public:
    void set_width(QString s_width)
    {
        pen_width= s_width.toInt();
    }

    QString get_width()
    {
        QString str = QString::number(pen_width);
        return str;
    }



    QString get_color()
    {
        QString str = "검정";
        if (pen_color == Qt::black)
            str = "검정";
        else if (pen_color == Qt::red)
            str = "빨강";
        else if (pen_color == Qt::blue)
            str = "파란";
        else if (pen_color == Qt::green)
            str = "녹색";

        return str;
    }

    void set_color(QString s_color)
    {

        if (!s_color.compare("검정"))
            pen_color = Qt::black;
        else if (!s_color.compare("빨강"))
            pen_color = Qt::red;
        else if (!s_color.compare("파란"))
            pen_color = Qt::blue;
        else if (!s_color.compare("녹색"))
            pen_color = Qt::green;
    }

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event)
    {
        qDebug() <<__func__<< event->globalPos();
        QMenu menu(this);

        menu.addAction(ac_color1);
        menu.addAction(ac_color2);
        menu.addAction(ac_color3);

        menu.addSeparator();

        menu.addAction(ac_width5);
        menu.addAction(ac_width10);
        menu.addAction(ac_width20);
        //        menu.addAction(s_ac2);

        menu.exec(event->globalPos());

        emit childEventSignal();
    }

public:
    void slot_action_red()
    {
        qDebug() << __func__;
        pen_color = Qt::red;
    }

    void slot_action_green()
    {
        qDebug() << __func__;
        pen_color = Qt::green;
    }

    void slot_action_blue()
    {
        qDebug() << __func__;
        pen_color = Qt::blue;
    }

    void slot_action_width5()
    {
        qDebug() << __func__;
        pen_width =5;
    }

    void slot_action_width10()
    {
        qDebug() << __func__;
        pen_width = 10;
    }

    void slot_action_width20()
    {
        qDebug() << __func__;
        pen_width = 20;
    }
};
#endif // SKETCH_WINDOW_H
