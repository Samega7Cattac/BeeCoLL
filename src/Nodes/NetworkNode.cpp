#include "NetworkNode.hh"

BeeCoLL::NetworkNode::NetworkNode(const NetworkNodeInfo& node_info, Coordinator* coordinator) :
    m_info(node_info),
    m_coordinator(coordinator)
{
    uint64_t unique_addr = node_info.SL;
    unique_addr |= static_cast<uint64_t>(node_info.SH) << 32;
    SetUniqueAddress(unique_addr);
}

BeeCoLL::NetworkNode::NetworkNode(const NetworkNode& other) :
    m_info(other.m_info),
    m_coordinator(other.m_coordinator)
{
    uint64_t unique_addr = other.m_info.SL;
    unique_addr |= static_cast<uint64_t>(other.m_info.SH) << 32;
    SetUniqueAddress(unique_addr);
}

BeeCoLL::NetworkNode::~NetworkNode()
{

}

void
BeeCoLL::NetworkNode::SetCallback(const std::function<void(const Frame&)>& callback)
{
    m_callback = callback;
}

void
BeeCoLL::NetworkNode::TriggerCallback(const Frame& frame)
{
    if (m_callback)
    {
        m_callback(frame);
    }
}
