#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QIODevice>
#include "../xovi-networkaccess.h"
#include "commons.cpp"

extern "C" QNetworkReply* override$_ZN21QNetworkAccessManager13createRequestENS_9OperationERK15QNetworkRequestP9QIODevice(
    QNetworkAccessManager* self,
    QNetworkAccessManager::Operation op,
    const QNetworkRequest& req,
    QIODevice* outgoingData
) {
    using CreateFn = QNetworkReply*(*)(QNetworkAccessManager*,
                        QNetworkAccessManager::Operation,
                        const QNetworkRequest&,
                        QIODevice*);
    CreateFn orig = reinterpret_cast<CreateFn>(
        $_ZN21QNetworkAccessManager13createRequestENS_9OperationERK15QNetworkRequestP9QIODevice
    );

    if(shouldPatchURL(req.url().host())) {
        // set new url
        QUrl newUrl = req.url();
        newUrl.setHost(newRMFCHostName);
        newUrl.setPort(newRMFCPort);

        // create a new request, so we don't have to modify the original request
        QNetworkRequest newReq(req);
        newReq.setUrl(newUrl);

        // call original function, and return the result
        return orig(self, op, newReq, outgoingData);
    } else {
        return orig(self, op, req, outgoingData);
    }
}
