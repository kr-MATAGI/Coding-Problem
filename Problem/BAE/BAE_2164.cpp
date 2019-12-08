#include <iostream>
#include <queue>
#include <vector>

typedef int32_t INT32;

#define CHANGE(flag) flag ? false : true

int main()
{
	// Easy
	// Compile Test
	INT32 N = 0;
	scanf( "%d", &N );
	
	std::queue<INT32> que;
	INT32 input = 1;
	for ( ; input <= N; input++ )
	{
		que.push( input );
	}

	bool isNeedDel = true;
	while ( true )
	{
		const INT32 queSize = static_cast< INT32 >( que.size() );
		if ( 1 == queSize )
		{
			break;
		}

		if ( true == isNeedDel )
		{
			que.pop();
		}
		else
		{
			INT32 moveNum = que.front();
			que.push( moveNum );
			que.pop();
		}

		//isNeedDel = CHANGE( isNeedDel ); // 8ms
		auto flag = []( bool _flag ) -> bool {
			return _flag ? false : true;
		}; // 4ms
		isNeedDel = flag( isNeedDel );
	}

	const INT32 result = que.back();
	printf( "%d", result );



	return 0;
}