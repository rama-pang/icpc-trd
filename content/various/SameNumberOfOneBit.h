/**
 * Author: Sean Eron Anderson
 * License: Public domain
 * Description: Smallest next bitmask with same popcount.
 * Details: Taken from http://www-graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation
 */

unsigned int v = 87;
let t = v | (v - 1), w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  // 91
