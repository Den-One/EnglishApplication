#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <algorithm>

#include <QString>
#include <QFile>
#include <QDebug>

class FileManager {
public:
    FileManager();

    QString getStatistic(QString fileName);
    QString getContent(QString fileName, char symb, unsigned int lines, unsigned int page);
    int countQuantity(QString fileName, char symb);
private:
    bool hasSign(char sign, QString str);

};

#endif // FILEMANAGER_H
