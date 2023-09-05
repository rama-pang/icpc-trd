/**
 * Author: 
 * Description:
 */
#if __cplusplus < 201799
namespace std{
	template<> struct is_integral<__int128> : true_type {};
	template<> struct is_signed<__int128> : true_type {};
	template<> struct is_integral<unsigned __int128> : true_type {};
	template<> struct is_unsigned<unsigned __int128> : true_type {};
}

#endif

ostream& operator<<(ostream& o, unsigned __int128 x){
	uint64_t const TENPOW19=10000000000000000000;
	if(x<TENPOW19) o<<(uint64_t)x;
	else{
		o<<x/TENPOW19<<
			setfill('0')<<setw(19)
			<<uint64_t(x%TENPOW19);
	}
	return o;
}

ostream& operator<<(ostream& o, __int128 x){
	if(x<0) return o<<'-'<<-(unsigned __int128)x;  // the minimum value causes overflow so cast before negate
	return o<<(unsigned __int128) x;
}

int ctz128(unsigned __int128 a){
	if(a & UINT64_MAX)
		return __builtin_ctzll(uint64_t(a));
	return 64+__builtin_ctzll(uint64_t(a>>64));
}
