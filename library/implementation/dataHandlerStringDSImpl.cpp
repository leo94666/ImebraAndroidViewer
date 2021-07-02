/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerStringDS.cpp
    \brief Implementation of the class dataHandlerStringDS.

*/

#include <sstream>
#include <iomanip>

#include "exceptionImpl.h"
#include "dataHandlerStringDSImpl.h"

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
// dataHandlerStringDS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringDS::readingDataHandlerStringDS(const memory& parseMemory): readingDataHandlerStringNumbers(parseMemory, tagVR_t::DS, '\\', 0x20)
{
}


writingDataHandlerStringDS::writingDataHandlerStringDS(const std::shared_ptr<buffer> pBuffer):
    writingDataHandlerStringNumbers(pBuffer, tagVR_t::DS, '\\', 0, 16)
{

}

} // namespace handlers

} // namespace implementation

} // namespace imebra
