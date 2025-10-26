#define NAME "rmfakecloud"
#include <QSettings>
#include <QFile>
#include <QVariant>
#include <iostream>
#include "../xovi-tokenstore.h"

extern "C" {
    static QSettings *tokenStorage;
    void _xovi_construct() {
        char *configRoot = Environment->getExtensionDirectory(NAME);

        // Prepare the token storage (leak object)
        QString tokenFile(configRoot);
        tokenFile += "tokens.conf";
        tokenStorage = new QSettings(tokenFile, QSettings::IniFormat);

        free(configRoot);
    }

    static inline bool checkKey(void **that, QAnyStringView &key) {
        if(key == "devicetoken" || key == "UserToken") {
            *that = tokenStorage;
            return true;
        }
        return false;
    }

    QVariant override$_ZNK9QSettings5valueE14QAnyStringView(void *that, QAnyStringView key) {
        if(checkKey(&that, key)) tokenStorage->sync();
        return $_ZNK9QSettings5valueE14QAnyStringView(that, key);
    }

    QVariant override$_ZNK9QSettings5valueE14QAnyStringViewRK8QVariant(void *that, QAnyStringView key, const QVariant &defaultValue) {
        if(checkKey(&that, key)) tokenStorage->sync();
        return $_ZNK9QSettings5valueE14QAnyStringViewRK8QVariant(that, key, defaultValue);
    }

    void override$_ZN9QSettings8setValueE14QAnyStringViewRK8QVariant(void *that, QAnyStringView key, const QVariant &value) {
        bool sync = checkKey(&that, key);
        $_ZN9QSettings8setValueE14QAnyStringViewRK8QVariant(that, key, value);
        if(sync) {
            tokenStorage->sync();
        }
    }
}
