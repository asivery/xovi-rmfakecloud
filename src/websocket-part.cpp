#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QIODevice>
#include <QWebSocket>
#include "../xovi-websocket.h"
#include "commons.cpp"

extern "C" void override$_ZN10QWebSocket4openERK15QNetworkRequest(
    QWebSocket* self,
    const QNetworkRequest& req
) {
    // set new url
    QUrl newUrl = req.url();
    newUrl.setHost(newRMFCHostName);
    newUrl.setPort(newRMFCPort);

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
