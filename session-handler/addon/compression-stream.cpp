#include <stdexcept>
#include <cstring>

#include "compression-stream.hpp"

CompressionStream::CompressionStream()
    : m_data()
    , m_index(0)
{ }

CompressionStream::CompressionStream(const std::vector<uint8_t>& data)
    : m_data(data)
    , m_index(0)
{ }

CompressionStream::CompressionStream(const std::vector<char>& data)
    : m_data(data.size())
    , m_index(0)
{
    std::memcpy(m_data.data(), data.data(), data.size());
}

void CompressionStream::putBytes(const uint8_t* bytes, const std::size_t length)
{
    for (std::size_t i(0); i < length; ++i)
    {
        m_data.push_back(*bytes++);
    }
}

void CompressionStream::putByte(const uint8_t byte)
{
    m_data.push_back(byte);
}

uint8_t CompressionStream::getByte()
{
    return m_data.at(m_index++);
}

void CompressionStream::getBytes(uint8_t* bytes, std::size_t length)
{
    if (m_index + length > m_data.size())
    {
        throw std::runtime_error("Too many bytes requested!");
    }

    std::memcpy(bytes, m_data.data() + m_index, length);
    m_index += length;
}

const std::vector<uint8_t>& CompressionStream::data() const
{
    return m_data;
}

