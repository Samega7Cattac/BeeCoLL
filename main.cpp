#include <iostream>

#include "Nodes/Coordinator.hh"

#include "Frames/ExplicitRxIndicator.hh"
#include "Frames/TransmitRequest.hh"

#include "ATCommands/ND.hh"

void HandleNodes(const BeeCoLL::Frame& frame)
{
    if (frame.GetType() == BeeCoLL::FrameType::EXPLICIT_RX_INDICATOR)
    {
        BeeCoLL::Frames::ExplicitRxIndicator reply_frame(frame);
        std::cout << std::hex << reply_frame.GetSourceUniqueAddr() << std::dec << " | " << reply_frame.GetReceivedDataToString() << std::endl;
    }
}

int main()
{
    BeeCoLL::Coordinator zigbee("/dev/ttyUSB0");

    zigbee.StartDiscover();
    std::vector<std::shared_ptr<BeeCoLL::NetworkNode>> nodes = zigbee.GetNetworkNodes();

    for (std::shared_ptr<BeeCoLL::NetworkNode> node : nodes)
    {
        node->SetCallback(&HandleNodes);
    }

    BeeCoLL::Frames::TransmitRequest frame;
    frame.SetDestUniqueAddr(0x0013A20041DC9CEA);
    std::vector<uint8_t> msg = { '1' };
    frame.SetPayload(msg);

    zigbee.SendAPICommand(frame, &HandleNodes);

    std::cout << std::hex << nodes[0]->GetUniqueAddress() << std::dec << std::endl;
    std::cout << std::hex << zigbee.GetUniqueAddress() << std::dec << std::endl;

    getchar();
     
    return 0;
}