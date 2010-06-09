#ifndef ENU_H
#define ENU_H

namespace Enu
{
    // Instruction mnemonics
    enum EMask
    {
        NMask = 0x08,
        ZMask = 0x04,
        VMask = 0x02,
        CMask = 0x01,

        eNONUNARY = 0x00,
        eUNARY = 0x01,
    };

    enum BusState {
        UNDEFINED,
        LOADED
    };

    enum MainBusState {
        None,
        MemReadWait,
        MemReadReady,
        MemWriteWait,
        MemWriteReady,
    };

    enum EMnemonic {
        LoadCk, C, B, A, MARCk, MDRCk, AMux, MDRMux, CMux,
        ALU, CCk, VCk, ANDZ, ZCk, NCk, MemWrite, MemRead, Pre, Post,
        Mem, X, SP, PC, IR, T1, T2, T3, T4, T5, T6, N, Z, V,
        MARA, MARB, MDR,
    };

}

#endif // ENU_H
