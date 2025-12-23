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

extern "C" void override$_ZN15QNetworkRequest6setUrlERK4QUrl(void *self, const QUrl &url) {
    using SetUrl = void(*)(void *, const QUrl &);
    SetUrl orig = reinterpret_cast<SetUrl>(
        $_ZN15QNetworkRequest6setUrlERK4QUrl
    );
    if(shouldPatchURL(url.host())) {
        std::cout << "SeturlPart: Set " << url.host().toStdString() << " to " << newRMFCHostName.toStdString() << std::endl;
        QUrl newUrl(url);
        newUrl.setHost(newRMFCHostName);
        newUrl.setPort(newRMFCPort);
        orig(self, newUrl);
    } else {
        orig(self, url);
    }
}
