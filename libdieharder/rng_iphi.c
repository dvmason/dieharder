/*
 *  rng_iphi.c
 * 
 *  This is a version of the inverse Phi as a PRNG in C
 *
 * Dave Mason, TMU Computer Science
 * (E-mail: dmason@torontomu.ca)
 *
 */

#include <dieharder/libdieharder.h>

static unsigned long int iphi_get (void *vstate);
static double iphi_get_double (void *vstate);
static void iphi_set (void *vstate, unsigned long int s);

typedef struct {
 /*
  * Seed variable.
  */
 unsigned int index;
} iphi_state_t;


static unsigned long int iphi_get (void *vstate)
{

 iphi_state_t *state = vstate;
 unsigned int result = state->index*2654435769;
 state->index += 1;
 return result;

}

static double iphi_get_double (void *vstate)
{
  return (double) iphi_get (vstate) / (double) UINT_MAX;
}

static void
iphi_set (void *vstate, unsigned long int s)
{

 /* Initialize automaton using specified seed. */
 iphi_state_t *state = (iphi_state_t *) vstate;
 
 state->index = s;
 return;

}

static const gsl_rng_type iphi_type =
{"iphi",			/* name */
 UINT_MAX,			/* RAND_MAX */
 0,				/* RAND_MIN */
 sizeof (iphi_state_t),
 &iphi_set,
 &iphi_get,
 &iphi_get_double};

const gsl_rng_type *gsl_rng_iphi = &iphi_type;
