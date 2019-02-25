#ifndef TEST_INFO_H
#define TEST_INFO_H

#define UNKNOWN_TEST -1

namespace Analyzer
{
	namespace Test
	{
		namespace Dependences
		{
			class TestInfo
			{
				int testId;
				int subTestId;
			public:
				TestInfo ()
				{
					testId = UNKNOWN_TEST;
					subTestId = UNKNOWN_TEST;
				}

				int GetTestId () {return testId;}
				int GetSubTestId () {return subTestId;}
			};
		}
	}
}

#endif