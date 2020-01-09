#include <stdio.h>
#include "gmp.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void    encode(mpz_t mes, mpz_t pub, mpz_t mod)
{
        mpz_powm(mes, mes, pub, mod);
}

void    decode(mpz_t mes, mpz_t priv, mpz_t mod)
{
        mpz_powm(mes, mes, priv, mod);
}

void    sign(mpz_t mes, mpz_t priv, mpz_t mod)
{
        mpz_powm(mes, mes, priv, mod);
}

void    verify(mpz_t mes, mpz_t pub, mpz_t mod, mpz_t copy)
{
        mpz_powm(mes, mes, pub, mod);
        if (mpz_cmp(mes, copy) == 0)
                printf("verification done\n");
        else
                printf("verification failed\n");
}

void receive_key(mpz_t module, mpz_t my_module, mpz_t my_private, mpz_t Key, mpz_t Sign)
{
	mpz_t pub;
	mpz_init(pub);
	mpz_set_str(pub, "10001", 16);
	decode(Key, my_private, my_module);
	decode(Sign, my_private, my_module);
	verify(Sign, pub, module, Key);
	gmp_printf("Key  is %Zx\nSign is %Zx\n", Key, Sign);
}

void send_key(mpz_t module, mpz_t my_module, mpz_t my_private, mpz_t Message)
{
	mpz_t pub;
	mpz_init(pub);
	mpz_set_str(pub, "10001", 16);
	mpz_t Sign;
	mpz_init(Sign);
	mpz_set(Sign, Message);
	sign(Sign, my_private, my_module);
	encode(Sign, pub, module);
	encode(Message, pub, module);
	gmp_printf("Key is %Zx\nSign is %Zx\n", Message, Sign);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (printf("Usage: %s flag [modulus] [args]\n", argv[0]) && 0);
	if (atoi(argv[1]) == 1)
	{
		if (argc != 7)
			return (printf("Usage: %s [modulus] [Key] [Signature] [my_module] [my_private]\n", argv[0]) && 0);
		mpz_t module;
		mpz_init(module);
		mpz_set_str(module, argv[2], 16);
		mpz_t my_module;
		mpz_init(my_module);
		mpz_set_str(my_module, argv[5], 16);
		mpz_t my_private;
		mpz_init(my_private);
		mpz_set_str(my_private, argv[6], 16);
		mpz_t Key;
		mpz_init(Key);
		mpz_set_str(Key, argv[3], 16);
		mpz_t Sign;
		mpz_init(Sign);
		mpz_set_str(Sign, argv[4], 16);
		receive_key(module, my_module, my_private, Key, Sign);
	}
	if (atoi(argv[1]) == 2)
	{
		printf("%d\n", argc);
		if (argc != 6)
			return (printf("Usage: %s [modulus] [my_modulus] [my_private] [message]", argv[0]) && 0);
		mpz_t module;
		mpz_init(module);
		mpz_set_str(module, argv[2], 16);
		mpz_t my_module;
		mpz_init(my_module);
		mpz_set_str(my_module, argv[3], 16);
		mpz_t my_private;
		mpz_init(my_private);
		mpz_set_str(my_private, argv[4], 16);
		mpz_t Message;
		mpz_init(Message);
		mpz_set_str(Message, argv[5], 10);
		send_key(module, my_module, my_private, Message);
	}
}
