#include "activite.h"
#include "statistiques.h"
#include<QSqlQuery>
#include<QDebug>
#include<QObject>
#include<QDate>
activite::activite()
{
id=0; nom=" ";type=" ";
}

activite::activite(int id,QString nom,QString type,QString datea)
{this->id=id;this->nom=nom;this->type=type;this->datea=datea;}

                    /* ##########     SET     ########## */

int activite::getid(){return id;}
QString activite::getnom(){return nom;}
QString activite::gettype(){return type;}
QString activite::getdatea(){return datea;}


                    /* ##########     SET     ########## */

void activite::setid(int id){this->id=id;}
void activite::setnom(QString nom){this->nom=nom;}
void activite::settype(QString type){this->type=type;}
void activite::setdatea(QString datea){this->datea=datea;}


bool activite::ajouter(){
    QSqlQuery query;
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO ACTIVITES (id, nom, type, datea) "
                        "VALUES (:id, :forename, :type, :datea)");
          query.bindValue(":id", id);
          query.bindValue(":forename", nom);
          query.bindValue(":type", type);
          query.bindValue(":date", datea);
    return query.exec();
}

QSqlQueryModel* activite::afficher(){

              QSqlQueryModel* model=new QSqlQueryModel();
                   model->setQuery("SELECT * FROM ACTIVITES");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("datea"));

              return model;
}
bool activite::supprimer(int id)
{ QSqlQuery query;
    query.prepare("Delete from ACTIVITES where id=:id");
     query.bindValue(0,id);

    query.exec();
}
bool activite::edit(int id ,QString nom,QString type,QString datea)
          {
              QSqlQuery query;
              query.prepare("UPDATE ACTIVITES SET id= :id,nom= :nom,type = :type,datea=:datea  WHERE id= :id ");
              query.bindValue(":id",id);
              query.bindValue(":nom",nom);
              query.bindValue(":type",type);
             query.bindValue(":datea",datea);
              return    query.exec();
          }
// rech
QSqlQueryModel *activite::afficher_id(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM ACTIVITES where id= '"+ch+"' ");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
          return model ;
}
QSqlQueryModel *activite::afficher_nom(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM ACTIVITES where nom= '"+ch+"' ");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
          return model ;
}

//pdf
QSqlQueryModel * activite:: getAllId(){
    QSqlQueryModel * model =new QSqlQueryModel();
            model->setQuery("select id from activites ");
            return model ;
}

activite* activite::readactivite (QString val)
{
 QSqlQuery query;
    query.prepare("Select * FROM activites where id='"+val+"'");
        if(query.exec())
        {     while(query.next())
            {
             setid(query.value(0).toInt());
             setnom(query.value(1).toString());
             settype(query.value(2).toString());
             setdatea(query.value(3).toString());
            }
        }
     return this;
}

//tri

QSqlQueryModel *activite:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

     if(choix=="nom croissants")
    {
        model->setQuery("SELECT * FROM activites  ORDER BY nom ASC ;");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
    }
     else if(choix=="nom decroissants")
     {
         model->setQuery("SELECT * FROM activites  ORDER BY nom DESC;");
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
     }else if(choix=="id croissants")
     {
         model->setQuery("SELECT * FROM activites  ORDER BY id ASC;");
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
     }else if(choix=="id decroissant")
     {
         model->setQuery("SELECT * FROM activites  ORDER BY id DESC;");
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
     }else if (choix=="choisir")
    {
        model->setQuery("SELECT * FROM activites ");
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("datea"));
    }


    return model;
}

//stat

int activite::statistique1(){
    QSqlQuery query;
            int count=0 ;
            QSqlQuery requete("select * from activites where type like 'jeux'") ;
            while(requete.next())
            {
                    count++ ;
            }

        return count ;
}

int activite::statistique2(){
    QSqlQuery query;
            int count=0 ;
            QSqlQuery requete("select * from activites where type like 'creative'") ;
            while(requete.next())
            {
                    count++ ;
            }

        return count ;
}
