#ifndef BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH
#define BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH

#ifdef _WIN32
    #ifdef BEECOLL_BUILD
        #define BEECOLL_API __declspec(dllexport)
    #else
        #define BEECOLL_API __declspec(dllimport)
    #endif
#elif __unix__
    #ifndef BEECOLL_API
        #define BEECOLL_API
    #endif
#endif

// BEECOLL headers
#include "Frame.hh"
#include "../../ATCommands/ATCommand.hh"

// STD headers
#include <vector>
#include <memory>

namespace BeeCoLL::Xbee
{
namespace Frames
{
    constexpr uint8_t LOCAL_ATCOMMAND_RESPONSE_FRAME_ID = 0x88;

    enum CommandStatus : uint8_t
    {
        OK = 0,
        ERROR = 1,
        INVALID_COMMAND = 2,
        INVALID_PARAM = 3
    };

    class BEECOLL_API LocalATCommandResponse : public Frame
    {
    public:
        explicit LocalATCommandResponse(const std::vector<uint8_t>& frame_data = {});
        explicit LocalATCommandResponse(const Frame& other);
        ~LocalATCommandResponse();

        uint8_t GetFrameID();
        void SetFrameID(uint8_t frame_id = 0);

        CommandStatus GetStatus();
        void SetStatus(CommandStatus status);

        ATCommand GetATCommand();
        void SetATCommand(const ATCommand& at_command);

    private:
        ATCommand m_at_command;

        void GenerateATCommand();
    };
};
};

#endif // BEECOLL_FRAMES_LOCALATCOMMANDRESPONSE_HH