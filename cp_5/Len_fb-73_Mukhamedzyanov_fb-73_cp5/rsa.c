#include <stdio.h>
#include "gmp.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

static mpz_t    s;
static mpz_t    d;
static mpz_t    one;
static int              k = 0;
static float    saved = 0;
gmp_randstate_t state;
static mp_bitcnt_t bits;
static mpz_t    a;
static mpz_t    j;
static mpz_t    temp;
static mpz_t    n_min;

int             check_often(mpz_t n)
{
        int ret;

        ret = !mpz_cdiv_ui(n, 3) || !mpz_cdiv_ui(n, 5) || !mpz_cdiv_ui(n, 7) ||
                !mpz_cdiv_ui(n, 11)|| !mpz_cdiv_ui(n, 13);
        return (ret);
}

static void            clear_mpz(void)
{
        mpz_clear(s);
        mpz_clear(d);
        mpz_clear(one);
        mpz_clear(a);
        mpz_clear(j);
        mpz_clear(temp);
        mpz_clear(n_min);
}

int             miller_rabin(mpz_t s, mpz_t d, mpz_t n, int count)
{
        mpz_div_ui(n_min, n, 1);
        while (count--)
        {
                mpz_urandomb(a, state, bits);
                mpz_setbit(a, bits);
                mpz_powm(a, a, d, n);
                if (!mpz_cmp_ui(a, 1) || !mpz_cmp(a, n_min))
                        continue;
                mpz_set_ui(j, 1);
                while (mpz_cmp(j, s) < 0)
                {
                        mpz_powm_ui(a, a, 2, n);
                        if (mpz_cmp_ui(a, 1) == 0)
                                return (0);
                        if (mpz_cmp(a, n_min) == 0)
                                break ;
                        mpz_add_ui(j, j, 1);
                }
                if (mpz_cmp(j, s) == 0)
                        return (0);
        }
        return (1);
}

int             ft_ssl_is_primary(mpz_t n, float prob)
{
        if (saved != prob)
       {
                k = (int)(log10(1 - prob) / log10(0.25));
                saved = prob;
        }
        if (check_often(n))
                return (0);
        mpz_set_ui(one, 1);
        mpz_set_ui(s, 0);
        mpz_sub_ui(d, n, 1);
        while (1)
        {
                mpz_and(temp, d, one);
                if (mpz_cmp_ui(temp, 0) != 0)
                        break ;
                mpz_add_ui(s, s, 1);
                mpz_div_ui(d, d, 2);
        }
        return (miller_rabin(s, d, n, k));
}

void    iterate_and_check(mpz_t n, mpz_t max_of_bits, int size, mp_bitcnt_t prev_bits)
{
        float   prob;

	bits = prev_bits;
        mpz_init(j);
        mpz_init(s);
        mpz_init(d);
        mpz_init(temp);
        mpz_init(one);
        mpz_init(n_min);
        mpz_init(a);
        prob = 1 - 0.000001 * size;
        while (mpz_cmp(n, max_of_bits) < 0)
        {
                if (ft_ssl_is_primary(n, prob))
                        break ;
                mpz_add_ui(n, n, 2);
        }
        clear_mpz();
        if (mpz_cmp(n, max_of_bits) >= 0)
        {
                mpz_urandomb(n, state, bits);
                iterate_and_check(n, max_of_bits, size, prev_bits);
        }
}	

void	calculate_variables(mpz_t module, mpz_t pub, mpz_t priv, mpz_t first, mpz_t second)
{
	mpz_set_str(pub, "10001", 16);//set pub exp 65537
	mpz_mul(module, first, second);//calculating module

	mpz_t euler_mul;
	mpz_t euler1;
	mpz_t euler2;
	mpz_init(euler1);
	mpz_init(euler2);
	mpz_init(euler_mul);
	mpz_sub_ui(euler1, first, 1);
	mpz_sub_ui(euler2, second, 1);
	mpz_mul(euler_mul, euler1, euler2);
	mpz_invert(priv, pub, euler_mul);
	gmp_printf("module = %Zx\npublic exp = %Zx\npriv = %Zx\n", module, pub, priv);
}

void	encode(mpz_t mes, mpz_t pub, mpz_t mod)
{
	mpz_powm(mes, mes, pub, mod);
}

void	decode(mpz_t mes, mpz_t priv, mpz_t mod)
{
	mpz_powm(mes, mes, priv, mod);
}

void	sign(mpz_t mes, mpz_t priv, mpz_t mod)
{
	mpz_powm(mes, mes, priv, mod);
}

void	verify(mpz_t mes, mpz_t pub, mpz_t mod, mpz_t copy)
{
	mpz_powm(mes, mes, pub, mod);
	if (mpz_cmp(mes, copy) == 0)
		printf("verification done\n");
	else
		printf("verification failed\n");
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Usage: %s [num_of_bits]\n", argv[0]) && 0);
	int num_bits = atoi(argv[1]);
	printf("num of bits = %d\n", num_bits);
	if (num_bits < 256)
		return (printf("num_bits can be only >255\n") && 0);
	mpz_t first;
	mpz_t second;
	mpz_t third;
	mpz_t fourth;
	mpz_t maximum;// maximum of this bits
	mpz_init(first);
	mpz_init(second);
	mpz_init(third);
	mpz_init(fourth);
	mpz_init(maximum);
	gmp_randinit_mt(state);//initialize random number generator
	gmp_randseed_ui(state, time(NULL));
	mpz_urandomb(first, state, num_bits / 2);
	mpz_urandomb(second, state, num_bits / 2);
	mpz_urandomb(third, state, num_bits / 2);
	mpz_urandomb(fourth, state, num_bits / 2);
	// stavim 1 v 0 i posledniy bit
	mpz_setbit(first, num_bits / 2 - 1);
	mpz_setbit(second, num_bits / 2 - 1);
	mpz_setbit(third, num_bits / 2 - 1);
	mpz_setbit(fourth, num_bits / 2 - 1);
	bits = num_bits / 2;
	mpz_setbit(first, 0);
	mpz_setbit(second, 0);
	mpz_setbit(third, 0);
	mpz_setbit(fourth, 0);
	gmp_printf("randomly generated\n%Zd\n%Zd\n%Zd\n%Zd\nStart searching primes\n", first, second, third, fourth);
	mpz_urandomb(maximum, state, bits);
	for (int i = 0; i < num_bits / 2; i++)
		mpz_setbit(maximum, i);
	iterate_and_check(first, maximum, num_bits / 2, bits);
	iterate_and_check(second, maximum, num_bits / 2, bits);
	iterate_and_check(third, maximum, num_bits / 2, bits);
	iterate_and_check(fourth, maximum, num_bits / 2, bits);
	gmp_printf("primes are\n%Zd\n%Zd\n%Zd\n%Zd\n", first, second, third, fourth);
	mpz_t module1;
	mpz_t pub1;
	mpz_t priv1;	
	mpz_t module2;
	mpz_t pub2;
	mpz_t priv2;
	mpz_init(module1);
	mpz_init(pub1);
	mpz_init(priv1);
	mpz_init(module2);
	mpz_init(pub2);
	mpz_init(priv2);
	calculate_variables(module1, pub1, priv1, first, second);
	calculate_variables(module2, pub2, priv2, third, fourth);
	//Encoding and decoding message
	mpz_t message;
	mpz_t copy;
	mpz_init(message);
	mpz_init(copy);
	mpz_urandomb(message, state, bits);
	mpz_set(copy, message);
	gmp_printf("generated Random message = %Zd\n", message);
	encode(message, pub1, module1);
	gmp_printf("Encoded message = %Zd\n", message);
	decode(message, priv1, module1);
	gmp_printf("Decoded message = %Zd\n", message);
	sign(message, priv1, module1);
	verify(message, pub1, module1, copy);
}
