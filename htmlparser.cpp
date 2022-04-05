#include "htmlparser.h"

HtmlParser::HtmlParser() {

}

QString HtmlParser::pars(QString str) {
    QString result = "";
    unsigned int size = std::strlen(str.toStdString().c_str());
    unsigned int start(0), end(0), i(0), j(0);

    for (i = 0; i < size; ++i) {
        if (str[i] == '>') {
            start = i + 1;
            break;
        }
    }

    while (str[start] == ' ')
        start++;

    for (i = start; i < size; ++i) {
        if (str[i] == '<') {
            end = i - 1;
            break;
        }
    }

    for (j = start; j <= end; j++)
        result += str[j];

    return result;
}
