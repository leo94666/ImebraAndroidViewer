/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerStringAS.cpp
    \brief Implementation of the class dataHandlerStringAS.

*/

#include <sstream>
#include <string>
#include <iomanip>
#include "../include/imebra/exceptions.h"
#include "ageImpl.h"
#include "exceptionImpl.h"
#include "dataHandlerStringASImpl.h"
#include "memoryImpl.h"
#include <memory.h>

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
// dataHandlerStringAS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
readingDataHandlerStringAS::readingDataHandlerStringAS(const memory& parseMemory): readingDataHandlerString(parseMemory, tagVR_t::AS, '\\', 0x20)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the age
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<age> readingDataHandlerStringAS::getAge(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::string ageString = getString(index);
    if(ageString.size() != 4)
    {
        IMEBRA_THROW(DataHandlerCorruptedBufferError, "The AGE string should be 4 bytes long but it is "<< ageString.size() << " bytes long");
    }
    std::istringstream ageStream(ageString);
    std::uint32_t ageValue;
    if(!(ageStream >> ageValue))
    {
        IMEBRA_THROW(DataHandlerCorruptedBufferError, "The AGE is not a number");
    }
    char unit = ageString[3];
    if(
            unit != static_cast<char>(ageUnit_t::days) &&
            unit != static_cast<char>(ageUnit_t::weeks) &&
            unit != static_cast<char>(ageUnit_t::months) &&
            unit != static_cast<char>(ageUnit_t::years))
    {
        IMEBRA_THROW(DataHandlerCorruptedBufferError, "The AGE unit should be D, W, M or Y but is ascii code " << +unit);
    }
    return std::make_shared<age>(ageValue, static_cast<ageUnit_t>(unit));

    IMEBRA_FUNCTION_END();
}



writingDataHandlerStringAS::writingDataHandlerStringAS(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerString(pBuffer, tagVR_t::AS, '\\', 4, 4)
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the age
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringAS::setAge(const size_t index, const std::shared_ptr<const age>& pAge)
{
    IMEBRA_FUNCTION_START();

    if(index >= getSize())
    {
        setSize(index + 1);
    }

    std::ostringstream ageStream;
    ageStream << std::setfill('0');
    ageStream << std::setw(3) << pAge->getAgeValue();
    ageStream << std::setw(1) << static_cast<char>(pAge->getAgeUnits());

    setString(index, ageStream.str());

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerStringAS::validate() const
{
    IMEBRA_FUNCTION_START();

    memory parseMemory(m_strings[0].size());
    ::memcpy(parseMemory.data(), m_strings[0].data(), parseMemory.size());
    try
    {
        readingDataHandlerStringAS readingHandler(parseMemory);
    }
    catch(const DataHandlerCorruptedBufferError& e)
    {
        IMEBRA_THROW(DataHandlerConversionError, e.what());
    }
    writingDataHandlerString::validate();

    IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
