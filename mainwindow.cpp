#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "validate.h"
#include "format.h"
#include "jsonConverter.h"
#include "compress.h"
//#include "decompress.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QVector>
#include<QDir>

static QString path;
static QString path_correct;
static QString path_format;
static QString path_json;
static QString path_compress;
static QString path_decompress;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_select_clicked()
{
    QString filter = "*.xml ;; *.json ;; *.txt";
    path = QFileDialog::getOpenFileName(this,"select xml file.","C://" );
    QFile input_file(path);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){return;}
    QTextStream ts(&input_file);
    QString data = ts.readAll();
    ui->textEdit1->setText(data);
    input_file.close();
}


void MainWindow::on_validate_clicked()
{
    if(is_valid(path.toStdString())){
        QString valid = "File is valid.";
        ui->textEdit_2->setText(valid);
    } else {
        QString valid = "File is NOT valid.";
        ui->textEdit_2->setText(valid);
        string s = path.toStdString();
        ui->textEdit_2->append("-----------------------------");
        ui->textEdit_2->append("There are errors in the following lines.");
        vector<vector<string>> v = get_correction(path.toStdString());
      //  vector<string> v1 = v.at(2);
      //  vector<int> v1 = get_errored_lines(path.toStdString());
        for(int i = 0; i < (int)v.size(); i++){

           // QString qstr = QString::fromStdString(v1.at(i));
//QString::number(v1[i])
            ui->textEdit_2->append(QString::fromStdString(v[i][2]));
        }
//        str += QString::number(z[i]);
//        for(int i = 0; i < v.size() ; i++){
//            QString st = QString::fromStdString(v[i]);
//            ui->textEdit_2->append(st);
//        }
    }
}


void MainWindow::on_correct_clicked()
{
    QFile input_file(path);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){return;}
    path_correct = QFileDialog::getSaveFileName(this,"Enter file name to save.","C://");
    create_correct_xml(path.toStdString(), path_correct.toStdString());
    QFile output_file(path_correct);
    if(!output_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);}
    QTextStream ts(&output_file);
    QString data = ts.readAll();
    ui->textEdit_2->setText(data);
    input_file.close();
//    output_file.close();
}


void MainWindow::on_json_clicked()
{
    QFile input_file(path);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);;}
    path_json = QFileDialog::getSaveFileName(this,"Enter file name to save.","C://");
    convert_to_json(path.toStdString(), path_json.toStdString());
    QFile output_file(path_json);
    if(!output_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);}
    QTextStream ts(&output_file);
    QString data = ts.readAll();
    ui->textEdit_2->setText(data);
    input_file.close();
//    output_file.close();
}


void MainWindow::on_format_clicked()
{
    QFile input_file(path);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){return;}
    path_format = QFileDialog::getSaveFileName(this,"Enter file name to save.","C://");
    Formating(path.toStdString(), path_format.toStdString());
    QFile output_file(path_format);
    if(!output_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);
    }
    QTextStream ts(&output_file);
    QString data = ts.readAll();
    ui->textEdit_2->setText(data);
    input_file.close();
//    output_file.close();
}


void MainWindow::on_compress_clicked()
{
    QFile input_file(path);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){return;}
    path_compress = QFileDialog::getSaveFileName(this,"Enter file name to save.","C://");
    Compressing(path.toStdString(), path_compress.toStdString());
    QFile output_file(path_compress);
    if(!output_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);}
    QTextStream ts(&output_file);
    QString data = ts.readAll();
    ui->textEdit_2->setText(data);
    input_file.close();
    output_file.close();
}


void MainWindow::on_decompress_clicked()
{
    QFile input_file(path_compress);
    if(!input_file.open(QFile::ReadOnly | QFile::Text)){return;}
    path_decompress = QFileDialog::getSaveFileName(this,"Enter file name to save.","C://");
    Decompress(path.toStdString() , path_decompress.toStdString());
    QFile output_file(path_decompress);
    if(!output_file.open(QFile::ReadOnly | QFile::Text)){
        QString valid = "file cannot be open.";
        ui->textEdit_2->setText(valid);
    }
    QTextStream ts(&output_file);
    QString data = ts.readAll();
    ui->textEdit_2->setText(data);
    input_file.close();
    output_file.close();
}


void MainWindow::on_pushButton_clicked()
{
    QDir::setCurrent("C:\\Users\\esraa\\Desktop\\projectalgo");

    system("dot -Tpng -O ap.dot");

    QPixmap p ("C:\\Users\\esraa\\Desktop\\projectalgo\\ap.dot.png");

    ui->label_3->setPixmap(p);

}


void MainWindow::on_gragh_clicked()
{
    QDir::setCurrent("C:\\Users\\esraa\\Desktop\\projectalgo");

    system("dot -Tpng -O ap.dot");

    QPixmap p ("C:\\Users\\esraa\\Desktop\\projectalgo\\ap.dot.png");

    ui->label_3->setPixmap(p);

}

