/*
 * state.cpp
 *
 *  Created on: 07/08/2014
 *      Author: wendell
 */

#include <state.h>

namespace ayvu {

State *State::instance = 0;

State::State()
{
    m_state = STOPPED;
}

int State::getState() const
{
    return (int) m_state;
}

void State::setState(int newState)
{
    this->m_state = (StateType) newState;
    qDebug() << "Setting new state: " << getStr(newState);
    emit stateChanged(newState);
}

bool State::isStopped() const
{
    return (m_state == STOPPED);
}

bool State::isInviting() const
{
    return (m_state == INVITING);
}

bool State::isIncomming() const
{
    return (m_state == INCOMMING);
}

bool State::isTalking() const
{
    return (m_state == TALKING);
}

bool State::wasRejected() const
{
    return (m_state == REJECTED);
}


bool State::wasAccepted() const
{
    return (m_state == ACCEPTED);
}


QString State::getStr(int type)
{
    QString str = "null";
    switch ((StateType) type)
    {
        case STOPPED:
            return "STOPPED";
        case INVITING:
            return "INVITING";
        case INCOMMING:
            return "INCOMMING";
        case TALKING:
            return "TALKING";
        case REJECTED:
            return "REJECTED";
        case ACCEPTED:
            return "ACCEPTED";
        default:
            return str;
    }
    return str;
}

QString State::getStateStr()
{
    return getStr(m_state);
}

void State::setStopped()
{
    qDebug() << "setStopped";
    setState(STOPPED);
}

void State::setInviting()
{
    qDebug() << "setInviting";
    setState(INVITING);
}

void State::setIncomming()
{
    qDebug() << "setIncomming";
    setState(INCOMMING);
}

void State::setTalking()
{
    qDebug() << "setTalking";
    setState(TALKING);
}

void State::setRejected()
{
    qDebug() << "setRejected";
    setState(REJECTED);
}

void State::setAccepted()
{
    qDebug() << "setAccepted";
    setState(ACCEPTED);
}

} /* namespace ayvu */

