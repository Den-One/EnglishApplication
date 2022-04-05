#include <QDebug>

#include "webmanager.h"

WebManager::WebManager(QObject *parent): QObject(parent) {
    _manager = new QNetworkAccessManager();

    connect(_manager, &QNetworkAccessManager::finished,
            this, &WebManager::replyFinished);
}

WebManager::~WebManager() {
    disconnect(_manager, &QNetworkAccessManager::finished,
               this, &WebManager::replyFinished);

    delete _manager;
}

void WebManager::downloadHtmlRequest(QString foreignWord) {
    QString pagePath = _SOURCE_URL + foreignWord;
    _manager->get(QNetworkRequest(QUrl(pagePath)));
}

void WebManager::replyFinished(QNetworkReply *reply) {
    QString webpageCode = "";
    while (!reply->atEnd()) {
        QString answer = reply->readLine();
        webpageCode += answer;
        qDebug() << answer;
    }

    emit sendWebpageCode(webpageCode);
}


