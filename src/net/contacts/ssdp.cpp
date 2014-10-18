/*
 * ssdp.cpp
 *
 *  Created on: 06/10/2014
 *      Author: wendell
 */

#include <ssdp.h>

namespace ayvu
{

SSDP::SSDP(int interval, QString usn, QObject *parent) :
        QObject(parent) {

    contacts_list = new QList<Contact>();
    last_id = -1;

    this->initialized = false;
    this->interval = interval;
    this->USN = usn;

    this->discoverTimer = new QTimer(this);
    this->udpSocket = new QUdpSocket(this);

}

SSDP::~SSDP() {
    delete this->discoverTimer;
    delete this->udpSocket;
}

void SSDP::init() {

    if(this->initialized)
        return;

    qDebug() << "SSDP: initing...";
    QHostAddress groupAddress = QHostAddress(SSDP_ADDR);

    // Create a new UDP socket and bind it against port 1900
    if (!udpSocket->bind(groupAddress, SSDP_PORT,
            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "cannot bind multicast socket in" << SSDP_ADDR;
    }

    // Tell the UDP socket which multicast group it should join
    if(!udpSocket->joinMulticastGroup(groupAddress))
    {
        qWarning() << "Error on joinMulticastGroup";
        emit multicastError();
    }

    /**
     * Create signal/slot connection to invoke datagramReceived() whenever
     * a new multicast datagram is received by the socket.
     */
    Q_ASSERT(connect(udpSocket, SIGNAL(readyRead()), this, SLOT(datagramReceived())));
    this->initialized = true;
}

bool SSDP::isInitialized() const
{
    return this->initialized;
}


void SSDP::start() {

    Q_ASSERT(this->initialized);

    this->discoverTimer->start(interval * 1000);
    Q_ASSERT(connect(discoverTimer, SIGNAL(timeout()), this, SLOT(discover())));

    this->doubleDiscover();
    emit setupEvent("SSDP: started");
}

void SSDP::stop() {
    udpSocket->disconnectFromHost();
    this->discoverTimer->stop();
}

void SSDP::discover(const QString &type, const QString &mx,
        const QString &userAgent) {
    QString discoverMessage = SSDP_DISCOVERY_REQUEST.arg(type, mx, userAgent);

    qDebug() << "Sending discovering message:";
    qDebug() << discoverMessage.toUtf8();

    udpSocket->moveToThread(this->thread());
    udpSocket->writeDatagram(discoverMessage.toUtf8(), QHostAddress(SSDP_ADDR),
            SSDP_PORT);
}

void SSDP::doubleDiscover(const QString &type, const QString &mx,
        const QString &userAgent) {
    discover(type, mx, userAgent);
    discover(type, mx, userAgent);
}

void SSDP::datagramReceived() {

    QUdpSocket *socket = static_cast<QUdpSocket *>(QObject::sender());

    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress peerAddress;
        quint16 peerPort;
        socket->readDatagram(datagram.data(), datagram.size(), &peerAddress,
                &peerPort);
        QString message = QString(datagram);
        this->parseMessage(message);
    }
}

/**
 * Parse SSDP message
 */
QMap<QString, QString> SSDP::getMapFromMessage(QString message) {

    QStringList messageLines = message.split("\r\n");
    QMap<QString, QString> response;

    foreach(QString line, messageLines) {
        if((line = line.trimmed())!= "") {
            int divpos = line.indexOf(':');
            //TODO Definir se vai sempre fazer toLower aqui
            QString key = line.left(divpos).toLower();
            QString value = line.right(line.size() - divpos).remove(0, 1).trimmed();
            response[key] = value;
        } else {
            break;
        }
    }

    return response;
}

void SSDP::parseMessage(const QString &message)
{
    QMap<QString, QString> request = this->getMapFromMessage(message);
    QMapIterator<QString, QString> iter(request);
    QString *v;

    QString username = "newuser"; //TODO Pegar meu user...

    if (message.startsWith(SSDP_SEARCH_METHOD, Qt::CaseInsensitive))
    {
        if((v = getValue(iter, "MAN")))
        {
            qDebug() << "Receiving discovery message: \n" << message;
            if(v->compare(SSDP_DISCOVER, Qt::CaseInsensitive)==0)
            {
                //TODO Gerar DATE
                qDebug() << "Discovering received. Creating response...";
                QString discoveryResponse = SSDP_DISCOVERY_AYVU_RESPONSE.arg(Network::getValidIPStr(), this->USN, "ayvu:voice", "01/01/2001");
                udpSocket->writeDatagram(discoveryResponse.toUtf8(), QHostAddress(SSDP_ADDR),
                            SSDP_PORT);
            }
        }
    }
    else if(message.startsWith(GENA_NOTIFY_METHOD, Qt::CaseInsensitive))
    {
        if((v = getValue(iter, "NTS")))
        {
            if(v->startsWith(SSDP_ALIVE_NTS, Qt::CaseInsensitive))
            {
                //TODO tratar alive
//                qDebug() << "Novo DEVICE!";
                emit deviceAlive("NEW!");
            }
            else if(v->startsWith(SSDP_BYEBYE_NTS, Qt::CaseInsensitive))
            {
                //TODO tratar byebye
                qDebug() << "DEVICE foi embora...";
                emit byebyeReceived("ByeBye!");
            }
        }
    }
    else if(message.startsWith("HTTP/1.1 200 OK", Qt::CaseInsensitive))
    {
        if((v = getValue(iter, "ST")))
        {
            if(v->startsWith("ayvu:", Qt::CaseInsensitive))
            {
                //TODO tratar new device (exclude myself...)
                qDebug() << "Novo DEVICE!";
                qDebug() << "------------------\n" << message;

                Contact c(++last_id);
                c.setFirstName("FirstName");
                c.setHostname("Host");
                c.setIp("IP");
                contacts_list->append(c);
                emit contactChanged(last_id);
            }
        }
    }

    delete v;
}

QString* SSDP::getValue(QMapIterator<QString, QString> &iter, QString mykey)
{
    while(iter.hasNext()) {

        QString key = iter.next().key();
        if(key.compare(mykey, Qt::CaseInsensitive)==0)
            return new QString(iter.value());
    }
    return 0;
}

const Contact& SSDP::contactDetails(int id)
{
    return contacts_list->at(id);
}

QList<Contact>* SSDP::getContacts()
{
    return contacts_list;
}

} /* namespace ayvu */


