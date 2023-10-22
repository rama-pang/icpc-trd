/**
 * Author: user202729
 * Description: Initialize mt19937 with high-precision clock seed.
 * Date: 2023-10-22
 */
mt19937 engine(
#if LOCAL
		123456
#else
		chrono::duration_cast<chrono::nanoseconds>(
			chrono::steady_clock::now().time_since_epoch()).count()
#endif
		);

