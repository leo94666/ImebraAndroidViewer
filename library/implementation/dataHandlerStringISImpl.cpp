/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerStringIS.cpp
    \brief Implementation of the class dataHandlerStringIS.

*/

#include "exceptionImpl.h"
#include "dataHandlerStringISImpl.h"

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
// dataHandlerStringIS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringIS::readingDataHandlerStringIS(const memory& parseMemory): readingDataHandlerStringNumbers(parseMemory, tagVR_t::IS, '\\', 0x20)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a value as a double.
// Overwritten to use getInt32()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
double readingDataHandlerStringIS::getDouble(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return (double)getInt32(index);

    IMEBRA_FUNCTION_END();
}

writingDataHandlerStringIS::writingDataHandlerStringIS(const std::shared_ptr<buffer> pBuffer):
    writingDataHandlerStringNumbers(pBuffer, tagVR_t::IS, '\\', 0, 12)
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a value as a double.
// Overwritten to use setInt32()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringIS::setDouble(const size_t index, const double value)
{
    IMEBRA_FUNCTION_START();

    if(value > static_cast<double>(std::numeric_limits<std::int32_t>::max()) || value < static_cast<double>(std::numeric_limits<std::int32_t>::lowest()))
    {
        IMEBRA_THROW(DataHandlerConversionError, "Cannot convert the value " << value << " to an integer (out of bounds)");
    }
    setInt32(index, (std::int32_t)value);

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerStringIS::setFloat(const size_t index, const float value)
{
    IMEBRA_FUNCTION_START();

    setDouble(index, static_cast<double>(value));

    IMEBRA_FUNCTION_END();
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
