#include <iostream>

// 绝对值
int absVal(int x) { return (x + (x >> 31) ^ (x >> 31)); }

int absVal_standard(int x) { return (x < 0) ? -x : x; }

// 负值
int negate(int x) { return (~x) + 1; }

int negate_standard(int x) { return -x; }

// 和
int bitAnd(int x, int y) { return ~((~x) | (~y)); }

int bitAnd_standard(int x, int y) { return x & y; }

// 或
int bitOr(int x, int y) { return ~((~x) & (~y)); }

int bitOr_standard(int x, int y) { return x | y; }

// 异或
int bitXor(int x, int y) { return ~(~x & ~y) & ~(x & y); }

int bitXor_standard(int x, int y) { return x ^ y; }

// 判最大正整数(7FFFFFF)
int isTmax(int x) { return !(~(x + (1 << 31))); }

int isTmax_standard(int x) { return x == 0x7fffffff; }

// 计算x二进制表示中1个数
int bitCount(int x) {
    int n1 = 0x11 | (0x11 << 8);    //0 0 0 0 1 1 1 1
    int num = n1 | (n1 << 16);  //1 1 1 1 1 1 1 1
    int account = x & num;
    account += x >> 1 & num;
    account += x >> 2 & num;
    account += x >> 3 & num;  //分别对各个四位操作
    account += (account >> 16);
    num = 0xf | (0xf << 8);
    account = (account & num) + ((account >> 4) & num);
    return (account + (account >> 8)) & 0x3f;

}

int bitCount_standard(int x) {
    int ret = 0;
    while (x) {
        x &= x - 1;
        ret++;
    }
    return ret;
}

// 产生从lb到hb全为1，其余位为0的数
int bitMask(int highbit, int lowbit) {
    return ((2 << highbit) + (~0)) & ~((1 << lowbit) + (~0));
}

int bitMask_standard(int highbit, int lowbit) {
    int result = 0;
    int i;
    for (i = lowbit; i <= highbit; i++)
        result |= 1 << i;
    return result;
}

// 判x+y是否溢出，若溢出返回1，反之返回0
int addOK(int x, int y) {
    int sum = x + y;
    x = x >> 31;    //取符号位
    y = y >> 31;
    sum = sum >> 31;
    return !(!(~(x ^ y) & (x ^ sum)));
}

int addOK_standard(int x, int y) {
    if (x > 2147483647 - y) {
        return 1;
    } else if (x < -2147483648 - y) {
        return 1;
    } else {
        return 0;
    }
}

// 将x中第n个字节与第m个字节交换，返回交换后结果
int byteSwap(int x, int n, int m) {
    int nTemp = n << 3;
    int mTemp = m << 3;

    int nNum = 0xff << nTemp;
    int mNum = 0xff << mTemp;

    int nByte = ((x & nNum) >> nTemp) & 0xff;
    int mByte = ((x & mNum) >> mTemp) & 0xff;

    int byteNum = nNum | mNum;
    int over = x & ~byteNum;

    return over | (nByte << mTemp) | (mByte << nTemp);
}

int byteSwap_standard(int x, int n, int m) {
    unsigned int nmask, mmask;

    switch (n) {
        case 0:
            nmask = x & 0xFF;
            x &= 0xFFFFFF00;
            break;
        case 1:
            nmask = (x & 0xFF00) >> 8;
            x &= 0xFFFF00FF;
            break;
        case 2:
            nmask = (x & 0xFF0000) >> 16;
            x &= 0xFF00FFFF;
            break;
        default:
            nmask = ((unsigned int) (x & 0xFF000000)) >> 24;
            x &= 0x00FFFFFF;
            break;
    }

    switch (m) {
        case 0:
            mmask = x & 0xFF;
            x &= 0xFFFFFF00;
            break;
        case 1:
            mmask = (x & 0xFF00) >> 8;
            x &= 0xFFFF00FF;
            break;
        case 2:
            mmask = (x & 0xFF0000) >> 16;
            x &= 0xFF00FFFF;
            break;
        default:
            mmask = ((unsigned int) (x & 0xFF000000)) >> 24;
            x &= 0x00FFFFFF;
            break;
    }

    nmask <<= 8 * m;
    mmask <<= 8 * n;

    return x | nmask | mmask;
}

int main() {
    //测试函数，根据需要修改main（）函数
    int x, y, z;
    std::cin >> x >> y >> z;
    while (true) {
//    int x;
//    std::cin >> x;
//    while (x) {
        std::cout << "byteSwap(x)函数值为：" << byteSwap(x, y, z) << std::endl;
        std::cout << "byteSwap_standard(x)函数值为：" << byteSwap_standard(x, y, z) << std::endl;
        if (byteSwap_standard(x, y, z) == byteSwap(x, y, z)) {
            std::cout << "byteSwap()函数与预期一致！" << std::endl;
        }
        if (x == 0 && y == 0 && z == 0) break;
        std::cin >> x >> y >> z;
//        std::cin >> x;
    }
    return 0;
}