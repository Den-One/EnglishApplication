#include "filemanager.h"

FileManager::FileManager() {

}

QString FileManager::getStatistic(QString fileName) {
    unsigned int pluses(0), minuses(0), notSure(0);
    QFile file(fileName);
    if (!file.exists())
        return "File not found";
    else {
        file.open(QIODevice::ReadOnly);
        while (!file.atEnd()) {
            QString fileLine = file.readLine();
            if (hasSign('+', fileLine))
                pluses++;
            else if (hasSign('-', fileLine))
                minuses++;
            else if (hasSign('#', fileLine))
                notSure++;
        }
        file.close();
    }

    // count persent
    int sum = pluses + minuses + notSure;
    double onePersent = (double)sum / 100;
    QString plusPersent = QString::number((double)pluses / onePersent, 'f', 2);
    QString minPersent = QString::number((double)minuses / onePersent, 'f', 2);
    QString notPersent = QString::number((double)notSure / onePersent, 'f', 2);

    // form result
    QString res = {};
    res += "To know:\t" + QString::number(pluses) + "\t" + plusPersent + " %\n";
    res += "Doesn't:\t" + QString::number(minuses) + "\t" + minPersent + " %\n";
    res += "Not sure:\t" + QString::number(notSure) + "\t" + notPersent + " %\n";
    return res;
}

int FileManager::countQuantity(QString fileName, char symb) {
    unsigned int signs = 0;
    QFile file(fileName);
    if (!file.exists())
        return 0;
    else {
        file.open(QIODevice::ReadOnly);
        while (!file.atEnd()) {
            QString fileLine = file.readLine();
            if (hasSign(symb, fileLine))
                signs++;
        }
        file.close();
    }
    return signs;
}

QString FileManager::getContent(QString fileName, char symb, unsigned int lines, unsigned int page) {
    QString result = "";
    // 0 - 9 (10, 0)
    // 10 - 19 (10, 1)
    // 20 - 29 (10, 2)
    unsigned int line(0), foundLines(0);
    QFile file(fileName);
    if (!file.exists())
        return "File not found";
    else {
        file.open(QIODevice::ReadOnly);
        while (!file.atEnd() && foundLines != lines * (page + 1)) {
            // пока мы не нашли число линий требуемое от lines
            // если мы нашли нужный результат и номер его нахождения входит в диапазон, то сохранить его
            QString currentLine = file.readLine();
            if (hasSign(symb, currentLine)) {
                qDebug() << currentLine;
                if ((foundLines >= lines * page) && foundLines <= (lines * page + lines))
                    result += currentLine;
                foundLines++;
            }
            line++;
        }
        file.close();
    }

    return result;
}

bool FileManager::hasSign(char sign, QString str) {
    return (str[0] == sign) ? true : false;
}
