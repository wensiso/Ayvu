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

#include <bb/cascades/InvokeActionItem>
#include <bb/cascades/InvokeQuery>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeTargetReply>

using namespace bb::cascades;
using namespace bb::system;

using namespace ayvu;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    ApplicationInfo::registerQmlTypes();
    this->initSettings();

    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);
    Q_UNUSED(res);
    onSystemLanguageChanged();

    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);
    // Create a SceneCover and set the application cover
//    ActiveFrameQML *activeFrame = new ActiveFrameQML();
//    Application::instance()->setCover(activeFrame);
    this->registerQmlTypes(qml);

    m_network->startDeviceDiscovery();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), m_network, SLOT(testConnection()));
    m_timer->start(5000);

    m_sessionServer->start();

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

ApplicationUI::~ApplicationUI()
{
    qDebug() << "Destructor";
    m_timer->stop();
    m_network->stopDeviceDiscovery();

    m_sessionClient->sendFinishMessage();
    m_sessionServer->stop();
}

void ApplicationUI::initSettings()
{
    m_settings = new QSettings("Wendell", "Ayvu", this);
    if (m_settings->contains("username"))
    {
        m_username = m_settings->value("username").toString();
    } else {
        m_username = DEFAULT_USERNAME;
        updateSettings();
    }
}

void ApplicationUI::registerQmlTypes(QmlDocument *qml)
{
    qmlRegisterType<Network>();
    m_network = Network::getInstance(m_settings, this);
    qml->setContextProperty("_network", m_network);

    qmlRegisterType<ContactList>();
    m_contactList = new ContactList(m_network->getSSDP(), this);
    qml->setContextProperty("_addressBook", m_contactList);

    qmlRegisterType<State>();
    m_state = State::getInstance();
    qml->setContextProperty("_state", m_state);

    qmlRegisterType<Client>();
    m_sessionClient = new Client(m_settings, this);
    qml->setContextProperty("_sessionClient", m_sessionClient);

    qmlRegisterType<Server>();
    m_sessionServer = new Server(m_settings, this);
    qml->setContextProperty("_sessionServer", m_sessionServer);

    qmlRegisterType<DataSender>();
    m_audioSender = DataSender::getInstance(this);
    qml->setContextProperty("_audioSender", m_audioSender);

    qmlRegisterType<DataReceiver>();
    m_audioReceiver = DataReceiver::getInstance(this);
    qml->setContextProperty("_audioReceiver", m_audioReceiver);
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

void ApplicationUI::callAppWorldVendorCard() {
    InvokeManager* invokeManager = new InvokeManager();
    InvokeRequest cardRequest;
    cardRequest.setTarget("sys.appworld"); // Aqui define o target~;
    cardRequest.setAction("bb.action.OPEN");
    cardRequest.setUri("appworld://vendor/82234"); // id vendor Wendell: 82234
    InvokeTargetReply* reply = invokeManager->invoke(cardRequest);
    reply->setParent(this);
}

void ApplicationUI::postAReview() {
    InvokeManager* invokeManager = new InvokeManager();
    InvokeRequest cardRequest;
    cardRequest.setTarget("sys.appworld"); // Aqui define o target~;
    cardRequest.setAction("bb.action.OPEN");
    cardRequest.setUri("appworld://content/37260887"); // id FeetFit: 37260887
    InvokeTargetReply* reply = invokeManager->invoke(cardRequest);
    reply->setParent(this);
}

void ApplicationUI::callSettingsCard(QString uri) {
    InvokeManager* invokeManager = new InvokeManager();
    InvokeRequest cardRequest;
    cardRequest.setTarget("sys.settings.target"); // Aqui define o target~;
    cardRequest.setAction("bb.action.OPEN");
    cardRequest.setMimeType("settings/view");
    cardRequest.setUri(uri);
    InvokeTargetReply* reply = invokeManager->invoke(cardRequest);
    reply->setParent(this);
}

void ApplicationUI::updateSettings() {
    m_settings->setValue("username", m_username);
    m_settings->sync();
}

const QString ApplicationUI::getUsername() const
{
    return m_username;
}

void ApplicationUI::setUsername(const QString& username)
{
    m_username = username;
}
