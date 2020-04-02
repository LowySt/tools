#ifndef TABLE_GEN_H
#define TABLE_GEN_H

void powersOfTwo(u32 lastPower)
{
    u32 sizeOfBiggestPower = u32(0.3010299957f * lastPower); // This is the log10 of the last Power which tells me approximately the number of digits of it.
    u32 *a = (u32 *)ls_alloc(sizeof(u32)*(sizeOfBiggestPower+2));
    
    u32 m = 1;
    u32 carry = 0;
    a[0] = 1;
    
    char bufferBegin[] = "char powersOfTwo[][] = \r\n{\r\n\t";
    char bufferBeginLine[] = "{\"";
    char bufferEndLine[] = "\"},\r\n\t";
    ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferBegin, sizeof(bufferBegin)-1, TRUE);
    
    char *bufferPowers = (char *)ls_alloc(lastPower);
    u32 idx = 0;
    
    for (u32 i = 1; i <= lastPower; i++)
    {
        for (u32 j = 0; j < m; j++)
        {
            int x = a[j] * 2 + carry;
            a[j] = x % 10;
            carry = x / 10;
        }
        while (carry != 0)
        {
            a[m++] = carry % 10;
            carry /= 10;
        }
        
        for (int k = (m - 1); k > -1; k--)
        {
            bufferPowers[idx++] = ls_itoc(a[k]);
        }
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferBeginLine, sizeof(bufferBeginLine)-1, TRUE);
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferPowers, idx, TRUE);
        ls_WriteFile("C:/Users/loren/Desktop/powersOfTwo.txt", (void *)bufferEndLine, sizeof(bufferEndLine)-1, TRUE);
        idx = 0;
        
    }
    
    char bufferEnd[] = "};";
}

void primes(u64 upperLimit)
{
    char bufferBegin[] = "u64 primes[] = \r\n{\r\n\t";
    ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)bufferBegin, sizeof(bufferBegin) - 1, TRUE);
    
    u32 newline = 0;
    for (u64 i = 1; i < upperLimit; i++)
    {
        for (u64 j = 2; j < i; j++)
        {
            if (i % j == 0)
            { break; }
            if (j == i - 1)
            {
                char *v = ls_itoa(i);
                string print = v; print += ", ";
                if (++newline == 30)
                {
                    newline = 0;
                    print += "\r\n\t";
                }
                ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)print.data, print.size, TRUE);
            }
        }
    }
    
    char end[] = "};";
    ls_WriteFile("C:/Users/loren/Desktop/primes.txt", (void *)end, sizeof(end), TRUE);
}

#endif //TABLE_GEN_H
