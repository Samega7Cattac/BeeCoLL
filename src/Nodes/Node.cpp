#include "Node.hh"

BeeCoLL::Node::Node()
{

}

BeeCoLL::Node::Node(const Node& other) :
    m_SH(other.m_SH),
    m_SL(other.m_SL),
    m_MY(other.m_MY),
    m_NI(other.m_NI),
    m_ID(other.m_ID),
    m_OP(other.m_OP),
    m_node_type(other.m_node_type)
{

}

BeeCoLL::Node::~Node()
{

}

uint64_t
BeeCoLL::Node::GetUniqueAddress() const
{
    uint64_t address;
    // Puts the least significant number in the least significant part of the address.
    address = m_SL;
    // Shifts by 32 bits and puts SH in address by OR operation.
    address |= static_cast<uint64_t>(m_SH) << 32;

    return address;
}

uint16_t
BeeCoLL::Node::GetNetworkAddress() const
{
    return m_MY;
}

std::string
BeeCoLL::Node::GetNodeIdentifier() const
{
    return m_NI;
}

uint16_t
BeeCoLL::Node::GetPANIdentifier() const
{
    // Check if the ID is in auto (set to 0).
    if (m_ID == 0)
    {
        // Return the Operating PAN ID.
        return m_OP;
    }
    // Return PAN ID.
    return m_ID;
}

void
BeeCoLL::Node::SetUniqueAddress(uint64_t new_addr)
{
    m_SL = new_addr;
    m_SH = new_addr >> 32;
}

void
BeeCoLL::Node::SetNetworkAddr(uint16_t new_addr)
{
    m_MY = new_addr;
}

void
BeeCoLL::Node::SetNodeIdentifier(const std::string& new_id)
{
    m_NI = new_id;
}

void
BeeCoLL::Node::SetPANIdentifier(uint16_t new_id)
{
    m_ID = new_id;
}

uint8_t
BeeCoLL::Node::GetNodeType()
{
    return m_node_type;
}

void
BeeCoLL::Node::SetNodeType(uint8_t node_type)
{
    m_node_type = node_type;
}
