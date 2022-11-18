#ifndef BEECOLL_FRAMES_LOCALATCOMMANDREQUEST_HH
#define BEECOLL_FRAMES_LOCALATCOMMANDREQUEST_HH

// BEECOLL headers
#include "Frame.hh"
#include "ATCommands/ATCommand.hh"

// STD headers
#include <vector>
#include <memory>

namespace BeeCoLL
{
namespace Frames
{
    class LocalATCommandRequest : public Frame
    {
    public:
        explicit LocalATCommandRequest(const std::vector<uint8_t>& frame_data = {});
        explicit LocalATCommandRequest(const Frame& other);
        ~LocalATCommandRequest();

        uint8_t GetFrameID();
        void SetFrameID(uint8_t frame_id);

        std::shared_ptr<ATCommand> GetATCommand();
        void SetATCommand(const ATCommand& at_command);

        std::vector<uint8_t> GetValue();
        void SetValue(const std::vector<uint8_t>& value);

    private:
        std::shared_ptr<ATCommand> m_at_command;
    };
};
};

#endif // BEECOLL_FRAMES_LOCALATCOMMANDREQUEST_HH