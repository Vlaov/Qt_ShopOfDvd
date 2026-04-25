#include "disk.h"

Disk::Disk(QString type, QString name, QString author, float price, QString note) : type(type), name(name),
    author(author), price(price), note(note) {}

Disk::Disk() : type(""), name(""), author(""), price(0.0), note("") {}

QString Disk::objectToString() const {
    QString stringPrice = QString::number(price, 'f', 2);
    QString resultingString;
    resultingString = type + "|" + name + "|" + author + "|" + stringPrice + "|" + note;
    return resultingString;
}

Disk Disk::stringToObject (QString line)  {
    Disk object;
    bool ok;
    QStringList parts = line.split('|');

    if (parts.size() < 5) {
        qDebug() << "Incorrect size of string";

    } else {
        object.type = parts[0].trimmed();
        if ((object.type).isEmpty()) object.type = "not indicated";

        object.name = parts[1].trimmed();
        if ((object.name).isEmpty()) object.name = "not indicated";

        object.author = parts[2].trimmed();
        if ((object.author).isEmpty()) object.author = "not indicated";

        object.price = parts[3].trimmed().toFloat(&ok);
        if (!ok || parts[3].trimmed() == "") {
            object.price = 0.0;
        }

        object.note = parts[4].trimmed();
        if ((object.note).isEmpty()) object.note = "not indicated";
    }
    return object;
}

QString Disk::toDisplayString() const{
    QString resultString;
    QString stringPrice = QString::number(price, 'f', 2);
    resultString = "Тип: " + type + "\n" + "Имя: " + name + "\n" + "Автор: " + author + "\n" + "Цена: " + stringPrice + "\n" + "Примечание: " + note;
    return resultString;
}


