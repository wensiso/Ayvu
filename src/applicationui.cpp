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

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include <bb/system/SystemDialog>
#include <bb/system/SystemUiResult>

#include <network.h>
#include <server.h>
#include <client.h>
#include <state.h>

#include <audiocontrol.h>
#include <datareceiver.h>
#include <datasender.h>

using namespace bb::cascades;
using namespace bb::system;

using namespace ayvu;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    this->err_dialog = new SystemDialog("Ok", "Cancel", this);

    qmlRegisterType<Network>();
    Network *network = Network::getInstance(this);
    qml->setContextProperty("_network", network);

    Q_ASSERT(connect(network, SIGNAL(networkError()), this, SLOT(onMulticastError())));
    network->startDeviceDiscovery();

    qmlRegisterType<State>();
    State *state = State::getInstance();
    qml->setContextProperty("_state", state);

    qmlRegisterType<Client>();
    Client *sessionClient = new Client(this);
    qml->setContextProperty("_sessionClient", sessionClient);

    qmlRegisterType<Server>();
    Server *sessionServer = new Server(this);
    qml->setContextProperty("_sessionServer", sessionServer);
    sessionServer->start();

    qmlRegisterType<DataSender>();
    DataSender *audioSender = DataSender::getInstance(this);
    qml->setContextProperty("_audioSender", audioSender);

    qmlRegisterType<DataReceiver>();
    DataReceiver *audioReceiver = DataReceiver::getInstance(this);
    qml->setContextProperty("_audioReceiver", audioReceiver);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onMulticastError()
{
    err_dialog->setTitle("Multicast error");
    err_dialog->setBody("Ayvu cannot join in multicast group. Are you connected in a Wi-Fi network?");
    err_dialog->setEmoticonsEnabled(true);

    Q_ASSERT(connect(err_dialog,
             SIGNAL(finished(bb::system::SystemUiResult::Type)),
             this,
             SLOT(onErrDialogFinished(bb::system::SystemUiResult::Type))));

   err_dialog->show();

}

void ApplicationUI::onMulticastErrorDialogFinished(int result)
{
    //TODO Treat results
    Q_UNUSED(result);
//    if(result==SystemUiResult::Type::ConfirmButtonSelection)
//        ;
//    else
//        ;

}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("Ayvu_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
