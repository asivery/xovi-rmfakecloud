#pragma once
#include <QSettings>
#include <QFile>
#include <QVariant>
#include <iostream>
#define NAME "rmfakecloud"
static QString newRMFCHostName = NULL;
static int newRMFCPort;

extern "C" void _xovi_construct() {
    char *configRoot = Environment->getExtensionDirectory(NAME);

    // Load the config file and read the host.
    QString configFile(configRoot);
    configFile += "config.conf";
    QSettings extensionConfig(configFile, QSettings::IniFormat);
    QString newRMFCHostNameQStr = extensionConfig.value("host").toString();
    if (newRMFCHostNameQStr == "") {
        std::cerr << "[" << NAME << "] No host defined in the config file!" << std::endl;
        abort();
    }
    std::cerr << "[" << NAME << "] New host set to: " << newRMFCHostNameQStr.toStdString() << std::endl;
    newRMFCHostName = newRMFCHostNameQStr;
    bool ok;
    newRMFCPort = extensionConfig.value("port").toInt(&ok);
    if(!ok) newRMFCPort = -1; // Default.

    // Load our CA to the global cert store.
    QString caCertFileName(configRoot);
    caCertFileName += "ca.pem";
    QFile caFile(caCertFileName);
    if (caFile.open(QIODevice::ReadOnly)) {
        const QByteArray caBytes = caFile.readAll();
        const QSslCertificate certificate(caBytes);
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        auto globalCerts = config.caCertificates();
        globalCerts.append(certificate);
        config.setCaCertificates(globalCerts);
        QSslConfiguration::setDefaultConfiguration(config);
    } else {
        std::cerr << "[" << NAME << "] Failed to open CA file!" << std::endl;
    }

    free(configRoot);
}

static inline bool shouldPatchURL(const QString &host) {
    return QString(R""""(
        hwr-production-dot-remarkable-production.appspot.com
        service-manager-production-dot-remarkable-production.appspot.com
        local.appspot.com
        my.remarkable.com
        ping.remarkable.com
        internal.cloud.remarkable.com
        eu.tectonic.remarkable.com
        backtrace-proxy.cloud.remarkable.engineering
        dev.ping.remarkable.com
        dev.tectonic.remarkable.com
        dev.internal.cloud.remarkable.com
        eu.internal.tctn.cloud.remarkable.com
        webapp-prod.cloud.remarkable.engineering
    )"""").contains(host);
}
