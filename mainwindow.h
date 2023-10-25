#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sketch_window.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SketchWindow* s_win;

private:
    Ui::MainWindow *ui;
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void status_update();

public slots:
    void file_submitter();
    void slot_width();
    void slot_color(QString);
    void slot_spin_width(QString);
    void onReceiveChildSignal();
    void slot_hovered();
    void slot_statusbar(QString);
};
#endif // MAINWINDOW_H
