#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QIODevice>
#include "xovi.h"

extern "C" QNetworkReply* override$_ZN21QNetworkAccessManager13createRequestENS_9OperationERK15QNetworkRequestP9QIODevice(
    QNetworkAccessManager* self,
    QNetworkAccessManager::Operation op,
    const QNetworkRequest& req,
    QIODevice* outgoingData
) {
    const char* host = std::getenv("RMFAKECLOUD_HOST");

    // set new url
    QUrl newUrl = req.url();
    newUrl.setHost(QString(host));

    // create a new request, so we don't have to modify the original request
    QNetworkRequest newReq(req);
    newReq.setUrl(newUrl);

    // get original function signature    
    using CreateFn = QNetworkReply*(*)(QNetworkAccessManager*,
                            QNetworkAccessManager::Operation,
                            const QNetworkRequest&,
                            QIODevice*);
    CreateFn orig = reinterpret_cast<CreateFn>(
        $_ZN21QNetworkAccessManager13createRequestENS_9OperationERK15QNetworkRequestP9QIODevice
    );

    // call original function, and return the result
    return orig(self, op, newReq, outgoingData);
}

extern "C" void _xovi_construct() {
    const char* host = std::getenv("RMFAKECLOUD_HOST");
    if (host == NULL) {
        qCritical() << "[rmfakecloud] Environment variable \"RMFAKECLOUD_HOST\" not set!";
        abort();
    }

    qDebug() << "Loading rmfakecloud by Tiebe. Using host " << 
}