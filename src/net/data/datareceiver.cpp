#include <datareceiver.h>

namespace ayvu {

DataReceiver *DataReceiver::instance = 0;

DataReceiver::DataReceiver(QObject *parent) : QObject(parent)
{
	m_udpListener = new QUdpSocket(this);
	m_datagram = new QByteArray();
	m_logfileCreated = false;
	m_loggingPercent = 0.0; //Default is 0
}

void DataReceiver::setLoggingPercent(double logPercent) {
	m_loggingPercent = logPercent;
}

void DataReceiver::start() {
	QHostAddress host = Network::getValidIP();

	m_udpListener->bind(host, DATA_PORT);

	bool ret = connect(m_udpListener, SIGNAL(readyRead()), this,
			SLOT(messageReceived()));
	if (ret) {
		qDebug()
				<< "Receiving audio data on " + host.toString() + ":"
						+ QString::number(DATA_PORT);
	} else {
		qWarning()
				<< "Socket bind failure on " + host.toString() + ":"
						+ QString::number(DATA_PORT);
	}
	Q_ASSERT(ret);
}

void DataReceiver::stop() {
	disconnect(m_udpListener, SIGNAL(readyRead()), this,
			SLOT(messageReceived()));
	m_udpListener->close();
}

/**
 * Slot for datagram received.
 */
void DataReceiver::messageReceived() {

	while (m_udpListener->hasPendingDatagrams()) {

		m_datagram->resize(m_udpListener->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		m_udpListener->readDatagram(m_datagram->data(), m_datagram->size(),
				&sender, &senderPort);
	}

	Message message;
	message.createFromReceivedDatagram(m_datagram);

	if(message.getType() == Message::NORMAL) {

		//If log is on... send control messages
		if(m_loggingPercent != 0.0) {

			double f = 100/m_loggingPercent; // 1% ==> (100/1 = 100) ===> (seq%100)
			int factor = (int) f;

			if(message.getSequence()%factor == 0)
			{
				DataSender *sender = DataSender::getInstance();
				message.setType(Message::CONTROL);
				QByteArray ctrl_datagram = message.createDatagram();
				sender->writeDatagram(ctrl_datagram);
			}
		}

		AudioPCM::writeDatagramToCircularBuffer(message.getData());
		AudioPCM::setCaptureReady(true);

	} else if (message.getType() == Message::CONTROL) {

		//If log is on...
		if(m_loggingPercent != 0.0) {
			qint64 sequence = message.getSequence();
			qint64 latency = message.getLatency();

			this->createLogFile();

			//		printLatency(sequence, latency);
			writeLatency(sequence, latency);
		}
	}

}

void DataReceiver::createLogFile() {

	if(!m_logfileCreated) {

		m_logdir = new QDir(LOG_DIR);
		if (!m_logdir->exists())
			QDir::root().mkpath(m_logdir->absolutePath());

		QDateTime now = QDateTime::currentDateTime();
		QString filename = LOG_FILE + QString::number(now.toMSecsSinceEpoch()) + ".txt";
		m_logfile = new QFile(m_logdir->absolutePath() + QDir::separator() + filename, this);

		if (m_logfile->open(QIODevice::WriteOnly)) {

			QTextStream stream(m_logfile);
			stream << "###############################################\r\n";
			stream << "# Log file.\r\n# Generated on " << now.toString(Qt::SystemLocaleLongDate);
			stream << "\r\n# Bitrate: " << QString::number(AudioPCM::getBitRate()) << " kbps";
			stream << "\r\n# Log Percentage: " << QString::number(m_loggingPercent) << "%";
			stream << "\r\n###############################################";
			stream << "\r\n\r\n";
			stream << "Sample\tLatency\r\n\r\n";
		}
		m_logfile->close();
		m_logfileCreated = true;
	}
}


void DataReceiver::printLatency(qint64 sequence, qint64 latency) {
	qDebug() << "[DataReceiver]: Latency (" << sequence << ") = " << latency << "ms";
}

void DataReceiver::writeLatency(qint64 sequence, qint64 latency)
{
	if(m_logfileCreated) {
		if (m_logfile->open(QIODevice::Append)) {
			QTextStream stream(m_logfile);
			QString line = QString::number(sequence) + "\t" + QString::number(latency);
			stream << line + "\r\n";
		}
		m_logfile->close();
	}
}

}


