/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerNumeric.cpp
    \brief Implementation of the handler for the numeric tags.

*/

#include "streamControllerImpl.h"
#include "dataHandlerNumericImpl.h"
#include "memoryImpl.h"
#include "bufferImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

readingDataHandlerNumericBase::readingDataHandlerNumericBase(const std::shared_ptr<const memory>& parseMemory, tagVR_t dataType):
    readingDataHandler(dataType), m_pMemory(parseMemory)
{
}

const std::uint8_t* readingDataHandlerNumericBase::getMemoryBuffer() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->data();

    IMEBRA_FUNCTION_END();
}

size_t readingDataHandlerNumericBase::getMemorySize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size();

    IMEBRA_FUNCTION_END();
}

std::shared_ptr<const memory> readingDataHandlerNumericBase::getMemory() const
{
    return m_pMemory;
}

void readingDataHandlerNumericBase::copyTo(std::shared_ptr<writingDataHandlerNumericBase> pDestination)
{
    IMEBRA_FUNCTION_START();

    if(pDestination->getDataType() == getDataType())
    {
        std::shared_ptr<memory> pDestMemory = pDestination->getMemory();
        std::shared_ptr<const memory> pMemory = getMemory();
        if(pDestMemory->size() < pMemory->size())
        {
            pDestMemory->assignRegion(pMemory->data(), pDestMemory->size(), 0);
        }
        else
        {
            pDestMemory->assignRegion(pMemory->data(), pMemory->size(), 0);
        }

        return;
    }

    imebra::implementation::handlers::writingDataHandlerNumericBase* pHandler(pDestination.get());
    if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::uint8_t>) ||
        dynamic_cast<imebra::implementation::handlers::writingDataHandlerNumeric<std::uint8_t>* >(pHandler) != 0)
    {
        copyTo((std::uint8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::int8_t>))
    {
        copyTo((std::int8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::uint16_t>))
    {
        copyTo((std::uint16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::int16_t>))
    {
        copyTo((std::int16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::uint32_t>))
    {
        copyTo((std::uint32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<std::int32_t>))
    {
        copyTo((std::int32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<float>))
    {
        copyTo((float*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::writingDataHandlerNumeric<double>))
    {
        copyTo((double*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else
    {
        IMEBRA_THROW(std::runtime_error, "Data type not valid");
    }

    IMEBRA_FUNCTION_END();
}


writingDataHandlerNumericBase::writingDataHandlerNumericBase(const std::shared_ptr<buffer> &pBuffer, const size_t initialSize, tagVR_t dataType, size_t unitSize):
    writingDataHandler(pBuffer, dataType), m_pMemory(std::make_shared<memory>(initialSize * unitSize))
{
}

size_t writingDataHandlerNumericBase::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size() / getUnitSize();

    IMEBRA_FUNCTION_END();
}

std::shared_ptr<memory> writingDataHandlerNumericBase::getMemory() const
{
    return m_pMemory;
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerNumericBase::setSize(const size_t elementsNumber)
{
    IMEBRA_FUNCTION_START();

    m_pMemory->resize(elementsNumber * getUnitSize());

    IMEBRA_FUNCTION_END();
}


writingDataHandlerNumericBase::~writingDataHandlerNumericBase()
{
    if(m_buffer != 0)
    {
        m_buffer->commit(m_pMemory);
    }
}

std::uint8_t* writingDataHandlerNumericBase::getMemoryBuffer() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->data();

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerNumericBase::getMemorySize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size();

    IMEBRA_FUNCTION_END();
}

// Copy the data from another handler
///////////////////////////////////////////////////////////
void writingDataHandlerNumericBase::copyFrom(std::shared_ptr<readingDataHandlerNumericBase> pSource)
{
    IMEBRA_FUNCTION_START();

    if(pSource->getDataType() == getDataType())
    {
        std::shared_ptr<const memory> pMemory = pSource->getMemory();
        std::shared_ptr<memory> pDestMemory = getMemory();
        pDestMemory->assign(pMemory->data(), pMemory->size());

        return;
    }

    imebra::implementation::handlers::readingDataHandlerNumericBase* pHandler(pSource.get());
    if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>) ||
        dynamic_cast<imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>* >(pHandler) != 0)
    {
        copyFrom((std::uint8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int8_t>))
    {
        copyFrom((std::int8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint16_t>))
    {
        copyFrom((std::uint16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int16_t>))
    {
        copyFrom((std::int16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint32_t>))
    {
        copyFrom((std::uint32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int32_t>))
    {
        copyFrom((std::int32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<float>))
    {
        copyFrom((float*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<double>))
    {
        copyFrom((double*)pHandler->getMemoryBuffer(), pHandler->getSize());
    }
    else
    {
        IMEBRA_THROW(std::runtime_error, "Data type not valid");
    }

    IMEBRA_FUNCTION_END();

}


std::uint32_t readingDataHandlerAT::getUint32(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    // In low bit endian machine revert the group and tag part
    std::uint32_t value = getValue<std::uint32_t>(index);
    if(streamController::getPlatformEndian() == streamController::tByteOrdering::lowByteEndian)
    {
        std::uint32_t group = value & 0x0000ffffu;
        std::uint32_t id = (value >> 16u) & 0x0000ffffu;
        value = (group << 16) | id;
    }

    return value;

    IMEBRA_FUNCTION_END();
}


std::int32_t readingDataHandlerAT::getInt32(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


std::int16_t readingDataHandlerAT::getInt16(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


std::uint16_t readingDataHandlerAT::getUint16(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


std::int8_t readingDataHandlerAT::getInt8(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


std::uint8_t readingDataHandlerAT::getUint8(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


double readingDataHandlerAT::getDouble(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


float readingDataHandlerAT::getFloat(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setUint32(const size_t index, const std::uint32_t value)
{
    IMEBRA_FUNCTION_START();

    // In low bit endian machine revert the group and tag part
    if(streamController::getPlatformEndian() == streamController::tByteOrdering::lowByteEndian)
    {
        std::uint32_t id = value & 0x0000ffffu;
        std::uint32_t group = (value >> 16u) & 0x0000ffffu;
        setValue<std::uint32_t>(index, id << 16 | group);
    }
    else
    {
        setValue<std::uint32_t>(index, value);
    }

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setInt32(const size_t /* index */, const std::int32_t /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setInt16(const size_t /* index */, const std::int16_t /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setUint16(const size_t /* index */, const std::uint16_t /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setInt8(const size_t /* index */, const std::int8_t /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setUint8(const size_t /* index */, const std::uint8_t /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setDouble(const size_t /* index */, const double /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


void writingDataHandlerAT::setFloat(const size_t /* index */, const float /* value */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerConversionError, "AT tag can handle only uint32 values");

    IMEBRA_FUNCTION_END();
}


}

}

}
