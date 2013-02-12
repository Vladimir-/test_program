#ifndef STATEDATA_H
#define STATEDATA_H

#include <QtCore/QMetaType>
#include <QtGui/QStyle>
#include <QDebug>

class StateData
{
public:
    StateData() {}
    StateData(QStyle::State state)        { State = state; }
    StateData(QStyle::StateFlag state)    { State = state; }
    StateData(const StateData & other) { State = other.State; }
    ~StateData() {}

    QStyle::State state() const { return State; }
    void setState(QStyle::State state) { State = state; }

    inline StateData & operator = (const StateData &state) { State = state.State; return *this; }
    inline operator int() const { return (int)State; }
    inline operator QStyle::State() const { return State; }

    inline StateData & operator |= (StateData state) { State |= state.State; return *this; }
    inline StateData & operator ^= (StateData state) { State ^= state.State; return *this; }
    inline StateData & operator &= (int mask)           { State &= mask; return *this; }
    inline StateData & operator &= (uint mask)          { State &= mask; return *this; }

    inline StateData operator | (StateData state) const { StateData tmp; tmp.State = State | state.State; return tmp; }
    inline StateData operator ^ (StateData state) const { StateData tmp; tmp.State = State ^ state.State; return tmp; }
    inline StateData operator & (int mask)  const { StateData tmp; tmp.State = State & mask; return tmp; }
    inline StateData operator & (uint mask) const { StateData tmp; tmp.State = State & mask; return tmp; }
    inline StateData operator~() const { StateData tmp; tmp.State = ~State; return tmp; }

    inline bool operator!() const { return !State; }

    inline bool testFlag(QStyle::StateFlag f) const { return (State & f) == f && (f != 0 || State == int(f) ); }

private:
    QStyle::State State;
};
Q_DECLARE_METATYPE(StateData);
QDebug operator<<(QDebug debug, const StateData & checkerState);

#endif // STATEDATA_H
