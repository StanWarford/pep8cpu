#ifndef ENU_H
#define ENU_H

namespace Enu
{
    // Instruction mnemonics
    enum EMask
    {
        NMask = 0x01,
        ZMask = 0x02,
        VMask = 0x04,
        CMask = 0x08,

        eNONUNARY = 0x00,
        eUNARY = 0x01,
    };

    enum BusState {
        UNDEFINED,
        LOADED
    };

    enum MainBusState {
        NVOID,
        MEM_READ_ADDR,
        MEM_WRITE_ADDR,
        MEM_READ_DATA,
        MEM_WRITE_DATA
    };

    enum EMnemonic {
        LoadCk, C, B, A, MARCk, MDRCk, AMux, MDRMux, CMux,
        ALU, CCk, VCk, ANDZ, ZCk, NCk, MemWrite, MemRead, Pre, Post,
        Mem, X, SP, PC, IR, T1, T2, T3, T4, T5, T6, N, Z, V,
        MARA, MARB, MDR,
    };
}

#endif // ENU_H
