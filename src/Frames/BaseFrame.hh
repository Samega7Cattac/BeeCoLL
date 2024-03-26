#ifndef BEECOLL_API_BASEFRAME_HH
#define BEECOLL_API_BASEFRAME_HH


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

// STD headers
#include <vector>
#include <cstdint>

namespace BeeCoLL
{
    class BEECOLL_API BaseFrame
    {
    public:
        virtual ~BaseFrame();


        std::vector<uint8_t> GetFrame() const;

        uint8_t GetID() const;
        /*
        std::vector<uint8_t> GetResponseTypes() const;

        uint8_t GetStatusResponseFrameType() const;
        */
    protected:
        BaseFrame();

        explicit BaseFrame(unsigned int initial_frame_byte_size);

        BaseFrame(const BaseFrame& other_frame);

        explicit BaseFrame(const std::vector<uint8_t>& frame);

        std::vector<uint8_t> GetData() const;
        std::vector<uint8_t>& GetData();

        std::size_t GetDataSize() const;
        virtual void SetData(const std::vector<uint8_t>& data);
        uint8_t GetDataByte(unsigned int byte_index) const;
        uint8_t* GetDataBytePtr(unsigned int byte_index);

        virtual void SetDataByte(unsigned int byte_index, uint8_t byte);

        bool GetDataBit(unsigned int byte_index, uint8_t bit_offset) const;
        bool GetDataBit(unsigned int bit_index) const;
        virtual void SetDataBit(unsigned int byte_index, uint8_t bit_offset, bool bit);
        virtual void SetDataBit(unsigned int bit_index, bool bit);

        bool GetDataBitMask(unsigned int byte_index, uint8_t mask) const;

        virtual void InsertData(unsigned int byte_index, const std::vector<uint8_t>& data);
        void EraseData(unsigned int start_position, unsigned int end_position);
        void EraseData(unsigned int position);

        void SetID(uint8_t id);
        
    private:

        std::vector<uint8_t> m_data;
        uint8_t m_id;

    };
};

#endif // BEECOLL_BASEFRAME_HH