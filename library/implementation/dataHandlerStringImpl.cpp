/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerString.cpp
    \brief Implementation of the base class for the string handlers.

*/

#include <sstream>
#include <iomanip>
#include <limits>

#include "exceptionImpl.h"
#include "dataHandlerStringImpl.h"
#include "memoryImpl.h"
#include "bufferImpl.h"
#include "dicomDictImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// readingDataHandlerString
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerString::readingDataHandlerString(const memory &parseMemory, tagVR_t dataType, const char separator, const uint8_t paddingByte):
    readingDataHandler(dataType)
{
    IMEBRA_FUNCTION_START();

    std::string parseString(reinterpret_cast<const char*>(parseMemory.data()), parseMemory.size());
    while(!parseString.empty() && (parseString.back() == static_cast<const char>(paddingByte) || parseString.back() == 0))
    {
        parseString.pop_back();
    }

    if(separator == 0)
    {
        m_strings.push_back(parseString);
        return;
    }

    for(size_t firstPosition(0); ;)
    {
        size_t nextPosition = parseString.find(separator, firstPosition);
        if(nextPosition == std::string::npos)
        {
            m_strings.push_back(parseString.substr(firstPosition));
            return;
        }
        m_strings.push_back(parseString.substr(firstPosition, nextPosition - firstPosition));
        firstPosition = ++nextPosition;
    }

    IMEBRA_FUNCTION_END();
}


void readingDataHandlerString::throwNumberConversionError() const
{
    IMEBRA_THROW(DataHandlerConversionError, "Cannot convert a " << dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()) << " to a number");
}

// Get the data element as a signed long
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerString::getInt32(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unsigned long
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerString::getUint32(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a int16
///////////////////////////////////////////////////////////
std::int16_t readingDataHandlerString::getInt16(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a uint16
///////////////////////////////////////////////////////////
std::uint16_t readingDataHandlerString::getUint16(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a int8
///////////////////////////////////////////////////////////
std::int8_t readingDataHandlerString::getInt8(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a uint8
///////////////////////////////////////////////////////////
std::uint8_t readingDataHandlerString::getUint8(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
double readingDataHandlerString::getDouble(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
float readingDataHandlerString::getFloat(const size_t /* index */) const
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Get the data element as a string
///////////////////////////////////////////////////////////
std::string readingDataHandlerString::getString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    if(index >= getSize())
    {
        IMEBRA_THROW(MissingItemError, "Missing item " << index);
    }

    return m_strings.at(index);

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unicode string
///////////////////////////////////////////////////////////
std::wstring readingDataHandlerString::getUnicodeString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    charsetsList_t charsets;
    charsets.push_back("ISO 2022 IR 6");
    return dicomConversion::convertToUnicode(getString(index), charsets);

    IMEBRA_FUNCTION_END();
}

// Retrieve the data element as a string
///////////////////////////////////////////////////////////
size_t readingDataHandlerString::getSize() const
{
    return m_strings.size();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// readingDataHandlerStringNumbers
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringNumbers::readingDataHandlerStringNumbers(const memory &parseMemory, tagVR_t dataType, const char separator, const uint8_t paddingByte):
    readingDataHandlerString(parseMemory, dataType, separator, paddingByte)
{
}


// Get the data element as a signed long
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerStringNumbers::getInt32(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::int32_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unsigned long
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerStringNumbers::getUint32(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::uint32_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a int16
///////////////////////////////////////////////////////////
std::int16_t readingDataHandlerStringNumbers::getInt16(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::int16_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a uint16
///////////////////////////////////////////////////////////
std::uint16_t readingDataHandlerStringNumbers::getUint16(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::uint16_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a int8
///////////////////////////////////////////////////////////
std::int8_t readingDataHandlerStringNumbers::getInt8(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::int8_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a uint8
///////////////////////////////////////////////////////////
std::uint8_t readingDataHandlerStringNumbers::getUint8(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, std::uint8_t>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
double readingDataHandlerStringNumbers::getDouble(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, double>(getString(index));

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
float readingDataHandlerStringNumbers::getFloat(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return convertFromString<std::string, float>(getString(index));

    IMEBRA_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// writingDataHandlerString
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

writingDataHandlerString::writingDataHandlerString(const std::shared_ptr<buffer> &pBuffer, tagVR_t dataType, const char separator, const size_t unitSize, const size_t maxSize):
    writingDataHandler(pBuffer, dataType), m_separator(separator), m_unitSize(unitSize), m_maxSize(maxSize)
{
}

writingDataHandlerString::~writingDataHandlerString()
{
    std::string completeString;
    for(size_t stringsIterator(0); stringsIterator != m_strings.size(); ++stringsIterator)
    {
        if(stringsIterator != 0)
        {
            completeString += m_separator;
        }
        completeString += m_strings.at(stringsIterator);
    }

    std::shared_ptr<memory> commitMemory = std::make_shared<memory>(completeString.size());
    commitMemory->assign(reinterpret_cast<const std::uint8_t*>(completeString.data()), completeString.size());

    m_buffer->commit(commitMemory);
}


void writingDataHandlerString::throwNumberConversionError() const
{
    IMEBRA_THROW(DataHandlerConversionError, "Cannot convert a number to " << dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()));
}

// Set the data element as a signed long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setInt32(const size_t /* index */, const std::int32_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as an unsigned long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setUint32(const size_t /* index */, const std::uint32_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a int16
///////////////////////////////////////////////////////////
void writingDataHandlerString::setInt16(const size_t /* index */, const std::int16_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a uint16
///////////////////////////////////////////////////////////
void writingDataHandlerString::setUint16(const size_t /* index */, const std::uint16_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a int8
///////////////////////////////////////////////////////////
void writingDataHandlerString::setInt8(const size_t /* index */, const std::int8_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a uint8
///////////////////////////////////////////////////////////
void writingDataHandlerString::setUint8(const size_t /* index */, const std::uint8_t /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerString::setDouble(const size_t /* index */, const double /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerString::setFloat(const size_t /* index */, const float /* value */)
{
    IMEBRA_FUNCTION_START();

    throwNumberConversionError();

    IMEBRA_FUNCTION_END();
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerString::setSize(const size_t elementsNumber)
{
    IMEBRA_FUNCTION_START();

    m_strings.resize(elementsNumber);

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerString::getSize() const
{
    return m_strings.size();
}

void writingDataHandlerString::setString(const size_t index, const std::string& value)
{
    IMEBRA_FUNCTION_START();

    if(m_separator == 0 && index != 0)
    {
        IMEBRA_THROW(DataHandlerInvalidDataError, "Cannot insert more than one item in this string tag");
    }
    if(index >= getSize())
    {
        setSize(index + 1);
    }
    m_strings[index] = value;

    validate();

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerString::setUnicodeString(const size_t index, const std::wstring& value)
{
    IMEBRA_FUNCTION_START();

    charsetsList_t charsets;
    charsets.push_back("ISO_IR 6");
    setString(index, dicomConversion::convertFromUnicode(value, charsets));

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerString::validate() const
{
    IMEBRA_FUNCTION_START();

    validateStringContainer(m_strings, m_maxSize, m_unitSize, m_separator != 0);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// writingDataHandlerStringNumbers
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

writingDataHandlerStringNumbers::writingDataHandlerStringNumbers(const std::shared_ptr<buffer> &pBuffer, tagVR_t dataType, const char separator, const size_t unitSize, const size_t maxSize):
    writingDataHandlerString(pBuffer, dataType, separator, unitSize, maxSize)
{
}

// Set the data element as a signed long
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setInt32(const size_t index, const std::int32_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::int32_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as an unsigned long
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setUint32(const size_t index, const std::uint32_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::uint32_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a int16
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setInt16(const size_t index, const std::int16_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::int16_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a uint16
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setUint16(const size_t index, const std::uint16_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::uint16_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a int8
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setInt8(const size_t index, const std::int8_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::int8_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a uint8
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setUint8(const size_t index, const std::uint8_t value)
{
    IMEBRA_FUNCTION_START();

    convertToString<std::uint8_t>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setDouble(const size_t index, const double value)
{
    IMEBRA_FUNCTION_START();

    convertToString<double>(index, value);

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerStringNumbers::setFloat(const size_t index, const float value)
{
    IMEBRA_FUNCTION_START();

    convertToString<float>(index, value);

    IMEBRA_FUNCTION_END();
}



} // namespace handlers

} // namespace implementation

} // namespace imebra
