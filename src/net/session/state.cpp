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

bool State::isCalling() const
{
    return (m_state == CALLING);
}

bool State::isIncomming() const
{
    return (m_state == INCOMMING);
}

bool State::isTalking() const
{
    return (m_state == TALKING);
}

QString State::getStr(int type)
{
    QString str = "null";
    switch ((StateType) type)
    {
        case STOPPED:
            return "STOPPED";
        case CALLING:
            return "CALLING";
        case INCOMMING:
            return "INCOMMING";
        case TALKING:
            return "TALKING";
        default:
            return str;
    }
    return str;
}

void State::setStopped()
{
    qDebug() << "setStopped";
    setState(STOPPED);
}

void State::setCalling()
{
    qDebug() << "setCalling";
    setState(CALLING);
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

} /* namespace ayvu */

