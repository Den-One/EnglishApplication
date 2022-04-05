#ifndef WEBMANAGER_H
#define WEBMANAGER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class WebManager : public QObject {
Q_OBJECT
public:
    explicit WebManager(QObject *parent = nullptr);
    ~WebManager();

    void downloadHtmlRequest(QString foreignWord);

public slots:
    void replyFinished(QNetworkReply *reply);

signals:
    QString sendWebpageCode(QString pageCode);

private:
    QNetworkAccessManager *_manager;
    const QString _SOURCE_URL = "https://dictionary.cambridge.org/dictionary/english/";
    //QString _webpageCode; // reply result
};

#endif // WEBMANAGER_H
