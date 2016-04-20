#include "../type/type.h"
#include "../system/descriptor.h"
#include "interface.h"

void testGateEntry();

void initInterfaceTable()
{
	setCallGateDescriptor(0x04, (int)testGateEntry, 0x01, 0x03, AR_386CGate);
}
