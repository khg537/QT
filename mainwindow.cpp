#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketch_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QMenuBar* menubar = menuBar();

    ui->setupUi(this);
    QMenu* menu = ui->menubar->addMenu("파일");


    //    menubar->addMenu(menu);

    QAction* ac1 = new QAction("제출자");
    QAction* ac2 = new QAction("종료");

    menu->addAction(ac1);
    menu->addSeparator();
    menu->addAction(ac2);

    QString str = ui->lineEdit->text();

    ui->combo->addItem("검정");
    ui->combo->addItem("빨강");
    ui->combo->addItem("파란");
    ui->combo->addItem("녹색");

    ui->spin->setValue(5);
    ui->spin->setRange(0, 100);
    ui->spin->setSingleStep(1);

    QString s_color = ui->combo->currentText();


    qDebug() << "현재색상" << s_color;

    connect(ac1, &QAction::triggered,
                this, &MainWindow::file_submitter);

    connect(ac2, &QAction::triggered,
            this, &MainWindow::close);

    //Child signal
    connect(ui->widget, SIGNAL(childEventSignal()), this, SLOT(onReceiveChildSignal()));

    setWindowTitle("Sketch Project 219185");
    status_update();
}


void MainWindow::file_submitter()
{
    qDebug() << __func__;
    QMessageBox msgBox;

    msgBox.setWindowTitle("제출자");
    msgBox.setText("hyungoo.kang@lge.com");

    status_update();
    msgBox.exec();
}

void MainWindow::slot_width()
{

    QString s_width = ui->lineEdit->text();
    qDebug() << __func__ <<": "<<s_width;
    ui->widget->set_width(s_width);

    status_update();
}

void MainWindow::slot_color(QString color)
{

    qDebug() << __func__ <<": "<<color;
    ui->widget->set_color(color);

    status_update();
}

void MainWindow::slot_spin_width(QString width)
{

    qDebug() << __func__ <<": "<<width;
    ui->widget->set_width(width);

    status_update();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    qDebug()<< "Window context";
    status_update();
}

void MainWindow::status_update()
{
    QString str = "색상 : " + ui->widget->get_color() + ",  ""두께 :" + ui->widget->get_width();

                    statusBar()->showMessage(str);

    ui->combo->setCurrentText(ui->widget->get_color());
    ui->lineEdit->setText(ui->widget->get_width());
    ui->spin->setValue(ui->widget->get_width().toInt());
    ui->verticalSlider->setValue(ui->widget->get_width().toInt());
}

void MainWindow::slot_hovered()
{
    qDebug() << __func__;

}

void MainWindow::slot_statusbar(QString str)
{
    qDebug() << __func__<< statusBar()->currentMessage();

    if (str =="") status_update();

}

void MainWindow::onReceiveChildSignal()
{
    qDebug() << __func__;
    status_update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

