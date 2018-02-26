#include "../../Platform/Platform.h"

#include "ExpandableBufferTest.h"

#include "../ExpandableBuffer.h"

#include "../../Tools/Utils.h"
#include "../../Tools/DebugTrace.h"

#include "../../TestTools/TestException.h"

#include <string>

using AmstelTech::Test::CTestException;

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

using std::string;

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static void PopulateBuffer(
	BYTE *pBuffer,
	const size_t size);

static void CheckBuffer(
	const _tstring &functionName,
	const BYTE * const pBuffer,
	const size_t size);

///////////////////////////////////////////////////////////////////////////////
// CExpandableBufferTest
///////////////////////////////////////////////////////////////////////////////

void CExpandableBufferTest::TestAll()
{
   TestConstruct();
   TestAssign();
   TestCopyConstruct();
   TestExpand();
   TestResize();
   TestRelease();
}

void CExpandableBufferTest::TestConstruct()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   TExpandableBuffer<BYTE> byteBuffer;

   THROW_ON_FAILURE(functionName, 0 == byteBuffer.GetSize());

   TExpandableBuffer<int> intBuffer(10);

   THROW_ON_FAILURE(functionName, 10 == intBuffer.GetSize());

   TExpandableBuffer<string> stringBuffer(1000);

   THROW_ON_FAILURE(functionName, 1000 == stringBuffer.GetSize());

   Output(functionName + _T(" - stop"));
}

void CExpandableBufferTest::TestAssign()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestAssign");
   
   Output(functionName + _T(" - start"));

   const size_t bufferSize = 500;

   TExpandableBuffer<BYTE> byteBuffer(bufferSize);

   BYTE *pBuffer1 = byteBuffer.GetBuffer();

   PopulateBuffer(pBuffer1, bufferSize);

   TExpandableBuffer<BYTE> byteBuffer2(10);

   BYTE *pBuffer2 = byteBuffer2.GetBuffer();
   
   memset(pBuffer2, 77, byteBuffer2.GetSize());

   byteBuffer2 = byteBuffer;

   THROW_ON_FAILURE(functionName, pBuffer2 != byteBuffer2.GetBuffer());
 
   THROW_ON_FAILURE(functionName, byteBuffer.GetBuffer() != byteBuffer2.GetBuffer());
 
   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   THROW_ON_FAILURE(functionName, byteBuffer.GetSize() == byteBuffer2.GetSize());

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer2.GetSize());

   BYTE *pBuffer3 = byteBuffer2.GetBuffer();

   CheckBuffer(functionName, pBuffer1, bufferSize);
   CheckBuffer(functionName, pBuffer3, bufferSize);

   Output(functionName + _T(" - stop"));
}

void CExpandableBufferTest::TestCopyConstruct()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestCopyConstruct");
   
   Output(functionName + _T(" - start"));

   const size_t bufferSize = 500;

   TExpandableBuffer<BYTE> byteBuffer(bufferSize);

   BYTE *pBuffer1 = byteBuffer.GetBuffer();

   PopulateBuffer(pBuffer1, bufferSize);

   TExpandableBuffer<BYTE> byteBuffer2(byteBuffer);

   THROW_ON_FAILURE(functionName, byteBuffer.GetBuffer() != byteBuffer2.GetBuffer());
 
   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   THROW_ON_FAILURE(functionName, byteBuffer.GetSize() == byteBuffer2.GetSize());

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer2.GetSize());

   BYTE *pBuffer2 = byteBuffer2.GetBuffer();

   CheckBuffer(functionName, pBuffer1, bufferSize);
   CheckBuffer(functionName, pBuffer2, bufferSize);

   Output(functionName + _T(" - stop"));
}

void CExpandableBufferTest::TestExpand()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestExpand");
   
   Output(functionName + _T(" - start"));

   const size_t bufferSize = 500;

   TExpandableBuffer<BYTE> byteBuffer(bufferSize);

   BYTE *pBuffer1 = byteBuffer.GetBuffer();

   PopulateBuffer(pBuffer1, bufferSize);

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Expand(0));

   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Expand(bufferSize));

   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   const size_t newBufferSize = bufferSize * 3;

   THROW_ON_FAILURE(functionName, newBufferSize == byteBuffer.Expand(newBufferSize));

   BYTE *pBuffer2 = byteBuffer.GetBuffer();

   THROW_ON_FAILURE(functionName, pBuffer1 != pBuffer2);

   CheckBuffer(functionName, pBuffer2, bufferSize);

   Output(functionName + _T(" - stop"));
}

void CExpandableBufferTest::TestResize()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestResize");
   
   Output(functionName + _T(" - start"));

   const size_t bufferSize = 500;

   TExpandableBuffer<BYTE> byteBuffer(bufferSize);

   BYTE *pBuffer1 = byteBuffer.GetBuffer();

   PopulateBuffer(pBuffer1, bufferSize);

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Resize(0));

   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Resize(bufferSize));

   THROW_ON_FAILURE(functionName, pBuffer1 == byteBuffer.GetBuffer());

   const size_t newBufferSize = bufferSize * 3;

   THROW_ON_FAILURE(functionName, newBufferSize == byteBuffer.Resize(newBufferSize));

   BYTE *pBuffer2 = byteBuffer.GetBuffer();

   THROW_ON_FAILURE(functionName, pBuffer1 != pBuffer2);

   Output(functionName + _T(" - stop"));
}

void CExpandableBufferTest::TestRelease()
{
   const _tstring functionName = _T("CExpandableBufferTest::TestRelease");
   
   Output(functionName + _T(" - start"));

   const size_t bufferSize = 500;

   TExpandableBuffer<BYTE> byteBuffer(bufferSize);

   BYTE *pBuffer1 = byteBuffer.GetBuffer();

   PopulateBuffer(pBuffer1, bufferSize);

   BYTE *pBuffer2 = byteBuffer.ReleaseBuffer();

   THROW_ON_FAILURE(functionName, 0 == byteBuffer.GetBuffer());

   THROW_ON_FAILURE(functionName, 0 == byteBuffer.GetSize());

   THROW_ON_FAILURE(functionName, pBuffer1 == pBuffer2);

   CheckBuffer(functionName, pBuffer2, bufferSize);

   delete [] pBuffer2;

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Resize(bufferSize));

   delete [] byteBuffer.ReleaseBuffer();

   THROW_ON_FAILURE(functionName, bufferSize == byteBuffer.Expand(bufferSize));

   delete [] byteBuffer.ReleaseBuffer();

   Output(functionName + _T(" - stop"));
}

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static void PopulateBuffer(
	BYTE *pBuffer,
	const size_t size)
{
   for (size_t i = 0; i < size; ++i)
   {
      pBuffer[i] = static_cast<BYTE>(i % 256);
   }
}

static void CheckBuffer(
	const _tstring &functionName,
	const BYTE * const pBuffer,
	const size_t size)
{
   for (size_t i = 0; i < size; ++i)
   {
      THROW_ON_FAILURE(functionName, pBuffer[i] == i % 256);
   }
}

} // End of namespace Test
} // End of namespace AmstelTech