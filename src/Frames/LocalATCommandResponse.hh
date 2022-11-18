#ifndef BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH
#define BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH

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
    enum CommandStatus : uint8_t
    {
        OK = 0,
        ERROR = 1,
        INVALID_COMMAND = 2,
        INVALID_PARAM = 3
    };

    class LocalATCommandResponse : public Frame
    {
    public:
        explicit LocalATCommandResponse(const std::vector<uint8_t>& frame_data = {});
        explicit LocalATCommandResponse(const Frame& other);
        ~LocalATCommandResponse();

        uint8_t GetFrameID();
        void SetFrameID(uint8_t frame_id);

        CommandStatus GetStatus();
        void SetStatus(CommandStatus status);

        std::shared_ptr<ATCommand> GetATCommand();
        void SetATCommand(const ATCommand& at_command);

    private:
        std::shared_ptr<ATCommand> m_at_command;
    };
};
};

#endif // BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH