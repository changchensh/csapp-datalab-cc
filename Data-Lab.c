第1题：
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return (~(x&y))&(~((~x)&(~y)));
}

第2题：
二进制补码表示的最小值为0x80000000
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}

第3题：
二进制补码表示的最大值为0x7FFFFFFF
tmax+1的相反数是本身，！！x_1是为了消除x=-1的影响
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int x_1=x+1;
  return (!(((~x_1)+1)^x_1))&(!!x_1);
}

第4题：
0xAAAAAAAA正好对应所有奇数位是1的情况
因为题目限制常数只能使用0到255,所以不能直接使用0xAAAAAAAA
通过(0xAA<<8)+0xAA创造0x0000AAAA
通过(half_bits<<16)+half_bits创造0xAAAAAAAA
先用(x&all_bits)清除偶数位
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int half_bits = (0xAA<<8)+0xAA;
  int all_bits = (half_bits<<16)+half_bits;
  return !((x&all_bits)^all_bits);
}

第5题：
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1;
}

第6题：
x-0x30,如果结果的符号位为1,说明x-0x30<0
0x39-x,如果结果的符号位为1,说明0x39-x<0
目标是得到，当x-0x30<0为0,0x39-x<0也为0时，最终结果才为1
001101011000
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int left_bool = ((x+(~0x30)+1)>>31)&1;
  int right_bool = ((0x39+(~x)+1)>>31)&1;
  return !((left_bool^right_bool)|(left_bool&right_bool));
}

第7题：
～0为0xFFFFFFFF
当x!=0时，!x=0, (!(x)+(~0)=0xFFFFFFFF, (j&y)=y, (~j)&z=0
当x==0时，!x=1, (!(x)+(~0)=0, (j&y)=0, (~j)&z=z
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int j = !(x)+(~0);
  return (j&y)|((~j)&z)
}

第8题：
一开始的想法：未考虑x，y异号，在x、y最大和最小时，相减会溢出
改正后的想法：考虑两种情况，
异号时直接看x的符号，x为正数则x>y，否则x<y
同号时相减，看结果的符号
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int x_sign = (x>>31)&1;
  int y_sign = (y>>31)&1;
  int same_or_dif = (x_sign^y_sign);
  return (same_or_dif&x_sign)|(!same_or_dif&!((y+(~x)+1)>>31)&1);
}

第9题：
0和0x80000000的相反数是其本身
利用了0+1=1,0xFFFFFFFF+1=0的规律
如果x==0,则x和x的相反数的符号移位|的结果仍为0
如果x!=0，则x和y的相反数的符号移位|的结果为0xFFFFFFFF
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x>>31)|(((~x)+1)>>31))+1;
}

第10题：
原文链接：https://blog.csdn.net/m0_51335239/article/details/125849757
我想得到第一行的异或统一正负数和之后的分而治之思想，但是不会具体落实，水平还是不够
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int temp = x ^ (x << 1);
    int bit_16,bit_8,bit_4,bit_2,bit_1;
  bit_16 = !!(temp >> 16) << 4;//0或16
  temp = temp >> bit_16;
  bit_8 = !!(temp >> 8) << 3;//0或8
  temp = temp >> bit_8;
  bit_4 = !!(temp >> 4) << 2;//0或4
  temp = temp >> bit_4;
  bit_2 = !!(temp >> 2) << 1;//0或2
  temp = temp >> bit_2;
  bit_1 = !!(temp >> 1);//0或1
    return 1 + bit_1 + bit_2 + bit_4 + bit_8 + bit_16;

                        
}

第11题：
首先判断是不是+0.0和-0.0
new_f是uf的绝对值，我也不知道为什么题目说是unsigned int，测试数据会出现负数0x80000000
然后判断是不是NaN
最后分别处理非规格化和规格化，非规格化数左移一位，规格化数的阶码部分加1
s是uf的符号，|s为了还原uf的符号
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
    int new_f = uf & (~(1<<31));
    if (!new_f)
    {
        if(uf>>31)
        {
            return uf;    
        }
        return 0;  
    }
    else 
    {
        int exp = new_f>>23;
        int s = uf&(1<<31);
        if(!(exp^0xFF)&&(new_f<<8))
        {
            return uf;                
        }
        else if(!exp)
        {
            return (new_f<<1)|s;     
        }else
        {
            return (new_f+(1<<23))|s;
        }        
    } 
}

第12题：
https://www.cnblogs.com/zhiyiYo/p/16242033.html
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4 
 */
int floatFloat2Int(unsigned uf) {
    // 计算阶码
    unsigned exp = (uf & 0x7f800000) >> 23;
    int e = exp - 127;

    // 0或小数直接返回 0
    if (e < 0) {
        return 0;
    }

    // NaN 或者 无穷大
    if (e > 31) {
        return 0x80000000;
    }

    // 尾数
    int frac = (uf & 0x7fffff) | 0x800000;

    // 移动小数点
    if (e > 23) {
        frac <<= (e - 23);
    } else {
        frac >>= (23 - e);
    }

    // 符号位不变
    if (!((uf >> 31) ^ (frac >> 31))) {
        return frac;
    }

    // 符号位变化，且当前符号为负，说明溢出
    if (frac >> 31) {
        return 0x80000000;
    }

    // 符号变化，返回补码
    return ~frac + 1;
}

第13题：
参考原书第三版P82页图2-36内容
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if(x<-149){
        return 0;
    }else if (x>127)
    {
        return 0x7f800000;
    }else
    {
        if(x<-126)
        {
            return 1<<(23+x+126);//非规格化数
        }
        return (x+127)<<23;//规格化数
    }
}
