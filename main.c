

#include <iostream>

uint8_t swapNoLoop(uint8_t a);
uint8_t swapLoop(uint8_t a);
uint8_t parityOfOnes(uint8_t a);
uint8_t countOfZero(uint8_t a);
uint8_t countOfOne(uint8_t a);

int main()
{
    uint8_t a = 0x36;
    uint8_t wynik = swapLoop(a);

    std::cout << std::hex << (int)wynik << '\n';

    return 0;
}

uint8_t countOfOne(uint8_t a)
{
    uint8_t ret = 0;
    uint8_t hood = 0x01;

    _asm
    {
        xor eax, eax
        xor ebx, ebx

        mov bl, hood
        mov bh , 0x08
        STARTLOOP :
        mov al, a // robocza przestrzen 
            and al, bl

            cmp al, bl
            jz JestJeden
            sub bh , 1
            JestJeden:

        cmp bl, 0x80//0x80 to zbieznik 
            jz ENDLOOP
            shl bl, 1
            jmp STARTLOOP
            ENDLOOP :

        mov ret , bh
    }
    return ret;

}

uint8_t countOfZero(uint8_t a)
{
    uint8_t ret = 0;
    uint8_t hood = 0x01;

    _asm
    {
        xor eax, eax
        xor ebx, ebx
        mov ah, 0x08
        mov bl, hood
        
        
        STARTLOOP:
            mov al, a 
            and al, bl
            cmp al, bl
            jz JestJeden
            sub ah , 1
            JestJeden:

            cmp bl, 0x80//0x80 to zbieznik 
            jz ENDLOOP
            shl bl, 1
            jmp STARTLOOP
            ENDLOOP :

        mov bh , 0x08
        sub bh ,  ah
        mov ret , bh
    }
    return ret;

}

uint8_t parityOfOnes(uint8_t a)
{
    uint8_t ret = 0;
    uint8_t hood = 0x01;

    _asm
    {
        xor eax,eax
        xor ebx,ebx

        mov bl, hood
        STARTLOOP:
        mov al , a // robocza przestrzen 
        and al , bl

        cmp al , bl
        jnz NieMaJeden
        add bh , 1
        NieMaJeden:

        cmp bl , 0x80//0x80 to zbieznik 
        jz ENDLOOP
        shl bl , 1
        jmp STARTLOOP
        ENDLOOP:
        
        mov ah , 0x01
        and ah , bh

        cmp ah , 0x00
        jz PARZYSTA
        NIEPARZYSTA:
        mov ret , 0
        jmp ENDFUNCTION
        PARZYSTA:
        mov ret , 1
        ENDFUNCTION:

    }
    return ret;

}

uint8_t swapLoop(uint8_t a)
{
    uint8_t ret = 0;


    _asm
    {
        xor eax, eax
        xor ebx, ebx



        mov bl, 0x01
        mov bh, 0x80
       

        STARTLOOP :
        mov al, a
        and al, bh

            cmp al, bh
            jnz NIEJEST
            or ah, bl
            NIEJEST :
            shl bl, 1
            shr bh, 1
            cmp bh, 0x00
            jz ENDLOOP
            jmp STARTLOOP
            ENDLOOP :
        mov ret ,ah
    }
    return ret;
}




uint8_t swapNoLoop(uint8_t a)
{
    uint8_t ret = 0;

    _asm
    {
        xor eax, eax
        xor ebx, ebx

        mov al, a
        mov bl, 0x01
        and al, bl
        shl al, 7
        or ah, al

        mov al, a
        mov bl, 0x02
        and al, bl
        shl al, 5
        or ah, al

        mov al, a
        mov bl, 0x04
        and al, bl
        shl al, 3
        or ah, al

        mov al, a
        mov bl, 0x08
        and al, bl
        shl al, 1
        or ah, al

        mov al, a
        mov bl, 0x10
        and al, bl
        shr al, 1
        or ah, al

        mov al, a
        mov bl, 0x20
        and al, bl
        shr al, 3
        or ah, al

        mov al, a
        mov bl, 0x40
        and al, bl
        shr al, 5
        or ah, al

        mov al, a
        mov bl, 0x80
        and al, bl
        shr al, 7
        or ah, al

        mov ret, ah




    }
    return ret;
}
