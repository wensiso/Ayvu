/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QSettings>
#include <QTimer>

#include <network.h>
#include <server.h>
#include <client.h>
#include <state.h>

#include <audiocontrol.h>
#include <datareceiver.h>
#include <datasender.h>

#include "applicationinfo.hpp"

#define DEFAULT_USERNAME "user"

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
    namespace system
    {
        class SystemDialog;
        class SystemUiResult;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI();

    Q_INVOKABLE void callAppWorldVendorCard();
    Q_INVOKABLE void postAReview();
    Q_INVOKABLE void callSettingsCard(QString uri);
    Q_INVOKABLE void updateSettings();

    Q_INVOKABLE const QString getUsername() const;
    Q_INVOKABLE void setUsername(const QString& username);

private slots:
    void onSystemLanguageChanged();

private:

    void registerQmlTypes(bb::cascades::QmlDocument*);
    void initSettings();

    QTimer *m_timer;
    QTranslator* m_pTranslator;

    QSettings *m_settings;
    QString m_username;

    bb::cascades::LocaleHandler* m_pLocaleHandler;

    ayvu::Network *m_network;
    ayvu::State *m_state;
    ayvu::Client *m_sessionClient;
    ayvu::Server *m_sessionServer;
    ayvu:: DataSender *m_audioSender;
    ayvu::DataReceiver *m_audioReceiver;
};

#endif /* ApplicationUI_HPP_ */
