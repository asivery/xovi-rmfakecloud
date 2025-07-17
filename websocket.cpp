#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QIODevice>
#include <QWebSocket>
#include "websocket-xovi.h"

extern "C" void override$_ZN10QWebSocket4openERK15QNetworkRequest(
    QWebSocket* self,
    const QNetworkRequest& req
) {
    const char* host = std::getenv("RMFAKECLOUD_HOST");

    // set new url
    QUrl newUrl = req.url();
    newUrl.setHost(QString(host));

    // create a new request, so we don't have to modify the original request
    QNetworkRequest newReq(req);
    newReq.setUrl(newUrl);

    // get original function signature
    using CreateFn = void*(*)(QWebSocket*,
                            const QNetworkRequest&);
    CreateFn orig = reinterpret_cast<CreateFn>(
        $_ZN10QWebSocket4openERK15QNetworkRequest
    );

    // call original function, and return the result
    orig(self, newReq);
}

extern "C" void _xovi_construct() {
    const char* host = std::getenv("RMFAKECLOUD_HOST");
    if (host == NULL) {
        qCritical() << "[rmfakecloud-websocket] Environment variable \"RMFAKECLOUD_HOST\" not set!";
        abort();
    }

    qDebug() << "Loading rmfakecloud-websocket by Tiebe. Using host " << host;
}