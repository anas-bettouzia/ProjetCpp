#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "activite.h"
#include "statistiques.h"
#include <QPrinter>
#include <QPainter>
#include<QIntValidator>
#include<QSqlQuery>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0, 9999999, this));
    ui->tableView->setModel(A.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    int id=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString type=ui->type->text();
    QString datea=ui->date->text();
    activite A(id,nom,type,datea);
    bool test = A.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
                    QObject::tr("ACTIVITE Ajouter.\n"), QMessageBox::Ok);


}
}

void MainWindow::on_pushButton_Annuler_clicked()
{
    close();
}
void MainWindow::on_pushButton_annulersup_clicked()
{
    close();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
 activite A1 ;
 A1.setid(ui->lineEdit_supp->text().toInt());
 bool test = A1.supprimer(A1.getid());
 if(test)
 {
     QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                 QObject::tr("Suppression Terminer.\n"), QMessageBox::Ok);

}
}

void MainWindow::on_pushButton_Ajouter_edit_clicked()
{
    activite A;
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom_edit->text();
    QString type=ui->lineEdit_prenom_edit->text();
    QString datea=ui->lineEdit_edit_date->text();
    bool test=A.edit(id,nom,type,datea);

                    if(test)
                    {

                        QMessageBox::information(nullptr, QObject::tr("modifie une activite"),
                                          QObject::tr("activite  modifiée.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView->setModel(A.afficher());
                    }
                    else
                        QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                                    QObject::tr("Erreur !.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
                        ui->tableView->setModel(A.afficher());

}
void MainWindow::on_rech_clicked()
{
    QString val=ui->le_rech->text();
    QString option=ui->cb_rech_acti->currentText();
    if((val!="")&&(option=="id"))
{        ui->tableView->setModel(A.afficher_id(val));}
    else if((val!="")&&(option=="nom"))
    {
             ui->tableView->setModel(A.afficher_nom(val));
    } else if(option=="choisir")
    {
       ui->tableView->setModel(A.afficher());
    }
}

void MainWindow::on_pdf_push_clicked()
{
    QString id_cb=ui->pdf_c->text();
    activite * En ;
    En=A.readactivite(id_cb);
    QString id_string=QString::number(En->getid());
    QString nom_string = En->getnom();
    QString type_string = En->gettype();
    QString datea_string = En->getdatea();

     QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName("C:/Users/MSII/Desktop/pdf/"+id_string+".pdf");
                           QPainter painter;
                           if(! painter.begin(&printer))
                           { qWarning("failed to open file");  }
                            painter.setFont(QFont("Sitka Heading", 25));
                            painter.setPen(Qt::blue);
                            painter.drawText(340,100," ADPH ");
                            painter.setPen(Qt::black);
                            painter.drawText(175,50,"Information relative à l'enseignant");
                            painter.setPen(Qt::black);
                            painter.drawText(250,300,"Identifiant : " + id_string);
                            painter.drawText(250,400,"Nom : "+nom_string);
                            painter.drawText(250,500,"Type : "+type_string);
                            painter.drawText(250,600,"Date : " +datea_string);
                            painter.end();
}

void MainWindow::on_cb_tri_activated(const QString &arg1)
{
    QString choix=ui->cb_tri->currentText();
    ui->tableView->setModel(A.afficher_choix(choix));
}

void MainWindow::on_pb_stat_clicked()
{
    statistiques S;
     S.setModal(true);
     S.exec();
}
