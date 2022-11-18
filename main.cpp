#include <iostream>

#include "Nodes/Coordinator.hh"

#include "Frames/ExplicitRxIndicator.hh"
#include "Frames/TransmitRequest.hh"

#include "ATCommands/ND.hh"

int main()
{
    BeeCoLL::Coordinator zigbee("/dev/ttyUSB0");

    zigbee.StartDiscover();

    BeeCoLL::Frames::TransmitRequest frame;
    frame.SetFrameID(1);
    frame.SetDestUniqueAddr(0x0013A20041DC9CEA);
    std::vector<uint8_t> msg = { '1' };
    frame.SetPayload(msg);

    zigbee.SendAPICommand(frame);
    BeeCoLL::Frames::ExplicitRxIndicator reply_frame(zigbee.ReceiveAPICommand());
    
    // unsigned char data_bytes[] = {0x01, 0x00, 0x13, 0xA2, 0x00, 0x41, 0xDC, 0x9C, 0xEA, 0xFF, 0xFE, 0x00, 0x00, 0x31};
    // std::string data(reinterpret_cast<char*>(data_bytes), 14);
    // TransmitRequest tx(data);

    // zigbee.SendAPICommand(tx);
    // std::shared_ptr<ExplicitRxIndicator> frame = std::dynamic_pointer_cast<ExplicitRxIndicator>(zigbee.ReceiveAPICommand());

    std::cout << reply_frame.GetReceivedDataToString() << std::endl;
    return 0;
}