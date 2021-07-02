/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerNumeric.h
    \brief Declaration of the handler for the numeric tags.

*/

#if !defined(imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_)
#define imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_

#include <sstream>
#include <iomanip>
#include <type_traits>
#include <numeric>
#include <string>
#include "../include/imebra/exceptions.h"
#include "exceptionImpl.h"
#include "dataHandlerImpl.h"
#include "memoryImpl.h"
#include "charsetConversionImpl.h"



namespace imebra
{

namespace implementation
{

namespace handlers
{

class writingDataHandlerNumericBase;

/// \brief This is the base class for the %data handlers
///         that manage numeric values.
///
///////////////////////////////////////////////////////////
class readingDataHandlerNumericBase: public readingDataHandler
{
public:
    readingDataHandlerNumericBase(const std::shared_ptr<const memory>& pMemory, tagVR_t dataType);

    const std::uint8_t* getMemoryBuffer() const;

    size_t getMemorySize() const;

    std::shared_ptr<const memory> getMemory() const;

    virtual void copyTo(std::shared_ptr<writingDataHandlerNumericBase> pDestination);
    virtual void copyTo(std::uint8_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int8_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::uint16_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int16_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::uint32_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int32_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(float* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(double* pMemory, size_t memorySize) const = 0;

    virtual void copyToInt32Interleaved(std::int32_t* pDest,
                                        std::uint32_t destSubSampleX,
                                        std::uint32_t destSubSampleY,
                                        std::uint32_t sourceStartCol,
                                        std::uint32_t sourceStartRow,
                                        std::uint32_t sourceEndCol,
                                        std::uint32_t sourceEndRow,
                                        std::uint32_t sourceStartChannel,
                                        std::uint32_t sourceWidth,
                                        std::uint32_t sourceHeight,
                                        std::uint32_t sourceNumChannels) const = 0;

    /// \brief Returns truen if the buffer's elements are
    ///         signed, false otherwise.
    ///
    /// @return true if the buffer's elements are signed,
    ///          or false otherwise
    ///
    ///////////////////////////////////////////////////////////
    virtual bool isSigned() const = 0;

    virtual bool isFloat() const = 0;

    virtual size_t getUnitSize() const = 0;

protected:
    // Memory buffer
    ///////////////////////////////////////////////////////////
    std::shared_ptr<const memory> m_pMemory;
};

class writingDataHandlerNumericBase: public writingDataHandler
{
public:
    writingDataHandlerNumericBase(const std::shared_ptr<buffer>& pBuffer, const size_t initialSize, tagVR_t dataType, size_t unitSize);
    ~writingDataHandlerNumericBase();

    std::uint8_t* getMemoryBuffer() const;

    size_t getMemorySize() const;

    virtual size_t getSize() const override;

    std::shared_ptr<memory> getMemory() const;

    // Set the buffer's size, in data elements
    ///////////////////////////////////////////////////////////
    virtual void setSize(const size_t elementsNumber) override;

    virtual void copyFromInt32Interleaved(const std::int32_t* pSource,
                                          std::uint32_t sourceReplicateX,
                                          std::uint32_t sourceReplicateY,
                                          std::uint32_t destStartCol,
                                          std::uint32_t destStartRow,
                                          std::uint32_t destEndCol,
                                          std::uint32_t destEndRow,
                                          std::uint32_t destStartChannel,
                                          std::uint32_t destWidth,
                                          std::uint32_t destHeight,
                                          std::uint32_t destNumChannels) = 0;

    void copyFrom(std::shared_ptr<readingDataHandlerNumericBase> pSource);

    virtual void copyFrom(const std::uint8_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const std::int8_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const std::uint16_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const std::int16_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const std::uint32_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const std::int32_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const float* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(const double* pMemory, size_t memorySize) = 0;

    virtual bool isSigned() const = 0;

    virtual bool isFloat() const = 0;

    virtual size_t getUnitSize() const = 0;

protected:
    // Memory buffer
    ///////////////////////////////////////////////////////////
    std::shared_ptr<memory> m_pMemory;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This data handler accesses to the numeric data
///         stored in a imebra::implementation::buffer class.
///
/// A special definition of this class
///  (imebra::implementation::handlers::imageHandler) is used
///  to access to the images' raw pixels.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<class dataHandlerType>
class readingDataHandlerNumeric : public readingDataHandlerNumericBase
{
public:
    typedef dataHandlerType value_type;

    readingDataHandlerNumeric(const std::shared_ptr<const memory>& pMemory, tagVR_t dataType): readingDataHandlerNumericBase(pMemory, dataType)
    {

    }

    virtual bool isSigned() const override
    {
        return std::is_signed<dataHandlerType>::value;
    }

    virtual bool isFloat() const override
    {
        return std::is_floating_point<dataHandlerType>::value;
    }

    virtual size_t getUnitSize() const override
    {
        return sizeof(dataHandlerType);
    }

    // Specialized getValue() methods with range checks
    //
    ///////////////////////////////////////////////////////////
    template<typename U>
    typename std::enable_if<std::is_same<U, dataHandlerType>::value, U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        return reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value == std::is_integral<dataHandlerType>::value &&
                   (std::is_signed<U>::value == std::is_signed<dataHandlerType>::value || std::is_signed<U>::value) &&
                   sizeof(dataHandlerType) < sizeof(U),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        return static_cast<U>(reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index]);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value == std::is_integral<dataHandlerType>::value &&
                   std::is_signed<U>::value == std::is_signed<dataHandlerType>::value &&
                   sizeof(U) < sizeof(dataHandlerType),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp < std::numeric_limits<U>::lowest() || temp > std::numeric_limits<U>::max())
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to lower precision (out of range)")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value &&
                   std::is_integral<dataHandlerType>::value &&
                   std::is_signed<U>::value &&
                   !std::is_signed<dataHandlerType>::value &&
                   sizeof(U) < sizeof(dataHandlerType),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp > static_cast<dataHandlerType>(std::numeric_limits<U>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to an integer with lower precision (out of range)")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value &&
                   std::is_integral<dataHandlerType>::value &&
                   !std::is_signed<U>::value &&
                   std::is_signed<dataHandlerType>::value &&
                   sizeof(U) < sizeof(dataHandlerType),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp < 0 || temp > static_cast<dataHandlerType>(std::numeric_limits<U>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to an integer with lower precision (out of range)")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value &&
                   std::is_integral<dataHandlerType>::value &&
                   !std::is_signed<U>::value &&
                   std::is_signed<dataHandlerType>::value &&
                   sizeof(U) == sizeof(dataHandlerType),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp < 0)
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert a signed integer to an unsigned integer")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value &&
                   std::is_integral<dataHandlerType>::value &&
                   std::is_signed<U>::value &&
                   !std::is_signed<dataHandlerType>::value &&
                   sizeof(U) == sizeof(dataHandlerType),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp > static_cast<dataHandlerType>(std::numeric_limits<U>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert an unsigned integer to a signed integer")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   !std::is_same<U, dataHandlerType>::value &&
                   std::is_integral<U>::value &&
                   std::is_integral<dataHandlerType>::value &&
                   !std::is_signed<U>::value &&
                   std::is_signed<dataHandlerType>::value &&
                   sizeof(dataHandlerType) < sizeof(U),
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp < 0)
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to an unsigned integer (negative value)")
        }

        return static_cast<U>(temp);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_floating_point<U>::value &&
                   std::is_integral<dataHandlerType>::value,
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        return static_cast<U>(reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index]);
    }

    template<typename U>
    typename std::enable_if<
                   std::is_integral<U>::value &&
                   std::is_floating_point<dataHandlerType>::value,
                   U>::type getValue(const size_t index) const
    {
        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        dataHandlerType temp = reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index];
        if(temp < static_cast<dataHandlerType>(std::numeric_limits<U>::lowest()) || temp > static_cast<dataHandlerType>(std::numeric_limits<U>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to lower precision (out of range)")
        }

        return static_cast<U>(temp);
    }

    // Retrieve the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual std::int32_t getInt32(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::int32_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element an unsigned long
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t getUint32(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::uint32_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as std::int16_t
    ///////////////////////////////////////////////////////////
    virtual std::int16_t getInt16(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::int16_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element an std::uint16_t
    ///////////////////////////////////////////////////////////
    virtual std::uint16_t getUint16(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::uint16_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as std::int16_t
    ///////////////////////////////////////////////////////////
    virtual std::int8_t getInt8(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::int8_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element an std::uint16_t
    ///////////////////////////////////////////////////////////
    virtual std::uint8_t getUint8(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<std::uint8_t>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as a double
    ///////////////////////////////////////////////////////////
    virtual double getDouble(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<double>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as a double
    ///////////////////////////////////////////////////////////
    virtual float getFloat(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        return getValue<float>(index);

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as a string
    ///////////////////////////////////////////////////////////
    virtual std::string getString(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        return std::to_string(+(reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index]));

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the data element as a unicode string
    ///////////////////////////////////////////////////////////
    virtual std::wstring getUnicodeString(const size_t index) const override
    {
        IMEBRA_FUNCTION_START();

        if(index >= getSize())
        {
            IMEBRA_THROW(MissingItemError, "Missing item " << index);
        }

        return std::to_wstring(+(reinterpret_cast<const dataHandlerType*>(m_pMemory->data())[index]));

        IMEBRA_FUNCTION_END();
    }

    // Retrieve the buffer's size in elements
    ///////////////////////////////////////////////////////////
    virtual size_t getSize() const override
    {
        IMEBRA_FUNCTION_START();

        if(m_pMemory.get() == 0)
        {
            return 0;
        }
        return m_pMemory->size() / sizeof(dataHandlerType);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::uint8_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::int8_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::uint16_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::int16_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::uint32_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(std::int32_t* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(float* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyTo(double* pMemory, size_t memorySize) const override
    {
        IMEBRA_FUNCTION_START();

        copyToMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }


    /// \brief Copy the buffer controlled by the handler into
    ///         an array of std::int32_t values, considering that
    ///         the destination buffer could be subsampled
    ///
    /// The destination buffer is supposed to have the
    ///  information related to a single channel.
    /// @param pDest        a pointer to the destination array
    ///                      of std::int32_t values
    /// @param destSubSampleX the horizontal subsamplig
    ///                      factor of the destination buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param destSubSampleY the vertical subsamplig
    ///                      factor of the destination buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param sourceStartCol the horizontal coordinate of the
    ///                      top left corner of the source
    ///                      rectangle
    /// @param sourceStartRow the vertical coordinate of the
    ///                      top left corner of the source
    ///                      rectangle
    /// @param sourceEndCol   the horizontal coordinate of the
    ///                      bottom right corner of the
    ///                      source rectangle
    /// @param sourceEndRow   the vertical coordinate of the
    ///                      bottom right corner of the
    ///                      source rectangle
    /// @param sourceStartChannel the source channel to be
    ///                      copied
    /// @param sourceWidth  the source buffer's width in
    ///                      pixels
    /// @param sourceHeight the source buffer's height in
    ///                      pixels
    /// @param sourceNumChannels the number of channels in the
    ///                      source buffer
    ///
    ///////////////////////////////////////////////////////////
    virtual void copyToInt32Interleaved(std::int32_t* pDest,
                                        std::uint32_t destSubSampleX,
                                        std::uint32_t destSubSampleY,
                                        std::uint32_t sourceStartCol,
                                        std::uint32_t sourceStartRow,
                                        std::uint32_t sourceEndCol,
                                        std::uint32_t sourceEndRow,
                                        std::uint32_t sourceStartChannel,
                                        std::uint32_t sourceWidth,
                                        std::uint32_t sourceHeight,
                                        std::uint32_t sourceNumChannels) const override
    {
        IMEBRA_FUNCTION_START();

        if(sourceStartCol >= sourceWidth || sourceStartRow >= sourceHeight)
        {
            return;
        }

        if(destSubSampleX == 1 && destSubSampleY == 1)
        {
            std::int32_t lastValue(0);
            for(std::uint32_t scanRow(sourceStartRow); scanRow != sourceEndRow; ++scanRow)
            {
                const dataHandlerType *pSource = &(((const dataHandlerType*)m_pMemory->data())[(scanRow * sourceWidth + sourceStartCol) * sourceNumChannels + sourceStartChannel]);
                for(std::uint32_t scanCol(sourceStartCol); scanCol != sourceEndCol; ++scanCol)
                {
                    if(scanCol < sourceWidth && scanRow < sourceHeight)
                    {
                        lastValue = (std::int32_t)*pSource;
                        pSource += sourceNumChannels;
                    }
                    *pDest++ = lastValue;
                }
            }
            return;
        }

        for(std::uint32_t scanRow = sourceStartRow; scanRow != sourceEndRow; ++scanRow)
        {
            const dataHandlerType *pSourceRowScan = &(((const dataHandlerType*)m_pMemory->data())[(scanRow * sourceWidth + sourceStartCol) * sourceNumChannels + sourceStartChannel]);
            std::int32_t* pDestRowAddress = &pDest[((sourceEndCol - sourceStartCol) / destSubSampleX) * ((scanRow - sourceStartRow) / destSubSampleY)];

            for(std::uint32_t scanCol(sourceStartCol); scanCol != sourceEndCol; ++scanCol)
            {
                if(scanCol < sourceWidth && scanRow < sourceHeight)
                {
                    pDestRowAddress[(scanCol - sourceStartCol) / destSubSampleX] += static_cast<std::int32_t>(*pSourceRowScan) * 8 + 1;
                    pSourceRowScan += sourceNumChannels;
                }
            }
        }

        for(std::uint32_t scanRow = sourceStartRow; scanRow < sourceEndRow; scanRow += destSubSampleY)
        {
            std::int32_t* pDestRowAddress = &pDest[(sourceEndCol - sourceStartCol) * (scanRow - sourceStartRow) / (destSubSampleY * destSubSampleX)];

            for(std::uint32_t scanCol(sourceStartCol); scanCol < sourceEndCol; scanCol += destSubSampleX)
            {
                std::int32_t cellValue = pDestRowAddress[(scanCol - sourceStartCol) / destSubSampleX];
                std::int32_t divisor = 8 * (cellValue & 0x7);
                if(divisor == 0)
                {
                    divisor = 8;
                }
                pDestRowAddress[(scanCol - sourceStartCol) / destSubSampleX] = (cellValue & -8) / divisor;
            }
        }

        IMEBRA_FUNCTION_END();
    }

protected:
    template<class destHandlerType>
    void copyToMemory(destHandlerType* pDestination, size_t destSize) const
    {
        IMEBRA_FUNCTION_START();

        if(getSize() < destSize)
        {
            destSize = getSize();
        }
        if(destSize != 0)
        {
            const dataHandlerType* pSource((const dataHandlerType*)m_pMemory->data());
            while(destSize-- != 0)
            {
                *(pDestination++) = (destHandlerType)*(pSource++);
            }
        }

        IMEBRA_FUNCTION_END();
    }
};

template<class dataHandlerType>
class writingDataHandlerNumeric : public writingDataHandlerNumericBase
{
public:
    typedef dataHandlerType value_type;

    writingDataHandlerNumeric(const std::shared_ptr<buffer> &pBuffer, const size_t initialSize, tagVR_t dataType):
        writingDataHandlerNumericBase(
            pBuffer,
            initialSize,
            dataType,
            sizeof(dataHandlerType))
    {
    }

    virtual bool isSigned() const override
    {
        return std::is_signed<dataHandlerType>::value;
    }


    virtual bool isFloat() const override
    {
        return std::is_floating_point<dataHandlerType>::value;
    }

    virtual size_t getUnitSize() const override
    {
        return sizeof(dataHandlerType);
    }

    // Specialized setValue() methods with range checks
    //
    ///////////////////////////////////////////////////////////
    template<typename U>
    void setValue(const size_t index, typename std::enable_if<std::is_same<U, dataHandlerType>::value, U>::type value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = value;
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value == std::is_integral<U>::value &&
                           (std::is_signed<dataHandlerType>::value == std::is_signed<U>::value || std::is_signed<dataHandlerType>::value) &&
                           sizeof(U) < sizeof(dataHandlerType),
                           U>::type value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value == std::is_integral<U>::value &&
                           std::is_signed<dataHandlerType>::value == std::is_signed<U>::value &&
                           sizeof(dataHandlerType) < sizeof(U),
                           U>::type value)
    {
        if(value < std::numeric_limits<dataHandlerType>::lowest() || value > std::numeric_limits<dataHandlerType>::max())
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to lower precision (out of range)")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value &&
                           std::is_integral<U>::value &&
                           std::is_signed<dataHandlerType>::value &&
                           !std::is_signed<U>::value &&
                           sizeof(dataHandlerType) < sizeof(U),
                           U>::type value)
    {
        if(value > static_cast<U>(std::numeric_limits<dataHandlerType>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to lower precision (out of range)")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           !std::is_same<U, dataHandlerType>::value &&
                           std::is_integral<dataHandlerType>::value &&
                           std::is_integral<U>::value &&
                           !std::is_signed<dataHandlerType>::value &&
                           std::is_signed<U>::value &&
                           sizeof(dataHandlerType) < sizeof(U),
                           U>::type value)
    {
        if(value < 0 || value > static_cast<U>(std::numeric_limits<dataHandlerType>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to lower precision (out of range)")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value &&
                           std::is_integral<U>::value &&
                           !std::is_signed<dataHandlerType>::value &&
                           std::is_signed<U>::value &&
                           sizeof(dataHandlerType) == sizeof(U),
                           U>::type value)
    {
        if(value < 0)
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert a signed integer to an unsigned integer")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value &&
                           std::is_integral<U>::value &&
                           std::is_signed<dataHandlerType>::value &&
                           !std::is_signed<U>::value &&
                           sizeof(dataHandlerType) == sizeof(U),
                           U>::type value)
    {
        if(value > static_cast<U>(std::numeric_limits<dataHandlerType>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert an unsigned integer to a signed integer")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value &&
                           std::is_integral<U>::value &&
                           !std::is_signed<dataHandlerType>::value &&
                           std::is_signed<U>::value &&
                           sizeof(U) < sizeof(dataHandlerType),
                           U>::type value)
    {
        if(value < 0)
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to an unsigned integer (negative value)")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_floating_point<dataHandlerType>::value &&
                           std::is_integral<U>::value,
                           U>::type value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    template<typename U>
    void setValue(
            const size_t index,
            typename std::enable_if<
                           std::is_integral<dataHandlerType>::value &&
                           std::is_floating_point<U>::value,
                           U>::type value)
    {
        if(value < static_cast<U>(std::numeric_limits<dataHandlerType>::lowest()) || value > static_cast<U>(std::numeric_limits<dataHandlerType>::max()))
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert to an unsigned integer (negative value)")
        }

        if(index >= getSize())
        {
            setSize(index + 1);
        }

        reinterpret_cast<dataHandlerType*>(m_pMemory->data())[index] = static_cast<dataHandlerType>(value);
    }

    // Set the data element as a std::int32_t
    ///////////////////////////////////////////////////////////
    virtual void setInt32(const size_t index, const std::int32_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::int32_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a std::uint32_t
    ///////////////////////////////////////////////////////////
    virtual void setUint32(const size_t index, const std::uint32_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::uint32_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a std::int16_t
    ///////////////////////////////////////////////////////////
    virtual void setInt16(const size_t index, const std::int16_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::int16_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a std::uint16_t
    ///////////////////////////////////////////////////////////
    virtual void setUint16(const size_t index, const std::uint16_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::uint16_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a std::int8_t
    ///////////////////////////////////////////////////////////
    virtual void setInt8(const size_t index, const std::int8_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::int8_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a std::uint8_t
    ///////////////////////////////////////////////////////////
    virtual void setUint8(const size_t index, const std::uint8_t value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<std::uint8_t>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a double
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<double>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as a float
    ///////////////////////////////////////////////////////////
    virtual void setFloat(const size_t index, const float value) override
    {
        IMEBRA_FUNCTION_START();

        setValue<float>(index, value);

        IMEBRA_FUNCTION_END();
    }

    template<class S, typename U = dataHandlerType>
    void setStringConvert(const size_t index,
            const typename std::enable_if<std::is_integral<U>::value &&
                std::is_signed<U>::value, S>::type& value)
    {
        try
        {
            long long numericValue(std::stoll(value));
            setValue<long long>(index, numericValue);
        }
        catch (const std::out_of_range& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number (out of range)");
        }
        catch(const std::invalid_argument& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number");
        }
    }

    template<class S, typename U = dataHandlerType>
    void setStringConvert(const size_t index,
            const typename std::enable_if<std::is_integral<U>::value &&
                !std::is_signed<U>::value, S>::type& value)
    {
        try
        {
            unsigned long long numericValue(std::stoull(value));
            setValue<unsigned long long>(index, numericValue);
        }
        catch (const std::out_of_range& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number (out of range)");
        }
        catch(const std::invalid_argument& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number");
        }
    }

    template<class S, typename U = dataHandlerType>
    void setStringConvert(const size_t index,
            const typename std::enable_if<std::is_floating_point<U>::value, S>::type& value)
    {
        try
        {
            setValue<double>(index, std::stod(value));
        }
        catch (const std::out_of_range& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number (out of range)");
        }
        catch(const std::invalid_argument& )
        {
            IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the string to a number");
        }
    }

    // Set the data element as a string
    ///////////////////////////////////////////////////////////
    virtual void setString(const size_t index, const std::string& value) override
    {
        IMEBRA_FUNCTION_START();

        setStringConvert<std::string>(index, value);

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual void setUnicodeString(const size_t index, const std::wstring& value) override
    {
        IMEBRA_FUNCTION_START();

        setStringConvert<std::wstring>(index, value);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::uint8_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::int8_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::uint16_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::int16_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::uint32_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const std::int32_t* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const float* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    virtual void copyFrom(const double* pMemory, size_t memorySize) override
    {
        IMEBRA_FUNCTION_START();

        copyFromMemory(pMemory, memorySize);

        IMEBRA_FUNCTION_END();
    }

    template<int subsampleX>
    inline void copyFromInt32Interleaved(
        const std::int32_t* pSource,
        typename std::enable_if < subsampleX == 1, std::uint32_t>::type sourceReplicateY,
        std::uint32_t destStartCol,
        std::uint32_t destStartRow,
        std::uint32_t destEndCol,
        std::uint32_t destEndRow,
        std::uint32_t destStartChannel,
        std::uint32_t destWidth,
        std::uint32_t destHeight,
        std::uint32_t destNumChannels)
    {
        IMEBRA_FUNCTION_START();

        dataHandlerType *pDestRowScan = &(((dataHandlerType*)m_pMemory->data())[(destStartRow*destWidth+destStartCol)*destNumChannels+destStartChannel]);
        const std::int32_t* pSourceRowScan = pSource;

        std::uint32_t replicateYCount = sourceReplicateY;
        const std::uint32_t replicateYIncrease = (destEndCol - destStartCol);

        if(destHeight < destEndRow)
        {
            destEndRow = destHeight;
        }
        if(destWidth < destEndCol)
        {
            destEndCol = destWidth;
        }

        const std::uint32_t numColumns(destEndCol - destStartCol);
        const std::uint32_t horizontalCopyOperations = numColumns;
        const std::uint32_t destRowScanIncrease(destWidth * destNumChannels);

        for(std::uint32_t numYCopies(destEndRow - destStartRow); numYCopies != 0; --numYCopies)
        {
            dataHandlerType* pDestColScan = pDestRowScan;
            const std::int32_t* pSourceColScan = pSourceRowScan;
            const std::int32_t* pSourceEndColScan = pSourceColScan + horizontalCopyOperations;

            while(pSourceColScan != pSourceEndColScan)
            {
                *pDestColScan = (dataHandlerType)(*(pSourceColScan++));
                pDestColScan += destNumChannels;
            }

            pDestRowScan += destRowScanIncrease;
            if(--replicateYCount == 0)
            {
                replicateYCount = sourceReplicateY;
                pSourceRowScan += replicateYIncrease;
            }
        }

        IMEBRA_FUNCTION_END();
    }


    template<int subsampleX>
    inline void copyFromInt32Interleaved(
        const std::int32_t* pSource,
        typename std::enable_if < subsampleX != 1, std::uint32_t>::type sourceReplicateY,
        std::uint32_t destStartCol,
        std::uint32_t destStartRow,
        std::uint32_t destEndCol,
        std::uint32_t destEndRow,
        std::uint32_t destStartChannel,
        std::uint32_t destWidth,
        std::uint32_t destHeight,
        std::uint32_t destNumChannels)
    {
        IMEBRA_FUNCTION_START();

        dataHandlerType* pDestRowScan = &(((dataHandlerType*)m_pMemory->data())[(destStartRow * destWidth + destStartCol) * destNumChannels + destStartChannel]);
        const std::int32_t* pSourceRowScan = pSource;

        std::uint32_t replicateYCount = sourceReplicateY;
        const std::uint32_t replicateYIncrease = (destEndCol - destStartCol) / subsampleX;

        if (destHeight < destEndRow)
        {
            destEndRow = destHeight;
        }
        if (destWidth < destEndCol)
        {
            destEndCol = destWidth;
        }

        const std::uint32_t numColumns(destEndCol - destStartCol);
        const std::uint32_t horizontalCopyOperations = numColumns / subsampleX;
        const std::uint32_t horizontalFinalCopyDest = numColumns - horizontalCopyOperations * subsampleX;
        const std::uint32_t destRowScanIncrease(destWidth * destNumChannels);

        for (std::uint32_t numYCopies(destEndRow - destStartRow); numYCopies != 0; --numYCopies)
        {
            dataHandlerType* pDestColScan = pDestRowScan;
            const std::int32_t* pSourceColScan = pSourceRowScan;
            const std::int32_t* pSourceEndColScan = pSourceColScan + horizontalCopyOperations;

            while (pSourceColScan != pSourceEndColScan)
            {
                const dataHandlerType copyValue = (dataHandlerType)(*(pSourceColScan++));
                for (std::int32_t scanDest = subsampleX; scanDest != 0; --scanDest)
                {
                    *pDestColScan = copyValue;
                    pDestColScan += destNumChannels;
                }
            }

            for (std::uint32_t scanHorizontalFinalCopyDest = horizontalFinalCopyDest; scanHorizontalFinalCopyDest != 0; --scanHorizontalFinalCopyDest)
            {
                *pDestColScan = (dataHandlerType)*pSourceColScan;
                pDestColScan += destNumChannels;
            }

            pDestRowScan += destRowScanIncrease;
            if (--replicateYCount == 0)
            {
                replicateYCount = sourceReplicateY;
                pSourceRowScan += replicateYIncrease;
            }
        }

        IMEBRA_FUNCTION_END();
    }


    /// \brief Copy the content of an array of std::int32_t values
    ///         into the buffer controlled by the handler,
    ///         considering that the source buffer could
    ///         have subsampled data.
    ///
    /// The source buffer is supposed to have the information
    ///  related to a single channel.
    /// @param pSource      a pointer to the source array of
    ///                      std::int32_t values
    /// @param sourceReplicateX the horizontal subsamplig
    ///                      factor of the source buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param sourceReplicateY the vertical subsamplig
    ///                      factor of the source buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param destStartCol the horizontal coordinate of the
    ///                      top left corner of the destination
    ///                      rectangle
    /// @param destStartRow the vertical coordinate of the
    ///                      top left corner of the destination
    ///                      rectangle
    /// @param destEndCol   the horizontal coordinate of the
    ///                      bottom right corner of the
    ///                      destination rectangle
    /// @param destEndRow   the vertical coordinate of the
    ///                      bottom right corner of the
    ///                      destination rectangle
    /// @param destStartChannel the destination channel
    /// @param destWidth    the destination buffer's width in
    ///                      pixels
    /// @param destHeight   the destination buffer's height in
    ///                      pixels
    /// @param destNumChannels the number of channels in the
    ///                      destination buffer
    ///
    ///////////////////////////////////////////////////////////
    virtual void copyFromInt32Interleaved(const std::int32_t* pSource,
                                          std::uint32_t sourceReplicateX,
                                          std::uint32_t sourceReplicateY,
                                          std::uint32_t destStartCol,
                                          std::uint32_t destStartRow,
                                          std::uint32_t destEndCol,
                                          std::uint32_t destEndRow,
                                          std::uint32_t destStartChannel,
                                          std::uint32_t destWidth,
                                          std::uint32_t destHeight,
                                          std::uint32_t destNumChannels) override
    {
        IMEBRA_FUNCTION_START();

        if(destStartCol >= destWidth || destStartRow >= destHeight)
        {
            return;
        }

        switch(sourceReplicateX)
        {
        case 1:
            copyFromInt32Interleaved< 1 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        case 2:
            copyFromInt32Interleaved< 2 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        case 4:
            copyFromInt32Interleaved< 4 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        default:
            IMEBRA_THROW(std::logic_error, "Invalid subsampling factor");
        }

        IMEBRA_FUNCTION_END();
    }

protected:
    /// \brief Copy the values from a memory location to
    ///         the buffer managed by the handler
    ///
    /// @param pSource a pointer to the first byte of the
    ///         memory area to copy
    /// @param sourceSize the number of values to copy
    ///
    ///////////////////////////////////////////////////////////
    template<class sourceHandlerType>
    void copyFromMemory(const sourceHandlerType* pSource, size_t sourceSize)
    {
        IMEBRA_FUNCTION_START();

        setSize(sourceSize);
        dataHandlerType* pDest((dataHandlerType*)m_pMemory->data());
        while(sourceSize-- != 0)
        {
            *(pDest++) = (dataHandlerType)*(pSource++);
        }

        IMEBRA_FUNCTION_END();
    }


};


class readingDataHandlerAT: public readingDataHandlerNumeric<std::uint32_t>
{
public:
    using readingDataHandlerNumeric<std::uint32_t>::readingDataHandlerNumeric;

    virtual std::uint32_t getUint32(const size_t index) const override;

    virtual std::int32_t getInt32(const size_t index) const override;

    virtual std::int16_t getInt16(const size_t index) const override;

    virtual std::uint16_t getUint16(const size_t index) const override;

    virtual std::int8_t getInt8(const size_t index) const override;

    virtual std::uint8_t getUint8(const size_t index) const override;

    virtual double getDouble(const size_t index) const override;

    virtual float getFloat(const size_t index) const override;
};


class writingDataHandlerAT: public writingDataHandlerNumeric<std::uint32_t>
{
public:
    using writingDataHandlerNumeric<std::uint32_t>::writingDataHandlerNumeric;

    virtual void setUint32(const size_t index, const std::uint32_t value) override;

    virtual void setInt32(const size_t index, const std::int32_t value) override;

    virtual void setInt16(const size_t index, const std::int16_t value) override;

    virtual void setUint16(const size_t index, const std::uint16_t value) override;

    virtual void setInt8(const size_t index, const std::int8_t value) override;

    virtual void setUint8(const size_t index, const std::uint8_t value) override;

    virtual void setDouble(const size_t index, const double value) override;

    virtual void setFloat(const size_t index, const float value) override;
};


typedef readingDataHandlerNumeric<std::uint8_t> readingDataHandlerRaw;
typedef readingDataHandlerNumeric<std::uint8_t> readingDataHandlerUint8;
typedef readingDataHandlerNumeric<std::int8_t> readingDataHandlerInt8;
typedef readingDataHandlerNumeric<std::uint16_t> readingDataHandlerUint16;
typedef readingDataHandlerNumeric<std::int16_t> readingDataHandlerInt16;
typedef readingDataHandlerNumeric<std::uint32_t> readingDataHandlerUint32;
typedef readingDataHandlerNumeric<std::int32_t> readingDataHandlerInt32;
typedef readingDataHandlerNumeric<float> readingDataHandlerFloat;
typedef readingDataHandlerNumeric<double> readingDataHandlerDouble;

typedef writingDataHandlerNumeric<std::uint8_t> writingDataHandlerRaw;
typedef writingDataHandlerNumeric<std::uint8_t> writingDataHandlerUint8;
typedef writingDataHandlerNumeric<std::int8_t> writingDataHandlerInt8;
typedef writingDataHandlerNumeric<std::uint16_t> writingDataHandlerUint16;
typedef writingDataHandlerNumeric<std::int16_t> writingDataHandlerInt16;
typedef writingDataHandlerNumeric<std::uint32_t> writingDataHandlerUint32;
typedef writingDataHandlerNumeric<std::int32_t> writingDataHandlerInt32;
typedef writingDataHandlerNumeric<float> writingDataHandlerFloat;
typedef writingDataHandlerNumeric<double> writingDataHandlerDouble;

} // namespace handlers

} // namespace implementation

} // namespace imebra

#define HANDLER_CALL_TEMPLATE_FUNCTION_WITH_PARAMS(functionName, handlerPointer, ...)\
{\
    IMEBRA_FUNCTION_START();\
    imebra::implementation::handlers::readingDataHandlerNumericBase* pHandler(handlerPointer.get()); \
    if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>)) \
    {\
        functionName<std::uint8_t> ((std::uint8_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int8_t>))\
    {\
        functionName<std::int8_t> ((std::int8_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint16_t>))\
    {\
        functionName<std::uint16_t> ((std::uint16_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int16_t>))\
    {\
        functionName<std::int16_t> ((std::int16_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint32_t>))\
    {\
        functionName<std::uint32_t> ((std::uint32_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int32_t>))\
    {\
        functionName<std::int32_t> ((std::int32_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else\
    {\
        IMEBRA_THROW(std::runtime_error, "Data type not valid");\
    }\
    IMEBRA_FUNCTION_END();\
}


#endif // !defined(imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_)
