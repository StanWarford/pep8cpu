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

    enum EMnemonic {
        E_LoadCk, E_C, E_B, E_A, E_MARCk, E_MDRCk, E_AMux, E_MDRMux, E_CMux,
        E_ALU, E_CCk, E_VCk, E_ANDZ, E_ZCk, E_NCk, E_MemWrite, E_MemRead
    };
}

#endif // ENU_H
