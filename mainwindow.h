#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QApplication>

#include "filemanager.h"
#include "webmanager.h"
#include "htmlparser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void printPageInfo(QString webpageCode);

private slots:
    void on_unlearned_clicked();
    void on_notSure_clicked();
    void on_known_clicked();
    void on_show_clicked();
    void on_left_clicked();
    void on_right_clicked();



    void on_getHtml_clicked();

private:
    QString getPagesRange();


private:
    Ui::MainWindow *ui;
    std::unique_ptr <FileManager>_fileManager;
    unsigned int _page;
    char _sign;
    QString _fileName;

    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString result;

    WebManager* _webManager;
    int _nLines;

};
#endif // MAINWINDOW_H
