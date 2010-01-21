#include "sim.h"
#include "enu.h"

using namespace Enu;

QVector<int> Sim::Mem(65536);
QVector<int> Sim::Reg(32);
QVector<int> Sim::MARA(2);
QVector<int> Sim::MARB(2);
QVector<int> Sim::MDR(2);
bool Sim::nBit, Sim::zBit, Sim::vBit, Sim::cBit;



