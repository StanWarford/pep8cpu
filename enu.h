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

    enum BusState {
        UNDEFINED,
        LOADED };

    enum MainBusState {
        NVOID,
        MEM_READ_ADDR,
        MEM_WRITE_ADDR,
        MEM_READ_DATA,
        MEM_WRITE_DATA };
}

#endif // ENU_H
