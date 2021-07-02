/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerStringUnicode.h
    \brief Declaration of the base class used by the string handlers that need to work
            with different charsets.

*/

#if !defined(imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "charsetConversionImpl.h"
#include "dataHandlerImpl.h"
#include <memory>
#include <vector>
#include <string>


namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for all the data handlers
///         that manage strings.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUnicode : public readingDataHandler
{
public:
    readingDataHandlerStringUnicode(const memory& parseMemory, const std::shared_ptr<const charsetsList_t>& pCharsets, tagVR_t dataType, const wchar_t separator, const std::uint8_t paddingByte);

    // Get the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual std::int32_t getInt32(const size_t index) const override;

    // Get the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t getUint32(const size_t index) const override;

    // Get the data element as a int16
    ///////////////////////////////////////////////////////////
    virtual std::int16_t getInt16(const size_t index) const override;

    // Get the data element as a uint16
    ///////////////////////////////////////////////////////////
    virtual std::uint16_t getUint16(const size_t index) const override;

    // Get the data element as a int9
    ///////////////////////////////////////////////////////////
    virtual std::int8_t getInt8(const size_t index) const override;

    // Get the data element as a uint8
    ///////////////////////////////////////////////////////////
    virtual std::uint8_t getUint8(const size_t index) const override;

    // Get the data element as a double
    ///////////////////////////////////////////////////////////
    virtual double getDouble(const size_t index) const override;

    // Get the data element as a double
    ///////////////////////////////////////////////////////////
    virtual float getFloat(const size_t index) const override;

    // Get the data element as a string
    ///////////////////////////////////////////////////////////
    virtual std::string getString(const size_t index) const override;

    // Get the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual std::wstring getUnicodeString(const size_t index) const override;

    // Retrieve the data element as a string
    ///////////////////////////////////////////////////////////
    virtual size_t getSize() const override;

protected:
    std::vector<std::wstring> m_strings;
};


class writingDataHandlerStringUnicode : public writingDataHandler
{
public:
    writingDataHandlerStringUnicode(const std::shared_ptr<buffer>& pBuffer, const std::shared_ptr<const charsetsList_t>& pCharsets, tagVR_t dataType, const wchar_t separator, const size_t unitSize, const size_t maxSize);

    ~writingDataHandlerStringUnicode() override;

    // Set the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual void setInt32(const size_t index, const std::int32_t value) override;

    // Set the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual void setUint32(const size_t index, const std::uint32_t value) override;

    // Set the data element as a int16
    ///////////////////////////////////////////////////////////
    virtual void setInt16(const size_t index, const std::int16_t value) override;

    // Set the data element as a uint16
    ///////////////////////////////////////////////////////////
    virtual void setUint16(const size_t index, const std::uint16_t value) override;

    // Set the data element as a int8
    ///////////////////////////////////////////////////////////
    virtual void setInt8(const size_t index, const std::int8_t value) override;

    // Set the data element as a uint8
    ///////////////////////////////////////////////////////////
    virtual void setUint8(const size_t index, const std::uint8_t value) override;

    // Set the data element as a double
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value) override;

    // Set the data element as a float
    ///////////////////////////////////////////////////////////
    virtual void setFloat(const size_t index, const float value) override;

    // Set the buffer's size, in data elements
    ///////////////////////////////////////////////////////////
    virtual void setSize(const size_t elementsNumber) override;

    virtual size_t getSize() const override;

    virtual void setString(const size_t index, const std::string& value) override;

    virtual void setUnicodeString(const size_t index, const std::wstring& value) override;

    // Throw an exception if the content is not valid
    ///////////////////////////////////////////////////////////
    virtual void validate() const;

protected:
    template<typename U> void convertToString(const size_t index, const U value)
    {
        std::wostringstream conversion;
        conversion << +value;
        setUnicodeString(index, conversion.str());
    }

    std::shared_ptr<memory> m_commitMemory;

    std::vector<std::wstring> m_strings;

    const std::shared_ptr<const charsetsList_t> m_pCharsets;

    wchar_t m_separator;
    size_t m_unitSize;
    size_t m_maxSize;

private:

    void buildCommitMemory();


};


} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
