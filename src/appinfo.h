/*
 * AppInfo.h
 *
 *  Created on: 06/09/2014
 *      Author: wendell
 */

#ifndef APPINFO_H_
#define APPINFO_H_

#include <QObject>
#include <bb/device/HardwareInfo>

#include <ssdp.h>

#define DEFAULT_USERNAME "user"

namespace ayvu
{

class AppInfo : public QObject
{
Q_OBJECT
public:
    static AppInfo *getInstance(QObject *parent=0)
    {
        if (!instance)
            instance = new AppInfo(parent);
        return instance;
    }

    const QString getUsername() const;
    void setUsername(const QString& username);

signals:
    void newDevice(QString);

private slots:
    void addNewDevice(QString);
    void removeDevice(QString);

private:
    static AppInfo *instance; //Singleton
    AppInfo(QObject *parent=0);

    bb::device::HardwareInfo m_deviceinfo;

    SSDP *ssdp;
    QList<QString> *devices;

    QString m_username;
    QString m_devicename;

};

} /* namespace ayvu */

#endif /* APPINFO_H_ */
