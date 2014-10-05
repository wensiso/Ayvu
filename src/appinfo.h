/*
 * AppInfo.h
 *
 *  Created on: 06/09/2014
 *      Author: wendell
 */

#ifndef APPINFO_H_
#define APPINFO_H_

#include <bb/device/HardwareInfo>

#define DEFAULT_USERNAME "user"

namespace ayvu
{

class AppInfo
{
public:
    static AppInfo *getInstance()
    {
        if (!instance)
            instance = new AppInfo();
        return instance;
    }

    const QString getUsername() const;
    void setUsername(const QString& username);

private:
    static AppInfo *instance; //Singleton
    AppInfo();

    bb::device::HardwareInfo m_deviceinfo;

    QString m_username;
    QString m_devicename;
};

} /* namespace ayvu */

#endif /* APPINFO_H_ */
