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

private:
    static AppInfo *instance; //Singleton
    AppInfo(QObject *parent=0);

    bb::device::HardwareInfo m_deviceinfo;

    QString m_username;
    QString m_devicename;

};

} /* namespace ayvu */

#endif /* APPINFO_H_ */
