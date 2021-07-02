/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerString.h
    \brief Declaration of the base class used by the string handlers.

*/

#if !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerImpl.h"
#include <vector>
#include <string>


namespace imebra
{

namespace implementation
{

namespace handlers
{

template<class S, typename U> U convertFromString(const typename std::enable_if<std::is_integral<U>::value && std::is_signed<U>::value, S>::type& string)
{
    try
    {
        signed long long value(std::stoll(string));
        if(value < std::numeric_limits<U>::lowest() || value > std::numeric_limits<U>::max())
        {
            IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
        }
        return static_cast<U>(value);
    }
    catch (const std::invalid_argument&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    catch (const std::out_of_range&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
    }
}

template<class S, typename U> U convertFromString(const typename std::enable_if<std::is_integral<U>::value && !std::is_signed<U>::value, S>::type& string)
{
    try
    {
        unsigned long long value(std::stoull(string));
        if(value < std::numeric_limits<U>::lowest() || value > std::numeric_limits<U>::max())
        {
            IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
        }
        return static_cast<U>(value);
    }
    catch (const std::invalid_argument&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    catch (const std::out_of_range&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
    }
}

template<class S, typename U> U convertFromString(const typename std::enable_if<std::is_floating_point<U>::value, S>::type& string)
{
    try
    {
        double value(std::stod(string));
        if(value < std::numeric_limits<U>::lowest() || value > std::numeric_limits<U>::max())
        {
            IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
        }
        return static_cast<U>(value);
    }
    catch (const std::invalid_argument&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    catch (const std::out_of_range&)
    {
        IMEBRA_THROW(DataHandlerConversionError, "The number in the string is out of bound");
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for all the data handlers
///         that manage strings.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerString : public readingDataHandler
{
public:
    readingDataHandlerString(const memory& parseMemory, tagVR_t dataType, const char separator, const std::uint8_t paddingByte);

    virtual std::int32_t getInt32(const size_t index) const override;

    virtual std::uint32_t getUint32(const size_t index) const override;

    virtual std::int16_t getInt16(const size_t index) const override;

    virtual std::uint16_t getUint16(const size_t index) const override;

    virtual std::int8_t getInt8(const size_t index) const override;

    virtual std::uint8_t getUint8(const size_t index) const override;

    virtual double getDouble(const size_t index) const override;

    virtual float getFloat(const size_t index) const override;

    virtual std::string getString(const size_t index) const override;

    virtual std::wstring getUnicodeString(const size_t index) const override;

    virtual size_t getSize() const override;

protected:
    [[ noreturn ]] void throwNumberConversionError() const;

    std::vector<std::string> m_strings;
};


class readingDataHandlerStringNumbers: public readingDataHandlerString
{
public:
    readingDataHandlerStringNumbers(const memory& parseMemory, tagVR_t dataType, const char separator, const std::uint8_t paddingByte);

    virtual std::int32_t getInt32(const size_t index) const override;

    virtual std::uint32_t getUint32(const size_t index) const override;

    virtual std::int16_t getInt16(const size_t index) const override;

    virtual std::uint16_t getUint16(const size_t index) const override;

    virtual std::int8_t getInt8(const size_t index) const override;

    virtual std::uint8_t getUint8(const size_t index) const override;

    virtual double getDouble(const size_t index) const override;

    virtual float getFloat(const size_t index) const override;

};


class writingDataHandlerString : public writingDataHandler
{
public:
    writingDataHandlerString(const std::shared_ptr<buffer>& pBuffer, tagVR_t dataType, const char separator, const size_t unitSize, const size_t maxSize);

    virtual ~writingDataHandlerString() override;

    virtual void setInt32(const size_t index, const std::int32_t value) override;

    virtual void setUint32(const size_t index, const std::uint32_t value) override;

    virtual void setInt16(const size_t index, const std::int16_t value) override;

    virtual void setUint16(const size_t index, const std::uint16_t value) override;

    virtual void setInt8(const size_t index, const std::int8_t value) override;

    virtual void setUint8(const size_t index, const std::uint8_t value) override;

    virtual void setDouble(const size_t index, const double value) override;

    virtual void setFloat(const size_t index, const float value) override;

    virtual void setSize(const size_t elementsNumber) override;

    virtual size_t getSize() const override;

    virtual void setString(const size_t index, const std::string& value) override;

    virtual void setUnicodeString(const size_t index, const std::wstring& value) override;

    // Throw an exception if the content is not valid
    ///////////////////////////////////////////////////////////
    virtual void validate() const;

protected:
    [[ noreturn ]] void throwNumberConversionError() const;

    std::vector<std::string> m_strings;

    char m_separator;
    size_t m_unitSize;
    size_t m_maxSize;

};


class writingDataHandlerStringNumbers: public writingDataHandlerString
{
public:
    writingDataHandlerStringNumbers(const std::shared_ptr<buffer>& pBuffer, tagVR_t dataType, const char separator, const size_t unitSize, const size_t maxSize);

    virtual void setInt32(const size_t index, const std::int32_t value) override;

    virtual void setUint32(const size_t index, const std::uint32_t value) override;

    virtual void setInt16(const size_t index, const std::int16_t value) override;

    virtual void setUint16(const size_t index, const std::uint16_t value) override;

    virtual void setInt8(const size_t index, const std::int8_t value) override;

    virtual void setUint8(const size_t index, const std::uint8_t value) override;

    virtual void setDouble(const size_t index, const double value) override;

    virtual void setFloat(const size_t index, const float value) override;

protected:
    template<typename U> void convertToString(const size_t index, const U value)
    {
        std::ostringstream conversion;
        conversion << +value;
        setString(index, conversion.str());
    }
};


} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
