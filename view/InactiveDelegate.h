#ifndef INACTIVEDELEGATE_H
#define INACTIVEDELEGATE_H
#include <view/ActiveDelegate.h>

namespace SSw
{

class InactiveDelegate : public ActiveDelegate
{
public:
    InactiveDelegate(QObject *parent = 0);

protected:
    virtual void getStyleForField(const SField& field,
                          QStyleOptionButton& buttonStyle) const;
};

}

#endif // INACTIVEDELEGATE_H
