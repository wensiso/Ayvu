/*
 * state.h
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#ifndef STATE_H_
#define STATE_H_

#include <QObject>
#include <QDebug>

/**
 * Unique and global session state
 */
namespace ayvu {

class State: public QObject {
    Q_OBJECT

    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)

    Q_PROPERTY(bool stopped READ isStopped NOTIFY stateChanged)
    Q_PROPERTY(bool inviting READ isInviting NOTIFY stateChanged)
    Q_PROPERTY(bool incomming READ isIncomming NOTIFY stateChanged)
    Q_PROPERTY(bool talking READ isTalking NOTIFY stateChanged)

public:
    enum StateType {
        STOPPED,
        INVITING,
        INCOMMING,
        TALKING
    };

    Q_INVOKABLE static State *getInstance()
    {
        if (!instance)
            instance = new State();
        return instance;
    }

    int getState() const;

    Q_INVOKABLE QString getStr(int);

    bool isStopped() const;
    bool isInviting() const;
    bool isIncomming() const;
    bool isTalking() const;

    Q_INVOKABLE void setStopped();
    Q_INVOKABLE void setInviting();
    Q_INVOKABLE void setIncomming();
    Q_INVOKABLE void setTalking();

signals:
    void stateChanged(int);

private:
    static State *instance; //Singleton
    State();

    void setState(int state);

    //The property value
    StateType m_state;
};


} /* namespace ayvu */

#endif /* STATE_H_ */
