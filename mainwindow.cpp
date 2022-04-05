#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    _fileName = "C:\\Users\\pcuser\\source\\";
    _fileName += "repos\\EnglishAnalyzer\\EnglishAnalyzer\\1-100.txt";
    _fileManager = std::make_unique<FileManager>();

    _webManager = new WebManager();
    connect(_webManager, &WebManager::sendWebpageCode, this, &MainWindow::printPageInfo);
    _nLines = 14;

    HtmlParser parser;
    QString s = "<h1> Hello world </h1>";
    parser.pars(s);
}

MainWindow::~MainWindow() {
    disconnect(_webManager, &WebManager::sendWebpageCode, this, &MainWindow::printPageInfo);

    delete ui;
    delete _webManager;
}

void MainWindow::printPageInfo(QString webpageCode) {
    QString descriptionDiv = "def ddef_d db";

    QString result = "";

    int startIndex = webpageCode.toStdString().find(descriptionDiv.toStdString());
    QString otherPagePart = "";
    for (int i = startIndex; i < webpageCode.size(); ++i) {
        otherPagePart += webpageCode[i];
    }

    HtmlParser parser;
    result = parser.pars(otherPagePart);

    unsigned int finishIndex = otherPagePart.toStdString().find("</div>");

    /*for (unsigned int i = 0; i < finishIndex; ++i) {
        i = otherPagePart.toStdString().find("title=");
        i += 7;
        while (otherPagePart[i] != '\"') {
            result += otherPagePart[i];
            i++;
        }
        result += " ";

        QString s;
        for (int j = i; j < otherPagePart.size(); ++j) {
            s += otherPagePart[j];
        }
        otherPagePart = s;
        finishIndex = otherPagePart.toStdString().find("</div>");
    }/*
    /*TEGS TO ALLABORATE
        * class="def ddef_d db" - class of meaning
        * class = "def-body ddef_b" - class of examples
    */

    ui->textEdit->setText(result);
}

QString MainWindow::getPagesRange() {
    QString result = "";
    result += QString::number(_page);
    result += " - ";
    result += QString::number(_fileManager->countQuantity(_fileName, _sign) / _nLines);

    return result;
}

void MainWindow::on_unlearned_clicked() {
    _sign = '-';
    _page = 0;

    QString content = _fileManager->getContent(_fileName, _sign, _nLines, _page);
    ui->textEdit->setText(content);
    ui->pagesRange->setText(getPagesRange());
    ui->pagesRange->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_notSure_clicked() {
    _sign = '#';
    _page = 0;

    QString content = _fileManager->getContent(_fileName, _sign, _nLines, _page);
    ui->textEdit->setText(content);
    ui->pagesRange->setText(getPagesRange());
    ui->pagesRange->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_known_clicked() {
    _sign = '+';
    _page = 0;

    QString content = _fileManager->getContent(_fileName, _sign, _nLines, _page);
    ui->textEdit->setText(content);
    ui->pagesRange->setText(getPagesRange());
    ui->pagesRange->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_show_clicked() {
    QString persentMessage = _fileManager->getStatistic(_fileName);
    ui->textEdit->setText(persentMessage);
}

void MainWindow::on_left_clicked() {
    if (_page != 0)
        _page--;

    QString content = _fileManager->getContent(_fileName, _sign, _nLines, _page);
    ui->textEdit->setText(content);
    ui->pagesRange->setText(getPagesRange());
    ui->pagesRange->setAlignment(Qt::AlignCenter);

}

void MainWindow::on_right_clicked() {
    if (_page < (_fileManager->countQuantity(_fileName, _sign) / _nLines))
        _page++;

    QString content = _fileManager->getContent(_fileName, _sign, _nLines, _page);
    ui->textEdit->setText(content);
    ui->pagesRange->setText(getPagesRange());
    ui->pagesRange->setAlignment(Qt::AlignCenter);
    //QRequest req(QUrl("https://dictionary.cambridge.org/dictionary/english/mine"));
}

void MainWindow::on_getHtml_clicked() {
    QString input = ui->lineEdit->text();
    _webManager->downloadHtmlRequest("milk");
    //request.setUrl(QUrl("https://dictionary.cambridge.org/dictionary/english/mine"));
    //manager->get(request);
}

