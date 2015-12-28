#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMap"
#include "QVector"

namespace Ui {
class MainWindow;
}

class CourseDetails
{
public:
    CourseDetails();
    CourseDetails(QString newcode,QString newtitle,QString newslot){
        code = newcode;
        title = newtitle;
        slot = newslot;
    }

    QString code;
    QString title;
    QString slot;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QVector<CourseDetails*> courses;
    QMap<QString,CourseDetails*> selectedList;
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_clear_clicked();

    void on_create_clicked();

    void on_del_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
