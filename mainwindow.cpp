#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"
#include "QVector"
#include "QFileDialog"
#include "QMessageBox"

bool lessthancode(CourseDetails *A, CourseDetails *B){return A->code < B->code;}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QXlsx::Document timeTable(":/table/table.xlsx");
    timeTable.selectSheet("Slot wise list of Courses");

    for(int iii = 3;timeTable.read(iii,2).toString()!="";iii++)
    {
        courses.push_back(new CourseDetails(timeTable.read(iii,1).toString(),timeTable.read(iii,2).toString(),timeTable.read(iii,4).toString()));
    }
    ui->setupUi(this);
    qSort(courses.begin(),courses.end(),lessthancode);
    int size = courses.size();
    for(int iii = 0; iii<size;iii++)
    {
        ui->comboBox->addItem(courses[iii]->code + " - " + courses[iii]->title,QVariant(iii));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    int current = ui->comboBox->currentIndex();
    QVariant curr = ui->comboBox->itemData(current);
    int iii = curr.toInt();
    if(selectedList.contains(courses[iii]->slot))
    {
        QMessageBox::information(this,"Alert","The slot "+courses[iii]->slot+" is already filled up.");
        return;
    }
    ui->listWidget->addItem(courses[iii]->code + " - " + courses[iii]->title);
    selectedList.insert(courses[iii]->slot,courses[iii]);
}

void MainWindow::on_clear_clicked()
{
    // clear all courses from listwidget and QMap
    ui->listWidget->clear();
    selectedList.clear();
}

void MainWindow::on_create_clicked()
{
    QXlsx::Document timeTable(":/table/table.xlsx");
    timeTable.selectSheet("Slot System");
    // cells from 3,2 to 15,10
    int i=1,j=1;
    for(;i<=16;i++)
    {
        j=1;
        for(;j<=10;j++)
        {
            QString slot = timeTable.read(i,j).toString();
            if(selectedList.contains(slot))
            {
                timeTable.write(i,j,selectedList.value(slot)->code,timeTable.cellAt(i,j)->format());
            }
            else
            {
                timeTable.write(i,j,timeTable.read(i,j),timeTable.cellAt(i,j)->format());
                if(slot=="8"||slot=="9"||slot=="1"||slot=="2"||slot=="3"||slot=="4")
                {
                    continue;
                }
                if(slot.size()>1)
                {

                }
                else
                if(slot.size()==1&&QString(slot.toInt())!=slot)
                {
                    timeTable.write(i,j,"",timeTable.cellAt(i,j)->format());
                }
            }
        }
    }

    QStringList list = timeTable.sheetNames();
    timeTable.deleteSheet(list[1]);
    timeTable.deleteSheet(list[2]);
    // Ask for filename
    QString url = QFileDialog::getSaveFileName(0,"Save your time table",QString(),".xlsx");
    // Save the file with given name
    timeTable.saveAs(url);
}

void MainWindow::on_del_clicked()
{

    int current = ui->listWidget->currentRow();
    if(current==-1)
        return;
    QString currentString = ui->listWidget->item(current)->text();
    QMapIterator<QString, CourseDetails*> i(selectedList);
    while (i.hasNext()) {
        i.next();
        if(i.value()->code + " - " + i.value()->title == currentString)
        {
            selectedList.remove(i.key());
        }
    }
    delete ui->listWidget->currentItem();
}
