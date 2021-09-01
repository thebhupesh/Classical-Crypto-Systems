#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// Playfair Cipher

int pf_key[5][5];
char pf_cipher[50] = "", pf_ptxt[50] = "";
void pf_key_gen(char key[])
{
    int k = 0, flag, flagi = 0, flagj = 0;
    char nkey[25] = "";
    for(int i=0; i<strlen(key); i++)
    {
        flag = 1;
        if(key[i] == 'i')
            flagi = 1;
        else if(key[i] == 'j')
            flagj = 1;
        for(int j=0; j<strlen(nkey); j++)
        {
            if(key[i] == nkey[j] || (flagi == 1 && flagj == 1))
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            nkey[k] = key[i];
            k++;
        }
    }
    for(int i=97; i<=122; i++)
    {
        flag = 1;
        for(int j=0; j<strlen(nkey); j++)
        {
            if(i == nkey[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            if((flagi == 1 || flagj == 1) && (i == 'i' || i == 'j'))
                continue;
            else
            {
                nkey[k] = i;
                k++;
                if(i == 'i')
                    flagi = 1;
            }
        }
    }
    k = 0;
    printf("\nPlayfair Key:\n\n");
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(nkey[k] == 'j')
                nkey[k] = 'i';
            pf_key[i][j] = nkey[k];
            printf("%c\t", pf_key[i][j]);
            k++;
        }
        printf("\n");
    }
}
void pf_enc_search(char a, char b)
{
    int ai = -1, aj, bi = -1, bj, temp;
    char enc[] = "";
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(pf_key[i][j] == a)
            {
                ai = i;
                aj = j;
            }
            else if(pf_key[i][j] == b)
            {
                bi = i;
                bj = j;
            }
        }
        if(ai != -1 && bi != -1)
            break;
    }
    if(aj == bj)
    {
        ai = (ai+1)%5;
        bi = (bi+1)%5;
    }
    else if(ai == bi)
    {
        aj = (aj+1)%5;
        bj = (bj+1)%5;
    }
    else
    {
        temp = aj;
        aj = bj;
        bj = temp;
    }
    enc[0] = pf_key[ai][aj];
    enc[1] = pf_key[bi][bj];
    strncat(pf_cipher, enc, 2);
}
void pf_encrypt(char txt[])
{
    int len = strlen(txt), k = 0;
    if(strlen(txt)%2 != 0)
        len += 1;
    char pair[len/2][2];
    for(int i=0; i<strlen(txt); i++)
    {
        if(txt[i] == 'j')
            txt[i] = 'i';
    }
    for(int i=0; i<strlen(txt);)
    {
        if(txt[i] == txt[i+1])
        {
            pair[k][0] = txt[i];
            pair[k][1] = 'z';
            i++;
            k++;
        }
        else if(i == strlen(txt)-1)
        {
            pair[k][0] = txt[i];
            pair[k][1] = 'z';
            i++;
        }
        else
        {
            pair[k][0] = txt[i];
            pair[k][1] = txt[i+1];
            i += 2;
            k++;
        }
    }
    for(int i=0; i<len/2; i++)
    {
        pf_enc_search(pair[i][0], pair[i][1]);
    }
    printf("\nCiphertext: %s\n", pf_cipher);
}
void pf_dec_search(char a, char b)
{
    int ai = -1, aj, bi = -1, bj, temp;
    char dec[] = "";
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(pf_key[i][j] == a)
            {
                ai = i;
                aj = j;
            }
            else if(pf_key[i][j] == b)
            {
                bi = i;
                bj = j;
            }
        }
        if(ai != -1 && bi != -1)
            break;
    }
    if(aj == bj)
    {
        ai -= 1;
        if(ai<0)
            ai += 5;
        bi -= 1;
        if(bi<0)
            bi += 5;
        ai %= 5;
        bi %= 5;
    }
    else if(ai == bi)
    {
        aj -= 1;
        if(aj<0)
            aj += 5;
        bj -= 1;
        if(bj<0)
            bj += 5;
        aj %= 5;
        bj %= 5;
    }
    else
    {
        temp = aj;
        aj = bj;
        bj = temp;
    }
    dec[0] = pf_key[ai][aj];
    dec[1] = pf_key[bi][bj];
    strncat(pf_ptxt, dec, 2);
}
void pf_decrypt()
{
    int len = strlen(pf_cipher), k = 0;
    char pair[len/2][2];
    for(int i=0; i<strlen(pf_cipher); i += 2)
    {
        pair[k][0] = pf_cipher[i];
        pair[k][1] = pf_cipher[i+1];
        k++;
    }
    for(int i=0; i<len/2; i++)
    {
        pf_dec_search(pair[i][0], pair[i][1]);
    }
    printf("\nPlaintext after decryption: %s\n\nDone!\n\n", pf_ptxt);
}

// Hill Cipher

int h_key[3][3], h_cipher[3][1];
void h_key_gen(char key[])
{
    int k = 0;
    printf("\nHill Cipher Key:\n\n");
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            h_key[i][j] = key[k]-97;
            k++;
            printf("%d\t", h_key[i][j]);
        }
        printf("\n");
    }
}
void h_multiply(int key[3][3], int txt[3][1])
{
    for(int i=0; i<3; i++)
    {
        h_cipher[i][0] = 0;
        for(int j=0; j<3; j++)
        {
            h_cipher[i][0] += key[i][j]*txt[j][0];
        }
        h_cipher[i][0] %= 26;
    }
}
void h_encrypt(char txt[])
{
    int ptxt[3][1], k = 0;
    for(int i=0; i<3; i++)
    {
        ptxt[i][0] = txt[k]-97;
        k++;
    }
    h_multiply(h_key, ptxt);
    printf("\nCiphertext: ");
    for(int i=0; i<3; i++)
    {
        printf("%c", h_cipher[i][0]+97);
    }
    printf("\n");
}
void h_decrypt()
{
    int det = 0, trans_key[3][3], dec_key[3][3], ptxt[3][1];
    for(int i=0; i<3; i++)
        det += (h_key[0][i] * (h_key[1][(i+1)%3] * h_key[2][(i+2)%3] - h_key[1][(i+2)%3] * h_key[2][(i+1)%3]));
    if(det<0)
    {
        det = 26-(abs(det)%26);
    }
    else
        det %= 26;
    for(int i=1;;i++)
    {
        if((i*det)%26 == 1)
        {
            det = i;
            break;
        }
    }
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            trans_key[i][j] = h_key[j][i];
    printf("\nDecryption Key:\n\n");
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            dec_key[i][j] = (trans_key[(i+1)%3][(j+1)%3] * trans_key[(i+2)%3][(j+2)%3]) - (trans_key[(i+1)%3][(j+2)%3]*trans_key[(i+2)%3][(j+1)%3]);
            dec_key[i][j] *= det;
            if(dec_key[i][j]<0)
            {
                dec_key[i][j] = 26-(abs(dec_key[i][j])%26);
            }
            else
                dec_key[i][j] %= 26;
            printf("%d\t",dec_key[i][j]);
        }
        printf("\n");
    }
    printf("\nPlaintext after decryption: ");
    for(int i=0; i<3; i++)
    {
        ptxt[i][0] = 0;
        for(int j=0; j<3; j++)
        {
            ptxt[i][0] += dec_key[i][j]*h_cipher[j][0];
        }
        ptxt[i][0] %= 26;
    }
    for(int i=0; i<3; i++)
    {
        printf("%c", ptxt[i][0]+97);
    }
    printf("\n\nDone!\n\n");
}

// Vigenere Cipher

char vig_sqr[26][26], vig_key[50] = "", vig_cipher[50] = "", vig_ptxt[50] = "";
void vig_sqr_gen()
{
    printf("\nVigenere Square:\n\n");
    for(int i=0; i<26; i++)
    {
        for(int j=i; j<i+26; j++)
        {
            vig_sqr[i][j-i] = (j%26)+97;
            printf("%c ", vig_sqr[i][j-i]);
        }
        printf("\n");
    }
}
void vig_key_gen(char key[], int size)
{
    int n = 0;
    char t_key[50] = "";
    for(int i=0; i<size; i++)
    {
        n += strlen(key);
        strncat(t_key, key, strlen(key));
        if(n>size)
            break;
    }
    strncat(vig_key, t_key, size);
}
void vig_encrypt(char txt[], int size)
{
    int m, n;
    for(int i=0; i<size; i++)
    {
        m = (txt[i]-97)%26;
        n = (vig_key[i]-97)%26;
        vig_cipher[i] = vig_sqr[m][n];
    }
    printf("\nCiphertext: %s\n", vig_cipher);
}
void vig_decrypt(int size)
{
    int m;
    for(int i=0; i<size; i++)
    {
        m = (vig_key[i]-97)%26;
        for(int j=0; j<26; j++)
        {
            if(vig_sqr[m][j] == vig_cipher[i])
            {
                vig_ptxt[i] = j+97;
                break;
            }
        }
    }
    printf("\nPlaintext after decryption: %s\n\nDone!\n\n", vig_ptxt);
}

// Vernam Cipher

char ver_cipher[50] = "", ver_ptxt[50] = "";
void ver_encrypt(char txt[], char key[], int size)
{
    for(int i=0; i<size; i++)
    {
        ver_cipher[i] = ((((txt[i]-97)%26) + ((key[i]-97)%26))%26)+97;
    }
    printf("\nCiphertext: %s\n", ver_cipher);
}
void ver_decrypt(char key[], int size)
{
    for(int i=0; i<size; i++)
    {
        ver_ptxt[i] = ((ver_cipher[i]-97)%26) - ((key[i]-97)%26);
        if(ver_ptxt[i]<0)
            ver_ptxt[i] += 26;
        ver_ptxt[i] = (ver_ptxt[i]%26)+97;
    }
    printf("\nPlaintext after decryption: %s\n\nDone!\n\n", ver_ptxt);
}

// To-Lowercase Function

const char* lower(char str[])
{
    int i = 0;
    while(str[i])
    {
        str[i] = tolower(str[i]);
        i++;
    }
    return str;
}

// Main Function

int main()
{
    int choice;
    while(1)
    {
        printf("---Menu---\n\n1. Plairfair Cipher\n2. Hill Cipher\n3. Vigenere Cipher\n4. Vernam Cipher\n5. Exit\n\nChoice: ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            {
                printf("\n---Playfair Cipher---\n");
                char txt[50], key[50];
                printf("\nPlaintext: ");
                scanf("%s", txt);
                printf("Key: ");
                scanf("%s", key);
                strcpy(txt, lower(txt));
                strcpy(key, lower(key));
                pf_key_gen(key);
                pf_encrypt(txt);
                pf_decrypt();
                break;
            }
        case 2:
            {
                printf("\n---Hill Cipher---\n");
                char txt[50], key[50];
                printf("\nPlaintext: ");
                scanf("%s", txt);
                printf("Key: ");
                scanf("%s", key);
                strcpy(txt, lower(txt));
                strcpy(key, lower(key));
                h_key_gen(key);
                h_encrypt(txt);
                h_decrypt();
                break;
            }
        case 3:
            {
                printf("\n---Vigenere Cipher---\n");
                char txt[50], key[50];
                printf("\nPlaintext: ");
                scanf("%s", txt);
                printf("Key: ");
                scanf("%s", key);
                strcpy(txt, lower(txt));
                strcpy(key, lower(key));
                vig_sqr_gen();
                vig_key_gen(key, strlen(txt));
                vig_encrypt(txt, strlen(txt));
                vig_decrypt(strlen(txt));
                break;
            }
        case 4:
            {
                printf("\n---Vernam Cipher---\n");
                char txt[50], key[50];
                printf("\nPlaintext: ");
                scanf("%s", txt);
                printf("Key: ");
                scanf("%s", key);
                strcpy(txt, lower(txt));
                strcpy(key, lower(key));
                ver_encrypt(txt, key, strlen(key));
                ver_decrypt(key, strlen(key));
                break;
            }
        case 5:
            {
                exit(0);
                break;
            }
        default:
            {
                printf("\nIncorrect Choice!!!\nTry Again.\n\n");
                break;
            }
        }
    }
    return 0;
}
