#ifndef DISK_H
#define DISK_H

#include <QString>
#include <QStringList>
#include <QDebug>

class Disk {
private:
    QString type;
    QString name;
    QString author;
    float price;
    QString note;

public:
    Disk(QString type, QString name, QString author, float price, QString note);
    Disk();

    QString objectToString() const;
    static Disk stringToObject (QString);
    QString toDisplayString() const;

    QString getType() const {
        return type;
    }
    QString getName() const {
        return name;
    }
    QString getAuthor() const {
        return author;
    }
    float getPrice() const {
        return price;
    }
    QString getNote() const {
        return note;
    }

    void setType(QString typeFromUser)  {
        type = typeFromUser;
    }
    void setName(QString nameFromUser)  {
        name = nameFromUser;
    }
    void setAuthor(QString authorFromUser)  {
        author = authorFromUser;
    }
    void setPrice(float priceFromUser)  {
        price = priceFromUser;
    }
    void setNote(QString noteFromUser)  {
        note = noteFromUser;
    }

};


#endif // DISK_H
