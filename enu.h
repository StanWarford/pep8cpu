#ifndef ENU_H
#define ENU_H

namespace Enu
{
   // Instruction mnemonics
    enum EMask
    {
        N = 0x01,
        Z = 0x02,
        V = 0x04,
        C = 0x08,

        eNONUNARY = 0x00,
        eUNARY = 0x01,
    };
}

#endif // ENU_H
