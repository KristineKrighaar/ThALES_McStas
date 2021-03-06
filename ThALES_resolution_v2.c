/* Automatically generated file. Do not edit. 
 * Format:     ANSI C source code
 * Creator:    McStas <http://www.mcstas.org>
 * Instrument: ThALES_resolution_v2.instr (ThALES_double_peak10)
 * Date:       Fri Jan  7 15:12:27 2022
 * File:       ./ThALES_resolution_v2.c
 * Compile:    cc -o ThALES_double_peak10.out ./ThALES_resolution_v2.c 
 * CFLAGS=
 */


#define MCCODE_STRING "McStas 2.7.1 - Oct. 04, 2021"
#define FLAVOR "mcstas"
#define FLAVOR_UPPER "MCSTAS"
#define MC_USE_DEFAULT_MAIN
#define MC_TRACE_ENABLED
#define MC_EMBEDDED_RUNTIME

#line 1 "mccode-r.h"
/*******************************************************************************
*
* McCode, neutron/xray ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mccode-r.h
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas 2.7.1
* Version: $Revision$
*
* Runtime system header for McStas/McXtrace.
*
* In order to use this library as an external library, the following variables
* and macros must be declared (see details in the code)
*
*   struct mcinputtable_struct mcinputtable[];
*   int mcnumipar;
*   char mcinstrument_name[], mcinstrument_source[];
*   int mctraceenabled, mcdefaultmain;
*   extern MCNUM  mccomp_storein[];
*   extern MCNUM  mcAbsorbProp[];
*   extern MCNUM  mcScattered;
*   #define MCCODE_STRING "the McStas/McXtrace version"
*
* Usage: Automatically embbeded in the c code.
*
* $Id$
*
*******************************************************************************/

#ifndef MCCODE_R_H
#define MCCODE_R_H "$Revision$"

#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <float.h>
#include <inttypes.h>

/* If the runtime is embedded in the simulation program, some definitions can
   be made static. */

#ifdef MC_EMBEDDED_RUNTIME
#define mcstatic static
#else
#define mcstatic
#endif

#ifdef __dest_os
#if (__dest_os == __mac_os)
#define MAC
#endif
#endif

#ifdef __FreeBSD__
#define NEED_STAT_H
#endif

#if defined(__APPLE__) && defined(__GNUC__)
#define NEED_STAT_H
#endif

#ifdef NEED_STAT_H
#include <sys/stat.h>
#endif

#ifndef MC_PATHSEP_C
#ifdef WIN32
#define MC_PATHSEP_C '\\'
#define MC_PATHSEP_S "\\"
#else  /* !WIN32 */
#define MC_PATHSEP_C '/'
#define MC_PATHSEP_S "/"
#endif /* !WIN32 */
#endif /* MC_PATHSEP_C */

#ifndef WIN32
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#endif

/* the version string is replaced when building distribution with mkdist */
#ifndef MCCODE_STRING
#define MCCODE_STRING "McStas 2.7.1 - Oct. 04, 2021"
#endif

#ifndef MCCODE_DATE
#define MCCODE_DATE "Oct. 04, 2021"
#endif

#ifndef MCCODE_VERSION
#define MCCODE_VERSION "2.7.1"
#endif

#ifndef MCCODE_NAME
#define MCCODE_NAME "McStas"
#endif

#ifndef MCCODE_PARTICLE
#define MCCODE_PARTICLE "neutron"
#endif

#ifndef MCCODE_LIBENV
#define MCCODE_LIBENV "MCSTAS"
#endif

#ifndef FLAVOR_UPPER
#define FLAVOR_UPPER MCCODE_NAME
#endif

#ifdef MC_PORTABLE
#ifndef NOSIGNALS
#define NOSIGNALS 1
#endif
#endif

#ifdef MAC
#ifndef NOSIGNALS
#define NOSIGNALS 1
#endif
#endif

#if (USE_MPI == 0)
#undef USE_MPI
#endif

#ifdef USE_MPI  /* default is to disable signals with MPI, as MPICH uses them to communicate */
#ifndef NOSIGNALS
#define NOSIGNALS 1
#endif
#endif

#if (NOSIGNALS == 0)
#undef NOSIGNALS
#endif

/* Note: the enum instr_formal_types definition MUST be kept
   synchronized with the one in mccode.h and with the
   instr_formal_type_names array in cogen.c. */
enum instr_formal_types
  {
    instr_type_double, instr_type_int, instr_type_string
  };
struct mcinputtable_struct { /* defines instrument parameters */
  char *name; /* name of parameter */
  void *par;  /* pointer to instrument parameter (variable) */
  enum instr_formal_types type;
  char *val;  /* default value */
};

typedef double MCNUM;
typedef struct {MCNUM x, y, z;} Coords;
typedef MCNUM Rotation[3][3];

/* the following variables are defined in the McStas generated C code
   but should be defined externally in case of independent library usage */
#ifndef DANSE
extern struct mcinputtable_struct mcinputtable[]; /* list of instrument parameters */
extern int    mcnumipar;                          /* number of instrument parameters */
extern char   mcinstrument_name[], mcinstrument_source[]; /* instrument name and filename */
extern char  *mcinstrument_exe;                           /* executable path = argv[0] or NULL */
extern MCNUM  mccomp_storein[]; /* 11 coords * number of components in instrument */
extern MCNUM  mcAbsorbProp[];
extern MCNUM  mcScattered;      /* number of SCATTER calls in current component */
extern MCNUM  mcRestore;        /* Flag to indicate if neutron needs to be restored */
#ifndef MC_ANCIENT_COMPATIBILITY
extern int mctraceenabled, mcdefaultmain;
#endif
#endif


/* Useful macros ============================================================ */

/* MPI stuff */

#ifdef USE_MPI
#include "mpi.h"

#ifdef OMPI_MPI_H  /* openmpi does not use signals: we may install our sighandler */
#undef NOSIGNALS
#endif

/*
 * MPI_MASTER(i):
 * execution of i only on master node
 */
#define MPI_MASTER(statement) { \
  if(mpi_node_rank == mpi_node_root)\
  { statement; } \
}

#ifndef MPI_REDUCE_BLOCKSIZE
#define MPI_REDUCE_BLOCKSIZE 1000
#endif

int mc_MPI_Sum(double* buf, long count);
int mc_MPI_Send(void *sbuf, long count, MPI_Datatype dtype, int dest);
int mc_MPI_Recv(void *rbuf, long count, MPI_Datatype dtype, int source);

/* MPI_Finalize exits gracefully and should be preferred to MPI_Abort */
#define exit(code) do {                                   \
    MPI_Finalize();                                       \
    exit(code);                                           \
  } while(0)

#else /* !USE_MPI */
#define MPI_MASTER(instr) instr
#endif /* USE_MPI */

#ifdef USE_MPI
static int mpi_node_count;
#endif

#ifdef USE_THREADS  /* user want threads */
#error Threading (USE_THREADS) support has been removed for very poor efficiency. Use MPI/SSH grid instead.
#endif


void   mcset_ncount(unsigned long long count);    /* wrapper to get mcncount */
unsigned long long int mcget_ncount(void);            /* wrapper to set mcncount */
unsigned long long mcget_run_num(void);           /* wrapper to get mcrun_num=0:mcncount */


/* Following part is only embedded when not redundant with mccode.h ========= */

#ifndef MCCODE_H

#ifndef NOSIGNALS
#include <signal.h>
#define SIG_MESSAGE(msg) strcpy(mcsig_message, msg);
#else
#define SIG_MESSAGE(msg)
#endif /* !NOSIGNALS */

/* Useful macros and constants ============================================== */

#ifndef FLT_MAX
#define FLT_MAX         3.40282347E+38F /* max decimal value of a "float" */
#endif

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef SQR
#define SQR(x) ( (x) * (x) )
#endif
#ifndef SIGN
#define SIGN(x) (((x)>0.0)?(1):(-1))
#endif

#ifndef PI
# ifdef M_PI
#  define PI M_PI
# else
/* When using c99 in the CFLAGS, some of these consts
   are lost... Perhaps we should in fact include everything from
   https://www.gnu.org/software/libc/manual/html_node/Mathematical-Constants.html
*/
#  define PI 3.14159265358979323846
#  define M_PI PI
#  define M_PI_2 M_PI/2.0
#  define M_PI_4 M_PI/4.0
#  define M_1_PI 1.0/M_PI
#  define M_2_PI 2*M_1_PI
#  define M_2_SQRTPI 2/sqrt(M_PI)
#  define M_SQRT2 sqrt(2)
#  define M_SQRT1_2 sqrt(1/2)
# endif
#endif

#define RAD2MIN  ((180*60)/PI)
#define MIN2RAD  (PI/(180*60))
#define DEG2RAD  (PI/180)
#define RAD2DEG  (180/PI)
#define FWHM2RMS 0.424660900144    /* Convert between full-width-half-max and */
#define RMS2FWHM 2.35482004503     /* root-mean-square (standard deviation) */
#define HBAR     1.05457168e-34    /* [Js] h bar Planck constant CODATA 2002 */
#define MNEUTRON 1.67492728e-27    /* [kg] mass of neutron CODATA 2002 */
#define GRAVITY  9.81              /* [m/s^2] gravitational acceleration */
#define NA       6.02214179e23     /* [#atoms/g .mole] Avogadro's number*/


/* wrapper to get absolute and relative position of comp */
/* mccomp_posa and mccomp_posr are defined in McStas generated C code */
#define POS_A_COMP_INDEX(index) \
    (mccomp_posa[index])
#define POS_R_COMP_INDEX(index) \
    (mccomp_posr[index])
/* number of SCATTER calls in current comp: mcScattered defined in generated C code */
#define SCATTERED mcScattered
/* Flag to indicate if neutron needs to be restored: mcRestore defined in generated C code */
#define RESTORE mcRestore


/* Retrieve component information from the kernel */
/* Name, position and orientation (both absolute and relative)  */
/* Any component: For "redundancy", see comment by KN */
#define tmp_name_comp(comp) #comp
#define NAME_COMP(comp) tmp_name_comp(comp)
#define tmp_pos_a_comp(comp) (mcposa ## comp)
#define POS_A_COMP(comp) tmp_pos_a_comp(comp)
#define tmp_pos_r_comp(comp) (mcposr ## comp)
#define POS_R_COMP(comp) tmp_pos_r_comp(comp)
#define tmp_rot_a_comp(comp) (mcrota ## comp)
#define ROT_A_COMP(comp) tmp_rot_a_comp(comp)
#define tmp_rot_r_comp(comp) (mcrotr ## comp)
#define ROT_R_COMP(comp) tmp_rot_r_comp(comp)

/* Current component name, index, position and orientation */
#define NAME_CURRENT_COMP  NAME_COMP(mccompcurname)
#define INDEX_CURRENT_COMP mccompcurindex
#define POS_A_CURRENT_COMP POS_A_COMP(mccompcurname)
#define POS_R_CURRENT_COMP POS_R_COMP(mccompcurname)
#define ROT_A_CURRENT_COMP ROT_A_COMP(mccompcurname)
#define ROT_R_CURRENT_COMP ROT_R_COMP(mccompcurname)

/* Note: The two-stage approach to MC_GETPAR is NOT redundant; without it,
* after #define C sample, MC_GETPAR(C,x) would refer to component C, not to
* component sample. Such are the joys of ANSI C.

* Anyway the usage of MCGETPAR requires that we use sometimes bare names...
*/
#define MC_GETPAR2(comp, par) (mcc ## comp ## _ ## par)
#define MC_GETPAR(comp, par) MC_GETPAR2(comp,par)

/* MCDISPLAY/trace and debugging message sent to stdout */
#ifdef MC_TRACE_ENABLED
#define DEBUG
#endif

#ifdef DEBUG
#define mcDEBUG_INSTR() if(!mcdotrace); else { printf("\nINSTRUMENT:\n"); printf("Instrument '%s' (%s)\n", mcinstrument_name, mcinstrument_source); }
#define mcDEBUG_COMPONENT(name,c,t) if(!mcdotrace); else {\
  printf("COMPONENT: \"%s\"\n" \
         "POS: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         name, c.x, c.y, c.z, t[0][0], t[0][1], t[0][2], \
         t[1][0], t[1][1], t[1][2], t[2][0], t[2][1], t[2][2]); \
  mcAccumulatedILength += coords_len(coords_sub(mcLastComp,c)); \
  printf("Component %30s AT (%g,%g,%g)    %g m from origin\n", name, c.x, c.y, c.z, mcAccumulatedILength); \
  mcLastComp=c;\
  }
#define mcDEBUG_INSTR_END() if(!mcdotrace); else printf("INSTRUMENT END:\n");
#define mcDEBUG_ENTER() if(!mcdotrace); else printf("ENTER:\n");
#define mcDEBUG_COMP(c) if(!mcdotrace); else printf("COMP: \"%s\"\n", c);
#define mcDEBUG_LEAVE() if(!mcdotrace); else printf("LEAVE:\n");
#define mcDEBUG_ABSORB() if(!mcdotrace); else printf("ABSORB:\n");
#else
#define mcDEBUG_INSTR()
#define mcDEBUG_COMPONENT(name,c,t)
#define mcDEBUG_INSTR_END()
#define mcDEBUG_ENTER()
#define mcDEBUG_COMP(c)
#define mcDEBUG_LEAVE()
#define mcDEBUG_ABSORB()
#endif

// mcDEBUG_STATE and mcDEBUG_SCATTER are defined by mcstas-r.h and mcxtrace-r.h



#ifdef TEST
#define test_printf printf
#else
#define test_printf while(0) printf
#endif

/* send MCDISPLAY message to stdout to show gemoetry */
void mcdis_magnify(char *what);
void mcdis_line(double x1, double y1, double z1,
                double x2, double y2, double z2);
void mcdis_dashed_linemcdis_dashed_line(double x1, double y1, double z1,
		       double x2, double y2, double z2, int n);
void mcdis_multiline(int count, ...);
void mcdis_rectangle(char* plane, double x, double y, double z,
		     double width, double height);
void mcdis_box(double x, double y, double z,
	       double width, double height, double length);
void mcdis_circle(char *plane, double x, double y, double z, double r);
void mcdis_Circle(double x, double y, double z, double r, double nx, double ny, double nz);
void mcdis_cylinder( double x, double y, double z,
        double r, double height, int N, double nx, double ny, double nz);
void mcdis_sphere(double x, double y, double z, double r, int N);

/* selection of random number generator. default is MT */
#ifndef MC_RAND_ALG
#define MC_RAND_ALG 1
#endif

#if MC_RAND_ALG == 0
   /* Use system random() (not recommended). */
#  define MC_RAND_MAX RAND_MAX
#elif MC_RAND_ALG == 1
   /* "Mersenne Twister", by Makoto Matsumoto and Takuji Nishimura. */
#  define MC_RAND_MAX ((unsigned long)0xffffffff)
#  define random mt_random
#  define srandom mt_srandom
#elif MC_RAND_ALG == 2
   /* Algorithm used in McStas CVS-080208 and earlier (not recommended). */
#  define MC_RAND_MAX 0x7fffffff
#  define random mc_random
#  define srandom mc_srandom
#else
#  error "Bad value for random number generator choice."
#endif

typedef int mc_int32_t;
mc_int32_t mc_random(void);
void mc_srandom (unsigned int x);
unsigned long mt_random(void);
void mt_srandom (unsigned long x);

double rand01();
double randpm1();
double rand0max(double max);
double randminmax(double min, double max);

double randnorm(void);
double randtriangle(void);

#ifndef DANSE
void mcinit(void);
void mcraytrace(void);
void mcsave(FILE *);
void mcfinally(void);
void mcdisplay(void);
#endif

/* simple vector algebra ==================================================== */
#define vec_prod(x, y, z, x1, y1, z1, x2, y2, z2) \
	vec_prod_func(&x, &y, &z, x1, y1, z1, x2, y2, z2)
mcstatic void vec_prod_func(double *x, double *y, double *z,
		double x1, double y1, double z1, double x2, double y2, double z2);

mcstatic double scalar_prod(
		double x1, double y1, double z1, double x2, double y2, double z2);

#define NORM(x,y,z) \
	norm_func(&x, &y, &z)
mcstatic void norm_func(double *x, double *y, double *z) {
	double temp = (*x * *x) + (*y * *y) + (*z * *z);
	if (temp != 0) {
		temp = sqrt(temp);
		*x /= temp;
		*y /= temp;
		*z /= temp;
	}
}
#define normal_vec(nx, ny, nz, x, y, z) \
    normal_vec_func(&(nx), &(ny), &(nz), x, y, z)
mcstatic void normal_vec_func(double *nx, double *ny, double *nz,
    double x, double y, double z);

/**
 * Rotate the vector vx,vy,vz psi radians around the vector ax,ay,az
 * and put the result in x,y,z.
 */
#define rotate(x, y, z, vx, vy, vz, phi, ax, ay, az) \
  do { \
    double mcrt_tmpx = (ax), mcrt_tmpy = (ay), mcrt_tmpz = (az); \
    double mcrt_vp, mcrt_vpx, mcrt_vpy, mcrt_vpz; \
    double mcrt_vnx, mcrt_vny, mcrt_vnz, mcrt_vn1x, mcrt_vn1y, mcrt_vn1z; \
    double mcrt_bx, mcrt_by, mcrt_bz; \
    double mcrt_cos, mcrt_sin; \
    NORM(mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_vp = scalar_prod((vx), (vy), (vz), mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_vpx = mcrt_vp*mcrt_tmpx; \
    mcrt_vpy = mcrt_vp*mcrt_tmpy; \
    mcrt_vpz = mcrt_vp*mcrt_tmpz; \
    mcrt_vnx = (vx) - mcrt_vpx; \
    mcrt_vny = (vy) - mcrt_vpy; \
    mcrt_vnz = (vz) - mcrt_vpz; \
    vec_prod(mcrt_bx, mcrt_by, mcrt_bz, \
             mcrt_tmpx, mcrt_tmpy, mcrt_tmpz, mcrt_vnx, mcrt_vny, mcrt_vnz); \
    mcrt_cos = cos((phi)); mcrt_sin = sin((phi)); \
    mcrt_vn1x = mcrt_vnx*mcrt_cos + mcrt_bx*mcrt_sin; \
    mcrt_vn1y = mcrt_vny*mcrt_cos + mcrt_by*mcrt_sin; \
    mcrt_vn1z = mcrt_vnz*mcrt_cos + mcrt_bz*mcrt_sin; \
    (x) = mcrt_vpx + mcrt_vn1x; \
    (y) = mcrt_vpy + mcrt_vn1y; \
    (z) = mcrt_vpz + mcrt_vn1z; \
  } while(0)

/**
 * Mirror (xyz) in the plane given by the point (rx,ry,rz) and normal (nx,ny,nz)
 *
 * TODO: This define is seemingly never used...
 */
#define mirror(x,y,z,rx,ry,rz,nx,ny,nz) \
  do { \
    double mcrt_tmpx= (nx), mcrt_tmpy = (ny), mcrt_tmpz = (nz); \
    double mcrt_tmpt; \
    NORM(mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_tmpt=scalar_prod((rx),(ry),(rz),mcrt_tmpx,mcrt_tmpy,mcrt_tmpz); \
    (x) = rx -2 * mcrt_tmpt*mcrt_rmpx; \
    (y) = ry -2 * mcrt_tmpt*mcrt_rmpy; \
    (z) = rz -2 * mcrt_tmpt*mcrt_rmpz; \
  } while (0)

Coords coords_set(MCNUM x, MCNUM y, MCNUM z);
Coords coords_get(Coords a, MCNUM *x, MCNUM *y, MCNUM *z);
Coords coords_add(Coords a, Coords b);
Coords coords_sub(Coords a, Coords b);
Coords coords_neg(Coords a);
Coords coords_scale(Coords b, double scale);
double coords_sp(Coords a, Coords b);
Coords coords_xp(Coords b, Coords c);
double coords_len(Coords a);
void   coords_print(Coords a);
mcstatic void coords_norm(Coords* c);

void rot_set_rotation(Rotation t, double phx, double phy, double phz);
int  rot_test_identity(Rotation t);
void rot_mul(Rotation t1, Rotation t2, Rotation t3);
void rot_copy(Rotation dest, Rotation src);
void rot_transpose(Rotation src, Rotation dst);
Coords rot_apply(Rotation t, Coords a);

void mccoordschange(Coords a, Rotation t, double *x, double *y, double *z,
    double *vx, double *vy, double *vz, double *sx, double *sy, double *sz);
void
mccoordschange_polarisation(Rotation t, double *sx, double *sy, double *sz);

double mcestimate_error(double N, double p1, double p2);
void mcreadparams(void);

/* this is now in mcstas-r.h and mcxtrace-r.h as the number of state parameters is no longer equal*/
/* void mcsetstate(double x, double y, double z, double vx, double vy, double vz,
                double t, double sx, double sy, double sz, double p);
*/
void mcgenstate(void);

/* trajectory/shape intersection routines */
int inside_rectangle(double, double, double, double);
int box_intersect(double *dt_in, double *dt_out, double x, double y, double z,
    double vx, double vy, double vz, double dx, double dy, double dz);
int cylinder_intersect(double *t0, double *t1, double x, double y, double z,
    double vx, double vy, double vz, double r, double h);
int sphere_intersect(double *t0, double *t1, double x, double y, double z,
                 double vx, double vy, double vz, double r);
/* second order equation roots */
int solve_2nd_order(double *t1, double *t2,
    double A,  double B,  double C);

/* random vector generation to shape */
void randvec_target_circle(double *xo, double *yo, double *zo,
    double *solid_angle, double xi, double yi, double zi, double radius);
#define randvec_target_sphere randvec_target_circle
void randvec_target_rect_angular(double *xo, double *yo, double *zo,
    double *solid_angle,
               double xi, double yi, double zi, double height, double width, Rotation A);
#define randvec_target_rect(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)  randvec_target_rect_real(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,0,0,0,1)
void randvec_target_rect_real(double *xo, double *yo, double *zo,
    double *solid_angle,
	       double xi, double yi, double zi, double height, double width, Rotation A,
			 double lx, double ly, double lz, int order);

/* this is the main() */
int mccode_main(int argc, char *argv[]);


#endif /* !MCCODE_H */

#ifndef MCCODE_R_IO_H
#define MCCODE_R_IO_H "$Revision$"

#if (USE_NEXUS == 0)
#undef USE_NEXUS
#endif

#ifndef CHAR_BUF_LENGTH
#define CHAR_BUF_LENGTH 1024
#endif

/* I/O section part ========================================================= */

/* ========================================================================== */

/*                               MCCODE_R_IO_C                                */

/* ========================================================================== */


/* main DETECTOR structure which stores most information to write to data files */
struct mcdetector_struct {
  char   filename[CHAR_BUF_LENGTH];   /* file name of monitor */
  char   position[CHAR_BUF_LENGTH];   /* position of detector component */
  char   component[CHAR_BUF_LENGTH];  /* component instance name */
  char   instrument[CHAR_BUF_LENGTH]; /* instrument name */
  char   type[CHAR_BUF_LENGTH];       /* data type, e.g. 0d, 1d, 2d, 3d */
  char   user[CHAR_BUF_LENGTH];       /* user name, e.g. HOME */
  char   date[CHAR_BUF_LENGTH];       /* date of simulation end/write time */
  char   title[CHAR_BUF_LENGTH];      /* title of detector */
  char   xlabel[CHAR_BUF_LENGTH];     /* X axis label */
  char   ylabel[CHAR_BUF_LENGTH];     /* Y axis label */
  char   zlabel[CHAR_BUF_LENGTH];     /* Z axis label */
  char   xvar[CHAR_BUF_LENGTH];       /* X variable name */
  char   yvar[CHAR_BUF_LENGTH];       /* Y variable name */
  char   zvar[CHAR_BUF_LENGTH];       /* Z variable name */
  char   ncount[CHAR_BUF_LENGTH];     /* number of events initially generated */
  char   limits[CHAR_BUF_LENGTH];     /* X Y Z limits, e.g. [xmin xmax ymin ymax zmin zmax] */
  char   variables[CHAR_BUF_LENGTH];  /* variables written into data block */
  char   statistics[CHAR_BUF_LENGTH]; /* center, mean and half width along axis */
  char   signal[CHAR_BUF_LENGTH];     /* min max and mean of signal (data block) */
  char   values[CHAR_BUF_LENGTH];     /* integrated values e.g. [I I_err N] */
  double xmin,xmax;                   /* min max of axes */
  double ymin,ymax;
  double zmin,zmax;
  double intensity;                   /* integrated values for data block */
  double error;
  double events;
  double min;                         /* statistics for data block */
  double max;
  double mean;
  double centerX;                     /* statistics for axes */
  double halfwidthX;
  double centerY;
  double halfwidthY;
  int    rank;                        /* dimensionaly of monitor, e.g. 0 1 2 3 */
  char   istransposed;                /* flag to transpose matrix for some formats */

  long   m,n,p;                       /* dimensions of data block and along axes */
  long   date_l;                      /* same as date, but in sec since 1970 */

  double *p0, *p1, *p2;               /* pointers to saved data, NULL when freed */
  char   format[CHAR_BUF_LENGTH];    /* format for file generation */
};

typedef struct mcdetector_struct MCDETECTOR;

static   char *mcdirname             = NULL;      /* name of output directory */
static   char *mcsiminfo_name        = "mccode";  /* default output sim file name */
char    *mcformat                    = NULL;      /* NULL (default) or a specific format */

/* file I/O definitions and function prototypes */

#ifndef MC_EMBEDDED_RUNTIME /* the mcstatic variables (from mccode-r.c) */
extern FILE * mcsiminfo_file;     /* handle to the output siminfo file */
extern int    mcgravitation;      /* flag to enable gravitation */
extern int    mcdotrace;          /* flag to print MCDISPLAY messages */
#else
mcstatic FILE *mcsiminfo_file        = NULL;
#endif

/* I/O function prototypes ================================================== */

/* output functions */
MCDETECTOR mcdetector_out_0D(char *t, double p0, double p1, double p2, char *c, Coords pos);
MCDETECTOR mcdetector_out_1D(char *t, char *xl, char *yl,
                  char *xvar, double x1, double x2, long n,
                  double *p0, double *p1, double *p2, char *f, char *c, Coords pos);
MCDETECTOR mcdetector_out_2D(char *t, char *xl, char *yl,
                  double x1, double x2, double y1, double y2, long m,
                  long n, double *p0, double *p1, double *p2, char *f,
                  char *c, Coords pos);
MCDETECTOR mcdetector_out_list(char *t, char *xl, char *yl,
                  long m, long n,
                  double *p1, char *f,
                  char *c, Coords posa);

/* wrappers to output functions, that automatically set NAME and POSITION */
#define DETECTOR_OUT(p0,p1,p2) mcdetector_out_0D(NAME_CURRENT_COMP,p0,p1,p2,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_0D(t,p0,p1,p2) mcdetector_out_0D(t,p0,p1,p2,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_1D(t,xl,yl,xvar,x1,x2,n,p0,p1,p2,f) \
     mcdetector_out_1D(t,xl,yl,xvar,x1,x2,n,p0,p1,p2,f,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_2D(t,xl,yl,x1,x2,y1,y2,m,n,p0,p1,p2,f) \
     mcdetector_out_2D(t,xl,yl,x1,x2,y1,y2,m,n,p0,p1,p2,f,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)

#ifdef USE_NEXUS
#include "napi.h"
NXhandle nxhandle;
#endif

#endif /* ndef MCCODE_R_IO_H */

#endif /* MCCODE_R_H */
/* End of file "mccode-r.h". */

#line 712 "./ThALES_resolution_v2.c"

#line 1 "mcstas-r.h"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mcstas-r.h
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas X.Y
* Version: $Revision$
*
* Runtime system header for McStas.
*
* In order to use this library as an external library, the following variables
* and macros must be declared (see details in the code)
*
*   struct mcinputtable_struct mcinputtable[];
*   int mcnumipar;
*   char mcinstrument_name[], mcinstrument_source[];
*   int mctraceenabled, mcdefaultmain;
*   extern MCNUM  mccomp_storein[];
*   extern MCNUM  mcAbsorbProp[];
*   extern MCNUM  mcScattered;
*   #define MCCODE_STRING "the McStas version"
*
* Usage: Automatically embbeded in the c code.
*
* $Id$
*
*******************************************************************************/

#ifndef MCSTAS_R_H
#define MCSTAS_R_H "$Revision$"

/* Following part is only embedded when not redundant with mcstas.h ========= */

#ifndef MCCODE_H

#define AA2MS    629.622368        /* Convert k[1/AA] to v[m/s] */
#define MS2AA    1.58825361e-3     /* Convert v[m/s] to k[1/AA] */
#define K2V      AA2MS
#define V2K      MS2AA
#define Q2V      AA2MS
#define V2Q      MS2AA
#define SE2V     437.393377        /* Convert sqrt(E)[meV] to v[m/s] */
#define VS2E     5.22703725e-6     /* Convert (v[m/s])**2 to E[meV] */

#define SCATTER do {mcDEBUG_SCATTER(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz, \
        mcnlt,mcnlsx,mcnlsy,mcnlsz, mcnlp); mcScattered++;} while(0)
#define ABSORB do {mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz, \
        mcnlt,mcnlsx,mcnlsy,mcnlsz, mcnlp); mcDEBUG_ABSORB(); MAGNET_OFF; goto mcabsorb;} while(0)

#define STORE_NEUTRON(index, x, y, z, vx, vy, vz, t, sx, sy, sz, p) \
  mcstore_neutron(mccomp_storein,index, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
#define RESTORE_NEUTRON(index, x, y, z, vx, vy, vz, t, sx, sy, sz, p) \
  mcrestore_neutron(mccomp_storein,index, &x, &y, &z, &vx, &vy, &vz, &t, &sx, &sy, &sz, &p);

#define MAGNET_ON \
  do { \
    mcMagnet = 1; \
  } while(0)

#define MAGNET_OFF \
  do { \
    mcMagnet = 0; \
  } while(0)

#define ALLOW_BACKPROP \
  do { \
    mcallowbackprop = 1; \
  } while(0)

#define DISALLOW_BACKPROP \
  do { \
    mcallowbackprop = 0; \
  } while(0)

#define PROP_MAGNET(dt) \
  do { \
  }while (0)
    /* change coordinates from local system to magnet system */
/*    Rotation rotLM, rotTemp; \
      Coords   posLM = coords_sub(POS_A_CURRENT_COMP, mcMagnetPos); \
      rot_transpose(ROT_A_CURRENT_COMP, rotTemp); \
      rot_mul(rotTemp, mcMagnetRot, rotLM); \
      mcMagnetPrecession(mcnlx, mcnly, mcnlz, mcnlt, mcnlvx, mcnlvy, mcnlvz, \
               &mcnlsx, &mcnlsy, &mcnlsz, dt, posLM, rotLM); \
      } while(0)
*/

#define mcPROP_DT(dt) \
  do { \
    if (mcMagnet && dt > 0) PROP_MAGNET(dt);\
    mcnlx += mcnlvx*(dt); \
    mcnly += mcnlvy*(dt); \
    mcnlz += mcnlvz*(dt); \
    mcnlt += (dt); \
    if (isnan(p) || isinf(p)) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }\
  } while(0)

/* ADD: E. Farhi, Aug 6th, 2001 PROP_GRAV_DT propagation with acceleration */
#define PROP_GRAV_DT(dt, Ax, Ay, Az) \
  do { \
    if(dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }\
    if (mcMagnet) printf("Spin precession gravity\n"); \
    mcnlx  += mcnlvx*(dt) + (Ax)*(dt)*(dt)/2; \
    mcnly  += mcnlvy*(dt) + (Ay)*(dt)*(dt)/2; \
    mcnlz  += mcnlvz*(dt) + (Az)*(dt)*(dt)/2; \
    mcnlvx += (Ax)*(dt); \
    mcnlvy += (Ay)*(dt); \
    mcnlvz += (Az)*(dt); \
    mcnlt  += (dt); \
    DISALLOW_BACKPROP;\
  } while(0)


#define PROP_DT(dt) \
  do { \
    if(dt < 0) { RESTORE=1; goto mcabsorbComp; }; \
    if (mcgravitation) { Coords mcLocG; double mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    PROP_GRAV_DT(dt, mc_gx, mc_gy, mc_gz); } \
    else mcPROP_DT(dt); \
    DISALLOW_BACKPROP;\
  } while(0)


#define PROP_Z0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, NULL, -mc_gz/2, -mcnlvz, -mcnlz); \
    if (mc_ret) {PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); mcnlz=0;}\
    else if (mcallowbackprop == 0 && mc_dt < 0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; } \
    else mcPROP_Z0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define mcPROP_Z0 \
  do { \
    double mc_dt; \
    if(mcnlvz == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnlz/mcnlvz; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnlz = 0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define PROP_X0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, NULL, -mc_gx/2, -mcnlvx, -mcnlx); \
    if (mc_ret) {PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); mcnlx=0;}\
    else if (mcallowbackprop == 0 && mc_dt < 0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; } \
    else mcPROP_X0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define mcPROP_X0 \
  do { \
    double mc_dt; \
    if(mcnlvx == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnlx/mcnlvx; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnlx = 0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define PROP_Y0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, NULL, -mc_gy/2, -mcnlvy, -mcnly); \
    if (mc_ret) {PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); mcnly=0;}\
    else if (mcallowbackprop == 0 && mc_dt < 0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; } \
    else mcPROP_Y0; \
    DISALLOW_BACKPROP;\
  } while(0)


#define mcPROP_Y0 \
  do { \
    double mc_dt; \
    if(mcnlvy == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnly/mcnlvy; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnly = 0; \
    DISALLOW_BACKPROP; \
  } while(0)

/*moved from mccode-r.h*/
void mcsetstate(double x, double y, double z, double vx, double vy, double vz,
                double t, double sx, double sy, double sz, double p);

#ifdef DEBUG

#define mcDEBUG_STATE(x,y,z,vx,vy,vz,t,sx,sy,sz,p) if(!mcdotrace); else \
  printf("STATE: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         x,y,z,vx,vy,vz,t,sx,sy,sz,p);
#define mcDEBUG_SCATTER(x,y,z,vx,vy,vz,t,sx,sy,sz,p) if(!mcdotrace); else \
  printf("SCATTER: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         x,y,z,vx,vy,vz,t,sx,sy,sz,p);

#else

#define mcDEBUG_STATE(x,y,z,vx,vy,vz,t,sx,sy,sz,p)
#define mcDEBUG_SCATTER(x,y,z,vx,vy,vz,t,sx,sy,sz,p)

#endif

#endif /* !MCCODE_H */

#endif /* MCSTAS_R_H */
/* End of file "mcstas-r.h". */

#line 945 "./ThALES_resolution_v2.c"

#line 1 "mccode-r.c"
/*******************************************************************************
*
* McCode, neutron/xray ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mccode-r.c
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas X.Y/McXtrace X.Y
* Version: $Revision$
*
* Runtime system for McStas and McXtrace.
* Embedded within instrument in runtime mode.
* Contains SECTIONS:
*   MPI handling (sum, send, recv)
*   format definitions
*   I/O
*   mcdisplay support
*   random numbers
*   coordinates handling
*   vectors math (solve 2nd order, normals, randvec...)
*   parameter handling
*   signal and main handlers
*
* Usage: Automatically embbeded in the c code whenever required.
*
* $Id$
*
*******************************************************************************/

/*******************************************************************************
* The I/O format definitions and functions
*******************************************************************************/


/** Include header files to avoid implicit declarations (not allowed on LLVM) */
#include <ctype.h>
#include <sys/types.h>

// UNIX specific headers (non-Windows)
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#endif

#include <sys/stat.h>

#ifdef _WIN32 
#include <direct.h>
# define  mkdir( D, M )   _mkdir( D ) 
#endif 

#ifndef DANSE
#ifdef MC_ANCIENT_COMPATIBILITY
int mctraceenabled = 0;
int mcdefaultmain  = 0;
#endif
/* else defined directly in the McCode generated C code */

static   long mcseed                 = 0; /* seed for random generator */
static   long mcstartdate            = 0; /* start simulation time */
static   int  mcdisable_output_files = 0; /* --no-output-files */
mcstatic int  mcgravitation          = 0; /* use gravitation flag, for PROP macros */
int      mcMagnet                    = 0; /* magnet stack flag */
mcstatic int  mcdotrace              = 0; /* flag for --trace and messages for DISPLAY */
int      mcallowbackprop             = 0;         /* flag to enable negative/backprop */

/* Number of particle histories to simulate. */
#ifdef NEUTRONICS
mcstatic unsigned long long int mcncount             = 1;
mcstatic unsigned long long int mcrun_num            = 0;
#else
mcstatic unsigned long long int mcncount             = 1000000;
mcstatic unsigned long long int mcrun_num            = 0;
#endif /* NEUTRONICS */

#else
#include "mcstas-globals.h"
#endif /* !DANSE */

/* SECTION: MPI handling ==================================================== */

#ifdef USE_MPI
/* MPI rank */
static int mpi_node_rank;
static int mpi_node_root = 0;


/*******************************************************************************
* mc_MPI_Reduce: Gathers arrays from MPI nodes using Reduce function.
*******************************************************************************/
int mc_MPI_Sum(double *sbuf, long count)
{
  if (!sbuf || count <= 0) return(MPI_SUCCESS); /* nothing to reduce */
  else {
    /* we must cut the buffer into blocks not exceeding the MPI max buffer size of 32000 */
    long   offset=0;
    double *rbuf=NULL;
    int    length=MPI_REDUCE_BLOCKSIZE; /* defined in mccode-r.h */
    int    i=0;
    rbuf = calloc(count, sizeof(double));
    if (!rbuf)
      exit(-fprintf(stderr, "Error: Out of memory %li (mc_MPI_Sum)\n", count*sizeof(double)));
    while (offset < count) {
      if (!length || offset+length > count-1) length=count-offset;
      else length=MPI_REDUCE_BLOCKSIZE;
      if (MPI_Reduce((double*)(sbuf+offset), (double*)(rbuf+offset),
              length, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD) != MPI_SUCCESS)
        return MPI_ERR_COUNT;
      offset += length;
    }

    for (i=0; i<count; i++) sbuf[i] = rbuf[i];
    free(rbuf);
  }
  return MPI_SUCCESS;
} /* mc_MPI_Sum */

/*******************************************************************************
* mc_MPI_Send: Send array to MPI node by blocks to avoid buffer limit
*******************************************************************************/
int mc_MPI_Send(void *sbuf,
                  long count, MPI_Datatype dtype,
                  int dest)
{
  int dsize;
  long offset=0;
  int  tag=1;
  int  length=MPI_REDUCE_BLOCKSIZE; /* defined in mccode-r.h */

  if (!sbuf || count <= 0) return(MPI_SUCCESS); /* nothing to send */
  MPI_Type_size(dtype, &dsize);

  while (offset < count) {
    if (offset+length > count-1) length=count-offset;
    else length=MPI_REDUCE_BLOCKSIZE;
    if (MPI_Send((void*)(sbuf+offset*dsize), length, dtype, dest, tag++, MPI_COMM_WORLD) != MPI_SUCCESS)
      return MPI_ERR_COUNT;
    offset += length;
  }

  return MPI_SUCCESS;
} /* mc_MPI_Send */

/*******************************************************************************
* mc_MPI_Recv: Receives arrays from MPI nodes by blocks to avoid buffer limit
*             the buffer must have been allocated previously.
*******************************************************************************/
int mc_MPI_Recv(void *sbuf,
                  long count, MPI_Datatype dtype,
                  int source)
{
  int dsize;
  long offset=0;
  int  tag=1;
  int  length=MPI_REDUCE_BLOCKSIZE; /* defined in mccode-r.h */

  if (!sbuf || count <= 0) return(MPI_SUCCESS); /* nothing to recv */
  MPI_Type_size(dtype, &dsize);

  while (offset < count) {
    if (offset+length > count-1) length=count-offset;
    else length=MPI_REDUCE_BLOCKSIZE;
    if (MPI_Recv((void*)(sbuf+offset*dsize), length, dtype, source, tag++,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS)
      return MPI_ERR_COUNT;
    offset += length;
  }

  return MPI_SUCCESS;
} /* mc_MPI_Recv */

#endif /* USE_MPI */

/* SECTION: parameters handling ============================================= */

/* Instrument input parameter type handling. */
/*******************************************************************************
* mcparm_double: extract double value from 's' into 'vptr'
*******************************************************************************/
static int
mcparm_double(char *s, void *vptr)
{
  char *p;
  double *v = (double *)vptr;

  if (!s) { *v = 0; return(1); }
  *v = strtod(s, &p);
  if(*s == '\0' || (p != NULL && *p != '\0') || errno == ERANGE)
    return 0;                        /* Failed */
  else
    return 1;                        /* Success */
}

/*******************************************************************************
* mcparminfo_double: display parameter type double
*******************************************************************************/
static char *
mcparminfo_double(char *parmname)
{
  return "double";
}

/*******************************************************************************
* mcparmerror_double: display error message when failed extract double
*******************************************************************************/
static void
mcparmerror_double(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for floating point parameter %s (mcparmerror_double)\n",
          val, parm);
}

/*******************************************************************************
* mcparmprinter_double: convert double to string
*******************************************************************************/
static void
mcparmprinter_double(char *f, void *vptr)
{
  double *v = (double *)vptr;
  sprintf(f, "%g", *v);
}

/*******************************************************************************
* mcparm_int: extract int value from 's' into 'vptr'
*******************************************************************************/
static int
mcparm_int(char *s, void *vptr)
{
  char *p;
  int *v = (int *)vptr;
  long x;

  if (!s) { *v = 0; return(1); }
  *v = 0;
  x = strtol(s, &p, 10);
  if(x < INT_MIN || x > INT_MAX)
    return 0;                        /* Under/overflow */
  *v = x;
  if(*s == '\0' || (p != NULL && *p != '\0') || errno == ERANGE)
    return 0;                        /* Failed */
  else
    return 1;                        /* Success */
}

/*******************************************************************************
* mcparminfo_int: display parameter type int
*******************************************************************************/
static char *
mcparminfo_int(char *parmname)
{
  return "int";
}

/*******************************************************************************
* mcparmerror_int: display error message when failed extract int
*******************************************************************************/
static void
mcparmerror_int(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for integer parameter %s (mcparmerror_int)\n",
          val, parm);
}

/*******************************************************************************
* mcparmprinter_int: convert int to string
*******************************************************************************/
static void
mcparmprinter_int(char *f, void *vptr)
{
  int *v = (int *)vptr;
  sprintf(f, "%d", *v);
}

/*******************************************************************************
* mcparm_string: extract char* value from 's' into 'vptr' (copy)
*******************************************************************************/
static int
mcparm_string(char *s, void *vptr)
{
  char **v = (char **)vptr;
  if (!s) { *v = NULL; return(1); }
  *v = (char *)malloc(strlen(s) + 1);
  if(*v == NULL)
  {
    exit(-fprintf(stderr, "Error: Out of memory %li (mcparm_string).\n", (long)strlen(s) + 1));
  }
  strcpy(*v, s);
  return 1;                        /* Success */
}

/*******************************************************************************
* mcparminfo_string: display parameter type string
*******************************************************************************/
static char *
mcparminfo_string(char *parmname)
{
  return "string";
}

/*******************************************************************************
* mcparmerror_string: display error message when failed extract string
*******************************************************************************/
static void
mcparmerror_string(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for string parameter %s (mcparmerror_string)\n",
          val, parm);
}

/*******************************************************************************
* mcparmprinter_string: convert string to string (including esc chars)
*******************************************************************************/
static void
mcparmprinter_string(char *f, void *vptr)
{
  char **v = (char **)vptr;
  char *p;

  if (!*v) { *f='\0'; return; }
  strcpy(f, "");
  for(p = *v; *p != '\0'; p++)
  {
    switch(*p)
    {
      case '\n':
        strcat(f, "\\n");
        break;
      case '\r':
        strcat(f, "\\r");
        break;
      case '"':
        strcat(f, "\\\"");
        break;
      case '\\':
        strcat(f, "\\\\");
        break;
      default:
        strncat(f, p, 1);
    }
  }
  /* strcat(f, "\""); */
} /* mcparmprinter_string */

/* now we may define the parameter structure, using previous functions */
static struct
  {
    int (*getparm)(char *, void *);
    char * (*parminfo)(char *);
    void (*error)(char *, char *);
    void (*printer)(char *, void *);
} mcinputtypes[] = {
  {
    mcparm_double, mcparminfo_double, mcparmerror_double,
    mcparmprinter_double
  }, {
    mcparm_int, mcparminfo_int, mcparmerror_int,
    mcparmprinter_int
  }, {
    mcparm_string, mcparminfo_string, mcparmerror_string,
    mcparmprinter_string
  }
};

/*******************************************************************************
* mcestimate_error: compute sigma from N,p,p2 in Gaussian large numbers approx
*******************************************************************************/
double mcestimate_error(double N, double p1, double p2)
{
  double pmean, n1;
  if(N <= 1)
    return p1;
  pmean = p1 / N;
  n1 = N - 1;
  /* Note: underflow may cause p2 to become zero; the fabs() below guards
     against this. */
  return sqrt((N/n1)*fabs(p2 - pmean*pmean));
}

double (*mcestimate_error_p)
  (double V2, double psum, double p2sum)=mcestimate_error;

/* ========================================================================== */

/*                               MCCODE_R_IO_C                                */

/* ========================================================================== */

#ifndef MCCODE_R_IO_C
#define MCCODE_R_IO_C "$Revision$"

/* SECTION: file i/o handling ================================================ */

#ifndef HAVE_STRCASESTR
// from msysgit: https://code.google.com/p/msysgit/source/browse/compat/strcasestr.c
char *strcasestr(const char *haystack, const char *needle)
{
  int nlen = strlen(needle);
  int hlen = strlen(haystack) - nlen + 1;
  int i;

  for (i = 0; i < hlen; i++) {
    int j;
    for (j = 0; j < nlen; j++) {
            unsigned char c1 = haystack[i+j];
            unsigned char c2 = needle[j];
            if (toupper(c1) != toupper(c2))
                    goto next;
    }
    return (char *) haystack + i;
  next:
    ;
  }
  return NULL;
}


#endif
#ifndef HAVE_STRCASECMP
int strcasecmp( const char *s1, const char *s2 )
{
  int c1, c2;
  do {
    c1 = tolower( (unsigned char) *s1++ );
    c2 = tolower( (unsigned char) *s2++ );
  } while (c1 == c2 && c1 != 0);
  return c2 > c1 ? -1 : c1 > c2;
}
#endif

/*******************************************************************************
* mcfull_file: allocates a full file name=mcdirname+file. Catenate extension if missing.
*******************************************************************************/
char *mcfull_file(char *name, char *ext)
{
  int   dirlen=0;
  char *mem   =NULL;

  dirlen = mcdirname ? strlen(mcdirname) : 0;
  mem = (char*)malloc(dirlen + strlen(name) + CHAR_BUF_LENGTH);
  if(!mem) {
    exit(-fprintf(stderr, "Error: Out of memory %li (mcfull_file)\n", (long)(dirlen + strlen(name) + 256)));
  }
  strcpy(mem, "");

  /* prepend directory name to path if name does not contain a path */
  if (dirlen > 0 && !strchr(name, MC_PATHSEP_C)) {
    strcat(mem, mcdirname);
    strcat(mem, MC_PATHSEP_S);
  } /* dirlen */

  strcat(mem, name);
  if (!strchr(name, '.') && ext && strlen(ext))
  { /* add extension if not in file name already */
    strcat(mem, ".");
    strcat(mem, ext);
  }
  return(mem);
} /* mcfull_file */

/*******************************************************************************
* mcnew_file: opens a new file within mcdirname if non NULL
*             the file is opened in "a" (append, create if does not exist)
*             the extension 'ext' is added if the file name does not include one.
*             the last argument is set to 0 if file did not exist, else to 1.
*******************************************************************************/
FILE *mcnew_file(char *name, char *ext, int *exists)
{
  char *mem;
  FILE *file=NULL;

  if (!name || strlen(name) == 0 || mcdisable_output_files) return(NULL);
  
  mem  = mcfull_file(name, ext); /* create mcdirname/name.ext */
  
  /* check for existence */
  file = fopen(mem, "r"); /* for reading -> fails if does not exist */
  if (file) {
    fclose(file);
    *exists=1;
  } else
    *exists=0;
  
  /* open the file for writing/appending */
#ifdef USE_NEXUS
  if (mcformat && strcasestr(mcformat, "NeXus")) {
    /* NXhandle nxhandle is defined in the .h with USE_NEXUS */
    NXaccess mode = (*exists ? NXACC_CREATE5 | NXACC_RDWR : NXACC_CREATE5);
      
    if (NXopen(mem, mode, &nxhandle) != NX_OK)
      file = NULL;
    else
      file = (FILE*)&nxhandle; /* to make it non NULL */
  } else
#endif
    file = fopen(mem, "a+"); 
    
  if(!file)
    fprintf(stderr, "Warning: could not open output file '%s' for %s (mcnew_file)\n", 
      mem, *exists ? "append" : "create");
  free(mem);

  return file;
} /* mcnew_file */

/*******************************************************************************
* mcdetector_statistics: compute detector statistics, error bars, [x I I_err N] 1D
* RETURN:            updated detector structure
* Used by: mcdetector_import
*******************************************************************************/
MCDETECTOR mcdetector_statistics(
  MCDETECTOR detector)
{

  if (!detector.p1 || !detector.m)
    return(detector);
  
  /* compute statistics and update MCDETECTOR structure ===================== */
  double sum_z  = 0, min_z  = 0, max_z  = 0;
  double fmon_x =0,  smon_x = 0, fmon_y =0, smon_y=0, mean_z=0;
  double Nsum=0, P2sum=0;

  double sum_xz = 0, sum_yz = 0, sum_x = 0, sum_y = 0, sum_x2z = 0, sum_y2z = 0;
  int    i,j;
  char   hasnan=0, hasinf=0;
  char   israw = ((char*)strcasestr(detector.format,"raw") != NULL);
  double *this_p1=NULL; /* new 1D McCode array [x I E N]. Freed after writing data */

  /* if McCode/PGPLOT and rank==1 we create a new m*4 data block=[x I E N] */
  if (detector.rank == 1 && strcasestr(detector.format,"McCode")) {
    this_p1 = (double *)calloc(detector.m*detector.n*detector.p*4, sizeof(double));
    if (!this_p1)
      exit(-fprintf(stderr, "Error: Out of memory creating %li 1D " MCCODE_STRING " data set for file '%s' (mcdetector_import)\n",
        detector.m*detector.n*detector.p*4*sizeof(double*), detector.filename));
  }

  max_z = min_z = detector.p1[0];
  
  /* compute sum and moments (not for lists) */
  if (!strcasestr(detector.format,"list") && detector.m)
  for(j = 0; j < detector.n*detector.p; j++)
  {
    for(i = 0; i < detector.m; i++)
    {
      double x,y,z;
      double N, E;
      long   index= !detector.istransposed ? i*detector.n*detector.p + j : i+j*detector.m;
      char   hasnaninf=0;

      if (detector.m) 
        x = detector.xmin + (i + 0.5)/detector.m*(detector.xmax - detector.xmin); 
      else x = 0;
      if (detector.n && detector.p) 
        y = detector.ymin + (j + 0.5)/detector.n/detector.p*(detector.ymax - detector.ymin); 
      else y = 0;
      z = detector.p1[index];
      N = detector.p0 ? detector.p0[index] : 1;
      E = detector.p2 ? detector.p2[index] : 0;
      if (detector.p2 && !israw) 
        detector.p2[index] = (*mcestimate_error_p)(detector.p0[index],detector.p1[index],detector.p2[index]); /* set sigma */
      
      if (detector.rank == 1 && this_p1 && strcasestr(detector.format,"McCode")) {
        /* fill-in 1D McCode array [x I E N] */
        this_p1[index*4]   = x;
        this_p1[index*4+1] = z;
        this_p1[index*4+2] = detector.p2 ? detector.p2[index] : 0;
        this_p1[index*4+3] = N;
      }
      
      if (isnan(z) || isnan(E) || isnan(N)) hasnaninf=hasnan=1;
      if (isinf(z) || isinf(E) || isinf(N)) hasnaninf=hasinf=1;

      /* compute stats integrals */
      if (!hasnaninf) {
        sum_xz += x*z;
        sum_yz += y*z;
        sum_x  += x;
        sum_y  += y;
        sum_z  += z;
        sum_x2z += x*x*z;
        sum_y2z += y*y*z;
        if (z > max_z) max_z = z;
        if (z < min_z) min_z = z;

        Nsum += N;
        P2sum += E;
      }

    }
  } /* for j */

  /* compute 1st and 2nd moments. For lists, sum_z=0 so this is skipped. */
  if (sum_z && detector.n*detector.m*detector.p)
  {
    fmon_x = sum_xz/sum_z;
    fmon_y = sum_yz/sum_z;
    smon_x = sum_x2z/sum_z-fmon_x*fmon_x; smon_x = smon_x > 0 ? sqrt(smon_x) : 0;
    smon_y = sum_y2z/sum_z-fmon_y*fmon_y; smon_y = smon_y > 0 ? sqrt(smon_y) : 0;
    mean_z = sum_z/detector.n/detector.m/detector.p;
  }
  /* store statistics into detector */
  detector.intensity = sum_z;
  detector.error     = Nsum ? (*mcestimate_error_p)(Nsum, sum_z, P2sum) : 0;
  detector.events    = Nsum;
  detector.min       = min_z;
  detector.max       = max_z;
  detector.mean      = mean_z;
  detector.centerX   = fmon_x;
  detector.halfwidthX= smon_x;
  detector.centerY   = fmon_y;
  detector.halfwidthY= smon_y;

  /* if McCode/PGPLOT and rank==1 replace p1 with new m*4 1D McCode and clear others */
  if (detector.rank == 1 && this_p1 && strcasestr(detector.format,"McCode")) {
    
    detector.p1 = this_p1;
    detector.n  = detector.m; detector.m  = 4;
    detector.p0 = detector.p2 = NULL;
    detector.istransposed = 1;
  }

  if (detector.n*detector.m*detector.p > 1)
    snprintf(detector.signal, CHAR_BUF_LENGTH, 
      "Min=%g; Max=%g; Mean=%g;", detector.min, detector.max, detector.mean);
  else
    strcpy(detector.signal, "None");
  snprintf(detector.values, CHAR_BUF_LENGTH,
    "%g %g %g", detector.intensity, detector.error, detector.events);

  switch (detector.rank) {
    case 1:  snprintf(detector.statistics, CHAR_BUF_LENGTH, "X0=%g; dX=%g;",
      detector.centerX, detector.halfwidthX); break;
    case 2:
    case 3:  snprintf(detector.statistics, CHAR_BUF_LENGTH, "X0=%g; dX=%g; Y0=%g; dY=%g;",
      detector.centerX, detector.halfwidthX, detector.centerY, detector.halfwidthY);
      break;
    default: strcpy(detector.statistics, "None");
  }
  
  if (hasnan)
    printf("WARNING: Nan detected in component/file %s %s\n", 
      detector.component, strlen(detector.filename) ? detector.filename : "");
  if (hasinf)
    printf("WARNING: Inf detected in component/file %s %s\n", 
      detector.component, strlen(detector.filename) ? detector.filename : "");
  
  return(detector);
  
} /* mcdetector_statistics */

/*******************************************************************************
* mcdetector_import: build detector structure, merge non-lists from MPI
*                    compute basic stat, write "Detector:" line
* RETURN:            detector structure. Invalid data if detector.p1 == NULL
*                    Invalid detector sets m=0 and filename=""
*                    Simulation data  sets m=0 and filename=mcsiminfo_name
* This function is equivalent to the old 'mcdetector_out', returning a structure
*******************************************************************************/
MCDETECTOR mcdetector_import(
  char *format,
  char *component, char *title,
  long m, long n,  long p,
  char *xlabel, char *ylabel, char *zlabel,
  char *xvar, char *yvar, char *zvar,
  double x1, double x2, double y1, double y2, double z1, double z2,
  char *filename,
  double *p0, double *p1, double *p2,
  Coords position)
{
  time_t t;       /* for detector.date */
  long   date_l;  /* date as a long number */
  char   istransposed=0;
  char   c[CHAR_BUF_LENGTH]; /* temp var for signal label */

  MCDETECTOR detector;

  /* build MCDETECTOR structure ============================================= */
  /* make sure we do not have NULL for char fields */

  /* these also apply to simfile */
  strncpy (detector.filename,  filename ? filename : "",        CHAR_BUF_LENGTH);
  strncpy (detector.format,    format   ? format   : "McCode" , CHAR_BUF_LENGTH);
  /* add extension if missing */
  if (strlen(detector.filename) && !strchr(detector.filename, '.'))
  { /* add extension if not in file name already */
    strcat(detector.filename, ".dat");
  }
  strncpy (detector.component, component ? component : MCCODE_STRING " component", CHAR_BUF_LENGTH);

  snprintf(detector.instrument, CHAR_BUF_LENGTH, "%s (%s)", mcinstrument_name, mcinstrument_source);
  snprintf(detector.user, CHAR_BUF_LENGTH,      "%s on %s",
        getenv("USER") ? getenv("USER") : MCCODE_NAME,
        getenv("HOST") ? getenv("HOST") : "localhost");
  time(&t);         /* get current write time */
  date_l = (long)t; /* same but as a long */
  snprintf(detector.date, CHAR_BUF_LENGTH, "%s", ctime(&t));
  if (strlen(detector.date))   detector.date[strlen(detector.date)-1] = '\0'; /* remove last \n in date */
  detector.date_l = date_l;

  if (!mcget_run_num() || mcget_run_num() >= mcget_ncount())
    snprintf(detector.ncount, CHAR_BUF_LENGTH, "%llu", mcget_ncount()
#ifdef USE_MPI
*mpi_node_count
#endif
  );
  else
    snprintf(detector.ncount, CHAR_BUF_LENGTH, "%g/%g", (double)mcget_run_num(), (double)mcget_ncount());

  detector.p0         = p0;
  detector.p1         = p1;
  detector.p2         = p2;

  /* handle transposition (not for NeXus) */
  if (!strcasestr(detector.format, "NeXus")) {
    if (m<0 || n<0 || p<0)             istransposed = !istransposed;
    if (strcasestr(detector.format, "transpose")) istransposed = !istransposed;
    if (istransposed) { /* do the swap once for all */
      long i=m; m=n; n=i;
    }
  }

  m=labs(m); n=labs(n); p=labs(p); /* make sure dimensions are positive */
  detector.istransposed = istransposed;

  /* determine detector rank (dimensionality) */
  if (!m || !n || !p || !p1) detector.rank = 4; /* invalid: exit with m=0 filename="" */
  else if (m*n*p == 1)       detector.rank = 0; /* 0D */
  else if (n == 1 || m == 1) detector.rank = 1; /* 1D */
  else if (p == 1)           detector.rank = 2; /* 2D */
  else                       detector.rank = 3; /* 3D */

  /* from rank, set type */
  switch (detector.rank) {
    case 0:  strcpy(detector.type,  "array_0d"); m=n=p=1; break;
    case 1:  snprintf(detector.type, CHAR_BUF_LENGTH, "array_1d(%ld)", m*n*p); m *= n*p; n=p=1; break;
    case 2:  snprintf(detector.type, CHAR_BUF_LENGTH, "array_2d(%ld, %ld)", m, n*p); n *= p; p=1; break;
    case 3:  snprintf(detector.type, CHAR_BUF_LENGTH, "array_3d(%ld, %ld, %ld)", m, n, p); break;
    default: m=0; strcpy(detector.type, ""); strcpy(detector.filename, "");/* invalid */
  }

  detector.m    = m;
  detector.n    = n;
  detector.p    = p;

  /* these only apply to detector files ===================================== */

  snprintf(detector.position, CHAR_BUF_LENGTH, "%g %g %g", position.x, position.y, position.z);
  /* may also store actual detector orientation in the future */

  strncpy(detector.title,      title && strlen(title) ? title : component,       CHAR_BUF_LENGTH);
  strncpy(detector.xlabel,     xlabel && strlen(xlabel) ? xlabel : "X", CHAR_BUF_LENGTH); /* axis labels */
  strncpy(detector.ylabel,     ylabel && strlen(ylabel) ? ylabel : "Y", CHAR_BUF_LENGTH);
  strncpy(detector.zlabel,     zlabel && strlen(zlabel) ? zlabel : "Z", CHAR_BUF_LENGTH);
  strncpy(detector.xvar,       xvar && strlen(xvar) ? xvar :       "x", CHAR_BUF_LENGTH); /* axis variables */
  strncpy(detector.yvar,       yvar && strlen(yvar) ? yvar :       detector.xvar, CHAR_BUF_LENGTH);
  strncpy(detector.zvar,       zvar && strlen(zvar) ? zvar :       detector.yvar, CHAR_BUF_LENGTH);

  /* set "variables" as e.g. "I I_err N" */
  strcpy(c, "I ");
  if (strlen(detector.zvar))      strncpy(c, detector.zvar,32);
  else if (strlen(detector.yvar)) strncpy(c, detector.yvar,32);
  else if (strlen(detector.xvar)) strncpy(c, detector.xvar,32);

  if (detector.rank == 1)
    snprintf(detector.variables, CHAR_BUF_LENGTH, "%s %s %s_err N", detector.xvar, c, c);
  else
    snprintf(detector.variables, CHAR_BUF_LENGTH, "%s %s_err N", c, c);

  /* limits */
  detector.xmin = x1;
  detector.xmax = x2;
  detector.ymin = y1;
  detector.ymax = y2;
  detector.zmin = z1;
  detector.zmax = z2;
  if (abs(detector.rank) == 1)
    snprintf(detector.limits, CHAR_BUF_LENGTH, "%g %g", x1, x2);
  else if (detector.rank == 2)
    snprintf(detector.limits, CHAR_BUF_LENGTH, "%g %g %g %g", x1, x2, y1, y2);
  else
    snprintf(detector.limits, CHAR_BUF_LENGTH, "%g %g %g %g %g %g", x1, x2, y1, y2, z1, z2);

  /* if MPI and nodes_nb > 1: reduce data sets when using MPI =============== */
#ifdef USE_MPI
  if (!strcasestr(detector.format,"list") && mpi_node_count > 1 && m) {
    /* we save additive data: reduce everything into mpi_node_root */
    if (p0) mc_MPI_Sum(p0, m*n*p);
    if (p1) mc_MPI_Sum(p1, m*n*p);
    if (p2) mc_MPI_Sum(p2, m*n*p);
    if (!p0) {  /* additive signal must be then divided by the number of nodes */
      int i;
      for (i=0; i<m*n*p; i++) {
        p1[i] /= mpi_node_count;
        if (p2) p2[i] /= mpi_node_count;
      }
    }
  }
#endif /* USE_MPI */

  /* compute statistics, Nsum, intensity, Error bars */
  detector = mcdetector_statistics(detector);

#ifdef USE_MPI
  /* slaves are done */
  if(mpi_node_rank != mpi_node_root) {
    return detector;
  }
#endif

  /* output "Detector:" line ================================================ */
  /* when this is a detector written by a component (not the SAVE from instrument),
     not an event lists */
  if (!m) return(detector);
  if (!strcasestr(detector.format,"list")) {
    if (!strcmp(detector.component, mcinstrument_name)) {
      if (strlen(detector.filename))  /* we name it from its filename, or from its title */
        strncpy(c, detector.filename, CHAR_BUF_LENGTH);
      else
        snprintf(c, CHAR_BUF_LENGTH, "%s", mcinstrument_name);
    } else
      strncpy(c, detector.component, CHAR_BUF_LENGTH);  /* usual detectors written by components */

    printf("Detector: %s_I=%g %s_ERR=%g %s_N=%g",
           c, detector.intensity,
           c, detector.error,
           c, detector.events);
    printf(" \"%s\"\n", strlen(detector.filename) ? detector.filename : detector.component);
  }
  

  return(detector);
} /* mcdetector_import */

/* end MCDETECTOR import section ============================================ */

















/* ========================================================================== */

/*                               ASCII output                                 */
/*     The SIM file is YAML based, the data files have '#' headers            */

/* ========================================================================== */


/*******************************************************************************
* mcinfo_out: output instrument tags/info (only in SIM)
* Used in: mcsiminfo_init (ascii), mcinfo(stdout)
*******************************************************************************/
static void mcinfo_out(char *pre, FILE *f)
{
  char Parameters[CHAR_BUF_LENGTH] = "";
  int  i;

  if (!f || mcdisable_output_files) return;

  /* create parameter string ================================================ */
  for(i = 0; i < mcnumipar; i++)
  {
    char ThisParam[CHAR_BUF_LENGTH];
    if (strlen(mcinputtable[i].name) > CHAR_BUF_LENGTH) break;
    snprintf(ThisParam, CHAR_BUF_LENGTH, " %s(%s)", mcinputtable[i].name,
            (*mcinputtypes[mcinputtable[i].type].parminfo)
                (mcinputtable[i].name));
    strcat(Parameters, ThisParam);
    if (strlen(Parameters) >= CHAR_BUF_LENGTH-64) break;
  }

  /* output data ============================================================ */
  if (f != stdout)
    fprintf(f, "%sFile: %s%c%s\n",    pre, mcdirname, MC_PATHSEP_C, mcsiminfo_name);
  else
    fprintf(f, "%sCreator: %s\n",     pre, MCCODE_STRING);

  fprintf(f, "%sSource: %s\n",   pre, mcinstrument_source);
  fprintf(f, "%sParameters: %s\n",    pre, Parameters);
  
  fprintf(f, "%sTrace_enabled: %s\n", pre, mctraceenabled ? "yes" : "no");
  fprintf(f, "%sDefault_main: %s\n",  pre, mcdefaultmain ?  "yes" : "no");
  fprintf(f, "%sEmbedded_runtime: %s\n", pre, 
#ifdef MC_EMBEDDED_RUNTIME
         "yes"
#else
         "no"
#endif
         );

  fflush(f);
} /* mcinfo_out */

/*******************************************************************************
* mcruninfo_out_backend: output simulation tags/info (both in SIM and data files)
* Used in: mcsiminfo_init (ascii case), mcdetector_out_xD_ascii, mcinfo(stdout)
*******************************************************************************/
static void mcruninfo_out_backend(char *pre, FILE *f, int info)
{
  int i;
  char Parameters[CHAR_BUF_LENGTH];

  if (!f || mcdisable_output_files) return;

  fprintf(f, "%sFormat: %s%s\n",      pre, 
    mcformat && strlen(mcformat) ? mcformat : MCCODE_NAME,
    mcformat && strcasestr(mcformat,"McCode") ? " with text headers" : "");
  fprintf(f, "%sURL: %s\n",         pre, "http://www.mccode.org");
  fprintf(f, "%sCreator: %s\n",     pre, MCCODE_STRING);
  fprintf(f, "%sInstrument: %s\n", pre, mcinstrument_source);
  fprintf(f, "%sNcount: %llu\n",        pre, mcget_ncount());
  fprintf(f, "%sTrace: %s\n",       pre, mcdotrace ? "yes" : "no");
  fprintf(f, "%sGravitation: %s\n", pre, mcgravitation ? "yes" : "no");
  snprintf(Parameters, CHAR_BUF_LENGTH, "%ld", mcseed);
  fprintf(f, "%sSeed: %s\n",        pre, Parameters);
  fprintf(f, "%sDirectory: %s\n",        pre, mcdirname ? mcdirname : ".");
#ifdef USE_MPI
  if (mpi_node_count > 1)
    fprintf(f, "%sNodes: %i\n",        pre, mpi_node_count);
#endif

  /* output parameter string ================================================ */
  for(i = 0; i < mcnumipar; i++) {
      if (!info){
          (*mcinputtypes[mcinputtable[i].type].printer)(Parameters, mcinputtable[i].par);
          fprintf(f, "%sParam: %s=%s\n", pre, mcinputtable[i].name, Parameters);
      }else{
        /*if an info run, some variables might not have values. Flag these by "NULL"*/
	if(mcinputtable[i].val && strlen(mcinputtable[i].val)){
            /* ... those with defautl values*/
            (*mcinputtypes[mcinputtable[i].type].printer)(Parameters, mcinputtable[i].par);
            fprintf(f, "%sParam: %s=%s\n", pre, mcinputtable[i].name, Parameters);
        }else{
            /* ... and those without */
            fprintf(f, "%sParam: %s=NULL\n", pre, mcinputtable[i].name);
	}
      }
  }
} /* mcruninfo_out_backend */

/************************
* wrapper function to mcruninfo_out_backend
*  Regular runs use this whereas the single call from mcinfo is directly to the backend
*************************/
static void mcruninfo_out(char *pre, FILE *f){
    mcruninfo_out_backend(pre,f,0);
}

/*******************************************************************************
* mcsiminfo_out:    wrapper to fprintf(mcsiminfo_file)
*******************************************************************************/
void mcsiminfo_out(char *format, ...)
{
  va_list ap;

  if(mcsiminfo_file && !mcdisable_output_files)
  {
    va_start(ap, format);
    vfprintf(mcsiminfo_file, format, ap);
    va_end(ap);
  }
} /* mcsiminfo_out */


/*******************************************************************************
* mcdatainfo_out: output detector header
*   mcdatainfo_out(prefix, file_handle, detector) writes info to data file
*******************************************************************************/
static void
mcdatainfo_out(char *pre, FILE *f, MCDETECTOR detector)
{
  if (!f || !detector.m || mcdisable_output_files) return;
  
  /* output data ============================================================ */
  fprintf(f, "%sDate: %s (%li)\n",       pre, detector.date, detector.date_l);
  fprintf(f, "%stype: %s\n",       pre, detector.type);
  fprintf(f, "%sSource: %s\n",     pre, detector.instrument);
  fprintf(f, "%scomponent: %s\n",  pre, detector.component);
  fprintf(f, "%sposition: %s\n",   pre, detector.position);

  fprintf(f, "%stitle: %s\n",      pre, detector.title);
  fprintf(f, !mcget_run_num() || mcget_run_num() >= mcget_ncount() ?
             "%sNcount: %s\n" : 
             "%sratio: %s\n",  pre, detector.ncount);

  if (strlen(detector.filename)) {
    fprintf(f, "%sfilename: %s\n", pre, detector.filename);
  }

  fprintf(f, "%sstatistics: %s\n", pre, detector.statistics);
  fprintf(f, "%ssignal: %s\n",     pre, detector.signal);
  fprintf(f, "%svalues: %s\n",     pre, detector.values);

  if (detector.rank >= 1)
  {
    fprintf(f, "%sxvar: %s\n",     pre, detector.xvar);
    fprintf(f, "%syvar: %s\n",     pre, detector.yvar);
    fprintf(f, "%sxlabel: %s\n",   pre, detector.xlabel);
    fprintf(f, "%sylabel: %s\n",   pre, detector.ylabel);
    if (detector.rank > 1) {
      fprintf(f, "%szvar: %s\n",   pre, detector.zvar);
      fprintf(f, "%szlabel: %s\n", pre, detector.zlabel);
    }
  }

  fprintf(f, 
    abs(detector.rank)==1 ?
             "%sxlimits: %s\n" : 
             "%sxylimits: %s\n", pre, detector.limits);
  fprintf(f, "%svariables: %s\n", pre, 
    strcasestr(detector.format, "list") ? detector.ylabel : detector.variables);
    
  fflush(f);

} /* mcdatainfo_out */

/* mcdetector_out_array_ascii: output a single array to a file
 *   m: columns
 *   n: rows
 *   p: array
 *   f: file handle (already opened)
 */
static void mcdetector_out_array_ascii(long m, long n, double *p, FILE *f, char istransposed)
{
  if(f)
  {
    int i,j;
    for(j = 0; j < n; j++)
    {
      for(i = 0; i < m; i++)
      {
          fprintf(f, "%.10g ", p[!istransposed ? i*n + j : j*m+i]);
      }
      fprintf(f,"\n");
    }
  }
} /* mcdetector_out_array_ascii */

/*******************************************************************************
* mcdetector_out_0D_ascii: called by mcdetector_out_0D for ascii output
*******************************************************************************/
MCDETECTOR mcdetector_out_0D_ascii(MCDETECTOR detector)
{
  int exists=0;
  FILE *outfile = NULL;
  
  /* Write data set information to simulation description file. */
  MPI_MASTER(
    mcsiminfo_out("\nbegin data\n"); // detector.component
    mcdatainfo_out("  ", mcsiminfo_file, detector);
    mcsiminfo_out("end data\n");
    /* Don't write if filename is NULL: mcnew_file handles this (return NULL) */
    outfile = mcnew_file(detector.component, "dat", &exists);
    if(outfile)
    {
      /* write data file header and entry in simulation description file */
      mcruninfo_out( "# ", outfile);
      mcdatainfo_out("# ", outfile, detector);
      /* write I I_err N */
      fprintf(outfile, "%g %g %g\n", 
        detector.intensity, detector.error, detector.events);
      fclose(outfile);
    }
  ); /* MPI_MASTER */
  return(detector);
} /* mcdetector_out_0D_ascii */

/*******************************************************************************
* mcdetector_out_1D_ascii: called by mcdetector_out_1D for ascii output
*******************************************************************************/
MCDETECTOR mcdetector_out_1D_ascii(MCDETECTOR detector)
{
  int exists=0;
  FILE *outfile = NULL;

  MPI_MASTER(
    /* Write data set information to simulation description file. */
    mcsiminfo_out("\nbegin data\n"); // detector.filename
    mcdatainfo_out("  ", mcsiminfo_file, detector);
    mcsiminfo_out("end data\n");
    /* Loop over array elements, writing to file. */
    /* Don't write if filename is NULL: mcnew_file handles this (return NULL) */
    outfile = mcnew_file(detector.filename, "dat", &exists);
    if(outfile)
    {
      /* write data file header and entry in simulation description file */
      mcruninfo_out( "# ", outfile);
      mcdatainfo_out("# ", outfile, detector);
      /* output the 1D array columns */
      mcdetector_out_array_ascii(detector.m, detector.n, detector.p1, outfile, detector.istransposed);
      
      fclose(outfile);
    }
  ); /* MPI_MASTER */
  return(detector);
  
}  /* mcdetector_out_1D_ascii */

/*******************************************************************************
* mcdetector_out_2D_ascii: called by mcdetector_out_2D for ascii output
*******************************************************************************/
MCDETECTOR mcdetector_out_2D_ascii(MCDETECTOR detector)
{
  int exists=0;
  FILE *outfile = NULL;
  
  MPI_MASTER(
    /* Loop over array elements, writing to file. */
    /* Don't write if filename is NULL: mcnew_file handles this (return NULL) */
    outfile = mcnew_file(detector.filename, "dat", &exists);
    if(outfile)
    {
      /* write header only if file has just been created (not appending) */
      if (!exists) {
        /* Write data set information to simulation description file. */
        mcsiminfo_out("\nbegin data\n"); // detector.filename
        mcdatainfo_out("  ", mcsiminfo_file, detector);
        mcsiminfo_out("end data\n");
      
        mcruninfo_out( "# ", outfile);
        mcdatainfo_out("# ", outfile,   detector);
      }
      fprintf(outfile, "# Data [%s/%s] %s:\n", detector.component, detector.filename, detector.zvar);
      mcdetector_out_array_ascii(detector.m, detector.n*detector.p, detector.p1, 
        outfile, detector.istransposed);
      if (detector.p2) {
        fprintf(outfile, "# Errors [%s/%s] %s_err:\n", detector.component, detector.filename, detector.zvar);
        mcdetector_out_array_ascii(detector.m, detector.n*detector.p, detector.p2, 
          outfile, detector.istransposed);
      }
      if (detector.p0) {
        fprintf(outfile, "# Events [%s/%s] N:\n", detector.component, detector.filename);
        mcdetector_out_array_ascii(detector.m, detector.n*detector.p, detector.p0, 
          outfile, detector.istransposed);
      }
      fclose(outfile);
      
      if (!exists) {
        if (strcasestr(detector.format, "list"))
          printf("Events:   \"%s\"\n",  
            strlen(detector.filename) ? detector.filename : detector.component);
      }
    } /* if outfile */
  ); /* MPI_MASTER */
#ifdef USE_MPI
  if (strcasestr(detector.format, "list") && mpi_node_count > 1) {
    int node_i=0;
    /* loop along MPI nodes to write sequentially */
    for(node_i=0; node_i<mpi_node_count; node_i++) {
      /* MPI: slaves wait for the master to write its block, then append theirs */
      MPI_Barrier(MPI_COMM_WORLD);
      if (node_i != mpi_node_root && node_i == mpi_node_rank) {
        if(strlen(detector.filename) && !mcdisable_output_files)	/* Don't write if filename is NULL */
          outfile = mcnew_file(detector.filename, "dat", &exists);
        if (!exists)
          fprintf(stderr, "Warning: [MPI node %i] file '%s' does not exist yet, "
                          "MASTER should have opened it before.\n",
            mpi_node_rank, detector.filename);
        if(outfile) {
          mcdetector_out_array_ascii(detector.m, detector.n*detector.p, detector.p1, 
            outfile, detector.istransposed);
          fclose(outfile);
        }
      }
    }
  } /* if strcasestr list */
#endif
  return(detector);
} /* mcdetector_out_2D_ascii */

/*******************************************************************************
* strcpy_valid: makes a valid string for variable names.
*   copy 'original' into 'valid', replacing invalid characters by '_'
*   char arrays must be pre-allocated
*******************************************************************************/
static char *strcpy_valid(char *valid, char *original)
{
  long i;
  int  n=CHAR_BUF_LENGTH; /* max length of valid names */

  if (original == NULL || !strlen(original)) return(NULL);

  if (n > strlen(original)) n = strlen(original);
  else original += strlen(original)-n;
  strncpy(valid, original, n);

  for (i=0; i < n; i++)
  {
    if ( (valid[i] > 122)
      || (valid[i] < 32)
      || (strchr("!\"#$%&'()*+,-.:;<=>?@[\\]^`/ \n\r\t", valid[i]) != NULL) )
    {
      if (i) valid[i] = '_'; else valid[i] = 'm';
    }
  }
  valid[i] = '\0';

  return(valid);
} /* strcpy_valid */

/* end ascii output section ================================================= */







#ifdef USE_NEXUS

/* ========================================================================== */

/*                               NeXus output                                 */

/* ========================================================================== */

#define nxprintf(...)    nxstr('d', __VA_ARGS__)
#define nxprintattr(...) nxstr('a', __VA_ARGS__)

/*******************************************************************************
* nxstr: output a tag=value data set (char) in NeXus/current group
*   when 'format' is larger that 1024 chars it is used as value for the 'tag'
*   else the value is assembled with format and following arguments.
*   type='d' -> data set
*        'a' -> attribute for current data set
*******************************************************************************/
static int nxstr(char type, NXhandle *f, char *tag, char *format, ...)
{
  va_list ap;
  char value[CHAR_BUF_LENGTH];
  int  i;
  int  ret=NX_OK;
  
  if (!tag || !format || !strlen(tag) || !strlen(format)) return(NX_OK);
  
  /* assemble the value string */
  if (strlen(format) < CHAR_BUF_LENGTH) {
    va_start(ap, format);
    ret = vsnprintf(value, CHAR_BUF_LENGTH, format, ap);
    va_end(ap);
  
    i = strlen(value);
  } else {
    i = strlen(format);
  }

  if (type == 'd') {
    /* open/put/close data set */
    if (NXmakedata (f, tag, NX_CHAR, 1, &i) != NX_OK) return(NX_ERROR);
    NXopendata (f, tag);
    if (strlen(format) < CHAR_BUF_LENGTH)
      ret = NXputdata  (f, value);
    else
      ret = NXputdata  (f, format);
    NXclosedata(f);
  } else {
    if (strlen(format) < CHAR_BUF_LENGTH)
      ret = NXputattr  (f, tag, value, strlen(value), NX_CHAR);
    else
      ret = NXputattr  (f, tag, format, strlen(format), NX_CHAR);
  }
  
  return(ret);
  
} /* nxstr */

/*******************************************************************************
* mcinfo_readfile: read a full file into a string buffer which is allocated
*   Think to free the buffer after use.
* Used in: mcinfo_out_nexus (nexus)
*******************************************************************************/
char *mcinfo_readfile(char *filename)
{
  FILE *f = fopen(filename, "rb");
  if (!f) return(NULL);
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  rewind(f);
  char *string = malloc(fsize + 1);
  if (string) {
    int n = fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;
  }
  return(string);
}

/*******************************************************************************
* mcinfo_out: output instrument/simulation groups in NeXus file
* Used in: mcsiminfo_init (nexus)
*******************************************************************************/
static void mcinfo_out_nexus(NXhandle f)
{
  FILE  *fid;     /* for intrument source code/C/IDF */
  char  *buffer=NULL;
  time_t t     =time(NULL); /* for date */
  char   entry0[CHAR_BUF_LENGTH];
  int    count=0;
  char   name[CHAR_BUF_LENGTH];
  char   class[CHAR_BUF_LENGTH];
  
  if (!f || mcdisable_output_files) return;
  
  /* write NeXus NXroot attributes */
  /* automatically added: file_name, HDF5_Version, file_time, NeXus_version */ 
  nxprintattr(f, "creator",   "%s generated with " MCCODE_STRING, mcinstrument_name);
  
  /* count the number of existing NXentry and create the next one */
  NXgetgroupinfo(f, &count, name, class);
  sprintf(entry0, "entry%i", count+1);

  /* create the main NXentry (mandatory in NeXus) */
  if (NXmakegroup(f, entry0, "NXentry") == NX_OK) 
  if (NXopengroup(f, entry0, "NXentry") == NX_OK) {
    
    nxprintf(nxhandle, "program_name", MCCODE_STRING);
    nxprintf(f, "start_time", ctime(&t));
    nxprintf(f, "title", "%s%s%s simulation generated by instrument %s", 
      mcdirname && strlen(mcdirname) ? mcdirname : ".", MC_PATHSEP_S, mcsiminfo_name,
      mcinstrument_name);
    nxprintattr(f, "program_name", MCCODE_STRING);
    nxprintattr(f, "instrument",   mcinstrument_name);
    nxprintattr(f, "simulation",   "%s%s%s",
        mcdirname && strlen(mcdirname) ? mcdirname : ".", MC_PATHSEP_S, mcsiminfo_name);

    /* write NeXus instrument group */
    if (NXmakegroup(f, "instrument", "NXinstrument") == NX_OK)
    if (NXopengroup(f, "instrument", "NXinstrument") == NX_OK) {
      int   i;
      char *string=NULL;

      /* write NeXus parameters(types) data =================================== */
      string = (char*)malloc(CHAR_BUF_LENGTH);
      if (string) {
        strcpy(string, "");
        for(i = 0; i < mcnumipar; i++)
        {
          char ThisParam[CHAR_BUF_LENGTH];
          snprintf(ThisParam, CHAR_BUF_LENGTH, " %s(%s)", mcinputtable[i].name,
                  (*mcinputtypes[mcinputtable[i].type].parminfo)
                      (mcinputtable[i].name));
          if (strlen(string) + strlen(ThisParam) < CHAR_BUF_LENGTH)
            strcat(string, ThisParam);
        }
        nxprintattr(f, "Parameters",    string);
        free(string);
      }
        
      nxprintattr(f, "name",          mcinstrument_name);
      nxprintf   (f, "name",          mcinstrument_name);
      nxprintattr(f, "Source",        mcinstrument_source);
      
      nxprintattr(f, "Trace_enabled", mctraceenabled ? "yes" : "no");
      nxprintattr(f, "Default_main",  mcdefaultmain ?  "yes" : "no");
      nxprintattr(f, "Embedded_runtime",  
  #ifdef MC_EMBEDDED_RUNTIME
           "yes"
  #else
           "no"
  #endif
           );
           
      /* add instrument source code when available */
      buffer = mcinfo_readfile(mcinstrument_source);
      if (buffer && strlen(buffer)) {
        long length=strlen(buffer);
        nxprintf (f, "description", buffer);
        NXopendata(f,"description");
        nxprintattr(f, "file_name", mcinstrument_source);
        nxprintattr(f, "file_size", "%li", length);
        nxprintattr(f, "MCCODE_STRING", MCCODE_STRING);
        NXclosedata(f);
        nxprintf (f,"instrument_source", "%s " MCCODE_NAME " " MCCODE_PARTICLE " Monte Carlo simulation", mcinstrument_name);
        free(buffer);
      } else
        nxprintf (f, "description", "File %s not found (instrument description %s is missing)", 
          mcinstrument_source, mcinstrument_name);
      
      /* add Mantid/IDF.xml when available */
      char *IDFfile=NULL;
      IDFfile = (char*)malloc(CHAR_BUF_LENGTH);
      sprintf(IDFfile,"%s%s",mcinstrument_source,".xml");
      buffer = mcinfo_readfile(IDFfile);
      if (buffer && strlen(buffer)) {
        NXmakegroup (nxhandle, "instrument_xml", "NXnote");
        NXopengroup (nxhandle, "instrument_xml", "NXnote");
        nxprintf(f, "data", buffer);
        nxprintf(f, "description", "IDF.xml file found with instrument %s", mcinstrument_source);
        nxprintf(f, "type", "text/xml");
        NXclosegroup(f); /* instrument_xml */
        free(buffer);
      }
      free(IDFfile);
      NXclosegroup(f); /* instrument */
    } /* NXinstrument */

    /* write NeXus simulation group */
    if (NXmakegroup(f, "simulation", "NXnote") == NX_OK)
    if (NXopengroup(f, "simulation", "NXnote") == NX_OK) {

      nxprintattr(f, "name",   "%s%s%s",
        mcdirname && strlen(mcdirname) ? mcdirname : ".", MC_PATHSEP_S, mcsiminfo_name);
      
      nxprintf   (f, "name",      "%s",     mcsiminfo_name);
      nxprintattr(f, "Format",    mcformat && strlen(mcformat) ? mcformat : MCCODE_NAME);
      nxprintattr(f, "URL",       "http://www.mccode.org");
      nxprintattr(f, "program",   MCCODE_STRING);
      nxprintattr(f, "Instrument",mcinstrument_source);
      nxprintattr(f, "Trace",     mcdotrace ?     "yes" : "no");
      nxprintattr(f, "Gravitation",mcgravitation ? "yes" : "no");
      nxprintattr(f, "Seed",      "%li", mcseed);
      nxprintattr(f, "Directory", mcdirname);
    #ifdef USE_MPI
      if (mpi_node_count > 1)
        nxprintf(f, "Nodes", "%i",        mpi_node_count);
    #endif
    
      /* output parameter string ================================================ */
      if (NXmakegroup(f, "Param", "NXparameters") == NX_OK)
      if (NXopengroup(f, "Param", "NXparameters") == NX_OK) {
        int i;
        char string[CHAR_BUF_LENGTH];
        for(i = 0; i < mcnumipar; i++) {
          if (mcget_run_num() || (mcinputtable[i].val && strlen(mcinputtable[i].val))) {
            if (mcinputtable[i].par == NULL)
              strncpy(string, (mcinputtable[i].val ? mcinputtable[i].val : ""), CHAR_BUF_LENGTH);
            else
              (*mcinputtypes[mcinputtable[i].type].printer)(string, mcinputtable[i].par);

            nxprintf(f,  mcinputtable[i].name, "%s", string);
            nxprintattr(f, mcinputtable[i].name, string);
          }
        }
        NXclosegroup(f); /* Param */
      } /* NXparameters */
      
      NXclosegroup(f); /* simulation */
    } /* NXsimulation */
    
    /* create a group to hold all monitors */
    NXmakegroup(f, "data", "NXdetector");

    /* leave the NXentry opened (closed at exit) */
  } /* NXentry */
} /* mcinfo_out_nexus */

/*******************************************************************************
* mcdatainfo_out_nexus: output detector header
*   mcdatainfo_out_nexus(detector) create group and write info to NeXus data file
*   open data:NXdetector then filename:NXdata and write headers/attributes
*   requires: NXentry to be opened
*******************************************************************************/
static void
mcdatainfo_out_nexus(NXhandle f, MCDETECTOR detector)
{
  char data_name[CHAR_BUF_LENGTH];
  if (!f || !detector.m || mcdisable_output_files) return;
  
  strcpy_valid(data_name, 
    detector.filename && strlen(detector.filename) ? 
      detector.filename : detector.component);

  /* the NXdetector group has been created in mcinfo_out_nexus (mcsiminfo_init) */
  if (NXopengroup(f, "data", "NXdetector") == NX_OK) {

    /* create and open the data group */
    /* this may fail when appending to list -> ignore/skip */
    NXMDisableErrorReporting(); /* unactivate NeXus error messages, as creation may fail */
    
    if (NXmakegroup(f, data_name, "NXdata") == NX_OK)
    if (NXopengroup(f, data_name, "NXdata") == NX_OK) {
    
      /* output metadata (as attributes) ======================================== */
      nxprintattr(f, "Date",       detector.date);
      nxprintattr(f, "type",       detector.type);
      nxprintattr(f, "Source",     detector.instrument);
      nxprintattr(f, "component",  detector.component);
      nxprintattr(f, "position",   detector.position);

      nxprintattr(f, "title",      detector.title);
      nxprintattr(f, !mcget_run_num() || mcget_run_num() >= mcget_ncount() ?
                 "Ncount" : 
                 "ratio",  detector.ncount);

      if (strlen(detector.filename)) {
        nxprintattr(f, "filename", detector.filename);
      }

      nxprintattr(f, "statistics", detector.statistics);
      nxprintattr(f, "signal",     detector.signal);
      nxprintattr(f, "values",     detector.values);

      if (detector.rank >= 1)
      {
        nxprintattr(f, "xvar",     detector.xvar);
        nxprintattr(f, "yvar",     detector.yvar);
        nxprintattr(f, "xlabel",   detector.xlabel);
        nxprintattr(f, "ylabel",   detector.ylabel);
        if (detector.rank > 1) {
          nxprintattr(f, "zvar",   detector.zvar);
          nxprintattr(f, "zlabel", detector.zlabel);
        }
      }

      nxprintattr(f, abs(detector.rank)==1 ?
                 "xlimits" : 
                 "xylimits", detector.limits);
      nxprintattr(f, "variables", 
        strcasestr(detector.format, "list") ? detector.ylabel : detector.variables);
      nxprintf(f, "distance", detector.position);
      nxprintf(f, "acquisition_mode",
        strcasestr(detector.format, "list") ? "event" : "summed");
        
      NXclosegroup(f);
    } /* NXdata (filename) */
    NXMEnableErrorReporting();  /* re-enable NeXus error messages */
    NXclosegroup(f);
  } /* NXdetector (data) */
  
} /* mcdatainfo_out_nexus */

/*******************************************************************************
* mcdetector_out_axis_nexus: write detector axis into current NXdata
*   requires: NXdata to be opened
*******************************************************************************/
int mcdetector_out_axis_nexus(NXhandle f, char *label, char *var, int rank, long length, double min, double max)
{
  if (!f || length <= 1 || mcdisable_output_files || max == min) return(NX_OK);
  else {
    double axis[length];
    char valid[CHAR_BUF_LENGTH];
    int dim=(int)length;
    int i;
    int nprimary=1;
    /* create an axis from [min:max] */
    for(i = 0; i < length; i++)
      axis[i] = min+(max-min)*(i+0.5)/length;
    /* create the data set */
    strcpy_valid(valid, label);
    NXcompmakedata(f, valid, NX_FLOAT64, 1, &dim, NX_COMP_LZW, &dim);
    /* open it */
    if (NXopendata(f, valid) != NX_OK) {
      fprintf(stderr, "Warning: could not open axis rank %i '%s' (NeXus)\n",
        rank, valid);
      return(NX_ERROR);
    }
    /* put the axis and its attributes */
    NXputdata  (f, axis);
    nxprintattr(f, "long_name",  label);
    nxprintattr(f, "short_name", var);
    NXputattr  (f, "axis",       &rank,     1, NX_INT32);
    nxprintattr(f, "units",      var);
    NXputattr  (f, "primary",    &nprimary, 1, NX_INT32);
    NXclosedata(f);
    
    return(NX_OK);
  }
} /* mcdetector_out_axis_nexus */

/*******************************************************************************
* mcdetector_out_array_nexus: write detector array into current NXdata (1D,2D)
*   requires: NXdata to be opened
*******************************************************************************/
int mcdetector_out_array_nexus(NXhandle f, char *part, double *data, MCDETECTOR detector)
{
  
  int dims[3]={detector.m,detector.n,detector.p};  /* number of elements to write */
  int signal=1;
  int exists=0;
  int current_dims[3]={0,0,0};
  int ret=NX_OK;
  
  if (!f || !data || !detector.m || mcdisable_output_files) return(NX_OK);
  
  /* when this is a list, we set 1st dimension to NX_UNLIMITED for creation */
  if (strcasestr(detector.format, "list")) dims[0] = NX_UNLIMITED;
  
  /* create the data set in NXdata group */
  NXMDisableErrorReporting(); /* unactivate NeXus error messages, as creation may fail */
  /* NXcompmakedata fails with NX_UNLIMITED */
  if (strcasestr(detector.format, "list"))
    ret = NXmakedata(    f, part, NX_FLOAT64, detector.rank, dims);
  else
    ret = NXcompmakedata(f, part, NX_FLOAT64, detector.rank, dims, NX_COMP_LZW, dims);
  if (ret != NX_OK) {
    /* failed: data set already exists */
    int datatype=0;
    int rank=0;
    exists=1;
    /* inquire current size of data set (nb of events stored) */
    NXopendata(f, part);
    NXgetinfo(f, &rank, current_dims, &datatype);
    NXclosedata(f);
  }
  NXMEnableErrorReporting();  /* re-enable NeXus error messages */
  dims[0] = detector.m; /* restore actual dimension from data writing */
  
  /* open the data set */
  if (NXopendata(f, part) == NX_ERROR) {
    fprintf(stderr, "Warning: could not open DataSet %s '%s' (NeXus)\n",
      part, detector.title);
    return(NX_ERROR);
  }
  if (strcasestr(detector.format, "list")) {
    current_dims[1] = current_dims[2] = 0; /* set starting location for writing slab */
    NXputslab(f, data, current_dims, dims);
    if (!exists)
      printf("Events:   \"%s\"\n",  
        strlen(detector.filename) ? detector.filename : detector.component);
  } else {
    NXputdata (f, data);
  }
  
  if (strstr(part,"data") || strstr(part, "events")) {
    NXputattr(f, "signal", &signal, 1, NX_INT32);
    nxprintattr(f, "short_name", detector.filename && strlen(detector.filename) ? 
      detector.filename : detector.component);
  }
  nxprintattr(f, "long_name", "%s '%s'", part, detector.title);
  NXclosedata(f);
  
  return(NX_OK);
} /* mcdetector_out_array_nexus */

/*******************************************************************************
* mcdetector_out_data_nexus: write detector axes+data into current NXdata
*   The data:NXdetector is opened, then filename:NXdata
*   requires: NXentry to be opened
*******************************************************************************/
int mcdetector_out_data_nexus(NXhandle f, MCDETECTOR detector)
{
  char data_name[CHAR_BUF_LENGTH];
  
  if (!f || !detector.m || mcdisable_output_files) return(NX_OK);
  
  strcpy_valid(data_name, 
    detector.filename && strlen(detector.filename) ? 
      detector.filename : detector.component);

  /* the NXdetector group has been created in mcinfo_out_nexus (mcsiminfo_init) */
  if (NXopengroup(f, "data", "NXdetector") == NX_OK) {

    /* the NXdata group has been created in mcdatainfo_out_nexus */
    if (NXopengroup(f, data_name, "NXdata") == NX_OK) {
  
      /* write axes, for histogram data sets, not for lists */
      if (!strcasestr(detector.format, "list")) {
        mcdetector_out_axis_nexus(f, detector.xlabel, detector.xvar, 
          1, detector.m, detector.xmin, detector.xmax);
          
        mcdetector_out_axis_nexus(f, detector.ylabel, detector.yvar, 
          2, detector.n, detector.ymin, detector.ymax);
          
        mcdetector_out_axis_nexus(f, detector.zlabel, detector.zvar, 
          3, detector.p, detector.zmin, detector.zmax);

      } /* !list */
      
      /* write the actual data (appended if already exists) */
      if (!strcasestr(detector.format, "list")) {
        mcdetector_out_array_nexus(f, "data", detector.p1, detector);
        mcdetector_out_array_nexus(f, "errors", detector.p2, detector);
        mcdetector_out_array_nexus(f, "ncount", detector.p0, detector);
      } else
        mcdetector_out_array_nexus(  f, "events", detector.p1, detector);
      
      NXclosegroup(f);
    } /* NXdata */
    NXclosegroup(f);
  } /* NXdetector */
  
  return(NX_OK);
} /* mcdetector_out_array_nexus */

#ifdef USE_MPI
/*******************************************************************************
* mcdetector_out_list_slaves: slaves send their list data to master which writes
*   requires: NXentry to be opened
* WARNING: this method has a flaw: it requires all nodes to flush the lists
*   the same number of times. In case one node is just below the buffer size
*   when finishing (e.g. monitor_nd), it may not trigger save but others may. 
*   Then the number of recv/send is not constant along nodes, and simulation stalls.  
*******************************************************************************/
MCDETECTOR mcdetector_out_list_slaves(MCDETECTOR detector)
{
  int     node_i=0;
  MPI_MASTER(
	     printf("\n** MPI master gathering slave node list data ** \n");
  );
  
  if (mpi_node_rank != mpi_node_root) {
    /* MPI slave: slaves send their data to master: 2 MPI_Send calls */
    /* m, n, p must be sent first, since all slaves do not have the same number of events */
    int mnp[3]={detector.m,detector.n,detector.p};

    if (mc_MPI_Send(mnp, 3, MPI_INT, mpi_node_root)!= MPI_SUCCESS)
      fprintf(stderr, "Warning: proc %i to master: MPI_Send mnp list error (mcdetector_out_list_slaves)\n", mpi_node_rank);
    if (!detector.p1
     || mc_MPI_Send(detector.p1, mnp[0]*mnp[1]*mnp[2], MPI_DOUBLE, mpi_node_root) != MPI_SUCCESS)
      fprintf(stderr, "Warning: proc %i to master: MPI_Send p1 list error: mnp=%i (mcdetector_out_list_slaves)\n", mpi_node_rank, abs(mnp[0]*mnp[1]*mnp[2]));
    /* slaves are done: sent mnp and p1 */
    return (detector);
  } /* end slaves */

  /* MPI master: receive data from slaves sequentially: 2 MPI_Recv calls */

  if (mpi_node_rank == mpi_node_root) {
    for(node_i=0; node_i<mpi_node_count; node_i++) {
      double *this_p1=NULL;                               /* buffer to hold the list from slaves */
      int     mnp[3]={0,0,0};  /* size of this buffer */
      if (node_i != mpi_node_root) { /* get data from slaves */
	if (mc_MPI_Recv(mnp, 3, MPI_INT, node_i) != MPI_SUCCESS)
	  fprintf(stderr, "Warning: master from proc %i: "
		  "MPI_Recv mnp list error (mcdetector_write_data)\n", node_i);
	if (mnp[0]*mnp[1]*mnp[2]) {
	  this_p1 = (double *)calloc(mnp[0]*mnp[1]*mnp[2], sizeof(double));
	  if (!this_p1 || mc_MPI_Recv(this_p1, abs(mnp[0]*mnp[1]*mnp[2]), MPI_DOUBLE, node_i)!= MPI_SUCCESS)
	    fprintf(stderr, "Warning: master from proc %i: "
		    "MPI_Recv p1 list error: mnp=%i (mcdetector_write_data)\n", node_i, mnp[0]*mnp[1]*mnp[2]);
	  else {
	    printf(". MPI master writing data for slave node %i\n",node_i);
	    detector.p1 = this_p1;
	    detector.m  = mnp[0]; detector.n  = mnp[1]; detector.p  = mnp[2];
	    
	    mcdetector_out_data_nexus(nxhandle, detector);
	  }
	}
      } /* if not master */
    } /* for */
  MPI_MASTER(
	     printf("\n** Done ** \n");
  );   
  }
}
#endif

MCDETECTOR mcdetector_out_0D_nexus(MCDETECTOR detector)
{
  /* Write data set information to NeXus file. */
  MPI_MASTER(
    mcdatainfo_out_nexus(nxhandle, detector);
  );
  
  return(detector);
} /* mcdetector_out_0D_ascii */

MCDETECTOR mcdetector_out_1D_nexus(MCDETECTOR detector_inc)
{
  MCDETECTOR detector = detector_inc;
  MPI_MASTER(
  mcdatainfo_out_nexus(nxhandle, detector);
  mcdetector_out_data_nexus(nxhandle, detector);
  );
  return(detector);
} /* mcdetector_out_1D_ascii */

MCDETECTOR mcdetector_out_2D_nexus(MCDETECTOR detector_inc)
{
  MCDETECTOR detector = detector_inc;
  MPI_MASTER(
  mcdatainfo_out_nexus(nxhandle, detector);
  mcdetector_out_data_nexus(nxhandle, detector);
  );
  
#ifdef USE_MPI // and USE_NEXUS
  /* NeXus: slave nodes have master write their lists */
  if (strcasestr(detector.format, "list") && mpi_node_count > 1) {
    mcdetector_out_list_slaves(detector);
  }
#endif /* USE_MPI */

  return(detector);
} /* mcdetector_out_2D_nexus */

#endif /* USE_NEXUS*/








/* ========================================================================== */

/*                            Main input functions                            */
/*            DETECTOR_OUT_xD function calls -> ascii or NeXus                */

/* ========================================================================== */

/*******************************************************************************
* mcsiminfo_init:   open SIM and write header
*******************************************************************************/
FILE *mcsiminfo_init(FILE *f)
{
  int exists=0;
  int index;
  
  /* check format */      
  if (!mcformat || !strlen(mcformat) 
   || !strcasecmp(mcformat, "MCSTAS") || !strcasecmp(mcformat, "MCXTRACE") 
   || !strcasecmp(mcformat, "PGPLOT") || !strcasecmp(mcformat, "GNUPLOT") || !strcasecmp(mcformat, "MCCODE")
   || !strcasecmp(mcformat, "MATLAB")) {
    mcformat="McCode";
#ifdef USE_NEXUS
  } else if (strcasestr(mcformat, "NeXus")) {
    /* Do nothing */
#endif
  } else {
    fprintf(stderr,
	    "Warning: You have requested the output format %s which is unsupported by this binary. Resetting to standard %s format.\n",mcformat ,"McCode");
    mcformat="McCode";
  }
  
  /* open the SIM file if not defined yet */
  if (mcsiminfo_file || mcdisable_output_files) 
    return (mcsiminfo_file);
    
#ifdef USE_NEXUS
  /* only master writes NeXus header: calls NXopen(nxhandle) */
  if (mcformat && strcasestr(mcformat, "NeXus")) {
	  MPI_MASTER(
	  mcsiminfo_file = mcnew_file(mcsiminfo_name, "h5", &exists);
    if(!mcsiminfo_file)
      fprintf(stderr,
	      "Warning: could not open simulation description file '%s'\n",
	      mcsiminfo_name);
	  else
	    mcinfo_out_nexus(nxhandle);
	  );
    return(mcsiminfo_file); /* points to nxhandle */
  }
#endif
  
  /* write main description file (only MASTER) */
  MPI_MASTER(

  mcsiminfo_file = mcnew_file(mcsiminfo_name, "sim", &exists);
  if(!mcsiminfo_file)
    fprintf(stderr,
	    "Warning: could not open simulation description file '%s'\n",
	    mcsiminfo_name);
  else
  {
    /* write SIM header */
    time_t t=time(NULL);
    mcsiminfo_out("%s simulation description file for %s.\n", 
      MCCODE_NAME, mcinstrument_name);
    mcsiminfo_out("Date:    %s", ctime(&t)); /* includes \n */
    mcsiminfo_out("Program: %s\n\n", MCCODE_STRING);
    
    mcsiminfo_out("begin instrument: %s\n", mcinstrument_name);
    mcinfo_out(   "  ", mcsiminfo_file);
    mcsiminfo_out("end instrument\n");

    mcsiminfo_out("\nbegin simulation: %s\n", mcdirname);
    mcruninfo_out("  ", mcsiminfo_file);
    mcsiminfo_out("end simulation\n");

  }
  return (mcsiminfo_file);
  
  ); /* MPI_MASTER */
  
} /* mcsiminfo_init */

/*******************************************************************************
*   mcsiminfo_close:  close SIM
*******************************************************************************/
void mcsiminfo_close()
{
  MPI_MASTER(
  if(mcsiminfo_file && !mcdisable_output_files) {
#ifdef USE_NEXUS
    if (mcformat && strcasestr(mcformat, "NeXus")) {
      time_t t=time(NULL);
      nxprintf(nxhandle, "end_time", ctime(&t));
      nxprintf(nxhandle, "duration", "%li", (long)t-mcstartdate);
      NXclosegroup(nxhandle); /* NXentry */
      NXclose(&nxhandle);
    } else
#endif
      fclose(mcsiminfo_file);
    );
    mcsiminfo_file = NULL;
  }
} /* mcsiminfo_close */

/*******************************************************************************
* mcdetector_out_0D: wrapper for 0D (single value).
*   Output single detector/monitor data (p0, p1, p2).
*   Title is t, component name is c.
*******************************************************************************/
MCDETECTOR mcdetector_out_0D(char *t, double p0, double p1, double p2,
                         char *c, Coords posa)
{
  /* import and perform basic detector analysis (and handle MPI reduce) */
  MCDETECTOR detector = mcdetector_import(mcformat,
    c, (t ? t : MCCODE_STRING " data"),
    1, 1, 1,
    "I", "", "",
    "I", "", "",
    0, 0, 0, 0, 0, 0, "",
    &p0, &p1, &p2, posa); /* write Detector: line */

#ifdef USE_NEXUS
  if (strcasestr(detector.format, "NeXus"))
    return(mcdetector_out_0D_nexus(detector));
  else
#endif
    return(mcdetector_out_0D_ascii(detector));
    
} /* mcdetector_out_0D */



/*******************************************************************************
* mcdetector_out_1D: wrapper for 1D.
*   Output 1d detector data (p0, p1, p2) for n bins linearly
*   distributed across the range x1..x2 (x1 is lower limit of first
*   bin, x2 is upper limit of last bin). Title is t, axis labels are xl
*   and yl. File name is f, component name is c.
*******************************************************************************/
MCDETECTOR mcdetector_out_1D(char *t, char *xl, char *yl,
        char *xvar, double x1, double x2,
        long n,
        double *p0, double *p1, double *p2, char *f,
        char *c, Coords posa)
{
  /* import and perform basic detector analysis (and handle MPI_Reduce) */
  MCDETECTOR detector = mcdetector_import(mcformat,
    c, (t ? t : MCCODE_STRING " 1D data"),
    n, 1, 1,
    xl, yl, (n > 1 ? "Signal per bin" : " Signal"),
    xvar, "(I,I_err)", "I",
    x1, x2, 0, 0, 0, 0, f,
    p0, p1, p2, posa); /* write Detector: line */
  if (!detector.p1 || !detector.m) return(detector);

#ifdef USE_NEXUS
  if (strcasestr(detector.format, "NeXus"))
    return(mcdetector_out_1D_nexus(detector));
  else
#endif
    return(mcdetector_out_1D_ascii(detector));
  
} /* mcdetector_out_1D */

/*******************************************************************************
* mcdetector_out_2D: wrapper for 2D.
*   special case for list: master creates file first, then slaves append their blocks without header
*******************************************************************************/
MCDETECTOR mcdetector_out_2D(char *t, char *xl, char *yl,
                  double x1, double x2, double y1, double y2,
                  long m, long n,
                  double *p0, double *p1, double *p2, char *f,
                  char *c, Coords posa)
{
  char xvar[CHAR_BUF_LENGTH];
  char yvar[CHAR_BUF_LENGTH];
  
  /* create short axes labels */
  if (xl && strlen(xl)) { strncpy(xvar, xl, CHAR_BUF_LENGTH); xvar[strcspn(xvar,"\n\r ")]='\0'; }
  else strcpy(xvar, "x");
  if (yl && strlen(yl)) { strncpy(yvar, yl, CHAR_BUF_LENGTH); yvar[strcspn(yvar,"\n\r ")]='\0'; }
  else strcpy(yvar, "y");

  MCDETECTOR detector;

  /* import and perform basic detector analysis (and handle MPI_Reduce) */
  if (labs(m) == 1) {/* n>1 on Y, m==1 on X: 1D, no X axis*/
    detector = mcdetector_import(mcformat,
      c, (t ? t : MCCODE_STRING " 1D data"),
      n, 1, 1,
      yl, "", "Signal per bin",
      yvar, "(I,Ierr)", "I",
      y1, y2, x1, x2, 0, 0, f,
      p0, p1, p2, posa); /* write Detector: line */
  } else if (labs(n)==1) {/* m>1 on X, n==1 on Y: 1D, no Y axis*/
    detector = mcdetector_import(mcformat,
      c, (t ? t : MCCODE_STRING " 1D data"),
      m, 1, 1,
      xl, "", "Signal per bin",
      xvar, "(I,Ierr)", "I",
      x1, x2, y1, y2, 0, 0, f,
      p0, p1, p2, posa); /* write Detector: line */
  }else {
    detector = mcdetector_import(mcformat,
      c, (t ? t : MCCODE_STRING " 2D data"),
      m, n, 1,
      xl, yl, "Signal per bin",
      xvar, yvar, "I",
      x1, x2, y1, y2, 0, 0, f,
      p0, p1, p2, posa); /* write Detector: line */
  }

  if (!detector.p1 || !detector.m) return(detector);

#ifdef USE_NEXUS
  if (strcasestr(detector.format, "NeXus"))
    return(mcdetector_out_2D_nexus(detector));
  else
#endif
    return(mcdetector_out_2D_ascii(detector));
  
} /* mcdetector_out_2D */

/*******************************************************************************
* mcdetector_out_list: wrapper for list output (calls out_2D with mcformat+"list").
*   m=number of events, n=size of each event
*******************************************************************************/
MCDETECTOR mcdetector_out_list(char *t, char *xl, char *yl,
                  long m, long n,
                  double *p1, char *f,
                  char *c, Coords posa)
{
  char       format_new[CHAR_BUF_LENGTH];
  char      *format_org;
  MCDETECTOR detector;
  
  format_org = mcformat;
  strcpy(format_new, mcformat);
  strcat(format_new, " list");
  mcformat = format_new;

  detector = mcdetector_out_2D(t, xl, yl,
                  1,labs(m),1,labs(n),
                  m,n,
                  NULL, p1, NULL, f,
                  c, posa);
  
  mcformat = format_org;
  return(detector);
}

/*******************************************************************************
 * mcuse_dir: set data/sim storage directory and create it,
 * or exit with error if exists
 ******************************************************************************/
static void
mcuse_dir(char *dir)
{
  if (!dir || !strlen(dir)) return;
#ifdef MC_PORTABLE
  fprintf(stderr, "Error: "
          "Directory output cannot be used with portable simulation (mcuse_dir)\n");
  exit(1);
#else  /* !MC_PORTABLE */
  /* handle file://directory URL type */
  if (strncmp(dir, "file://", strlen("file://")))
    mcdirname = dir;
  else
    mcdirname = dir+strlen("file://");
  
  
  
  MPI_MASTER(
    if(mkdir(mcdirname, 0777)) {
#ifndef DANSE
      fprintf(stderr, "Error: unable to create directory '%s' (mcuse_dir)\n", dir);
      fprintf(stderr, "(Maybe the directory already exists?)\n");
#endif
#ifdef USE_MPI
    MPI_Abort(MPI_COMM_WORLD, -1);
#endif
    exit(-1);
    }
  ); /* MPI_MASTER */
  
  /* remove trailing PATHSEP (if any) */
  while (strlen(mcdirname) && mcdirname[strlen(mcdirname) - 1] == MC_PATHSEP_C)
    mcdirname[strlen(mcdirname) - 1]='\0';
#endif /* !MC_PORTABLE */
} /* mcuse_dir */

/*******************************************************************************
* mcinfo: display instrument simulation info to stdout and exit
*******************************************************************************/
static void
mcinfo(void)
{
  fprintf(stdout, "begin instrument: %s\n", mcinstrument_name);
  mcinfo_out("  ", stdout);
  fprintf(stdout, "end instrument\n");
  fprintf(stdout, "begin simulation: %s\n", mcdirname ? mcdirname : ".");
  mcruninfo_out_backend("  ", stdout,1);
  fprintf(stdout, "end simulation\n");
  exit(0); /* includes MPI_Finalize in MPI mode */
} /* mcinfo */

#endif /* ndef MCCODE_R_IO_C */

/* end of the I/O section =================================================== */







/*******************************************************************************
* mcset_ncount: set total number of rays to generate
*******************************************************************************/
void mcset_ncount(unsigned long long int count)
{
  mcncount = count;
}

/* mcget_ncount: get total number of rays to generate */
unsigned long long int mcget_ncount(void)
{
  return mcncount;
}

/* mcget_run_num: get curent number of rays in TRACE */
unsigned long long int mcget_run_num(void)
{
  return mcrun_num;
}

/* mcsetn_arg: get ncount from a string argument */
static void
mcsetn_arg(char *arg)
{
  mcset_ncount((long long int) strtod(arg, NULL));
}

/* mcsetseed: set the random generator seed from a string argument */
static void
mcsetseed(char *arg)
{
  mcseed = atol(arg);
  if(mcseed) {
    srandom(mcseed);
  } else {
    fprintf(stderr, "Error: seed must not be zero (mcsetseed)\n");
    exit(1);
  }
}

/* Following part is only embedded when not redundent with mccode-r.h ========= */

#ifndef MCCODE_H

/* SECTION: MCDISPLAY support. =============================================== */

/*******************************************************************************
* Just output MCDISPLAY keywords to be caught by an external plotter client.
*******************************************************************************/

void mcdis_magnify(char *what){
  // Do nothing here, better use interactive zoom from the tools
}

void mcdis_line(double x1, double y1, double z1,
                double x2, double y2, double z2){
  printf("MCDISPLAY: multiline(2,%g,%g,%g,%g,%g,%g)\n",
         x1,y1,z1,x2,y2,z2);
}

void mcdis_dashed_line(double x1, double y1, double z1,
		       double x2, double y2, double z2, int n){
  int i;
  const double dx = (x2-x1)/(2*n+1);
  const double dy = (y2-y1)/(2*n+1);
  const double dz = (z2-z1)/(2*n+1);

  for(i = 0; i < n+1; i++)
    mcdis_line(x1 + 2*i*dx,     y1 + 2*i*dy,     z1 + 2*i*dz,
	       x1 + (2*i+1)*dx, y1 + (2*i+1)*dy, z1 + (2*i+1)*dz);
}

void mcdis_multiline(int count, ...){
  va_list ap;
  double x,y,z;

  printf("MCDISPLAY: multiline(%d", count);
  va_start(ap, count);
  while(count--)
    {
    x = va_arg(ap, double);
    y = va_arg(ap, double);
    z = va_arg(ap, double);
    printf(",%g,%g,%g", x, y, z);
    }
  va_end(ap);
  printf(")\n");
}

void mcdis_rectangle(char* plane, double x, double y, double z,
		     double width, double height){
  /* draws a rectangle in the plane           */
  /* x is ALWAYS width and y is ALWAYS height */
  if (strcmp("xy", plane)==0) {
    mcdis_multiline(5,
		    x - width/2, y - height/2, z,
		    x + width/2, y - height/2, z,
		    x + width/2, y + height/2, z,
		    x - width/2, y + height/2, z,
		    x - width/2, y - height/2, z);
  } else if (strcmp("xz", plane)==0) {
    mcdis_multiline(5,
		    x - width/2, y, z - height/2,
		    x + width/2, y, z - height/2,
		    x + width/2, y, z + height/2,
		    x - width/2, y, z + height/2,
		    x - width/2, y, z - height/2);
  } else if (strcmp("yz", plane)==0) {
    mcdis_multiline(5,
		    x, y - height/2, z - width/2,
		    x, y - height/2, z + width/2,
		    x, y + height/2, z + width/2,
		    x, y + height/2, z - width/2,
		    x, y - height/2, z - width/2);
  } else {

    fprintf(stderr, "Error: Definition of plane %s unknown\n", plane);
    exit(1);
  }
}

/*  draws a box with center at (x, y, z) and
    width (deltax), height (deltay), length (deltaz) */
void mcdis_box(double x, double y, double z,
	       double width, double height, double length){

  mcdis_rectangle("xy", x, y, z-length/2, width, height);
  mcdis_rectangle("xy", x, y, z+length/2, width, height);
  mcdis_line(x-width/2, y-height/2, z-length/2,
	     x-width/2, y-height/2, z+length/2);
  mcdis_line(x-width/2, y+height/2, z-length/2,
	     x-width/2, y+height/2, z+length/2);
  mcdis_line(x+width/2, y-height/2, z-length/2,
	     x+width/2, y-height/2, z+length/2);
  mcdis_line(x+width/2, y+height/2, z-length/2,
	     x+width/2, y+height/2, z+length/2);
}

void mcdis_circle(char *plane, double x, double y, double z, double r){
  printf("MCDISPLAY: circle('%s',%g,%g,%g,%g)\n", plane, x, y, z, r);
}

/* Draws a circle with center (x,y,z), radius (r), and in the plane
 * with normal (nx,ny,nz)*/
void mcdis_Circle(double x, double y, double z, double r, double nx, double ny, double nz){
    int i;
    if(nx==0 && ny && nz==0){
        for (i=0;i<24; i++){
            mcdis_line(x+r*sin(i*2*M_PI/24),y,z+r*cos(i*2*M_PI/24),
                    x+r*sin((i+1)*2*M_PI/24),y,z+r*cos((i+1)*2*M_PI/24));
        }
    }else{
        double mx,my,mz;
        /*generate perpendicular vector using (nx,ny,nz) and (0,1,0)*/
        vec_prod(mx,my,mz, 0,1,0, nx,ny,nz);
        NORM(mx,my,mz);
        /*draw circle*/
        for (i=0;i<24; i++){
            double ux,uy,uz;
            double wx,wy,wz;
            rotate(ux,uy,uz, mx,my,mz, i*2*M_PI/24, nx,ny,nz);
            rotate(wx,wy,wz, mx,my,mz, (i+1)*2*M_PI/24, nx,ny,nz);
            mcdis_line(x+ux*r,y+uy*r,z+uz*r,
                    x+wx*r,y+wy*r,z+wz*r);
        }
    }
}

/* Draws a cylinder with center at (x,y,z) with extent (r,height).
 * The cylinder axis is along the vector nx,ny,nz.
 * N determines how many vertical lines are drawn.*/
void mcdis_cylinder( double x, double y, double z,
        double r, double height, int N, double nx, double ny, double nz){
    int i;
    /*no lines make little sense - so trigger the default*/
    if(N<=0) N=5;

    NORM(nx,ny,nz);
    double h_2=height/2.0;
    mcdis_Circle(x+nx*h_2,y+ny*h_2,z+nz*h_2,r,nx,ny,nz);
    mcdis_Circle(x-nx*h_2,y-ny*h_2,z-nz*h_2,r,nx,ny,nz);

    double mx,my,mz;
    /*generate perpendicular vector using (nx,ny,nz) and (0,1,0)*/
    if(nx==0 && ny && nz==0){
        mx=my=0;mz=1;
    }else{
        vec_prod(mx,my,mz, 0,1,0, nx,ny,nz);
        NORM(mx,my,mz);
    }
    /*draw circle*/
    for (i=0; i<24; i++){
        double ux,uy,uz;
        rotate(ux,uy,uz, mx,my,mz, i*2*M_PI/24, nx,ny,nz);
        mcdis_line(x+nx*h_2+ux*r, y+ny*h_2+uy*r, z+nz*h_2+uz*r,
                 x-nx*h_2+ux*r, y-ny*h_2+uy*r, z-nz*h_2+uz*r);
    }
}

/* draws a sphere with center at (x,y,z) with extent (r)
 * The sphere is drawn using N longitudes and N latitudes.*/
void mcdis_sphere(double x, double y, double z, double r, int N){
    double nx,ny,nz;
    int i;
    /*no lines make little sense - so trigger the default*/
    if(N<=0) N=5;

    nx=0;ny=0;nz=1;
    mcdis_Circle(x,y,z,r,nx,ny,nz);
    for (i=1;i<N;i++){
        rotate(nx,ny,nz, nx,ny,nz, M_PI/N, 0,1,0);
        mcdis_Circle(x,y,z,r,nx,ny,nz);
    }
    /*lastly draw a great circle perpendicular to all N circles*/
    //mcdis_Circle(x,y,z,radius,1,0,0);

    for (i=1;i<=N;i++){
        double yy=-r+ 2*r*((double)i/(N+1));
        mcdis_Circle(x,y+yy ,z,  sqrt(r*r-yy*yy) ,0,1,0);
    }
}

/* SECTION: coordinates handling ============================================ */

/*******************************************************************************
* Since we use a lot of geometric calculations using Cartesian coordinates,
* we collect some useful routines here. However, it is also permissible to
* work directly on the underlying struct coords whenever that is most
* convenient (that is, the type Coords is not abstract).
*
* Coordinates are also used to store rotation angles around x/y/z axis.
*
* Since coordinates are used much like a basic type (such as double), the
* structure itself is passed and returned, rather than a pointer.
*
* At compile-time, the values of the coordinates may be unknown (for example
* a motor position). Hence coordinates are general expressions and not simple
* numbers. For this we used the type Coords_exp which has three CExp
* fields. For runtime (or calculations possible at compile time), we use
* Coords which contains three double fields.
*******************************************************************************/

/* coords_set: Assign coordinates. */
Coords
coords_set(MCNUM x, MCNUM y, MCNUM z)
{
  Coords a;

  a.x = x;
  a.y = y;
  a.z = z;
  return a;
}

/* coords_get: get coordinates. Required when 'x','y','z' are #defined as ray pars */
Coords
coords_get(Coords a, MCNUM *x, MCNUM *y, MCNUM *z)
{
  *x = a.x;
  *y = a.y;
  *z = a.z;
  return a;
}

/* coords_add: Add two coordinates. */
Coords
coords_add(Coords a, Coords b)
{
  Coords c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  if (fabs(c.z) < 1e-14) c.z=0.0;
  return c;
}

/* coords_sub: Subtract two coordinates. */
Coords
coords_sub(Coords a, Coords b)
{
  Coords c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  if (fabs(c.z) < 1e-14) c.z=0.0;
  return c;
}

/* coords_neg: Negate coordinates. */
Coords
coords_neg(Coords a)
{
  Coords b;

  b.x = -a.x;
  b.y = -a.y;
  b.z = -a.z;
  return b;
}

/* coords_scale: Scale a vector. */
Coords coords_scale(Coords b, double scale) {
  Coords a;

  a.x = b.x*scale;
  a.y = b.y*scale;
  a.z = b.z*scale;
  return a;
}

/* coords_sp: Scalar product: a . b */
double coords_sp(Coords a, Coords b) {
  double value;

  value = a.x*b.x + a.y*b.y + a.z*b.z;
  return value;
}

/* coords_xp: Cross product: a = b x c. */
Coords coords_xp(Coords b, Coords c) {
  Coords a;

  a.x = b.y*c.z - c.y*b.z;
  a.y = b.z*c.x - c.z*b.x;
  a.z = b.x*c.y - c.x*b.y;
  return a;
}

/* coords_len: Gives length of coords set. */
double coords_len(Coords a) {
  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

/* coords_mirror: Mirror a in plane (through the origin) defined by normal n*/
Coords coords_mirror(Coords a, Coords n) {
  double t = scalar_prod(n.x, n.y, n.z, n.x, n.y, n.z);
  Coords b;
  if (t!=1) {
    t = sqrt(t);
    n.x /= t;
    n.y /= t;
    n.z /= t;
  }
  t=scalar_prod(a.x, a.y, a.z, n.x, n.y, n.z);
  b.x = a.x-2*t*n.x;
  b.y = a.y-2*t*n.y;
  b.z = a.z-2*t*n.z;
  return b;
}

/* coords_print: Print out vector values. */
void coords_print(Coords a) {

  fprintf(stdout, "(%f, %f, %f)\n", a.x, a.y, a.z);
  return;
}

mcstatic void coords_norm(Coords* c) {
	double temp = coords_sp(*c,*c);

	// Skip if we will end dividing by zero
	if (temp == 0) return;

	temp = sqrt(temp);

	c->x /= temp;
	c->y /= temp;
	c->z /= temp;
}

/*******************************************************************************
* The Rotation type implements a rotation transformation of a coordinate
* system in the form of a double[3][3] matrix.
*
* Contrary to the Coords type in coords.c, rotations are passed by
* reference. Functions that yield new rotations do so by writing to an
* explicit result parameter; rotations are not returned from functions. The
* reason for this is that arrays cannot by returned from functions (though
* structures can; thus an alternative would have been to wrap the
* double[3][3] array up in a struct). Such are the ways of C programming.
*
* A rotation represents the tranformation of the coordinates of a vector when
* changing between coordinate systems that are rotated with respect to each
* other. For example, suppose that coordinate system Q is rotated 45 degrees
* around the Z axis with respect to coordinate system P. Let T be the
* rotation transformation representing a 45 degree rotation around Z. Then to
* get the coordinates of a vector r in system Q, apply T to the coordinates
* of r in P. If r=(1,0,0) in P, it will be (sqrt(1/2),-sqrt(1/2),0) in
* Q. Thus we should be careful when interpreting the sign of rotation angles:
* they represent the rotation of the coordinate systems, not of the
* coordinates (which has opposite sign).
*******************************************************************************/

/*******************************************************************************
* rot_set_rotation: Get transformation for rotation first phx around x axis,
* then phy around y, then phz around z.
*******************************************************************************/
void
rot_set_rotation(Rotation t, double phx, double phy, double phz)
{
  if ((phx == 0) && (phy == 0) && (phz == 0)) {
    t[0][0] = 1.0;
    t[0][1] = 0.0;
    t[0][2] = 0.0;
    t[1][0] = 0.0;
    t[1][1] = 1.0;
    t[1][2] = 0.0;
    t[2][0] = 0.0;
    t[2][1] = 0.0;
    t[2][2] = 1.0;
  } else {
    double cx = cos(phx);
    double sx = sin(phx);
    double cy = cos(phy);
    double sy = sin(phy);
    double cz = cos(phz);
    double sz = sin(phz);

    t[0][0] = cy*cz;
    t[0][1] = sx*sy*cz + cx*sz;
    t[0][2] = sx*sz - cx*sy*cz;
    t[1][0] = -cy*sz;
    t[1][1] = cx*cz - sx*sy*sz;
    t[1][2] = sx*cz + cx*sy*sz;
    t[2][0] = sy;
    t[2][1] = -sx*cy;
    t[2][2] = cx*cy;
  }
}

/*******************************************************************************
* rot_test_identity: Test if rotation is identity
*******************************************************************************/
int
rot_test_identity(Rotation t)
{
  return (t[0][0] + t[1][1] + t[2][2] == 3);
}

/*******************************************************************************
* rot_mul: Matrix multiplication of transformations (this corresponds to
* combining transformations). After rot_mul(T1, T2, T3), doing T3 is
* equal to doing first T2, then T1.
* Note that T3 must not alias (use the same array as) T1 or T2.
*******************************************************************************/
void
rot_mul(Rotation t1, Rotation t2, Rotation t3)
{
  if (rot_test_identity(t1)) {
    rot_copy(t3, t2);
  } else if (rot_test_identity(t2)) {
    rot_copy(t3, t1);
  } else {
    int i,j;
    for(i = 0; i < 3; i++)
      for(j = 0; j < 3; j++)
	t3[i][j] = t1[i][0]*t2[0][j] + t1[i][1]*t2[1][j] + t1[i][2]*t2[2][j];
  }
}

/*******************************************************************************
* rot_copy: Copy a rotation transformation (arrays cannot be assigned in C).
*******************************************************************************/
void
rot_copy(Rotation dest, Rotation src)
{
  int i,j;
  for(i = 0; i < 3; i++)
    for(j = 0; j < 3; j++)
      dest[i][j] = src[i][j];
}

/*******************************************************************************
* rot_transpose: Matrix transposition, which is inversion for Rotation matrices
*******************************************************************************/
void
rot_transpose(Rotation src, Rotation dst)
{
  dst[0][0] = src[0][0];
  dst[0][1] = src[1][0];
  dst[0][2] = src[2][0];
  dst[1][0] = src[0][1];
  dst[1][1] = src[1][1];
  dst[1][2] = src[2][1];
  dst[2][0] = src[0][2];
  dst[2][1] = src[1][2];
  dst[2][2] = src[2][2];
}

/*******************************************************************************
* rot_invert: Matrix inversion, in case a Rotatoin is used to represent a
* a general non-orthonormal matrix.
*******************************************************************************/
void
rot_invert(Rotation t1, Rotation t2)
{
  Rotation cofactors;
  int r,c;
  double det=0;
  for (r=0;r<3;r++){
    for (c=0;c<3;c++){
      /*this algorithm automatically takes care of the sign changes in computing cofactors*/
      cofactors[r][c]=t1[(r+1) % 3][(c+1) % 3]*t1[(r+2) % 3][(c+2) % 3] - t1[(r+2) % 3][(c+1) % 3]*t1[(r+1) % 3][(c +2) % 3] ;
    }
  }
  det=t1[0][0]*cofactors[0][0] + t1[0][1]*cofactors[0][1] + t1[0][2]*cofactors[0][2];
  if(det==0){
    fprintf(stderr,"Warning: matrix not invertable\n");
  }
  rot_transpose(cofactors,t2);

  /*the adjoint matrix should now be scaled by 1/det to get the inverse*/
  for (r=0;r<3;r++){
    for (c=0;c<3;c++){
      t2[r][c]=t2[r][c]/det;
    }
  }
}
/*******************************************************************************
* rot_apply: returns t*a
*******************************************************************************/
Coords
rot_apply(Rotation t, Coords a)
{
  Coords b;
  if (rot_test_identity(t)) {
    return a;
  } else {
    b.x = t[0][0]*a.x + t[0][1]*a.y + t[0][2]*a.z;
    b.y = t[1][0]*a.x + t[1][1]*a.y + t[1][2]*a.z;
    b.z = t[2][0]*a.x + t[2][1]*a.y + t[2][2]*a.z;
    return b;
  }
}

/**
 * Pretty-printing of rotation matrices.
 */
void rot_print(Rotation rot) {
	printf("[ %4.2f %4.2f %4.2f ]\n",
			rot[0][0], rot[0][1], rot[0][2]);
	printf("[ %4.2f %4.2f %4.2f ]\n",
			rot[1][0], rot[1][1], rot[1][2]);
	printf("[ %4.2f %4.2f %4.2f ]\n\n",
			rot[2][0], rot[2][1], rot[2][2]);
}

/**
 * Vector product: used by vec_prod (mccode-r.h). Use coords_xp for Coords.
 */
mcstatic void vec_prod_func(double *x, double *y, double *z,
		double x1, double y1, double z1,
		double x2, double y2, double z2) {
    *x = (y1)*(z2) - (y2)*(z1);
    *y = (z1)*(x2) - (z2)*(x1);
    *z = (x1)*(y2) - (x2)*(y1);
}

/**
 * Scalar product: use coords_sp for Coords.
 */
mcstatic double scalar_prod(
		double x1, double y1, double z1,
		double x2, double y2, double z2) {
	return ((x1 * x2) + (y1 * y2) + (z1 * z2));
}

/*******************************************************************************
* mccoordschange: applies rotation to (x y z) and (vx vy vz) and Spin (sx,sy,sz)
*******************************************************************************/
void
mccoordschange(Coords a, Rotation t, double *x, double *y, double *z,
               double *vx, double *vy, double *vz, double *sx, double *sy, double *sz)
{
  Coords b, c;

  b.x = *x;
  b.y = *y;
  b.z = *z;
  c = rot_apply(t, b);
  b = coords_add(c, a);
  *x = b.x;
  *y = b.y;
  *z = b.z;

  if ( (vz && vy  && vx) && (*vz != 0.0 || *vx != 0.0 || *vy != 0.0) ) mccoordschange_polarisation(t, vx, vy, vz);

  if ( (sz && sy  && sx) && (*sz != 0.0 || *sx != 0.0 || *sy != 0.0) ) mccoordschange_polarisation(t, sx, sy, sz);

}

/*******************************************************************************
* mccoordschange_polarisation: applies rotation to vector (sx sy sz)
*******************************************************************************/
void
mccoordschange_polarisation(Rotation t, double *sx, double *sy, double *sz)
{
  Coords b, c;

  b.x = *sx;
  b.y = *sy;
  b.z = *sz;
  c = rot_apply(t, b);
  *sx = c.x;
  *sy = c.y;
  *sz = c.z;
}

/* SECTION: vector math  ==================================================== */

/* normal_vec_func: Compute normal vector to (x,y,z). */
mcstatic void normal_vec_func(double *nx, double *ny, double *nz,
                double x, double y, double z)
{
  double ax = fabs(x);
  double ay = fabs(y);
  double az = fabs(z);
  double l;
  if(x == 0 && y == 0 && z == 0)
  {
    *nx = 0;
    *ny = 0;
    *nz = 0;
    return;
  }
  if(ax < ay)
  {
    if(ax < az)
    {                           /* Use X axis */
      l = sqrt(z*z + y*y);
      *nx = 0;
      *ny = z/l;
      *nz = -y/l;
      return;
    }
  }
  else
  {
    if(ay < az)
    {                           /* Use Y axis */
      l = sqrt(z*z + x*x);
      *nx = z/l;
      *ny = 0;
      *nz = -x/l;
      return;
    }
  }
  /* Use Z axis */
  l = sqrt(y*y + x*x);
  *nx = y/l;
  *ny = -x/l;
  *nz = 0;
} /* normal_vec */

/*******************************************************************************
 * solve_2nd_order: second order equation solve: A*t^2 + B*t + C = 0
 * solve_2nd_order(&t1, NULL, A,B,C)
 *   returns 0 if no solution was found, or set 't1' to the smallest positive
 *   solution.
 * solve_2nd_order(&t1, &t2, A,B,C)
 *   same as with &t2=NULL, but also returns the second solution.
 * EXAMPLE usage for intersection of a trajectory with a plane in gravitation
 * field (gx,gy,gz):
 * The neutron starts at point r=(x,y,z) with velocityv=(vx vy vz). The plane
 * has a normal vector n=(nx,ny,nz) and contains the point W=(wx,wy,wz).
 * The problem consists in solving the 2nd order equation:
 *      1/2.n.g.t^2 + n.v.t + n.(r-W) = 0
 * so that A = 0.5 n.g; B = n.v; C = n.(r-W);
 * Without acceleration, t=-n.(r-W)/n.v
 ******************************************************************************/
int solve_2nd_order_old(double *t1, double *t2,
                  double A,  double B,  double C)
{
  int ret=0;

  if (!t1) return 0;
  *t1 = 0;
  if (t2) *t2=0;

  if (fabs(A) < 1E-10) /* approximate to linear equation: A ~ 0 */
  {
    if (B) {  *t1 = -C/B; ret=1; if (t2) *t2=*t1; }
    /* else no intersection: A=B=0 ret=0 */
  }
  else
  {
    double D;
    D = B*B - 4*A*C;
    if (D >= 0) /* Delta > 0: two solutions */
    {
      double sD, dt1, dt2;
      sD = sqrt(D);
      dt1 = (-B + sD)/2/A;
      dt2 = (-B - sD)/2/A;
      /* we identify very small values with zero */
      if (fabs(dt1) < 1e-10) dt1=0.0;
      if (fabs(dt2) < 1e-10) dt2=0.0;

      /* now we choose the smallest positive solution */
      if      (dt1<=0.0 && dt2>0.0) ret=2; /* dt2 positive */
      else if (dt2<=0.0 && dt1>0.0) ret=1; /* dt1 positive */
      else if (dt1> 0.0 && dt2>0.0)
      {  if (dt1 < dt2) ret=1; else ret=2; } /* all positive: min(dt1,dt2) */
      /* else two solutions are negative. ret=-1 */
      if (ret==1) { *t1 = dt1;  if (t2) *t2=dt2; }
      else        { *t1 = dt2;  if (t2) *t2=dt1; }
      ret=2;  /* found 2 solutions and t1 is the positive one */
    } /* else Delta <0: no intersection. ret=0 */
  }
  return(ret);
} /* solve_2nd_order */

int solve_2nd_order(double *t0, double *t1, double A, double B, double C){
  int retval=0;
  double sign=copysign(1.0,B);
  double dt0,dt1;

  dt0=0;
  dt1=0;
  *t0;
  if(t1){ *t1=0;}

  /*protect against rounding errors by locally equating DBL_EPSILON with 0*/
  if (fabs(A)<DBL_EPSILON){
    A=0;
  }
  if (fabs(B)<DBL_EPSILON){
    B=0;
  }
  if (fabs(C)<DBL_EPSILON){
    C=0;
  }

  /*check if coefficient are sane*/
  if( A==0  && B==0){
    retval=0;
  }else{
    if(A==0){
      /*equation is linear*/
      dt0=-C/B;
      retval=1;
    }else if (C==0){
      /*one root is 0*/
      if(sign<0){
        dt0=0;dt1=-B/A;
      }else{
        dt0=-B/A;dt1=0;
      }
      retval=2;
    }else{
      /*a regular 2nd order eq. Also works out fine for B==0.*/
      double D;
      D=B*B-4*A*C;
      if (D>=0){
        dt0=(-B - sign*sqrt(B*B-4*A*C))/(2*A);
        dt1=C/(A*dt0);
        retval=2;
      }else{
        /*no real roots*/
        retval=0;
      }
    }
    /*sort the solutions*/
    if (retval==1){
      /*put both solutions in t0 and t1*/
      *t0=dt0;
      if(t1) *t1=dt1;
    }else{
      /*we have two solutions*/
      /*swap if both are positive and t1 smaller than t0 or t1 the only positive*/
      int swap=0;
      if(dt1>0 && ( dt1<dt0 || dt0<=0) ){
        swap=1;
      }
      if (swap){
        *t0=dt1;
        if(t1) *t1=dt0;
      }else{
        *t0=dt0;
        if(t1) *t1=dt0;
      }
    }

  }
  return retval;

} /*solve_2nd_order_improved*/


/*******************************************************************************
 * randvec_target_circle: Choose random direction towards target at (x,y,z)
 * with given radius.
 * If radius is zero, choose random direction in full 4PI, no target.
 ******************************************************************************/
void
randvec_target_circle(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi, double radius)
{
  double l2, phi, theta, nx, ny, nz, xt, yt, zt, xu, yu, zu;

  if(radius == 0.0)
  {
    /* No target, choose uniformly a direction in full 4PI solid angle. */
    theta = acos (1 - rand0max(2));
    phi = rand0max(2 * PI);
    if(solid_angle)
      *solid_angle = 4*PI;
    nx = 1;
    ny = 0;
    nz = 0;
    yi = sqrt(xi*xi+yi*yi+zi*zi);
    zi = 0;
    xi = 0;
  }
  else
  {
    double costheta0;
    l2 = xi*xi + yi*yi + zi*zi; /* sqr Distance to target. */
    costheta0 = sqrt(l2/(radius*radius+l2));
    if (radius < 0) costheta0 *= -1;
    if(solid_angle)
    {
      /* Compute solid angle of target as seen from origin. */
        *solid_angle = 2*PI*(1 - costheta0);
    }

    /* Now choose point uniformly on circle surface within angle theta0 */
    theta = acos (1 - rand0max(1 - costheta0)); /* radius on circle */
    phi = rand0max(2 * PI); /* rotation on circle at given radius */
    /* Now, to obtain the desired vector rotate (xi,yi,zi) angle theta around a
       perpendicular axis u=i x n and then angle phi around i. */
    if(xi == 0 && zi == 0)
    {
      nx = 1;
      ny = 0;
      nz = 0;
    }
    else
    {
      nx = -zi;
      nz = xi;
      ny = 0;
    }
  }

  /* [xyz]u = [xyz]i x n[xyz] (usually vertical) */
  vec_prod(xu,  yu,  zu, xi, yi, zi,        nx, ny, nz);
  /* [xyz]t = [xyz]i rotated theta around [xyz]u */
  rotate  (xt,  yt,  zt, xi, yi, zi, theta, xu, yu, zu);
  /* [xyz]o = [xyz]t rotated phi around n[xyz] */
  rotate (*xo, *yo, *zo, xt, yt, zt, phi, xi, yi, zi);
} /* randvec_target_circle */

/*******************************************************************************
 * randvec_target_rect_angular: Choose random direction towards target at
 * (xi,yi,zi) with given ANGULAR dimension height x width. height=phi_x=[0,PI],
 * width=phi_y=[0,2*PI] (radians)
 * If height or width is zero, choose random direction in full 4PI, no target.
 *******************************************************************************/
void
randvec_target_rect_angular(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi, double width, double height, Rotation A)
{
  double theta, phi, nx, ny, nz, xt, yt, zt, xu, yu, zu;
  Coords tmp;
  Rotation Ainverse;

  rot_transpose(A, Ainverse);

  if(height == 0.0 || width == 0.0)
  {
    randvec_target_circle(xo, yo, zo, solid_angle,
               xi, yi, zi, 0);
    return;
  }
  else
  {
    if(solid_angle)
    {
      /* Compute solid angle of target as seen from origin. */
      *solid_angle = 2*fabs(width*sin(height/2));
    }

    /* Go to global coordinate system */

    tmp = coords_set(xi, yi, zi);
    tmp = rot_apply(Ainverse, tmp);
    coords_get(tmp, &xi, &yi, &zi);

    /* Now choose point uniformly on the unit sphere segment with angle theta/phi */
    phi   = width*randpm1()/2.0;
    theta = asin(randpm1()*sin(height/2.0));
    /* Now, to obtain the desired vector rotate (xi,yi,zi) angle theta around
       n, and then phi around u. */
    if(xi == 0 && zi == 0)
    {
      nx = 1;
      ny = 0;
      nz = 0;
    }
    else
    {
      nx = -zi;
      nz = xi;
      ny = 0;
    }
  }

  /* [xyz]u = [xyz]i x n[xyz] (usually vertical) */
  vec_prod(xu,  yu,  zu, xi, yi, zi,        nx, ny, nz);
  /* [xyz]t = [xyz]i rotated theta around [xyz]u */
  rotate  (xt,  yt,  zt, xi, yi, zi, theta, nx, ny, nz);
  /* [xyz]o = [xyz]t rotated phi around n[xyz] */
  rotate (*xo, *yo, *zo, xt, yt, zt, phi, xu,  yu,  zu);

  /* Go back to local coordinate system */
  tmp = coords_set(*xo, *yo, *zo);
  tmp = rot_apply(A, tmp);
  coords_get(tmp, &*xo, &*yo, &*zo);

} /* randvec_target_rect_angular */

/*******************************************************************************
 * randvec_target_rect_real: Choose random direction towards target at (xi,yi,zi)
 * with given dimension height x width (in meters !).
 *
 * Local emission coordinate is taken into account and corrected for 'order' times.
 * (See remarks posted to mcstas-users by George Apostolopoulus <gapost@ipta.demokritos.gr>)
 *
 * If height or width is zero, choose random direction in full 4PI, no target.
 *
 * Traditionally, this routine had the name randvec_target_rect - this is now a
 * a define (see mcstas-r.h) pointing here. If you use the old rouine, you are NOT
 * taking the local emmission coordinate into account.
*******************************************************************************/

void
randvec_target_rect_real(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi,
               double width, double height, Rotation A,
               double lx, double ly, double lz, int order)
{
  double dx, dy, dist, dist_p, nx, ny, nz, mx, my, mz, n_norm, m_norm;
  double cos_theta;
  Coords tmp;
  Rotation Ainverse;

  rot_transpose(A, Ainverse);

  if(height == 0.0 || width == 0.0)
  {
    randvec_target_circle(xo, yo, zo, solid_angle,
               xi, yi, zi, 0);
    return;
  }
  else
  {

    /* Now choose point uniformly on rectangle within width x height */
    dx = width*randpm1()/2.0;
    dy = height*randpm1()/2.0;

    /* Determine distance to target plane*/
    dist = sqrt(xi*xi + yi*yi + zi*zi);
    /* Go to global coordinate system */

    tmp = coords_set(xi, yi, zi);
    tmp = rot_apply(Ainverse, tmp);
    coords_get(tmp, &xi, &yi, &zi);

    /* Determine vector normal to trajectory axis (z) and gravity [0 1 0] */
    vec_prod(nx, ny, nz, xi, yi, zi, 0, 1, 0);

    /* This now defines the x-axis, normalize: */
    n_norm=sqrt(nx*nx + ny*ny + nz*nz);
    nx = nx/n_norm;
    ny = ny/n_norm;
    nz = nz/n_norm;

    /* Now, determine our y-axis (vertical in many cases...) */
    vec_prod(mx, my, mz, xi, yi, zi, nx, ny, nz);
    m_norm=sqrt(mx*mx + my*my + mz*mz);
    mx = mx/m_norm;
    my = my/m_norm;
    mz = mz/m_norm;

    /* Our output, random vector can now be defined by linear combination: */

    *xo = xi + dx * nx + dy * mx;
    *yo = yi + dx * ny + dy * my;
    *zo = zi + dx * nz + dy * mz;

    /* Go back to local coordinate system */
    tmp = coords_set(*xo, *yo, *zo);
    tmp = rot_apply(A, tmp);
    coords_get(tmp, &*xo, &*yo, &*zo);

    /* Go back to local coordinate system */
    tmp = coords_set(xi, yi, zi);
    tmp = rot_apply(A, tmp);
    coords_get(tmp, &xi, &yi, &zi);

    if (solid_angle) {
      /* Calculate vector from local point to remote random point */
      lx = *xo - lx;
      ly = *yo - ly;
      lz = *zo - lz;
      dist_p = sqrt(lx*lx + ly*ly + lz*lz);

      /* Adjust the 'solid angle' */
      /* 1/r^2 to the chosen point times cos(\theta) between the normal */
      /* vector of the target rectangle and direction vector of the chosen point. */
      cos_theta = (xi * lx + yi * ly + zi * lz) / (dist * dist_p);
      *solid_angle = width * height / (dist_p * dist_p);
      int counter;
      for (counter = 0; counter < order; counter++) {
	*solid_angle = *solid_angle * cos_theta;
      }
    }
  }
} /* randvec_target_rect_real */

/* SECTION: random numbers ================================================== */

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * This is derived from the Berkeley source:
 *        @(#)random.c        5.5 (Berkeley) 7/6/88
 * It was reworked for the GNU C Library by Roland McGrath.
 * Rewritten to use reentrant functions by Ulrich Drepper, 1995.
 */

/*******************************************************************************
* Modified for McStas from glibc 2.0.7pre1 stdlib/random.c and
* stdlib/random_r.c.
*
* This way random() is more than four times faster compared to calling
* standard glibc random() on ix86 Linux, probably due to multithread support,
* ELF shared library overhead, etc. It also makes McStas generated
* simulations more portable (more likely to behave identically across
* platforms, important for parrallel computations).
*******************************************************************************/


#define        TYPE_3                3
#define        BREAK_3                128
#define        DEG_3                31
#define        SEP_3                3

static mc_int32_t randtbl[DEG_3 + 1] =
  {
    TYPE_3,

    -1726662223, 379960547, 1735697613, 1040273694, 1313901226,
    1627687941, -179304937, -2073333483, 1780058412, -1989503057,
    -615974602, 344556628, 939512070, -1249116260, 1507946756,
    -812545463, 154635395, 1388815473, -1926676823, 525320961,
    -1009028674, 968117788, -123449607, 1284210865, 435012392,
    -2017506339, -911064859, -370259173, 1132637927, 1398500161,
    -205601318,
  };

static mc_int32_t *fptr = &randtbl[SEP_3 + 1];
static mc_int32_t *rptr = &randtbl[1];
static mc_int32_t *state = &randtbl[1];
#define rand_deg DEG_3
#define rand_sep SEP_3
static mc_int32_t *end_ptr = &randtbl[sizeof (randtbl) / sizeof (randtbl[0])];

mc_int32_t
mc_random (void)
{
  mc_int32_t result;

  *fptr += *rptr;
  /* Chucking least random bit.  */
  result = (*fptr >> 1) & 0x7fffffff;
  ++fptr;
  if (fptr >= end_ptr)
  {
    fptr = state;
    ++rptr;
  }
  else
  {
    ++rptr;
    if (rptr >= end_ptr)
      rptr = state;
  }
  return result;
}

void
mc_srandom (unsigned int x)
{
  /* We must make sure the seed is not 0.  Take arbitrarily 1 in this case.  */
  state[0] = x ? x : 1;
  {
    long int i;
    for (i = 1; i < rand_deg; ++i)
    {
      /* This does:
         state[i] = (16807 * state[i - 1]) % 2147483647;
         but avoids overflowing 31 bits.  */
      long int hi = state[i - 1] / 127773;
      long int lo = state[i - 1] % 127773;
      long int test = 16807 * lo - 2836 * hi;
      state[i] = test + (test < 0 ? 2147483647 : 0);
    }
    fptr = &state[rand_sep];
    rptr = &state[0];
    for (i = 0; i < 10 * rand_deg; ++i)
      random ();
  }
}

/* "Mersenne Twister", by Makoto Matsumoto and Takuji Nishimura. */
/* See http://www.math.keio.ac.jp/~matumoto/emt.html for original source. */


/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using mt_srandom(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.keio.ac.jp/matumoto/emt.html
   email: matumoto@math.keio.ac.jp
*/

#include <stdio.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void mt_srandom(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
            (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void init_by_array(unsigned long init_key[], unsigned long key_length)
{
    int i, j, k;
    mt_srandom(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long mt_random(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if mt_srandom() has not been called, */
            mt_srandom(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

#undef N
#undef M
#undef MATRIX_A
#undef UPPER_MASK
#undef LOWER_MASK

/* End of "Mersenne Twister". */

/* End of McCode random number routine. */

/* randnorm: generate a random number from normal law */
double
randnorm(void)
{
  static double v1, v2, s;
  static int phase = 0;
  double X, u1, u2;

  if(phase == 0)
  {
    do
    {
      u1 = rand01();
      u2 = rand01();
      v1 = 2*u1 - 1;
      v2 = 2*u2 - 1;
      s = v1*v1 + v2*v2;
    } while(s >= 1 || s == 0);

    X = v1*sqrt(-2*log(s)/s);
  }
  else
  {
    X = v2*sqrt(-2*log(s)/s);
  }

  phase = 1 - phase;
  return X;
}

/**
 * Generate a random number from -1 to 1 with triangle distribution
 */
double randtriangle(void) {
	double randnum = rand01();
	if (randnum>0.5) return(1-sqrt(2*(randnum-0.5)));
	else return(sqrt(2*randnum)-1);
}

/**
 * Random number between 0.0 and 1.0 (including?)
 */
double rand01() {
	double randnum;
	randnum = (double) random();
	randnum /= (double) MC_RAND_MAX + 1;
	return randnum;
}

/**
 * Return a random number between 1 and -1
 */
double randpm1() {
	double randnum;
	randnum = (double) random();
	randnum /= ((double) MC_RAND_MAX + 1) / 2;
	randnum -= 1;
	return randnum;
}

/**
 * Return a random number between 0 and max.
 */
double rand0max(double max) {
	double randnum;
	randnum = (double) random();
	randnum /= ((double) MC_RAND_MAX + 1) / max;
	return randnum;
}

/**
 * Return a random number between min and max.
 */
double randminmax(double min, double max) {
	return rand0max(max - min) + max;
}

/* SECTION: main and signal handlers ======================================== */

/*******************************************************************************
* mchelp: displays instrument executable help with possible options
*******************************************************************************/
static void
mchelp(char *pgmname)
{
  int i;

  fprintf(stderr, "%s (%s) instrument simulation, generated with " MCCODE_STRING " (" MCCODE_DATE ")\n", mcinstrument_name, mcinstrument_source);
  fprintf(stderr, "Usage: %s [options] [parm=value ...]\n", pgmname);
  fprintf(stderr,
"Options are:\n"
"  -s SEED   --seed=SEED      Set random seed (must be != 0)\n"
"  -n COUNT  --ncount=COUNT   Set number of " MCCODE_PARTICLE "s to simulate.\n"
"  -d DIR    --dir=DIR        Put all data files in directory DIR.\n"
"  -t        --trace          Enable trace of " MCCODE_PARTICLE "s through instrument.\n"
"  -g        --gravitation    Enable gravitation for all trajectories.\n"
"  --no-output-files          Do not write any data files.\n"
"  -h        --help           Show this help message.\n"
"  -i        --info           Detailed instrument information.\n"
"  --format=FORMAT            Output data files using FORMAT="
   FLAVOR_UPPER
#ifdef USE_NEXUS
   " NEXUS"
#endif
"\n\n"
);
#ifdef USE_MPI
  fprintf(stderr,
  "This instrument has been compiled with MPI support.\n  Use 'mpirun %s [options] [parm=value ...]'.\n", pgmname);
#endif
  if(mcnumipar > 0)
  {
    fprintf(stderr, "Instrument parameters are:\n");
    for(i = 0; i < mcnumipar; i++)
      if (mcinputtable[i].val && strlen(mcinputtable[i].val))
        fprintf(stderr, "  %-16s(%s) [default='%s']\n", mcinputtable[i].name,
        (*mcinputtypes[mcinputtable[i].type].parminfo)(mcinputtable[i].name),
        mcinputtable[i].val);
      else
        fprintf(stderr, "  %-16s(%s)\n", mcinputtable[i].name,
        (*mcinputtypes[mcinputtable[i].type].parminfo)(mcinputtable[i].name));
  }

#ifndef NOSIGNALS
  fprintf(stderr, "Known signals are: "
#ifdef SIGUSR1
  "USR1 (status) "
#endif
#ifdef SIGUSR2
  "USR2 (save) "
#endif
#ifdef SIGBREAK
  "BREAK (save) "
#endif
#ifdef SIGTERM
  "TERM (save and exit)"
#endif
  "\n");
#endif /* !NOSIGNALS */
} /* mchelp */


/* mcshowhelp: show help and exit with 0 */
static void
mcshowhelp(char *pgmname)
{
  mchelp(pgmname);
  exit(0);
}

/* mcusage: display usage when error in input arguments and exit with 1 */
static void
mcusage(char *pgmname)
{
  fprintf(stderr, "Error: incorrect command line arguments\n");
  mchelp(pgmname);
  exit(1);
}

/* mcenabletrace: enable trace/mcdisplay or error if requires recompile */
static void
mcenabletrace(void)
{
 if(mctraceenabled)
  mcdotrace = 1;
 else
 {
   fprintf(stderr,
           "Error: trace not enabled (mcenabletrace)\n"
           "Please re-run the " MCCODE_NAME " compiler "
                   "with the --trace option, or rerun the\n"
           "C compiler with the MC_TRACE_ENABLED macro defined.\n");
   exit(1);
 }
}

/*******************************************************************************
* mcreadparams: request parameters from the prompt (or use default)
*******************************************************************************/
void
mcreadparams(void)
{
  int i,j,status;
  static char buf[CHAR_BUF_LENGTH];
  char *p;
  int len;

  MPI_MASTER(printf("Instrument parameters for %s (%s)\n",
                    mcinstrument_name, mcinstrument_source));

  for(i = 0; mcinputtable[i].name != 0; i++)
  {
    do
    {
      MPI_MASTER(
                 if (mcinputtable[i].val && strlen(mcinputtable[i].val))
                   printf("Set value of instrument parameter %s (%s) [default='%s']:\n",
                          mcinputtable[i].name,
                          (*mcinputtypes[mcinputtable[i].type].parminfo)
                          (mcinputtable[i].name), mcinputtable[i].val);
                 else
                   printf("Set value of instrument parameter %s (%s):\n",
                          mcinputtable[i].name,
                          (*mcinputtypes[mcinputtable[i].type].parminfo)
                          (mcinputtable[i].name));
                 fflush(stdout);
                 );
#ifdef USE_MPI
      if(mpi_node_rank == mpi_node_root)
        {
          p = fgets(buf, CHAR_BUF_LENGTH, stdin);
          if(p == NULL)
            {
              fprintf(stderr, "Error: empty input for paramater %s (mcreadparams)\n", mcinputtable[i].name);
              exit(1);
            }
        }
      else
        p = buf;
      MPI_Bcast(buf, CHAR_BUF_LENGTH, MPI_CHAR, mpi_node_root, MPI_COMM_WORLD);
#else /* !USE_MPI */
      p = fgets(buf, CHAR_BUF_LENGTH, stdin);
      if(p == NULL)
        {
          fprintf(stderr, "Error: empty input for paramater %s (mcreadparams)\n", mcinputtable[i].name);
          exit(1);
        }
#endif /* USE_MPI */
      len = strlen(buf);
      if (!len || (len == 1 && (buf[0] == '\n' || buf[0] == '\r')))
      {
        if (mcinputtable[i].val && strlen(mcinputtable[i].val)) {
          strncpy(buf, mcinputtable[i].val, CHAR_BUF_LENGTH);  /* use default value */
          len = strlen(buf);
        }
      }
      for(j = 0; j < 2; j++)
      {
        if(len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
        {
          len--;
          buf[len] = '\0';
        }
      }

      status = (*mcinputtypes[mcinputtable[i].type].getparm)
                   (buf, mcinputtable[i].par);
      if(!status)
      {
        (*mcinputtypes[mcinputtable[i].type].error)(mcinputtable[i].name, buf);
        if (!mcinputtable[i].val || strlen(mcinputtable[i].val)) {
          fprintf(stderr, "       Change %s default value in instrument definition.\n", mcinputtable[i].name);
          exit(1);
        }
      }
    } while(!status);
  }
} /* mcreadparams */

/*******************************************************************************
* mcparseoptions: parse command line arguments (options, parameters)
*******************************************************************************/
void
mcparseoptions(int argc, char *argv[])
{
  int i, j;
  char *p;
  int paramset = 0, *paramsetarray;
  char *usedir=NULL;

  /* Add one to mcnumipar to avoid allocating zero size memory block. */
  paramsetarray = (int*)malloc((mcnumipar + 1)*sizeof(*paramsetarray));
  if(paramsetarray == NULL)
  {
    fprintf(stderr, "Error: insufficient memory (mcparseoptions)\n");
    exit(1);
  }
  for(j = 0; j < mcnumipar; j++)
    {
      paramsetarray[j] = 0;
      if (mcinputtable[j].val != NULL && strlen(mcinputtable[j].val))
      {
        int  status;
        char buf[CHAR_BUF_LENGTH];
        strncpy(buf, mcinputtable[j].val, CHAR_BUF_LENGTH);
        status = (*mcinputtypes[mcinputtable[j].type].getparm)
                   (buf, mcinputtable[j].par);
        if(!status) fprintf(stderr, "Invalid '%s' default value %s in instrument definition (mcparseoptions)\n", mcinputtable[j].name, buf);
        else paramsetarray[j] = 1;
      } else {
        (*mcinputtypes[mcinputtable[j].type].getparm)
          (NULL, mcinputtable[j].par);
        paramsetarray[j] = 0;
      }
    }
  for(i = 1; i < argc; i++)
  {
    if(!strcmp("-s", argv[i]) && (i + 1) < argc)
      mcsetseed(argv[++i]);
    else if(!strncmp("-s", argv[i], 2))
      mcsetseed(&argv[i][2]);
    else if(!strcmp("--seed", argv[i]) && (i + 1) < argc)
      mcsetseed(argv[++i]);
    else if(!strncmp("--seed=", argv[i], 7))
      mcsetseed(&argv[i][7]);
    else if(!strcmp("-n", argv[i]) && (i + 1) < argc)
      mcsetn_arg(argv[++i]);
    else if(!strncmp("-n", argv[i], 2))
      mcsetn_arg(&argv[i][2]);
    else if(!strcmp("--ncount", argv[i]) && (i + 1) < argc)
      mcsetn_arg(argv[++i]);
    else if(!strncmp("--ncount=", argv[i], 9))
      mcsetn_arg(&argv[i][9]);
    else if(!strcmp("-d", argv[i]) && (i + 1) < argc)
      usedir=argv[++i];  /* will create directory after parsing all arguments (end of this function) */
    else if(!strncmp("-d", argv[i], 2))
      usedir=&argv[i][2];
    else if(!strcmp("--dir", argv[i]) && (i + 1) < argc)
      usedir=argv[++i];
    else if(!strncmp("--dir=", argv[i], 6))
      usedir=&argv[i][6];
    else if(!strcmp("-h", argv[i]))
      mcshowhelp(argv[0]);
    else if(!strcmp("--help", argv[i]))
      mcshowhelp(argv[0]);
    else if(!strcmp("-i", argv[i])) {
      mcformat=FLAVOR_UPPER;
      mcinfo();
    }
    else if(!strcmp("--info", argv[i]))
      mcinfo();
    else if(!strcmp("-t", argv[i]))
      mcenabletrace();
    else if(!strcmp("--trace", argv[i]))
      mcenabletrace();
    else if(!strcmp("--gravitation", argv[i]))
      mcgravitation = 1;
    else if(!strcmp("-g", argv[i]))
      mcgravitation = 1;
    else if(!strncmp("--format=", argv[i], 9)) {
      mcformat=&argv[i][9];
    }
    else if(!strcmp("--format", argv[i]) && (i + 1) < argc) {
      mcformat=argv[++i];
    }
    else if(!strcmp("--no-output-files", argv[i]))
      mcdisable_output_files = 1;
    else if(argv[i][0] != '-' && (p = strchr(argv[i], '=')) != NULL)
    {
      *p++ = '\0';

      for(j = 0; j < mcnumipar; j++)
        if(!strcmp(mcinputtable[j].name, argv[i]))
        {
          int status;
          status = (*mcinputtypes[mcinputtable[j].type].getparm)(p,
                        mcinputtable[j].par);
          if(!status || !strlen(p))
          {
            (*mcinputtypes[mcinputtable[j].type].error)
              (mcinputtable[j].name, p);
            exit(1);
          }
          paramsetarray[j] = 1;
          paramset = 1;
          break;
        }
      if(j == mcnumipar)
      {                                /* Unrecognized parameter name */
        fprintf(stderr, "Error: unrecognized parameter %s (mcparseoptions)\n", argv[i]);
        exit(1);
      }
    }
    else if(argv[i][0] == '-') {
      fprintf(stderr, "Error: unrecognized option argument %s (mcparseoptions). Ignored.\n", argv[i++]);
    }
    else {
      fprintf(stderr, "Error: unrecognized argument %s (mcparseoptions). Aborting.\n", argv[i]);
      mcusage(argv[0]);
    }
  }
  if(!paramset)
    mcreadparams();                /* Prompt for parameters if not specified. */
  else
  {
    for(j = 0; j < mcnumipar; j++)
      if(!paramsetarray[j])
      {
        fprintf(stderr, "Error: Instrument parameter %s left unset (mcparseoptions)\n",
                mcinputtable[j].name);
        exit(1);
      }
  }
  free(paramsetarray);
#ifdef USE_MPI
  if (mcdotrace) mpi_node_count=1; /* disable threading when in trace mode */
#endif
  if (usedir && strlen(usedir) && !mcdisable_output_files) mcuse_dir(usedir);
} /* mcparseoptions */

#ifndef NOSIGNALS
mcstatic char  mcsig_message[256];


/*******************************************************************************
* sighandler: signal handler that makes simulation stop, and save results
*******************************************************************************/
void sighandler(int sig)
{
  /* MOD: E. Farhi, Sep 20th 2001: give more info */
  time_t t1, t0;
#define SIG_SAVE 0
#define SIG_TERM 1
#define SIG_STAT 2
#define SIG_ABRT 3

  printf("\n# " MCCODE_STRING ": [pid %i] Signal %i detected", getpid(), sig);
#ifdef USE_MPI
  printf(" [proc %i]", mpi_node_rank);
#endif
#if defined(SIGUSR1) && defined(SIGUSR2) && defined(SIGKILL)
  if (!strcmp(mcsig_message, "sighandler") && (sig != SIGUSR1) && (sig != SIGUSR2))
  {
    printf("\n# Fatal : unrecoverable loop ! Suicide (naughty boy).\n");
    kill(0, SIGKILL); /* kill myself if error occurs within sighandler: loops */
  }
#endif
  switch (sig) {
#ifdef SIGINT
    case SIGINT : printf(" SIGINT (interrupt from terminal, Ctrl-C)"); sig = SIG_TERM; break;
#endif
#ifdef SIGILL
    case SIGILL  : printf(" SIGILL (Illegal instruction)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGFPE
    case SIGFPE  : printf(" SIGFPE (Math Error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGSEGV
    case SIGSEGV : printf(" SIGSEGV (Mem Error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGTERM
    case SIGTERM : printf(" SIGTERM (Termination)"); sig = SIG_TERM; break;
#endif
#ifdef SIGABRT
    case SIGABRT : printf(" SIGABRT (Abort)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGQUIT
    case SIGQUIT : printf(" SIGQUIT (Quit from terminal)"); sig = SIG_TERM; break;
#endif
#ifdef SIGTRAP
    case SIGTRAP : printf(" SIGTRAP (Trace trap)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGPIPE
    case SIGPIPE : printf(" SIGPIPE (Broken pipe)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGUSR1
    case SIGUSR1 : printf(" SIGUSR1 (Display info)"); sig = SIG_STAT; break;
#endif
#ifdef SIGUSR2
    case SIGUSR2 : printf(" SIGUSR2 (Save simulation)"); sig = SIG_SAVE; break;
#endif
#ifdef SIGHUP
    case SIGHUP  : printf(" SIGHUP (Hangup/update)"); sig = SIG_SAVE; break;
#endif
#ifdef SIGBUS
    case SIGBUS  : printf(" SIGBUS (Bus error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGURG
    case SIGURG  : printf(" SIGURG (Urgent socket condition)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGBREAK
    case SIGBREAK: printf(" SIGBREAK (Break signal, Ctrl-Break)"); sig = SIG_SAVE; break;
#endif
    default : printf(" (look at signal list for signification)"); sig = SIG_ABRT; break;
  }
  printf("\n");
  printf("# Simulation: %s (%s) \n", mcinstrument_name, mcinstrument_source);
  printf("# Breakpoint: %s ", mcsig_message);
  if (strstr(mcsig_message, "Save") && (sig == SIG_SAVE))
    sig = SIG_STAT;
  SIG_MESSAGE("sighandler");
  if (mcget_ncount() == 0)
    printf("(0 %%)\n" );
  else
  {
    printf("%.2f %% (%10.1f/%10.1f)\n", 100.0*mcget_run_num()/mcget_ncount(), 1.0*mcget_run_num(), 1.0*mcget_ncount());
  }
  t0 = (time_t)mcstartdate;
  t1 = time(NULL);
  printf("# Date:      %s", ctime(&t1));
  printf("# Started:   %s", ctime(&t0));

  if (sig == SIG_STAT)
  {
    printf("# " MCCODE_STRING ": Resuming simulation (continue)\n");
    fflush(stdout);
    return;
  }
  else
  if (sig == SIG_SAVE)
  {
    printf("# " MCCODE_STRING ": Saving data and resume simulation (continue)\n");
    mcsave(NULL);
    fflush(stdout);
    return;
  }
  else
  if (sig == SIG_TERM)
  {
    printf("# " MCCODE_STRING ": Finishing simulation (save results and exit)\n");
    mcfinally();
    exit(0);
  }
  else
  {
    fflush(stdout);
    perror("# Last I/O Error");
    printf("# " MCCODE_STRING ": Simulation stop (abort).\n");
// This portion of the signal handling only works on UNIX
#if defined(__unix__) || defined(__APPLE__)
    signal(sig, SIG_DFL); /* force to use default sighandler now */
    kill(getpid(), sig);  /* and trigger it with the current signal */
#endif
    exit(-1);
  }
#undef SIG_SAVE
#undef SIG_TERM
#undef SIG_STAT
#undef SIG_ABRT

} /* sighandler */
#endif /* !NOSIGNALS */

/*******************************************************************************
* mccode_main: McCode main() function.
*******************************************************************************/
int mccode_main(int argc, char *argv[])
{
/*  double run_num = 0; */
  time_t  t;
#ifdef USE_MPI
  char mpi_node_name[MPI_MAX_PROCESSOR_NAME];
  int  mpi_node_name_len;
#endif /* USE_MPI */

#ifdef MAC
  argc = ccommand(&argv);
#endif

#ifdef USE_MPI
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_node_count); /* get number of nodes */
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_node_rank);
  MPI_Comm_set_name(MPI_COMM_WORLD, mcinstrument_name);
  MPI_Get_processor_name(mpi_node_name, &mpi_node_name_len);
#endif /* USE_MPI */

t = time(NULL);
mcseed = (long)t+(long)getpid();

#ifdef USE_MPI
/* *** print number of nodes *********************************************** */
  if (mpi_node_count > 1) {
    MPI_MASTER(
    printf("Simulation '%s' (%s): running on %i nodes (master is '%s', MPI version %i.%i).\n",
      mcinstrument_name, mcinstrument_source, mpi_node_count, mpi_node_name, MPI_VERSION, MPI_SUBVERSION);
    );
  }
#endif /* USE_MPI */
  
  mcstartdate = (long)t;  /* set start date before parsing options and creating sim file */

/* *** parse options ******************************************************* */
  SIG_MESSAGE("main (Start)");
  mcformat=getenv(FLAVOR_UPPER "_FORMAT") ?
           getenv(FLAVOR_UPPER "_FORMAT") : FLAVOR_UPPER;
  mcinstrument_exe = argv[0]; /* store the executable path */
  /* read simulation parameters and options */
  mcparseoptions(argc, argv); /* sets output dir and format */
  
#ifdef USE_MPI
  if (mpi_node_count > 1) {
    /* share the same seed, then adapt random seed for each node */
    MPI_Bcast(&mcseed, 1, MPI_LONG, 0, MPI_COMM_WORLD); /* root sends its seed to slaves */
    mcseed += mpi_node_rank; /* make sure we use different seeds per node */
  }
#endif
  srandom(mcseed);

/* *** install sig handler, but only once !! after parameters parsing ******* */
#ifndef NOSIGNALS
#ifdef SIGQUIT
  if (signal( SIGQUIT ,sighandler) == SIG_IGN)
    signal( SIGQUIT,SIG_IGN);   /* quit (ASCII FS) */
#endif
#ifdef SIGABRT
  if (signal( SIGABRT ,sighandler) == SIG_IGN)
    signal( SIGABRT,SIG_IGN);   /* used by abort, replace SIGIOT in the future */
#endif
#ifdef SIGTERM
  if (signal( SIGTERM ,sighandler) == SIG_IGN)
    signal( SIGTERM,SIG_IGN);   /* software termination signal from kill */
#endif
#ifdef SIGUSR1
  if (signal( SIGUSR1 ,sighandler) == SIG_IGN)
    signal( SIGUSR1,SIG_IGN);   /* display simulation status */
#endif
#ifdef SIGUSR2
  if (signal( SIGUSR2 ,sighandler) == SIG_IGN)
    signal( SIGUSR2,SIG_IGN);
#endif
#ifdef SIGHUP
  if (signal( SIGHUP ,sighandler) == SIG_IGN)
    signal( SIGHUP,SIG_IGN);
#endif
#ifdef SIGILL
  if (signal( SIGILL ,sighandler) == SIG_IGN)
    signal( SIGILL,SIG_IGN);    /* illegal instruction (not reset when caught) */
#endif
#ifdef SIGFPE
  if (signal( SIGFPE ,sighandler) == SIG_IGN)
    signal( SIGSEGV,SIG_IGN);    /* floating point exception */
#endif
#ifdef SIGBUS
  if (signal( SIGBUS ,sighandler) == SIG_IGN)
    signal( SIGSEGV,SIG_IGN);    /* bus error */
#endif
#ifdef SIGSEGV
  if (signal( SIGSEGV ,sighandler) == SIG_IGN)
    signal( SIGSEGV,SIG_IGN);   /* segmentation violation */
#endif
#endif /* !NOSIGNALS */
  mcsiminfo_init(NULL); /* open SIM */
  SIG_MESSAGE("main (Init)");
  mcinit();
#ifndef NOSIGNALS
#ifdef SIGINT
  if (signal( SIGINT ,sighandler) == SIG_IGN)
    signal( SIGINT,SIG_IGN);    /* interrupt (rubout) only after INIT */
#endif
#endif /* !NOSIGNALS */

/* ================ main particle generation/propagation loop ================ */
#if defined (USE_MPI)
  /* sliced Ncount on each MPI node */
  mcncount = mpi_node_count > 1 ?
    floor(mcncount / mpi_node_count) :
    mcncount; /* number of rays per node */
#endif

/* main particle event loop */
while(mcrun_num < mcncount || mcrun_num < mcget_ncount())
  {
#ifndef NEUTRONICS
    mcgenstate();
#endif
    /* old init: mcsetstate(0, 0, 0, 0, 0, 1, 0, sx=0, sy=1, sz=0, 1); */
    mcraytrace();
    mcrun_num++;
  }

#ifdef USE_MPI
 /* merge run_num from MPI nodes */
  if (mpi_node_count > 1) {
  double mcrun_num_double = (double)mcrun_num;
  mc_MPI_Sum(&mcrun_num_double, 1);
  mcrun_num = (unsigned long long)mcrun_num_double;
  }
#endif

/* save/finally executed by master node/thread */
  mcfinally();

#ifdef USE_MPI
  MPI_Finalize();
#endif /* USE_MPI */

  return 0;
} /* mccode_main */

#ifdef NEUTRONICS
/*Main neutronics function steers the McStas calls, initializes parameters etc */
/* Only called in case NEUTRONICS = TRUE */
void neutronics_main_(float *inx, float *iny, float *inz, float *invx, float *invy, float *invz, float *intime, float *insx, float *insy, float *insz, float *inw, float *outx, float *outy, float *outz, float *outvx, float *outvy, float *outvz, float *outtime, float *outsx, float *outsy, float *outsz, float *outwgt)
{

  extern double mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz;
  extern double mcnt, mcnsx, mcnsy, mcnsz, mcnp;

  /* External code governs iteration - McStas is iterated once per call to neutronics_main. I.e. below counter must be initiancated for each call to neutronics_main*/
  mcrun_num=0;

  time_t t;
  t = (time_t)mcstartdate;
  mcstartdate = t;  /* set start date before parsing options and creating sim file */
  mcinit();

  /* *** parse options *** */
  SIG_MESSAGE("main (Start)");
  mcformat=getenv(FLAVOR_UPPER "_FORMAT") ?
           getenv(FLAVOR_UPPER "_FORMAT") : FLAVOR_UPPER;

  /* Set neutron state based on input from neutronics code */
  mcsetstate(*inx,*iny,*inz,*invx,*invy,*invz,*intime,*insx,*insy,*insz,*inw);

  /* main neutron event loop - runs only one iteration */

  //mcstas_raytrace(&mcncount); /* prior to McStas 1.12 */

  mcallowbackprop = 1; //avoid absorbtion from negative dt
  int argc=1;
  char *argv[0];
  int dummy = mccode_main(argc, argv);

  *outx =  mcnx;
  *outy =  mcny;
  *outz =  mcnz;
  *outvx =  mcnvx;
  *outvy =  mcnvy;
  *outvz =  mcnvz;
  *outtime =  mcnt;
  *outsx =  mcnsx;
  *outsy =  mcnsy;
  *outsz =  mcnsz;
  *outwgt =  mcnp;

  return;
} /* neutronics_main */

#endif /*NEUTRONICS*/

#endif /* !MCCODE_H */
/* End of file "mccode-r.c". */
/* End of file "mccode-r.c". */

#line 5083 "./ThALES_resolution_v2.c"

#line 1 "mcstas-r.c"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mcstas-r.c
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas X.Y
* Version: $Revision$
*
* Runtime system for McStas.
* Embedded within instrument in runtime mode.
*
* Usage: Automatically embbeded in the c code whenever required.
*
* $Id$
*
*******************************************************************************/

#ifndef MCSTAS_R_H
#include "mcstas-r.h"
#endif
#ifdef DANSE
#include "mcstas-globals.h"
#endif

/*******************************************************************************
* The I/O format definitions and functions
*******************************************************************************/

/*the magnet stack*/
#ifdef MC_POL_COMPAT
void (*mcMagnetPrecession) (double, double, double, double, double, double,
    double, double*, double*, double*, double, Coords, Rotation)=NULL;
Coords   mcMagnetPos;
Rotation mcMagnetRot;
double*  mcMagnetData                = NULL;
/* mcMagneticField(x, y, z, t, Bx, By, Bz) */
int (*mcMagneticField) (double, double, double, double,
    double*, double*, double*, void *) = NULL;
#endif

#ifndef MCSTAS_H

/*******************************************************************************
* mcstore_neutron: stores neutron coodinates into global array (per component)
*******************************************************************************/
void
mcstore_neutron(MCNUM *s, int index, double x, double y, double z,
               double vx, double vy, double vz, double t,
               double sx, double sy, double sz, double p)
{
    double *dptr = &s[11*index];
    *dptr++  = x;
    *dptr++  = y ;
    *dptr++  = z ;
    *dptr++  = vx;
    *dptr++  = vy;
    *dptr++  = vz;
    *dptr++  = t ;
    *dptr++  = sx;
    *dptr++  = sy;
    *dptr++  = sz;
    *dptr    = p ;
} /* mcstore_neutron */

/*******************************************************************************
* mcrestore_neutron: restores neutron coodinates from global array
*******************************************************************************/
void
mcrestore_neutron(MCNUM *s, int index, double *x, double *y, double *z,
               double *vx, double *vy, double *vz, double *t,
               double *sx, double *sy, double *sz, double *p)
{
    double *dptr = &s[11*index];
    *x  =  *dptr++;
    *y  =  *dptr++;
    *z  =  *dptr++;
    *vx =  *dptr++;
    *vy =  *dptr++;
    *vz =  *dptr++;
    *t  =  *dptr++;
    *sx =  *dptr++;
    *sy =  *dptr++;
    *sz =  *dptr++;
    *p  =  *dptr;
} /* mcrestore_neutron */

/*******************************************************************************
* mcsetstate: transfer parameters into global McStas variables 
*******************************************************************************/
void
mcsetstate(double x, double y, double z, double vx, double vy, double vz,
           double t, double sx, double sy, double sz, double p)
{
  extern double mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz;
  extern double mcnt, mcnsx, mcnsy, mcnsz, mcnp;

  mcnx = x;
  mcny = y;
  mcnz = z;
  mcnvx = vx;
  mcnvy = vy;
  mcnvz = vz;
  mcnt = t;
  mcnsx = sx;
  mcnsy = sy;
  mcnsz = sz;
  mcnp = p;
} /* mcsetstate */

/*******************************************************************************
* mcgenstate: set default neutron parameters 
*******************************************************************************/
void
mcgenstate(void)
{
  mcsetstate(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  /* old initialisation: mcsetstate(0, 0, 0, 0, 0, 1, 0, sx=0, sy=1, sz=0, 1); */
}

/* intersection routines ==================================================== */

/*******************************************************************************
* inside_rectangle: Check if (x,y) is inside rectangle (xwidth, yheight) 
* return 0 if outside and 1 if inside 
*******************************************************************************/
int inside_rectangle(double x, double y, double xwidth, double yheight)
{
  if (x>-xwidth/2 && x<xwidth/2 && y>-yheight/2 && y<yheight/2)
    return 1;
  else
    return 0;
}

/*******************************************************************************
 * box_intersect: compute time intersection with a box
 * returns 0 when no intersection is found
 *      or 1 in case of intersection with resulting times dt_in and dt_out
 * This function written by Stine Nyborg, 1999. 
 *******************************************************************************/
int box_intersect(double *dt_in, double *dt_out,
                  double x, double y, double z,
                  double vx, double vy, double vz,
                  double dx, double dy, double dz)
{
  double x_in, y_in, z_in, tt, t[6], a, b;
  int i, count, s;

      /* Calculate intersection time for each of the six box surface planes
       *  If the box surface plane is not hit, the result is zero.*/

  if(vx != 0)
   {
    tt = -(dx/2 + x)/vx;
    y_in = y + tt*vy;
    z_in = z + tt*vz;
    if( y_in > -dy/2 && y_in < dy/2 && z_in > -dz/2 && z_in < dz/2)
      t[0] = tt;
    else
      t[0] = 0;

    tt = (dx/2 - x)/vx;
    y_in = y + tt*vy;
    z_in = z + tt*vz;
    if( y_in > -dy/2 && y_in < dy/2 && z_in > -dz/2 && z_in < dz/2)
      t[1] = tt;
    else
      t[1] = 0;
   }
  else
    t[0] = t[1] = 0;

  if(vy != 0)
   {
    tt = -(dy/2 + y)/vy;
    x_in = x + tt*vx;
    z_in = z + tt*vz;
    if( x_in > -dx/2 && x_in < dx/2 && z_in > -dz/2 && z_in < dz/2)
      t[2] = tt;
    else
      t[2] = 0;

    tt = (dy/2 - y)/vy;
    x_in = x + tt*vx;
    z_in = z + tt*vz;
    if( x_in > -dx/2 && x_in < dx/2 && z_in > -dz/2 && z_in < dz/2)
      t[3] = tt;
    else
      t[3] = 0;
   }
  else
    t[2] = t[3] = 0;

  if(vz != 0)
   {
    tt = -(dz/2 + z)/vz;
    x_in = x + tt*vx;
    y_in = y + tt*vy;
    if( x_in > -dx/2 && x_in < dx/2 && y_in > -dy/2 && y_in < dy/2)
      t[4] = tt;
    else
      t[4] = 0;

    tt = (dz/2 - z)/vz;
    x_in = x + tt*vx;
    y_in = y + tt*vy;
    if( x_in > -dx/2 && x_in < dx/2 && y_in > -dy/2 && y_in < dy/2)
      t[5] = tt;
    else
      t[5] = 0;
   }
  else
    t[4] = t[5] = 0;

  /* The intersection is evaluated and *dt_in and *dt_out are assigned */

  a = b = s = 0;
  count = 0;

  for( i = 0; i < 6; i = i + 1 )
    if( t[i] == 0 )
      s = s+1;
    else if( count == 0 )
    {
      a = t[i];
      count = 1;
    }
    else
    {
      b = t[i];
      count = 2;
    }

  if ( a == 0 && b == 0 )
    return 0;
  else if( a < b )
  {
    *dt_in = a;
    *dt_out = b;
    return 1;
  }
  else
  {
    *dt_in = b;
    *dt_out = a;
    return 1;
  }

} /* box_intersect */

/*******************************************************************************
 * cylinder_intersect: compute intersection with a cylinder
 * returns 0 when no intersection is found
 *      or 2/4/8/16 bits depending on intersection,
 *     and resulting times t0 and t1
 * Written by: EM,NB,ABA 4.2.98 
  *******************************************************************************/
int
cylinder_intersect(double *t0, double *t1, double x, double y, double z,
                   double vx, double vy, double vz, double r, double h)
{
  double D, t_in, t_out, y_in, y_out;
  int ret=1;

  D = (2*vx*x + 2*vz*z)*(2*vx*x + 2*vz*z)
    - 4*(vx*vx + vz*vz)*(x*x + z*z - r*r);

  if (D>=0)
  {
    if (vz*vz + vx*vx) {
      t_in  = (-(2*vz*z + 2*vx*x) - sqrt(D))/(2*(vz*vz + vx*vx));
      t_out = (-(2*vz*z + 2*vx*x) + sqrt(D))/(2*(vz*vz + vx*vx));
    } else if (vy) { /* trajectory parallel to cylinder axis */
      t_in = (-h/2-y)/vy;
      t_out = (h/2-y)/vy;
      if (t_in>t_out){
        double tmp=t_in;
        t_in=t_out;t_out=tmp;
      }
    } else return 0;
    y_in = vy*t_in + y;
    y_out =vy*t_out + y;

    if ( (y_in > h/2 && y_out > h/2) || (y_in < -h/2 && y_out < -h/2) )
      return 0;
    else
    {
      if (y_in > h/2)
        { t_in = ((h/2)-y)/vy; ret += 2; }
      else if (y_in < -h/2)
        { t_in = ((-h/2)-y)/vy; ret += 4; }
      if (y_out > h/2)
        { t_out = ((h/2)-y)/vy; ret += 8; }
      else if (y_out < -h/2)
        { t_out = ((-h/2)-y)/vy; ret += 16; }
    }
    *t0 = t_in;
    *t1 = t_out;
    return ret;
  }
  else
  {
    *t0 = *t1 = 0;
    return 0;
  }
} /* cylinder_intersect */


/*******************************************************************************
 * sphere_intersect: Calculate intersection between a line and a sphere.
 * returns 0 when no intersection is found
 *      or 1 in case of intersection with resulting times t0 and t1 
 *******************************************************************************/
int
sphere_intersect(double *t0, double *t1, double x, double y, double z,
                 double vx, double vy, double vz, double r)
{
  double A, B, C, D, v;

  v = sqrt(vx*vx + vy*vy + vz*vz);
  A = v*v;
  B = 2*(x*vx + y*vy + z*vz);
  C = x*x + y*y + z*z - r*r;
  D = B*B - 4*A*C;
  if(D < 0)
    return 0;
  D = sqrt(D);
  *t0 = (-B - D) / (2*A);
  *t1 = (-B + D) / (2*A);
  return 1;
} /* sphere_intersect */

/*******************************************************************************
 * plane_intersect: Calculate intersection between a plane and a line.
 * returns 0 when no intersection is found (i.e. line is parallel to the plane)
 * returns 1 or -1 when intersection time is positive and negative respectively
 *******************************************************************************/
int
plane_intersect(double *t, double x, double y, double z,
                 double vx, double vy, double vz, double nx, double ny, double nz, double wx, double wy, double wz)
{
  double s;
  if (fabs(s=scalar_prod(nx,ny,nz,vx,vy,vz))<FLT_EPSILON) return 0;
  *t = - scalar_prod(nx,ny,nz,x-wx,y-wy,z-wz)/s;
  if (*t<0) return -1;
  else return 1;
} /* plane_intersect */

#endif /* !MCSTAS_H */
/* End of file "mcstas-r.c". */

#line 5443 "./ThALES_resolution_v2.c"
#ifdef MC_TRACE_ENABLED
int mctraceenabled = 1;
#else
int mctraceenabled = 0;
#endif
#define MCSTAS "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../"
int mcdefaultmain = 1;
char mcinstrument_name[] = "ThALES_double_peak10";
char mcinstrument_source[] = "ThALES_resolution_v2.instr";
char *mcinstrument_exe=NULL; /* will be set to argv[0] in main */
int main(int argc, char *argv[]){return mccode_main(argc, argv);}
void mcinit(void);
void mcraytrace(void);
void mcsave(FILE *);
void mcfinally(void);
void mcdisplay(void);

/* Shared user declarations for all components 'Source_gen'. */
#line 140 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2002, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/read_table-lib.h
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas 1.6
* Version: $Revision$
*
* This file is to be imported by components that may read data from table files
* It handles some shared functions.
*
* This library may be used directly as an external library. It has no dependency
*
* Usage: within SHARE
* %include "read_table-lib"
*
*******************************************************************************/

#ifndef READ_TABLE_LIB_H
#define READ_TABLE_LIB_H "$Revision$"

#define READ_TABLE_STEPTOL  0.04 /* tolerancy for constant step approx */

#ifndef MC_PATHSEP_C
#ifdef WIN32
#define MC_PATHSEP_C '\\'
#define MC_PATHSEP_S "\\"
#else  /* !WIN32 */
#ifdef MAC
#define MC_PATHSEP_C ':'
#define MC_PATHSEP_S ":"
#else  /* !MAC */
#define MC_PATHSEP_C '/'
#define MC_PATHSEP_S "/"
#endif /* !MAC */
#endif /* !WIN32 */
#endif /* !MC_PATHSEP_C */

#ifndef MCSTAS
#ifdef WIN32
#define MCSTAS "C:\\mcstas\\lib"
#else  /* !WIN32 */
#ifdef MAC
#define MCSTAS ":mcstas:lib" /* ToDo: What to put here? */
#else  /* !MAC */
#define MCSTAS "/usr/local/lib/mcstas"
#endif /* !MAC */
#endif /* !WIN32 */
#endif /* !MCSTAS */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

  typedef struct struct_table
  {
    char    filename[1024];
    long    filesize;
    char   *header;  /* text header, e.g. comments */
    double *data;    /* vector { x[0], y[0], ... x[n-1], y[n-1]... } */
    double  min_x;   /* min value of first column */
    double  max_x;   /* max value of first column */
    double  step_x;  /* minimal step value of first column */
    long    rows;    /* number of rows in matrix block */
    long    columns; /* number of columns in matrix block */

    long    begin;   /* start fseek index of block */
    long    end;     /* stop  fseek index of block */
    long    block_number;  /* block index. 0 is catenation of all */
    long    array_length;  /* number of elements in the t_Table array */
    char    monotonic;     /* true when 1st column/vector data is monotonic */
    char    constantstep;  /* true when 1st column/vector data has constant step */
    char    method[32];    /* interpolation method: nearest, linear */
  } t_Table;

/*maximum number of rows to rebin a table = 1M*/
enum { mcread_table_rebin_maxsize = 1000000 };

typedef struct t_Read_table_file_item {
    int ref_count;
    t_Table *table_ref;
} t_Read_table_file_item;

typedef enum enum_Read_table_file_actions {STORE,FIND,GC}  t_Read_table_file_actions;

/* read_table-lib function prototypes */
/* ========================================================================= */

/* 'public' functions */
long     Table_Read              (t_Table *Table, char *File, long block_number);
long     Table_Read_Offset       (t_Table *Table, char *File, long block_number,
                                  long *offset, long max_lines);
long     Table_Read_Offset_Binary(t_Table *Table, char *File, char *Type,
                                  long *Offset, long Rows, long Columns);
long     Table_Rebin(t_Table *Table); /* rebin table with regular 1st column and interpolate all columns 2:end */
long     Table_Info (t_Table Table);
double   Table_Index(t_Table Table,   long i, long j); /* get indexed value */
double   Table_Value(t_Table Table, double X, long j); /* search X in 1st column and return interpolated value in j-column */
t_Table *Table_Read_Array(char *File, long *blocks);
void     Table_Free_Array(t_Table *Table);
long     Table_Info_Array(t_Table *Table);
int      Table_SetElement(t_Table *Table, long i, long j, double value);
long     Table_Init(t_Table *Table, long rows, long columns); /* create a Table */
double   Table_Value2d(t_Table Table, double X, double Y);    /* same as Table_Index with non-integer indices and 2d interpolation */
MCDETECTOR Table_Write(t_Table Table, char*file, char*xl, char*yl, 
           double x1, double x2, double y1, double y2); /* write Table to disk */
void * Table_File_List_Handler(t_Read_table_file_actions action, void *item, void *item_modifier);
t_Table *Table_File_List_find(char *name, int block, int offset);
int Table_File_List_gc(t_Table *tab);
void *Table_File_List_store(t_Table *tab);

#define Table_ParseHeader(header, ...) \
  Table_ParseHeader_backend(header,__VA_ARGS__,NULL);

char **Table_ParseHeader_backend(char *header, ...);

/* private functions */
void Table_Free(t_Table *Table);
long Table_Read_Handle(t_Table *Table, FILE *fid, long block_number, long max_lines, char *name);
static void Table_Stat(t_Table *Table);
double Table_Interp1d(double x, double x1, double y1, double x2, double y2);
double Table_Interp1d_nearest(double x, double x1, double y1, double x2, double y2);
double Table_Interp2d(double x, double y, double x1, double y1, double x2, double y2,
double z11, double z12, double z21, double z22);

#endif

/* end of read_table-lib.h */
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/read_table-lib.c
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas CVS_090504
* Version: $Revision: 5052 $
*
* This file is to be imported by components that may read data from table files
* It handles some shared functions. Embedded within instrument in runtime mode.
*
* Usage: within SHARE
* %include "read_table-lib"
*
*******************************************************************************/

#ifndef READ_TABLE_LIB_H
#include "read_table-lib.h"
#endif


/*******************************************************************************
 * void *Table_File_List_Handler(action, item, item_modifier)
 *   ACTION: handle file entries in the read_table-lib file list. If a file is read - it is supposed to be
 *   stored in a list such that we can avoid reading the same file many times.
 *   input  action: FIND, STORE, GC. check if file exists in the list, store an item in the list, or check if it can be garbage collected.
 *   input item: depends on the action.
 *    FIND)  item is a filename, and item_modifier is the block number
 *    STORE) item is the Table to store - item_modifier is ignored
 *    GC)    item is the Table to check. If it has a ref_count >1 then this is simply decremented.
 *   return  depends on the action
 *    FIND)  return a reference to a table+ref_count item if found - NULL otherwise. I.e. NULL means the file has not been read before and must be read again.
 *    STORE) return NULL always
 *    GC)    return NULL if no garbage collection is needed, return an adress to the t_Table which should be garbage collected. 0x1 is returned if
 *           the item is not found in the list
*******************************************************************************/
void * Table_File_List_Handler(t_Read_table_file_actions action, void *item, void *item_modifier){

    /* logic here is Read_Table should include a call to FIND. If found the return value should just be used as
     * if the table had been read from disk. If not found then read the table and STORE.
     * Table_Free should include a call to GC. If this returns non-NULL then we should proceed with freeing the memory
     * associated with the table item - otherwise only decrement the reference counter since there are more references
     * that may need it.*/

    static t_Read_table_file_item read_table_file_list[1024];  
    static int read_table_file_count=0;

    t_Read_table_file_item *tr;
    switch(action){
        case FIND:
            /*interpret data item as a filename, if it is found return a pointer to the table and increment refcount.
             * if not found return the item itself*/
            tr=read_table_file_list;
            while ( tr->table_ref!=NULL ){
                int i=*((int*) item_modifier);
                int j=*( ((int*) item_modifier)+1);
                if ( !strcmp(tr->table_ref->filename,(char *) item) &&
                        tr->table_ref->block_number==i && tr->table_ref->begin==j ){
                    tr->ref_count++;
                    return (void *) tr;
                }
                tr++;
            }
            return NULL;
        case STORE:
            /*find an available slot and store references to table there*/
            tr=&(read_table_file_list[read_table_file_count++]);
            tr->table_ref = ((t_Table *) item);
            tr->ref_count++;
            return NULL;
        case GC:
            /* Should this item be garbage collected (freed) - if so scratch the entry and return the address of the item - 
             * else decrement ref_count and return NULL.
             * A non-NULL return expects the item to actually be freed afterwards.*/
            tr=read_table_file_list;
            while ( tr->table_ref!=NULL ){
                if ( tr->table_ref->data ==((t_Table *)item)->data && 
                        tr->table_ref->block_number == ((t_Table *)item)->block_number){
                    /*matching item found*/
                    if (tr->ref_count>1){
                        /*the item is found and no garbage collection needed*/
                        tr->ref_count--;
                        return NULL;
                    }else{
                        /* The item is found and the reference counter is 1.
                         * This means we should garbage collect. Move remaining list items up one slot,
                         * and return the table for garbage collection by caller*/
                        while (tr->table_ref!=NULL){
                            *tr=*(tr+1);
                            tr++;
                        }
                        read_table_file_count--;
                        return (t_Table *) item;
                    }
                }
                tr++;
            }
            /* item not found, and so should be garbage collected. This could be the case if freeing a
             * Table that has been constructed from code - not read from file. Return 0x1 to flag it for
             * collection.*/
            return (void *) 0x1 ;
    }
}

/* Access functions to the handler*/

/********************************************
 * t_Table *Table_File_List_find(char *name, int block, int offset)
 * input name: filename to search for in the file list
 * input block: data block in the file as each file may contain more than 1 data block.
 * return a ref. to a table if it is found (you may use this pointer and skip reading the file), NULL otherwise (i.e. go ahead and read the file)
*********************************************/
t_Table *Table_File_List_find(char *name, int block, int offset){
    int vars[2]={block,offset};
    t_Read_table_file_item *item = Table_File_List_Handler(FIND,name, vars);
    if (item == NULL){
        return NULL;
    }else{
        return item->table_ref;
    }
}
/********************************************
 * int Table_File_List_gc(t_Table *tab)
 * input tab: the table to check for references.
 * return 0: no garbage collection needed
 *        1: Table's data and header (at least) should be freed.
*********************************************/
int Table_File_List_gc(t_Table *tab){
    void *rval=Table_File_List_Handler(GC,tab,0);
    if (rval==NULL) return 0;
    else return 1;
}


/*****************************************************************************
 * void *Table_File_List_store(t_Table *tab)
 * input tab: pointer to table to store.
 * return None. 
*******************************************************************************/
void *Table_File_List_store(t_Table *tab){
    return Table_File_List_Handler(STORE,tab,0);
}


/*******************************************************************************
* FILE *Open_File(char *name, char *Mode, char *path)
*   ACTION: search for a file and open it. Optionally return the opened path.
*   input   name:  file name from which table should be extracted
*           mode: "r", "w", "a" or any valid fopen mode
*           path:  NULL or a pointer to at least 1024 allocated chars
*   return  initialized file handle or NULL in case of error
*******************************************************************************/

  FILE *Open_File(char *File, const char *Mode, char *Path)
  {
    char path[1024];
    FILE *hfile = NULL;
    
    if (!File || File[0]=='\0')                     return(NULL);
    if (!strcmp(File,"NULL") || !strcmp(File,"0"))  return(NULL);
    
    /* search in current or full path */
    strncpy(path, File, 1024);
    hfile = fopen(path, Mode);
    if(!hfile)
    {
      char dir[1024];

      if (!hfile && mcinstrument_source[0] != '\0' && strlen(mcinstrument_source)) /* search in instrument source location */
      {
        char *path_pos   = NULL;
        /* extract path: searches for last file separator */
        path_pos    = strrchr(mcinstrument_source, MC_PATHSEP_C);  /* last PATHSEP */
        if (path_pos) {
          long path_length = path_pos +1 - mcinstrument_source;  /* from start to path+sep */
          if (path_length) {
            strncpy(dir, mcinstrument_source, path_length);
            dir[path_length] = '\0';
            snprintf(path, 1024, "%s%c%s", dir, MC_PATHSEP_C, File);
            hfile = fopen(path, Mode);
          }
        }
      }
      if (!hfile && mcinstrument_exe[0] != '\0' && strlen(mcinstrument_exe)) /* search in PWD instrument executable location */
      {
        char *path_pos   = NULL;
        /* extract path: searches for last file separator */
        path_pos    = strrchr(mcinstrument_exe, MC_PATHSEP_C);  /* last PATHSEP */
        if (path_pos) {
          long path_length = path_pos +1 - mcinstrument_exe;  /* from start to path+sep */
          if (path_length) {
            strncpy(dir, mcinstrument_exe, path_length);
            dir[path_length] = '\0';
            snprintf(path, 1024, "%s%c%s", dir, MC_PATHSEP_C, File);
            hfile = fopen(path, Mode);
          }
        }
      }
      if (!hfile) /* search in HOME or . */
      {
        strcpy(dir, getenv("HOME") ? getenv("HOME") : ".");
        snprintf(path, 1024, "%s%c%s", dir, MC_PATHSEP_C, File);
        hfile = fopen(path, Mode);
      }
      if (!hfile) /* search in MCSTAS/data */
      {
        strcpy(dir, getenv(FLAVOR_UPPER) ? getenv(FLAVOR_UPPER) : MCSTAS);
        snprintf(path, 1024, "%s%c%s%c%s", dir, MC_PATHSEP_C, "data", MC_PATHSEP_C, File);
        hfile = fopen(path, Mode);
      }
      if (!hfile) /* search in MVCSTAS/contrib */
      {
        strcpy(dir, getenv(FLAVOR_UPPER) ? getenv(FLAVOR_UPPER) : MCSTAS);
        snprintf(path, 1024, "%s%c%s%c%s", dir, MC_PATHSEP_C, "contrib", MC_PATHSEP_C, File);
        hfile = fopen(path, Mode);
      }
      if(!hfile)
      {
        fprintf(stderr, "Error: Could not open input file '%s' (Open_File)\n", File);
        return (NULL);
      }
    }
    if (Path) strncpy(Path, path, 1024);
    return(hfile);
  } /* end Open_File */

/*******************************************************************************
* long Read_Table(t_Table *Table, char *name, int block_number)
*   ACTION: read a single Table from a text file
*   input   Table: pointer to a t_Table structure
*           name:  file name from which table should be extracted
*           block_number: if the file does contain more than one
*                 data block, then indicates which one to get (from index 1)
*                 a 0 value means append/catenate all
*   return  initialized single Table t_Table structure containing data, header, ...
*           number of read elements (-1: error, 0:header only)
* The routine stores any line starting with '#', '%' and ';' into the header
* File is opened, read and closed
* Other lines are interpreted as numerical data, and stored.
* Data block should be a rectangular matrix or vector.
* Data block may be rebinned with Table_Rebin (also sort in ascending order)
*******************************************************************************/
  long Table_Read(t_Table *Table, char *File, long block_number)
  { /* reads all or a single data block from 'file' and returns a Table structure  */
    return(Table_Read_Offset(Table, File, block_number, NULL, 0));
  } /* end Table_Read */

/*******************************************************************************
* long Table_Read_Offset(t_Table *Table, char *name, int block_number, long *offset
*                        long max_rows)
*   ACTION: read a single Table from a text file, starting at offset
*     Same as Table_Read(..) except:
*   input   offset:    pointer to an offset (*offset should be 0 at start)
*           max_rows: max number of data rows to read from file (0 means all)
*   return  initialized single Table t_Table structure containing data, header, ...
*           number of read elements (-1: error, 0:header only)
*           updated *offset position (where end of reading occured)
*******************************************************************************/
  long Table_Read_Offset(t_Table *Table, char *File,
                         long block_number, long *offset,
                         long max_rows)
  { /* reads all/a data block in 'file' and returns a Table structure  */
    FILE *hfile;
    long  nelements=0;
    long  begin=0;
    long  filesize=0;
    char  name[1024];
    char  path[1024];
    struct stat stfile;

    /*Need to be able to store the pointer*/
    if (!Table) return(-1);
    
    //if (offset && *offset) snprintf(name, 1024, "%s@%li", File, *offset);
    //else                   
    strncpy(name, File, 1024);
    if(offset && *offset){
        begin=*offset;
    }
    /* Check if the table has already been read from file.
     * If so just reuse the table, if not (this is flagged by returning NULL
     * set up a new table and read the data into it */
    t_Table *tab_p= Table_File_List_find(name,block_number,begin);
    if ( tab_p!=NULL ){
        /*table was found in the Table_File_List*/
        // printf("Reusing input file '%s' (Table_Read_Offset)\n", name);
        *Table=*tab_p;
        return Table->rows*Table->columns;
    }

    /* open the file */
    hfile = Open_File(File, "r", path);
    if (!hfile) return(-1);
    else {
      MPI_MASTER(
      printf("Opening input file '%s' (Table_Read_Offset)\n", path);
      );
    }
    
    /* read file state */
    stat(path,&stfile); filesize = stfile.st_size;
    if (offset && *offset) fseek(hfile, *offset, SEEK_SET);
    begin     = ftell(hfile);
    
    Table_Init(Table, 0, 0);

    /* read file content and set the Table */
    nelements = Table_Read_Handle(Table, hfile, block_number, max_rows, name);
    Table->begin = begin;
    Table->end   = ftell(hfile);
    Table->filesize = (filesize>0 ? filesize : 0);
    Table_Stat(Table);
    
    Table_File_List_store(Table);

    if (offset) *offset=Table->end;
    fclose(hfile);
    return(nelements);

  } /* end Table_Read_Offset */

/*******************************************************************************
* long Table_Read_Offset_Binary(t_Table *Table, char *File, char *type,
*                               long *offset, long rows, long columns)
*   ACTION: read a single Table from a binary file, starting at offset
*     Same as Table_Read_Offset(..) except that it handles binary files.
*   input   type: may be "float"/NULL or "double"
*           offset: pointer to an offset (*offset should be 0 at start)
*           rows   : number of rows (0 means read all)
*           columns: number of columns
*   return  initialized single Table t_Table structure containing data, header, ...
*           number of read elements (-1: error, 0:header only)
*           updated *offset position (where end of reading occured)
*******************************************************************************/
  long Table_Read_Offset_Binary(t_Table *Table, char *File, char *type,
                                long *offset, long rows, long columns)
  { /* reads all/a data block in binary 'file' and returns a Table structure  */
    long    nelements, sizeofelement;
    long    filesize;
    FILE   *hfile;
    char    path[1024];
    struct stat stfile;
    double *data;
    long    i;
    long    begin;

    if (!Table) return(-1);

    Table_Init(Table, 0, 0);
    
    /* open the file */
    hfile = Open_File(File, "r", path);
    if (!hfile) return(-1);
    else {
      MPI_MASTER(
      printf("Opening input file '%s' (Table_Read, Binary)\n", path);
      );
    }
    
    /* read file state */
    stat(File,&stfile);
    filesize = stfile.st_size;
    Table->filesize=filesize;
    
    /* read file content */
    if (type && !strcmp(type,"double")) sizeofelement = sizeof(double);
    else  sizeofelement = sizeof(float);
    if (offset && *offset) fseek(hfile, *offset, SEEK_SET);
    begin     = ftell(hfile);
    if (rows && filesize > sizeofelement*columns*rows)
      nelements = columns*rows;
    else nelements = (long)(filesize/sizeofelement);
    if (!nelements || filesize <= *offset) return(0);
    data    = (double*)malloc(nelements*sizeofelement);
    if (!data) {
      fprintf(stderr,"Error: allocating %ld elements for %s file '%s'. Too big (Table_Read_Offset_Binary).\n", nelements, type, File);
      exit(-1);
    }
    nelements = fread(data, sizeofelement, nelements, hfile);

    if (!data || !nelements)
    {
      fprintf(stderr,"Error: reading %ld elements from %s file '%s' (Table_Read_Offset_Binary)\n", nelements, type, File);
      exit(-1);
    }
    Table->begin   = begin;
    Table->end     = ftell(hfile);
    if (offset) *offset=Table->end;
    fclose(hfile);
    data = (double*)realloc(data, (double)nelements*sizeofelement);
    /* copy file data into Table */
    if (type && !strcmp(type,"double")) Table->data = data;
    else {
      float  *s;
      double *dataf;
      s     = (float*)data;
      dataf = (double*)malloc(sizeof(double)*nelements);
      for (i=0; i<nelements; i++)
        dataf[i]=s[i];
      free(data);
      Table->data = dataf;
    }
    strncpy(Table->filename, File, 1024);
    Table->rows    = nelements/columns;
    Table->columns = columns;
    Table->array_length = 1;
    Table->block_number = 1;

    Table_Stat(Table);

    return(nelements);
  } /* end Table_Read_Offset_Binary */

/*******************************************************************************
* long Table_Read_Handle(t_Table *Table, FILE *fid, int block_number, long max_rows, char *name)
*   ACTION: read a single Table from a text file handle (private)
*   input   Table:pointer to a t_Table structure
*           fid:  pointer to FILE handle
*           block_number: if the file does contain more than one
*                 data block, then indicates which one to get (from index 1)
*                 a 0 value means append/catenate all
*           max_rows: if non 0, only reads that number of lines
*   return  initialized single Table t_Table structure containing data, header, ...
*           modified Table t_Table structure containing data, header, ...
*           number of read elements (-1: error, 0:header only)
* The routine stores any line starting with '#', '%' and ';' into the header
* Other lines are interpreted as numerical data, and stored.
* Data block should be a rectangular matrix or vector.
* Data block may be rebined with Table_Rebin (also sort in ascending order)
*******************************************************************************/
  long Table_Read_Handle(t_Table *Table, FILE *hfile,
                         long block_number, long max_rows, char *name)
  { /* reads all/a data block from 'file' handle and returns a Table structure  */
    double *Data;
    char *Header              = NULL;
    long  malloc_size         = CHAR_BUF_LENGTH;
    long  malloc_size_h       = 4096;
    long  Rows = 0,   Columns = 0;
    long  count_in_array      = 0;
    long  count_in_header     = 0;
    long  block_Current_index = 0;
    char  flag_End_row_loop   = 0;

    if (!Table) return(-1);
    Table_Init(Table, 0, 0);
    if (name && name[0]!='\0') strncpy(Table->filename, name, 1024);

    if(!hfile) {
       fprintf(stderr, "Error: File handle is NULL (Table_Read_Handle).\n");
       return (-1);
    }
    Header = (char*)  calloc(malloc_size_h, sizeof(char));
    Data   = (double*)calloc(malloc_size,   sizeof(double));
    if ((Header == NULL) || (Data == NULL)) {
       fprintf(stderr, "Error: Could not allocate Table and Header (Table_Read_Handle).\n");
       return (-1);
    }

    int flag_In_array = 0;
    do { /* while (!flag_End_row_loop) */
      char  line[1024*CHAR_BUF_LENGTH];
      long  back_pos=0;   /* ftell start of line */

      back_pos = ftell(hfile);
      if (fgets(line, 1024*CHAR_BUF_LENGTH, hfile) != NULL) { /* analyse line */
        /* first skip blank and tabulation characters */
        int i = strspn(line, " \t");

        /* handle comments: stored in header */
        if (NULL != strchr("#%;/", line[i]))
        { /* line is a comment */
          count_in_header += strlen(line);
          if (count_in_header >= malloc_size_h) {
            /* if succeed and in array : add (and realloc if necessary) */
            malloc_size_h = count_in_header+4096;
            Header        = (char*)realloc(Header, malloc_size_h*sizeof(char));
          }
          strncat(Header, line, 4096);
          flag_In_array=0;
          /* exit line and file if passed desired block */
          if (block_number > 0 && block_number == block_Current_index) {
            flag_End_row_loop = 1;
          }

          /* Continue with next line */
          continue;
        }

        /* get the number of columns splitting line with strtok */
        char  *lexeme;
        char  flag_End_Line = 0;
        long  block_Num_Columns = 0;
        const char seps[] = " ,;\t\n\r";

        lexeme = strtok(line, seps);
        while (!flag_End_Line) {
          if ((lexeme != NULL) && (lexeme[0] != '\0')) {
            /* reading line: the token is not empty */
            double X;
            int    count=1;
            /* test if we have 'NaN','Inf' */
            if (!strncasecmp(lexeme,"NaN",3))
              X = 0;
            else if (!strncasecmp(lexeme,"Inf",3) || !strncasecmp(lexeme,"+Inf",4))
              X = FLT_MAX;
            else if (!strncasecmp(lexeme,"-Inf",4))
              X = -FLT_MAX;
            else
              count = sscanf(lexeme,"%lg",&X);
            if (count == 1) {
              /* reading line: the token is a number in the line */
              if (!flag_In_array) {
                /* reading num: not already in a block: starts a new data block */
                block_Current_index++;
                flag_In_array    = 1;
                block_Num_Columns= 0;
                if (block_number > 0) {
                  /* initialise a new data block */
                  Rows = 0;
                  count_in_array = 0;
                } /* else append */
              }
              /* reading num: all blocks or selected block */
              if (flag_In_array && (block_number == 0 ||
                  block_number == block_Current_index)) {
                /* starting block: already the desired number of rows ? */
                if (block_Num_Columns == 0 &&
                    max_rows > 0 && Rows >= max_rows) {
                  flag_End_Line      = 1;
                  flag_End_row_loop  = 1;
                  flag_In_array      = 0;
                  /* reposition to begining of line (ignore line) */
                  fseek(hfile, back_pos, SEEK_SET);
                } else { /* store into data array */
                  if (count_in_array >= malloc_size) {
                    /* realloc data buffer if necessary */
                    malloc_size = count_in_array*1.5;
                    Data = (double*) realloc(Data, malloc_size*sizeof(double));
                    if (Data == NULL) {
                      fprintf(stderr, "Error: Can not re-allocate memory %li (Table_Read_Handle).\n",
                              malloc_size*sizeof(double));
                      return (-1);
                    }
                  }
                  if (0 == block_Num_Columns) Rows++;
                  Data[count_in_array] = X;
                  count_in_array++;
                  block_Num_Columns++;
                }
              } /* reading num: end if flag_In_array */
            } /* end reading num: end if sscanf lexeme -> numerical */
            else {
              /* reading line: the token is not numerical in that line. end block */
              if (block_Current_index == block_number) {
                flag_End_Line = 1;
                flag_End_row_loop = 1;
              } else {
                flag_In_array = 0;
                flag_End_Line = 1;
              }
            }
          }
          else {
            /* no more tokens in line */
            flag_End_Line = 1;
            if (block_Num_Columns > 0) Columns = block_Num_Columns;
          }

          // parse next token
          lexeme = strtok(NULL, seps);

        } /* while (!flag_End_Line) */
      } /* end: if fgets */
      else flag_End_row_loop = 1; /* else fgets : end of file */

    } while (!flag_End_row_loop); /* end while flag_End_row_loop */

    Table->block_number = block_number;
    Table->array_length = 1;

    // shrink header to actual size (plus terminating 0-byte)
    if (count_in_header) {
      Header = (char*)realloc(Header, count_in_header*sizeof(char) + 1);
    }
    Table->header = Header;

    if (count_in_array*Rows*Columns == 0)
    {
      Table->rows         = 0;
      Table->columns      = 0;
      free(Data);
      return (0);
    }
    if (Rows * Columns != count_in_array)
    {
      fprintf(stderr, "Warning: Read_Table :%s %s Data has %li values that should be %li x %li\n",
        (Table->filename[0] != '\0' ? Table->filename : ""),
        (!block_number ? " catenated" : ""),
        count_in_array, Rows, Columns);
      Columns = count_in_array; Rows = 1;
    }
    Data     = (double*)realloc(Data, count_in_array*sizeof(double));
    Table->data         = Data;
    Table->rows         = Rows;
    Table->columns      = Columns;

    return (count_in_array);

  } /* end Table_Read_Handle */

/*******************************************************************************
* long Table_Rebin(t_Table *Table)
*   ACTION: rebin a single Table, sorting 1st column in ascending order
*   input   Table: single table containing data.
*                  The data block is reallocated in this process
*   return  updated Table with increasing, evenly spaced first column (index 0)
*           number of data elements (-1: error, 0:empty data)
*******************************************************************************/
  long Table_Rebin(t_Table *Table)
  {
    double new_step=0;
    long   i;
    /* performs linear interpolation on X axis (0-th column) */

    if (!Table) return(-1);
    if (!Table->data 
    || Table->rows*Table->columns == 0 || !Table->step_x)
      return(0);
    Table_Stat(Table); /* recompute statitstics and minimal step */
    new_step = Table->step_x; /* minimal step in 1st column */

    if (!(Table->constantstep)) /* not already evenly spaced */
    {
      long Length_Table;
      double *New_Table;

      Length_Table = ceil(fabs(Table->max_x - Table->min_x)/new_step)+1;
      /*return early if the rebinned table will become too large*/
      if (Length_Table > mcread_table_rebin_maxsize){
        fprintf(stderr,"WARNING: (Table_Rebin): Rebinning table from %s would exceed 1M rows. Skipping.\n", Table->filename); 
        return(Table->rows*Table->columns);
      }
      New_Table    = (double*)malloc(Length_Table*Table->columns*sizeof(double));

      for (i=0; i < Length_Table; i++)
      {
        long   j;
        double X;
        X = Table->min_x + i*new_step;
        New_Table[i*Table->columns] = X;
        for (j=1; j < Table->columns; j++)
          New_Table[i*Table->columns+j]
                = Table_Value(*Table, X, j);
      } /* end for i */

      Table->rows = Length_Table;
      Table->step_x = new_step;
      Table->max_x = Table->min_x + (Length_Table-1)*new_step; 
      /*max might not be the same anymore
       * Use Length_Table -1 since the first and laset rows are the limits of the defined interval.*/
      free(Table->data);
      Table->data = New_Table;
      Table->constantstep=1;
    } /* end else (!constantstep) */
    return (Table->rows*Table->columns);
  } /* end Table_Rebin */

/*******************************************************************************
* double Table_Index(t_Table Table, long i, long j)
*   ACTION: read an element [i,j] of a single Table
*   input   Table: table containing data
*           i : index of row      (0:Rows-1)
*           j : index of column   (0:Columns-1)
*   return  Value = data[i][j]
* Returns Value from the i-th row, j-th column of Table
* Tests are performed on indexes i,j to avoid errors
*******************************************************************************/

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

double Table_Index(t_Table Table, long i, long j)
{
  long AbsIndex;

  if (Table.rows == 1 || Table.columns == 1) {
    /* vector */
    j = MIN(MAX(0, i+j), Table.columns*Table.rows - 1);
    i = 0;
  } else {
    /* matrix */
    i = MIN(MAX(0, i), Table.rows - 1);
    j = MIN(MAX(0, j), Table.columns - 1);
  }

  /* handle vectors specifically */
  AbsIndex = i*(Table.columns)+j;

  if (Table.data != NULL)
    return (Table.data[AbsIndex]);
  else
    return 0;
} /* end Table_Index */

/*******************************************************************************
* void Table_SetElement(t_Table *Table, long i, long j, double value)
*   ACTION: set an element [i,j] of a single Table
*   input   Table: table containing data
*           i : index of row      (0:Rows-1)
*           j : index of column   (0:Columns-1)
*           value = data[i][j]
* Returns 0 in case of error
* Tests are performed on indexes i,j to avoid errors
*******************************************************************************/
int Table_SetElement(t_Table *Table, long i, long j,
                     double value)
{
  long AbsIndex;

  if (Table->rows == 1 || Table->columns == 1) {
    /* vector */
    j = MIN(MAX(0, i+j), Table->columns*Table->rows - 1); i=0;
  } else {
    /* matrix */
    i = MIN(MAX(0, i), Table->rows - 1);
    j = MIN(MAX(0, j), Table->columns - 1);
  }

  AbsIndex = i*(Table->columns)+j;
  if (Table->data != NULL) {
    Table->data[AbsIndex] = value;
    return 1;
  }

  return 0;
} /* end Table_SetElement */

/*******************************************************************************
* double Table_Value(t_Table Table, double X, long j)
*   ACTION: read column [j] of a single Table at row which 1st column is X
*   input   Table: table containing data.
*           X : data value in the first column (index 0)
*           j : index of column from which is extracted the Value (0:Columns-1)
*   return  Value = data[index for X][j] with linear interpolation
* Returns Value from the j-th column of Table corresponding to the
* X value for the 1st column (index 0)
* Tests are performed (within Table_Index) on indexes i,j to avoid errors
* NOTE: data should rather be monotonic, and evenly sampled.
*******************************************************************************/
double Table_Value(t_Table Table, double X, long j)
{
  long   Index = -1;
  double X1=0, Y1=0, X2=0, Y2=0;
  double ret=0;

  if (X > Table.max_x) return Table_Index(Table,Table.rows-1  ,j);
  if (X < Table.min_x) return Table_Index(Table,0  ,j);

  // Use constant-time lookup when possible
  if(Table.constantstep) {
    Index = (long)floor(
              (X - Table.min_x) / (Table.max_x - Table.min_x) * (Table.rows-1));
    X1 = Table_Index(Table,Index-1,0);
    X2 = Table_Index(Table,Index  ,0);
  }
  // Use binary search on large, monotonic tables
  else if(Table.monotonic && Table.rows > 100) {
    long left = Table.min_x;
    long right = Table.max_x;

    while (!((X1 <= X) && (X < X2)) && (right - left > 1)) {
      Index = (left + right) / 2;

      X1 = Table_Index(Table, Index-1, 0);
      X2 = Table_Index(Table, Index,   0);

      if (X < X1) {
        right = Index;
      } else {
        left  = Index;
      }
    }
  }

  // Fall back to linear search, if no-one else has set X1, X2 correctly
  if (!((X1 <= X) && (X < X2))) {
    /* look for index surrounding X in the table -> Index */
    for (Index=1; Index <= Table.rows-1; Index++) {
        X1 = Table_Index(Table, Index-1,0);
        X2 = Table_Index(Table, Index  ,0);
        if ((X1 <= X) && (X < X2)) break;
      } /* end for Index */
  }

  Y1 = Table_Index(Table,Index-1, j);
  Y2 = Table_Index(Table,Index  , j);

  if (!strcmp(Table.method,"linear")) {
    ret = Table_Interp1d(X, X1,Y1, X2,Y2);
  }
  else if (!strcmp(Table.method,"nearest")) {
    ret = Table_Interp1d_nearest(X, X1,Y1, X2,Y2);
  }

  return ret;
} /* end Table_Value */

/*******************************************************************************
* double Table_Value2d(t_Table Table, double X, double Y)
*   ACTION: read element [X,Y] of a matrix Table
*   input   Table: table containing data.
*           X : row index, may be non integer
*           Y : column index, may be non integer
*   return  Value = data[index X][index Y] with bi-linear interpolation
* Returns Value for the indices [X,Y]
* Tests are performed (within Table_Index) on indexes i,j to avoid errors
* NOTE: data should rather be monotonic, and evenly sampled.
*******************************************************************************/
  double Table_Value2d(t_Table Table, double X, double Y)
  {
    long   x1,x2,y1,y2;
    double z11,z12,z21,z22;
    double ret=0;

    x1 = (long)floor(X);
    y1 = (long)floor(Y);

    if (x1 > Table.rows-1 || x1 < 0) {
      x2 = x1;
    } else {
      x2 = x1 + 1;
    }

    if (y1 > Table.columns-1 || y1 < 0) {
      y2 = y1;
    } else {
      y2 = y1 + 1;
    }

    z11 = Table_Index(Table, x1, y1);

    if (y2 != y1) z12=Table_Index(Table, x1, y2); else z12 = z11;
    if (x2 != x1) z21=Table_Index(Table, x2, y1); else z21 = z11;
    if (y2 != y1) z22=Table_Index(Table, x2, y2); else z22 = z21;

    if (!strcmp(Table.method,"linear"))
      ret = Table_Interp2d(X,Y, x1,y1,x2,y2, z11,z12,z21,z22);
    else {
      if (fabs(X-x1) < fabs(X-x2)) {
        if (fabs(Y-y1) < fabs(Y-y2)) ret = z11; else ret = z12;
      } else {
        if (fabs(Y-y1) < fabs(Y-y2)) ret = z21; else ret = z22;
      }
    }
    return ret;
  } /* end Table_Value2d */


/*******************************************************************************
* void Table_Free(t_Table *Table)
*   ACTION: free a single Table. First Call Table_File_list_gc. If this returns
*   non-zero it means there are more refernces to the table, and so the table
*   should not bee freed.
*   return: empty Table
*******************************************************************************/
  void Table_Free(t_Table *Table)
  {
    if( !Table_File_List_gc(Table) ){
       return;
    } 
    if (!Table) return;
    if (Table->data   != NULL) free(Table->data);
    if (Table->header != NULL) free(Table->header);
    Table->data   = NULL;
    Table->header = NULL;
  } /* end Table_Free */

/******************************************************************************
* void Table_Info(t_Table Table)
*    ACTION: print informations about a single Table
*******************************************************************************/
  long Table_Info(t_Table Table)
  {
    char buffer[256];
    long ret=0;

    if (!Table.block_number) strcpy(buffer, "catenated");
    else sprintf(buffer, "block %li", Table.block_number);
    printf("Table from file '%s' (%s)",
      Table.filename[0] != '\0' ? Table.filename : "", buffer);
    if ((Table.data != NULL) && (Table.rows*Table.columns))
    {
      printf(" is %li x %li ", Table.rows, Table.columns);
      if (Table.rows*Table.columns > 1)
        printf("(x=%g:%g)", Table.min_x, Table.max_x);
      else printf("(x=%g) ", Table.min_x);
      ret = Table.rows*Table.columns;
      if (Table.monotonic)    printf(", monotonic");
      if (Table.constantstep) printf(", constant step");
      printf(". interpolation: %s\n", Table.method);
    }
    else printf(" is empty.\n");

    if (Table.header && strlen(Table.header)) {
      char *header;
      int  i;
      header = malloc(80);
      if (!header) return(ret);
      for (i=0; i<80; header[i++]=0);
      strncpy(header, Table.header, 75);
      if (strlen(Table.header) > 75) {
        strcat( header, " ...");
      }
      for (i=0; i<strlen(header); i++)
        if (header[i] == '\n' || header[i] == '\r') header[i] = ';';
      printf("  '%s'\n", header);
      free(header);
    }

    return(ret);
  } /* end Table_Info */

/******************************************************************************
* long Table_Init(t_Table *Table, m, n)
*   ACTION: initialise a Table to empty m by n table
*   return: empty Table
******************************************************************************/
long Table_Init(t_Table *Table, long rows, long columns)
{
  double *data=NULL;
  long   i;

  if (!Table) return(0);

  Table->header  = NULL;
  Table->filename[0]= '\0';
  Table->filesize= 0;
  Table->min_x   = 0;
  Table->max_x   = 0;
  Table->step_x  = 0;
  Table->block_number = 0;
  Table->array_length = 0;
  Table->monotonic    = 0;
  Table->constantstep = 0;
  Table->begin   = 0;
  Table->end     = 0;
  strcpy(Table->method,"linear");

  if (rows*columns >= 1) {
    data    = (double*)malloc(rows*columns*sizeof(double));
    if (data) for (i=0; i < rows*columns; data[i++]=0);
    else {
      fprintf(stderr,"Error: allocating %ld double elements."
                     "Too big (Table_Init).\n", rows*columns);
      rows = columns = 0;
    }
  }
  Table->rows    = (rows >= 1 ? rows : 0);
  Table->columns = (columns >= 1 ? columns : 0);
  Table->data    = data;
  return(Table->rows*Table->columns);
} /* end Table_Init */

/******************************************************************************
* long Table_Write(t_Table Table, char *file, x1,x2, y1,y2)
*   ACTION: write a Table to disk (ascii).
*     when x1=x2=0 or y1=y2=0, the table default limits are used.
*   return: 0=all is fine, non-0: error
*******************************************************************************/
MCDETECTOR Table_Write(t_Table Table, char *file, char *xl, char *yl, 
  double x1, double x2, double y1, double y2)
{
  MCDETECTOR detector;

  if ((Table.data == NULL) && (Table.rows*Table.columns)) {
    detector.m = 0;
    return(detector); /* Table is empty - nothing to do */
  }
  if (!x1 && !x2) {
    x1 = Table.min_x;
    x2 = Table.max_x;
  }
  if (!y1 && !y2) {
    y1 = 1;
    y2 = Table.columns;
  }

  /* transfer content of the Table into a 2D detector */
  Coords coords = { 0, 0, 0};

  if (Table.rows == 1 || Table.columns == 1) {
    detector = mcdetector_out_1D(Table.filename,
                      xl ? xl : "", yl ? yl : "",
                      "x", x1, x2,
                      Table.rows * Table.columns,
                      NULL, Table.data, NULL,
                      file, file, coords);
  } else {
    detector = mcdetector_out_2D(Table.filename,
                      xl ? xl : "", yl ? yl : "",
                      x1, x2, y1, y2,
                      Table.rows, Table.columns,
                      NULL, Table.data, NULL,
                      file, file, coords);
  }
  return(detector);
}

/******************************************************************************
* void Table_Stat(t_Table *Table)
*   ACTION: computes min/max/mean step of 1st column for a single table (private)
*   return: updated Table
*******************************************************************************/
  static void Table_Stat(t_Table *Table)
  {
    long   i;
    double max_x, min_x;
    double row=1;
    char   monotonic=1;
    char   constantstep=1;
    double step=0;
    long n;

    if (!Table) return;
    if (!Table->rows || !Table->columns) return;
    if (Table->rows == 1) row=0; // single row
    max_x = -FLT_MAX;
    min_x =  FLT_MAX;
    n     = (row ? Table->rows : Table->columns);
    /* get min and max of first column/vector */
    for (i=0; i < n; i++)
    {
      double X;
      X = (row ? Table_Index(*Table,i  ,0)
                               : Table_Index(*Table,0, i));
      if (X < min_x) min_x = X;
      if (X > max_x) max_x = X;
    } /* for */
    
    /* test for monotonicity and constant step if the table is an XY or single vector */
    if (n > 1) {
      /* mean step */
      step = (max_x - min_x)/(n-1);
      /* now test if table is monotonic on first column, and get minimal step size */
      for (i=0; i < n-1; i++) {
        double X, diff;;
        X    = (row ? Table_Index(*Table,i  ,0)
                    : Table_Index(*Table,0,  i));
        diff = (row ? Table_Index(*Table,i+1,0)
                    : Table_Index(*Table,0,  i+1)) - X;
        if (diff && fabs(diff) < fabs(step)) step = diff;
        /* change sign ? */
        if ((max_x - min_x)*diff < 0 && monotonic)
          monotonic = 0;
      } /* end for */
      
      /* now test if steps are constant within READ_TABLE_STEPTOL */
      if(!step){
        /*means there's a disconitnuity -> not constantstep*/
        constantstep=0;
      }else if (monotonic) {
        for (i=0; i < n-1; i++) {
          double X, diff;
          X    = (row ? Table_Index(*Table,i  ,0)
              : Table_Index(*Table,0,  i));
          diff = (row ? Table_Index(*Table,i+1,0)
              : Table_Index(*Table,0,  i+1)) - X;
          if ( fabs(step)*(1+READ_TABLE_STEPTOL) < fabs(diff) ||
                fabs(diff) < fabs(step)*(1-READ_TABLE_STEPTOL) )
          { constantstep = 0; break; }
        }
      }

    }
    Table->step_x= step;
    Table->max_x = max_x;
    Table->min_x = min_x;
    Table->monotonic = monotonic;
    Table->constantstep = constantstep;
  } /* end Table_Stat */

/******************************************************************************
* t_Table *Table_Read_Array(char *File, long *blocks)
*   ACTION: read as many data blocks as available, iteratively from file
*   return: initialized t_Table array, last element is an empty Table.
*           the number of extracted blocks in non NULL pointer *blocks
*******************************************************************************/
  t_Table *Table_Read_Array(char *File, long *blocks)
  {
    t_Table *Table_Array=NULL;
    long offset=0;
    long block_number=0;
    long allocated=256;
    long nelements=1;

    /* first allocate an initial empty t_Table array */
    Table_Array = (t_Table *)malloc(allocated*sizeof(t_Table));
    if (!Table_Array) {
      fprintf(stderr, "Error: Can not allocate memory %li (Table_Read_Array).\n",
         allocated*sizeof(t_Table));
      *blocks = 0;
      return (NULL);
    }

    while (nelements > 0)
    {
      t_Table Table;

      /* if ok, set t_Table block number else exit loop */
      block_number++;
      Table.block_number = block_number;
      
      /* access file at offset and get following block. Block number is from the set offset
       * hence the hardcoded 1 - i.e. the next block counted from offset.*/
      nelements = Table_Read_Offset(&Table, File, 1, &offset,0);
      /*if the block is empty - don't store it*/
      if (nelements>0){
          /* if t_Table array is not long enough, expand and realocate */
          if (block_number >= allocated-1) {
              allocated += 256;
              Table_Array = (t_Table *)realloc(Table_Array,
                      allocated*sizeof(t_Table));
              if (!Table_Array) {
                  fprintf(stderr, "Error: Can not re-allocate memory %li (Table_Read_Array).\n",
                          allocated*sizeof(t_Table));
                  *blocks = 0;
                  return (NULL);
              }
          }
          /* store it into t_Table array */
          //snprintf(Table.filename, 1024, "%s#%li", File, block_number-1);
          Table_Array[block_number-1] = Table;
      }
      /* continues until we find an empty block */
    }
    /* send back number of extracted blocks */
    if (blocks) *blocks = block_number-1;

    /* now store total number of elements in Table array */
    for (offset=0; offset < block_number;
      Table_Array[offset++].array_length = block_number-1);

    return(Table_Array);
  } /* end Table_Read_Array */
/*******************************************************************************
* void Table_Free_Array(t_Table *Table)
*   ACTION: free a Table array
*******************************************************************************/
  void Table_Free_Array(t_Table *Table)
  {
    long index;
    if (!Table) return;
    for (index=0;index < Table[0].array_length; index++){
            Table_Free(&Table[index]);
    }
    free(Table);
  } /* end Table_Free_Array */

/******************************************************************************
* long Table_Info_Array(t_Table *Table)
*    ACTION: print informations about a Table array
*    return: number of elements in the Table array
*******************************************************************************/
  long Table_Info_Array(t_Table *Table)
  {
    long index=0;

    if (!Table) return(-1);
    while (index < Table[index].array_length
       && (Table[index].data || Table[index].header)
       && (Table[index].rows*Table[index].columns) ) {
      Table_Info(Table[index]);
      index++;
    }
    printf("This Table array contains %li elements\n", index);
    return(index);
  } /* end Table_Info_Array */

/******************************************************************************
* char **Table_ParseHeader(char *header, symbol1, symbol2, ..., NULL)
*    ACTION: search for char* symbols in header and return their value or NULL
*            the search is not case sensitive.
*            Last argument MUST be NULL
*    return: array of char* with line following each symbol, or NULL if not found
*******************************************************************************/
#ifndef MyNL_ARGMAX
#define MyNL_ARGMAX 50
#endif

char **Table_ParseHeader_backend(char *header, ...){
  va_list ap;
  char exit_flag=0;
  int counter   =0;
  char **ret    =NULL;
  if (!header || header[0]=='\0') return(NULL);

  ret = (char**)calloc(MyNL_ARGMAX, sizeof(char*));
  if (!ret) {
    printf("Table_ParseHeader: Cannot allocate %i values array for Parser (Table_ParseHeader).\n",
      MyNL_ARGMAX);
    return(NULL);
  }
  for (counter=0; counter < MyNL_ARGMAX; ret[counter++] = NULL);
  counter=0;

  va_start(ap, header);
  while(!exit_flag && counter < MyNL_ARGMAX-1)
  {
    char *arg_char=NULL;
    char *pos     =NULL;
    /* get variable argument value as a char */
    arg_char = va_arg(ap, char *);
    if (!arg_char || arg_char[0]=='\0'){
      exit_flag = 1; break;
    }
    /* search for the symbol in the header */
    pos = (char*)strcasestr(header, arg_char);
    if (pos) {
      char *eol_pos;
      eol_pos = strchr(pos+strlen(arg_char), '\n');
      if (!eol_pos)
        eol_pos = strchr(pos+strlen(arg_char), '\r');
      if (!eol_pos)
        eol_pos = pos+strlen(pos)-1;
      ret[counter] = (char*)malloc(eol_pos - pos);
      if (!ret[counter]) {
        printf("Table_ParseHeader: Cannot allocate value[%i] array for Parser searching for %s (Table_ParseHeader).\n",
          counter, arg_char);
        exit_flag = 1; break;
      }
      strncpy(ret[counter], pos+strlen(arg_char), eol_pos - pos - strlen(arg_char));
      ret[counter][eol_pos - pos - strlen(arg_char)]='\0';
    }
    counter++;
  }
  va_end(ap);
  return(ret);
} /* Table_ParseHeader */

/******************************************************************************
* double Table_Interp1d(x, x1, y1, x2, y2)
*    ACTION: interpolates linearly at x between y1=f(x1) and y2=f(x2)
*    return: y=f(x) value
*******************************************************************************/
double Table_Interp1d(double x,
  double x1, double y1,
  double x2, double y2)
{
  double slope;
  if (x2 == x1) return (y1+y2)/2;
  if (y1 == y2) return  y1;
  slope = (y2 - y1)/(x2 - x1);
  return y1+slope*(x - x1);
} /* Table_Interp1d */

/******************************************************************************
* double Table_Interp1d_nearest(x, x1, y1, x2, y2)
*    ACTION: table lookup with nearest method at x between y1=f(x1) and y2=f(x2)
*    return: y=f(x) value
*******************************************************************************/
double Table_Interp1d_nearest(double x,
  double x1, double y1,
  double x2, double y2)
{
  if (fabs(x-x1) < fabs(x-x2)) return (y1);
  else return(y2);
} /* Table_Interp1d_nearest */

/******************************************************************************
* double Table_Interp2d(x,y, x1,y1, x2,y2, z11,z12,z21,z22)
*    ACTION: interpolates bi-linearly at (x,y) between z1=f(x1,y1) and z2=f(x2,y2)
*    return: z=f(x,y) value
*    x,y |   x1   x2
*    ----------------
*     y1 |   z11  z21
*     y2 |   z12  z22
*******************************************************************************/
double Table_Interp2d(double x, double y,
  double x1, double y1,
  double x2, double y2,
  double z11, double z12, double z21, double z22)
{
  double ratio_x, ratio_y;
  if (x2 == x1) return Table_Interp1d(y, y1,z11, y2,z12);
  if (y1 == y2) return Table_Interp1d(x, x1,z11, x2,z21);

  ratio_y = (y - y1)/(y2 - y1);
  ratio_x = (x - x1)/(x2 - x1);
  return (1-ratio_x)*(1-ratio_y)*z11 + ratio_x*(1-ratio_y)*z21
    + ratio_x*ratio_y*z22         + (1-ratio_x)*ratio_y*z12;
} /* Table_Interp2d */

/* end of read_table-lib.c */


#ifndef SOURCE_GEN_DEF
#define SOURCE_GEN_DEF
/*******************************************************************************
* str_dup_numeric: replaces non 'valid name' chars with spaces
*******************************************************************************/
char *str_dup_numeric(char *orig)
  {
    long i;

    if (!orig || !strlen(orig)) return(NULL);

    for (i=0; i < strlen(orig); i++)
    {
      if ( (orig[i] > 122)
        || (orig[i] < 32)
        || (strchr("!\"#$%&'()*,:;<=>?@[\\]^`/ ", orig[i]) != NULL) )
      {
        orig[i] = ' ';
      }
    }
    orig[i] = '\0';
    /* now skip spaces */
    for (i=0; i < strlen(orig); i++) {
      if (*orig == ' ') orig++;
      else break;
    }

    return(orig);
  } /* str_dup_numeric */

  /* A normalised Maxwellian distribution : Integral over all l = 1 */
  double SG_Maxwell(double l, double temp)
  {
    double a=949.0/temp;
    return 2*a*a*exp(-a/(l*l))/(l*l*l*l*l);
  }
#endif

#line 6945 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'Guide_gravity'. */
#line 124 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
/*****************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2006, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/ref-lib.h
*
* %Identification
* Written by: Peter Christiansen
* Date: August, 2006
* Origin: RISOE
* Release: McStas 1.10
* Version: $Revision$
*
* Commonly used reflection functions are declared in this file which
* are used by some guide and mirror components.
*
* Depends on read_table-lib
*
* Usage: within SHARE
* %include "ref-lib"
*
****************************************************************************/


#ifndef REF_LIB_H
#define REF_LIB_H "$Revision$"

void StdReflecFunc(double, double*, double*);
void TableReflecFunc(double, t_Table*, double*);

#endif

/* end of ref-lib.h */
/****************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2006, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/ref-lib.c
*
* %Identification
* Written by: Peter Christiansen
* Date: August, 2006
* Origin: RISOE
* Release: McStas 1.10
* Version: $Revision$
*
* Commonly used reflection functions are declared in this file which
* are used by some guide and mirror components.
*
* Variable names have prefix 'mc_ref_' for 'McStas Reflection' 
* to avoid conflicts
*
* Usage: within SHARE
* %include "ref-lib"
*
****************************************************************************/

#ifndef REF_LIB_H
#include "ref-lib.h"
#endif

#ifndef READ_TABLE_LIB_H
#include "read_table-lib.h"
#include "read_table-lib.c"
#endif

/****************************************************************************
* void StdReflecFunc(double q, double *par, double *r)
* 
* The McStas standard analytic parametrization of the reflectivity.
* The parameters are:
* R0:      [1]    Low-angle reflectivity
* Qc:      [AA-1] Critical scattering vector
* alpha:   [AA]   Slope of reflectivity
* m:       [1]    m-value of material. Zero means completely absorbing.
* W:       [AA-1] Width of supermirror cut-off
*****************************************************************************/
void StdReflecFunc(double mc_pol_q, double *mc_pol_par, double *mc_pol_r) {
    double R0    = mc_pol_par[0];
    double Qc    = mc_pol_par[1];
    double alpha = mc_pol_par[2];
    double m     = mc_pol_par[3];
    double W     = mc_pol_par[4];
    double beta  = 0;
    mc_pol_q     = fabs(mc_pol_q);
    double arg;
        
    /* Simpler parametrization from Henrik Jacobsen uses these values that depend on m only.
       double m_value=m*0.9853+0.1978;
       double W=-0.0002*m_value+0.0022;
       double alpha=0.2304*m_value+5.0944;
       double beta=-7.6251*m_value+68.1137; 
       If W and alpha are set to 0, use Henrik's approach for estimating these parameters
       and apply the formulation:
       arg = R0*0.5*(1-tanh(arg))*(1-alpha*(q-Qc)+beta*(q-Qc)*(q-Qc));
    */  
    if (W==0 && alpha==0) {
      m=m*0.9853+0.1978;
      W=-0.0002*m+0.0022;
      alpha=0.2304*m+5.0944;
      beta=-7.6251*m+68.1137;
      if (m<=3) {
	alpha=m;
	beta=0;
      }
    }
    
    arg = W > 0 ? (mc_pol_q - m*Qc)/W : 11;

    if (arg > 10 || m <= 0 || Qc <=0 || R0 <= 0) {
      *mc_pol_r = 0;
      return;
    }
    
    if (m < 1) { Qc *= m; m=1; }
    
    if(mc_pol_q <= Qc) {      
      *mc_pol_r = R0;
      return;
    }
    
    
    *mc_pol_r = R0*0.5*(1 - tanh(arg))*(1 - alpha*(mc_pol_q - Qc) + beta*(mc_pol_q - Qc)*(mc_pol_q - Qc));
    
    return;
  }

/****************************************************************************
* void TableReflecFunc(double q, t_Table *par, double *r) {
* 
* Looks up the reflectivity in a table using the routines in read_table-lib.
*****************************************************************************/
void TableReflecFunc(double mc_pol_q, t_Table *mc_pol_par, double *mc_pol_r) {
    
  *mc_pol_r = Table_Value(*mc_pol_par, mc_pol_q, 1);
  if(*mc_pol_r>1)
    *mc_pol_r = 1;
  return;
}

/* end of ref-lib.c */

#ifndef Gravity_guide_Version
#define Gravity_guide_Version "$Revision$"

#ifndef PROP_GRAV_DT
#error McStas : You need PROP_GRAV_DT (McStas >= 1.4.3) to run this component
#endif

/*
* G:       (m/s^2) Gravitation acceleration along y axis [-9.81]
* Gx:      (m/s^2) Gravitation acceleration along x axis [0]
* Gy:      (m/s^2) Gravitation acceleration along y axis [-9.81]
* Gz:      (m/s^2) Gravitation acceleration along z axis [0]
* mh:      (1)    m-value of material for left/right vert. mirrors
* mv:      (1)    m-value of material for top/bottom horz. mirrors
* mx:      (1)    m-value of material for left/right vert. mirrors
* my:      (1)    m-value of material for top/bottom horz. mirrors
*/

  typedef struct Gravity_guide_Vars
  {
    double gx;
    double gy;
    double gz;
    double nx[6], ny[6], nz[6];
    double wx[6], wy[6], wz[6];
    double A[6], norm_n2[6], norm_n[6];
    long   N_reflection[7];
    double w1c, h1c;
    double w2c, h2c;
    double M[5];
    double Alpha[5];
    double nzC[5], norm_n2xy[5], Axy[5];
    double wav_lr, wav_tb, wav_z;
    double chamfer_z, chamfer_lr, chamfer_tb;
    char   compcurname[256];
    double fc_freq, fc_phase;
    double warnings;
  } Gravity_guide_Vars_type;

  void Gravity_guide_Init(Gravity_guide_Vars_type *aVars,
    MCNUM a_w1, MCNUM a_h1, MCNUM a_w2, MCNUM a_h2, MCNUM a_l, MCNUM a_R0,
    MCNUM a_Qc, MCNUM a_alpha, MCNUM a_m, MCNUM a_W, MCNUM a_nslit, MCNUM a_d,
    MCNUM a_Gx, MCNUM a_Gy, MCNUM a_Gz,
    MCNUM a_mleft, MCNUM a_mright, MCNUM a_mtop, MCNUM a_mbottom, MCNUM a_nhslit,
    MCNUM a_wavy_lr, MCNUM a_wavy_tb, MCNUM a_wavy_z, MCNUM a_wavy,
    MCNUM a_chamfers_z, MCNUM a_chamfers_lr, MCNUM a_chamfers_tb, MCNUM a_chamfers,
    MCNUM a_nu, MCNUM a_phase, MCNUM a_aleft, MCNUM a_aright, MCNUM a_atop, MCNUM a_abottom)
  {
    int i;

    for (i=0; i<7; aVars->N_reflection[i++] = 0);
    for (i=0; i<5; aVars->M[i++] = 0);
    for (i=0; i<5; aVars->Alpha[i++] = 0);

    aVars->gx = a_Gx; /* The gravitation vector in the current component axis system */
    aVars->gy = a_Gy;
    aVars->gz = a_Gz;
    aVars->warnings=0;

    if (a_nslit <= 0 || a_nhslit <= 0) { fprintf(stderr,"%s: Fatal: no channel in this guide (nhslit or nslit=0).\n", aVars->compcurname); exit(-1); }
    if (a_d < 0) { fprintf(stderr,"%s: Fatal: subdividing walls have negative thickness in this guide (d<0).\n", aVars->compcurname); exit(-1); }
    aVars->w1c = (a_w1 - (a_nslit-1) *a_d)/(double)a_nslit;
    aVars->w2c = (a_w2 - (a_nslit-1) *a_d)/(double)a_nslit;
    aVars->h1c = (a_h1 - (a_nhslit-1)*a_d)/(double)a_nhslit;
    aVars->h2c = (a_h2 - (a_nhslit-1)*a_d)/(double)a_nhslit;

    for (i=0; i <= 4;   aVars->M[i++]=a_m);
    for (i=0; i <= 4;   aVars->Alpha[i++]=a_alpha);
    if (a_mleft   >= 0) aVars->M[1] =a_mleft  ;
    if (a_mright  >= 0) aVars->M[2] =a_mright ;
    if (a_mtop    >= 0) aVars->M[3] =a_mtop   ;
    if (a_mbottom >= 0) aVars->M[4] =a_mbottom;
    if (a_aleft   >= 0) aVars->Alpha[1] =a_aleft  ;
    if (a_aright  >= 0) aVars->Alpha[2] =a_aright ;
    if (a_atop    >= 0) aVars->Alpha[3] =a_atop   ;
    if (a_abottom >= 0) aVars->Alpha[4] =a_abottom;

    /* n: normal vectors to surfaces */
    aVars->nx[1] =  a_l; aVars->ny[1] =  0;   aVars->nz[1] =  0.5*(aVars->w2c-aVars->w1c);  /* 1:+X left       */
    aVars->nx[2] = -a_l; aVars->ny[2] =  0;   aVars->nz[2] = -aVars->nz[1];             /* 2:-X right      */
    aVars->nx[3] =  0;   aVars->ny[3] =  a_l; aVars->nz[3] =  0.5*(aVars->h2c-aVars->h1c);  /* 3:+Y top        */
    aVars->nx[4] =  0;   aVars->ny[4] = -a_l; aVars->nz[4] = -aVars->nz[3];             /* 4:-Y bottom     */
    aVars->nx[5] =  0;   aVars->ny[5] =  0;   aVars->nz[5] =  a_l;                      /* 5:+Z exit       */
    aVars->nx[0] =  0;   aVars->ny[0] =  0;   aVars->nz[0] = -a_l;                      /* 0:Z0 input      */
    /* w: a point on these surfaces */
    aVars->wx[1] = +(aVars->w1c)/2; aVars->wy[1] =  0;              aVars->wz[1] = 0;   /* 1:+X left       */
    aVars->wx[2] = -(aVars->w1c)/2; aVars->wy[2] =  0;              aVars->wz[2] = 0;   /* 2:-X right      */
    aVars->wx[3] =  0;              aVars->wy[3] = +(aVars->h1c)/2; aVars->wz[3] = 0;   /* 3:+Y top        */
    aVars->wx[4] =  0;              aVars->wy[4] = -(aVars->h1c)/2; aVars->wz[4] = 0;   /* 4:-Y bottom     */
    aVars->wx[5] =  0;              aVars->wy[5] =  0;              aVars->wz[5] = a_l; /* 5:+Z exit       */
    aVars->wx[0] =  0;              aVars->wy[0] =  0;              aVars->wz[0] = 0;   /* 0:Z0 input      */

    for (i=0; i <= 5; i++)
    {
      aVars->A[i] = scalar_prod(aVars->nx[i], aVars->ny[i], aVars->nz[i], aVars->gx, aVars->gy, aVars->gz)/2;
      aVars->norm_n2[i] = aVars->nx[i]*aVars->nx[i] + aVars->ny[i]*aVars->ny[i] + aVars->nz[i]*aVars->nz[i];
      if (aVars->norm_n2[i] <= 0)
        { fprintf(stderr,"%s: Fatal: normal vector norm %i is null/negative ! check guide dimensions.\n", aVars->compcurname, i); exit(-1); } /* should never occur */
      else
        aVars->norm_n[i] = sqrt(aVars->norm_n2[i]);
    }
    /* partial computations for l/r/t/b sides, to save computing time */
    for (i=1; i <= 4; i++)
    { /* stores nz that changes in case non box element (focus/defocus) */
      aVars->nzC[i]      =  aVars->nz[i]; /* partial xy terms */
      aVars->norm_n2xy[i]=  aVars->nx[i]*aVars->nx[i] + aVars->ny[i]*aVars->ny[i];
      aVars->Axy[i]      = (aVars->nx[i]*aVars->gx    + aVars->ny[i]*aVars->gy)/2;
    }
    /* handle waviness init */
    if (a_wavy && (!a_wavy_tb && !a_wavy_lr && !a_wavy_z))
    { aVars->wav_tb=aVars->wav_lr=aVars->wav_z=a_wavy; }
    else
    { aVars->wav_tb=a_wavy_tb; aVars->wav_lr=a_wavy_lr; aVars->wav_z=a_wavy_z; }
    aVars->wav_tb *= DEG2RAD/(sqrt(8*log(2)));   /* Convert from deg FWHM to rad Gaussian sigma */
    aVars->wav_lr *= DEG2RAD/(sqrt(8*log(2)));
    aVars->wav_z  *= DEG2RAD/(sqrt(8*log(2)));
    /* handle chamfers init */
    if (a_chamfers && (!a_chamfers_z && !a_chamfers_lr && !a_chamfers_tb))
    { aVars->chamfer_z=aVars->chamfer_lr=aVars->chamfer_tb=a_chamfers; }
    else
    {
      aVars->chamfer_z=a_chamfers_z;
      aVars->chamfer_lr=a_chamfers_lr;
      aVars->chamfer_tb=a_chamfers_tb;
    }

    aVars->fc_freq  = a_nu;
    aVars->fc_phase = a_phase;
  }

  int Gravity_guide_Trace(double *dt,
        Gravity_guide_Vars_type *aVars,
        double cx, double cy, double cz,
        double cvx, double cvy, double cvz,
        double cxnum, double cxk, double cynum, double cyk,
        double *cnx, double *cny,double *cnz)
  {
    double B, C;
    int    ret=0;
    int    side=0;
    double n1;
    double dt0, dt_min=0;
    int    i;
    double loc_num, loc_nslit;
    int    i_slope=3;

    /* look if there is a previous intersection with guide sides */
    /* A = 0.5 n.g; B = n.v; C = n.(r-W); */
    /* 5=+Z side: n=(0, 0, -l) ; W = (0, 0, l) (at z=l, guide exit)*/
    B = aVars->nz[5]*cvz; C = aVars->nz[5]*(cz - aVars->wz[5]);
    ret = solve_2nd_order(&dt0, NULL, aVars->A[5], B, C);
    if (ret && dt0>1e-10) { dt_min = dt0; side=5; }

    loc_num = cynum; loc_nslit = cyk;
    for (i=4; i>0; i--)
    {
      if (i == 2) { i_slope=1; loc_num = cxnum; loc_nslit = cxk; }

      if (aVars->nzC[i_slope] != 0) {
        n1 = loc_nslit - 2*(loc_num);  /* slope of l/r/u/d sides depends on the channel ! */
        loc_num++; /* use partial computations to alter nz and A */
        aVars->nz[i]= aVars->nzC[i]*n1;
        aVars->A[i] = aVars->Axy[i] + aVars->nz[i]*aVars->gz/2;
      }
      if (i < 3)
      {      B = aVars->nx[i]*cvx + aVars->nz[i]*cvz; C = aVars->nx[i]*(cx-aVars->wx[i]) + aVars->nz[i]*cz; }
      else { B = aVars->ny[i]*cvy + aVars->nz[i]*cvz; C = aVars->ny[i]*(cy-aVars->wy[i]) + aVars->nz[i]*cz; }
      ret = solve_2nd_order(&dt0, NULL, aVars->A[i], B, C);
      if (ret && dt0>1e-10 && (dt0<dt_min || !dt_min))
      { dt_min = dt0; side=i;
        if (aVars->nzC[i] != 0)
        { aVars->norm_n2[i] = aVars->norm_n2xy[i] + aVars->nz[i]*aVars->nz[i];
          aVars->norm_n[i]  = sqrt(aVars->norm_n2[i]); }
      }
     }

    *dt = dt_min;
    /* handles waviness: rotate n vector */
    if (side > 0 && side < 5 && (aVars->wav_z || aVars->wav_lr || aVars->wav_tb))
    {
      double nt_x, nt_y, nt_z;  /* transverse vector */
      double nn_x, nn_y, nn_z;  /* normal vector (tmp) */
      double phi;
      /* normal vector n_z = [ 0,0,1], n_t = n x n_z; */
      vec_prod(nt_x,nt_y,nt_z, aVars->nx[side],aVars->ny[side],aVars->nz[side], 0,0,1);
      /* rotate n with angle wavy_z around n_t -> nn */
      if (aVars->wav_z) {
        phi = aVars->wav_z;
        rotate(nn_x,nn_y,nn_z, aVars->nx[side],aVars->ny[side],aVars->nz[side], aVars->wav_z*randnorm(), nt_x,nt_y,nt_z);
      } else { nn_x=aVars->nx[side]; nn_y=aVars->ny[side]; nn_z=aVars->nz[side]; }
      /* rotate n with angle wavy_{x|y} around n_z -> nt */
      phi = (side <=2) ? aVars->wav_lr : aVars->wav_tb;
      if (phi) {
        rotate(nt_x,nt_y,nt_z, nn_x,nn_y,nn_z, phi*randnorm(), 0,0,1);
      } else { nt_x=nn_x; nt_y=nn_y; nt_z=nn_z; }
      *cnx=nt_x; *cny=nt_y; *cnz=nt_z;
    } else
    { *cnx=aVars->nx[side]; *cny=aVars->ny[side]; *cnz=aVars->nz[side]; }
    return (side);
  }



#endif
#line 7301 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'Guide_tapering'. */
#line 91 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"

#line 7306 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'Monochromator_curved'. */
#line 109 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
#ifndef GAUSS
/* Define these arrays only once for all instances. */
/* Values for Gauss quadrature. Taken from Brice Carnahan, H. A. Luther and
James O Wilkes, "Applied numerical methods", Wiley, 1969, page 103.
This reference is available from the Copenhagen UB2 library */
double Gauss_X[] = {-0.987992518020485, -0.937273392400706, -0.848206583410427,
-0.724417731360170, -0.570972172608539, -0.394151347077563,
-0.201194093997435, 0, 0.201194093997435,
0.394151347077563, 0.570972172608539, 0.724417731360170,
0.848206583410427, 0.937273392400706, 0.987992518020485};
double Gauss_W[] = {0.030753241996117, 0.070366047488108, 0.107159220467172,
0.139570677926154, 0.166269205816994, 0.186161000115562,
0.198431485327111, 0.202578241925561, 0.198431485327111,
0.186161000115562, 0.166269205816994, 0.139570677926154,
0.107159220467172, 0.070366047488108, 0.030753241996117};


#define GAUSS(x,mean,rms) \
  (exp(-((x)-(mean))*((x)-(mean))/(2*(rms)*(rms)))/(sqrt(2*PI)*(rms)))
#endif


#line 7332 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'PSD_monitor'. */
#line 58 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"

#ifndef ARRAYS_H
#define ARRAYS_H
typedef double* DArray1d;
DArray1d create_darr1d(int n);
void destroy_darr1d(DArray1d a);

typedef double** DArray2d;
DArray2d create_darr2d(int nx, int ny);
void destroy_darr2d(DArray2d a);

typedef double*** DArray3d;
DArray3d create_darr3d(int nx, int ny, int nz);
void destroy_darr3d(DArray3d a);
#endif
#ifndef ARRAYS_C
#define ARRAYS_C
#include <stdlib.h>

DArray1d create_darr1d(int n){
  DArray1d arr2d;
  arr2d = calloc(n, sizeof(double));
  return arr2d;
}
void destroy_darr1d(DArray1d a){
  free(a);
}

DArray2d create_darr2d(int nx, int ny){
  DArray2d arr2d;
  arr2d = calloc(nx, sizeof(double *));

  double *p1;
  p1 = calloc(nx*ny, sizeof(double));

  int i;
  for (i=0; i<nx; i++){
    arr2d[i] = &(p1[i*ny]);
  }
  return arr2d;
}
void destroy_darr2d(DArray2d a){
  free(a[0]);
  free(a);
}

DArray3d create_darr3d(int nx, int ny, int nz){
  DArray3d arr3d;
  int i, j;

  // 1d
  arr3d = calloc(nx, sizeof(double **));

  // d2
  double **p1;
  p1 = calloc(nx*ny, sizeof(double *));

  for (i=0; i<nx; i++){
    arr3d[i] = &(p1[i*ny]);
  }

  // 3d
  double *p2;
  p2 = calloc(nx*ny*nz, sizeof(double));
  for (i=0; i<nx; i++){
    for (j=0; j<ny; j++){
      arr3d[i][j] = &(p2[(i*ny+j)*nz]);
    }
  }
  return arr3d;
}
void destroy_darr3d(DArray3d a){
  free(a[0][0]);
  free(a[0]);
  free(a);
}
#endif

#line 7414 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'Res_sample'. */
#line 71 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../samples/Res_sample.comp"
struct Res_sample_struct
{
double ki_x,ki_y,ki_z,kf_x,kf_y,kf_z;
double rx,ry,rz,pi;
char   isrect;      /* true when sample is a box */
double aw,ah;       /* rectangular angular dimensions */
double xw,yh;       /* rectangular metrical dimensions */
double tx,ty,tz;    /* target coords */
};
#line 7427 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'V_sample'. */
#line 100 "V_sample.comp"
struct StructVarsV
{
double  sigma_a; /* Absorption cross section per atom (barns) */
    double  sigma_i; /* Incoherent scattering cross section per atom (barns) */
    double  rho;     /* Density of atoms (AA-3) */
    double  my_s;
    double  my_a_v;
    int     shapetyp;    /* 0 double well cylynder, 1 box,  3 sphere */
    double  distance;    /* when non zero, gives rect target distance */
    double  aw,ah;       /* rectangular angular dimensions */
    double  xw,yh;       /* rectangular metrical dimensions */
    double  tx,ty,tz;    /* target coords */
  };
#line 7444 "./ThALES_resolution_v2.c"

/* Shared user declarations for all components 'Res_monitor'. */
#line 77 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2002, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/monitor_nd-lib.h
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas 1.6
* Version: $Revision$
*
* This file is to be imported by the monitor_nd related components
* It handles some shared functions.
*
* Usage: within SHARE
* %include "monitor_nd-lib"
*
*******************************************************************************/

#ifndef MONITOR_ND_LIB_H

#define MONITOR_ND_LIB_H "$Revision$"
#define MONnD_COORD_NMAX  30  /* max number of variables to record */

  typedef struct MonitornD_Defines
  {
    int COORD_NONE  ;
    int COORD_X     ;
    int COORD_Y     ;
    int COORD_Z     ;
    int COORD_RADIUS; 
    int COORD_VX    ;
    int COORD_VY    ;
    int COORD_VZ    ;
    int COORD_V     ;
    int COORD_T     ;
    int COORD_P     ;
    int COORD_SX    ;
    int COORD_SY    ;
    int COORD_SZ    ;
    int COORD_KX    ;
    int COORD_KY    ;
    int COORD_KZ    ;
    int COORD_K     ;
    int COORD_ENERGY;
    int COORD_LAMBDA;
    int COORD_KXY   ;
    int COORD_KYZ   ;
    int COORD_KXZ   ;
    int COORD_VXY   ;
    int COORD_VYZ   ;
    int COORD_VXZ   ;
    int COORD_HDIV  ;
    int COORD_VDIV  ;
    int COORD_ANGLE ;
    int COORD_NCOUNT;
    int COORD_THETA ;
    int COORD_PHI   ;
    int COORD_USER1 ;
    int COORD_USER2 ;
    int COORD_USER3 ;
    int COORD_XY    ;
    int COORD_XZ    ;
    int COORD_YZ    ;
    int COORD_PIXELID;

    /* token modifiers */
    int COORD_VAR   ; /* next token should be a variable or normal option */
    int COORD_MIN   ; /* next token is a min value */
    int COORD_MAX   ; /* next token is a max value */
    int COORD_DIM   ; /* next token is a bin value */
    int COORD_FIL   ; /* next token is a filename */
    int COORD_EVNT  ; /* next token is a buffer size value */
    int COORD_3HE   ; /* next token is a 3He pressure value */
    int COORD_LOG   ; /* next variable will be in log scale */
    int COORD_ABS   ; /* next variable will be in abs scale */
    int COORD_SIGNAL; /* next variable will be the signal var */
    int COORD_AUTO  ; /* set auto limits */

    char TOKEN_DEL[32]; /* token separators */

    char SHAPE_SQUARE; /* shape of the monitor */
    char SHAPE_DISK  ;
    char SHAPE_SPHERE;
    char SHAPE_CYLIND;
    char SHAPE_BANANA; /* cylinder without top/bottom, on restricted angular area */
    char SHAPE_BOX   ;
    char SHAPE_PREVIOUS;
    char SHAPE_OFF;

  } MonitornD_Defines_type;

  typedef struct MonitornD_Variables
  {
    double area;
    double Sphere_Radius     ;
    double Cylinder_Height   ;
    char   Flag_With_Borders ;   /* 2 means xy borders too */
    char   Flag_List         ;   /* 1 store 1 buffer, 2 is list all, 3 list all+append */
    char   Flag_Multiple     ;   /* 1 when n1D, 0 for 2D */
    char   Flag_Verbose      ;
    int    Flag_Shape        ;
    char   Flag_Auto_Limits  ;   /* get limits from first Buffer */
    char   Flag_Absorb       ;   /* monitor is also a slit */
    char   Flag_per_cm2      ;   /* flux is per cm2 */
    char   Flag_log          ;   /* log10 of the flux */
    char   Flag_parallel     ;   /* set neutron state back after detection (parallel components) */
    char   Flag_Binary_List  ;
    char   Flag_capture      ;   /* lambda monitor with lambda/lambda(2200m/s = 1.7985 Angs) weightening */
    int    Flag_signal       ;   /* 0:monitor p, else monitor a mean value */
    int    Flag_mantid       ;   /* 0:normal monitor, else do mantid-event specifics */
    int    Flag_OFF          ;   /* Flag to indicate external geometry from OFF file */
    unsigned long OFF_polyidx;   /* When intersection is done externally by off_intersect, this gives the 
				    polygon number, i.e. pixel index */

    unsigned long Coord_Number      ;   /* total number of variables to monitor, plus intensity (0) */
    unsigned long Coord_NumberNoPixel;  /* same but without counting PixelID */
    unsigned long Buffer_Block      ;   /* Buffer size for list or auto limits */
    unsigned long Neutron_Counter   ;   /* event counter, simulation total counts is mcget_ncount() */
    unsigned long Buffer_Counter    ;   /* index in Buffer size (for realloc) */
    unsigned long Buffer_Size       ;
    int    Coord_Type[MONnD_COORD_NMAX];      /* type of variable */
    char   Coord_Label[MONnD_COORD_NMAX][30]; /* label of variable */
    char   Coord_Var[MONnD_COORD_NMAX][30];   /* short id of variable */
    long   Coord_Bin[MONnD_COORD_NMAX];       /* bins of variable array */
    long   Coord_BinProd[MONnD_COORD_NMAX];   /* product of bins of variable array */
    double Coord_Min[MONnD_COORD_NMAX];
    double Coord_Max[MONnD_COORD_NMAX];
    char   Monitor_Label[MONnD_COORD_NMAX*30];/* Label for monitor */
    char   Mon_File[128];                     /* output file name */

    double cx,cy,cz;
    double cvx, cvy, cvz;
    double ckx, cky, ckz;
    double csx, csy, csz;
    double cEx, cEy, cEz;
    double cs1, cs2, ct, cphi, cp;
    double He3_pressure;
    char   Flag_UsePreMonitor    ;   /* use a previously stored neutron parameter set */
    char   UserName1[128];
    char   UserName2[128];
    char   UserName3[128];
    double UserVariable1;
    double UserVariable2;
    double UserVariable3;
    char   option[CHAR_BUF_LENGTH];

    long long int Nsum;
    double psum, p2sum;
    double **Mon2D_N;
    double **Mon2D_p;
    double **Mon2D_p2;
    double *Mon2D_Buffer;
    unsigned long PixelID;

    double mxmin,mxmax,mymin,mymax,mzmin,mzmax;
    double mean_dx, mean_dy, min_x, min_y, max_x, max_y, mean_p;

    char   compcurname[128];
    Coords compcurpos;

  } MonitornD_Variables_type;

/* monitor_nd-lib function prototypes */
/* ========================================================================= */

void Monitor_nD_Init(MonitornD_Defines_type *, MonitornD_Variables_type *, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, int);
int Monitor_nD_Trace(MonitornD_Defines_type *, MonitornD_Variables_type *);
MCDETECTOR Monitor_nD_Save(MonitornD_Defines_type *, MonitornD_Variables_type *);
void Monitor_nD_Finally(MonitornD_Defines_type *, MonitornD_Variables_type *);
void Monitor_nD_McDisplay(MonitornD_Defines_type *,
 MonitornD_Variables_type *);

#define MONND_DECLARE(monname) \
  struct MonitornD_Variables *mcmonnd ## monname;
#define MONND_USER_TITLE(monname, num, title) \
  { mcmonnd ## monname = &(MC_GETPAR(monname, Vars)); \
    strcpy(mcmonnd ## monname->UserName ## num, title); }
#define MONND_USER_VALUE(monname, num, value) \
  { mcmonnd ## monname = &(MC_GETPAR(monname, Vars)); \
    mcmonnd ## monname->UserVariable ## num = (value); }

#endif

/* end of monitor_nd-lib.h */
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2002, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/monitor_nd-lib.c
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas 1.6
* Version: $Revision$
*
* This file is to be imported by the monitor_nd related components
* It handles some shared functions. Embedded within instrument in runtime mode.
*
* Usage: within SHARE
* %include "monitor_nd-lib"
*
*******************************************************************************/

#ifndef MONITOR_ND_LIB_H
#error McStas : please import this library with %include "monitor_nd-lib"
#endif

/* ========================================================================= */
/* Monitor_nD_Init: this routine is used to parse options                    */
/* ========================================================================= */

void Monitor_nD_Init(MonitornD_Defines_type *DEFS,
  MonitornD_Variables_type *Vars,
  MCNUM xwidth,
  MCNUM yheight,
  MCNUM zdepth,
  MCNUM xmin,
  MCNUM xmax,
  MCNUM ymin,
  MCNUM ymax,
  MCNUM zmin,
  MCNUM zmax,
  int offflag)
  {
    long carg = 1;
    char *option_copy, *token;
    char Flag_New_token = 1;
    char Flag_End       = 1;
    char Flag_All       = 0;
    char Flag_No        = 0;
    char Flag_abs       = 0;
    int  Flag_auto      = 0;  /* -1: all, 1: the current variable */
    int  Set_Vars_Coord_Type;
    char Set_Vars_Coord_Label[64];
    char Set_Vars_Coord_Var[64];
    char Short_Label[MONnD_COORD_NMAX][64];
    int  Set_Coord_Mode;
    long i=0, j=0;
    double lmin, lmax, XY=0;
    long t;


    t = (long)time(NULL);

/* initialize DEFS */
/* Variables to monitor */
    DEFS->COORD_NONE   =0;
    DEFS->COORD_X      =1;
    DEFS->COORD_Y      =2;
    DEFS->COORD_Z      =3;
    DEFS->COORD_RADIUS =19;
    DEFS->COORD_VX     =4;
    DEFS->COORD_VY     =5;
    DEFS->COORD_VZ     =6;
    DEFS->COORD_V      =16;
    DEFS->COORD_T      =7;
    DEFS->COORD_P      =8;
    DEFS->COORD_SX     =9;
    DEFS->COORD_SY     =10;
    DEFS->COORD_SZ     =11;
    DEFS->COORD_KX     =12;
    DEFS->COORD_KY     =13;
    DEFS->COORD_KZ     =14;
    DEFS->COORD_K      =15;
    DEFS->COORD_ENERGY =17;
    DEFS->COORD_LAMBDA =18;
    DEFS->COORD_HDIV   =20;
    DEFS->COORD_VDIV   =21;
    DEFS->COORD_ANGLE  =22;
    DEFS->COORD_NCOUNT =23;
    DEFS->COORD_THETA  =24;
    DEFS->COORD_PHI    =25;
    DEFS->COORD_USER1  =26;
    DEFS->COORD_USER2  =27;
    DEFS->COORD_USER3  =28;
    DEFS->COORD_XY     =37;
    DEFS->COORD_YZ     =31;
    DEFS->COORD_XZ     =32;
    DEFS->COORD_VXY    =30;
    DEFS->COORD_VYZ    =34;
    DEFS->COORD_VXZ    =36;
    DEFS->COORD_KXY    =29;
    DEFS->COORD_KYZ    =33;
    DEFS->COORD_KXZ    =35;
    DEFS->COORD_PIXELID=38;

/* token modifiers */
    DEFS->COORD_VAR    =0;    /* next token should be a variable or normal option */
    DEFS->COORD_MIN    =1;    /* next token is a min value */
    DEFS->COORD_MAX    =2;    /* next token is a max value */
    DEFS->COORD_DIM    =3;    /* next token is a bin value */
    DEFS->COORD_FIL    =4;    /* next token is a filename */
    DEFS->COORD_EVNT   =5;    /* next token is a buffer size value */
    DEFS->COORD_3HE    =6;    /* next token is a 3He pressure value */
    DEFS->COORD_LOG    =64;   /* next variable will be in log scale */
    DEFS->COORD_ABS    =128;  /* next variable will be in abs scale */
    DEFS->COORD_SIGNAL =256;  /* next variable will be the signal var */
    DEFS->COORD_AUTO   =512;  /* set auto limits */

    strcpy(DEFS->TOKEN_DEL, " =,;[](){}:");  /* token separators */

    DEFS->SHAPE_SQUARE =0;    /* shape of the monitor */
    DEFS->SHAPE_DISK   =1;
    DEFS->SHAPE_SPHERE =2;
    DEFS->SHAPE_CYLIND =3;
    DEFS->SHAPE_BANANA =4;
    DEFS->SHAPE_BOX    =5;
    DEFS->SHAPE_PREVIOUS=6;
    DEFS->SHAPE_OFF=7;

    Vars->Sphere_Radius     = 0;
    Vars->Cylinder_Height   = 0;
    Vars->Flag_With_Borders = 0;   /* 2 means xy borders too */
    Vars->Flag_List         = 0;   /* 1=store 1 buffer, 2=list all, 3=re-use buffer */
    Vars->Flag_Multiple     = 0;   /* 1 when n1D, 0 for 2D */
    Vars->Flag_Verbose      = 0;
    Vars->Flag_Shape        = DEFS->SHAPE_SQUARE;
    Vars->Flag_Auto_Limits  = 0;   /* get limits from first Buffer */
    Vars->Flag_Absorb       = 0;   /* monitor is also a slit */
    Vars->Flag_per_cm2      = 0;   /* flux is per cm2 */
    Vars->Flag_log          = 0;   /* log10 of the flux */
    Vars->Flag_parallel     = 0;   /* set neutron state back after detection (parallel components) */
    Vars->Flag_Binary_List  = 0;   /* save list as a binary file (smaller) */
    Vars->Coord_Number      = 0;   /* total number of variables to monitor, plus intensity (0) */
    Vars->Coord_NumberNoPixel=0;   /* same but without counting PixelID */

/* Allow to specify size of Monitor_nD buffer via a define*/
#ifndef MONND_BUFSIZ
    Vars->Buffer_Block      = 100000;     /* Buffer size for list or auto limits */
#else
	Vars->Buffer_Block      = MONND_BUFSIZ;     /* Buffer size for list or auto limits */	
#endif
    Vars->Neutron_Counter   = 0;   /* event counter, simulation total counts is mcget_ncount() */
    Vars->Buffer_Counter    = 0;   /* index in Buffer size (for realloc) */
    Vars->Buffer_Size       = 0;
    Vars->UserVariable1     = 0;
    Vars->UserVariable2     = 0;
    Vars->He3_pressure      = 0;
    Vars->Flag_capture      = 0;
    Vars->Flag_signal       = DEFS->COORD_P;
    Vars->Flag_mantid       = 0;
    Vars->Flag_OFF          = offflag;
    Vars->OFF_polyidx       = -1;
    Vars->mean_dx=Vars->mean_dy=0;
    Vars->min_x = Vars->max_x  =0;
    Vars->min_y = Vars->max_y  =0;

    Set_Vars_Coord_Type = DEFS->COORD_NONE;
    Set_Coord_Mode = DEFS->COORD_VAR;

    /* handle size parameters */
    /* normal use is with xwidth, yheight, zdepth */
    /* if xmin,xmax,ymin,ymax,zmin,zmax are non 0, use them */
    if (fabs(xmin-xmax) == 0)
      { Vars->mxmin = -fabs(xwidth)/2; Vars->mxmax = fabs(xwidth)/2; }
    else
      { if (xmin < xmax) {Vars->mxmin = xmin; Vars->mxmax = xmax;}
        else {Vars->mxmin = xmax; Vars->mxmax = xmin;}
      }
    if (fabs(ymin-ymax) == 0)
      { Vars->mymin = -fabs(yheight)/2; Vars->mymax = fabs(yheight)/2; }
    else
      { if (ymin < ymax) {Vars->mymin = ymin; Vars->mymax = ymax;}
        else {Vars->mymin = ymax; Vars->mymax = ymin;}
      }
    if (fabs(zmin-zmax) == 0)
      { Vars->mzmin = -fabs(zdepth)/2; Vars->mzmax = fabs(zdepth)/2; }
    else
      { if (zmin < zmax) {Vars->mzmin = zmin; Vars->mzmax = zmax; }
        else {Vars->mzmin = zmax; Vars->mzmax = zmin; }
      }

    if (fabs(Vars->mzmax-Vars->mzmin) == 0)
      Vars->Flag_Shape        = DEFS->SHAPE_SQUARE;
    else
      Vars->Flag_Shape        = DEFS->SHAPE_BOX;

    if (Vars->Flag_OFF) {
      Vars->Flag_Shape        = DEFS->SHAPE_OFF;
    }
    
    /* parse option string */

    option_copy = (char*)malloc(strlen(Vars->option)+1);
    if (option_copy == NULL)
    {
      fprintf(stderr,"Monitor_nD: %s cannot allocate 'options' copy (%li). Fatal.\n", Vars->compcurname, (long)strlen(Vars->option));
      exit(-1);
    }

    if (strlen(Vars->option))
    {
      Flag_End = 0;
      strcpy(option_copy, Vars->option);
    }

    if (strstr(Vars->option, "cm2") || strstr(Vars->option, "cm^2")) Vars->Flag_per_cm2 = 1;

    if (strstr(Vars->option, "binary") || strstr(Vars->option, "float"))
      Vars->Flag_Binary_List  = 1;
    if (strstr(Vars->option, "double"))
      Vars->Flag_Binary_List  = 2;

    strcpy(Vars->Coord_Label[0],"Intensity");
    strncpy(Vars->Coord_Var[0],"p",30);
    Vars->Coord_Type[0] = DEFS->COORD_P;
    Vars->Coord_Bin[0] = 1;
    Vars->Coord_Min[0] = 0;
    Vars->Coord_Max[0] = FLT_MAX;

    /* default file name is comp_name+dateID */
    sprintf(Vars->Mon_File, "%s_%li", Vars->compcurname, t);

    carg = 1;
    while((Flag_End == 0) && (carg < 128))
    {

      if (Flag_New_token) /* retain previous token or get a new one */
      {
        if (carg == 1) token=(char *)strtok(option_copy,DEFS->TOKEN_DEL);
        else token=(char *)strtok(NULL,DEFS->TOKEN_DEL);
        if (token == NULL) Flag_End=1;
      }
      Flag_New_token = 1;
      if ((token != NULL) && (strlen(token) != 0))
      {
        char iskeyword=0; /* left at 0 when variables are processed, 1 for modifiers */
        int  old_Mode;
        /* change token to lower case */
        for (i=0; i<strlen(token); i++) token[i]=tolower(token[i]);
        /* first handle option values from preceeding keyword token detected */
        old_Mode = Set_Coord_Mode;
        if (Set_Coord_Mode == DEFS->COORD_MAX)  /* max=%i */
        {
          if (!Flag_All)
            Vars->Coord_Max[Vars->Coord_Number] = atof(token);
          else
            for (i = 0; i <= Vars->Coord_Number; Vars->Coord_Max[i++] = atof(token));
          Set_Coord_Mode = DEFS->COORD_VAR; Flag_All = 0;
        }
        if (Set_Coord_Mode == DEFS->COORD_MIN)  /* min=%i */
        {
          if (!Flag_All)
            Vars->Coord_Min[Vars->Coord_Number] = atof(token);
          else
            for (i = 0; i <= Vars->Coord_Number; Vars->Coord_Min[i++] = atof(token));
          Set_Coord_Mode = DEFS->COORD_MAX;
        }
        if (Set_Coord_Mode == DEFS->COORD_DIM)  /* bins=%i */
        {
          if (!Flag_All)
            Vars->Coord_Bin[Vars->Coord_Number] = atoi(token);
          else
            for (i = 0; i <= Vars->Coord_Number; Vars->Coord_Bin[i++] = atoi(token));
          Set_Coord_Mode = DEFS->COORD_VAR; Flag_All = 0;
        }
        if (Set_Coord_Mode == DEFS->COORD_FIL)  /* file=%s */
        {
          if (!Flag_No) strncpy(Vars->Mon_File,token,128);
          else { strcpy(Vars->Mon_File,""); Vars->Coord_Number = 0; Flag_End = 1;}
          Set_Coord_Mode = DEFS->COORD_VAR;
        }
        if (Set_Coord_Mode == DEFS->COORD_EVNT) /* list=%i */
        {
          if (!strcmp(token, "all") || Flag_All) Vars->Flag_List = 2;
          else { i = (long)ceil(atof(token)); if (i) Vars->Buffer_Block = i;
            Vars->Flag_List = 1; }
          Set_Coord_Mode = DEFS->COORD_VAR; Flag_All = 0;
        }
        if (Set_Coord_Mode == DEFS->COORD_3HE)  /* pressure=%g */
        {
            Vars->He3_pressure = atof(token);
            Set_Coord_Mode = DEFS->COORD_VAR; Flag_All = 0;
        }

        /* now look for general option keywords */
        if (!strcmp(token, "borders"))  {Vars->Flag_With_Borders = 1; iskeyword=1; }
        if (!strcmp(token, "verbose"))  {Vars->Flag_Verbose      = 1; iskeyword=1; }
        if (!strcmp(token, "log"))      {Vars->Flag_log          = 1; iskeyword=1; }
        if (!strcmp(token, "abs"))      {Flag_abs                = 1; iskeyword=1; }
        if (!strcmp(token, "multiple")) {Vars->Flag_Multiple     = 1; iskeyword=1; }
        if (!strcmp(token, "list") || !strcmp(token, "events")) {
          Vars->Flag_List = 1; Set_Coord_Mode = DEFS->COORD_EVNT;  }
        if (!strcmp(token, "limits") || !strcmp(token, "min"))
          Set_Coord_Mode = DEFS->COORD_MIN;
        if (!strcmp(token, "slit") || !strcmp(token, "absorb")) {
          Vars->Flag_Absorb = 1;  iskeyword=1; }
        if (!strcmp(token, "max"))  Set_Coord_Mode = DEFS->COORD_MAX;
        if (!strcmp(token, "bins") || !strcmp(token, "dim")) Set_Coord_Mode = DEFS->COORD_DIM;
        if (!strcmp(token, "file") || !strcmp(token, "filename")) {
          Set_Coord_Mode = DEFS->COORD_FIL;
          if (Flag_No) { strcpy(Vars->Mon_File,""); Vars->Coord_Number = 0; Flag_End = 1; }
        }
        if (!strcmp(token, "unactivate")) {
          Flag_End = 1; Vars->Coord_Number = 0; iskeyword=1; }
        if (!strcmp(token, "all"))    { Flag_All = 1;  iskeyword=1; }
        if (!strcmp(token, "sphere")) { Vars->Flag_Shape = DEFS->SHAPE_SPHERE; iskeyword=1; }
        if (!strcmp(token, "cylinder")) { Vars->Flag_Shape = DEFS->SHAPE_CYLIND; iskeyword=1; }
        if (!strcmp(token, "banana")) { Vars->Flag_Shape = DEFS->SHAPE_BANANA; iskeyword=1; }
        if (!strcmp(token, "square")) { Vars->Flag_Shape = DEFS->SHAPE_SQUARE; iskeyword=1; }
        if (!strcmp(token, "disk"))   { Vars->Flag_Shape = DEFS->SHAPE_DISK; iskeyword=1; }
        if (!strcmp(token, "box"))     { Vars->Flag_Shape = DEFS->SHAPE_BOX; iskeyword=1; }
        if (!strcmp(token, "previous")) { Vars->Flag_Shape = DEFS->SHAPE_PREVIOUS; iskeyword=1; }
        if (!strcmp(token, "parallel")){ Vars->Flag_parallel = 1; iskeyword=1; }
        if (!strcmp(token, "capture")) { Vars->Flag_capture = 1; iskeyword=1; }
        if (!strcmp(token, "auto") && (Flag_auto != -1)) {
          Vars->Flag_Auto_Limits = 1;
          if (Flag_All) Flag_auto = -1;
          else          Flag_auto = 1;
          iskeyword=1; Flag_All=0; }
        if (!strcmp(token, "premonitor")) {
          Vars->Flag_UsePreMonitor = 1; iskeyword=1; }
        if (!strcmp(token, "3He_pressure") || !strcmp(token, "pressure")) {
          Vars->He3_pressure = 3; iskeyword=1; }
        if (!strcmp(token, "no") || !strcmp(token, "not")) { Flag_No = 1;  iskeyword=1; }
        if (!strcmp(token, "signal")) Set_Coord_Mode = DEFS->COORD_SIGNAL;
        if (!strcmp(token, "mantid")) { Vars->Flag_mantid = 1; iskeyword=1; }

        /* Mode has changed: this was a keyword or value  ? */
        if (Set_Coord_Mode != old_Mode) iskeyword=1;

        /* now look for variable names to monitor */
        Set_Vars_Coord_Type = DEFS->COORD_NONE; lmin = 0; lmax = 0;

        if (!strcmp(token, "x"))
          { Set_Vars_Coord_Type = DEFS->COORD_X; strcpy(Set_Vars_Coord_Label,"x [m]"); strcpy(Set_Vars_Coord_Var,"x");
          lmin = Vars->mxmin; lmax = Vars->mxmax;
          Vars->Coord_Min[Vars->Coord_Number+1] = Vars->mxmin;
          Vars->Coord_Max[Vars->Coord_Number+1] = Vars->mxmax;}
        if (!strcmp(token, "y"))
          { Set_Vars_Coord_Type = DEFS->COORD_Y; strcpy(Set_Vars_Coord_Label,"y [m]"); strcpy(Set_Vars_Coord_Var,"y");
          lmin = Vars->mymin; lmax = Vars->mymax;
          Vars->Coord_Min[Vars->Coord_Number+1] = Vars->mymin;
          Vars->Coord_Max[Vars->Coord_Number+1] = Vars->mymax;}
        if (!strcmp(token, "z"))
          { Set_Vars_Coord_Type = DEFS->COORD_Z; strcpy(Set_Vars_Coord_Label,"z [m]"); strcpy(Set_Vars_Coord_Var,"z"); lmin = Vars->mzmin; lmax = Vars->mzmax; }
        if (!strcmp(token, "k") || !strcmp(token, "wavevector"))
          { Set_Vars_Coord_Type = DEFS->COORD_K; strcpy(Set_Vars_Coord_Label,"|k| [Angs-1]"); strcpy(Set_Vars_Coord_Var,"k"); lmin = 0; lmax = 10; }
        if (!strcmp(token, "v"))
          { Set_Vars_Coord_Type = DEFS->COORD_V; strcpy(Set_Vars_Coord_Label,"Velocity [m/s]"); strcpy(Set_Vars_Coord_Var,"v"); lmin = 0; lmax = 1000000; }
        if (!strcmp(token, "t") || !strcmp(token, "time") || !strcmp(token, "tof"))
          { Set_Vars_Coord_Type = DEFS->COORD_T; strcpy(Set_Vars_Coord_Label,"TOF [s]"); strcpy(Set_Vars_Coord_Var,"t"); lmin = 0; lmax = 1.0; }
        if ((!strcmp(token, "p") || !strcmp(token, "i") || !strcmp(token, "intensity") || !strcmp(token, "flux")))
          { Set_Vars_Coord_Type = DEFS->COORD_P;
            strcpy(Set_Vars_Coord_Label,"Intensity");
            strncat(Set_Vars_Coord_Label, " [n/s", 30);
            if (Vars->Flag_per_cm2) strncat(Set_Vars_Coord_Label, "/cm2", 30);
            if (XY > 1 && Vars->Coord_Number)
              strncat(Set_Vars_Coord_Label, "/bin", 30);
            strncat(Set_Vars_Coord_Label, "]", 30);
            strcpy(Set_Vars_Coord_Var,"I");
            lmin = 0; lmax = FLT_MAX;
            if (Flag_auto>0) Flag_auto=0;
          }

        if (!strcmp(token, "vx"))
          { Set_Vars_Coord_Type = DEFS->COORD_VX; strcpy(Set_Vars_Coord_Label,"vx [m/s]"); strcpy(Set_Vars_Coord_Var,"vx"); lmin = -1000; lmax = 1000; }
        if (!strcmp(token, "vy"))
          { Set_Vars_Coord_Type = DEFS->COORD_VY; strcpy(Set_Vars_Coord_Label,"vy [m/s]"); strcpy(Set_Vars_Coord_Var,"vy"); lmin = -1000; lmax = 1000; }
        if (!strcmp(token, "vz"))
          { Set_Vars_Coord_Type = DEFS->COORD_VZ; strcpy(Set_Vars_Coord_Label,"vz [m/s]"); strcpy(Set_Vars_Coord_Var,"vz"); lmin = -10000; lmax = 10000; }
        if (!strcmp(token, "kx"))
          { Set_Vars_Coord_Type = DEFS->COORD_KX; strcpy(Set_Vars_Coord_Label,"kx [Angs-1]"); strcpy(Set_Vars_Coord_Var,"kx"); lmin = -1; lmax = 1; }
        if (!strcmp(token, "ky"))
          { Set_Vars_Coord_Type = DEFS->COORD_KY; strcpy(Set_Vars_Coord_Label,"ky [Angs-1]"); strcpy(Set_Vars_Coord_Var,"ky"); lmin = -1; lmax = 1; }
        if (!strcmp(token, "kz"))
          { Set_Vars_Coord_Type = DEFS->COORD_KZ; strcpy(Set_Vars_Coord_Label,"kz [Angs-1]"); strcpy(Set_Vars_Coord_Var,"kz"); lmin = -10; lmax = 10; }
        if (!strcmp(token, "sx"))
          { Set_Vars_Coord_Type = DEFS->COORD_SX; strcpy(Set_Vars_Coord_Label,"sx [1]"); strcpy(Set_Vars_Coord_Var,"sx"); lmin = -1; lmax = 1; }
        if (!strcmp(token, "sy"))
          { Set_Vars_Coord_Type = DEFS->COORD_SY; strcpy(Set_Vars_Coord_Label,"sy [1]"); strcpy(Set_Vars_Coord_Var,"sy"); lmin = -1; lmax = 1; }
        if (!strcmp(token, "sz"))
          { Set_Vars_Coord_Type = DEFS->COORD_SZ; strcpy(Set_Vars_Coord_Label,"sz [1]"); strcpy(Set_Vars_Coord_Var,"sz"); lmin = -1; lmax = 1; }

        if (!strcmp(token, "energy") || !strcmp(token, "omega") || !strcmp(token, "e"))
          { Set_Vars_Coord_Type = DEFS->COORD_ENERGY; strcpy(Set_Vars_Coord_Label,"Energy [meV]"); strcpy(Set_Vars_Coord_Var,"E"); lmin = 0; lmax = 100; }
        if (!strcmp(token, "lambda") || !strcmp(token, "wavelength") || !strcmp(token, "l"))
          { Set_Vars_Coord_Type = DEFS->COORD_LAMBDA; strcpy(Set_Vars_Coord_Label,"Wavelength [Angs]"); strcpy(Set_Vars_Coord_Var,"L"); lmin = 0; lmax = 100; }
        if (!strcmp(token, "radius") || !strcmp(token, "r"))
          { Set_Vars_Coord_Type = DEFS->COORD_RADIUS; strcpy(Set_Vars_Coord_Label,"Radius [m]"); strcpy(Set_Vars_Coord_Var,"xy"); lmin = 0; lmax = xmax; }
        if (!strcmp(token, "xy"))
          { Set_Vars_Coord_Type = DEFS->COORD_XY; strcpy(Set_Vars_Coord_Label,"Radius (xy) [m]"); strcpy(Set_Vars_Coord_Var,"xy"); lmin = 0; lmax = xmax; }
        if (!strcmp(token, "yz"))
          { Set_Vars_Coord_Type = DEFS->COORD_YZ; strcpy(Set_Vars_Coord_Label,"Radius (yz) [m]"); strcpy(Set_Vars_Coord_Var,"yz"); lmin = 0; lmax = xmax; }
        if (!strcmp(token, "xz"))
          { Set_Vars_Coord_Type = DEFS->COORD_XZ; strcpy(Set_Vars_Coord_Label,"Radius (xz) [m]"); strcpy(Set_Vars_Coord_Var,"xz"); lmin = 0; lmax = xmax; }
        if (!strcmp(token, "vxy"))
          { Set_Vars_Coord_Type = DEFS->COORD_VXY; strcpy(Set_Vars_Coord_Label,"Radial Velocity (xy) [m]"); strcpy(Set_Vars_Coord_Var,"Vxy"); lmin = 0; lmax = 2000; }
        if (!strcmp(token, "kxy"))
          { Set_Vars_Coord_Type = DEFS->COORD_KXY; strcpy(Set_Vars_Coord_Label,"Radial Wavevector (xy) [Angs-1]"); strcpy(Set_Vars_Coord_Var,"Kxy"); lmin = 0; lmax = 2; }
        if (!strcmp(token, "vyz"))
          { Set_Vars_Coord_Type = DEFS->COORD_VYZ; strcpy(Set_Vars_Coord_Label,"Radial Velocity (yz) [m]"); strcpy(Set_Vars_Coord_Var,"Vyz"); lmin = 0; lmax = 2000; }
        if (!strcmp(token, "kyz"))
          { Set_Vars_Coord_Type = DEFS->COORD_KYZ; strcpy(Set_Vars_Coord_Label,"Radial Wavevector (yz) [Angs-1]"); strcpy(Set_Vars_Coord_Var,"Kyz"); lmin = 0; lmax = 2; }
        if (!strcmp(token, "vxz"))
          { Set_Vars_Coord_Type = DEFS->COORD_VXZ; strcpy(Set_Vars_Coord_Label,"Radial Velocity (xz) [m]"); strcpy(Set_Vars_Coord_Var,"Vxz"); lmin = 0; lmax = 2000; }
        if (!strcmp(token, "kxz"))
          { Set_Vars_Coord_Type = DEFS->COORD_KXZ; strcpy(Set_Vars_Coord_Label,"Radial Wavevector (xz) [Angs-1]"); strcpy(Set_Vars_Coord_Var,"Kxz"); lmin = 0; lmax = 2; }
        if (!strcmp(token, "angle") || !strcmp(token, "a"))
          { Set_Vars_Coord_Type = DEFS->COORD_ANGLE; strcpy(Set_Vars_Coord_Label,"Angle [deg]"); strcpy(Set_Vars_Coord_Var,"A"); lmin = -50; lmax = 50; }
        if (!strcmp(token, "hdiv")|| !strcmp(token, "divergence") || !strcmp(token, "xdiv") || !strcmp(token, "hd") || !strcmp(token, "dx"))
          { Set_Vars_Coord_Type = DEFS->COORD_HDIV; strcpy(Set_Vars_Coord_Label,"Hor. Divergence [deg]"); strcpy(Set_Vars_Coord_Var,"hd"); lmin = -5; lmax = 5; }
        if (!strcmp(token, "vdiv") || !strcmp(token, "ydiv") || !strcmp(token, "vd") || !strcmp(token, "dy"))
          { Set_Vars_Coord_Type = DEFS->COORD_VDIV; strcpy(Set_Vars_Coord_Label,"Vert. Divergence [deg]"); strcpy(Set_Vars_Coord_Var,"vd"); lmin = -5; lmax = 5; }
        if (!strcmp(token, "theta") || !strcmp(token, "longitude") || !strcmp(token, "th"))
          { Set_Vars_Coord_Type = DEFS->COORD_THETA; strcpy(Set_Vars_Coord_Label,"Longitude [deg]"); strcpy(Set_Vars_Coord_Var,"th"); lmin = -180; lmax = 180; }
        if (!strcmp(token, "phi") || !strcmp(token, "lattitude") || !strcmp(token, "ph"))
          { Set_Vars_Coord_Type = DEFS->COORD_PHI; strcpy(Set_Vars_Coord_Label,"Lattitude [deg]"); strcpy(Set_Vars_Coord_Var,"ph"); lmin = -90; lmax = 90; }
        if (!strcmp(token, "ncounts") || !strcmp(token, "n") || !strcmp(token, "neutron"))
          { Set_Vars_Coord_Type = DEFS->COORD_NCOUNT; strcpy(Set_Vars_Coord_Label,"Neutron ID [1]"); strcpy(Set_Vars_Coord_Var,"n"); lmin = 0; lmax = mcget_ncount(); if (Flag_auto>0) Flag_auto=0; }
        if (!strcmp(token, "id") || !strcmp(token, "pixel"))
          { Set_Vars_Coord_Type = DEFS->COORD_PIXELID; 
            strcpy(Set_Vars_Coord_Label,"Pixel ID [1]"); 
            strcpy(Set_Vars_Coord_Var,"id"); lmin = 0; lmax = FLT_MAX; 
            if (Flag_auto>0) Flag_auto=0;
            Vars->Flag_List = 1; }
        if (!strcmp(token, "user") || !strcmp(token, "user1") || !strcmp(token, "u1"))
          { Set_Vars_Coord_Type = DEFS->COORD_USER1; strncpy(Set_Vars_Coord_Label,Vars->UserName1,30); strcpy(Set_Vars_Coord_Var,"U1"); lmin = -1e10; lmax = 1e10; }
        if (!strcmp(token, "user2") || !strcmp(token, "u2"))
          { Set_Vars_Coord_Type = DEFS->COORD_USER2; strncpy(Set_Vars_Coord_Label,Vars->UserName2,30); strcpy(Set_Vars_Coord_Var,"U2"); lmin = -1e10; lmax = 1e10; }
        if (!strcmp(token, "user3") || !strcmp(token, "u3"))
          { Set_Vars_Coord_Type = DEFS->COORD_USER3; strncpy(Set_Vars_Coord_Label,Vars->UserName3,30); strcpy(Set_Vars_Coord_Var,"U3"); lmin = -1e10; lmax = 1e10; }

        /* now stores variable keywords detected, if any */
        if (Set_Vars_Coord_Type != DEFS->COORD_NONE)
        {
          int Coord_Number = Vars->Coord_Number;
          if (Vars->Flag_log) { Set_Vars_Coord_Type |= DEFS->COORD_LOG; Vars->Flag_log = 0; }
          if (Flag_abs) { Set_Vars_Coord_Type |= DEFS->COORD_ABS; Flag_abs = 0; }
          if (Flag_auto != 0) { Set_Vars_Coord_Type |= DEFS->COORD_AUTO; 
            if (Flag_auto > 0) Flag_auto = 0; }
          if (Set_Coord_Mode == DEFS->COORD_SIGNAL)
          {
            Coord_Number = 0;
            Vars->Flag_signal = Set_Vars_Coord_Type;
          }
          else
          {
            if (Coord_Number < MONnD_COORD_NMAX)
            { Coord_Number++;
              Vars->Coord_Number = Coord_Number; 
              if (Set_Vars_Coord_Type != DEFS->COORD_PIXELID)
                Vars->Coord_NumberNoPixel++;
            }
            else if (Vars->Flag_Verbose) printf("Monitor_nD: %s reached max number of variables (%i).\n", Vars->compcurname, MONnD_COORD_NMAX);
          }
          Vars->Coord_Type[Coord_Number] = Set_Vars_Coord_Type;
          strncpy(Vars->Coord_Label[Coord_Number], Set_Vars_Coord_Label,30);
          strncpy(Vars->Coord_Var[Coord_Number], Set_Vars_Coord_Var,30);
          if (lmin > lmax) { XY = lmin; lmin=lmax; lmax = XY; }
          Vars->Coord_Min[Coord_Number] = lmin;
          Vars->Coord_Max[Coord_Number] = lmax;
          if (Set_Vars_Coord_Type == DEFS->COORD_NCOUNT || Set_Vars_Coord_Type == DEFS->COORD_PIXELID || Set_Vars_Coord_Type == DEFS->COORD_SIGNAL)
            Vars->Coord_Bin[Coord_Number] = 1;
          else
            Vars->Coord_Bin[Coord_Number] = 20;
          Set_Coord_Mode = DEFS->COORD_VAR;
          Flag_All = 0;
          Flag_No  = 0;
        } else {
          /* no variable name could be read from options */
          if (!iskeyword) {
            if (strcmp(token, "cm2") && strcmp(token, "incoming")
             && strcmp(token, "outgoing") && strcmp(token, "cm2")
             && strcmp(token, "cm^2") && strcmp(token, "float")
             && strcmp(token, "double") && strcmp(token, "binary")
             && strcmp(token, "steradian") && Vars->Flag_Verbose)
              printf("Monitor_nD: %s: unknown '%s' keyword in 'options'. Ignoring.\n", Vars->compcurname, token);
          }
        }
      carg++;
      } /* end if token */
    } /* end while carg */
    free(option_copy);
    if (carg == 128) printf("Monitor_nD: %s reached max number of tokens (%i). Skipping.\n", Vars->compcurname, 128);

    if ((Vars->Flag_Shape == DEFS->SHAPE_BOX) && (fabs(Vars->mzmax - Vars->mzmin) == 0)) Vars->Flag_Shape = DEFS->SHAPE_SQUARE;

    if (Vars->Flag_log == 1) Vars->Coord_Type[0] |= DEFS->COORD_LOG;
    if (Vars->Coord_Number == 0)
    { Vars->Flag_Auto_Limits=0; Vars->Flag_Multiple=0; Vars->Flag_List=0; }

    /* now setting Monitor Name from variable labels */
    strcpy(Vars->Monitor_Label,"");
    XY = 1; /* will contain total bin number */
    for (i = 0; i <= Vars->Coord_Number; i++)
    {
      if (Flag_auto != 0) Vars->Coord_Type[i] |= DEFS->COORD_AUTO;
      Set_Vars_Coord_Type = (Vars->Coord_Type[i] & (DEFS->COORD_LOG-1));
      if ((Set_Vars_Coord_Type == DEFS->COORD_X)
       || (Set_Vars_Coord_Type == DEFS->COORD_Y)
       || (Set_Vars_Coord_Type == DEFS->COORD_Z))
       strcpy(Short_Label[i],"Position");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_THETA)
       || (Set_Vars_Coord_Type == DEFS->COORD_PHI)
       || (Set_Vars_Coord_Type == DEFS->COORD_ANGLE))
       strcpy(Short_Label[i],"Angle");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_XY)
       || (Set_Vars_Coord_Type == DEFS->COORD_XZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_YZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_RADIUS))
       strcpy(Short_Label[i],"Radius");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_VX)
       || (Set_Vars_Coord_Type == DEFS->COORD_VY)
       || (Set_Vars_Coord_Type == DEFS->COORD_VZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_V)
       || (Set_Vars_Coord_Type == DEFS->COORD_VXY)
       || (Set_Vars_Coord_Type == DEFS->COORD_VYZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_VXZ))
       strcpy(Short_Label[i],"Velocity");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_KX)
       || (Set_Vars_Coord_Type == DEFS->COORD_KY)
       || (Set_Vars_Coord_Type == DEFS->COORD_KZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_KXY)
       || (Set_Vars_Coord_Type == DEFS->COORD_KYZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_KXZ)
       || (Set_Vars_Coord_Type == DEFS->COORD_K))
       strcpy(Short_Label[i],"Wavevector");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_SX)
       || (Set_Vars_Coord_Type == DEFS->COORD_SY)
       || (Set_Vars_Coord_Type == DEFS->COORD_SZ))
       strcpy(Short_Label[i],"Spin");
      else
      if ((Set_Vars_Coord_Type == DEFS->COORD_HDIV)
       || (Set_Vars_Coord_Type == DEFS->COORD_VDIV))
       strcpy(Short_Label[i],"Divergence");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_ENERGY)
       strcpy(Short_Label[i],"Energy");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_LAMBDA)
       strcpy(Short_Label[i],"Wavelength");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_NCOUNT)
       strcpy(Short_Label[i],"Neutron_ID");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_PIXELID)
       strcpy(Short_Label[i],"Pixel_ID");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_T)
          strcpy(Short_Label[i],"Time_Of_Flight");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_P)
          strcpy(Short_Label[i],"Intensity");
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_USER1)
          strncpy(Short_Label[i],Vars->UserName1,30);
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_USER2)
          strncpy(Short_Label[i],Vars->UserName2,30);
      else
      if (Set_Vars_Coord_Type == DEFS->COORD_USER3)
          strncpy(Short_Label[i],Vars->UserName3,30);
      else
          strcpy(Short_Label[i],"Unknown");

      if (Vars->Coord_Type[i] & DEFS->COORD_ABS)
      { strcat(Vars->Coord_Label[i]," (abs)"); }

      if (Vars->Coord_Type[i] & DEFS->COORD_LOG)
      { strcat(Vars->Coord_Label[i]," (log)"); }

      strcat(Vars->Monitor_Label, " ");
      strcat(Vars->Monitor_Label, Short_Label[i]);
      XY *= Vars->Coord_Bin[i];

    } /* end for Short_Label */

    if ((Vars->Coord_Type[0] & (DEFS->COORD_LOG-1)) == DEFS->COORD_P) {
      strncat(Vars->Coord_Label[0], " [n/s", 30);
      if (Vars->Flag_per_cm2) strncat(Vars->Coord_Label[0], "/cm2", 30);

      if (XY > 1 && Vars->Coord_Number)
        strncat(Vars->Coord_Label[0], "/bin", 30);
      strncat(Vars->Coord_Label[0], "]", 30);
    }

    /* update label 'signal per bin' if more than 1 bin */
    if (XY > 1 && Vars->Coord_Number) {
      if (Vars->Flag_capture)
        printf("Monitor_nD: %s: Using capture flux weightening on %ld bins.\n"
               "WARNING     Use binned data with caution, and prefer monitor integral value (I,Ierr).\n", Vars->compcurname, (long)XY);
    }

    strcat(Vars->Monitor_Label, " Monitor");
    if (Vars->Flag_Shape == DEFS->SHAPE_SQUARE) strcat(Vars->Monitor_Label, " (Square)");
    if (Vars->Flag_Shape == DEFS->SHAPE_DISK)   strcat(Vars->Monitor_Label, " (Disk)");
    if (Vars->Flag_Shape == DEFS->SHAPE_SPHERE) strcat(Vars->Monitor_Label, " (Sphere)");
    if (Vars->Flag_Shape == DEFS->SHAPE_CYLIND) strcat(Vars->Monitor_Label, " (Cylinder)");
    if (Vars->Flag_Shape == DEFS->SHAPE_BANANA) strcat(Vars->Monitor_Label, " (Banana)");
    if (Vars->Flag_Shape == DEFS->SHAPE_BOX)    strcat(Vars->Monitor_Label, " (Box)");
    if (Vars->Flag_Shape == DEFS->SHAPE_PREVIOUS) strcat(Vars->Monitor_Label, " (on PREVIOUS)");
    if (Vars->Flag_Shape == DEFS->SHAPE_OFF) strcat(Vars->Monitor_Label, " (OFF geometry)");
    if ((Vars->Flag_Shape == DEFS->SHAPE_CYLIND) || (Vars->Flag_Shape == DEFS->SHAPE_BANANA) || (Vars->Flag_Shape == DEFS->SHAPE_SPHERE) || (Vars->Flag_Shape == DEFS->SHAPE_BOX))
    {
      if (strstr(Vars->option, "incoming"))
      {
        Vars->Flag_Shape = abs(Vars->Flag_Shape);
        strcat(Vars->Monitor_Label, " [in]");
      }
      else /* if strstr(Vars->option, "outgoing")) */
      {
        Vars->Flag_Shape = -abs(Vars->Flag_Shape);
        strcat(Vars->Monitor_Label, " [out]");
      }
    }
    if (Vars->Flag_UsePreMonitor == 1)
    {
        strcat(Vars->Monitor_Label, " at ");
        strncat(Vars->Monitor_Label, Vars->UserName1,30);
    }
    if (Vars->Flag_log == 1) strcat(Vars->Monitor_Label, " [log] ");

    /* now allocate memory to store variables in TRACE */

    /* Vars->Coord_Number  0   : intensity or signal
     * Vars->Coord_Number  1:n : detector variables */

    if ((Vars->Coord_NumberNoPixel != 2) && !Vars->Flag_Multiple && !Vars->Flag_List)
    { Vars->Flag_Multiple = 1; /* default is n1D */
      if (Vars->Coord_Number != Vars->Coord_NumberNoPixel) Vars->Flag_List = 1; }

    /* list and auto limits case : Vars->Flag_List or Vars->Flag_Auto_Limits
     * -> Buffer to flush and suppress after Vars->Flag_Auto_Limits
     */
    if ((Vars->Flag_Auto_Limits || Vars->Flag_List) && Vars->Coord_Number)
    { /* Dim : (Vars->Coord_Number+1)*Vars->Buffer_Block matrix (for p, dp) */
      Vars->Mon2D_Buffer = (double *)malloc((Vars->Coord_Number+1)*Vars->Buffer_Block*sizeof(double));
      if (Vars->Mon2D_Buffer == NULL)
      { printf("Monitor_nD: %s cannot allocate Vars->Mon2D_Buffer (%li). No list and auto limits.\n", Vars->compcurname, Vars->Buffer_Block*(Vars->Coord_Number+1)*sizeof(double)); Vars->Flag_List = 0; Vars->Flag_Auto_Limits = 0; }
      else
      {
        for (i=0; i < (Vars->Coord_Number+1)*Vars->Buffer_Block; Vars->Mon2D_Buffer[i++] = (double)0);
      }
      Vars->Buffer_Size = Vars->Buffer_Block;
    }

    /* 1D and n1D case : Vars->Flag_Multiple */
    if (Vars->Flag_Multiple && Vars->Coord_NumberNoPixel)
    { /* Dim : Vars->Coord_Number*Vars->Coord_Bin[i] vectors */
      Vars->Mon2D_N  = (double **)malloc((Vars->Coord_Number)*sizeof(double *));
      Vars->Mon2D_p  = (double **)malloc((Vars->Coord_Number)*sizeof(double *));
      Vars->Mon2D_p2 = (double **)malloc((Vars->Coord_Number)*sizeof(double *));
      if ((Vars->Mon2D_N == NULL) || (Vars->Mon2D_p == NULL) || (Vars->Mon2D_p2 == NULL))
      { fprintf(stderr,"Monitor_nD: %s n1D cannot allocate Vars->Mon2D_N/p/p2 (%li). Fatal.\n", Vars->compcurname, (Vars->Coord_Number)*sizeof(double *)); exit(-1); }
      for (i= 1; i <= Vars->Coord_Number; i++)
      {
        Vars->Mon2D_N[i-1]  = (double *)malloc(Vars->Coord_Bin[i]*sizeof(double));
        Vars->Mon2D_p[i-1]  = (double *)malloc(Vars->Coord_Bin[i]*sizeof(double));
        Vars->Mon2D_p2[i-1] = (double *)malloc(Vars->Coord_Bin[i]*sizeof(double));
        if ((Vars->Mon2D_N == NULL) || (Vars->Mon2D_p == NULL) || (Vars->Mon2D_p2 == NULL))
        { fprintf(stderr,"Monitor_nD: %s n1D cannot allocate %s Vars->Mon2D_N/p/p2[%li] (%li). Fatal.\n", Vars->compcurname, Vars->Coord_Var[i], i, (Vars->Coord_Bin[i])*sizeof(double *)); exit(-1); }
        else
        {
          for (j=0; j < Vars->Coord_Bin[i]; j++ )
          { Vars->Mon2D_N[i-1][j] = (double)0; Vars->Mon2D_p[i-1][j] = (double)0; Vars->Mon2D_p2[i-1][j] = (double)0; }
        }
      }
    }
    else /* 2D case : Vars->Coord_Number==2 and !Vars->Flag_Multiple and !Vars->Flag_List */
    if ((Vars->Coord_NumberNoPixel == 2) && !Vars->Flag_Multiple)
    { /* Dim : Vars->Coord_Bin[1]*Vars->Coord_Bin[2] matrix */
      Vars->Mon2D_N  = (double **)malloc((Vars->Coord_Bin[1])*sizeof(double *));
      Vars->Mon2D_p  = (double **)malloc((Vars->Coord_Bin[1])*sizeof(double *));
      Vars->Mon2D_p2 = (double **)malloc((Vars->Coord_Bin[1])*sizeof(double *));
      if ((Vars->Mon2D_N == NULL) || (Vars->Mon2D_p == NULL) || (Vars->Mon2D_p2 == NULL))
      { fprintf(stderr,"Monitor_nD: %s 2D cannot allocate %s Vars->Mon2D_N/p/p2 (%li). Fatal.\n", Vars->compcurname, Vars->Coord_Var[1], (Vars->Coord_Bin[1])*sizeof(double *)); exit(-1); }
      for (i= 0; i < Vars->Coord_Bin[1]; i++)
      {
        Vars->Mon2D_N[i]  = (double *)malloc(Vars->Coord_Bin[2]*sizeof(double));
        Vars->Mon2D_p[i]  = (double *)malloc(Vars->Coord_Bin[2]*sizeof(double));
        Vars->Mon2D_p2[i] = (double *)malloc(Vars->Coord_Bin[2]*sizeof(double));
        if ((Vars->Mon2D_N == NULL) || (Vars->Mon2D_p == NULL) || (Vars->Mon2D_p2 == NULL))
        { fprintf(stderr,"Monitor_nD: %s 2D cannot allocate %s Vars->Mon2D_N/p/p2[%li] (%li). Fatal.\n", Vars->compcurname, Vars->Coord_Var[1], i, (Vars->Coord_Bin[2])*sizeof(double *)); exit(-1); }
        else
        {
          for (j=0; j < Vars->Coord_Bin[2]; j++ )
          { Vars->Mon2D_N[i][j] = (double)0; Vars->Mon2D_p[i][j] = (double)0; Vars->Mon2D_p2[i][j] = (double)0; }
        }
      }
    }
    else {
      Vars->Mon2D_N = Vars->Mon2D_p = Vars->Mon2D_p2 = NULL;
    }
      /* no Mon2D allocated for
       * (Vars->Coord_Number != 2) && !Vars->Flag_Multiple && Vars->Flag_List */

    Vars->psum  = 0;
    Vars->p2sum = 0;
    Vars->Nsum  = 0;

    Vars->area  = fabs(Vars->mxmax - Vars->mxmin)*fabs(Vars->mymax - Vars->mymin)*1E4; /* in cm**2 for square and box shapes */
    Vars->Sphere_Radius = fabs(Vars->mxmax - Vars->mxmin)/2;
    if ((abs(Vars->Flag_Shape) == DEFS->SHAPE_DISK) || (abs(Vars->Flag_Shape) == DEFS->SHAPE_SPHERE))
    {
      Vars->area = PI*Vars->Sphere_Radius*Vars->Sphere_Radius*1E4; /* disk shapes */
    }


    if (Vars->area == 0 && abs(Vars->Flag_Shape) != DEFS->SHAPE_PREVIOUS ) {
      if (abs(Vars->Flag_Shape) != DEFS->SHAPE_OFF) {  
	Vars->Coord_Number = 0;
      }
    }
    if (Vars->Coord_Number == 0 && Vars->Flag_Verbose)
      printf("Monitor_nD: %s is unactivated (0D)\n", Vars->compcurname);
    Vars->Cylinder_Height = fabs(Vars->mymax - Vars->mymin);

    if (Vars->Flag_Verbose)
    {
      printf("Monitor_nD: %s is a %s.\n", Vars->compcurname, Vars->Monitor_Label);
      printf("Monitor_nD: version %s with options=%s\n", MONITOR_ND_LIB_H, Vars->option);
    }
    
    /* compute the product of bin dimensions for PixelID */
    Vars->Coord_BinProd[0]=1;
    for (i = 1; i <= Vars->Coord_Number; i++)
      Vars->Coord_BinProd[i]=Vars->Coord_Bin[i]*Vars->Coord_BinProd[i-1];
  } /* end Monitor_nD_Init */

/* ========================================================================= */
/* Monitor_nD_Trace: this routine is used to monitor one propagating neutron */
/* return values: 0=neutron was absorbed, -1=neutron was outside bounds, 1=neutron was measured*/
/* ========================================================================= */

int Monitor_nD_Trace(MonitornD_Defines_type *DEFS, MonitornD_Variables_type *Vars)
{

  double  XY=0, pp=0;
  int     retval;
  long    i =0, j =0;
  double  Coord[MONnD_COORD_NMAX];
  long    Coord_Index[MONnD_COORD_NMAX];
  char    While_End   =0;
  long    While_Buffer=0;
  char    Set_Vars_Coord_Type = DEFS->COORD_NONE;
  
  /* the logic below depends mainly on:
       Flag_List:        1=store 1 buffer, 2=list all, 3=re-use buffer 
       Flag_Auto_Limits: 0 (no auto limits/list), 1 (store events into Buffer), 2 (re-emit store events)
   */

  /* Vars->Flag_Auto_Limits=1: buffer full, we read the Buffer, and determine min and max bounds */
  if ((Vars->Buffer_Counter >= Vars->Buffer_Block) && (Vars->Flag_Auto_Limits == 1) && (Vars->Coord_Number > 0))
  {
    /* auto limits case : get limits in Buffer for each variable */
          /* Dim : (Vars->Coord_Number+1)*Vars->Buffer_Block matrix (for p, dp) */
    if (Vars->Flag_Verbose) printf("Monitor_nD: %s getting %li Auto Limits from List (%li events) in TRACE.\n", Vars->compcurname, Vars->Coord_Number, Vars->Buffer_Counter);
    for (i = 1; i <= Vars->Coord_Number; i++)
    {
      if (Vars->Coord_Type[i] & DEFS->COORD_AUTO)
      {
        Vars->Coord_Min[i] =  FLT_MAX;
        Vars->Coord_Max[i] = -FLT_MAX;
        for (j = 0; j < Vars->Buffer_Counter; j++)
        {
          XY = Vars->Mon2D_Buffer[i+j*(Vars->Coord_Number+1)];  /* scanning variables in Buffer */
          if (XY < Vars->Coord_Min[i]) Vars->Coord_Min[i] = XY;
          if (XY > Vars->Coord_Max[i]) Vars->Coord_Max[i] = XY;
        }
        if  (Vars->Flag_Verbose)  
          printf("  %s: min=%g max=%g\n", Vars->Coord_Var[i], Vars->Coord_Min[i], Vars->Coord_Max[i]);
      }
    }
    Vars->Flag_Auto_Limits = 2;  /* pass to 2nd auto limits step (read Buffer and generate new events to store in histograms) */
  } /* end if Flag_Auto_Limits == 1 */

  /* manage realloc for 'list all' if Buffer size exceeded: flush Buffer to file */
  if ((Vars->Buffer_Counter >= Vars->Buffer_Block) && (Vars->Flag_List >= 2))
  {
    if (Vars->Buffer_Size >= 1000000 || Vars->Flag_List == 3)
    { /* save current (possibly append) and re-use Buffer */
      Monitor_nD_Save(DEFS, Vars);
      Vars->Flag_List = 3;
      Vars->Buffer_Block = Vars->Buffer_Size;
      Vars->Buffer_Counter  = 0;
      Vars->Neutron_Counter = 0;
    }
    else
    {
      Vars->Mon2D_Buffer  = (double *)realloc(Vars->Mon2D_Buffer, (Vars->Coord_Number+1)*(Vars->Neutron_Counter+Vars->Buffer_Block)*sizeof(double));
      if (Vars->Mon2D_Buffer == NULL)
            { printf("Monitor_nD: %s cannot reallocate Vars->Mon2D_Buffer[%li] (%li). Skipping.\n", Vars->compcurname, i, (Vars->Neutron_Counter+Vars->Buffer_Block)*sizeof(double)); Vars->Flag_List = 1; }
      else { Vars->Buffer_Counter = 0; Vars->Buffer_Size = Vars->Neutron_Counter+Vars->Buffer_Block; }
    }
  } /* end if Buffer realloc */

  char    outsidebounds=0;
  while (!While_End)
  { /* we generate Coord[] and Coord_index[] from Buffer (auto limits) or passing neutron */
    if ((Vars->Flag_Auto_Limits == 2) && (Vars->Coord_Number > 0))
    { /* Vars->Flag_Auto_Limits == 2: read back from Buffer (Buffer is filled or auto limits have been computed) */
      if (While_Buffer < Vars->Buffer_Block)
      {
        /* first while loop (While_Buffer) */
        /* auto limits case : scan Buffer within limits and store in Mon2D */
        Coord[0] = pp = Vars->Mon2D_Buffer[While_Buffer*(Vars->Coord_Number+1)];

        for (i = 1; i <= Vars->Coord_Number; i++)
        {
          /* scanning variables in Buffer */
          if (Vars->Coord_Bin[i] <= 1) continue;
          XY = (Vars->Coord_Max[i]-Vars->Coord_Min[i]);

          Coord[i] = Vars->Mon2D_Buffer[i+While_Buffer*(Vars->Coord_Number+1)];
          if (XY > 0) Coord_Index[i] = floor((Coord[i]-Vars->Coord_Min[i])*Vars->Coord_Bin[i]/XY);
          else        Coord_Index[i] = 0;
          if (Vars->Flag_With_Borders)
          {
            if (Coord_Index[i] < 0)                   Coord_Index[i] = 0;
            if (Coord_Index[i] >= Vars->Coord_Bin[i]) Coord_Index[i] = Vars->Coord_Bin[i] - 1;
          }
        } /* end for */
        
        /* update the PixelID, we compute it from the previous variables index */
        if (Vars->Coord_NumberNoPixel < Vars->Coord_Number) /* there is a Pixel variable */
        for (i = 1; i <= Vars->Coord_Number; i++) {
          char Set_Vars_Coord_Type = (Vars->Coord_Type[i] & (DEFS->COORD_LOG-1));
          if (Set_Vars_Coord_Type == DEFS->COORD_PIXELID) {
            char flag_outside=0;
            Coord_Index[i] = Coord[i] = 0;
            for (j= 1; j < i; j++) {
              /* not for 1D variables with Bin=1 such as PixelID, NCOUNT, Intensity */
              if (Vars->Coord_Bin[j] == 1) continue; 
              if (0 > Coord_Index[j] || Coord_Index[j] >= Vars->Coord_Bin[j]) {
                flag_outside=1;
                Coord[i] = 0;
                break;
              }
              Coord[i] += Coord_Index[j]*Vars->Coord_BinProd[j-1];
            }
            if (!flag_outside) {
              Vars->Mon2D_Buffer[i+While_Buffer*(Vars->Coord_Number+1)] = Coord[i];
            }
          } /* end if PixelID */
        }
        While_Buffer++;
      } /* end if in Buffer */
      else /* (While_Buffer >= Vars->Buffer_Block) && (Vars->Flag_Auto_Limits == 2) */
      {
        Vars->Flag_Auto_Limits = 0;
        if (!Vars->Flag_List) /* free Buffer not needed anymore (no list to output) */
        { /* Dim : (Vars->Coord_Number+1)*Vars->Buffer_Block matrix (for p, p2) */
          free(Vars->Mon2D_Buffer); Vars->Mon2D_Buffer = NULL;
        }
        if (Vars->Flag_Verbose) printf("Monitor_nD: %s flushed %li Auto Limits from List (%li) in TRACE.\n", Vars->compcurname, Vars->Coord_Number, Vars->Buffer_Counter);
      }
    } /* if Vars->Flag_Auto_Limits == 2 */
    
    if (Vars->Flag_Auto_Limits != 2 || !Vars->Coord_Number) /* Vars->Flag_Auto_Limits == 0 (no auto limits/list) or 1 (store events into Buffer) */
    {
      /* automatically compute area and steradian solid angle when in AUTO mode */
      /* compute the steradian solid angle incoming on the monitor */
      double v;
      v=sqrt(Vars->cvx*Vars->cvx
            +Vars->cvy*Vars->cvy
            +Vars->cvz*Vars->cvz);
      if (Vars->min_x > Vars->cx) Vars->min_x = Vars->cx;
      if (Vars->max_x < Vars->cx) Vars->max_x = Vars->cx;
      if (Vars->min_y > Vars->cy) Vars->min_y = Vars->cy;
      if (Vars->max_y < Vars->cy) Vars->max_y = Vars->cy;
      Vars->mean_p  += Vars->cp;
      if (v) {
        Vars->mean_dx += Vars->cp*fabs(Vars->cvx/v);
        Vars->mean_dy += Vars->cp*fabs(Vars->cvy/v);
      }

      for (i = 0; i <= Vars->Coord_Number; i++)
      { /* handle current neutron : last while */
        XY = 0;
        Set_Vars_Coord_Type = (Vars->Coord_Type[i] & (DEFS->COORD_LOG-1));
        /* get values for variables to monitor */
        if (Set_Vars_Coord_Type == DEFS->COORD_X) XY = Vars->cx;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_Y) XY = Vars->cy;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_Z) XY = Vars->cz;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VX) XY = Vars->cvx;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VY) XY = Vars->cvy;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VZ) XY = Vars->cvz;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KX) XY = V2K*Vars->cvx;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KY) XY = V2K*Vars->cvy;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KZ) XY = V2K*Vars->cvz;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_SX) XY = Vars->csx;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_SY) XY = Vars->csy;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_SZ) XY = Vars->csz;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_T) XY = Vars->ct;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_P) XY = Vars->cp;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_HDIV) XY = RAD2DEG*atan2(Vars->cvx,Vars->cvz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VDIV) XY = RAD2DEG*atan2(Vars->cvy,Vars->cvz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_V) XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_RADIUS)
          XY = sqrt(Vars->cx*Vars->cx+Vars->cy*Vars->cy+Vars->cz*Vars->cz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_XY)
          XY = sqrt(Vars->cx*Vars->cx+Vars->cy*Vars->cy)*(Vars->cx > 0 ? 1 : -1);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_YZ) XY = sqrt(Vars->cy*Vars->cy+Vars->cz*Vars->cz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_XZ)
          XY = sqrt(Vars->cx*Vars->cx+Vars->cz*Vars->cz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VXY) XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VXZ) XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvz*Vars->cvz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_VYZ) XY = sqrt(Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz);
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_K) { XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz);  XY *= V2K; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KXY) { XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy);  XY *= V2K; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KXZ) { XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvz*Vars->cvz);  XY *= V2K; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_KYZ) { XY = sqrt(Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz);  XY *= V2K; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_ENERGY) { XY = Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz;  XY *= VS2E; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_LAMBDA) { XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy+Vars->cvz*Vars->cvz);  XY *= V2K; if (XY != 0) XY = 2*PI/XY; }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_NCOUNT) XY = Vars->Neutron_Counter;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_ANGLE)
        {  XY = sqrt(Vars->cvx*Vars->cvx+Vars->cvy*Vars->cvy);
           if (Vars->cvz != 0)
                XY = RAD2DEG*atan2(XY,Vars->cvz)*(Vars->cx > 0 ? 1 : -1);
           else XY = 0;
        }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_THETA)  { if (Vars->cz != 0) XY = RAD2DEG*atan2(Vars->cx,Vars->cz); }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_PHI) { if (Vars->cz != 0) XY = RAD2DEG*asin(Vars->cy/Vars->cz); }
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_USER1) XY = Vars->UserVariable1;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_USER2) XY = Vars->UserVariable2;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_USER3) XY = Vars->UserVariable3;
        else
        if (Set_Vars_Coord_Type == DEFS->COORD_PIXELID && !Vars->Flag_Auto_Limits) {
          /* compute the PixelID from previous coordinates 
             the PixelID is the product of Coord_Index[i] in the detector geometry 
             pixelID = sum( Coord_Index[j]*prod(Vars->Coord_Bin[1:(j-1)]) )
             
             this does not apply when we store events in the buffer as Coord_Index
             is not set. Then the pixelID will be re-computed during SAVE.
          */
          char flag_outside=0;
          for (j= 1; j < i; j++) {
            /* not for 1D variables with Bin=1 such as PixelID, NCOUNT, Intensity */
            if (Vars->Coord_Bin[j] <= 1) continue; 
            if (0 > Coord_Index[j] || Coord_Index[j] >= Vars->Coord_Bin[j]) { 
              flag_outside=1; XY=0; break;
            }
            XY += Coord_Index[j]*Vars->Coord_BinProd[j-1];
          }
	  if (Vars->Flag_mantid && Vars->Flag_OFF && Vars->OFF_polyidx >=0) XY=Vars->OFF_polyidx;
          if (!flag_outside) XY += Vars->Coord_Min[i];
        }
        
        /* handle 'abs' and 'log' keywords */
        if (Vars->Coord_Type[i] & DEFS->COORD_ABS) XY=fabs(XY);

        if (Vars->Coord_Type[i] & DEFS->COORD_LOG) /* compute log of variable if requested */
        {  if (XY > 0) XY = log(XY)/log(10);
           else        XY = -100; }

        Coord[i] = XY; Coord_Index[i] = 0;
        if (i == 0) { pp = XY; Coord_Index[i] = 0; }
        else {
        /* check bounds for variables which have no automatic limits */
          if ((!Vars->Flag_Auto_Limits || !(Vars->Coord_Type[i] & DEFS->COORD_AUTO)) && Vars->Coord_Bin[i]>1)
          { /* compute index in histograms for each variable to monitor */
            XY = (Vars->Coord_Max[i]-Vars->Coord_Min[i]);
            if (XY > 0) Coord_Index[i] = floor((Coord[i]-Vars->Coord_Min[i])*Vars->Coord_Bin[i]/XY);
            if (Vars->Flag_With_Borders)
            {
              if (Coord_Index[i] >= Vars->Coord_Bin[i]) Coord_Index[i] = Vars->Coord_Bin[i] - 1;
              if (Coord_Index[i] < 0) Coord_Index[i] = 0;
            }
            //if (0 > Coord_Index[i] || Coord_Index[i] >= Vars->Coord_Bin[i])
            //  outsidebounds=1;
          } /* else will get Index later from Buffer when Flag_Auto_Limits == 2 */
        }
        
      } /* end for i */
      While_End = 1;
    }/* end else if Vars->Flag_Auto_Limits == 2 */
    
    /* ====================================================================== */
    /* store n1d/2d neutron from Buffer (Auto_Limits == 2) or current neutron in while */
    if (Vars->Flag_Auto_Limits != 1) /* not when storing auto limits Buffer */
    {
      /* apply per cm2 */
      if (Vars->Flag_per_cm2 && Vars->area != 0)
        pp /= Vars->area;

      /* 2D case : Vars->Coord_Number==2 and !Vars->Flag_Multiple and !Vars->Flag_List */
      if ( Vars->Coord_NumberNoPixel == 2 && !Vars->Flag_Multiple)
      { /* Dim : Vars->Coord_Bin[1]*Vars->Coord_Bin[2] matrix */
        
        i = Coord_Index[1];
        j = Coord_Index[2];
        if (i >= 0 && i < Vars->Coord_Bin[1] && j >= 0 && j < Vars->Coord_Bin[2])
        {
          if (Vars->Mon2D_N) { 
            Vars->Mon2D_N[i][j]++;
            Vars->Mon2D_p[i][j] += pp;
            Vars->Mon2D_p2[i][j] += pp*pp;
          }
        } else {
          outsidebounds=1; 
        }
      } else {
        /* 1D and n1D case : Vars->Flag_Multiple */
        /* Dim : Vars->Coord_Number*Vars->Coord_Bin[i] vectors (intensity is not included) */
          
        for (i= 1; i <= Vars->Coord_Number; i++) {
          j = Coord_Index[i];
          if (j >= 0 && j < Vars->Coord_Bin[i]) {
            if  (Vars->Flag_Multiple && Vars->Mon2D_N) {
              Vars->Mon2D_N[i-1][j]++;
              Vars->Mon2D_p[i-1][j]  += pp;
              Vars->Mon2D_p2[i-1][j] += pp*pp;
            }
          } else { 
            outsidebounds=1;
            break;
          }
        }
      }
    } /* end (Vars->Flag_Auto_Limits != 1) */
    
    if (Vars->Flag_Auto_Limits != 2 && !outsidebounds) /* not when reading auto limits Buffer */
    { /* now store Coord into Buffer (no index needed) if necessary (list or auto limits) */
      if ((Vars->Buffer_Counter < Vars->Buffer_Block) && ((Vars->Flag_List) || (Vars->Flag_Auto_Limits == 1)))
      {
          
        for (i = 0; i <= Vars->Coord_Number; i++)
        {
          Vars->Mon2D_Buffer[i + Vars->Neutron_Counter*(Vars->Coord_Number+1)] = Coord[i];
        }
        Vars->Buffer_Counter++;
        if (Vars->Flag_Verbose && (Vars->Buffer_Counter >= Vars->Buffer_Block) && (Vars->Flag_List == 1)) 
          printf("Monitor_nD: %s %li neutrons stored in List.\n", Vars->compcurname, Vars->Buffer_Counter);
      }
      Vars->Neutron_Counter++;
    } /* end (Vars->Flag_Auto_Limits != 2) */
    
  } /* end while */
  Vars->Nsum++;
  Vars->psum  += pp;
  Vars->p2sum += pp*pp;

  /*determine return value: 1:neutron was in bounds and measured, -1: outside bounds, 0: outside bounds, should be absorbed.*/
  if(outsidebounds){
      if(Vars->Flag_Absorb){
          return 0;
      }else{
          return -1;
      }
  }
  return 1;
} /* end Monitor_nD_Trace */

/* ========================================================================= */
/* Monitor_nD_Save: this routine is used to save data files                  */
/* ========================================================================= */

MCDETECTOR Monitor_nD_Save(MonitornD_Defines_type *DEFS, MonitornD_Variables_type *Vars)
  {
    char   *fname;
    long    i,j;
    double *p0m = NULL;
    double *p1m = NULL;
    double *p2m = NULL;
    char    Coord_X_Label[CHAR_BUF_LENGTH];
    double  min1d, max1d;
    double  min2d, max2d;
    long    bin1d, bin2d;
    char    While_End = 0;
    long    While_Buffer = 0;
    double  XY=0, pp=0;
    double  Coord[MONnD_COORD_NMAX];
    long    Coord_Index[MONnD_COORD_NMAX];
    char    label[CHAR_BUF_LENGTH];
    double  ratio;

    MCDETECTOR detector;

    ratio = 100.0*mcget_run_num()/mcget_ncount();
    if (Vars->Flag_Verbose && Vars->Flag_per_cm2) {
      printf("Monitor_nD: %s: active flat detector area is %g [cm^2], total area is %g [cm^2]\n",
        Vars->compcurname, (Vars->max_x-Vars->min_x)
                          *(Vars->max_y-Vars->min_y)*1E4, Vars->area);
      printf("Monitor_nD: %s: beam solid angle is %g [st] (%g x %g [deg^2])\n",
        Vars->compcurname,
        2*fabs(2*atan(Vars->mean_dx/Vars->mean_p)
         *sin(2*atan(Vars->mean_dy/Vars->mean_p)/2)),
        atan(Vars->mean_dx/Vars->mean_p)*RAD2DEG,
        atan(Vars->mean_dy/Vars->mean_p)*RAD2DEG);
    }

    /* check Buffer flush when end of simulation reached */
    if ((Vars->Buffer_Counter <= Vars->Buffer_Block) && Vars->Flag_Auto_Limits && Vars->Mon2D_Buffer && Vars->Buffer_Counter)
    {
      /* Get Auto Limits */
      if (Vars->Flag_Verbose) printf("Monitor_nD: %s getting %li Auto Limits from List (%li events).\n", Vars->compcurname, Vars->Coord_Number, Vars->Buffer_Counter);

      for (i = 1; i <= Vars->Coord_Number; i++)
      {
        if ((Vars->Coord_Type[i] & DEFS->COORD_AUTO) && Vars->Coord_Bin[i] > 1)
        {
          Vars->Coord_Min[i] = FLT_MAX;
          Vars->Coord_Max[i] = -FLT_MAX;
          for (j = 0; j < Vars->Buffer_Counter; j++)
          {
            XY = Vars->Mon2D_Buffer[i+j*(Vars->Coord_Number+1)];  /* scanning variables in Buffer */
            if (XY < Vars->Coord_Min[i]) Vars->Coord_Min[i] = XY;
            if (XY > Vars->Coord_Max[i]) Vars->Coord_Max[i] = XY;
          }
          if  (Vars->Flag_Verbose)  
            printf("  %s: min=%g max=%g in %li bins\n", Vars->Coord_Var[i], Vars->Coord_Min[i], Vars->Coord_Max[i], Vars->Coord_Bin[i]);
        }
      }
      Vars->Flag_Auto_Limits = 2;  /* pass to 2nd auto limits step */
      Vars->Buffer_Block = Vars->Buffer_Counter;

      while (!While_End)
      { /* we generate Coord[] and Coord_index[] from Buffer (auto limits) */
        /* simulation ended before Buffer was filled. Limits have to be computed, and stored events must be sent into histograms */
        
        if (While_Buffer < Vars->Buffer_Block)
        {
          /* first while loops (While_Buffer) */
          Coord[0] = Vars->Mon2D_Buffer[While_Buffer*(Vars->Coord_Number+1)];

          /* auto limits case : scan Buffer within limits and store in Mon2D */
          for (i = 1; i <= Vars->Coord_Number; i++)
          {
            /* scanning variables in Buffer */
            if (Vars->Coord_Bin[i] <= 1) Coord_Index[i] = 0;
            else {
              XY = (Vars->Coord_Max[i]-Vars->Coord_Min[i]);
              Coord[i] = Vars->Mon2D_Buffer[i+While_Buffer*(Vars->Coord_Number+1)];
              if (XY > 0) Coord_Index[i] = floor((Coord[i]-Vars->Coord_Min[i])*Vars->Coord_Bin[i]/XY);
              else Coord_Index[i] = 0;
              if (Vars->Flag_With_Borders)
              {
                if (Coord_Index[i] < 0) Coord_Index[i] = 0;
                if (Coord_Index[i] >= Vars->Coord_Bin[i]) Coord_Index[i] = Vars->Coord_Bin[i] - 1;
              }
            }
          } /* end for */

          /* update the PixelID, we compute it from the previous variables index */
          for (i = 1; i <= Vars->Coord_Number; i++) {
            char Set_Vars_Coord_Type = (Vars->Coord_Type[i] & (DEFS->COORD_LOG-1));
            if (Set_Vars_Coord_Type == DEFS->COORD_PIXELID) {
              char outsidebounds=0;
              Coord_Index[i] = Coord[i] = 0;
              for (j= 1; j < i; j++) {
                /* not for 1D variables with Bin=1 such as PixelID, NCOUNT, Intensity */
                if (Vars->Coord_Bin[j] == 1) continue; 
                if (0 > Coord_Index[j] || Coord_Index[j] >= Vars->Coord_Bin[j]) {
                  outsidebounds=1;
                  Coord[i] = 0;
                  break;
                }
                Coord[i] += Coord_Index[j]*Vars->Coord_BinProd[j-1];
              }
              if (!outsidebounds) {
                Vars->Mon2D_Buffer[i+While_Buffer*(Vars->Coord_Number+1)] = Coord[i];
              }
            } /* end if PixelID */
          }
          While_Buffer++;
        } /* end if in Buffer */
        else /* (While_Buffer >= Vars->Buffer_Block) && (Vars->Flag_Auto_Limits == 2) */
        {
          Vars->Flag_Auto_Limits = 0;
          While_End = 1;
          if (Vars->Flag_Verbose) printf("Monitor_nD: %s flushed %li Auto Limits from List (%li).\n", Vars->compcurname, Vars->Coord_Number, Vars->Buffer_Counter);
        }

        /* store n1d/2d section from Buffer */

        pp = Coord[0];
        /* apply per cm2 or per st */
        if (Vars->Flag_per_cm2 && Vars->area      != 0)
          pp /= Vars->area;
        
        /* 2D case : Vars->Coord_Number==2 and !Vars->Flag_Multiple and !Vars->Flag_List */
        if (!Vars->Flag_Multiple && Vars->Coord_NumberNoPixel == 2)
        { /* Dim : Vars->Coord_Bin[1]*Vars->Coord_Bin[2] matrix */
          i = Coord_Index[1];
          j = Coord_Index[2];
          if (i >= 0 && i < Vars->Coord_Bin[1] && j >= 0 && j < Vars->Coord_Bin[2])
          {
            if (Vars->Mon2D_N) {
              Vars->Mon2D_N[i][j]++;
              Vars->Mon2D_p[i][j] += pp;
              Vars->Mon2D_p2[i][j] += pp*pp;
            }
          } else if (Vars->Flag_Absorb) pp=0;
        }
        else
        /* 1D and n1D case : Vars->Flag_Multiple */
        { /* Dim : Vars->Coord_Number*Vars->Coord_Bin[i] vectors (intensity is not included) */
          for (i= 1; i <= Vars->Coord_Number; i++)
          {
            j = Coord_Index[i];
            if (j >= 0 && j < Vars->Coord_Bin[i])
            {
              if (Vars->Flag_Multiple && Vars->Mon2D_N) {
                Vars->Mon2D_N[i-1][j]++;
                Vars->Mon2D_p[i-1][j] += pp;
                Vars->Mon2D_p2[i-1][j] += pp*pp;
              }
            } else if (Vars->Flag_Absorb) {
              pp=0; break;
            }
          }
        } /* end store 2D/1D */
        
      } /* end while */
    } /* end Force Get Limits */

    /* write output files (sent to file as p[i*n + j] vectors) */
    if (Vars->Coord_Number == 0)
    {
      double Nsum;
      double psum, p2sum;
      Nsum = Vars->Nsum;
      psum = Vars->psum;
      p2sum= Vars->p2sum;
      if (Vars->Flag_signal != DEFS->COORD_P && Nsum > 0)
      { psum /=Nsum; p2sum /= Nsum*Nsum; }
      /* DETECTOR_OUT_0D(Vars->Monitor_Label, Vars->Nsum, Vars->psum, Vars->p2sum); */
      detector = mcdetector_out_0D(Vars->Monitor_Label, Nsum, psum, p2sum, Vars->compcurname, Vars->compcurpos);
    }
    else
    if (strlen(Vars->Mon_File) > 0)
    {
      fname = (char*)malloc(strlen(Vars->Mon_File)+10*Vars->Coord_Number);
      if (Vars->Flag_List && Vars->Mon2D_Buffer) /* List: DETECTOR_OUT_2D */
      {
       
        if (Vars->Flag_List >= 2) Vars->Buffer_Size = Vars->Neutron_Counter;
        if (Vars->Buffer_Size >= Vars->Neutron_Counter)
          Vars->Buffer_Size = Vars->Neutron_Counter;
        strcpy(fname,Vars->Mon_File);
        if (strchr(Vars->Mon_File,'.') == NULL) strcat(fname, "_list");

        strcpy(Coord_X_Label,"");
        for (i= 0; i <= Vars->Coord_Number; i++)
        {
          strcat(Coord_X_Label, Vars->Coord_Var[i]);
          strcat(Coord_X_Label, " ");
          if (strchr(Vars->Mon_File,'.') == NULL)
          { strcat(fname, "."); strcat(fname, Vars->Coord_Var[i]); }
        }
        if (Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s List (%lix%li).\n", Vars->compcurname, fname,bin2d,bin1d);

        /* handle the type of list output */
        strcpy(label, Vars->Monitor_Label);
        
        detector = mcdetector_out_list(
              label, "List of neutron events", Coord_X_Label,
              -Vars->Buffer_Size, Vars->Coord_Number+1,
              Vars->Mon2D_Buffer,
              fname, Vars->compcurname, Vars->compcurpos);
      }
      if (Vars->Flag_Multiple) /* n1D: DETECTOR_OUT_1D */
      {
        for (i= 0; i < Vars->Coord_Number; i++)
        {

          strcpy(fname,Vars->Mon_File);
          if (strchr(Vars->Mon_File,'.') == NULL)
          { strcat(fname, "."); strcat(fname, Vars->Coord_Var[i+1]); }
          sprintf(Coord_X_Label, "%s monitor", Vars->Coord_Label[i+1]);
          strcpy(label, Coord_X_Label);
          if (Vars->Coord_Bin[i+1] > 0) { /* 1D monitor */
            if (Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s 1D (%li).\n", Vars->compcurname, fname, Vars->Coord_Bin[i+1]);
            min1d = Vars->Coord_Min[i+1];
            max1d = Vars->Coord_Max[i+1];
            if (min1d == max1d) max1d = min1d+1e-6;
            p1m = (double *)malloc(Vars->Coord_Bin[i+1]*sizeof(double));
            p2m = (double *)malloc(Vars->Coord_Bin[i+1]*sizeof(double));
            if (p2m == NULL) /* use Raw Buffer line output */
            {
              if (Vars->Flag_Verbose) printf("Monitor_nD: %s cannot allocate memory for output. Using raw data.\n", Vars->compcurname);
              if (p1m != NULL) free(p1m);
              detector = mcdetector_out_1D(
              label,
              Vars->Coord_Label[i+1],
              Vars->Coord_Label[0],
              Vars->Coord_Var[i+1],
              min1d, max1d,
              Vars->Coord_Bin[i+1],
              Vars->Mon2D_N[i],Vars->Mon2D_p[i],Vars->Mon2D_p2[i],
              fname, Vars->compcurname, Vars->compcurpos);
            } /* if (p2m == NULL) */
            else
            {
              if (Vars->Flag_log != 0)
              {
                XY = FLT_MAX;
                for (j=0; j < Vars->Coord_Bin[i+1]; j++) /* search min of signal */
                  if ((XY > Vars->Mon2D_p[i][j]) && (Vars->Mon2D_p[i][j] > 0)) XY = Vars->Mon2D_p[i][j];
                if (XY <= 0) XY = -log(FLT_MAX)/log(10); else XY = log(XY)/log(10)-1;
              } /* if */

              for (j=0; j < Vars->Coord_Bin[i+1]; j++)
              {
                p1m[j] = Vars->Mon2D_p[i][j];
                p2m[j] = Vars->Mon2D_p2[i][j];
                if (Vars->Flag_signal != DEFS->COORD_P && Vars->Mon2D_N[i][j] > 0)
                { /* normalize mean signal to the number of events */
                  p1m[j] /= Vars->Mon2D_N[i][j];
                  p2m[j] /= Vars->Mon2D_N[i][j]*Vars->Mon2D_N[i][j];
                }
                if (Vars->Flag_log != 0)
                {
                  if ((p1m[j] > 0) && (p2m[j] > 0))
                  {
                    p2m[j] /= p1m[j]*p1m[j];
                    p1m[j] = log(p1m[j])/log(10);
                  }
                  else
                  {
                    p1m[j] = XY;
                    p2m[j] = 0;
                  }
                }
              } /* for */
              detector = mcdetector_out_1D(
                label,
                Vars->Coord_Label[i+1],
                Vars->Coord_Label[0],
                Vars->Coord_Var[i+1],
                min1d, max1d,
                Vars->Coord_Bin[i+1],
                Vars->Mon2D_N[i],p1m,p2m,
                fname, Vars->compcurname, Vars->compcurpos);

            } /* else */
            /* comment out 'free memory' lines to avoid loosing arrays if
               'detector' structure is used by other instrument parts
            if (p1m != NULL) free(p1m); p1m=NULL;
            if (p2m != NULL) free(p2m); p2m=NULL;
            */
          } else { /* 0d monitor */
            detector = mcdetector_out_0D(label, Vars->Mon2D_p[i][0], Vars->Mon2D_p2[i][0], Vars->Mon2D_N[i][0], Vars->compcurname, Vars->compcurpos);
          }


        } /* for */
      } /* if 1D */
      else
      if (Vars->Coord_NumberNoPixel == 2)  /* 2D: DETECTOR_OUT_2D */
      {
        strcpy(fname,Vars->Mon_File);

        p0m = (double *)malloc(Vars->Coord_Bin[1]*Vars->Coord_Bin[2]*sizeof(double));
        p1m = (double *)malloc(Vars->Coord_Bin[1]*Vars->Coord_Bin[2]*sizeof(double));
        p2m = (double *)malloc(Vars->Coord_Bin[1]*Vars->Coord_Bin[2]*sizeof(double));
        if (p2m == NULL)
        {
          if (Vars->Flag_Verbose) printf("Monitor_nD: %s cannot allocate memory for 2D array (%li). Skipping.\n", Vars->compcurname, 3*Vars->Coord_Bin[1]*Vars->Coord_Bin[2]*sizeof(double));
          /* comment out 'free memory' lines to avoid loosing arrays if
               'detector' structure is used by other instrument parts
          if (p0m != NULL) free(p0m);
          if (p1m != NULL) free(p1m);
          */
        }
        else
        {
          if (Vars->Flag_log != 0)
          {
            XY = FLT_MAX;
            for (i= 0; i < Vars->Coord_Bin[1]; i++)
              for (j= 0; j < Vars->Coord_Bin[2]; j++) /* search min of signal */
                if ((XY > Vars->Mon2D_p[i][j]) && (Vars->Mon2D_p[i][j]>0)) XY = Vars->Mon2D_p[i][j];
            if (XY <= 0) XY = -log(FLT_MAX)/log(10); else XY = log(XY)/log(10)-1;
          }
          for (i= 0; i < Vars->Coord_Bin[1]; i++)
          {
            for (j= 0; j < Vars->Coord_Bin[2]; j++)
            {
              long index;
              index = j + i*Vars->Coord_Bin[2];
              p0m[index] = Vars->Mon2D_N[i][j];
              p1m[index] = Vars->Mon2D_p[i][j];
              p2m[index] = Vars->Mon2D_p2[i][j];
              if (Vars->Flag_signal != DEFS->COORD_P && p0m[index] > 0)
              {
                  p1m[index] /= p0m[index];
                  p2m[index] /= p0m[index]*p0m[index];
              }

              if (Vars->Flag_log != 0)
              {
                if ((p1m[index] > 0) && (p2m[index] > 0))
                {
                  p2m[index] /= (p1m[index]*p1m[index]);
                  p1m[index] = log(p1m[index])/log(10);

                }
                else
                {
                  p1m[index] = XY;
                  p2m[index] = 0;
                }
              }
            }
          }
          if (strchr(Vars->Mon_File,'.') == NULL)
          { strcat(fname, "."); strcat(fname, Vars->Coord_Var[1]);
              strcat(fname, "_"); strcat(fname, Vars->Coord_Var[2]); }
          if (Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s 2D (%lix%li).\n", Vars->compcurname, fname, Vars->Coord_Bin[1], Vars->Coord_Bin[2]);

          min1d = Vars->Coord_Min[1];
          max1d = Vars->Coord_Max[1];
          if (min1d == max1d) max1d = min1d+1e-6;
          min2d = Vars->Coord_Min[2];
          max2d = Vars->Coord_Max[2];
          if (min2d == max2d) max2d = min2d+1e-6;
          strcpy(label, Vars->Monitor_Label);
          if (Vars->Coord_Bin[1]*Vars->Coord_Bin[2] > 1
           && Vars->Flag_signal == DEFS->COORD_P)
            strcat(label, " per bin");

          detector = mcdetector_out_2D(
            label,
            Vars->Coord_Label[1],
            Vars->Coord_Label[2],
            min1d, max1d,
            min2d, max2d,
            Vars->Coord_Bin[1],
            Vars->Coord_Bin[2],
            p0m,p1m,p2m,
            fname, Vars->compcurname, Vars->compcurpos);

          /* comment out 'free memory' lines to avoid loosing arrays if
               'detector' structure is used by other instrument parts
          if (p0m != NULL) free(p0m);
          if (p1m != NULL) free(p1m);
          if (p2m != NULL) free(p2m);
          */
        }
      }
      free(fname);
    }
    return(detector);
  } /* end Monitor_nD_Save */

/* ========================================================================= */
/* Monitor_nD_Finally: this routine is used to free memory                   */
/* ========================================================================= */

void Monitor_nD_Finally(MonitornD_Defines_type *DEFS,
  MonitornD_Variables_type *Vars)
  {
    int i;

    /* Now Free memory Mon2D.. */
    if ((Vars->Flag_Auto_Limits || Vars->Flag_List) && Vars->Coord_Number)
    { /* Dim : (Vars->Coord_Number+1)*Vars->Buffer_Block matrix (for p, dp) */
      if (Vars->Mon2D_Buffer != NULL) free(Vars->Mon2D_Buffer);
    }

    /* 1D and n1D case : Vars->Flag_Multiple */
    if (Vars->Flag_Multiple && Vars->Coord_Number)
    { /* Dim : Vars->Coord_Number*Vars->Coord_Bin[i] vectors */
      for (i= 0; i < Vars->Coord_Number; i++)
      {
        free(Vars->Mon2D_N[i]);
        free(Vars->Mon2D_p[i]);
        free(Vars->Mon2D_p2[i]);
      }
      free(Vars->Mon2D_N);
      free(Vars->Mon2D_p);
      free(Vars->Mon2D_p2);
    }


    /* 2D case : Vars->Coord_Number==2 and !Vars->Flag_Multiple and !Vars->Flag_List */
    if ((Vars->Coord_NumberNoPixel == 2) && !Vars->Flag_Multiple)
    { /* Dim : Vars->Coord_Bin[1]*Vars->Coord_Bin[2] matrix */
      for (i= 0; i < Vars->Coord_Bin[1]; i++)
      {
        free(Vars->Mon2D_N[i]);
        free(Vars->Mon2D_p[i]);
        free(Vars->Mon2D_p2[i]);
      }
      free(Vars->Mon2D_N);
      free(Vars->Mon2D_p);
      free(Vars->Mon2D_p2);
    }
  } /* end Monitor_nD_Finally */

/* ========================================================================= */
/* Monitor_nD_McDisplay: this routine is used to display component           */
/* ========================================================================= */

void Monitor_nD_McDisplay(MonitornD_Defines_type *DEFS,
  MonitornD_Variables_type *Vars)
  {
    double radius, h;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
    int    i;
    double hdiv_min=-180, hdiv_max=180, vdiv_min=-90, vdiv_max=90;
    char   restricted = 0;

    radius = Vars->Sphere_Radius;
    h = Vars->Cylinder_Height;
    xmin = Vars->mxmin;
    xmax = Vars->mxmax;
    ymin = Vars->mymin;
    ymax = Vars->mymax;
    zmin = Vars->mzmin;
    zmax = Vars->mzmax;

    /* determine if there are angular limits set at start (no auto) in coord_types
     * cylinder/banana: look for hdiv
     * sphere: look for angle, radius (->atan2(val,radius)), hdiv, vdiv
     * this activates a 'restricted' flag, to draw a region as blades on cylinder/sphere
     */
    for (i= 0; i <= Vars->Coord_Number; i++)
    {
      int Set_Vars_Coord_Type;
      Set_Vars_Coord_Type = (Vars->Coord_Type[i] & (DEFS->COORD_LOG-1));
      if (Set_Vars_Coord_Type == DEFS->COORD_HDIV || Set_Vars_Coord_Type == DEFS->COORD_THETA)
      { hdiv_min = Vars->Coord_Min[i]; hdiv_max = Vars->Coord_Max[i]; restricted = 1; }
      else if (Set_Vars_Coord_Type == DEFS->COORD_VDIV || Set_Vars_Coord_Type == DEFS->COORD_PHI)
      { vdiv_min = Vars->Coord_Min[i]; vdiv_max = Vars->Coord_Max[i];restricted = 1;  }
      else if (Set_Vars_Coord_Type == DEFS->COORD_ANGLE)
      { hdiv_min = vdiv_min = Vars->Coord_Min[i];
        hdiv_max = vdiv_max = Vars->Coord_Max[i];
        restricted = 1; }
      else if (Set_Vars_Coord_Type == DEFS->COORD_RADIUS)
      { double angle;
        angle = RAD2DEG*atan2(Vars->Coord_Max[i], radius);
        hdiv_min = vdiv_min = angle;
        hdiv_max = vdiv_max = angle;
        restricted = 1; }
      else if (Set_Vars_Coord_Type == DEFS->COORD_Y && abs(Vars->Flag_Shape) == DEFS->SHAPE_SPHERE)
      {
        vdiv_min = atan2(ymin,radius)*RAD2DEG;
        vdiv_max = atan2(ymax,radius)*RAD2DEG;
        restricted = 1;
      }
    }
    /* full sphere */
    if ((!restricted && (abs(Vars->Flag_Shape) == DEFS->SHAPE_SPHERE))
    || abs(Vars->Flag_Shape) == DEFS->SHAPE_PREVIOUS)
    {
      mcdis_magnify("");
      mcdis_circle("xy",0,0,0,radius);
      mcdis_circle("xz",0,0,0,radius);
      mcdis_circle("yz",0,0,0,radius);
    }
    /* banana/cylinder/sphere portion */
    else
    if (restricted && ((abs(Vars->Flag_Shape) == DEFS->SHAPE_CYLIND)
                    || (abs(Vars->Flag_Shape) == DEFS->SHAPE_BANANA)
                    || (abs(Vars->Flag_Shape) == DEFS->SHAPE_SPHERE)))
    {
      int NH=24, NV=24;
      int ih, iv;
      double width, height;
      int issphere;
      issphere = (abs(Vars->Flag_Shape) == DEFS->SHAPE_SPHERE);
      width = (hdiv_max-hdiv_min)/NH;
      if (!issphere) NV=1; /* cylinder has vertical axis */
      else height= (vdiv_max-vdiv_min)/NV;
      
      /* check width and height of elements (sphere) to make sure the nb
         of plates remains limited */
      if (width < 10  && NH > 1) { width = 10;  NH=(hdiv_max-hdiv_min)/width; width=(hdiv_max-hdiv_min)/NH; }
      if (height < 10 && NV > 1) { height = 10; NV=(vdiv_max-vdiv_min)/height; height= (vdiv_max-vdiv_min)/NV; }
      
      mcdis_magnify("xyz");
      for(ih = 0; ih < NH; ih++)
        for(iv = 0; iv < NV; iv++)
        {
          double theta0, phi0, theta1, phi1;          /* angles in spherical coordinates */
          double x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3; /* vertices at plate edges */
          phi0 = (hdiv_min+ width*ih-90)*DEG2RAD;        /* in xz plane */
          phi1 = (hdiv_min+ width*(ih+1)-90)*DEG2RAD;
          if (issphere)
          {
            theta0= (vdiv_min+height* iv + 90)   *DEG2RAD; /* in vertical plane */
            theta1= (vdiv_min+height*(iv+1) + 90)*DEG2RAD;
            if (y0 < ymin) y0=ymin; 
            if (y0 > ymax) y0=ymax;
            if (y1 < ymin) y1=ymin; 
            if (y1 > ymax) y1=ymax;
            
            y0 = -radius*cos(theta0);            /* z with Z vertical */
            y1 = -radius*cos(theta1);
            if (y0 < ymin) y0=ymin;
            if (y0 > ymax) y0=ymax;
            if (y1 < ymin) y1=ymin;
            if (y1 > ymax) y1=ymax;
          } else {
            y0 = ymin;
            y1 = ymax;
            theta0=theta1=90*DEG2RAD;
          }

          x0 = radius*sin(theta0)*cos(phi0); /* x with Z vertical */
          z0 =-radius*sin(theta0)*sin(phi0); /* y with Z vertical */
          x1 = radius*sin(theta1)*cos(phi0); 
          z1 =-radius*sin(theta1)*sin(phi0);
          x2 = radius*sin(theta1)*cos(phi1); 
          z2 =-radius*sin(theta1)*sin(phi1);
          x3 = radius*sin(theta0)*cos(phi1); 
          z3 =-radius*sin(theta0)*sin(phi1);
          y2 = y1; y3 = y0;

          mcdis_multiline(5,
            x0,y0,z0,
            x1,y1,z1,
            x2,y2,z2,
            x3,y3,z3,
            x0,y0,z0);
        }
      if (Vars->Flag_mantid) {
	/* First define the base pixel type */
	double dt, dy;
	dt = (Vars->Coord_Max[1]-Vars->Coord_Min[1])/Vars->Coord_Bin[1];
	dy = (Vars->Coord_Max[2]-Vars->Coord_Min[2])/Vars->Coord_Bin[2];
	printf("MANTID_BANANA_DET:  %g, %g, %g, %g, %g, %li, %li, %g\n", radius, 
	       Vars->Coord_Min[1],Vars->Coord_Max[1], Vars->Coord_Min[2],Vars->Coord_Max[2], Vars->Coord_Bin[1], Vars->Coord_Bin[2], Vars->Coord_Min[4]); 
      }
    }
    /* disk (circle) */
    else
    if (abs(Vars->Flag_Shape) == DEFS->SHAPE_DISK)
    {
      mcdis_magnify("");
      mcdis_circle("xy",0,0,0,radius);
    }
    /* rectangle (square) */
    else
    if (abs(Vars->Flag_Shape) == DEFS->SHAPE_SQUARE)
    {
      mcdis_magnify("xy");
      mcdis_multiline(5, (double)xmin, (double)ymin, 0.0,
             (double)xmax, (double)ymin, 0.0,
             (double)xmax, (double)ymax, 0.0,
             (double)xmin, (double)ymax, 0.0,
             (double)xmin, (double)ymin, 0.0);
      
      if (Vars->Flag_mantid) {
	/* First define the base pixel type */
	double dx, dy;
	dx = (Vars->Coord_Max[1]-Vars->Coord_Min[1])/Vars->Coord_Bin[1];
	dy = (Vars->Coord_Max[2]-Vars->Coord_Min[2])/Vars->Coord_Bin[2];
	printf("MANTID_RECTANGULAR_DET:  %g, %g, %g, %g, %li, %li, %g\n", 
	       Vars->Coord_Min[1],Vars->Coord_Max[1], Vars->Coord_Min[2],Vars->Coord_Max[2], Vars->Coord_Bin[1], Vars->Coord_Bin[2], Vars->Coord_Min[4]);
      }
    }
    /* full cylinder/banana */
    else
    if (!restricted && ((abs(Vars->Flag_Shape) == DEFS->SHAPE_CYLIND) || (abs(Vars->Flag_Shape) == DEFS->SHAPE_BANANA)))
    {
      mcdis_magnify("xyz");
      mcdis_circle("xz", 0,  h/2.0, 0, radius);
      mcdis_circle("xz", 0, -h/2.0, 0, radius);
      mcdis_line(-radius, -h/2.0, 0, -radius, +h/2.0, 0);
      mcdis_line(+radius, -h/2.0, 0, +radius, +h/2.0, 0);
      mcdis_line(0, -h/2.0, -radius, 0, +h/2.0, -radius);
      mcdis_line(0, -h/2.0, +radius, 0, +h/2.0, +radius);
    }
    else
    /* box */
    if (abs(Vars->Flag_Shape) == DEFS->SHAPE_BOX)
    {
      mcdis_magnify("xyz");
      mcdis_multiline(5, xmin, ymin, zmin,
                   xmax, ymin, zmin,
                   xmax, ymax, zmin,
                   xmin, ymax, zmin,
                   xmin, ymin, zmin);
      mcdis_multiline(5, xmin, ymin, zmax,
                   xmax, ymin, zmax,
                   xmax, ymax, zmax,
                   xmin, ymax, zmax,
                   xmin, ymin, zmax);
      mcdis_line(xmin, ymin, zmin, xmin, ymin, zmax);
      mcdis_line(xmax, ymin, zmin, xmax, ymin, zmax);
      mcdis_line(xmin, ymax, zmin, xmin, ymax, zmax);
      mcdis_line(xmax, ymax, zmin, xmax, ymax, zmax);
    }
  } /* end Monitor_nD_McDisplay */

/* end of monitor_nd-lib.c */

#line 9386 "./ThALES_resolution_v2.c"

/* Instrument parameters. */
MCNUM mcipThALES_dE;
MCNUM mcipA3;
MCNUM mcipA4;
MCNUM mcipEi;
MCNUM mcipEf;
MCNUM mcipq_x_elastic;
MCNUM mcipq_z_elastic;
MCNUM mcipSAMPLE;

#define mcNUMIPAR 8
int mcnumipar = 8;
struct mcinputtable_struct mcinputtable[mcNUMIPAR+1] = {
  "ThALES_dE", &mcipThALES_dE, instr_type_double, "0.5", 
  "A3", &mcipA3, instr_type_double, "0", 
  "A4", &mcipA4, instr_type_double, "20", 
  "Ei", &mcipEi, instr_type_double, "5", 
  "Ef", &mcipEf, instr_type_double, "5", 
  "q_x_elastic", &mcipq_x_elastic, instr_type_double, "1.3139", 
  "q_z_elastic", &mcipq_z_elastic, instr_type_double, "0.1460", 
  "SAMPLE", &mcipSAMPLE, instr_type_double, "0", 
  NULL, NULL, instr_type_double, ""
};

/* User declarations from instrument definition. */
#define mccompcurname  ThALES_double_peak10
#define mccompcurtype  INSTRUMENT
#define mccompcurindex 0
#define mcposaThALES_double_peak10 coords_set(0,0,0)
#define ThALES_dE mcipThALES_dE
#define A3 mcipA3
#define A4 mcipA4
#define Ei mcipEi
#define Ef mcipEf
#define q_x_elastic mcipq_x_elastic
#define q_z_elastic mcipq_z_elastic
#define SAMPLE mcipSAMPLE
#line 42 "ThALES_resolution_v2.instr"
  
  /* HCS (H5) source 'Measured' parameters */
  double sT3,sI3;
  double sT2,sI2;
  double sT1,sI1;
  
  /* guide coating parameters */
  double gR0;
  double gQc;
  double gAlpha;
  double gW;        
  
  double Al_Thickness;
  double gGap;
  
  double ThALES_DM; /* PG002 */
  double ThALES_A1;
  double ThALES_L;
  double L;
  double flag;
  
  double A5;
  double A6;
  double ThALES_lambda;
  double delta_E;
  double final_lambda;
  double sample_select;
  double ThALES_RMV;
  double ThALES_RMH;
  double A3_offset;

  double dist_ana_det; //m
  double dist_sample_ana; //m
  double ana_RMV;
  double ana_RMH;

  int elastic_flag_instr_1;
  int elastic_flag_instr_2;

#line 9465 "./ThALES_resolution_v2.c"
#undef SAMPLE
#undef q_z_elastic
#undef q_x_elastic
#undef Ef
#undef Ei
#undef A4
#undef A3
#undef ThALES_dE
#undef mcposaThALES_double_peak10
#undef mccompcurindex
#undef mccompcurtype
#undef mccompcurname

/* neutron state table at each component input (local coords) */
/* [x, y, z, vx, vy, vz, t, sx, sy, sz, p] */
MCNUM mccomp_storein[11*34];
/* Components position table (absolute and relative coords) */
Coords mccomp_posa[34];
Coords mccomp_posr[34];
/* Counter for each comp to check for inactive ones */
MCNUM  mcNCounter[34];
MCNUM  mcPCounter[34];
MCNUM  mcP2Counter[34];
#define mcNUMCOMP 33 /* number of components */
/* Counter for PROP ABSORB */
MCNUM  mcAbsorbProp[34];
/* Flag true when previous component acted on the neutron (SCATTER) */
MCNUM mcScattered=0;
/* Flag true when neutron should be restored (RESTORE) */
MCNUM mcRestore=0;
/* Declarations of component definition and setting parameters. */

/* Setting parameters for component 'Origin' [1]. */
char mccOrigin_profile[16384];
MCNUM mccOrigin_percent;
MCNUM mccOrigin_flag_save;
MCNUM mccOrigin_minutes;

/* Setting parameters for component 'HCS' [2]. */
char mccHCS_flux_file[16384];
char mccHCS_xdiv_file[16384];
char mccHCS_ydiv_file[16384];
MCNUM mccHCS_radius;
MCNUM mccHCS_dist;
MCNUM mccHCS_focus_xw;
MCNUM mccHCS_focus_yh;
MCNUM mccHCS_focus_aw;
MCNUM mccHCS_focus_ah;
MCNUM mccHCS_E0;
MCNUM mccHCS_dE;
MCNUM mccHCS_lambda0;
MCNUM mccHCS_dlambda;
MCNUM mccHCS_I1;
MCNUM mccHCS_yheight;
MCNUM mccHCS_xwidth;
MCNUM mccHCS_verbose;
MCNUM mccHCS_T1;
MCNUM mccHCS_flux_file_perAA;
MCNUM mccHCS_flux_file_log;
MCNUM mccHCS_Lmin;
MCNUM mccHCS_Lmax;
MCNUM mccHCS_Emin;
MCNUM mccHCS_Emax;
MCNUM mccHCS_T2;
MCNUM mccHCS_I2;
MCNUM mccHCS_T3;
MCNUM mccHCS_I3;
MCNUM mccHCS_zdepth;
int mccHCS_target_index;

/* Setting parameters for component 'H5_rect' [4]. */
MCNUM mccH5_rect_w1;
MCNUM mccH5_rect_h1;
MCNUM mccH5_rect_w2;
MCNUM mccH5_rect_h2;
MCNUM mccH5_rect_l;
MCNUM mccH5_rect_R0;
MCNUM mccH5_rect_Qc;
MCNUM mccH5_rect_alpha;
MCNUM mccH5_rect_m;
MCNUM mccH5_rect_W;
MCNUM mccH5_rect_nslit;
MCNUM mccH5_rect_d;
MCNUM mccH5_rect_mleft;
MCNUM mccH5_rect_mright;
MCNUM mccH5_rect_mtop;
MCNUM mccH5_rect_mbottom;
MCNUM mccH5_rect_nhslit;
MCNUM mccH5_rect_G;
MCNUM mccH5_rect_aleft;
MCNUM mccH5_rect_aright;
MCNUM mccH5_rect_atop;
MCNUM mccH5_rect_abottom;
MCNUM mccH5_rect_wavy;
MCNUM mccH5_rect_wavy_z;
MCNUM mccH5_rect_wavy_tb;
MCNUM mccH5_rect_wavy_lr;
MCNUM mccH5_rect_chamfers;
MCNUM mccH5_rect_chamfers_z;
MCNUM mccH5_rect_chamfers_lr;
MCNUM mccH5_rect_chamfers_tb;
MCNUM mccH5_rect_nelements;
MCNUM mccH5_rect_nu;
MCNUM mccH5_rect_phase;
char mccH5_rect_reflect[16384];

/* Setting parameters for component 'H53_inpile' [7]. */
MCNUM mccH53_inpile_w1;
MCNUM mccH53_inpile_h1;
MCNUM mccH53_inpile_w2;
MCNUM mccH53_inpile_h2;
MCNUM mccH53_inpile_l;
MCNUM mccH53_inpile_R0;
MCNUM mccH53_inpile_Qc;
MCNUM mccH53_inpile_alpha;
MCNUM mccH53_inpile_m;
MCNUM mccH53_inpile_W;
MCNUM mccH53_inpile_nslit;
MCNUM mccH53_inpile_d;
MCNUM mccH53_inpile_mleft;
MCNUM mccH53_inpile_mright;
MCNUM mccH53_inpile_mtop;
MCNUM mccH53_inpile_mbottom;
MCNUM mccH53_inpile_nhslit;
MCNUM mccH53_inpile_G;
MCNUM mccH53_inpile_aleft;
MCNUM mccH53_inpile_aright;
MCNUM mccH53_inpile_atop;
MCNUM mccH53_inpile_abottom;
MCNUM mccH53_inpile_wavy;
MCNUM mccH53_inpile_wavy_z;
MCNUM mccH53_inpile_wavy_tb;
MCNUM mccH53_inpile_wavy_lr;
MCNUM mccH53_inpile_chamfers;
MCNUM mccH53_inpile_chamfers_z;
MCNUM mccH53_inpile_chamfers_lr;
MCNUM mccH53_inpile_chamfers_tb;
MCNUM mccH53_inpile_nelements;
MCNUM mccH53_inpile_nu;
MCNUM mccH53_inpile_phase;
char mccH53_inpile_reflect[16384];

/* Setting parameters for component 'H53_Obt' [8]. */
MCNUM mccH53_Obt_w1;
MCNUM mccH53_Obt_h1;
MCNUM mccH53_Obt_w2;
MCNUM mccH53_Obt_h2;
MCNUM mccH53_Obt_l;
MCNUM mccH53_Obt_R0;
MCNUM mccH53_Obt_Qc;
MCNUM mccH53_Obt_alpha;
MCNUM mccH53_Obt_m;
MCNUM mccH53_Obt_W;
MCNUM mccH53_Obt_nslit;
MCNUM mccH53_Obt_d;
MCNUM mccH53_Obt_mleft;
MCNUM mccH53_Obt_mright;
MCNUM mccH53_Obt_mtop;
MCNUM mccH53_Obt_mbottom;
MCNUM mccH53_Obt_nhslit;
MCNUM mccH53_Obt_G;
MCNUM mccH53_Obt_aleft;
MCNUM mccH53_Obt_aright;
MCNUM mccH53_Obt_atop;
MCNUM mccH53_Obt_abottom;
MCNUM mccH53_Obt_wavy;
MCNUM mccH53_Obt_wavy_z;
MCNUM mccH53_Obt_wavy_tb;
MCNUM mccH53_Obt_wavy_lr;
MCNUM mccH53_Obt_chamfers;
MCNUM mccH53_Obt_chamfers_z;
MCNUM mccH53_Obt_chamfers_lr;
MCNUM mccH53_Obt_chamfers_tb;
MCNUM mccH53_Obt_nelements;
MCNUM mccH53_Obt_nu;
MCNUM mccH53_Obt_phase;
char mccH53_Obt_reflect[16384];

/* Setting parameters for component 'H53_VSComC1' [10]. */
MCNUM mccH53_VSComC1_w1;
MCNUM mccH53_VSComC1_h1;
MCNUM mccH53_VSComC1_w2;
MCNUM mccH53_VSComC1_h2;
MCNUM mccH53_VSComC1_l;
MCNUM mccH53_VSComC1_R0;
MCNUM mccH53_VSComC1_Qc;
MCNUM mccH53_VSComC1_alpha;
MCNUM mccH53_VSComC1_m;
MCNUM mccH53_VSComC1_W;
MCNUM mccH53_VSComC1_nslit;
MCNUM mccH53_VSComC1_d;
MCNUM mccH53_VSComC1_mleft;
MCNUM mccH53_VSComC1_mright;
MCNUM mccH53_VSComC1_mtop;
MCNUM mccH53_VSComC1_mbottom;
MCNUM mccH53_VSComC1_nhslit;
MCNUM mccH53_VSComC1_G;
MCNUM mccH53_VSComC1_aleft;
MCNUM mccH53_VSComC1_aright;
MCNUM mccH53_VSComC1_atop;
MCNUM mccH53_VSComC1_abottom;
MCNUM mccH53_VSComC1_wavy;
MCNUM mccH53_VSComC1_wavy_z;
MCNUM mccH53_VSComC1_wavy_tb;
MCNUM mccH53_VSComC1_wavy_lr;
MCNUM mccH53_VSComC1_chamfers;
MCNUM mccH53_VSComC1_chamfers_z;
MCNUM mccH53_VSComC1_chamfers_lr;
MCNUM mccH53_VSComC1_chamfers_tb;
MCNUM mccH53_VSComC1_nelements;
MCNUM mccH53_VSComC1_nu;
MCNUM mccH53_VSComC1_phase;
char mccH53_VSComC1_reflect[16384];

/* Setting parameters for component 'H53_Nose' [11]. */
char mccH53_Nose_option[16384];
MCNUM mccH53_Nose_w1;
MCNUM mccH53_Nose_h1;
MCNUM mccH53_Nose_l;
MCNUM mccH53_Nose_linw;
MCNUM mccH53_Nose_loutw;
MCNUM mccH53_Nose_linh;
MCNUM mccH53_Nose_louth;
MCNUM mccH53_Nose_R0;
MCNUM mccH53_Nose_Qcx;
MCNUM mccH53_Nose_Qcy;
MCNUM mccH53_Nose_alphax;
MCNUM mccH53_Nose_alphay;
MCNUM mccH53_Nose_W;
MCNUM mccH53_Nose_mx;
MCNUM mccH53_Nose_my;
MCNUM mccH53_Nose_segno;
MCNUM mccH53_Nose_curvature;
MCNUM mccH53_Nose_curvature_v;

/* Setting parameters for component 'before_monochromator_slit' [12]. */
MCNUM mccbefore_monochromator_slit_xmin;
MCNUM mccbefore_monochromator_slit_xmax;
MCNUM mccbefore_monochromator_slit_ymin;
MCNUM mccbefore_monochromator_slit_ymax;
MCNUM mccbefore_monochromator_slit_radius;
MCNUM mccbefore_monochromator_slit_xwidth;
MCNUM mccbefore_monochromator_slit_yheight;

/* Definition parameters for component 'l_monitor' [13]. */
#define mccl_monitor_nL 200
/* Setting parameters for component 'l_monitor' [13]. */
char mccl_monitor_filename[16384];
MCNUM mccl_monitor_xmin;
MCNUM mccl_monitor_xmax;
MCNUM mccl_monitor_ymin;
MCNUM mccl_monitor_ymax;
MCNUM mccl_monitor_xwidth;
MCNUM mccl_monitor_yheight;
MCNUM mccl_monitor_Lmin;
MCNUM mccl_monitor_Lmax;
MCNUM mccl_monitor_restore_neutron;
int mccl_monitor_nowritefile;

/* Setting parameters for component 'H53_ThALES_Monochromator' [15]. */
char mccH53_ThALES_Monochromator_reflect[16384];
char mccH53_ThALES_Monochromator_transmit[16384];
MCNUM mccH53_ThALES_Monochromator_zwidth;
MCNUM mccH53_ThALES_Monochromator_yheight;
MCNUM mccH53_ThALES_Monochromator_gap;
MCNUM mccH53_ThALES_Monochromator_NH;
MCNUM mccH53_ThALES_Monochromator_NV;
MCNUM mccH53_ThALES_Monochromator_mosaich;
MCNUM mccH53_ThALES_Monochromator_mosaicv;
MCNUM mccH53_ThALES_Monochromator_r0;
MCNUM mccH53_ThALES_Monochromator_t0;
MCNUM mccH53_ThALES_Monochromator_Q;
MCNUM mccH53_ThALES_Monochromator_RV;
MCNUM mccH53_ThALES_Monochromator_RH;
MCNUM mccH53_ThALES_Monochromator_DM;
MCNUM mccH53_ThALES_Monochromator_mosaic;
MCNUM mccH53_ThALES_Monochromator_width;
MCNUM mccH53_ThALES_Monochromator_height;
MCNUM mccH53_ThALES_Monochromator_verbose;
MCNUM mccH53_ThALES_Monochromator_order;

/* Setting parameters for component 'before_sample_slit' [17]. */
MCNUM mccbefore_sample_slit_xmin;
MCNUM mccbefore_sample_slit_xmax;
MCNUM mccbefore_sample_slit_ymin;
MCNUM mccbefore_sample_slit_ymax;
MCNUM mccbefore_sample_slit_radius;
MCNUM mccbefore_sample_slit_xwidth;
MCNUM mccbefore_sample_slit_yheight;

/* Definition parameters for component 'E_sample_mon' [18]. */
#define mccE_sample_mon_nE 200
/* Setting parameters for component 'E_sample_mon' [18]. */
char mccE_sample_mon_filename[16384];
MCNUM mccE_sample_mon_xmin;
MCNUM mccE_sample_mon_xmax;
MCNUM mccE_sample_mon_ymin;
MCNUM mccE_sample_mon_ymax;
MCNUM mccE_sample_mon_xwidth;
MCNUM mccE_sample_mon_yheight;
MCNUM mccE_sample_mon_Emin;
MCNUM mccE_sample_mon_Emax;
MCNUM mccE_sample_mon_restore_neutron;
int mccE_sample_mon_nowritefile;

/* Setting parameters for component 'PSD_sample_mon' [19]. */
int mccPSD_sample_mon_nx;
int mccPSD_sample_mon_ny;
char mccPSD_sample_mon_filename[16384];
MCNUM mccPSD_sample_mon_xmin;
MCNUM mccPSD_sample_mon_xmax;
MCNUM mccPSD_sample_mon_ymin;
MCNUM mccPSD_sample_mon_ymax;
MCNUM mccPSD_sample_mon_xwidth;
MCNUM mccPSD_sample_mon_yheight;
MCNUM mccPSD_sample_mon_restore_neutron;
int mccPSD_sample_mon_nowritefile;

/* Setting parameters for component 'res_sample' [21]. */
MCNUM mccres_sample_thickness;
MCNUM mccres_sample_radius;
MCNUM mccres_sample_focus_r;
MCNUM mccres_sample_E0;
MCNUM mccres_sample_dE;
MCNUM mccres_sample_target_x;
MCNUM mccres_sample_target_y;
MCNUM mccres_sample_target_z;
MCNUM mccres_sample_focus_xw;
MCNUM mccres_sample_focus_yh;
MCNUM mccres_sample_focus_aw;
MCNUM mccres_sample_focus_ah;
MCNUM mccres_sample_xwidth;
MCNUM mccres_sample_yheight;
MCNUM mccres_sample_zdepth;
int mccres_sample_target_index;

/* Setting parameters for component 'v_sample' [22]. */
MCNUM mccv_sample_radius;
MCNUM mccv_sample_thickness;
MCNUM mccv_sample_zdepth;
MCNUM mccv_sample_Vc;
MCNUM mccv_sample_sigma_abs;
MCNUM mccv_sample_sigma_inc;
MCNUM mccv_sample_radius_i;
MCNUM mccv_sample_radius_o;
MCNUM mccv_sample_h;
MCNUM mccv_sample_focus_r;
MCNUM mccv_sample_pack;
MCNUM mccv_sample_frac;
MCNUM mccv_sample_f_QE;
MCNUM mccv_sample_gamma;
MCNUM mccv_sample_target_x;
MCNUM mccv_sample_target_y;
MCNUM mccv_sample_target_z;
MCNUM mccv_sample_focus_xw;
MCNUM mccv_sample_focus_yh;
MCNUM mccv_sample_focus_aw;
MCNUM mccv_sample_focus_ah;
MCNUM mccv_sample_xwidth;
MCNUM mccv_sample_yheight;
MCNUM mccv_sample_zthick;
MCNUM mccv_sample_rad_sphere;
MCNUM mccv_sample_sig_a;
MCNUM mccv_sample_sig_i;
MCNUM mccv_sample_V0;
int mccv_sample_target_index;
MCNUM mccv_sample_multiples;

/* Setting parameters for component 'after_sample_slit' [24]. */
MCNUM mccafter_sample_slit_xmin;
MCNUM mccafter_sample_slit_xmax;
MCNUM mccafter_sample_slit_ymin;
MCNUM mccafter_sample_slit_ymax;
MCNUM mccafter_sample_slit_radius;
MCNUM mccafter_sample_slit_xwidth;
MCNUM mccafter_sample_slit_yheight;

/* Setting parameters for component 'PSD_analyzer' [26]. */
int mccPSD_analyzer_nx;
int mccPSD_analyzer_ny;
char mccPSD_analyzer_filename[16384];
MCNUM mccPSD_analyzer_xmin;
MCNUM mccPSD_analyzer_xmax;
MCNUM mccPSD_analyzer_ymin;
MCNUM mccPSD_analyzer_ymax;
MCNUM mccPSD_analyzer_xwidth;
MCNUM mccPSD_analyzer_yheight;
MCNUM mccPSD_analyzer_restore_neutron;
int mccPSD_analyzer_nowritefile;

/* Setting parameters for component 'analyzer' [27]. */
char mccanalyzer_reflect[16384];
char mccanalyzer_transmit[16384];
MCNUM mccanalyzer_zwidth;
MCNUM mccanalyzer_yheight;
MCNUM mccanalyzer_gap;
MCNUM mccanalyzer_NH;
MCNUM mccanalyzer_NV;
MCNUM mccanalyzer_mosaich;
MCNUM mccanalyzer_mosaicv;
MCNUM mccanalyzer_r0;
MCNUM mccanalyzer_t0;
MCNUM mccanalyzer_Q;
MCNUM mccanalyzer_RV;
MCNUM mccanalyzer_RH;
MCNUM mccanalyzer_DM;
MCNUM mccanalyzer_mosaic;
MCNUM mccanalyzer_width;
MCNUM mccanalyzer_height;
MCNUM mccanalyzer_verbose;
MCNUM mccanalyzer_order;

/* Setting parameters for component 'slit' [29]. */
MCNUM mccslit_xmin;
MCNUM mccslit_xmax;
MCNUM mccslit_ymin;
MCNUM mccslit_ymax;
MCNUM mccslit_radius;
MCNUM mccslit_xwidth;
MCNUM mccslit_yheight;

/* Setting parameters for component 'PSD_det' [30]. */
int mccPSD_det_nx;
int mccPSD_det_ny;
char mccPSD_det_filename[16384];
MCNUM mccPSD_det_xmin;
MCNUM mccPSD_det_xmax;
MCNUM mccPSD_det_ymin;
MCNUM mccPSD_det_ymax;
MCNUM mccPSD_det_xwidth;
MCNUM mccPSD_det_yheight;
MCNUM mccPSD_det_restore_neutron;
int mccPSD_det_nowritefile;

/* Definition parameters for component 'res_monitor' [31]. */
#define mccres_monitor_res_sample_comp res_sample
/* Setting parameters for component 'res_monitor' [31]. */
char mccres_monitor_filename[16384];
char mccres_monitor_options[16384];
MCNUM mccres_monitor_xwidth;
MCNUM mccres_monitor_yheight;
MCNUM mccres_monitor_zdepth;
MCNUM mccres_monitor_radius;
MCNUM mccres_monitor_xmin;
MCNUM mccres_monitor_xmax;
MCNUM mccres_monitor_ymin;
MCNUM mccres_monitor_ymax;
MCNUM mccres_monitor_zmin;
MCNUM mccres_monitor_zmax;
MCNUM mccres_monitor_bufsize;
MCNUM mccres_monitor_restore_neutron;

/* Setting parameters for component 'detector_all' [32]. */
MCNUM mccdetector_all_xmin;
MCNUM mccdetector_all_xmax;
MCNUM mccdetector_all_ymin;
MCNUM mccdetector_all_ymax;
MCNUM mccdetector_all_xwidth;
MCNUM mccdetector_all_yheight;
MCNUM mccdetector_all_restore_neutron;

/* User component declarations. */

/* User declarations for component 'Origin' [1]. */
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
#define profile mccOrigin_profile
#define percent mccOrigin_percent
#define flag_save mccOrigin_flag_save
#define minutes mccOrigin_minutes
#line 44 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
#ifndef PROGRESS_BAR
#define PROGRESS_BAR
#else
#error Only one Progress_bar component may be used in an instrument definition.
#endif

double IntermediateCnts;
time_t StartTime;
time_t EndTime;
time_t CurrentTime;
#line 9952 "./ThALES_resolution_v2.c"
#undef minutes
#undef flag_save
#undef percent
#undef profile
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'HCS' [2]. */
#define mccompcurname  HCS
#define mccompcurtype  Source_gen
#define mccompcurindex 2
#define p_in mccHCS_p_in
#define lambda1 mccHCS_lambda1
#define lambda2 mccHCS_lambda2
#define lambda3 mccHCS_lambda3
#define pTable mccHCS_pTable
#define pTable_x mccHCS_pTable_x
#define pTable_y mccHCS_pTable_y
#define pTable_xmin mccHCS_pTable_xmin
#define pTable_xmax mccHCS_pTable_xmax
#define pTable_xsum mccHCS_pTable_xsum
#define pTable_ymin mccHCS_pTable_ymin
#define pTable_ymax mccHCS_pTable_ymax
#define pTable_ysum mccHCS_pTable_ysum
#define pTable_dxmin mccHCS_pTable_dxmin
#define pTable_dxmax mccHCS_pTable_dxmax
#define pTable_dymin mccHCS_pTable_dymin
#define pTable_dymax mccHCS_pTable_dymax
#define flux_file mccHCS_flux_file
#define xdiv_file mccHCS_xdiv_file
#define ydiv_file mccHCS_ydiv_file
#define radius mccHCS_radius
#define dist mccHCS_dist
#define focus_xw mccHCS_focus_xw
#define focus_yh mccHCS_focus_yh
#define focus_aw mccHCS_focus_aw
#define focus_ah mccHCS_focus_ah
#define E0 mccHCS_E0
#define dE mccHCS_dE
#define lambda0 mccHCS_lambda0
#define dlambda mccHCS_dlambda
#define I1 mccHCS_I1
#define yheight mccHCS_yheight
#define xwidth mccHCS_xwidth
#define verbose mccHCS_verbose
#define T1 mccHCS_T1
#define flux_file_perAA mccHCS_flux_file_perAA
#define flux_file_log mccHCS_flux_file_log
#define Lmin mccHCS_Lmin
#define Lmax mccHCS_Lmax
#define Emin mccHCS_Emin
#define Emax mccHCS_Emax
#define T2 mccHCS_T2
#define I2 mccHCS_I2
#define T3 mccHCS_T3
#define I3 mccHCS_I3
#define zdepth mccHCS_zdepth
#define target_index mccHCS_target_index
#line 184 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"

  double p_in;
  double lambda1;  /* first Maxwellian source */
  double lambda2;  /* second Maxwellian source */
  double lambda3;  /* third Maxwellian source */
  t_Table pTable;
  t_Table pTable_x;
  t_Table pTable_y;
  double pTable_xmin;
  double pTable_xmax;
  double pTable_xsum;
  double pTable_ymin;
  double pTable_ymax;
  double pTable_ysum;
  double pTable_dxmin;
  double pTable_dxmax;
  double pTable_dymin;
  double pTable_dymax;

#line 10036 "./ThALES_resolution_v2.c"
#undef target_index
#undef zdepth
#undef I3
#undef T3
#undef I2
#undef T2
#undef Emax
#undef Emin
#undef Lmax
#undef Lmin
#undef flux_file_log
#undef flux_file_perAA
#undef T1
#undef verbose
#undef xwidth
#undef yheight
#undef I1
#undef dlambda
#undef lambda0
#undef dE
#undef E0
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef dist
#undef radius
#undef ydiv_file
#undef xdiv_file
#undef flux_file
#undef pTable_dymax
#undef pTable_dymin
#undef pTable_dxmax
#undef pTable_dxmin
#undef pTable_ysum
#undef pTable_ymax
#undef pTable_ymin
#undef pTable_xsum
#undef pTable_xmax
#undef pTable_xmin
#undef pTable_y
#undef pTable_x
#undef pTable
#undef lambda3
#undef lambda2
#undef lambda1
#undef p_in
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H5' [3]. */
#define mccompcurname  H5
#define mccompcurtype  Arm
#define mccompcurindex 3
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H5_rect' [4]. */
#define mccompcurname  H5_rect
#define mccompcurtype  Guide_gravity
#define mccompcurindex 4
#define GVars mccH5_rect_GVars
#define pTable mccH5_rect_pTable
#define w1 mccH5_rect_w1
#define h1 mccH5_rect_h1
#define w2 mccH5_rect_w2
#define h2 mccH5_rect_h2
#define l mccH5_rect_l
#define R0 mccH5_rect_R0
#define Qc mccH5_rect_Qc
#define alpha mccH5_rect_alpha
#define m mccH5_rect_m
#define W mccH5_rect_W
#define nslit mccH5_rect_nslit
#define d mccH5_rect_d
#define mleft mccH5_rect_mleft
#define mright mccH5_rect_mright
#define mtop mccH5_rect_mtop
#define mbottom mccH5_rect_mbottom
#define nhslit mccH5_rect_nhslit
#define G mccH5_rect_G
#define aleft mccH5_rect_aleft
#define aright mccH5_rect_aright
#define atop mccH5_rect_atop
#define abottom mccH5_rect_abottom
#define wavy mccH5_rect_wavy
#define wavy_z mccH5_rect_wavy_z
#define wavy_tb mccH5_rect_wavy_tb
#define wavy_lr mccH5_rect_wavy_lr
#define chamfers mccH5_rect_chamfers
#define chamfers_z mccH5_rect_chamfers_z
#define chamfers_lr mccH5_rect_chamfers_lr
#define chamfers_tb mccH5_rect_chamfers_tb
#define nelements mccH5_rect_nelements
#define nu mccH5_rect_nu
#define phase mccH5_rect_phase
#define reflect mccH5_rect_reflect
#line 334 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
  Gravity_guide_Vars_type GVars;
  t_Table pTable;
#line 10139 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_origin' [5]. */
#define mccompcurname  H53_origin
#define mccompcurtype  Arm
#define mccompcurindex 5
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_start' [6]. */
#define mccompcurname  H53_start
#define mccompcurtype  Arm
#define mccompcurindex 6
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_inpile' [7]. */
#define mccompcurname  H53_inpile
#define mccompcurtype  Guide_gravity
#define mccompcurindex 7
#define GVars mccH53_inpile_GVars
#define pTable mccH53_inpile_pTable
#define w1 mccH53_inpile_w1
#define h1 mccH53_inpile_h1
#define w2 mccH53_inpile_w2
#define h2 mccH53_inpile_h2
#define l mccH53_inpile_l
#define R0 mccH53_inpile_R0
#define Qc mccH53_inpile_Qc
#define alpha mccH53_inpile_alpha
#define m mccH53_inpile_m
#define W mccH53_inpile_W
#define nslit mccH53_inpile_nslit
#define d mccH53_inpile_d
#define mleft mccH53_inpile_mleft
#define mright mccH53_inpile_mright
#define mtop mccH53_inpile_mtop
#define mbottom mccH53_inpile_mbottom
#define nhslit mccH53_inpile_nhslit
#define G mccH53_inpile_G
#define aleft mccH53_inpile_aleft
#define aright mccH53_inpile_aright
#define atop mccH53_inpile_atop
#define abottom mccH53_inpile_abottom
#define wavy mccH53_inpile_wavy
#define wavy_z mccH53_inpile_wavy_z
#define wavy_tb mccH53_inpile_wavy_tb
#define wavy_lr mccH53_inpile_wavy_lr
#define chamfers mccH53_inpile_chamfers
#define chamfers_z mccH53_inpile_chamfers_z
#define chamfers_lr mccH53_inpile_chamfers_lr
#define chamfers_tb mccH53_inpile_chamfers_tb
#define nelements mccH53_inpile_nelements
#define nu mccH53_inpile_nu
#define phase mccH53_inpile_phase
#define reflect mccH53_inpile_reflect
#line 334 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
  Gravity_guide_Vars_type GVars;
  t_Table pTable;
#line 10239 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_Obt' [8]. */
#define mccompcurname  H53_Obt
#define mccompcurtype  Guide_gravity
#define mccompcurindex 8
#define GVars mccH53_Obt_GVars
#define pTable mccH53_Obt_pTable
#define w1 mccH53_Obt_w1
#define h1 mccH53_Obt_h1
#define w2 mccH53_Obt_w2
#define h2 mccH53_Obt_h2
#define l mccH53_Obt_l
#define R0 mccH53_Obt_R0
#define Qc mccH53_Obt_Qc
#define alpha mccH53_Obt_alpha
#define m mccH53_Obt_m
#define W mccH53_Obt_W
#define nslit mccH53_Obt_nslit
#define d mccH53_Obt_d
#define mleft mccH53_Obt_mleft
#define mright mccH53_Obt_mright
#define mtop mccH53_Obt_mtop
#define mbottom mccH53_Obt_mbottom
#define nhslit mccH53_Obt_nhslit
#define G mccH53_Obt_G
#define aleft mccH53_Obt_aleft
#define aright mccH53_Obt_aright
#define atop mccH53_Obt_atop
#define abottom mccH53_Obt_abottom
#define wavy mccH53_Obt_wavy
#define wavy_z mccH53_Obt_wavy_z
#define wavy_tb mccH53_Obt_wavy_tb
#define wavy_lr mccH53_Obt_wavy_lr
#define chamfers mccH53_Obt_chamfers
#define chamfers_z mccH53_Obt_chamfers_z
#define chamfers_lr mccH53_Obt_chamfers_lr
#define chamfers_tb mccH53_Obt_chamfers_tb
#define nelements mccH53_Obt_nelements
#define nu mccH53_Obt_nu
#define phase mccH53_Obt_phase
#define reflect mccH53_Obt_reflect
#line 334 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
  Gravity_guide_Vars_type GVars;
  t_Table pTable;
#line 10323 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_Obt_Out' [9]. */
#define mccompcurname  H53_Obt_Out
#define mccompcurtype  Arm
#define mccompcurindex 9
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_VSComC1' [10]. */
#define mccompcurname  H53_VSComC1
#define mccompcurtype  Guide_gravity
#define mccompcurindex 10
#define GVars mccH53_VSComC1_GVars
#define pTable mccH53_VSComC1_pTable
#define w1 mccH53_VSComC1_w1
#define h1 mccH53_VSComC1_h1
#define w2 mccH53_VSComC1_w2
#define h2 mccH53_VSComC1_h2
#define l mccH53_VSComC1_l
#define R0 mccH53_VSComC1_R0
#define Qc mccH53_VSComC1_Qc
#define alpha mccH53_VSComC1_alpha
#define m mccH53_VSComC1_m
#define W mccH53_VSComC1_W
#define nslit mccH53_VSComC1_nslit
#define d mccH53_VSComC1_d
#define mleft mccH53_VSComC1_mleft
#define mright mccH53_VSComC1_mright
#define mtop mccH53_VSComC1_mtop
#define mbottom mccH53_VSComC1_mbottom
#define nhslit mccH53_VSComC1_nhslit
#define G mccH53_VSComC1_G
#define aleft mccH53_VSComC1_aleft
#define aright mccH53_VSComC1_aright
#define atop mccH53_VSComC1_atop
#define abottom mccH53_VSComC1_abottom
#define wavy mccH53_VSComC1_wavy
#define wavy_z mccH53_VSComC1_wavy_z
#define wavy_tb mccH53_VSComC1_wavy_tb
#define wavy_lr mccH53_VSComC1_wavy_lr
#define chamfers mccH53_VSComC1_chamfers
#define chamfers_z mccH53_VSComC1_chamfers_z
#define chamfers_lr mccH53_VSComC1_chamfers_lr
#define chamfers_tb mccH53_VSComC1_chamfers_tb
#define nelements mccH53_VSComC1_nelements
#define nu mccH53_VSComC1_nu
#define phase mccH53_VSComC1_phase
#define reflect mccH53_VSComC1_reflect
#line 334 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
  Gravity_guide_Vars_type GVars;
  t_Table pTable;
#line 10415 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_Nose' [11]. */
#define mccompcurname  H53_Nose
#define mccompcurtype  Guide_tapering
#define mccompcurindex 11
#define w1c mccH53_Nose_w1c
#define w2c mccH53_Nose_w2c
#define ww mccH53_Nose_ww
#define hh mccH53_Nose_hh
#define whalf mccH53_Nose_whalf
#define hhalf mccH53_Nose_hhalf
#define lwhalf mccH53_Nose_lwhalf
#define lhhalf mccH53_Nose_lhhalf
#define h1_in mccH53_Nose_h1_in
#define h2_out mccH53_Nose_h2_out
#define w1_in mccH53_Nose_w1_in
#define w2_out mccH53_Nose_w2_out
#define l_seg mccH53_Nose_l_seg
#define seg mccH53_Nose_seg
#define h12 mccH53_Nose_h12
#define h2 mccH53_Nose_h2
#define w12 mccH53_Nose_w12
#define w2 mccH53_Nose_w2
#define a_ell_q mccH53_Nose_a_ell_q
#define b_ell_q mccH53_Nose_b_ell_q
#define lbw mccH53_Nose_lbw
#define lbh mccH53_Nose_lbh
#define mxi mccH53_Nose_mxi
#define u1 mccH53_Nose_u1
#define u2 mccH53_Nose_u2
#define div1 mccH53_Nose_div1
#define p2_para mccH53_Nose_p2_para
#define test mccH53_Nose_test
#define Div1 mccH53_Nose_Div1
#define i mccH53_Nose_i
#define ii mccH53_Nose_ii
#define seg mccH53_Nose_seg
#define fu mccH53_Nose_fu
#define pos mccH53_Nose_pos
#define file_name mccH53_Nose_file_name
#define ep mccH53_Nose_ep
#define num mccH53_Nose_num
#define rotation_h mccH53_Nose_rotation_h
#define rotation_v mccH53_Nose_rotation_v
#define option mccH53_Nose_option
#define w1 mccH53_Nose_w1
#define h1 mccH53_Nose_h1
#define l mccH53_Nose_l
#define linw mccH53_Nose_linw
#define loutw mccH53_Nose_loutw
#define linh mccH53_Nose_linh
#define louth mccH53_Nose_louth
#define R0 mccH53_Nose_R0
#define Qcx mccH53_Nose_Qcx
#define Qcy mccH53_Nose_Qcy
#define alphax mccH53_Nose_alphax
#define alphay mccH53_Nose_alphay
#define W mccH53_Nose_W
#define mx mccH53_Nose_mx
#define my mccH53_Nose_my
#define segno mccH53_Nose_segno
#define curvature mccH53_Nose_curvature
#define curvature_v mccH53_Nose_curvature_v
#line 97 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"
double *w1c;
double *w2c;
double *ww, *hh;
double *whalf, *hhalf;
double *lwhalf, *lhhalf;
double *h1_in, *h2_out, *w1_in, *w2_out;
double l_seg, h12, h2, w12, w2, a_ell_q, b_ell_q, lbw, lbh;
double mxi ,u1 ,u2 ,div1, p2_para;
double test,Div1;
int i,ii,seg;
char *fu;
char *pos;
char file_name[1024];
char *ep;
FILE *num;
double rotation_h, rotation_v;
#line 10535 "./ThALES_resolution_v2.c"
#undef curvature_v
#undef curvature
#undef segno
#undef my
#undef mx
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef louth
#undef linh
#undef loutw
#undef linw
#undef l
#undef h1
#undef w1
#undef option
#undef rotation_v
#undef rotation_h
#undef num
#undef ep
#undef file_name
#undef pos
#undef fu
#undef seg
#undef ii
#undef i
#undef Div1
#undef test
#undef p2_para
#undef div1
#undef u2
#undef u1
#undef mxi
#undef lbh
#undef lbw
#undef b_ell_q
#undef a_ell_q
#undef w2
#undef w12
#undef h2
#undef h12
#undef seg
#undef l_seg
#undef w2_out
#undef w1_in
#undef h2_out
#undef h1_in
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'before_monochromator_slit' [12]. */
#define mccompcurname  before_monochromator_slit
#define mccompcurtype  Slit
#define mccompcurindex 12
#define xmin mccbefore_monochromator_slit_xmin
#define xmax mccbefore_monochromator_slit_xmax
#define ymin mccbefore_monochromator_slit_ymin
#define ymax mccbefore_monochromator_slit_ymax
#define radius mccbefore_monochromator_slit_radius
#define xwidth mccbefore_monochromator_slit_xwidth
#define yheight mccbefore_monochromator_slit_yheight
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'l_monitor' [13]. */
#define mccompcurname  l_monitor
#define mccompcurtype  L_monitor
#define mccompcurindex 13
#define nL mccl_monitor_nL
#define L_N mccl_monitor_L_N
#define L_p mccl_monitor_L_p
#define L_p2 mccl_monitor_L_p2
#define filename mccl_monitor_filename
#define xmin mccl_monitor_xmin
#define xmax mccl_monitor_xmax
#define ymin mccl_monitor_ymin
#define ymax mccl_monitor_ymax
#define xwidth mccl_monitor_xwidth
#define yheight mccl_monitor_yheight
#define Lmin mccl_monitor_Lmin
#define Lmax mccl_monitor_Lmax
#define restore_neutron mccl_monitor_restore_neutron
#define nowritefile mccl_monitor_nowritefile
#line 57 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/L_monitor.comp"
double L_N[nL];
double L_p[nL], L_p2[nL];
#line 10642 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef Lmax
#undef Lmin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef L_p2
#undef L_p
#undef L_N
#undef nL
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_ThALES_Monochromator_Cradle' [14]. */
#define mccompcurname  H53_ThALES_Monochromator_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 14
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_ThALES_Monochromator' [15]. */
#define mccompcurname  H53_ThALES_Monochromator
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 15
#define mos_rms_y mccH53_ThALES_Monochromator_mos_rms_y
#define mos_rms_z mccH53_ThALES_Monochromator_mos_rms_z
#define mos_rms_max mccH53_ThALES_Monochromator_mos_rms_max
#define mono_Q mccH53_ThALES_Monochromator_mono_Q
#define SlabWidth mccH53_ThALES_Monochromator_SlabWidth
#define SlabHeight mccH53_ThALES_Monochromator_SlabHeight
#define rTable mccH53_ThALES_Monochromator_rTable
#define tTable mccH53_ThALES_Monochromator_tTable
#define row mccH53_ThALES_Monochromator_row
#define col mccH53_ThALES_Monochromator_col
#define tiltH mccH53_ThALES_Monochromator_tiltH
#define tiltV mccH53_ThALES_Monochromator_tiltV
#define reflect mccH53_ThALES_Monochromator_reflect
#define transmit mccH53_ThALES_Monochromator_transmit
#define zwidth mccH53_ThALES_Monochromator_zwidth
#define yheight mccH53_ThALES_Monochromator_yheight
#define gap mccH53_ThALES_Monochromator_gap
#define NH mccH53_ThALES_Monochromator_NH
#define NV mccH53_ThALES_Monochromator_NV
#define mosaich mccH53_ThALES_Monochromator_mosaich
#define mosaicv mccH53_ThALES_Monochromator_mosaicv
#define r0 mccH53_ThALES_Monochromator_r0
#define t0 mccH53_ThALES_Monochromator_t0
#define Q mccH53_ThALES_Monochromator_Q
#define RV mccH53_ThALES_Monochromator_RV
#define RH mccH53_ThALES_Monochromator_RH
#define DM mccH53_ThALES_Monochromator_DM
#define mosaic mccH53_ThALES_Monochromator_mosaic
#define width mccH53_ThALES_Monochromator_width
#define height mccH53_ThALES_Monochromator_height
#define verbose mccH53_ThALES_Monochromator_verbose
#define order mccH53_ThALES_Monochromator_order
#line 136 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
  double mos_rms_y; /* root-mean-square of mosaic, in radians */
  double mos_rms_z;
  double mos_rms_max;
  double mono_Q;
  double SlabWidth, SlabHeight;
  t_Table rTable, tTable;
  double row,col;
  double* tiltH;
  double* tiltV;
#line 10716 "./ThALES_resolution_v2.c"
#undef order
#undef verbose
#undef height
#undef width
#undef mosaic
#undef DM
#undef RH
#undef RV
#undef Q
#undef t0
#undef r0
#undef mosaicv
#undef mosaich
#undef NV
#undef NH
#undef gap
#undef yheight
#undef zwidth
#undef transmit
#undef reflect
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'H53_ThALES_Monochromator_Out' [16]. */
#define mccompcurname  H53_ThALES_Monochromator_Out
#define mccompcurtype  Arm
#define mccompcurindex 16
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'before_sample_slit' [17]. */
#define mccompcurname  before_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 17
#define xmin mccbefore_sample_slit_xmin
#define xmax mccbefore_sample_slit_xmax
#define ymin mccbefore_sample_slit_ymin
#define ymax mccbefore_sample_slit_ymax
#define radius mccbefore_sample_slit_radius
#define xwidth mccbefore_sample_slit_xwidth
#define yheight mccbefore_sample_slit_yheight
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'E_sample_mon' [18]. */
#define mccompcurname  E_sample_mon
#define mccompcurtype  E_monitor
#define mccompcurindex 18
#define nE mccE_sample_mon_nE
#define E_N mccE_sample_mon_E_N
#define E_p mccE_sample_mon_E_p
#define E_p2 mccE_sample_mon_E_p2
#define S_p mccE_sample_mon_S_p
#define S_pE mccE_sample_mon_S_pE
#define S_pE2 mccE_sample_mon_S_pE2
#define filename mccE_sample_mon_filename
#define xmin mccE_sample_mon_xmin
#define xmax mccE_sample_mon_xmax
#define ymin mccE_sample_mon_ymin
#define ymax mccE_sample_mon_ymax
#define xwidth mccE_sample_mon_xwidth
#define yheight mccE_sample_mon_yheight
#define Emin mccE_sample_mon_Emin
#define Emax mccE_sample_mon_Emax
#define restore_neutron mccE_sample_mon_restore_neutron
#define nowritefile mccE_sample_mon_nowritefile
#line 60 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/E_monitor.comp"
double E_N[nE];
double E_p[nE], E_p2[nE];
double S_p, S_pE, S_pE2;
#line 10809 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef Emax
#undef Emin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef nE
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'PSD_sample_mon' [19]. */
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
#define nx mccPSD_sample_mon_nx
#define ny mccPSD_sample_mon_ny
#define filename mccPSD_sample_mon_filename
#define xmin mccPSD_sample_mon_xmin
#define xmax mccPSD_sample_mon_xmax
#define ymin mccPSD_sample_mon_ymin
#define ymax mccPSD_sample_mon_ymax
#define xwidth mccPSD_sample_mon_xwidth
#define yheight mccPSD_sample_mon_yheight
#define restore_neutron mccPSD_sample_mon_restore_neutron
#define nowritefile mccPSD_sample_mon_nowritefile
#line 63 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
  DArray2d PSD_N;
  DArray2d PSD_p;
  DArray2d PSD_p2;
#line 10854 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'sample_arm' [20]. */
#define mccompcurname  sample_arm
#define mccompcurtype  Arm
#define mccompcurindex 20
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'res_sample' [21]. */
#define mccompcurname  res_sample
#define mccompcurtype  Res_sample
#define mccompcurindex 21
#define res_struct mccres_sample_res_struct
#define thickness mccres_sample_thickness
#define radius mccres_sample_radius
#define focus_r mccres_sample_focus_r
#define E0 mccres_sample_E0
#define dE mccres_sample_dE
#define target_x mccres_sample_target_x
#define target_y mccres_sample_target_y
#define target_z mccres_sample_target_z
#define focus_xw mccres_sample_focus_xw
#define focus_yh mccres_sample_focus_yh
#define focus_aw mccres_sample_focus_aw
#define focus_ah mccres_sample_focus_ah
#define xwidth mccres_sample_xwidth
#define yheight mccres_sample_yheight
#define zdepth mccres_sample_zdepth
#define target_index mccres_sample_target_index
#line 84 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../samples/Res_sample.comp"
struct Res_sample_struct res_struct;
#line 10904 "./ThALES_resolution_v2.c"
#undef target_index
#undef zdepth
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef dE
#undef E0
#undef focus_r
#undef radius
#undef thickness
#undef res_struct
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'v_sample' [22]. */
#define mccompcurname  v_sample
#define mccompcurtype  V_sample
#define mccompcurindex 22
#define VarsV mccv_sample_VarsV
#define radius mccv_sample_radius
#define thickness mccv_sample_thickness
#define zdepth mccv_sample_zdepth
#define Vc mccv_sample_Vc
#define sigma_abs mccv_sample_sigma_abs
#define sigma_inc mccv_sample_sigma_inc
#define radius_i mccv_sample_radius_i
#define radius_o mccv_sample_radius_o
#define h mccv_sample_h
#define focus_r mccv_sample_focus_r
#define pack mccv_sample_pack
#define frac mccv_sample_frac
#define f_QE mccv_sample_f_QE
#define gamma mccv_sample_gamma
#define target_x mccv_sample_target_x
#define target_y mccv_sample_target_y
#define target_z mccv_sample_target_z
#define focus_xw mccv_sample_focus_xw
#define focus_yh mccv_sample_focus_yh
#define focus_aw mccv_sample_focus_aw
#define focus_ah mccv_sample_focus_ah
#define xwidth mccv_sample_xwidth
#define yheight mccv_sample_yheight
#define zthick mccv_sample_zthick
#define rad_sphere mccv_sample_rad_sphere
#define sig_a mccv_sample_sig_a
#define sig_i mccv_sample_sig_i
#define V0 mccv_sample_V0
#define target_index mccv_sample_target_index
#define multiples mccv_sample_multiples
#line 117 "V_sample.comp"
  struct StructVarsV VarsV;
#line 10963 "./ThALES_resolution_v2.c"
#undef multiples
#undef target_index
#undef V0
#undef sig_i
#undef sig_a
#undef rad_sphere
#undef zthick
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef gamma
#undef f_QE
#undef frac
#undef pack
#undef focus_r
#undef h
#undef radius_o
#undef radius_i
#undef sigma_inc
#undef sigma_abs
#undef Vc
#undef zdepth
#undef thickness
#undef radius
#undef VarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'Sample_Out' [23]. */
#define mccompcurname  Sample_Out
#define mccompcurtype  Arm
#define mccompcurindex 23
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'after_sample_slit' [24]. */
#define mccompcurname  after_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 24
#define xmin mccafter_sample_slit_xmin
#define xmax mccafter_sample_slit_xmax
#define ymin mccafter_sample_slit_ymin
#define ymax mccafter_sample_slit_ymax
#define radius mccafter_sample_slit_radius
#define xwidth mccafter_sample_slit_xwidth
#define yheight mccafter_sample_slit_yheight
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'Ana_Cradle' [25]. */
#define mccompcurname  Ana_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 25
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'PSD_analyzer' [26]. */
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
#define nx mccPSD_analyzer_nx
#define ny mccPSD_analyzer_ny
#define filename mccPSD_analyzer_filename
#define xmin mccPSD_analyzer_xmin
#define xmax mccPSD_analyzer_xmax
#define ymin mccPSD_analyzer_ymin
#define ymax mccPSD_analyzer_ymax
#define xwidth mccPSD_analyzer_xwidth
#define yheight mccPSD_analyzer_yheight
#define restore_neutron mccPSD_analyzer_restore_neutron
#define nowritefile mccPSD_analyzer_nowritefile
#line 63 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
  DArray2d PSD_N;
  DArray2d PSD_p;
  DArray2d PSD_p2;
#line 11059 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'analyzer' [27]. */
#define mccompcurname  analyzer
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 27
#define mos_rms_y mccanalyzer_mos_rms_y
#define mos_rms_z mccanalyzer_mos_rms_z
#define mos_rms_max mccanalyzer_mos_rms_max
#define mono_Q mccanalyzer_mono_Q
#define SlabWidth mccanalyzer_SlabWidth
#define SlabHeight mccanalyzer_SlabHeight
#define rTable mccanalyzer_rTable
#define tTable mccanalyzer_tTable
#define row mccanalyzer_row
#define col mccanalyzer_col
#define tiltH mccanalyzer_tiltH
#define tiltV mccanalyzer_tiltV
#define reflect mccanalyzer_reflect
#define transmit mccanalyzer_transmit
#define zwidth mccanalyzer_zwidth
#define yheight mccanalyzer_yheight
#define gap mccanalyzer_gap
#define NH mccanalyzer_NH
#define NV mccanalyzer_NV
#define mosaich mccanalyzer_mosaich
#define mosaicv mccanalyzer_mosaicv
#define r0 mccanalyzer_r0
#define t0 mccanalyzer_t0
#define Q mccanalyzer_Q
#define RV mccanalyzer_RV
#define RH mccanalyzer_RH
#define DM mccanalyzer_DM
#define mosaic mccanalyzer_mosaic
#define width mccanalyzer_width
#define height mccanalyzer_height
#define verbose mccanalyzer_verbose
#define order mccanalyzer_order
#line 136 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
  double mos_rms_y; /* root-mean-square of mosaic, in radians */
  double mos_rms_z;
  double mos_rms_max;
  double mono_Q;
  double SlabWidth, SlabHeight;
  t_Table rTable, tTable;
  double row,col;
  double* tiltH;
  double* tiltV;
#line 11124 "./ThALES_resolution_v2.c"
#undef order
#undef verbose
#undef height
#undef width
#undef mosaic
#undef DM
#undef RH
#undef RV
#undef Q
#undef t0
#undef r0
#undef mosaicv
#undef mosaich
#undef NV
#undef NH
#undef gap
#undef yheight
#undef zwidth
#undef transmit
#undef reflect
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'Ana_Out' [28]. */
#define mccompcurname  Ana_Out
#define mccompcurtype  Arm
#define mccompcurindex 28
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'slit' [29]. */
#define mccompcurname  slit
#define mccompcurtype  Slit
#define mccompcurindex 29
#define xmin mccslit_xmin
#define xmax mccslit_xmax
#define ymin mccslit_ymin
#define ymax mccslit_ymax
#define radius mccslit_radius
#define xwidth mccslit_xwidth
#define yheight mccslit_yheight
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'PSD_det' [30]. */
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
#define nx mccPSD_det_nx
#define ny mccPSD_det_ny
#define filename mccPSD_det_filename
#define xmin mccPSD_det_xmin
#define xmax mccPSD_det_xmax
#define ymin mccPSD_det_ymin
#define ymax mccPSD_det_ymax
#define xwidth mccPSD_det_xwidth
#define yheight mccPSD_det_yheight
#define restore_neutron mccPSD_det_restore_neutron
#define nowritefile mccPSD_det_nowritefile
#line 63 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
  DArray2d PSD_N;
  DArray2d PSD_p;
  DArray2d PSD_p2;
#line 11213 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'res_monitor' [31]. */
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
#define filename mccres_monitor_filename
#define options mccres_monitor_options
#define xwidth mccres_monitor_xwidth
#define yheight mccres_monitor_yheight
#define zdepth mccres_monitor_zdepth
#define radius mccres_monitor_radius
#define xmin mccres_monitor_xmin
#define xmax mccres_monitor_xmax
#define ymin mccres_monitor_ymin
#define ymax mccres_monitor_ymax
#define zmin mccres_monitor_zmin
#define zmax mccres_monitor_zmax
#define bufsize mccres_monitor_bufsize
#define restore_neutron mccres_monitor_restore_neutron
#line 82 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
MonitornD_Defines_type DEFS;
MonitornD_Variables_type Vars;
long buffer_index;
#line 11258 "./ThALES_resolution_v2.c"
#undef restore_neutron
#undef bufsize
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef radius
#undef zdepth
#undef yheight
#undef xwidth
#undef options
#undef filename
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'detector_all' [32]. */
#define mccompcurname  detector_all
#define mccompcurtype  Monitor
#define mccompcurindex 32
#define Nsum mccdetector_all_Nsum
#define psum mccdetector_all_psum
#define p2sum mccdetector_all_p2sum
#define xmin mccdetector_all_xmin
#define xmax mccdetector_all_xmax
#define ymin mccdetector_all_ymin
#define ymax mccdetector_all_ymax
#define xwidth mccdetector_all_xwidth
#define yheight mccdetector_all_yheight
#define restore_neutron mccdetector_all_restore_neutron
#line 52 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Monitor.comp"
double Nsum;
double psum, p2sum;
#line 11298 "./ThALES_resolution_v2.c"
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef p2sum
#undef psum
#undef Nsum
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

Coords mcposaOrigin, mcposrOrigin;
Rotation mcrotaOrigin, mcrotrOrigin;
Coords mcposaHCS, mcposrHCS;
Rotation mcrotaHCS, mcrotrHCS;
Coords mcposaH5, mcposrH5;
Rotation mcrotaH5, mcrotrH5;
Coords mcposaH5_rect, mcposrH5_rect;
Rotation mcrotaH5_rect, mcrotrH5_rect;
Coords mcposaH53_origin, mcposrH53_origin;
Rotation mcrotaH53_origin, mcrotrH53_origin;
Coords mcposaH53_start, mcposrH53_start;
Rotation mcrotaH53_start, mcrotrH53_start;
Coords mcposaH53_inpile, mcposrH53_inpile;
Rotation mcrotaH53_inpile, mcrotrH53_inpile;
Coords mcposaH53_Obt, mcposrH53_Obt;
Rotation mcrotaH53_Obt, mcrotrH53_Obt;
Coords mcposaH53_Obt_Out, mcposrH53_Obt_Out;
Rotation mcrotaH53_Obt_Out, mcrotrH53_Obt_Out;
Coords mcposaH53_VSComC1, mcposrH53_VSComC1;
Rotation mcrotaH53_VSComC1, mcrotrH53_VSComC1;
Coords mcposaH53_Nose, mcposrH53_Nose;
Rotation mcrotaH53_Nose, mcrotrH53_Nose;
Coords mcposabefore_monochromator_slit, mcposrbefore_monochromator_slit;
Rotation mcrotabefore_monochromator_slit, mcrotrbefore_monochromator_slit;
Coords mcposal_monitor, mcposrl_monitor;
Rotation mcrotal_monitor, mcrotrl_monitor;
Coords mcposaH53_ThALES_Monochromator_Cradle, mcposrH53_ThALES_Monochromator_Cradle;
Rotation mcrotaH53_ThALES_Monochromator_Cradle, mcrotrH53_ThALES_Monochromator_Cradle;
Coords mcposaH53_ThALES_Monochromator, mcposrH53_ThALES_Monochromator;
Rotation mcrotaH53_ThALES_Monochromator, mcrotrH53_ThALES_Monochromator;
Coords mcposaH53_ThALES_Monochromator_Out, mcposrH53_ThALES_Monochromator_Out;
Rotation mcrotaH53_ThALES_Monochromator_Out, mcrotrH53_ThALES_Monochromator_Out;
Coords mcposabefore_sample_slit, mcposrbefore_sample_slit;
Rotation mcrotabefore_sample_slit, mcrotrbefore_sample_slit;
Coords mcposaE_sample_mon, mcposrE_sample_mon;
Rotation mcrotaE_sample_mon, mcrotrE_sample_mon;
Coords mcposaPSD_sample_mon, mcposrPSD_sample_mon;
Rotation mcrotaPSD_sample_mon, mcrotrPSD_sample_mon;
Coords mcposasample_arm, mcposrsample_arm;
Rotation mcrotasample_arm, mcrotrsample_arm;
Coords mcposares_sample, mcposrres_sample;
Rotation mcrotares_sample, mcrotrres_sample;
Coords mcposav_sample, mcposrv_sample;
Rotation mcrotav_sample, mcrotrv_sample;
Coords mcposaSample_Out, mcposrSample_Out;
Rotation mcrotaSample_Out, mcrotrSample_Out;
Coords mcposaafter_sample_slit, mcposrafter_sample_slit;
Rotation mcrotaafter_sample_slit, mcrotrafter_sample_slit;
Coords mcposaAna_Cradle, mcposrAna_Cradle;
Rotation mcrotaAna_Cradle, mcrotrAna_Cradle;
Coords mcposaPSD_analyzer, mcposrPSD_analyzer;
Rotation mcrotaPSD_analyzer, mcrotrPSD_analyzer;
Coords mcposaanalyzer, mcposranalyzer;
Rotation mcrotaanalyzer, mcrotranalyzer;
Coords mcposaAna_Out, mcposrAna_Out;
Rotation mcrotaAna_Out, mcrotrAna_Out;
Coords mcposaslit, mcposrslit;
Rotation mcrotaslit, mcrotrslit;
Coords mcposaPSD_det, mcposrPSD_det;
Rotation mcrotaPSD_det, mcrotrPSD_det;
Coords mcposares_monitor, mcposrres_monitor;
Rotation mcrotares_monitor, mcrotrres_monitor;
Coords mcposadetector_all, mcposrdetector_all;
Rotation mcrotadetector_all, mcrotrdetector_all;

MCNUM mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz, mcnt, mcnsx, mcnsy, mcnsz, mcnp;

/* end declare */

void mcinit(void) {
#define mccompcurname  ThALES_double_peak10
#define mccompcurtype  INSTRUMENT
#define mccompcurindex 0
#define mcposaThALES_double_peak10 coords_set(0,0,0)
#define ThALES_dE mcipThALES_dE
#define A3 mcipA3
#define A4 mcipA4
#define Ei mcipEi
#define Ef mcipEf
#define q_x_elastic mcipq_x_elastic
#define q_z_elastic mcipq_z_elastic
#define SAMPLE mcipSAMPLE
#line 83 "ThALES_resolution_v2.instr"
{

  sT3=413.5, sI3=10.22e12;
  sT2=145.8, sI2=3.44e13;
  sT1=40.1, sI1=2.78e13;
  
  /* guide coating parameters */
  gR0 = 1;
  gQc = 0.0216;
  gAlpha = 4.07;
  gW = 1.0/300.0;
  
  Al_Thickness = 0.001;
  gGap = 0.001;
  
  ThALES_DM      = 3.355; /* PG002 */
  ThALES_A1      = 0;
  ThALES_L       = 2.000;
  
  flag         = 0;
  
  A5=0;
  A6=0;
  delta_E=0;
  ThALES_RMV = -1;
  ThALES_RMH=-1;
  A3_offset=0;

  dist_ana_det=0.640; //m
  dist_sample_ana=1.260; //m
  ana_RMV=-1;
  ana_RMH=-1;

  /* the effective guide divergence is 1.2*0.1*lambda*pi/180 for m=1.2 */
  /* the effective inguide length for focusing is thus 
         (0.12/2)/(1.2*0.1*lambda*PI/180)

  /* compute H53 parameters: ThALES */
      
  ThALES_lambda=1/(0.1106*sqrt(Ei)); 
  final_lambda=1/(0.1106*sqrt(Ef));

  A5  = -asin(final_lambda/2/ThALES_DM)*RAD2DEG;
  A6  = 2*A5;

  ThALES_A1  = asin(ThALES_lambda/2/ThALES_DM)*RAD2DEG;
  
/*  
//From Farhi
       L   = 1/(1/ThALES_L+1/( (0.12/2)/(3*0.1*ThALES_lambda*PI/180) ));
  if (ThALES_RMV<0)
  ThALES_RMV = 2*L*sin(DEG2RAD*fabs(ThALES_A1));
  if (ThALES_RMH<0)
  ThALES_RMH = 2*L/sin(DEG2RAD*fabs(ThALES_A1));
  */
  
//Monochromator curvature
    
  if (ThALES_RMV<0)
    ThALES_RMV = 1/(    (   1/ThALES_L + 1/7.0 )   / (2*sin(DEG2RAD*fabs(ThALES_A1)))    );
//  ThALES_RMV = 1/(    (   1/ThALES_L + 1/( (0.12/2)/(3*0.1*ThALES_lambda*PI/180) )   )   / (2*sin(DEG2RAD*fabs(ThALES_A1)))    );
  if (ThALES_RMH<0)
    ThALES_RMH = 1/(    (   1/ThALES_L + 1/2.0 )  *sin(DEG2RAD*fabs(ThALES_A1)) / (2)    );
  
  printf("%s: ThALES: A1=%g [deg] RMV=%g [m] RMH=%g [m] lambda=%g [Angs]\n", 
    NAME_CURRENT_COMP, ThALES_A1, ThALES_RMV, ThALES_RMH, ThALES_lambda); 
    
    //analyzer curvature
  if (ana_RMV<0)
    ana_RMV = 1/(    (   1/dist_ana_det + 1/dist_sample_ana )   / (2*sin(DEG2RAD*fabs(A5)))    );
  if (ana_RMH<0)
    ana_RMH = 1/(    (   1/dist_ana_det + 1/dist_sample_ana )  *sin(DEG2RAD*fabs(A5)) / (2)    );

  printf("%s: ThALES: A5=%g [deg] ana_RMV=%g [m] ana_RMH=%g [m] lambda=%g [Angs]\n", 
    NAME_CURRENT_COMP, A5, ana_RMV, ana_RMH, ThALES_lambda); 

// Rotation of sample for alignment purpose
  A3_offset=atan(q_z_elastic/q_x_elastic)*RAD2DEG;

}
#line 11476 "./ThALES_resolution_v2.c"
#undef SAMPLE
#undef q_z_elastic
#undef q_x_elastic
#undef Ef
#undef Ei
#undef A4
#undef A3
#undef ThALES_dE
#undef mcposaThALES_double_peak10
#undef mccompcurindex
#undef mccompcurtype
#undef mccompcurname
  /* Computation of coordinate transformations. */
  {
    Coords mctc1, mctc2, mcLastComp;
    Rotation mctr1;
    double mcAccumulatedILength = 0;
    /* Initialize "last" component origin as (0,0,0) */
    mcLastComp = coords_set(0,0,0);

    mcDEBUG_INSTR()
  /* Component initializations. */
    /* Component Origin. */
  /* Setting parameters for component Origin. */
  SIG_MESSAGE("Origin (Init:SetPar)");
#line 39 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccOrigin_profile, "NULL" ? "NULL" : "", 16384); else mccOrigin_profile[0]='\0';
#line 39 "ThALES_resolution_v2.instr"
  mccOrigin_percent = 10;
#line 39 "ThALES_resolution_v2.instr"
  mccOrigin_flag_save = 0;
#line 39 "ThALES_resolution_v2.instr"
  mccOrigin_minutes = 0;
#line 11510 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("Origin (Init:Place/Rotate)");
  rot_set_rotation(mcrotaOrigin,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11517 "./ThALES_resolution_v2.c"
  rot_copy(mcrotrOrigin, mcrotaOrigin);
  mcposaOrigin = coords_set(
#line 170 "ThALES_resolution_v2.instr"
    0,
#line 170 "ThALES_resolution_v2.instr"
    0,
#line 170 "ThALES_resolution_v2.instr"
    0);
#line 11526 "./ThALES_resolution_v2.c"
  mctc1 = coords_neg(mcposaOrigin);
  mcposrOrigin = rot_apply(mcrotaOrigin, mctc1);
  mcDEBUG_COMPONENT("Origin", mcposaOrigin, mcrotaOrigin)
  mccomp_posa[1] = mcposaOrigin;
  mccomp_posr[1] = mcposrOrigin;
  mcNCounter[1]  = mcPCounter[1] = mcP2Counter[1] = 0;
  mcAbsorbProp[1]= 0;
    /* Component HCS. */
  /* Setting parameters for component HCS. */
  SIG_MESSAGE("HCS (Init:SetPar)");
#line 129 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccHCS_flux_file, "NULL" ? "NULL" : "", 16384); else mccHCS_flux_file[0]='\0';
#line 129 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccHCS_xdiv_file, "NULL" ? "NULL" : "", 16384); else mccHCS_xdiv_file[0]='\0';
#line 129 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccHCS_ydiv_file, "NULL" ? "NULL" : "", 16384); else mccHCS_ydiv_file[0]='\0';
#line 173 "ThALES_resolution_v2.instr"
  mccHCS_radius = 0.21 / 2;
#line 175 "ThALES_resolution_v2.instr"
  mccHCS_dist = 2.155;
#line 176 "ThALES_resolution_v2.instr"
  mccHCS_focus_xw = 0.170;
#line 177 "ThALES_resolution_v2.instr"
  mccHCS_focus_yh = 0.120;
#line 130 "ThALES_resolution_v2.instr"
  mccHCS_focus_aw = 0;
#line 130 "ThALES_resolution_v2.instr"
  mccHCS_focus_ah = 0;
#line 178 "ThALES_resolution_v2.instr"
  mccHCS_E0 = mcipEi;
#line 179 "ThALES_resolution_v2.instr"
  mccHCS_dE = mcipThALES_dE;
#line 131 "ThALES_resolution_v2.instr"
  mccHCS_lambda0 = 0;
#line 131 "ThALES_resolution_v2.instr"
  mccHCS_dlambda = 0;
#line 181 "ThALES_resolution_v2.instr"
  mccHCS_I1 = sI1;
#line 132 "ThALES_resolution_v2.instr"
  mccHCS_yheight = 0.1;
#line 132 "ThALES_resolution_v2.instr"
  mccHCS_xwidth = 0.1;
#line 186 "ThALES_resolution_v2.instr"
  mccHCS_verbose = 0;
#line 180 "ThALES_resolution_v2.instr"
  mccHCS_T1 = sT1;
#line 133 "ThALES_resolution_v2.instr"
  mccHCS_flux_file_perAA = 0;
#line 133 "ThALES_resolution_v2.instr"
  mccHCS_flux_file_log = 0;
#line 134 "ThALES_resolution_v2.instr"
  mccHCS_Lmin = 0;
#line 134 "ThALES_resolution_v2.instr"
  mccHCS_Lmax = 0;
#line 134 "ThALES_resolution_v2.instr"
  mccHCS_Emin = 0;
#line 134 "ThALES_resolution_v2.instr"
  mccHCS_Emax = 0;
#line 182 "ThALES_resolution_v2.instr"
  mccHCS_T2 = sT2;
#line 183 "ThALES_resolution_v2.instr"
  mccHCS_I2 = sI2;
#line 184 "ThALES_resolution_v2.instr"
  mccHCS_T3 = sT3;
#line 185 "ThALES_resolution_v2.instr"
  mccHCS_I3 = sI3;
#line 174 "ThALES_resolution_v2.instr"
  mccHCS_zdepth = 0.15;
#line 134 "ThALES_resolution_v2.instr"
  mccHCS_target_index = + 1;
#line 11597 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("HCS (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11604 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaOrigin, mcrotaHCS);
  rot_transpose(mcrotaOrigin, mctr1);
  rot_mul(mcrotaHCS, mctr1, mcrotrHCS);
  mctc1 = coords_set(
#line 187 "ThALES_resolution_v2.instr"
    0,
#line 187 "ThALES_resolution_v2.instr"
    0,
#line 187 "ThALES_resolution_v2.instr"
    0);
#line 11615 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaOrigin, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaHCS = coords_add(mcposaOrigin, mctc2);
  mctc1 = coords_sub(mcposaOrigin, mcposaHCS);
  mcposrHCS = rot_apply(mcrotaHCS, mctc1);
  mcDEBUG_COMPONENT("HCS", mcposaHCS, mcrotaHCS)
  mccomp_posa[2] = mcposaHCS;
  mccomp_posr[2] = mcposrHCS;
  mcNCounter[2]  = mcPCounter[2] = mcP2Counter[2] = 0;
  mcAbsorbProp[2]= 0;
    /* Component H5. */
  /* Setting parameters for component H5. */
  SIG_MESSAGE("H5 (Init:SetPar)");

  SIG_MESSAGE("H5 (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11635 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaHCS, mcrotaH5);
  rot_transpose(mcrotaHCS, mctr1);
  rot_mul(mcrotaH5, mctr1, mcrotrH5);
  mctc1 = coords_set(
#line 190 "ThALES_resolution_v2.instr"
    0,
#line 190 "ThALES_resolution_v2.instr"
    0,
#line 190 "ThALES_resolution_v2.instr"
    2.155);
#line 11646 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaHCS, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH5 = coords_add(mcposaHCS, mctc2);
  mctc1 = coords_sub(mcposaHCS, mcposaH5);
  mcposrH5 = rot_apply(mcrotaH5, mctc1);
  mcDEBUG_COMPONENT("H5", mcposaH5, mcrotaH5)
  mccomp_posa[3] = mcposaH5;
  mccomp_posr[3] = mcposrH5;
  mcNCounter[3]  = mcPCounter[3] = mcP2Counter[3] = 0;
  mcAbsorbProp[3]= 0;
    /* Component H5_rect. */
  /* Setting parameters for component H5_rect. */
  SIG_MESSAGE("H5_rect (Init:SetPar)");
#line 192 "ThALES_resolution_v2.instr"
  mccH5_rect_w1 = 0.170;
#line 192 "ThALES_resolution_v2.instr"
  mccH5_rect_h1 = 0.12;
#line 113 "ThALES_resolution_v2.instr"
  mccH5_rect_w2 = 0;
#line 113 "ThALES_resolution_v2.instr"
  mccH5_rect_h2 = 0;
#line 192 "ThALES_resolution_v2.instr"
  mccH5_rect_l = 1.0;
#line 193 "ThALES_resolution_v2.instr"
  mccH5_rect_R0 = gR0;
#line 193 "ThALES_resolution_v2.instr"
  mccH5_rect_Qc = gQc;
#line 193 "ThALES_resolution_v2.instr"
  mccH5_rect_alpha = gAlpha;
#line 193 "ThALES_resolution_v2.instr"
  mccH5_rect_m = 2;
#line 193 "ThALES_resolution_v2.instr"
  mccH5_rect_W = gW;
#line 114 "ThALES_resolution_v2.instr"
  mccH5_rect_nslit = 1;
#line 114 "ThALES_resolution_v2.instr"
  mccH5_rect_d = 0.0005;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_mleft = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_mright = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_mtop = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_mbottom = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_nhslit = 1;
#line 115 "ThALES_resolution_v2.instr"
  mccH5_rect_G = 0;
#line 116 "ThALES_resolution_v2.instr"
  mccH5_rect_aleft = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH5_rect_aright = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH5_rect_atop = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH5_rect_abottom = -1;
#line 117 "ThALES_resolution_v2.instr"
  mccH5_rect_wavy = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH5_rect_wavy_z = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH5_rect_wavy_tb = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH5_rect_wavy_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH5_rect_chamfers = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH5_rect_chamfers_z = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH5_rect_chamfers_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH5_rect_chamfers_tb = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH5_rect_nelements = 1;
#line 119 "ThALES_resolution_v2.instr"
  mccH5_rect_nu = 0;
#line 119 "ThALES_resolution_v2.instr"
  mccH5_rect_phase = 0;
#line 119 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccH5_rect_reflect, "NULL" ? "NULL" : "", 16384); else mccH5_rect_reflect[0]='\0';
#line 11728 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H5_rect (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11735 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaHCS, mcrotaH5_rect);
  rot_transpose(mcrotaH5, mctr1);
  rot_mul(mcrotaH5_rect, mctr1, mcrotrH5_rect);
  mctc1 = coords_set(
#line 194 "ThALES_resolution_v2.instr"
    0,
#line 194 "ThALES_resolution_v2.instr"
    0,
#line 194 "ThALES_resolution_v2.instr"
    2.155);
#line 11746 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaHCS, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH5_rect = coords_add(mcposaHCS, mctc2);
  mctc1 = coords_sub(mcposaH5, mcposaH5_rect);
  mcposrH5_rect = rot_apply(mcrotaH5_rect, mctc1);
  mcDEBUG_COMPONENT("H5_rect", mcposaH5_rect, mcrotaH5_rect)
  mccomp_posa[4] = mcposaH5_rect;
  mccomp_posr[4] = mcposrH5_rect;
  mcNCounter[4]  = mcPCounter[4] = mcP2Counter[4] = 0;
  mcAbsorbProp[4]= 0;
    /* Component H53_origin. */
  /* Setting parameters for component H53_origin. */
  SIG_MESSAGE("H53_origin (Init:SetPar)");

  SIG_MESSAGE("H53_origin (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 199 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 199 "ThALES_resolution_v2.instr"
    (1.5)*DEG2RAD,
#line 199 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 11769 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH5, mcrotaH53_origin);
  rot_transpose(mcrotaH5_rect, mctr1);
  rot_mul(mcrotaH53_origin, mctr1, mcrotrH53_origin);
  mctc1 = coords_set(
#line 198 "ThALES_resolution_v2.instr"
    0.17 / 2 -0.06 / 2,
#line 198 "ThALES_resolution_v2.instr"
    0,
#line 198 "ThALES_resolution_v2.instr"
    1 + gGap);
#line 11780 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH5, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_origin = coords_add(mcposaH5, mctc2);
  mctc1 = coords_sub(mcposaH5_rect, mcposaH53_origin);
  mcposrH53_origin = rot_apply(mcrotaH53_origin, mctc1);
  mcDEBUG_COMPONENT("H53_origin", mcposaH53_origin, mcrotaH53_origin)
  mccomp_posa[5] = mcposaH53_origin;
  mccomp_posr[5] = mcposrH53_origin;
  mcNCounter[5]  = mcPCounter[5] = mcP2Counter[5] = 0;
  mcAbsorbProp[5]= 0;
    /* Component H53_start. */
  /* Setting parameters for component H53_start. */
  SIG_MESSAGE("H53_start (Init:SetPar)");

  SIG_MESSAGE("H53_start (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11800 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_origin, mcrotaH53_start);
  rot_transpose(mcrotaH53_origin, mctr1);
  rot_mul(mcrotaH53_start, mctr1, mcrotrH53_start);
  mctc1 = coords_set(
#line 205 "ThALES_resolution_v2.instr"
    0,
#line 205 "ThALES_resolution_v2.instr"
    0,
#line 205 "ThALES_resolution_v2.instr"
    0);
#line 11811 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_origin, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_start = coords_add(mcposaH53_origin, mctc2);
  mctc1 = coords_sub(mcposaH53_origin, mcposaH53_start);
  mcposrH53_start = rot_apply(mcrotaH53_start, mctc1);
  mcDEBUG_COMPONENT("H53_start", mcposaH53_start, mcrotaH53_start)
  mccomp_posa[6] = mcposaH53_start;
  mccomp_posr[6] = mcposrH53_start;
  mcNCounter[6]  = mcPCounter[6] = mcP2Counter[6] = 0;
  mcAbsorbProp[6]= 0;
    /* Component H53_inpile. */
  /* Setting parameters for component H53_inpile. */
  SIG_MESSAGE("H53_inpile (Init:SetPar)");
#line 207 "ThALES_resolution_v2.instr"
  mccH53_inpile_w1 = 0.06;
#line 192 "ThALES_resolution_v2.instr"
  mccH53_inpile_h1 = 0.12;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_inpile_w2 = 0;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_inpile_h2 = 0;
#line 207 "ThALES_resolution_v2.instr"
  mccH53_inpile_l = 4.930 -3.155;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_inpile_R0 = gR0;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_inpile_Qc = gQc;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_inpile_alpha = gAlpha;
#line 207 "ThALES_resolution_v2.instr"
  mccH53_inpile_m = 3;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_inpile_W = gW;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_inpile_nslit = 1;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_inpile_d = 0.0005;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_mleft = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_mright = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_mtop = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_mbottom = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_nhslit = 1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_inpile_G = 0;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_inpile_aleft = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_inpile_aright = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_inpile_atop = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_inpile_abottom = -1;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_inpile_wavy = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_inpile_wavy_z = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_inpile_wavy_tb = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_inpile_wavy_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_inpile_chamfers = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_inpile_chamfers_z = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_inpile_chamfers_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_inpile_chamfers_tb = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_inpile_nelements = 1;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_inpile_nu = 0;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_inpile_phase = 0;
#line 119 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccH53_inpile_reflect, "NULL" ? "NULL" : "", 16384); else mccH53_inpile_reflect[0]='\0';
#line 11893 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H53_inpile (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 11900 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_start, mcrotaH53_inpile);
  rot_transpose(mcrotaH53_start, mctr1);
  rot_mul(mcrotaH53_inpile, mctr1, mcrotrH53_inpile);
  mctc1 = coords_set(
#line 208 "ThALES_resolution_v2.instr"
    0,
#line 208 "ThALES_resolution_v2.instr"
    0,
#line 208 "ThALES_resolution_v2.instr"
    0);
#line 11911 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_start, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_inpile = coords_add(mcposaH53_start, mctc2);
  mctc1 = coords_sub(mcposaH53_start, mcposaH53_inpile);
  mcposrH53_inpile = rot_apply(mcrotaH53_inpile, mctc1);
  mcDEBUG_COMPONENT("H53_inpile", mcposaH53_inpile, mcrotaH53_inpile)
  mccomp_posa[7] = mcposaH53_inpile;
  mccomp_posr[7] = mcposrH53_inpile;
  mcNCounter[7]  = mcPCounter[7] = mcP2Counter[7] = 0;
  mcAbsorbProp[7]= 0;
    /* Component H53_Obt. */
  /* Setting parameters for component H53_Obt. */
  SIG_MESSAGE("H53_Obt (Init:SetPar)");
#line 210 "ThALES_resolution_v2.instr"
  mccH53_Obt_w1 = 0.06;
#line 192 "ThALES_resolution_v2.instr"
  mccH53_Obt_h1 = 0.12;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_Obt_w2 = 0;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_Obt_h2 = 0;
#line 210 "ThALES_resolution_v2.instr"
  mccH53_Obt_l = 3;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_Obt_R0 = gR0;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_Obt_Qc = gQc;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_Obt_alpha = gAlpha;
#line 210 "ThALES_resolution_v2.instr"
  mccH53_Obt_m = 3;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_Obt_W = gW;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_Obt_nslit = 1;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_Obt_d = 0.0005;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_mleft = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_mright = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_mtop = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_mbottom = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_nhslit = 1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_Obt_G = 0;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_Obt_aleft = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_Obt_aright = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_Obt_atop = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_Obt_abottom = -1;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_Obt_wavy = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_Obt_wavy_z = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_Obt_wavy_tb = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_Obt_wavy_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_Obt_chamfers = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_Obt_chamfers_z = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_Obt_chamfers_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_Obt_chamfers_tb = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_Obt_nelements = 1;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_Obt_nu = 0;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_Obt_phase = 0;
#line 119 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccH53_Obt_reflect, "NULL" ? "NULL" : "", 16384); else mccH53_Obt_reflect[0]='\0';
#line 11993 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H53_Obt (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12000 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_inpile, mcrotaH53_Obt);
  rot_transpose(mcrotaH53_inpile, mctr1);
  rot_mul(mcrotaH53_Obt, mctr1, mcrotrH53_Obt);
  mctc1 = coords_set(
#line 211 "ThALES_resolution_v2.instr"
    0,
#line 211 "ThALES_resolution_v2.instr"
    0,
#line 211 "ThALES_resolution_v2.instr"
    Al_Thickness + 0.015 + 4.930 -3.155);
#line 12011 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_inpile, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_Obt = coords_add(mcposaH53_inpile, mctc2);
  mctc1 = coords_sub(mcposaH53_inpile, mcposaH53_Obt);
  mcposrH53_Obt = rot_apply(mcrotaH53_Obt, mctc1);
  mcDEBUG_COMPONENT("H53_Obt", mcposaH53_Obt, mcrotaH53_Obt)
  mccomp_posa[8] = mcposaH53_Obt;
  mccomp_posr[8] = mcposrH53_Obt;
  mcNCounter[8]  = mcPCounter[8] = mcP2Counter[8] = 0;
  mcAbsorbProp[8]= 0;
    /* Component H53_Obt_Out. */
  /* Setting parameters for component H53_Obt_Out. */
  SIG_MESSAGE("H53_Obt_Out (Init:SetPar)");

  SIG_MESSAGE("H53_Obt_Out (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12031 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_Obt, mcrotaH53_Obt_Out);
  rot_transpose(mcrotaH53_Obt, mctr1);
  rot_mul(mcrotaH53_Obt_Out, mctr1, mcrotrH53_Obt_Out);
  mctc1 = coords_set(
#line 214 "ThALES_resolution_v2.instr"
    0,
#line 214 "ThALES_resolution_v2.instr"
    0,
#line 214 "ThALES_resolution_v2.instr"
    3 + 0.04);
#line 12042 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_Obt, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_Obt_Out = coords_add(mcposaH53_Obt, mctc2);
  mctc1 = coords_sub(mcposaH53_Obt, mcposaH53_Obt_Out);
  mcposrH53_Obt_Out = rot_apply(mcrotaH53_Obt_Out, mctc1);
  mcDEBUG_COMPONENT("H53_Obt_Out", mcposaH53_Obt_Out, mcrotaH53_Obt_Out)
  mccomp_posa[9] = mcposaH53_Obt_Out;
  mccomp_posr[9] = mcposrH53_Obt_Out;
  mcNCounter[9]  = mcPCounter[9] = mcP2Counter[9] = 0;
  mcAbsorbProp[9]= 0;
    /* Component H53_VSComC1. */
  /* Setting parameters for component H53_VSComC1. */
  SIG_MESSAGE("H53_VSComC1 (Init:SetPar)");
#line 207 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_w1 = 0.06;
#line 192 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_h1 = 0.12;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_w2 = 0;
#line 113 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_h2 = 0;
#line 217 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_l = 7;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_R0 = gR0;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_Qc = gQc;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_alpha = gAlpha;
#line 207 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_m = 3;
#line 193 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_W = gW;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_nslit = 1;
#line 114 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_d = 0.0005;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_mleft = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_mright = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_mtop = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_mbottom = -1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_nhslit = 1;
#line 115 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_G = 0;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_aleft = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_aright = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_atop = -1;
#line 116 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_abottom = -1;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_wavy = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_wavy_z = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_wavy_tb = 0;
#line 117 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_wavy_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_chamfers = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_chamfers_z = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_chamfers_lr = 0;
#line 118 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_chamfers_tb = 0;
#line 217 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_nelements = 7;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_nu = 0;
#line 119 "ThALES_resolution_v2.instr"
  mccH53_VSComC1_phase = 0;
#line 119 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccH53_VSComC1_reflect, "NULL" ? "NULL" : "", 16384); else mccH53_VSComC1_reflect[0]='\0';
#line 12124 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H53_VSComC1 (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12131 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_Obt, mcrotaH53_VSComC1);
  rot_transpose(mcrotaH53_Obt_Out, mctr1);
  rot_mul(mcrotaH53_VSComC1, mctr1, mcrotrH53_VSComC1);
  mctc1 = coords_set(
#line 218 "ThALES_resolution_v2.instr"
    0,
#line 218 "ThALES_resolution_v2.instr"
    0,
#line 218 "ThALES_resolution_v2.instr"
    3 + 0.075);
#line 12142 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_Obt, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_VSComC1 = coords_add(mcposaH53_Obt, mctc2);
  mctc1 = coords_sub(mcposaH53_Obt_Out, mcposaH53_VSComC1);
  mcposrH53_VSComC1 = rot_apply(mcrotaH53_VSComC1, mctc1);
  mcDEBUG_COMPONENT("H53_VSComC1", mcposaH53_VSComC1, mcrotaH53_VSComC1)
  mccomp_posa[10] = mcposaH53_VSComC1;
  mccomp_posr[10] = mcposrH53_VSComC1;
  mcNCounter[10]  = mcPCounter[10] = mcP2Counter[10] = 0;
  mcAbsorbProp[10]= 0;
    /* Component H53_Nose. */
  /* Setting parameters for component H53_Nose. */
  SIG_MESSAGE("H53_Nose (Init:SetPar)");
#line 225 "ThALES_resolution_v2.instr"
  if("parabolical") strncpy(mccH53_Nose_option, "parabolical" ? "parabolical" : "", 16384); else mccH53_Nose_option[0]='\0';
#line 223 "ThALES_resolution_v2.instr"
  mccH53_Nose_w1 = 0.06;
#line 223 "ThALES_resolution_v2.instr"
  mccH53_Nose_h1 = 0.12;
#line 224 "ThALES_resolution_v2.instr"
  mccH53_Nose_l = 2.0;
#line 224 "ThALES_resolution_v2.instr"
  mccH53_Nose_linw = 0.0;
#line 224 "ThALES_resolution_v2.instr"
  mccH53_Nose_loutw = 0.7;
#line 224 "ThALES_resolution_v2.instr"
  mccH53_Nose_linh = 0.0;
#line 225 "ThALES_resolution_v2.instr"
  mccH53_Nose_louth = 0.0;
#line 225 "ThALES_resolution_v2.instr"
  mccH53_Nose_R0 = gR0;
#line 226 "ThALES_resolution_v2.instr"
  mccH53_Nose_Qcx = gQc;
#line 226 "ThALES_resolution_v2.instr"
  mccH53_Nose_Qcy = gQc;
#line 226 "ThALES_resolution_v2.instr"
  mccH53_Nose_alphax = gAlpha;
#line 227 "ThALES_resolution_v2.instr"
  mccH53_Nose_alphay = gAlpha;
#line 227 "ThALES_resolution_v2.instr"
  mccH53_Nose_W = gW;
#line 228 "ThALES_resolution_v2.instr"
  mccH53_Nose_mx = 3;
#line 228 "ThALES_resolution_v2.instr"
  mccH53_Nose_my = 3;
#line 228 "ThALES_resolution_v2.instr"
  mccH53_Nose_segno = 20;
#line 83 "ThALES_resolution_v2.instr"
  mccH53_Nose_curvature = 0;
#line 83 "ThALES_resolution_v2.instr"
  mccH53_Nose_curvature_v = 0;
#line 12194 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H53_Nose (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12201 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_VSComC1, mcrotaH53_Nose);
  rot_transpose(mcrotaH53_VSComC1, mctr1);
  rot_mul(mcrotaH53_Nose, mctr1, mcrotrH53_Nose);
  mctc1 = coords_set(
#line 229 "ThALES_resolution_v2.instr"
    0,
#line 229 "ThALES_resolution_v2.instr"
    0,
#line 229 "ThALES_resolution_v2.instr"
    7 + 0.01);
#line 12212 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_VSComC1, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_Nose = coords_add(mcposaH53_VSComC1, mctc2);
  mctc1 = coords_sub(mcposaH53_VSComC1, mcposaH53_Nose);
  mcposrH53_Nose = rot_apply(mcrotaH53_Nose, mctc1);
  mcDEBUG_COMPONENT("H53_Nose", mcposaH53_Nose, mcrotaH53_Nose)
  mccomp_posa[11] = mcposaH53_Nose;
  mccomp_posr[11] = mcposrH53_Nose;
  mcNCounter[11]  = mcPCounter[11] = mcP2Counter[11] = 0;
  mcAbsorbProp[11]= 0;
    /* Component before_monochromator_slit. */
  /* Setting parameters for component before_monochromator_slit. */
  SIG_MESSAGE("before_monochromator_slit (Init:SetPar)");
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_xmin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_xmax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_ymin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_ymax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_radius = 0;
#line 235 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_xwidth = 0.04;
#line 235 "ThALES_resolution_v2.instr"
  mccbefore_monochromator_slit_yheight = 0.12;
#line 12240 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("before_monochromator_slit (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12247 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_Nose, mcrotabefore_monochromator_slit);
  rot_transpose(mcrotaH53_Nose, mctr1);
  rot_mul(mcrotabefore_monochromator_slit, mctr1, mcrotrbefore_monochromator_slit);
  mctc1 = coords_set(
#line 236 "ThALES_resolution_v2.instr"
    0,
#line 236 "ThALES_resolution_v2.instr"
    0,
#line 236 "ThALES_resolution_v2.instr"
    2.3);
#line 12258 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_Nose, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposabefore_monochromator_slit = coords_add(mcposaH53_Nose, mctc2);
  mctc1 = coords_sub(mcposaH53_Nose, mcposabefore_monochromator_slit);
  mcposrbefore_monochromator_slit = rot_apply(mcrotabefore_monochromator_slit, mctc1);
  mcDEBUG_COMPONENT("before_monochromator_slit", mcposabefore_monochromator_slit, mcrotabefore_monochromator_slit)
  mccomp_posa[12] = mcposabefore_monochromator_slit;
  mccomp_posr[12] = mcposrbefore_monochromator_slit;
  mcNCounter[12]  = mcPCounter[12] = mcP2Counter[12] = 0;
  mcAbsorbProp[12]= 0;
    /* Component l_monitor. */
  /* Setting parameters for component l_monitor. */
  SIG_MESSAGE("l_monitor (Init:SetPar)");
#line 240 "ThALES_resolution_v2.instr"
  if("lambda_slit_mono") strncpy(mccl_monitor_filename, "lambda_slit_mono" ? "lambda_slit_mono" : "", 16384); else mccl_monitor_filename[0]='\0';
#line 50 "ThALES_resolution_v2.instr"
  mccl_monitor_xmin = -0.05;
#line 50 "ThALES_resolution_v2.instr"
  mccl_monitor_xmax = 0.05;
#line 50 "ThALES_resolution_v2.instr"
  mccl_monitor_ymin = -0.05;
#line 50 "ThALES_resolution_v2.instr"
  mccl_monitor_ymax = 0.05;
#line 241 "ThALES_resolution_v2.instr"
  mccl_monitor_xwidth = 0.5;
#line 242 "ThALES_resolution_v2.instr"
  mccl_monitor_yheight = 0.5;
#line 243 "ThALES_resolution_v2.instr"
  mccl_monitor_Lmin = 0;
#line 244 "ThALES_resolution_v2.instr"
  mccl_monitor_Lmax = 10;
#line 245 "ThALES_resolution_v2.instr"
  mccl_monitor_restore_neutron = 1;
#line 51 "ThALES_resolution_v2.instr"
  mccl_monitor_nowritefile = 0;
#line 12294 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("l_monitor (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12301 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotabefore_monochromator_slit, mcrotal_monitor);
  rot_transpose(mcrotabefore_monochromator_slit, mctr1);
  rot_mul(mcrotal_monitor, mctr1, mcrotrl_monitor);
  mctc1 = coords_set(
#line 246 "ThALES_resolution_v2.instr"
    0,
#line 246 "ThALES_resolution_v2.instr"
    0,
#line 246 "ThALES_resolution_v2.instr"
    0.001);
#line 12312 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotabefore_monochromator_slit, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposal_monitor = coords_add(mcposabefore_monochromator_slit, mctc2);
  mctc1 = coords_sub(mcposabefore_monochromator_slit, mcposal_monitor);
  mcposrl_monitor = rot_apply(mcrotal_monitor, mctc1);
  mcDEBUG_COMPONENT("l_monitor", mcposal_monitor, mcrotal_monitor)
  mccomp_posa[13] = mcposal_monitor;
  mccomp_posr[13] = mcposrl_monitor;
  mcNCounter[13]  = mcPCounter[13] = mcP2Counter[13] = 0;
  mcAbsorbProp[13]= 0;
    /* Component H53_ThALES_Monochromator_Cradle. */
  /* Setting parameters for component H53_ThALES_Monochromator_Cradle. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Cradle (Init:SetPar)");

  SIG_MESSAGE("H53_ThALES_Monochromator_Cradle (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12332 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_Nose, mcrotaH53_ThALES_Monochromator_Cradle);
  rot_transpose(mcrotal_monitor, mctr1);
  rot_mul(mcrotaH53_ThALES_Monochromator_Cradle, mctr1, mcrotrH53_ThALES_Monochromator_Cradle);
  mctc1 = coords_set(
#line 249 "ThALES_resolution_v2.instr"
    0,
#line 249 "ThALES_resolution_v2.instr"
    0,
#line 249 "ThALES_resolution_v2.instr"
    2 + 2.3);
#line 12343 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_Nose, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_ThALES_Monochromator_Cradle = coords_add(mcposaH53_Nose, mctc2);
  mctc1 = coords_sub(mcposal_monitor, mcposaH53_ThALES_Monochromator_Cradle);
  mcposrH53_ThALES_Monochromator_Cradle = rot_apply(mcrotaH53_ThALES_Monochromator_Cradle, mctc1);
  mcDEBUG_COMPONENT("H53_ThALES_Monochromator_Cradle", mcposaH53_ThALES_Monochromator_Cradle, mcrotaH53_ThALES_Monochromator_Cradle)
  mccomp_posa[14] = mcposaH53_ThALES_Monochromator_Cradle;
  mccomp_posr[14] = mcposrH53_ThALES_Monochromator_Cradle;
  mcNCounter[14]  = mcPCounter[14] = mcP2Counter[14] = 0;
  mcAbsorbProp[14]= 0;
    /* Component H53_ThALES_Monochromator. */
  /* Setting parameters for component H53_ThALES_Monochromator. */
  SIG_MESSAGE("H53_ThALES_Monochromator (Init:SetPar)");
#line 255 "ThALES_resolution_v2.instr"
  if("HOPG.rfl") strncpy(mccH53_ThALES_Monochromator_reflect, "HOPG.rfl" ? "HOPG.rfl" : "", 16384); else mccH53_ThALES_Monochromator_reflect[0]='\0';
#line 255 "ThALES_resolution_v2.instr"
  if("HOPG.trm") strncpy(mccH53_ThALES_Monochromator_transmit, "HOPG.trm" ? "HOPG.trm" : "", 16384); else mccH53_ThALES_Monochromator_transmit[0]='\0';
#line 100 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_zwidth = 0.01;
#line 100 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_yheight = 0.01;
#line 253 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_gap = 0.0005;
#line 253 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_NH = 13;
#line 253 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_NV = 13;
#line 254 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_mosaich = 30;
#line 254 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_mosaicv = 30;
#line 255 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_r0 = 1;
#line 101 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_t0 = 1.0;
#line 101 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_Q = 1.8734;
#line 254 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_RV = ThALES_RMV;
#line 254 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_RH = ThALES_RMH;
#line 254 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_DM = ThALES_DM;
#line 102 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_mosaic = 0;
#line 253 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_width = 0.25;
#line 253 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_height = 0.2;
#line 102 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_verbose = 0;
#line 102 "ThALES_resolution_v2.instr"
  mccH53_ThALES_Monochromator_order = 0;
#line 12397 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("H53_ThALES_Monochromator (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 257 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 257 "ThALES_resolution_v2.instr"
    (ThALES_A1)*DEG2RAD,
#line 257 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 12407 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_ThALES_Monochromator_Cradle, mcrotaH53_ThALES_Monochromator);
  rot_transpose(mcrotaH53_ThALES_Monochromator_Cradle, mctr1);
  rot_mul(mcrotaH53_ThALES_Monochromator, mctr1, mcrotrH53_ThALES_Monochromator);
  mctc1 = coords_set(
#line 256 "ThALES_resolution_v2.instr"
    0,
#line 256 "ThALES_resolution_v2.instr"
    0,
#line 256 "ThALES_resolution_v2.instr"
    0);
#line 12418 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_ThALES_Monochromator_Cradle, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_ThALES_Monochromator = coords_add(mcposaH53_ThALES_Monochromator_Cradle, mctc2);
  mctc1 = coords_sub(mcposaH53_ThALES_Monochromator_Cradle, mcposaH53_ThALES_Monochromator);
  mcposrH53_ThALES_Monochromator = rot_apply(mcrotaH53_ThALES_Monochromator, mctc1);
  mcDEBUG_COMPONENT("H53_ThALES_Monochromator", mcposaH53_ThALES_Monochromator, mcrotaH53_ThALES_Monochromator)
  mccomp_posa[15] = mcposaH53_ThALES_Monochromator;
  mccomp_posr[15] = mcposrH53_ThALES_Monochromator;
  mcNCounter[15]  = mcPCounter[15] = mcP2Counter[15] = 0;
  mcAbsorbProp[15]= 0;
    /* Component H53_ThALES_Monochromator_Out. */
  /* Setting parameters for component H53_ThALES_Monochromator_Out. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Out (Init:SetPar)");

  SIG_MESSAGE("H53_ThALES_Monochromator_Out (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 264 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 264 "ThALES_resolution_v2.instr"
    (2 * ThALES_A1)*DEG2RAD,
#line 264 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 12441 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_ThALES_Monochromator_Cradle, mcrotaH53_ThALES_Monochromator_Out);
  rot_transpose(mcrotaH53_ThALES_Monochromator, mctr1);
  rot_mul(mcrotaH53_ThALES_Monochromator_Out, mctr1, mcrotrH53_ThALES_Monochromator_Out);
  mctc1 = coords_set(
#line 263 "ThALES_resolution_v2.instr"
    0,
#line 263 "ThALES_resolution_v2.instr"
    0,
#line 263 "ThALES_resolution_v2.instr"
    0);
#line 12452 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_ThALES_Monochromator_Cradle, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaH53_ThALES_Monochromator_Out = coords_add(mcposaH53_ThALES_Monochromator_Cradle, mctc2);
  mctc1 = coords_sub(mcposaH53_ThALES_Monochromator, mcposaH53_ThALES_Monochromator_Out);
  mcposrH53_ThALES_Monochromator_Out = rot_apply(mcrotaH53_ThALES_Monochromator_Out, mctc1);
  mcDEBUG_COMPONENT("H53_ThALES_Monochromator_Out", mcposaH53_ThALES_Monochromator_Out, mcrotaH53_ThALES_Monochromator_Out)
  mccomp_posa[16] = mcposaH53_ThALES_Monochromator_Out;
  mccomp_posr[16] = mcposrH53_ThALES_Monochromator_Out;
  mcNCounter[16]  = mcPCounter[16] = mcP2Counter[16] = 0;
  mcAbsorbProp[16]= 0;
    /* Component before_sample_slit. */
  /* Setting parameters for component before_sample_slit. */
  SIG_MESSAGE("before_sample_slit (Init:SetPar)");
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_xmin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_xmax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_ymin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_ymax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_radius = 0;
#line 266 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_xwidth = 0.03;
#line 266 "ThALES_resolution_v2.instr"
  mccbefore_sample_slit_yheight = 0.028;
#line 12480 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("before_sample_slit (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12487 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_ThALES_Monochromator_Out, mcrotabefore_sample_slit);
  rot_transpose(mcrotaH53_ThALES_Monochromator_Out, mctr1);
  rot_mul(mcrotabefore_sample_slit, mctr1, mcrotrbefore_sample_slit);
  mctc1 = coords_set(
#line 267 "ThALES_resolution_v2.instr"
    0,
#line 267 "ThALES_resolution_v2.instr"
    0,
#line 267 "ThALES_resolution_v2.instr"
    ThALES_L -0.250);
#line 12498 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_ThALES_Monochromator_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposabefore_sample_slit = coords_add(mcposaH53_ThALES_Monochromator_Out, mctc2);
  mctc1 = coords_sub(mcposaH53_ThALES_Monochromator_Out, mcposabefore_sample_slit);
  mcposrbefore_sample_slit = rot_apply(mcrotabefore_sample_slit, mctc1);
  mcDEBUG_COMPONENT("before_sample_slit", mcposabefore_sample_slit, mcrotabefore_sample_slit)
  mccomp_posa[17] = mcposabefore_sample_slit;
  mccomp_posr[17] = mcposrbefore_sample_slit;
  mcNCounter[17]  = mcPCounter[17] = mcP2Counter[17] = 0;
  mcAbsorbProp[17]= 0;
    /* Component E_sample_mon. */
  /* Setting parameters for component E_sample_mon. */
  SIG_MESSAGE("E_sample_mon (Init:SetPar)");
#line 270 "ThALES_resolution_v2.instr"
  if("E_sample_mon") strncpy(mccE_sample_mon_filename, "E_sample_mon" ? "E_sample_mon" : "", 16384); else mccE_sample_mon_filename[0]='\0';
#line 53 "ThALES_resolution_v2.instr"
  mccE_sample_mon_xmin = -0.05;
#line 53 "ThALES_resolution_v2.instr"
  mccE_sample_mon_xmax = 0.05;
#line 53 "ThALES_resolution_v2.instr"
  mccE_sample_mon_ymin = -0.05;
#line 53 "ThALES_resolution_v2.instr"
  mccE_sample_mon_ymax = 0.05;
#line 270 "ThALES_resolution_v2.instr"
  mccE_sample_mon_xwidth = 0.05;
#line 271 "ThALES_resolution_v2.instr"
  mccE_sample_mon_yheight = 0.05;
#line 271 "ThALES_resolution_v2.instr"
  mccE_sample_mon_Emin = mcipEi - mcipThALES_dE;
#line 271 "ThALES_resolution_v2.instr"
  mccE_sample_mon_Emax = mcipEi + mcipThALES_dE;
#line 271 "ThALES_resolution_v2.instr"
  mccE_sample_mon_restore_neutron = 1;
#line 54 "ThALES_resolution_v2.instr"
  mccE_sample_mon_nowritefile = 0;
#line 12534 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("E_sample_mon (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12541 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_ThALES_Monochromator_Out, mcrotaE_sample_mon);
  rot_transpose(mcrotabefore_sample_slit, mctr1);
  rot_mul(mcrotaE_sample_mon, mctr1, mcrotrE_sample_mon);
  mctc1 = coords_set(
#line 272 "ThALES_resolution_v2.instr"
    0,
#line 272 "ThALES_resolution_v2.instr"
    0,
#line 272 "ThALES_resolution_v2.instr"
    ThALES_L -0.050);
#line 12552 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_ThALES_Monochromator_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaE_sample_mon = coords_add(mcposaH53_ThALES_Monochromator_Out, mctc2);
  mctc1 = coords_sub(mcposabefore_sample_slit, mcposaE_sample_mon);
  mcposrE_sample_mon = rot_apply(mcrotaE_sample_mon, mctc1);
  mcDEBUG_COMPONENT("E_sample_mon", mcposaE_sample_mon, mcrotaE_sample_mon)
  mccomp_posa[18] = mcposaE_sample_mon;
  mccomp_posr[18] = mcposrE_sample_mon;
  mcNCounter[18]  = mcPCounter[18] = mcP2Counter[18] = 0;
  mcAbsorbProp[18]= 0;
    /* Component PSD_sample_mon. */
  /* Setting parameters for component PSD_sample_mon. */
  SIG_MESSAGE("PSD_sample_mon (Init:SetPar)");
#line 275 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_nx = 200;
#line 275 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_ny = 200;
#line 276 "ThALES_resolution_v2.instr"
  if("PSD_sample_mon.dat") strncpy(mccPSD_sample_mon_filename, "PSD_sample_mon.dat" ? "PSD_sample_mon.dat" : "", 16384); else mccPSD_sample_mon_filename[0]='\0';
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_xmin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_xmax = 0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_ymin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_ymax = 0.05;
#line 276 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_xwidth = 0.05;
#line 276 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_yheight = 0.05;
#line 275 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_restore_neutron = 1;
#line 52 "ThALES_resolution_v2.instr"
  mccPSD_sample_mon_nowritefile = 0;
#line 12588 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("PSD_sample_mon (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12595 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaE_sample_mon, mcrotaPSD_sample_mon);
  rot_transpose(mcrotaE_sample_mon, mctr1);
  rot_mul(mcrotaPSD_sample_mon, mctr1, mcrotrPSD_sample_mon);
  mctc1 = coords_set(
#line 277 "ThALES_resolution_v2.instr"
    0,
#line 277 "ThALES_resolution_v2.instr"
    0,
#line 277 "ThALES_resolution_v2.instr"
    0.001);
#line 12606 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaE_sample_mon, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaPSD_sample_mon = coords_add(mcposaE_sample_mon, mctc2);
  mctc1 = coords_sub(mcposaE_sample_mon, mcposaPSD_sample_mon);
  mcposrPSD_sample_mon = rot_apply(mcrotaPSD_sample_mon, mctc1);
  mcDEBUG_COMPONENT("PSD_sample_mon", mcposaPSD_sample_mon, mcrotaPSD_sample_mon)
  mccomp_posa[19] = mcposaPSD_sample_mon;
  mccomp_posr[19] = mcposrPSD_sample_mon;
  mcNCounter[19]  = mcPCounter[19] = mcP2Counter[19] = 0;
  mcAbsorbProp[19]= 0;
    /* Component sample_arm. */
  /* Setting parameters for component sample_arm. */
  SIG_MESSAGE("sample_arm (Init:SetPar)");

  SIG_MESSAGE("sample_arm (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12626 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaH53_ThALES_Monochromator_Out, mcrotasample_arm);
  rot_transpose(mcrotaPSD_sample_mon, mctr1);
  rot_mul(mcrotasample_arm, mctr1, mcrotrsample_arm);
  mctc1 = coords_set(
#line 280 "ThALES_resolution_v2.instr"
    0,
#line 280 "ThALES_resolution_v2.instr"
    0,
#line 280 "ThALES_resolution_v2.instr"
    ThALES_L);
#line 12637 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaH53_ThALES_Monochromator_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposasample_arm = coords_add(mcposaH53_ThALES_Monochromator_Out, mctc2);
  mctc1 = coords_sub(mcposaPSD_sample_mon, mcposasample_arm);
  mcposrsample_arm = rot_apply(mcrotasample_arm, mctc1);
  mcDEBUG_COMPONENT("sample_arm", mcposasample_arm, mcrotasample_arm)
  mccomp_posa[20] = mcposasample_arm;
  mccomp_posr[20] = mcposrsample_arm;
  mcNCounter[20]  = mcPCounter[20] = mcP2Counter[20] = 0;
  mcAbsorbProp[20]= 0;
    /* Component res_sample. */
  /* Setting parameters for component res_sample. */
  SIG_MESSAGE("res_sample (Init:SetPar)");
#line 284 "ThALES_resolution_v2.instr"
  mccres_sample_thickness = 0.001;
#line 283 "ThALES_resolution_v2.instr"
  mccres_sample_radius = 0.005;
#line 64 "ThALES_resolution_v2.instr"
  mccres_sample_focus_r = 0.05;
#line 285 "ThALES_resolution_v2.instr"
  mccres_sample_E0 = 5;
#line 286 "ThALES_resolution_v2.instr"
  mccres_sample_dE = 0.25;
#line 65 "ThALES_resolution_v2.instr"
  mccres_sample_target_x = 0;
#line 65 "ThALES_resolution_v2.instr"
  mccres_sample_target_y = 0;
#line 65 "ThALES_resolution_v2.instr"
  mccres_sample_target_z = .5;
#line 287 "ThALES_resolution_v2.instr"
  mccres_sample_focus_xw = 0.03;
#line 288 "ThALES_resolution_v2.instr"
  mccres_sample_focus_yh = 0.04;
#line 66 "ThALES_resolution_v2.instr"
  mccres_sample_focus_aw = 0;
#line 66 "ThALES_resolution_v2.instr"
  mccres_sample_focus_ah = 0;
#line 66 "ThALES_resolution_v2.instr"
  mccres_sample_xwidth = 0;
#line 289 "ThALES_resolution_v2.instr"
  mccres_sample_yheight = 0.05;
#line 66 "ThALES_resolution_v2.instr"
  mccres_sample_zdepth = 0;
#line 290 "ThALES_resolution_v2.instr"
  mccres_sample_target_index = 4;
#line 12683 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("res_sample (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12690 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotasample_arm, mcrotares_sample);
  rot_transpose(mcrotasample_arm, mctr1);
  rot_mul(mcrotares_sample, mctr1, mcrotrres_sample);
  mctc1 = coords_set(
#line 291 "ThALES_resolution_v2.instr"
    0,
#line 291 "ThALES_resolution_v2.instr"
    0,
#line 291 "ThALES_resolution_v2.instr"
    0);
#line 12701 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotasample_arm, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposares_sample = coords_add(mcposasample_arm, mctc2);
  mctc1 = coords_sub(mcposasample_arm, mcposares_sample);
  mcposrres_sample = rot_apply(mcrotares_sample, mctc1);
  mcDEBUG_COMPONENT("res_sample", mcposares_sample, mcrotares_sample)
  mccomp_posa[21] = mcposares_sample;
  mccomp_posr[21] = mcposrres_sample;
  mcNCounter[21]  = mcPCounter[21] = mcP2Counter[21] = 0;
  mcAbsorbProp[21]= 0;
    /* Component v_sample. */
  /* Setting parameters for component v_sample. */
  SIG_MESSAGE("v_sample (Init:SetPar)");
#line 304 "ThALES_resolution_v2.instr"
  mccv_sample_radius = 0.005;
#line 305 "ThALES_resolution_v2.instr"
  mccv_sample_thickness = 0.001;
#line 91 "ThALES_resolution_v2.instr"
  mccv_sample_zdepth = 0;
#line 91 "ThALES_resolution_v2.instr"
  mccv_sample_Vc = 13.827;
#line 91 "ThALES_resolution_v2.instr"
  mccv_sample_sigma_abs = 5.08;
#line 91 "ThALES_resolution_v2.instr"
  mccv_sample_sigma_inc = 5.08;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_radius_i = 0;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_radius_o = 0;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_h = 0;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_focus_r = 0;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_pack = 1;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_frac = 1;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_f_QE = 0;
#line 92 "ThALES_resolution_v2.instr"
  mccv_sample_gamma = 0;
#line 93 "ThALES_resolution_v2.instr"
  mccv_sample_target_x = 0;
#line 93 "ThALES_resolution_v2.instr"
  mccv_sample_target_y = 0;
#line 93 "ThALES_resolution_v2.instr"
  mccv_sample_target_z = 0;
#line 306 "ThALES_resolution_v2.instr"
  mccv_sample_focus_xw = 0.03;
#line 307 "ThALES_resolution_v2.instr"
  mccv_sample_focus_yh = 0.04;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_focus_aw = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_focus_ah = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_xwidth = 0;
#line 308 "ThALES_resolution_v2.instr"
  mccv_sample_yheight = 0.05;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_zthick = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_rad_sphere = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_sig_a = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_sig_i = 0;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_V0 = 0;
#line 309 "ThALES_resolution_v2.instr"
  mccv_sample_target_index = 3;
#line 94 "ThALES_resolution_v2.instr"
  mccv_sample_multiples = 1;
#line 12775 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("v_sample (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12782 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotasample_arm, mcrotav_sample);
  rot_transpose(mcrotares_sample, mctr1);
  rot_mul(mcrotav_sample, mctr1, mcrotrv_sample);
  mctc1 = coords_set(
#line 310 "ThALES_resolution_v2.instr"
    0,
#line 310 "ThALES_resolution_v2.instr"
    0,
#line 310 "ThALES_resolution_v2.instr"
    0);
#line 12793 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotasample_arm, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposav_sample = coords_add(mcposasample_arm, mctc2);
  mctc1 = coords_sub(mcposares_sample, mcposav_sample);
  mcposrv_sample = rot_apply(mcrotav_sample, mctc1);
  mcDEBUG_COMPONENT("v_sample", mcposav_sample, mcrotav_sample)
  mccomp_posa[22] = mcposav_sample;
  mccomp_posr[22] = mcposrv_sample;
  mcNCounter[22]  = mcPCounter[22] = mcP2Counter[22] = 0;
  mcAbsorbProp[22]= 0;
    /* Component Sample_Out. */
  /* Setting parameters for component Sample_Out. */
  SIG_MESSAGE("Sample_Out (Init:SetPar)");

  SIG_MESSAGE("Sample_Out (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 315 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 315 "ThALES_resolution_v2.instr"
    (- mcipA4)*DEG2RAD,
#line 315 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 12816 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotasample_arm, mcrotaSample_Out);
  rot_transpose(mcrotav_sample, mctr1);
  rot_mul(mcrotaSample_Out, mctr1, mcrotrSample_Out);
  mctc1 = coords_set(
#line 314 "ThALES_resolution_v2.instr"
    0,
#line 314 "ThALES_resolution_v2.instr"
    0,
#line 314 "ThALES_resolution_v2.instr"
    0);
#line 12827 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotasample_arm, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaSample_Out = coords_add(mcposasample_arm, mctc2);
  mctc1 = coords_sub(mcposav_sample, mcposaSample_Out);
  mcposrSample_Out = rot_apply(mcrotaSample_Out, mctc1);
  mcDEBUG_COMPONENT("Sample_Out", mcposaSample_Out, mcrotaSample_Out)
  mccomp_posa[23] = mcposaSample_Out;
  mccomp_posr[23] = mcposrSample_Out;
  mcNCounter[23]  = mcPCounter[23] = mcP2Counter[23] = 0;
  mcAbsorbProp[23]= 0;
    /* Component after_sample_slit. */
  /* Setting parameters for component after_sample_slit. */
  SIG_MESSAGE("after_sample_slit (Init:SetPar)");
#line 46 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_xmin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_xmax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_ymin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_ymax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_radius = 0;
#line 317 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_xwidth = 0.03;
#line 317 "ThALES_resolution_v2.instr"
  mccafter_sample_slit_yheight = 0.04;
#line 12855 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("after_sample_slit (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12862 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaSample_Out, mcrotaafter_sample_slit);
  rot_transpose(mcrotaSample_Out, mctr1);
  rot_mul(mcrotaafter_sample_slit, mctr1, mcrotrafter_sample_slit);
  mctc1 = coords_set(
#line 318 "ThALES_resolution_v2.instr"
    0,
#line 318 "ThALES_resolution_v2.instr"
    0,
#line 318 "ThALES_resolution_v2.instr"
    0.250);
#line 12873 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaSample_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaafter_sample_slit = coords_add(mcposaSample_Out, mctc2);
  mctc1 = coords_sub(mcposaSample_Out, mcposaafter_sample_slit);
  mcposrafter_sample_slit = rot_apply(mcrotaafter_sample_slit, mctc1);
  mcDEBUG_COMPONENT("after_sample_slit", mcposaafter_sample_slit, mcrotaafter_sample_slit)
  mccomp_posa[24] = mcposaafter_sample_slit;
  mccomp_posr[24] = mcposrafter_sample_slit;
  mcNCounter[24]  = mcPCounter[24] = mcP2Counter[24] = 0;
  mcAbsorbProp[24]= 0;
    /* Component Ana_Cradle. */
  /* Setting parameters for component Ana_Cradle. */
  SIG_MESSAGE("Ana_Cradle (Init:SetPar)");

  SIG_MESSAGE("Ana_Cradle (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12893 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaSample_Out, mcrotaAna_Cradle);
  rot_transpose(mcrotaafter_sample_slit, mctr1);
  rot_mul(mcrotaAna_Cradle, mctr1, mcrotrAna_Cradle);
  mctc1 = coords_set(
#line 321 "ThALES_resolution_v2.instr"
    0,
#line 321 "ThALES_resolution_v2.instr"
    0,
#line 321 "ThALES_resolution_v2.instr"
    dist_sample_ana);
#line 12904 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaSample_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaAna_Cradle = coords_add(mcposaSample_Out, mctc2);
  mctc1 = coords_sub(mcposaafter_sample_slit, mcposaAna_Cradle);
  mcposrAna_Cradle = rot_apply(mcrotaAna_Cradle, mctc1);
  mcDEBUG_COMPONENT("Ana_Cradle", mcposaAna_Cradle, mcrotaAna_Cradle)
  mccomp_posa[25] = mcposaAna_Cradle;
  mccomp_posr[25] = mcposrAna_Cradle;
  mcNCounter[25]  = mcPCounter[25] = mcP2Counter[25] = 0;
  mcAbsorbProp[25]= 0;
    /* Component PSD_analyzer. */
  /* Setting parameters for component PSD_analyzer. */
  SIG_MESSAGE("PSD_analyzer (Init:SetPar)");
#line 324 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_nx = 200;
#line 324 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_ny = 200;
#line 325 "ThALES_resolution_v2.instr"
  if("PSD_ana.dat") strncpy(mccPSD_analyzer_filename, "PSD_ana.dat" ? "PSD_ana.dat" : "", 16384); else mccPSD_analyzer_filename[0]='\0';
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_xmin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_xmax = 0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_ymin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_ymax = 0.05;
#line 325 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_xwidth = 0.25;
#line 325 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_yheight = 0.25;
#line 324 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_restore_neutron = 1;
#line 52 "ThALES_resolution_v2.instr"
  mccPSD_analyzer_nowritefile = 0;
#line 12940 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("PSD_analyzer (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 12947 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Cradle, mcrotaPSD_analyzer);
  rot_transpose(mcrotaAna_Cradle, mctr1);
  rot_mul(mcrotaPSD_analyzer, mctr1, mcrotrPSD_analyzer);
  mctc1 = coords_set(
#line 326 "ThALES_resolution_v2.instr"
    0,
#line 326 "ThALES_resolution_v2.instr"
    0,
#line 326 "ThALES_resolution_v2.instr"
    0);
#line 12958 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Cradle, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaPSD_analyzer = coords_add(mcposaAna_Cradle, mctc2);
  mctc1 = coords_sub(mcposaAna_Cradle, mcposaPSD_analyzer);
  mcposrPSD_analyzer = rot_apply(mcrotaPSD_analyzer, mctc1);
  mcDEBUG_COMPONENT("PSD_analyzer", mcposaPSD_analyzer, mcrotaPSD_analyzer)
  mccomp_posa[26] = mcposaPSD_analyzer;
  mccomp_posr[26] = mcposrPSD_analyzer;
  mcNCounter[26]  = mcPCounter[26] = mcP2Counter[26] = 0;
  mcAbsorbProp[26]= 0;
    /* Component analyzer. */
  /* Setting parameters for component analyzer. */
  SIG_MESSAGE("analyzer (Init:SetPar)");
#line 99 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccanalyzer_reflect, "NULL" ? "NULL" : "", 16384); else mccanalyzer_reflect[0]='\0';
#line 99 "ThALES_resolution_v2.instr"
  if("NULL") strncpy(mccanalyzer_transmit, "NULL" ? "NULL" : "", 16384); else mccanalyzer_transmit[0]='\0';
#line 100 "ThALES_resolution_v2.instr"
  mccanalyzer_zwidth = 0.01;
#line 100 "ThALES_resolution_v2.instr"
  mccanalyzer_yheight = 0.01;
#line 330 "ThALES_resolution_v2.instr"
  mccanalyzer_gap = 0.0005;
#line 330 "ThALES_resolution_v2.instr"
  mccanalyzer_NH = 11;
#line 330 "ThALES_resolution_v2.instr"
  mccanalyzer_NV = 9;
#line 331 "ThALES_resolution_v2.instr"
  mccanalyzer_mosaich = 30;
#line 331 "ThALES_resolution_v2.instr"
  mccanalyzer_mosaicv = 30;
#line 331 "ThALES_resolution_v2.instr"
  mccanalyzer_r0 = 0.7;
#line 101 "ThALES_resolution_v2.instr"
  mccanalyzer_t0 = 1.0;
#line 101 "ThALES_resolution_v2.instr"
  mccanalyzer_Q = 1.8734;
#line 330 "ThALES_resolution_v2.instr"
  mccanalyzer_RV = ana_RMV;
#line 330 "ThALES_resolution_v2.instr"
  mccanalyzer_RH = ana_RMH;
#line 331 "ThALES_resolution_v2.instr"
  mccanalyzer_DM = 3.355;
#line 102 "ThALES_resolution_v2.instr"
  mccanalyzer_mosaic = 0;
#line 329 "ThALES_resolution_v2.instr"
  mccanalyzer_width = 0.17;
#line 329 "ThALES_resolution_v2.instr"
  mccanalyzer_height = 0.13;
#line 102 "ThALES_resolution_v2.instr"
  mccanalyzer_verbose = 0;
#line 102 "ThALES_resolution_v2.instr"
  mccanalyzer_order = 0;
#line 13012 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("analyzer (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 333 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 333 "ThALES_resolution_v2.instr"
    (- A5)*DEG2RAD,
#line 333 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 13022 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Cradle, mcrotaanalyzer);
  rot_transpose(mcrotaPSD_analyzer, mctr1);
  rot_mul(mcrotaanalyzer, mctr1, mcrotranalyzer);
  mctc1 = coords_set(
#line 332 "ThALES_resolution_v2.instr"
    0,
#line 332 "ThALES_resolution_v2.instr"
    0,
#line 332 "ThALES_resolution_v2.instr"
    0);
#line 13033 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Cradle, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaanalyzer = coords_add(mcposaAna_Cradle, mctc2);
  mctc1 = coords_sub(mcposaPSD_analyzer, mcposaanalyzer);
  mcposranalyzer = rot_apply(mcrotaanalyzer, mctc1);
  mcDEBUG_COMPONENT("analyzer", mcposaanalyzer, mcrotaanalyzer)
  mccomp_posa[27] = mcposaanalyzer;
  mccomp_posr[27] = mcposranalyzer;
  mcNCounter[27]  = mcPCounter[27] = mcP2Counter[27] = 0;
  mcAbsorbProp[27]= 0;
    /* Component Ana_Out. */
  /* Setting parameters for component Ana_Out. */
  SIG_MESSAGE("Ana_Out (Init:SetPar)");

  SIG_MESSAGE("Ana_Out (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
#line 337 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD,
#line 337 "ThALES_resolution_v2.instr"
    (- A6)*DEG2RAD,
#line 337 "ThALES_resolution_v2.instr"
    (0)*DEG2RAD);
#line 13056 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Cradle, mcrotaAna_Out);
  rot_transpose(mcrotaanalyzer, mctr1);
  rot_mul(mcrotaAna_Out, mctr1, mcrotrAna_Out);
  mctc1 = coords_set(
#line 336 "ThALES_resolution_v2.instr"
    0,
#line 336 "ThALES_resolution_v2.instr"
    0,
#line 336 "ThALES_resolution_v2.instr"
    0);
#line 13067 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Cradle, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaAna_Out = coords_add(mcposaAna_Cradle, mctc2);
  mctc1 = coords_sub(mcposaanalyzer, mcposaAna_Out);
  mcposrAna_Out = rot_apply(mcrotaAna_Out, mctc1);
  mcDEBUG_COMPONENT("Ana_Out", mcposaAna_Out, mcrotaAna_Out)
  mccomp_posa[28] = mcposaAna_Out;
  mccomp_posr[28] = mcposrAna_Out;
  mcNCounter[28]  = mcPCounter[28] = mcP2Counter[28] = 0;
  mcAbsorbProp[28]= 0;
    /* Component slit. */
  /* Setting parameters for component slit. */
  SIG_MESSAGE("slit (Init:SetPar)");
#line 46 "ThALES_resolution_v2.instr"
  mccslit_xmin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccslit_xmax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccslit_ymin = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccslit_ymax = 0;
#line 46 "ThALES_resolution_v2.instr"
  mccslit_radius = 0;
#line 340 "ThALES_resolution_v2.instr"
  mccslit_xwidth = 0.03;
#line 341 "ThALES_resolution_v2.instr"
  mccslit_yheight = 0.08;
#line 13095 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("slit (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 13102 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Out, mcrotaslit);
  rot_transpose(mcrotaAna_Out, mctr1);
  rot_mul(mcrotaslit, mctr1, mcrotrslit);
  mctc1 = coords_set(
#line 342 "ThALES_resolution_v2.instr"
    0,
#line 342 "ThALES_resolution_v2.instr"
    0,
#line 342 "ThALES_resolution_v2.instr"
    0.340);
#line 13113 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaslit = coords_add(mcposaAna_Out, mctc2);
  mctc1 = coords_sub(mcposaAna_Out, mcposaslit);
  mcposrslit = rot_apply(mcrotaslit, mctc1);
  mcDEBUG_COMPONENT("slit", mcposaslit, mcrotaslit)
  mccomp_posa[29] = mcposaslit;
  mccomp_posr[29] = mcposrslit;
  mcNCounter[29]  = mcPCounter[29] = mcP2Counter[29] = 0;
  mcAbsorbProp[29]= 0;
    /* Component PSD_det. */
  /* Setting parameters for component PSD_det. */
  SIG_MESSAGE("PSD_det (Init:SetPar)");
#line 348 "ThALES_resolution_v2.instr"
  mccPSD_det_nx = 200;
#line 348 "ThALES_resolution_v2.instr"
  mccPSD_det_ny = 200;
#line 349 "ThALES_resolution_v2.instr"
  if("PSD_det.dat") strncpy(mccPSD_det_filename, "PSD_det.dat" ? "PSD_det.dat" : "", 16384); else mccPSD_det_filename[0]='\0';
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_det_xmin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_det_xmax = 0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_det_ymin = -0.05;
#line 51 "ThALES_resolution_v2.instr"
  mccPSD_det_ymax = 0.05;
#line 349 "ThALES_resolution_v2.instr"
  mccPSD_det_xwidth = 0.2;
#line 349 "ThALES_resolution_v2.instr"
  mccPSD_det_yheight = 0.2;
#line 348 "ThALES_resolution_v2.instr"
  mccPSD_det_restore_neutron = 1;
#line 52 "ThALES_resolution_v2.instr"
  mccPSD_det_nowritefile = 0;
#line 13149 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("PSD_det (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 13156 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Out, mcrotaPSD_det);
  rot_transpose(mcrotaslit, mctr1);
  rot_mul(mcrotaPSD_det, mctr1, mcrotrPSD_det);
  mctc1 = coords_set(
#line 350 "ThALES_resolution_v2.instr"
    0,
#line 350 "ThALES_resolution_v2.instr"
    0,
#line 350 "ThALES_resolution_v2.instr"
    dist_ana_det -0.0001);
#line 13167 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposaPSD_det = coords_add(mcposaAna_Out, mctc2);
  mctc1 = coords_sub(mcposaslit, mcposaPSD_det);
  mcposrPSD_det = rot_apply(mcrotaPSD_det, mctc1);
  mcDEBUG_COMPONENT("PSD_det", mcposaPSD_det, mcrotaPSD_det)
  mccomp_posa[30] = mcposaPSD_det;
  mccomp_posr[30] = mcposrPSD_det;
  mcNCounter[30]  = mcPCounter[30] = mcP2Counter[30] = 0;
  mcAbsorbProp[30]= 0;
    /* Component res_monitor. */
  /* Setting parameters for component res_monitor. */
  SIG_MESSAGE("res_monitor (Init:SetPar)");
#line 354 "ThALES_resolution_v2.instr"
  if("res_monitor") strncpy(mccres_monitor_filename, "res_monitor" ? "res_monitor" : "", 16384); else mccres_monitor_filename[0]='\0';
#line 69 "ThALES_resolution_v2.instr"
  if(0) strncpy(mccres_monitor_options, 0 ? 0 : "", 16384); else mccres_monitor_options[0]='\0';
#line 355 "ThALES_resolution_v2.instr"
  mccres_monitor_xwidth = 0.05;
#line 356 "ThALES_resolution_v2.instr"
  mccres_monitor_yheight = 0.12;
#line 69 "ThALES_resolution_v2.instr"
  mccres_monitor_zdepth = 0;
#line 69 "ThALES_resolution_v2.instr"
  mccres_monitor_radius = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_xmin = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_xmax = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_ymin = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_ymax = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_zmin = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_zmax = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_bufsize = 0;
#line 70 "ThALES_resolution_v2.instr"
  mccres_monitor_restore_neutron = 0;
#line 13209 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("res_monitor (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 13216 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Out, mcrotares_monitor);
  rot_transpose(mcrotaPSD_det, mctr1);
  rot_mul(mcrotares_monitor, mctr1, mcrotrres_monitor);
  mctc1 = coords_set(
#line 357 "ThALES_resolution_v2.instr"
    0,
#line 357 "ThALES_resolution_v2.instr"
    0,
#line 357 "ThALES_resolution_v2.instr"
    dist_ana_det);
#line 13227 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposares_monitor = coords_add(mcposaAna_Out, mctc2);
  mctc1 = coords_sub(mcposaPSD_det, mcposares_monitor);
  mcposrres_monitor = rot_apply(mcrotares_monitor, mctc1);
  mcDEBUG_COMPONENT("res_monitor", mcposares_monitor, mcrotares_monitor)
  mccomp_posa[31] = mcposares_monitor;
  mccomp_posr[31] = mcposrres_monitor;
  mcNCounter[31]  = mcPCounter[31] = mcP2Counter[31] = 0;
  mcAbsorbProp[31]= 0;
    /* Component detector_all. */
  /* Setting parameters for component detector_all. */
  SIG_MESSAGE("detector_all (Init:SetPar)");
#line 45 "ThALES_resolution_v2.instr"
  mccdetector_all_xmin = -0.05;
#line 45 "ThALES_resolution_v2.instr"
  mccdetector_all_xmax = 0.05;
#line 45 "ThALES_resolution_v2.instr"
  mccdetector_all_ymin = -0.05;
#line 45 "ThALES_resolution_v2.instr"
  mccdetector_all_ymax = 0.05;
#line 360 "ThALES_resolution_v2.instr"
  mccdetector_all_xwidth = 0.05;
#line 361 "ThALES_resolution_v2.instr"
  mccdetector_all_yheight = 0.12;
#line 46 "ThALES_resolution_v2.instr"
  mccdetector_all_restore_neutron = 0;
#line 13255 "./ThALES_resolution_v2.c"

  SIG_MESSAGE("detector_all (Init:Place/Rotate)");
  rot_set_rotation(mctr1,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD,
    (0.0)*DEG2RAD);
#line 13262 "./ThALES_resolution_v2.c"
  rot_mul(mctr1, mcrotaAna_Out, mcrotadetector_all);
  rot_transpose(mcrotares_monitor, mctr1);
  rot_mul(mcrotadetector_all, mctr1, mcrotrdetector_all);
  mctc1 = coords_set(
#line 362 "ThALES_resolution_v2.instr"
    0,
#line 362 "ThALES_resolution_v2.instr"
    0,
#line 362 "ThALES_resolution_v2.instr"
    dist_ana_det + 0.001);
#line 13273 "./ThALES_resolution_v2.c"
  rot_transpose(mcrotaAna_Out, mctr1);
  mctc2 = rot_apply(mctr1, mctc1);
  mcposadetector_all = coords_add(mcposaAna_Out, mctc2);
  mctc1 = coords_sub(mcposares_monitor, mcposadetector_all);
  mcposrdetector_all = rot_apply(mcrotadetector_all, mctc1);
  mcDEBUG_COMPONENT("detector_all", mcposadetector_all, mcrotadetector_all)
  mccomp_posa[32] = mcposadetector_all;
  mccomp_posr[32] = mcposrdetector_all;
  mcNCounter[32]  = mcPCounter[32] = mcP2Counter[32] = 0;
  mcAbsorbProp[32]= 0;
  /* Component initializations. */
  /* Initializations for component Origin. */
  SIG_MESSAGE("Origin (Init)");
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
#define profile mccOrigin_profile
#define percent mccOrigin_percent
#define flag_save mccOrigin_flag_save
#define minutes mccOrigin_minutes
#line 57 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
{
IntermediateCnts=0;
StartTime=0;
EndTime=0;
CurrentTime=0;

fprintf(stdout, "[%s] Initialize\n", mcinstrument_name);
  if (percent*mcget_ncount()/100 < 1e5) {
    percent=1e5*100.0/mcget_ncount();
  }
}
#line 13310 "./ThALES_resolution_v2.c"
#undef minutes
#undef flag_save
#undef percent
#undef profile
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component HCS. */
  SIG_MESSAGE("HCS (Init)");
#define mccompcurname  HCS
#define mccompcurtype  Source_gen
#define mccompcurindex 2
#define p_in mccHCS_p_in
#define lambda1 mccHCS_lambda1
#define lambda2 mccHCS_lambda2
#define lambda3 mccHCS_lambda3
#define pTable mccHCS_pTable
#define pTable_x mccHCS_pTable_x
#define pTable_y mccHCS_pTable_y
#define pTable_xmin mccHCS_pTable_xmin
#define pTable_xmax mccHCS_pTable_xmax
#define pTable_xsum mccHCS_pTable_xsum
#define pTable_ymin mccHCS_pTable_ymin
#define pTable_ymax mccHCS_pTable_ymax
#define pTable_ysum mccHCS_pTable_ysum
#define pTable_dxmin mccHCS_pTable_dxmin
#define pTable_dxmax mccHCS_pTable_dxmax
#define pTable_dymin mccHCS_pTable_dymin
#define pTable_dymax mccHCS_pTable_dymax
#define flux_file mccHCS_flux_file
#define xdiv_file mccHCS_xdiv_file
#define ydiv_file mccHCS_ydiv_file
#define radius mccHCS_radius
#define dist mccHCS_dist
#define focus_xw mccHCS_focus_xw
#define focus_yh mccHCS_focus_yh
#define focus_aw mccHCS_focus_aw
#define focus_ah mccHCS_focus_ah
#define E0 mccHCS_E0
#define dE mccHCS_dE
#define lambda0 mccHCS_lambda0
#define dlambda mccHCS_dlambda
#define I1 mccHCS_I1
#define yheight mccHCS_yheight
#define xwidth mccHCS_xwidth
#define verbose mccHCS_verbose
#define T1 mccHCS_T1
#define flux_file_perAA mccHCS_flux_file_perAA
#define flux_file_log mccHCS_flux_file_log
#define Lmin mccHCS_Lmin
#define Lmax mccHCS_Lmax
#define Emin mccHCS_Emin
#define Emax mccHCS_Emax
#define T2 mccHCS_T2
#define I2 mccHCS_I2
#define T3 mccHCS_T3
#define I3 mccHCS_I3
#define zdepth mccHCS_zdepth
#define target_index mccHCS_target_index
#line 206 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"
{
  pTable_xsum=0;
  pTable_ysum=0;


  double source_area, k;

  if (target_index && !dist)
  {
    Coords ToTarget;
    double tx,ty,tz;
    ToTarget = coords_sub(POS_A_COMP_INDEX(INDEX_CURRENT_COMP+target_index),POS_A_CURRENT_COMP);
    ToTarget = rot_apply(ROT_A_CURRENT_COMP, ToTarget);
    coords_get(ToTarget, &tx, &ty, &tz);
    dist=sqrt(tx*tx+ty*ty+tz*tz);
  }

  /* spectrum characteristics */
  if (flux_file && strlen(flux_file) && strcmp(flux_file,"NULL") && strcmp(flux_file,"0")) {
    if (Table_Read(&pTable, flux_file, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr, "Source_gen: %s: can not read flux file %s\n", NAME_CURRENT_COMP, flux_file));
    /* put table in Log scale */
    int i;
    if (pTable.columns < 2) exit(fprintf(stderr, "Source_gen: %s: Flux file %s should contain at least 2 columns [wavelength in Angs,flux].\n", NAME_CURRENT_COMP, flux_file));
    double table_lmin=FLT_MAX, table_lmax=-FLT_MAX;
    double tmin=FLT_MAX, tmax=-FLT_MAX;
    for (i=0; i<pTable.rows; i++) {
      double val = Table_Index(pTable, i,1);
      val = Table_Index(pTable, i,0); /* lambda */
      if (val > tmax) tmax=val;
      if (val < tmin) tmin=val;
    }
    for (i=0; i<pTable.rows; i++) {
      double val = Table_Index(pTable, i,1);
      if (val < 0) fprintf(stderr, "Source_gen: %s: File %s has negative flux at row %i.\n", NAME_CURRENT_COMP, flux_file, i+1);
      if (flux_file_log)
        val = log(val > 0 ? val : tmin/10);
      Table_SetElement(&pTable, i, 1, val);
      val = Table_Index(pTable, i,0); /* lambda */
      if (val > table_lmax) table_lmax=val;
      if (val < table_lmin) table_lmin=val;
    }
    if (!Lmin && !Lmax && !lambda0 && !dlambda && !E0 && !dE && !Emin && !Emax) {
      Lmin = table_lmin; Lmax = table_lmax;
    }
    if (Lmax > table_lmax) {
      if (verbose) fprintf(stderr, "Source_gen: %s: Maximum wavelength %g is beyond table range upper limit %g. Constraining.\n", NAME_CURRENT_COMP, Lmax, table_lmax);
      Lmax = table_lmax;
    }
    if (Lmin < table_lmin) {
      if (verbose) fprintf(stderr, "Source_gen: %s: Minimum wavelength %g is below table range lower limit %g. Constraining.\n", NAME_CURRENT_COMP, Lmin, table_lmin);
      Lmin = table_lmin;
    }
  }  /* end flux file */
  else
  {
    k  = 1.38066e-23; /* k_B */
    if (T1 > 0)
    {
      lambda1  = 1.0e10*sqrt(HBAR*HBAR*4.0*PI*PI/2.0/MNEUTRON/k/T1);
    }
    else
      { lambda1 = lambda0; }

    if (T2 > 0)
    {
      lambda2  = 1.0e10*sqrt(HBAR*HBAR*4.0*PI*PI/2.0/MNEUTRON/k/T2);
    }
    else
      { lambda2 = lambda0; }

    if (T3 > 0)
    {
      lambda3  = 1.0e10*sqrt(HBAR*HBAR*4.0*PI*PI/2.0/MNEUTRON/k/T3);
    }
    else
      { lambda3 = lambda0; }
  }

  /* now read position-divergence files, if any */
  if (xdiv_file && strlen(xdiv_file) && strcmp(xdiv_file,"NULL") && strcmp(xdiv_file,"0")) {
    int i,j;
    if (Table_Read(&pTable_x, xdiv_file, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr, "Source_gen: %s: can not read XDiv file %s\n", NAME_CURRENT_COMP, xdiv_file));
    pTable_xsum = 0;
    for (i=0; i<pTable_x.rows; i++)
      for (j=0; j<pTable_x.columns; j++)
        pTable_xsum += Table_Index(pTable_x, i,j);

    /* now extract limits */
    char **parsing;
    char xylimits[1024];
    strcpy(xylimits, "");
    parsing = Table_ParseHeader(pTable_x.header,
      "xlimits", "xylimits",
      NULL);

    if (parsing) {
      if (parsing[0])  strcpy(xylimits, str_dup_numeric(parsing[0]));
      if (parsing[1] && !strlen(xylimits))
                       strcpy(xylimits, str_dup_numeric(parsing[1]));
      for (i=0; i<=1; i++) {
        if (parsing[i]) free(parsing[i]);
      }
      free(parsing);
    }
    i = sscanf(xylimits, "%lg %lg %lg %lg",
      &(pTable_xmin),  &(pTable_xmax),
      &(pTable_dxmin), &(pTable_dxmax));
    if (i != 2 && i != 4 && verbose)
      fprintf(stderr, "Source_gen: %s: invalid xylimits '%s' from file %s. extracted %i values\n",
        NAME_CURRENT_COMP, xylimits, xdiv_file, i);

    if (!xwidth) xwidth=pTable_xmax-pTable_xmin;
    if (!focus_xw && !dist) focus_xw=fabs(pTable_dxmax-pTable_dxmin);
  } /* end xdiv file */

  if (ydiv_file && strlen(ydiv_file) && strcmp(ydiv_file,"NULL") && strcmp(ydiv_file,"0")) {
    int i,j;
    if (Table_Read(&pTable_y, ydiv_file, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr, "Source_gen: %s: can not read YDiv file %s\n", NAME_CURRENT_COMP, ydiv_file));
    pTable_ysum = 0;
    for (i=0; i<pTable_y.rows; i++)
      for (j=0; j<pTable_y.columns; j++)
        pTable_ysum += Table_Index(pTable_y, i,j);

    /* now extract limits */
    char **parsing;
    char xylimits[1024];
    strcpy(xylimits, "");
    parsing = Table_ParseHeader(pTable_y.header,
      "xlimits", "xylimits",
      NULL);

    if (parsing) {
      if (parsing[0])  strcpy(xylimits,str_dup_numeric(parsing[0]));
      if (parsing[1] && !strlen(xylimits))
                       strcpy(xylimits,str_dup_numeric(parsing[1]));
      for (i=0; i<=1; i++) {
        if (parsing[i]) free(parsing[i]);
      }
      free(parsing);
    }
    i = sscanf(xylimits, "%lg %lg %lg %lg",
      &(pTable_ymin),  &(pTable_ymax),
      &(pTable_dymin), &(pTable_dymax));
    if (i != 2 && i != 4 && verbose)
      fprintf(stderr, "Source_gen: %s: invalid xylimits '%s' from file %s. extracted %i values\n",
        NAME_CURRENT_COMP, xylimits, ydiv_file, i);
    if (!yheight)  yheight=pTable_ymax-pTable_ymin;
    if (!focus_yh && !dist) focus_yh=fabs(pTable_dymax-pTable_dymin);
  } /* end ydiv file */

  /* tests for parameter values */
  if (Emin < 0 || Emax < 0 || Lmin < 0 || Lmax < 0 || E0 < 0 || dE < 0 || lambda0 < 0 || dlambda < 0)
  {
    fprintf(stderr,"Source_gen: %s: Error: Negative average\n"
                   "            or range values for wavelength or energy encountered\n",
                   NAME_CURRENT_COMP);
    exit(-1);
  }
  if ((Emin == 0 && Emax > 0) || (dE > 0 && dE >= E0))
  {
    fprintf(stderr,"Source_gen: %s: Error: minimal energy cannot be less or equal zero\n",
      NAME_CURRENT_COMP);
    exit(-1);
  }
  if ((Emax >= Emin) && (Emin > 0))
  { E0 = (Emax+Emin)/2;
    dE = (Emax-Emin)/2;
  }
  if ((E0 > dE) && (dE >= 0))
  {
    Lmin = sqrt(81.81/(E0+dE)); /* Angstroem */
    Lmax = sqrt(81.81/(E0-dE));
  }
  if (Lmax > 0)
  { lambda0 = (Lmax+Lmin)/2;
    dlambda = (Lmax-Lmin)/2;
  }
  if (lambda0 <= 0 || (lambda0 < dlambda) || (dlambda < 0))
  { fprintf(stderr,"Source_gen: %s: Error: Wavelength range %.3f +/- %.3f AA calculated \n",
      NAME_CURRENT_COMP, lambda0, dlambda);
    fprintf(stderr,"- whole wavelength range must be >= 0 \n");
    fprintf(stderr,"- range must be > 0; otherwise intensity gets zero, use other sources in this case \n\n");
    exit(-1);
  }

  radius = fabs(radius); xwidth=fabs(xwidth); yheight=fabs(yheight);  I1=fabs(I1);
  lambda0=fabs(lambda0); dlambda=fabs(dlambda);
  focus_xw = fabs(focus_xw); focus_yh=fabs(focus_yh); dist=fabs(dist);

  if ((!focus_ah && !focus_aw) && (!focus_xw && !focus_yh))
  {
    fprintf(stderr,"Source_gen: %s: Error: No focusing information.\n"
                   "            Specify focus_xw, focus_yh or focus_aw, focus_ah\n",
                   NAME_CURRENT_COMP);
    exit(-1);
  }
  Lmin = lambda0 - dlambda; /* Angstroem */
  Lmax = lambda0 + dlambda;

  /* compute initial weight factor p_in to get [n/s] */
  if ((I1 > 0  && T1 >= 0)
     || (flux_file && strlen(flux_file) && strcmp(flux_file,"NULL") && strcmp(flux_file,"0")))
  { /* the I1,2,3 are usually in [n/s/cm2/st/AA] */
    if (radius)
      source_area = radius*radius*PI*1e4; /* circular cm^2 */
    else
      source_area = yheight*xwidth*1e4; /* square cm^2 */
    p_in  = source_area; /* cm2 */
    p_in *= (Lmax-Lmin); /* AA. 1 bin=AA/n */
    if (flux_file && strlen(flux_file) && strcmp(flux_file,"NULL") && strcmp(flux_file,"0")
      && !flux_file_perAA)  p_in *= pTable.rows/(Lmax-Lmin);
  }
  else
    p_in = 1.0/4/PI; /* Small angle approx. */
  p_in /= mcget_ncount();
  if (!T1 && I1) p_in *= I1;

  if (radius == 0 && yheight == 0 && xwidth == 0)
  {
    fprintf(stderr,"Source_gen: %s: Error: Please specify source geometry (radius, yheight, xwidth)\n",
      NAME_CURRENT_COMP);
    exit(-1);
  }
  if (focus_xw*focus_yh == 0)
  {
    fprintf(stderr,"Source_gen: %s: Error: Please specify source target (focus_xw, focus_yh)\n",
      NAME_CURRENT_COMP);
    exit(-1);
  }
  MPI_MASTER(
  if (verbose)
  {
    printf("Source_gen: component %s ", NAME_CURRENT_COMP);
    if ((yheight == 0) || (xwidth == 0))
      printf("(disk, radius=%g)", radius);
    else
      printf("(square %g x %g)",xwidth,yheight);
    if (dist) printf("\n            focusing distance dist=%g area=%g x %g\n", dist, focus_xw, focus_yh);
    printf("            spectra ");
    printf("%.3f to %.3f AA (%.3f to %.3f meV)", Lmin, Lmax, 81.81/Lmax/Lmax, 81.81/Lmin/Lmin);
    printf("\n");
    if (flux_file && strlen(flux_file) && strcmp(flux_file,"NULL") && strcmp(flux_file,"0"))
    { printf("  File %s for flux distribution used. Flux is dPhi/dlambda in [n/s/AA]. \n", flux_file);
      Table_Info(pTable);
    }
    else if (T1>=0 && I1)
    { if (T1 != 0)
        printf("            T1=%.1f K (%.3f AA)", T1, lambda1);
      if (T2*I2 != 0)
        printf(", T2=%.1f K (%.3f AA)", T2, lambda2);
      if (T3*I3 != 0)
        printf(", T3=%.1f K (%.3f AA)", T3, lambda3);
      if (T1) printf("\n");
      printf("  Flux is dPhi/dlambda in [n/s/cm2].\n");
    }
    else
    { printf("  Flux is Phi in [n/s].\n");
    }
    if (xdiv_file && strlen(xdiv_file) && strcmp(xdiv_file,"NULL") && strcmp(xdiv_file,"0"))
      printf("  File %s x=[%g:%g] [m] xdiv=[%g:%g] [deg] used as horizontal phase space distribution.\n", xdiv_file, pTable_xmin, pTable_xmax, pTable_dxmin, pTable_dxmax);
    if (ydiv_file && strlen(ydiv_file) && strcmp(ydiv_file,"NULL") && strcmp(ydiv_file,"0"))
      printf("  File %s y=[%g:%g] [m] ydiv=[%g:%g] [deg] used as vertical phase space distribution.\n", ydiv_file, pTable_ymin, pTable_ymax, pTable_dymin, pTable_dymax);
  }
  else
    if (verbose == -1)
      printf("Source_gen: component %s unactivated", NAME_CURRENT_COMP);
  );
}
#line 13647 "./ThALES_resolution_v2.c"
#undef target_index
#undef zdepth
#undef I3
#undef T3
#undef I2
#undef T2
#undef Emax
#undef Emin
#undef Lmax
#undef Lmin
#undef flux_file_log
#undef flux_file_perAA
#undef T1
#undef verbose
#undef xwidth
#undef yheight
#undef I1
#undef dlambda
#undef lambda0
#undef dE
#undef E0
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef dist
#undef radius
#undef ydiv_file
#undef xdiv_file
#undef flux_file
#undef pTable_dymax
#undef pTable_dymin
#undef pTable_dxmax
#undef pTable_dxmin
#undef pTable_ysum
#undef pTable_ymax
#undef pTable_ymin
#undef pTable_xsum
#undef pTable_xmax
#undef pTable_xmin
#undef pTable_y
#undef pTable_x
#undef pTable
#undef lambda3
#undef lambda2
#undef lambda1
#undef p_in
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H5. */
  SIG_MESSAGE("H5 (Init)");

  /* Initializations for component H5_rect. */
  SIG_MESSAGE("H5_rect (Init)");
#define mccompcurname  H5_rect
#define mccompcurtype  Guide_gravity
#define mccompcurindex 4
#define GVars mccH5_rect_GVars
#define pTable mccH5_rect_pTable
#define w1 mccH5_rect_w1
#define h1 mccH5_rect_h1
#define w2 mccH5_rect_w2
#define h2 mccH5_rect_h2
#define l mccH5_rect_l
#define R0 mccH5_rect_R0
#define Qc mccH5_rect_Qc
#define alpha mccH5_rect_alpha
#define m mccH5_rect_m
#define W mccH5_rect_W
#define nslit mccH5_rect_nslit
#define d mccH5_rect_d
#define mleft mccH5_rect_mleft
#define mright mccH5_rect_mright
#define mtop mccH5_rect_mtop
#define mbottom mccH5_rect_mbottom
#define nhslit mccH5_rect_nhslit
#define G mccH5_rect_G
#define aleft mccH5_rect_aleft
#define aright mccH5_rect_aright
#define atop mccH5_rect_atop
#define abottom mccH5_rect_abottom
#define wavy mccH5_rect_wavy
#define wavy_z mccH5_rect_wavy_z
#define wavy_tb mccH5_rect_wavy_tb
#define wavy_lr mccH5_rect_wavy_lr
#define chamfers mccH5_rect_chamfers
#define chamfers_z mccH5_rect_chamfers_z
#define chamfers_lr mccH5_rect_chamfers_lr
#define chamfers_tb mccH5_rect_chamfers_tb
#define nelements mccH5_rect_nelements
#define nu mccH5_rect_nu
#define phase mccH5_rect_phase
#define reflect mccH5_rect_reflect
#line 339 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  double Gx=0, Gy=-GRAVITY, Gz=0;
  Coords mcLocG;
  int i;

  if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0")) {
    if (Table_Read(&pTable, reflect, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr,"Guide_gravity: %s: can not read file %s\n", NAME_CURRENT_COMP, reflect));
  } else {
    if (W < 0 || R0 < 0 || Qc < 0)
    { fprintf(stderr,"Guide_gravity: %s: W R0 Qc must be >0.\n", NAME_CURRENT_COMP);
      exit(-1); }
  }

  if (nslit <= 0 || nhslit <= 0)
  { fprintf(stderr,"Guide_gravity: %s: nslit nhslit must be >0.\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (!w1 || !h1)
  { fprintf(stderr,"Guide_gravity: %s: input window is closed (w1=h1=0).\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (d*nslit > w1) exit(fprintf(stderr, "Guide_gravity: %s: absorbing walls fill input window. No space left for transmission (d*nslit > w1).\n", NAME_CURRENT_COMP));

  if (!w2) w2=w1;
  if (!h2) h2=h1;

  if (mcgravitation) G=-GRAVITY;
  mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,G,0));
  coords_get(mcLocG, &Gx, &Gy, &Gz);

  strcpy(GVars.compcurname, NAME_CURRENT_COMP);

  if (l > 0 && nelements > 0) {

    Gravity_guide_Init(&GVars,
      w1, h1, w2, h2, l, R0,
      Qc, alpha, m, W, nslit, d,
      Gx, Gy, Gz, mleft, mright, mtop,
      mbottom, nhslit, wavy_lr, wavy_tb, wavy_z, wavy,
      chamfers_z, chamfers_lr, chamfers_tb, chamfers,nu,phase,aleft,aright,atop,abottom);
    if (!G) for (i=0; i<5; GVars.A[i++] = 0);
    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) {
      if (w1 != w2 || h1 != h2)
      exit(fprintf(stderr,"Guide_gravity: %s: rotating slit pack must be straight (w1=w2 and h1=h2).\n", NAME_CURRENT_COMP));
      printf("Guide_gravity: %s: Fermi Chopper mode: frequency=%g [Hz] phase=%g [deg]\n",
        NAME_CURRENT_COMP, GVars.fc_freq, GVars.fc_phase);
    }
  } else printf("Guide_gravity: %s: unactivated (l=0 or nelements=0)\n", NAME_CURRENT_COMP);

}
#line 13795 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_origin. */
  SIG_MESSAGE("H53_origin (Init)");

  /* Initializations for component H53_start. */
  SIG_MESSAGE("H53_start (Init)");

  /* Initializations for component H53_inpile. */
  SIG_MESSAGE("H53_inpile (Init)");
#define mccompcurname  H53_inpile
#define mccompcurtype  Guide_gravity
#define mccompcurindex 7
#define GVars mccH53_inpile_GVars
#define pTable mccH53_inpile_pTable
#define w1 mccH53_inpile_w1
#define h1 mccH53_inpile_h1
#define w2 mccH53_inpile_w2
#define h2 mccH53_inpile_h2
#define l mccH53_inpile_l
#define R0 mccH53_inpile_R0
#define Qc mccH53_inpile_Qc
#define alpha mccH53_inpile_alpha
#define m mccH53_inpile_m
#define W mccH53_inpile_W
#define nslit mccH53_inpile_nslit
#define d mccH53_inpile_d
#define mleft mccH53_inpile_mleft
#define mright mccH53_inpile_mright
#define mtop mccH53_inpile_mtop
#define mbottom mccH53_inpile_mbottom
#define nhslit mccH53_inpile_nhslit
#define G mccH53_inpile_G
#define aleft mccH53_inpile_aleft
#define aright mccH53_inpile_aright
#define atop mccH53_inpile_atop
#define abottom mccH53_inpile_abottom
#define wavy mccH53_inpile_wavy
#define wavy_z mccH53_inpile_wavy_z
#define wavy_tb mccH53_inpile_wavy_tb
#define wavy_lr mccH53_inpile_wavy_lr
#define chamfers mccH53_inpile_chamfers
#define chamfers_z mccH53_inpile_chamfers_z
#define chamfers_lr mccH53_inpile_chamfers_lr
#define chamfers_tb mccH53_inpile_chamfers_tb
#define nelements mccH53_inpile_nelements
#define nu mccH53_inpile_nu
#define phase mccH53_inpile_phase
#define reflect mccH53_inpile_reflect
#line 339 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  double Gx=0, Gy=-GRAVITY, Gz=0;
  Coords mcLocG;
  int i;

  if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0")) {
    if (Table_Read(&pTable, reflect, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr,"Guide_gravity: %s: can not read file %s\n", NAME_CURRENT_COMP, reflect));
  } else {
    if (W < 0 || R0 < 0 || Qc < 0)
    { fprintf(stderr,"Guide_gravity: %s: W R0 Qc must be >0.\n", NAME_CURRENT_COMP);
      exit(-1); }
  }

  if (nslit <= 0 || nhslit <= 0)
  { fprintf(stderr,"Guide_gravity: %s: nslit nhslit must be >0.\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (!w1 || !h1)
  { fprintf(stderr,"Guide_gravity: %s: input window is closed (w1=h1=0).\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (d*nslit > w1) exit(fprintf(stderr, "Guide_gravity: %s: absorbing walls fill input window. No space left for transmission (d*nslit > w1).\n", NAME_CURRENT_COMP));

  if (!w2) w2=w1;
  if (!h2) h2=h1;

  if (mcgravitation) G=-GRAVITY;
  mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,G,0));
  coords_get(mcLocG, &Gx, &Gy, &Gz);

  strcpy(GVars.compcurname, NAME_CURRENT_COMP);

  if (l > 0 && nelements > 0) {

    Gravity_guide_Init(&GVars,
      w1, h1, w2, h2, l, R0,
      Qc, alpha, m, W, nslit, d,
      Gx, Gy, Gz, mleft, mright, mtop,
      mbottom, nhslit, wavy_lr, wavy_tb, wavy_z, wavy,
      chamfers_z, chamfers_lr, chamfers_tb, chamfers,nu,phase,aleft,aright,atop,abottom);
    if (!G) for (i=0; i<5; GVars.A[i++] = 0);
    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) {
      if (w1 != w2 || h1 != h2)
      exit(fprintf(stderr,"Guide_gravity: %s: rotating slit pack must be straight (w1=w2 and h1=h2).\n", NAME_CURRENT_COMP));
      printf("Guide_gravity: %s: Fermi Chopper mode: frequency=%g [Hz] phase=%g [deg]\n",
        NAME_CURRENT_COMP, GVars.fc_freq, GVars.fc_phase);
    }
  } else printf("Guide_gravity: %s: unactivated (l=0 or nelements=0)\n", NAME_CURRENT_COMP);

}
#line 13935 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_Obt. */
  SIG_MESSAGE("H53_Obt (Init)");
#define mccompcurname  H53_Obt
#define mccompcurtype  Guide_gravity
#define mccompcurindex 8
#define GVars mccH53_Obt_GVars
#define pTable mccH53_Obt_pTable
#define w1 mccH53_Obt_w1
#define h1 mccH53_Obt_h1
#define w2 mccH53_Obt_w2
#define h2 mccH53_Obt_h2
#define l mccH53_Obt_l
#define R0 mccH53_Obt_R0
#define Qc mccH53_Obt_Qc
#define alpha mccH53_Obt_alpha
#define m mccH53_Obt_m
#define W mccH53_Obt_W
#define nslit mccH53_Obt_nslit
#define d mccH53_Obt_d
#define mleft mccH53_Obt_mleft
#define mright mccH53_Obt_mright
#define mtop mccH53_Obt_mtop
#define mbottom mccH53_Obt_mbottom
#define nhslit mccH53_Obt_nhslit
#define G mccH53_Obt_G
#define aleft mccH53_Obt_aleft
#define aright mccH53_Obt_aright
#define atop mccH53_Obt_atop
#define abottom mccH53_Obt_abottom
#define wavy mccH53_Obt_wavy
#define wavy_z mccH53_Obt_wavy_z
#define wavy_tb mccH53_Obt_wavy_tb
#define wavy_lr mccH53_Obt_wavy_lr
#define chamfers mccH53_Obt_chamfers
#define chamfers_z mccH53_Obt_chamfers_z
#define chamfers_lr mccH53_Obt_chamfers_lr
#define chamfers_tb mccH53_Obt_chamfers_tb
#define nelements mccH53_Obt_nelements
#define nu mccH53_Obt_nu
#define phase mccH53_Obt_phase
#define reflect mccH53_Obt_reflect
#line 339 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  double Gx=0, Gy=-GRAVITY, Gz=0;
  Coords mcLocG;
  int i;

  if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0")) {
    if (Table_Read(&pTable, reflect, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr,"Guide_gravity: %s: can not read file %s\n", NAME_CURRENT_COMP, reflect));
  } else {
    if (W < 0 || R0 < 0 || Qc < 0)
    { fprintf(stderr,"Guide_gravity: %s: W R0 Qc must be >0.\n", NAME_CURRENT_COMP);
      exit(-1); }
  }

  if (nslit <= 0 || nhslit <= 0)
  { fprintf(stderr,"Guide_gravity: %s: nslit nhslit must be >0.\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (!w1 || !h1)
  { fprintf(stderr,"Guide_gravity: %s: input window is closed (w1=h1=0).\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (d*nslit > w1) exit(fprintf(stderr, "Guide_gravity: %s: absorbing walls fill input window. No space left for transmission (d*nslit > w1).\n", NAME_CURRENT_COMP));

  if (!w2) w2=w1;
  if (!h2) h2=h1;

  if (mcgravitation) G=-GRAVITY;
  mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,G,0));
  coords_get(mcLocG, &Gx, &Gy, &Gz);

  strcpy(GVars.compcurname, NAME_CURRENT_COMP);

  if (l > 0 && nelements > 0) {

    Gravity_guide_Init(&GVars,
      w1, h1, w2, h2, l, R0,
      Qc, alpha, m, W, nslit, d,
      Gx, Gy, Gz, mleft, mright, mtop,
      mbottom, nhslit, wavy_lr, wavy_tb, wavy_z, wavy,
      chamfers_z, chamfers_lr, chamfers_tb, chamfers,nu,phase,aleft,aright,atop,abottom);
    if (!G) for (i=0; i<5; GVars.A[i++] = 0);
    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) {
      if (w1 != w2 || h1 != h2)
      exit(fprintf(stderr,"Guide_gravity: %s: rotating slit pack must be straight (w1=w2 and h1=h2).\n", NAME_CURRENT_COMP));
      printf("Guide_gravity: %s: Fermi Chopper mode: frequency=%g [Hz] phase=%g [deg]\n",
        NAME_CURRENT_COMP, GVars.fc_freq, GVars.fc_phase);
    }
  } else printf("Guide_gravity: %s: unactivated (l=0 or nelements=0)\n", NAME_CURRENT_COMP);

}
#line 14069 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_Obt_Out. */
  SIG_MESSAGE("H53_Obt_Out (Init)");

  /* Initializations for component H53_VSComC1. */
  SIG_MESSAGE("H53_VSComC1 (Init)");
#define mccompcurname  H53_VSComC1
#define mccompcurtype  Guide_gravity
#define mccompcurindex 10
#define GVars mccH53_VSComC1_GVars
#define pTable mccH53_VSComC1_pTable
#define w1 mccH53_VSComC1_w1
#define h1 mccH53_VSComC1_h1
#define w2 mccH53_VSComC1_w2
#define h2 mccH53_VSComC1_h2
#define l mccH53_VSComC1_l
#define R0 mccH53_VSComC1_R0
#define Qc mccH53_VSComC1_Qc
#define alpha mccH53_VSComC1_alpha
#define m mccH53_VSComC1_m
#define W mccH53_VSComC1_W
#define nslit mccH53_VSComC1_nslit
#define d mccH53_VSComC1_d
#define mleft mccH53_VSComC1_mleft
#define mright mccH53_VSComC1_mright
#define mtop mccH53_VSComC1_mtop
#define mbottom mccH53_VSComC1_mbottom
#define nhslit mccH53_VSComC1_nhslit
#define G mccH53_VSComC1_G
#define aleft mccH53_VSComC1_aleft
#define aright mccH53_VSComC1_aright
#define atop mccH53_VSComC1_atop
#define abottom mccH53_VSComC1_abottom
#define wavy mccH53_VSComC1_wavy
#define wavy_z mccH53_VSComC1_wavy_z
#define wavy_tb mccH53_VSComC1_wavy_tb
#define wavy_lr mccH53_VSComC1_wavy_lr
#define chamfers mccH53_VSComC1_chamfers
#define chamfers_z mccH53_VSComC1_chamfers_z
#define chamfers_lr mccH53_VSComC1_chamfers_lr
#define chamfers_tb mccH53_VSComC1_chamfers_tb
#define nelements mccH53_VSComC1_nelements
#define nu mccH53_VSComC1_nu
#define phase mccH53_VSComC1_phase
#define reflect mccH53_VSComC1_reflect
#line 339 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  double Gx=0, Gy=-GRAVITY, Gz=0;
  Coords mcLocG;
  int i;

  if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0")) {
    if (Table_Read(&pTable, reflect, 1) <= 0) /* read 1st block data from file into pTable */
      exit(fprintf(stderr,"Guide_gravity: %s: can not read file %s\n", NAME_CURRENT_COMP, reflect));
  } else {
    if (W < 0 || R0 < 0 || Qc < 0)
    { fprintf(stderr,"Guide_gravity: %s: W R0 Qc must be >0.\n", NAME_CURRENT_COMP);
      exit(-1); }
  }

  if (nslit <= 0 || nhslit <= 0)
  { fprintf(stderr,"Guide_gravity: %s: nslit nhslit must be >0.\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (!w1 || !h1)
  { fprintf(stderr,"Guide_gravity: %s: input window is closed (w1=h1=0).\n", NAME_CURRENT_COMP);
    exit(-1); }

  if (d*nslit > w1) exit(fprintf(stderr, "Guide_gravity: %s: absorbing walls fill input window. No space left for transmission (d*nslit > w1).\n", NAME_CURRENT_COMP));

  if (!w2) w2=w1;
  if (!h2) h2=h1;

  if (mcgravitation) G=-GRAVITY;
  mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,G,0));
  coords_get(mcLocG, &Gx, &Gy, &Gz);

  strcpy(GVars.compcurname, NAME_CURRENT_COMP);

  if (l > 0 && nelements > 0) {

    Gravity_guide_Init(&GVars,
      w1, h1, w2, h2, l, R0,
      Qc, alpha, m, W, nslit, d,
      Gx, Gy, Gz, mleft, mright, mtop,
      mbottom, nhslit, wavy_lr, wavy_tb, wavy_z, wavy,
      chamfers_z, chamfers_lr, chamfers_tb, chamfers,nu,phase,aleft,aright,atop,abottom);
    if (!G) for (i=0; i<5; GVars.A[i++] = 0);
    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) {
      if (w1 != w2 || h1 != h2)
      exit(fprintf(stderr,"Guide_gravity: %s: rotating slit pack must be straight (w1=w2 and h1=h2).\n", NAME_CURRENT_COMP));
      printf("Guide_gravity: %s: Fermi Chopper mode: frequency=%g [Hz] phase=%g [deg]\n",
        NAME_CURRENT_COMP, GVars.fc_freq, GVars.fc_phase);
    }
  } else printf("Guide_gravity: %s: unactivated (l=0 or nelements=0)\n", NAME_CURRENT_COMP);

}
#line 14206 "./ThALES_resolution_v2.c"
#undef reflect
#undef phase
#undef nu
#undef nelements
#undef chamfers_tb
#undef chamfers_lr
#undef chamfers_z
#undef chamfers
#undef wavy_lr
#undef wavy_tb
#undef wavy_z
#undef wavy
#undef abottom
#undef atop
#undef aright
#undef aleft
#undef G
#undef nhslit
#undef mbottom
#undef mtop
#undef mright
#undef mleft
#undef d
#undef nslit
#undef W
#undef m
#undef alpha
#undef Qc
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_Nose. */
  SIG_MESSAGE("H53_Nose (Init)");
#define mccompcurname  H53_Nose
#define mccompcurtype  Guide_tapering
#define mccompcurindex 11
#define w1c mccH53_Nose_w1c
#define w2c mccH53_Nose_w2c
#define ww mccH53_Nose_ww
#define hh mccH53_Nose_hh
#define whalf mccH53_Nose_whalf
#define hhalf mccH53_Nose_hhalf
#define lwhalf mccH53_Nose_lwhalf
#define lhhalf mccH53_Nose_lhhalf
#define h1_in mccH53_Nose_h1_in
#define h2_out mccH53_Nose_h2_out
#define w1_in mccH53_Nose_w1_in
#define w2_out mccH53_Nose_w2_out
#define l_seg mccH53_Nose_l_seg
#define seg mccH53_Nose_seg
#define h12 mccH53_Nose_h12
#define h2 mccH53_Nose_h2
#define w12 mccH53_Nose_w12
#define w2 mccH53_Nose_w2
#define a_ell_q mccH53_Nose_a_ell_q
#define b_ell_q mccH53_Nose_b_ell_q
#define lbw mccH53_Nose_lbw
#define lbh mccH53_Nose_lbh
#define mxi mccH53_Nose_mxi
#define u1 mccH53_Nose_u1
#define u2 mccH53_Nose_u2
#define div1 mccH53_Nose_div1
#define p2_para mccH53_Nose_p2_para
#define test mccH53_Nose_test
#define Div1 mccH53_Nose_Div1
#define i mccH53_Nose_i
#define ii mccH53_Nose_ii
#define seg mccH53_Nose_seg
#define fu mccH53_Nose_fu
#define pos mccH53_Nose_pos
#define file_name mccH53_Nose_file_name
#define ep mccH53_Nose_ep
#define num mccH53_Nose_num
#define rotation_h mccH53_Nose_rotation_h
#define rotation_v mccH53_Nose_rotation_v
#define option mccH53_Nose_option
#define w1 mccH53_Nose_w1
#define h1 mccH53_Nose_h1
#define l mccH53_Nose_l
#define linw mccH53_Nose_linw
#define loutw mccH53_Nose_loutw
#define linh mccH53_Nose_linh
#define louth mccH53_Nose_louth
#define R0 mccH53_Nose_R0
#define Qcx mccH53_Nose_Qcx
#define Qcy mccH53_Nose_Qcy
#define alphax mccH53_Nose_alphax
#define alphay mccH53_Nose_alphay
#define W mccH53_Nose_W
#define mx mccH53_Nose_mx
#define my mccH53_Nose_my
#define segno mccH53_Nose_segno
#define curvature mccH53_Nose_curvature
#define curvature_v mccH53_Nose_curvature_v
#line 116 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"
{
rotation_h=0;
rotation_v=0;

// dynamic memory allocation is good
w1c = (double*)malloc(sizeof(double)*segno);
  w2c = (double*)malloc(sizeof(double)*segno);
  ww = (double*)malloc(sizeof(double)*segno);
  hh = (double*)malloc(sizeof(double)*segno);
  whalf = (double*)malloc(sizeof(double)*segno);
  hhalf = (double*)malloc(sizeof(double)*segno);
  lwhalf = (double*)malloc(sizeof(double)*segno);
  lhhalf = (double*)malloc(sizeof(double)*segno);
  h1_in = (double*)malloc(sizeof(double)*(segno+1));
  h2_out = (double*)malloc(sizeof(double)*(segno+1));
  w1_in = (double*)malloc(sizeof(double)*(segno+1));
  w2_out = (double*)malloc(sizeof(double)*(segno+1));

  struct para {
    char st[128];
  } segment[800];
  if (W <=0)
  {
    fprintf(stderr,"Component: %s (Guide_tapering) W must \n", NAME_CURRENT_COMP);
    fprintf(stderr,"           be positive\n");
    exit(-1);
  }
  if (l <= 0)
  {
    fprintf(stderr,"Component: %s (Guide_tapering) real guide length \n",
    NAME_CURRENT_COMP);
    fprintf(stderr,"           is <= ZERO ! \n");
    exit(-1);
  }
  if (mcgravitation) fprintf(stderr,"WARNING: Guide_tapering: %s: "
    "This component produces wrong results with gravitation !\n"
    "Use Guide_gravity.\n",
    NAME_CURRENT_COMP);
  seg=segno;
  l_seg=l/(seg);
  h12 = h1/2.0;
  if (option != NULL)
  {
     fu = (char*)malloc(sizeof(char)*(strlen(option)+1));
     strcpy(fu,option);
  } else {
     exit(-1);
  }
  /* handle guide geometry ================================================== */
  if (!strcmp(fu,"elliptical"))
  {
     /* calculate parameter b of elliptical equestion - vertical mirrors */
     /* (l+linh+louth) -> distance between focal points */
     /*  printf("A1 \n"); */
     lbh = l + linh + louth;
     if (linh == 0 && louth == 0 )
     {
        /* plane mirrors (vertical) */
        b_ell_q = 0;
        h2 = h1;
     } else {
        /* elliptical mirrors */
        u1 = sqrt((linh*linh)+(h12*h12));
        u2 = sqrt((h12*h12) + ((l+louth)*(l+louth)));
        a_ell_q = ((u1 + u2)/2.0)*((u1 + u2)/2.0);
        b_ell_q = a_ell_q - ((lbh/2.0)*(lbh/2.0));
        /* calculate heigth of guide exit (h2) */
        div1 = ((lbh/2.0-louth)*(lbh/2.0-louth))/a_ell_q;
        h2 = sqrt(b_ell_q*(1.0-div1));
        h2 = h2*2.0;
     }
  } else if (!strcmp(fu,"parabolical")) {
     if ((linh > 0) && (louth > 0))
     {
       fprintf(stderr,"Component: %s (Guide_tapering) Two focal\n",NAME_CURRENT_COMP);
       fprintf(stderr,"            points lout and linh are not allowed! \n");
        free(fu);exit(-1);
     }
     if (louth == 0 && linh == 0)
     {
        /* plane mirrors (vertical) */
        h2 = h1;
     } else {
        /* parabolical mirrors */
        if (linh == 0)
        {
           Div1=((2.0*louth+2.0*l)*(2.0*louth+2.0*l))/4.0;
           p2_para=((sqrt(Div1+(h12*h12)))-(louth+l))*2.0;
           /* calculate heigth of guide exit (h2) */
           h2 = sqrt(p2_para*(louth+p2_para/4.0));
           h2 = h2*2.0;
         } else {
            /* anti-trompete */
           Div1=((2.0*linh)*(2.0*linh))/4.0;
           p2_para=((sqrt(Div1+(h12*h12)))-linh)*2.0;
           /* calculate heigth of guide exit (h2) */
           h2 = sqrt(p2_para*(l+linh+p2_para/4.0));
           h2 = h2*2.0;
         }
     }
  } else if (!strncmp(fu,"file",4)) {
     pos = strtok(fu,"=");
     while (pos=strtok(0,"="))
     {
        strcpy(file_name,pos);
     }
     if ((num=fopen(file_name,"r")) == NULL)
     {
        fprintf(stderr,"Component: %s (Guide_tapering)\n",NAME_CURRENT_COMP);
        fprintf(stderr,"           File %s not found! \n", file_name);
         free(fu);exit(-1);
     } else {
        ii = 0;
        while (!feof(num))
        {
          fgets(segment[ii].st,128,num);
          if (ii >  799) {
             fprintf(stderr,"%s: Number of segments is limited to 800 !! \n",NAME_CURRENT_COMP);
              free(fu);exit(-1);
          }
          ii++;
        }
        fclose(num);
        ii--;
     }
     seg = ii-3;
     l_seg=l/seg;
     for (i=3;i<ii;i++)
     {
        if (strlen(segment[i].st) < 4)
        {
          fprintf(stderr,"Component: %s (Guide_tapering)\n",NAME_CURRENT_COMP);
          fprintf(stderr,"           Data Format Error! \n");
          free(fu);exit(-1);
        }
        h1_in[i-3] = strtod(strtok(segment[i].st," "), &ep);
        h2_out[i-3] = strtod(strtok(0," "), &ep);
        w1_in[i-3] = strtod(strtok(0," "), &ep);
        w2_out[i-3] = strtod(strtok(0," "), &ep);
     }
     h1 = h1_in[0];
     h2 = h2_out[seg-1];
     w1 = w1_in[0];
     w2 = w2_out[seg-1];
     for (i=0;i<seg;i++)
     {
      fprintf(stderr,"%d: %lf %lf %lf %lf \n",i,h1_in[i],h2_out[i],w1_in[i],w2_out[i]);
     }
  } else if (!strcmp(fu,"straight")) {
    for (i=0;i<seg;i++) {
      h1_in[i] = h2_out[i] = h2 = h1;
      w1_in[i] = w2_out[i] = w2 = w1;
    }
  } else {
     fprintf(stderr,"Component: %s (Guide_tapering)\n",NAME_CURRENT_COMP);
     fprintf(stderr,"           Unknown KEYWORD: %s \n", fu);
     free(fu);exit(-1);
  }
  fprintf(stderr,"Component: %s (Guide_tapering)\n",NAME_CURRENT_COMP);
  fprintf(stderr,"           Height at the guide exit (h2): %lf \n", h2);
  if (h2 <= 0)
  {
   fprintf(stderr,"Component: %s (Guide_tapering)\n", NAME_CURRENT_COMP);
   fprintf(stderr,"           Height at the guide exit (h2) was calculated\n");
   fprintf(stderr,"           <=0; Please change the parameter h1 and/or\n");
   fprintf(stderr,"           linh and/or louth! \n");
    free(fu);exit(-1);
  }
  if (!strcmp(fu,"elliptical"))
  {
     h1_in[0] = h1;
     for (i=1;i<seg;i++)
     {
       if (b_ell_q == 0)
       {
         h1_in[i]=h1;
       } else {
         mxi = (((lbh/2.0)-linh) - (l_seg * i));
         h1_in[i] = (sqrt((1.0-((mxi*mxi)/a_ell_q))*b_ell_q))*2.0;
       }
     h2_out[i-1] = h1_in[i];
     }
     h2_out[seg-1]=h2;
  } else if (!strcmp(fu,"parabolical")) {
     h1_in[0] = h1;
     ii=seg-1;
     if (louth == 0 && linh == 0)
     {
        for (i=1;i<(seg+1);i++)
        {
           h1_in[i]=h1;
           ii=ii-1;
           h2_out[i-1] = h1_in[i];
        }
     } else {
        if ((linh == 0) && (louth > 0))
        {
           for (i=1;i<(seg+1);i++)
           {
             h1_in[i] = (sqrt((p2_para/4.0+louth+(l_seg*ii))*p2_para))*2.0;
             ii=ii-1;
             h2_out[i-1] = h1_in[i];
           }
        } else {
           for (i=1;i<(seg+1);i++)
           {
             h1_in[i] = (sqrt((p2_para/4.0+linh+(l_seg*i))*p2_para))*2.0;
             h2_out[i-1] = h1_in[i];
           }
        }
     }
  }
  /* compute each value for horizontal mirrors */
  w12 = w1/2.0;
  if (!strcmp(fu,"elliptical"))
  {
    /* calculate lbw the distance between focal points of horizontal mirrors */
    lbw = l + linw + loutw;
    /* calculate parameter b of elliptical equestion - horizontal mirrors */
    if (linw == 0 && loutw == 0 )
    {
       /* plane mirrors (horizontal) */
       b_ell_q = 0;
       w2 = w1;
    } else {
       /* elliptical mirrors */
       u1 = sqrt((linw*linw)+(w12*w12));
       u2 = sqrt((w12*w12) + ((l+loutw)*(l+loutw)));
       a_ell_q = ((u1 + u2)/2.0)*((u1 + u2)/2.0);
       b_ell_q = a_ell_q - ((lbw/2.0)*(lbw/2.0));
       /* calculate weigth of guide exit (w2) */
       div1 = ((lbw/2.0-loutw)*(lbw/2.0-loutw))/a_ell_q;
       w2 = sqrt(b_ell_q*(1.0-div1));
       w2 = w2*2.0;
     }
  } else if (!strcmp(fu,"parabolical")) {
     if ((linw > 0) && (loutw > 0))
     {
       fprintf(stderr,"Component: %s (Guide_tapering) Two focal\n",NAME_CURRENT_COMP);
       fprintf(stderr,"           points linw and loutw are not allowed! \n");
         free(fu);exit(-1);
     }
     if (loutw == 0 && linw == 0)
     {
        /* plane mirrors (horizontal) */
        w2 = w1;
     } else {
       if (linw == 0)
       {
          /* parabolical mirrors */
          Div1=((2.0*loutw+2.0*l)*(2.0*loutw+2.0*l))/4.0;
          p2_para=((sqrt(Div1+(w12*w12)))-(loutw+l))*2.0;
          /* calculate weigth of guide exit (w2) */
          w2 = sqrt(p2_para*(loutw+p2_para/4.0));
          w2 = w2*2.0;
       } else {
          /* anti-trompete */
          Div1=((2.0*linw)*(2.0*linw))/4.0;
          p2_para=((sqrt(Div1+(w12*w12)))-linw)*2.0;
          /* calculate heigth of guide exit (w2) */
          w2 = sqrt(p2_para*(l+linw+p2_para/4.0));
          w2 = w2*2.0;
       }
     }
  }
  fprintf(stderr,"Component: %s (Guide_tapering)\n",NAME_CURRENT_COMP);
  fprintf(stderr,"           Width at the guide exit (w2): %lf \n", w2);
  if (w2 <= 0)
  {
   fprintf(stderr,"Component: %s (Guide_tapering)\n", NAME_CURRENT_COMP);
   fprintf(stderr,"           Width at the guide exit (w2) was calculated\n");
   fprintf(stderr,"           <=0; Please change the parameter w1 and/or\n");
   fprintf(stderr,"           l! \n");
    free(fu);exit(-1);
  }
  if (!strcmp(fu,"elliptical"))
  {
     w1_in[0]=w1;
     for (i=1;i<seg;i++)
     {
       if (b_ell_q == 0)
       {
         w1_in[i]=w1;
       } else {
         mxi = (((lbw/2.0)-linw) - (l_seg * i));
         w1_in[i] = (sqrt((1.0-((mxi*mxi)/a_ell_q))*b_ell_q))*2.0;
       }
       w2_out[i-1] = w1_in[i];
     }
     w2_out[seg-1]=w2;
  } else if (!strcmp(fu,"parabolical")) {
     w1_in[0]=w1;
     ii=seg-1;
     if (loutw == 0 && linw == 0)
     {
        for (i=1;i<(seg+1);i++)
        {
           w1_in[i]=w1;
           ii=ii-1;
           w2_out[i-1] = w1_in[i];
        }
     } else {
        if ((linw == 0) && (loutw > 0))
        {
           for (i=1;i<(seg+1);i++)
           {
             w1_in[i] = (sqrt((p2_para/4+loutw+(l_seg*ii))*p2_para))*2;
             ii=ii-1;
             w2_out[i-1] = w1_in[i];
           }
        } else {
           for (i=1;i<(seg+1);i++)
           {
             w1_in[i] = (sqrt((p2_para/4+linw+(l_seg*i))*p2_para))*2;
             w2_out[i-1] = w1_in[i];
           }
        }
     }
  }
  free(fu);
  for (i=0;i<seg;i++)
  {
    w1c[i] = w1_in[i];
    w2c[i] = w2_out[i];
    ww[i] = .5*(w2c[i] - w1c[i]);
    hh[i] = .5*(h2_out[i] - h1_in[i]);
    whalf[i] = .5*w1c[i];
    hhalf[i] = .5*h1_in[i];
    lwhalf[i] = l_seg*whalf[i];
    lhhalf[i] = l_seg*hhalf[i];
  }
  /* guide curvature: rotation angle [rad] between each guide segment */
  if (curvature && l && segno)   rotation_h = l/curvature/segno;
  if (curvature_v && l && segno) rotation_v = l/curvature_v/segno;
}
#line 14646 "./ThALES_resolution_v2.c"
#undef curvature_v
#undef curvature
#undef segno
#undef my
#undef mx
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef louth
#undef linh
#undef loutw
#undef linw
#undef l
#undef h1
#undef w1
#undef option
#undef rotation_v
#undef rotation_h
#undef num
#undef ep
#undef file_name
#undef pos
#undef fu
#undef seg
#undef ii
#undef i
#undef Div1
#undef test
#undef p2_para
#undef div1
#undef u2
#undef u1
#undef mxi
#undef lbh
#undef lbw
#undef b_ell_q
#undef a_ell_q
#undef w2
#undef w12
#undef h2
#undef h12
#undef seg
#undef l_seg
#undef w2_out
#undef w1_in
#undef h2_out
#undef h1_in
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component before_monochromator_slit. */
  SIG_MESSAGE("before_monochromator_slit (Init)");
#define mccompcurname  before_monochromator_slit
#define mccompcurtype  Slit
#define mccompcurindex 12
#define xmin mccbefore_monochromator_slit_xmin
#define xmax mccbefore_monochromator_slit_xmax
#define ymin mccbefore_monochromator_slit_ymin
#define ymax mccbefore_monochromator_slit_ymax
#define radius mccbefore_monochromator_slit_radius
#define xwidth mccbefore_monochromator_slit_xwidth
#define yheight mccbefore_monochromator_slit_yheight
#line 50 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
if (xwidth > 0)  { 
  if (!xmin && !xmax) {
    xmax=xwidth/2;  xmin=-xmax;
  } else {
    fprintf(stderr,"Slit: %s: Error: please specify EITHER xmin & xmax or xwidth\n", NAME_CURRENT_COMP); exit(-1);
  }
 }
 if (yheight > 0) { 
   if (!ymin && !ymax) {
     ymax=yheight/2; ymin=-ymax; 
   } else {
     fprintf(stderr,"Slit: %s: Error: please specify EITHER ymin & ymax or ywidth\n", NAME_CURRENT_COMP); exit(-1);
   }
 }
 if (xmin == 0 && xmax == 0 && ymin == 0 && ymax == 0 && radius == 0)
    { fprintf(stderr,"Slit: %s: Warning: Running with CLOSED slit - is this intentional?? \n", NAME_CURRENT_COMP); }

}
#line 14741 "./ThALES_resolution_v2.c"
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component l_monitor. */
  SIG_MESSAGE("l_monitor (Init)");
#define mccompcurname  l_monitor
#define mccompcurtype  L_monitor
#define mccompcurindex 13
#define nL mccl_monitor_nL
#define L_N mccl_monitor_L_N
#define L_p mccl_monitor_L_p
#define L_p2 mccl_monitor_L_p2
#define filename mccl_monitor_filename
#define xmin mccl_monitor_xmin
#define xmax mccl_monitor_xmax
#define ymin mccl_monitor_ymin
#define ymax mccl_monitor_ymax
#define xwidth mccl_monitor_xwidth
#define yheight mccl_monitor_yheight
#define Lmin mccl_monitor_Lmin
#define Lmax mccl_monitor_Lmax
#define restore_neutron mccl_monitor_restore_neutron
#define nowritefile mccl_monitor_nowritefile
#line 62 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/L_monitor.comp"
{
int i;

if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
    if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

    if ((xmin >= xmax) || (ymin >= ymax)) {
            printf("L_monitor: %s: Null detection area !\n"
                   "ERROR      (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
           NAME_CURRENT_COMP);
      exit(-1);
    }

    for (i=0; i<nL; i++)
    {
      L_N[i] = 0;
      L_p[i] = 0;
      L_p2[i] = 0;
    }
}
#line 14794 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef Lmax
#undef Lmin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef L_p2
#undef L_p
#undef L_N
#undef nL
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_ThALES_Monochromator_Cradle. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Cradle (Init)");

  /* Initializations for component H53_ThALES_Monochromator. */
  SIG_MESSAGE("H53_ThALES_Monochromator (Init)");
#define mccompcurname  H53_ThALES_Monochromator
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 15
#define mos_rms_y mccH53_ThALES_Monochromator_mos_rms_y
#define mos_rms_z mccH53_ThALES_Monochromator_mos_rms_z
#define mos_rms_max mccH53_ThALES_Monochromator_mos_rms_max
#define mono_Q mccH53_ThALES_Monochromator_mono_Q
#define SlabWidth mccH53_ThALES_Monochromator_SlabWidth
#define SlabHeight mccH53_ThALES_Monochromator_SlabHeight
#define rTable mccH53_ThALES_Monochromator_rTable
#define tTable mccH53_ThALES_Monochromator_tTable
#define row mccH53_ThALES_Monochromator_row
#define col mccH53_ThALES_Monochromator_col
#define tiltH mccH53_ThALES_Monochromator_tiltH
#define tiltV mccH53_ThALES_Monochromator_tiltV
#define reflect mccH53_ThALES_Monochromator_reflect
#define transmit mccH53_ThALES_Monochromator_transmit
#define zwidth mccH53_ThALES_Monochromator_zwidth
#define yheight mccH53_ThALES_Monochromator_yheight
#define gap mccH53_ThALES_Monochromator_gap
#define NH mccH53_ThALES_Monochromator_NH
#define NV mccH53_ThALES_Monochromator_NV
#define mosaich mccH53_ThALES_Monochromator_mosaich
#define mosaicv mccH53_ThALES_Monochromator_mosaicv
#define r0 mccH53_ThALES_Monochromator_r0
#define t0 mccH53_ThALES_Monochromator_t0
#define Q mccH53_ThALES_Monochromator_Q
#define RV mccH53_ThALES_Monochromator_RV
#define RH mccH53_ThALES_Monochromator_RH
#define DM mccH53_ThALES_Monochromator_DM
#define mosaic mccH53_ThALES_Monochromator_mosaic
#define width mccH53_ThALES_Monochromator_width
#define height mccH53_ThALES_Monochromator_height
#define verbose mccH53_ThALES_Monochromator_verbose
#define order mccH53_ThALES_Monochromator_order
#line 148 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  int i;

  if (mosaic != 0) {
    mos_rms_y = MIN2RAD*mosaic/sqrt(8*log(2));
    mos_rms_z = mos_rms_y; }
  else {
    mos_rms_y = MIN2RAD*mosaich/sqrt(8*log(2));
    mos_rms_z = MIN2RAD*mosaicv/sqrt(8*log(2)); }
  mos_rms_max = mos_rms_y > mos_rms_z ? mos_rms_y : mos_rms_z;

  mono_Q = Q;
  if (DM != 0) mono_Q = 2*PI/DM;

  if (mono_Q <= 0) { fprintf(stderr,"Monochromator_curved: %s: Error scattering vector Q = 0\n", NAME_CURRENT_COMP); exit(-1); }
  if (r0 <  0) { fprintf(stderr,"Monochromator_curved: %s: Error reflectivity r0 is negative\n", NAME_CURRENT_COMP); exit(-1); }
  if (r0 == 0) { fprintf(stderr,"Monochromator_curved: %s: Reflectivity r0 is null. Ignoring component.\n", NAME_CURRENT_COMP); }
  if (NH*NV == 0) { fprintf(stderr,"Monochromator_curved: %s: no slabs ??? (NH or NV=0)\n", NAME_CURRENT_COMP); exit(-1); }


  if (verbose && r0)
  {
    printf("Monochromator_curved: component %s Q=%.3g Angs-1 (DM=%.4g Angs)\n", NAME_CURRENT_COMP, mono_Q, 2*PI/mono_Q);
    if (NH*NV == 1) printf("            flat.\n");
    else
    { if (NH > 1)
      { printf("            horizontal: %i blades", (int)NH);
        if (RH != 0) printf(" focusing with RH=%.3g [m]", RH);
        printf("\n");
      }
      if (NV > 1)
      { printf("            vertical:   %i blades", (int)NV);
        if (RV != 0) printf(" focusing with RV=%.3g [m]", RV);
        printf("\n");
      }
    }
  }

  if (reflect != NULL && r0 && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
  {
    if (verbose) fprintf(stdout, "Monochromator_curved: %s: Reflectivity data (k, R) from %s\n", NAME_CURRENT_COMP, reflect);
    Table_Read(&rTable, reflect, 1); /* read 1st block data from file into rTable */
    Table_Rebin(&rTable);         /* rebin as evenly, increasing array */
    if (rTable.rows < 2) Table_Free(&rTable);
    if (verbose) Table_Info(rTable);
  } else rTable.data = NULL;

  if (transmit != NULL && strlen(transmit) && strcmp(transmit,"NULL") && strcmp(transmit,"0"))
  {
    if (verbose) fprintf(stdout, "Monochromator_curved: %s: Transmission data (k, T) from %s\n", NAME_CURRENT_COMP, transmit);
    Table_Read(&tTable, transmit, 1); /* read 1st block data from file into rTable */
    Table_Rebin(&tTable);         /* rebin as evenly, increasing array */
    if (tTable.rows < 2) Table_Free(&tTable);
    if (verbose) Table_Info(tTable);
  } else tTable.data = NULL;

  if (width == 0) SlabWidth = zwidth;
  else SlabWidth = (width+gap)/NH - gap;
  if (height == 0) SlabHeight = yheight;
  else SlabHeight = (height+gap)/NV - gap;

  tiltH=malloc((int)(NH+1)*sizeof(double));
  tiltV=malloc((int)(NV+1)*sizeof(double));

  if (!tiltH) printf("Monochromator_curved: %s: Warning: not enough memory to allocate tilts (NH=%g).\n", NAME_CURRENT_COMP, NH);
  else if (RH) { /* pre-compute tilts */
    for (i=0;i<=NH;i++)
    {
      tiltH[i]=asin((i-(NH+1)/2)*(SlabWidth+gap)/RH);
    }
  }
  if (!tiltV) printf("Monochromator_curved: %s: Warning: not enough memory to allocate tilts (NV=%g).\n", NAME_CURRENT_COMP, NV);
  else if (RV) {
    for (i=0;i<=NV;i++)
    {
      tiltV[i]=-asin((i-(NV+1)/2)*(SlabHeight+gap)/RV);
    }
  }

}
#line 14935 "./ThALES_resolution_v2.c"
#undef order
#undef verbose
#undef height
#undef width
#undef mosaic
#undef DM
#undef RH
#undef RV
#undef Q
#undef t0
#undef r0
#undef mosaicv
#undef mosaich
#undef NV
#undef NH
#undef gap
#undef yheight
#undef zwidth
#undef transmit
#undef reflect
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component H53_ThALES_Monochromator_Out. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Out (Init)");

  /* Initializations for component before_sample_slit. */
  SIG_MESSAGE("before_sample_slit (Init)");
#define mccompcurname  before_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 17
#define xmin mccbefore_sample_slit_xmin
#define xmax mccbefore_sample_slit_xmax
#define ymin mccbefore_sample_slit_ymin
#define ymax mccbefore_sample_slit_ymax
#define radius mccbefore_sample_slit_radius
#define xwidth mccbefore_sample_slit_xwidth
#define yheight mccbefore_sample_slit_yheight
#line 50 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
if (xwidth > 0)  { 
  if (!xmin && !xmax) {
    xmax=xwidth/2;  xmin=-xmax;
  } else {
    fprintf(stderr,"Slit: %s: Error: please specify EITHER xmin & xmax or xwidth\n", NAME_CURRENT_COMP); exit(-1);
  }
 }
 if (yheight > 0) { 
   if (!ymin && !ymax) {
     ymax=yheight/2; ymin=-ymax; 
   } else {
     fprintf(stderr,"Slit: %s: Error: please specify EITHER ymin & ymax or ywidth\n", NAME_CURRENT_COMP); exit(-1);
   }
 }
 if (xmin == 0 && xmax == 0 && ymin == 0 && ymax == 0 && radius == 0)
    { fprintf(stderr,"Slit: %s: Warning: Running with CLOSED slit - is this intentional?? \n", NAME_CURRENT_COMP); }

}
#line 15007 "./ThALES_resolution_v2.c"
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component E_sample_mon. */
  SIG_MESSAGE("E_sample_mon (Init)");
#define mccompcurname  E_sample_mon
#define mccompcurtype  E_monitor
#define mccompcurindex 18
#define nE mccE_sample_mon_nE
#define E_N mccE_sample_mon_E_N
#define E_p mccE_sample_mon_E_p
#define E_p2 mccE_sample_mon_E_p2
#define S_p mccE_sample_mon_S_p
#define S_pE mccE_sample_mon_S_pE
#define S_pE2 mccE_sample_mon_S_pE2
#define filename mccE_sample_mon_filename
#define xmin mccE_sample_mon_xmin
#define xmax mccE_sample_mon_xmax
#define ymin mccE_sample_mon_ymin
#define ymax mccE_sample_mon_ymax
#define xwidth mccE_sample_mon_xwidth
#define yheight mccE_sample_mon_yheight
#define Emin mccE_sample_mon_Emin
#define Emax mccE_sample_mon_Emax
#define restore_neutron mccE_sample_mon_restore_neutron
#define nowritefile mccE_sample_mon_nowritefile
#line 66 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/E_monitor.comp"
{
int i;

if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
    if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

    if ((xmin >= xmax) || (ymin >= ymax)) {
            printf("E_monitor: %s: Null detection area !\n"
                   "ERROR      (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
           NAME_CURRENT_COMP);
      exit(-1);
    }

    for (i=0; i<nE; i++)
    {
      E_N[i] = 0;
      E_p[i] = 0;
      E_p2[i] = 0;
    }
    S_p = S_pE = S_pE2 = 0;
}
#line 15064 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef Emax
#undef Emin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef nE
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component PSD_sample_mon. */
  SIG_MESSAGE("PSD_sample_mon (Init)");
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
#define nx mccPSD_sample_mon_nx
#define ny mccPSD_sample_mon_ny
#define filename mccPSD_sample_mon_filename
#define xmin mccPSD_sample_mon_xmin
#define xmax mccPSD_sample_mon_xmax
#define ymin mccPSD_sample_mon_ymin
#define ymax mccPSD_sample_mon_ymax
#define xwidth mccPSD_sample_mon_xwidth
#define yheight mccPSD_sample_mon_yheight
#define restore_neutron mccPSD_sample_mon_restore_neutron
#define nowritefile mccPSD_sample_mon_nowritefile
#line 69 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
  if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

  if ((xmin >= xmax) || (ymin >= ymax)){
    printf("PSD_monitor: %s: Null detection area !\n"
           "ERROR        (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
    NAME_CURRENT_COMP);
    exit(-1);
  }

  PSD_N = create_darr2d(nx, ny);
  PSD_p = create_darr2d(nx, ny);
  PSD_p2 = create_darr2d(nx, ny);

  int i, j;
  for (i=0; i<nx; i++){
    for (j=0; j<ny; j++){
      PSD_N[i][j] = 0;
      PSD_p[i][j] = 0;
      PSD_p2[i][j] = 0;
    }
  }
}
#line 15131 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component sample_arm. */
  SIG_MESSAGE("sample_arm (Init)");

  /* Initializations for component res_sample. */
  SIG_MESSAGE("res_sample (Init)");
#define mccompcurname  res_sample
#define mccompcurtype  Res_sample
#define mccompcurindex 21
#define res_struct mccres_sample_res_struct
#define thickness mccres_sample_thickness
#define radius mccres_sample_radius
#define focus_r mccres_sample_focus_r
#define E0 mccres_sample_E0
#define dE mccres_sample_dE
#define target_x mccres_sample_target_x
#define target_y mccres_sample_target_y
#define target_z mccres_sample_target_z
#define focus_xw mccres_sample_focus_xw
#define focus_yh mccres_sample_focus_yh
#define focus_aw mccres_sample_focus_aw
#define focus_ah mccres_sample_focus_ah
#define xwidth mccres_sample_xwidth
#define yheight mccres_sample_yheight
#define zdepth mccres_sample_zdepth
#define target_index mccres_sample_target_index
#line 88 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../samples/Res_sample.comp"
{
if (!radius || !yheight) {
    if (!xwidth || !yheight || !zdepth) exit(fprintf(stderr,"Res_sample: %s: sample has no volume (zero dimensions)\n", NAME_CURRENT_COMP));
    else res_struct.isrect=1; }
  else res_struct.isrect=0;

  /* now compute target coords if a component index is supplied */
  if (!target_index && !target_x && !target_y && !target_z) target_index=1;
  if (target_index)
  {
    Coords ToTarget;
    ToTarget = coords_sub(POS_A_COMP_INDEX(INDEX_CURRENT_COMP+target_index),POS_A_CURRENT_COMP);
    ToTarget = rot_apply(ROT_A_CURRENT_COMP, ToTarget);
    coords_get(ToTarget, &res_struct.tx, &res_struct.ty, &res_struct.tz);
  }
  else
  { res_struct.tx = target_x; res_struct.ty = target_y; res_struct.tz = target_z; }

  if (!(res_struct.tx || res_struct.ty || res_struct.tz)) {
    printf("Res_sample: %s: The target is not defined. Using direct beam (Z-axis).\n",
      NAME_CURRENT_COMP);
    res_struct.tz=1;
  }

  /* different ways of setting rectangular area */
  res_struct.aw  = res_struct.ah = 0;
  if (focus_xw) {
    res_struct.xw = focus_xw;
  }
  if (focus_yh) {
    res_struct.yh = focus_yh;
  }
  if (focus_aw) {
    res_struct.aw = DEG2RAD*focus_aw;
  }
  if (focus_ah) {
    res_struct.ah = DEG2RAD*focus_ah;
  }
}
#line 15215 "./ThALES_resolution_v2.c"
#undef target_index
#undef zdepth
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef dE
#undef E0
#undef focus_r
#undef radius
#undef thickness
#undef res_struct
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component v_sample. */
  SIG_MESSAGE("v_sample (Init)");
#define mccompcurname  v_sample
#define mccompcurtype  V_sample
#define mccompcurindex 22
#define VarsV mccv_sample_VarsV
#define radius mccv_sample_radius
#define thickness mccv_sample_thickness
#define zdepth mccv_sample_zdepth
#define Vc mccv_sample_Vc
#define sigma_abs mccv_sample_sigma_abs
#define sigma_inc mccv_sample_sigma_inc
#define radius_i mccv_sample_radius_i
#define radius_o mccv_sample_radius_o
#define h mccv_sample_h
#define focus_r mccv_sample_focus_r
#define pack mccv_sample_pack
#define frac mccv_sample_frac
#define f_QE mccv_sample_f_QE
#define gamma mccv_sample_gamma
#define target_x mccv_sample_target_x
#define target_y mccv_sample_target_y
#define target_z mccv_sample_target_z
#define focus_xw mccv_sample_focus_xw
#define focus_yh mccv_sample_focus_yh
#define focus_aw mccv_sample_focus_aw
#define focus_ah mccv_sample_focus_ah
#define xwidth mccv_sample_xwidth
#define yheight mccv_sample_yheight
#define zthick mccv_sample_zthick
#define rad_sphere mccv_sample_rad_sphere
#define sig_a mccv_sample_sig_a
#define sig_i mccv_sample_sig_i
#define V0 mccv_sample_V0
#define target_index mccv_sample_target_index
#define multiples mccv_sample_multiples
#line 121 "V_sample.comp"
{
  /* Backward compatibility */
  if (radius) radius_o = radius;
  if (thickness) radius_i = radius_o - thickness;
  if (zdepth) zthick = zdepth;
  if (yheight) h = yheight;
  if (Vc) V0 = Vc;
  if (sigma_abs) sig_a = sigma_abs;
  if (sigma_inc) sig_i = sigma_inc;

  VarsV.shapetyp = -1;
  if (xwidth && yheight && zdepth)  VarsV.shapetyp=1; /* box */
  else if (radius > 0 && yheight)        VarsV.shapetyp=0; /* cylinder */
  else if (radius && !yheight)           VarsV.shapetyp=2; /* sphere */
  
  if (VarsV.shapetyp < 0)
    exit(fprintf(stderr,"V_sample: %s: sample has invalid dimensions. Please check parameter values.\n", NAME_CURRENT_COMP));

  VarsV.sigma_a=sig_a;
  VarsV.sigma_i=sig_i;
  VarsV.rho = (pack/V0);
  VarsV.my_s=(VarsV.rho * 100 * VarsV.sigma_i);
  VarsV.my_a_v=(VarsV.rho * 100 * VarsV.sigma_a);

  /* now compute target coords if a component index is supplied */
  VarsV.tx= VarsV.ty=VarsV.tz=0;
  if (target_index)
  {
    Coords ToTarget;
    ToTarget = coords_sub(POS_A_COMP_INDEX(INDEX_CURRENT_COMP+target_index),POS_A_CURRENT_COMP);
    ToTarget = rot_apply(ROT_A_CURRENT_COMP, ToTarget);
    coords_get(ToTarget, &VarsV.tx, &VarsV.ty, &VarsV.tz);
  }
  else
  { VarsV.tx = target_x; VarsV.ty = target_y; VarsV.tz = target_z; }

  if (!(VarsV.tx || VarsV.ty || VarsV.tz))
    printf("V_sample: %s: The target is not defined. Using direct beam (Z-axis).\n",
      NAME_CURRENT_COMP);

  VarsV.distance=sqrt(VarsV.tx*VarsV.tx+VarsV.ty*VarsV.ty+VarsV.tz*VarsV.tz);

  /* different ways of setting rectangular area */
  VarsV.aw  = VarsV.ah = 0;
  if (focus_xw) {
  VarsV.xw = focus_xw;
  }
  if (focus_yh) {
    VarsV.yh = focus_yh;
  }
  if (focus_aw) {
    VarsV.aw = DEG2RAD*focus_aw;
  }
  if (focus_ah) {
    VarsV.ah = DEG2RAD*focus_ah;
  }
}
#line 15331 "./ThALES_resolution_v2.c"
#undef multiples
#undef target_index
#undef V0
#undef sig_i
#undef sig_a
#undef rad_sphere
#undef zthick
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef gamma
#undef f_QE
#undef frac
#undef pack
#undef focus_r
#undef h
#undef radius_o
#undef radius_i
#undef sigma_inc
#undef sigma_abs
#undef Vc
#undef zdepth
#undef thickness
#undef radius
#undef VarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component Sample_Out. */
  SIG_MESSAGE("Sample_Out (Init)");

  /* Initializations for component after_sample_slit. */
  SIG_MESSAGE("after_sample_slit (Init)");
#define mccompcurname  after_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 24
#define xmin mccafter_sample_slit_xmin
#define xmax mccafter_sample_slit_xmax
#define ymin mccafter_sample_slit_ymin
#define ymax mccafter_sample_slit_ymax
#define radius mccafter_sample_slit_radius
#define xwidth mccafter_sample_slit_xwidth
#define yheight mccafter_sample_slit_yheight
#line 50 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
if (xwidth > 0)  { 
  if (!xmin && !xmax) {
    xmax=xwidth/2;  xmin=-xmax;
  } else {
    fprintf(stderr,"Slit: %s: Error: please specify EITHER xmin & xmax or xwidth\n", NAME_CURRENT_COMP); exit(-1);
  }
 }
 if (yheight > 0) { 
   if (!ymin && !ymax) {
     ymax=yheight/2; ymin=-ymax; 
   } else {
     fprintf(stderr,"Slit: %s: Error: please specify EITHER ymin & ymax or ywidth\n", NAME_CURRENT_COMP); exit(-1);
   }
 }
 if (xmin == 0 && xmax == 0 && ymin == 0 && ymax == 0 && radius == 0)
    { fprintf(stderr,"Slit: %s: Warning: Running with CLOSED slit - is this intentional?? \n", NAME_CURRENT_COMP); }

}
#line 15402 "./ThALES_resolution_v2.c"
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component Ana_Cradle. */
  SIG_MESSAGE("Ana_Cradle (Init)");

  /* Initializations for component PSD_analyzer. */
  SIG_MESSAGE("PSD_analyzer (Init)");
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
#define nx mccPSD_analyzer_nx
#define ny mccPSD_analyzer_ny
#define filename mccPSD_analyzer_filename
#define xmin mccPSD_analyzer_xmin
#define xmax mccPSD_analyzer_xmax
#define ymin mccPSD_analyzer_ymin
#define ymax mccPSD_analyzer_ymax
#define xwidth mccPSD_analyzer_xwidth
#define yheight mccPSD_analyzer_yheight
#define restore_neutron mccPSD_analyzer_restore_neutron
#define nowritefile mccPSD_analyzer_nowritefile
#line 69 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
  if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

  if ((xmin >= xmax) || (ymin >= ymax)){
    printf("PSD_monitor: %s: Null detection area !\n"
           "ERROR        (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
    NAME_CURRENT_COMP);
    exit(-1);
  }

  PSD_N = create_darr2d(nx, ny);
  PSD_p = create_darr2d(nx, ny);
  PSD_p2 = create_darr2d(nx, ny);

  int i, j;
  for (i=0; i<nx; i++){
    for (j=0; j<ny; j++){
      PSD_N[i][j] = 0;
      PSD_p[i][j] = 0;
      PSD_p2[i][j] = 0;
    }
  }
}
#line 15461 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component analyzer. */
  SIG_MESSAGE("analyzer (Init)");
#define mccompcurname  analyzer
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 27
#define mos_rms_y mccanalyzer_mos_rms_y
#define mos_rms_z mccanalyzer_mos_rms_z
#define mos_rms_max mccanalyzer_mos_rms_max
#define mono_Q mccanalyzer_mono_Q
#define SlabWidth mccanalyzer_SlabWidth
#define SlabHeight mccanalyzer_SlabHeight
#define rTable mccanalyzer_rTable
#define tTable mccanalyzer_tTable
#define row mccanalyzer_row
#define col mccanalyzer_col
#define tiltH mccanalyzer_tiltH
#define tiltV mccanalyzer_tiltV
#define reflect mccanalyzer_reflect
#define transmit mccanalyzer_transmit
#define zwidth mccanalyzer_zwidth
#define yheight mccanalyzer_yheight
#define gap mccanalyzer_gap
#define NH mccanalyzer_NH
#define NV mccanalyzer_NV
#define mosaich mccanalyzer_mosaich
#define mosaicv mccanalyzer_mosaicv
#define r0 mccanalyzer_r0
#define t0 mccanalyzer_t0
#define Q mccanalyzer_Q
#define RV mccanalyzer_RV
#define RH mccanalyzer_RH
#define DM mccanalyzer_DM
#define mosaic mccanalyzer_mosaic
#define width mccanalyzer_width
#define height mccanalyzer_height
#define verbose mccanalyzer_verbose
#define order mccanalyzer_order
#line 148 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  int i;

  if (mosaic != 0) {
    mos_rms_y = MIN2RAD*mosaic/sqrt(8*log(2));
    mos_rms_z = mos_rms_y; }
  else {
    mos_rms_y = MIN2RAD*mosaich/sqrt(8*log(2));
    mos_rms_z = MIN2RAD*mosaicv/sqrt(8*log(2)); }
  mos_rms_max = mos_rms_y > mos_rms_z ? mos_rms_y : mos_rms_z;

  mono_Q = Q;
  if (DM != 0) mono_Q = 2*PI/DM;

  if (mono_Q <= 0) { fprintf(stderr,"Monochromator_curved: %s: Error scattering vector Q = 0\n", NAME_CURRENT_COMP); exit(-1); }
  if (r0 <  0) { fprintf(stderr,"Monochromator_curved: %s: Error reflectivity r0 is negative\n", NAME_CURRENT_COMP); exit(-1); }
  if (r0 == 0) { fprintf(stderr,"Monochromator_curved: %s: Reflectivity r0 is null. Ignoring component.\n", NAME_CURRENT_COMP); }
  if (NH*NV == 0) { fprintf(stderr,"Monochromator_curved: %s: no slabs ??? (NH or NV=0)\n", NAME_CURRENT_COMP); exit(-1); }


  if (verbose && r0)
  {
    printf("Monochromator_curved: component %s Q=%.3g Angs-1 (DM=%.4g Angs)\n", NAME_CURRENT_COMP, mono_Q, 2*PI/mono_Q);
    if (NH*NV == 1) printf("            flat.\n");
    else
    { if (NH > 1)
      { printf("            horizontal: %i blades", (int)NH);
        if (RH != 0) printf(" focusing with RH=%.3g [m]", RH);
        printf("\n");
      }
      if (NV > 1)
      { printf("            vertical:   %i blades", (int)NV);
        if (RV != 0) printf(" focusing with RV=%.3g [m]", RV);
        printf("\n");
      }
    }
  }

  if (reflect != NULL && r0 && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
  {
    if (verbose) fprintf(stdout, "Monochromator_curved: %s: Reflectivity data (k, R) from %s\n", NAME_CURRENT_COMP, reflect);
    Table_Read(&rTable, reflect, 1); /* read 1st block data from file into rTable */
    Table_Rebin(&rTable);         /* rebin as evenly, increasing array */
    if (rTable.rows < 2) Table_Free(&rTable);
    if (verbose) Table_Info(rTable);
  } else rTable.data = NULL;

  if (transmit != NULL && strlen(transmit) && strcmp(transmit,"NULL") && strcmp(transmit,"0"))
  {
    if (verbose) fprintf(stdout, "Monochromator_curved: %s: Transmission data (k, T) from %s\n", NAME_CURRENT_COMP, transmit);
    Table_Read(&tTable, transmit, 1); /* read 1st block data from file into rTable */
    Table_Rebin(&tTable);         /* rebin as evenly, increasing array */
    if (tTable.rows < 2) Table_Free(&tTable);
    if (verbose) Table_Info(tTable);
  } else tTable.data = NULL;

  if (width == 0) SlabWidth = zwidth;
  else SlabWidth = (width+gap)/NH - gap;
  if (height == 0) SlabHeight = yheight;
  else SlabHeight = (height+gap)/NV - gap;

  tiltH=malloc((int)(NH+1)*sizeof(double));
  tiltV=malloc((int)(NV+1)*sizeof(double));

  if (!tiltH) printf("Monochromator_curved: %s: Warning: not enough memory to allocate tilts (NH=%g).\n", NAME_CURRENT_COMP, NH);
  else if (RH) { /* pre-compute tilts */
    for (i=0;i<=NH;i++)
    {
      tiltH[i]=asin((i-(NH+1)/2)*(SlabWidth+gap)/RH);
    }
  }
  if (!tiltV) printf("Monochromator_curved: %s: Warning: not enough memory to allocate tilts (NV=%g).\n", NAME_CURRENT_COMP, NV);
  else if (RV) {
    for (i=0;i<=NV;i++)
    {
      tiltV[i]=-asin((i-(NV+1)/2)*(SlabHeight+gap)/RV);
    }
  }

}
#line 15598 "./ThALES_resolution_v2.c"
#undef order
#undef verbose
#undef height
#undef width
#undef mosaic
#undef DM
#undef RH
#undef RV
#undef Q
#undef t0
#undef r0
#undef mosaicv
#undef mosaich
#undef NV
#undef NH
#undef gap
#undef yheight
#undef zwidth
#undef transmit
#undef reflect
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component Ana_Out. */
  SIG_MESSAGE("Ana_Out (Init)");

  /* Initializations for component slit. */
  SIG_MESSAGE("slit (Init)");
#define mccompcurname  slit
#define mccompcurtype  Slit
#define mccompcurindex 29
#define xmin mccslit_xmin
#define xmax mccslit_xmax
#define ymin mccslit_ymin
#define ymax mccslit_ymax
#define radius mccslit_radius
#define xwidth mccslit_xwidth
#define yheight mccslit_yheight
#line 50 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
if (xwidth > 0)  { 
  if (!xmin && !xmax) {
    xmax=xwidth/2;  xmin=-xmax;
  } else {
    fprintf(stderr,"Slit: %s: Error: please specify EITHER xmin & xmax or xwidth\n", NAME_CURRENT_COMP); exit(-1);
  }
 }
 if (yheight > 0) { 
   if (!ymin && !ymax) {
     ymax=yheight/2; ymin=-ymax; 
   } else {
     fprintf(stderr,"Slit: %s: Error: please specify EITHER ymin & ymax or ywidth\n", NAME_CURRENT_COMP); exit(-1);
   }
 }
 if (xmin == 0 && xmax == 0 && ymin == 0 && ymax == 0 && radius == 0)
    { fprintf(stderr,"Slit: %s: Warning: Running with CLOSED slit - is this intentional?? \n", NAME_CURRENT_COMP); }

}
#line 15670 "./ThALES_resolution_v2.c"
#undef yheight
#undef xwidth
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component PSD_det. */
  SIG_MESSAGE("PSD_det (Init)");
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
#define nx mccPSD_det_nx
#define ny mccPSD_det_ny
#define filename mccPSD_det_filename
#define xmin mccPSD_det_xmin
#define xmax mccPSD_det_xmax
#define ymin mccPSD_det_ymin
#define ymax mccPSD_det_ymax
#define xwidth mccPSD_det_xwidth
#define yheight mccPSD_det_yheight
#define restore_neutron mccPSD_det_restore_neutron
#define nowritefile mccPSD_det_nowritefile
#line 69 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
  if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

  if ((xmin >= xmax) || (ymin >= ymax)){
    printf("PSD_monitor: %s: Null detection area !\n"
           "ERROR        (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
    NAME_CURRENT_COMP);
    exit(-1);
  }

  PSD_N = create_darr2d(nx, ny);
  PSD_p = create_darr2d(nx, ny);
  PSD_p2 = create_darr2d(nx, ny);

  int i, j;
  for (i=0; i<nx; i++){
    for (j=0; j<ny; j++){
      PSD_N[i][j] = 0;
      PSD_p[i][j] = 0;
      PSD_p2[i][j] = 0;
    }
  }
}
#line 15726 "./ThALES_resolution_v2.c"
#undef nowritefile
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef filename
#undef ny
#undef nx
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component res_monitor. */
  SIG_MESSAGE("res_monitor (Init)");
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
#define filename mccres_monitor_filename
#define options mccres_monitor_options
#define xwidth mccres_monitor_xwidth
#define yheight mccres_monitor_yheight
#define zdepth mccres_monitor_zdepth
#define radius mccres_monitor_radius
#define xmin mccres_monitor_xmin
#define xmax mccres_monitor_xmax
#define ymin mccres_monitor_ymin
#define ymax mccres_monitor_ymax
#define zmin mccres_monitor_zmin
#define zmax mccres_monitor_zmax
#define bufsize mccres_monitor_bufsize
#define restore_neutron mccres_monitor_restore_neutron
#line 88 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
{
long buffer_index=0;

int i;
char tmp[1024];
strcpy(Vars.compcurname, NAME_CURRENT_COMP);

  if (options != NULL)
    strncpy(tmp, options, 1024);
  else
    strcpy(tmp, "");

  if (strstr(tmp, "list"))
    exit(fprintf(stderr, "Res_monitor: %s: Error: Only use geometry keywords (remove list from 'option').\n", NAME_CURRENT_COMP));
  if (!bufsize)
    sprintf(Vars.option, "%s borders list all, x vx sx y vy sy z vz sz t ", tmp);
  else
    sprintf(Vars.option, "%s borders list=%f, x vx sx y vy sy z vz sz t ", tmp, bufsize);

  if (radius) xwidth = 2*radius;

  Monitor_nD_Init(&DEFS, &Vars, xwidth, yheight, zdepth, xmin,xmax,ymin,ymax,zmin,zmax,0);

  if (Vars.Coord_Number != 10) exit(fprintf(stderr,"Res_monitor: %s: Error: Invalid number of variables to monitor (%li).\n", NAME_CURRENT_COMP, Vars.Coord_Number+1));
  /* set the labels */
  /* we have to record ki_x ki_y ki_z kf_x kf_y kf_z x y z p_i p_f */
  strcpy(tmp,"ki_x"); strcpy(Vars.Coord_Label[0],tmp);strcpy(Vars.Coord_Var[0],tmp);
  strcpy(tmp,"ki_y"); strcpy(Vars.Coord_Label[1],tmp);strcpy(Vars.Coord_Var[1],tmp);
  strcpy(tmp,"ki_z"); strcpy(Vars.Coord_Label[2],tmp);strcpy(Vars.Coord_Var[2],tmp);
  strcpy(tmp,"kf_x"); strcpy(Vars.Coord_Label[3],tmp);strcpy(Vars.Coord_Var[3],tmp);
  strcpy(tmp,"kf_y"); strcpy(Vars.Coord_Label[4],tmp);strcpy(Vars.Coord_Var[4],tmp);
  strcpy(tmp,"kf_z"); strcpy(Vars.Coord_Label[5],tmp);strcpy(Vars.Coord_Var[5],tmp);
  strcpy(tmp,"x");    strcpy(Vars.Coord_Label[6],tmp);strcpy(Vars.Coord_Var[6],tmp);
  strcpy(tmp,"y");    strcpy(Vars.Coord_Label[7],tmp);strcpy(Vars.Coord_Var[7],tmp);
  strcpy(tmp,"z");    strcpy(Vars.Coord_Label[8],tmp);strcpy(Vars.Coord_Var[8],tmp);
  strcpy(tmp,"p_i");  strcpy(Vars.Coord_Label[9],tmp);strcpy(Vars.Coord_Var[9],tmp);
  strcpy(tmp,"p_f");  strcpy(Vars.Coord_Label[10],tmp);strcpy(Vars.Coord_Var[10],tmp);

  if (filename != NULL)
    strncpy(Vars.Mon_File, filename, 128);
}
#line 15810 "./ThALES_resolution_v2.c"
#undef restore_neutron
#undef bufsize
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef radius
#undef zdepth
#undef yheight
#undef xwidth
#undef options
#undef filename
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component detector_all. */
  SIG_MESSAGE("detector_all (Init)");
#define mccompcurname  detector_all
#define mccompcurtype  Monitor
#define mccompcurindex 32
#define Nsum mccdetector_all_Nsum
#define psum mccdetector_all_psum
#define p2sum mccdetector_all_p2sum
#define xmin mccdetector_all_xmin
#define xmax mccdetector_all_xmax
#define ymin mccdetector_all_ymin
#define ymax mccdetector_all_ymax
#define xwidth mccdetector_all_xwidth
#define yheight mccdetector_all_yheight
#define restore_neutron mccdetector_all_restore_neutron
#line 57 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Monitor.comp"
{
psum = 0;
p2sum = 0;
Nsum = 0;

if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
    if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

    if ((xmin >= xmax) || (ymin >= ymax)) {
            printf("Monitor: %s: Null detection area !\n"
                   "ERROR    (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
           NAME_CURRENT_COMP);
      exit(-1);
    }
}
#line 15864 "./ThALES_resolution_v2.c"
#undef restore_neutron
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef p2sum
#undef psum
#undef Nsum
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if(mcdotrace) mcdisplay();
    mcDEBUG_INSTR_END()
  }

} /* end init */

void mcraytrace(void) {
  /* Neutronics-specific defines */
#ifdef NEUTRONICS
extern double mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz;
extern double mcnt, mcnsx, mcnsy, mcnsz, mcnp;
#endif
  /* End of Neutronics-specific defines */
  /* Copy neutron state to local variables. */
  MCNUM mcnlx = mcnx;
  MCNUM mcnly = mcny;
  MCNUM mcnlz = mcnz;
  MCNUM mcnlvx = mcnvx;
  MCNUM mcnlvy = mcnvy;
  MCNUM mcnlvz = mcnvz;
  MCNUM mcnlt = mcnt;
  MCNUM mcnlsx = mcnsx;
  MCNUM mcnlsy = mcnsy;
  MCNUM mcnlsz = mcnsz;
  MCNUM mcnlp = mcnp;

  mcDEBUG_ENTER()
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define mcabsorb mcabsorbAll
  /* TRACE Component Origin [1] */
  mccoordschange(mcposrOrigin, mcrotrOrigin,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component Origin (without coords transformations) */
  mcJumpTrace_Origin:
  SIG_MESSAGE("Origin (Trace)");
  mcDEBUG_COMP("Origin")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompOrigin
  STORE_NEUTRON(1,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[1]++;
  mcPCounter[1] += p;
  mcP2Counter[1] += p*p;
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
{   /* Declarations of Origin=Progress_bar() SETTING parameters. */
char* profile = mccOrigin_profile;
MCNUM percent = mccOrigin_percent;
MCNUM flag_save = mccOrigin_flag_save;
MCNUM minutes = mccOrigin_minutes;
#line 70 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
{
  double ncount;
  ncount = mcget_run_num();
  if (!StartTime) {
    time(&StartTime); /* compute starting time */
    IntermediateCnts = 1e3;
  }
  time_t NowTime;
  time(&NowTime);
  /* compute initial estimate of computation duration */
  if (!EndTime && ncount >= IntermediateCnts) {
    CurrentTime = NowTime;
    if (difftime(NowTime,StartTime) > 10 && ncount) { /* wait 10 sec before writing ETA */
      EndTime = StartTime + (time_t)(difftime(NowTime,StartTime)
				     *(double)mcget_ncount()/ncount);
      IntermediateCnts = 0;
      fprintf(stdout, "\nTrace ETA ");
      if (difftime(EndTime,StartTime) < 60.0)
        fprintf(stdout, "%g [s] %% ", difftime(EndTime,StartTime));
      else if (difftime(EndTime,StartTime) > 3600.0)
        fprintf(stdout, "%g [h] %% ", difftime(EndTime,StartTime)/3600.0);
      else
        fprintf(stdout, "%g [min] %% ", difftime(EndTime,StartTime)/60.0);
    } else IntermediateCnts += 1e3;
    fflush(stdout);
  }

  /* display percentage when percent or minutes have reached step */
  if (EndTime && mcget_ncount() &&
    (    (minutes && difftime(NowTime,CurrentTime) > minutes*60)
      || (percent && !minutes && ncount >= IntermediateCnts))   )
  {
    fprintf(stdout, "%d ", (int)(ncount*100.0/mcget_ncount())); fflush(stdout);
    CurrentTime = NowTime;

    IntermediateCnts = ncount + percent*mcget_ncount()/100;
    /* check that next intermediate ncount check is a multiple of the desired percentage */
    IntermediateCnts = floor(IntermediateCnts*100/percent/mcget_ncount())*percent*mcget_ncount()/100;
    /* raise flag to indicate that we did something */
    SCATTER;
    if (flag_save) mcsave(NULL);
  }
}
#line 16032 "./ThALES_resolution_v2.c"
}   /* End of Origin=Progress_bar() SETTING parameter declarations. */
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompOrigin:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(1,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component HCS [2] */
  mccoordschange(mcposrHCS, mcrotrHCS,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component HCS (without coords transformations) */
  mcJumpTrace_HCS:
  SIG_MESSAGE("HCS (Trace)");
  mcDEBUG_COMP("HCS")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompHCS
  STORE_NEUTRON(2,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[2]++;
  mcPCounter[2] += p;
  mcP2Counter[2] += p*p;
#define mccompcurname  HCS
#define mccompcurtype  Source_gen
#define mccompcurindex 2
#define p_in mccHCS_p_in
#define lambda1 mccHCS_lambda1
#define lambda2 mccHCS_lambda2
#define lambda3 mccHCS_lambda3
#define pTable mccHCS_pTable
#define pTable_x mccHCS_pTable_x
#define pTable_y mccHCS_pTable_y
#define pTable_xmin mccHCS_pTable_xmin
#define pTable_xmax mccHCS_pTable_xmax
#define pTable_xsum mccHCS_pTable_xsum
#define pTable_ymin mccHCS_pTable_ymin
#define pTable_ymax mccHCS_pTable_ymax
#define pTable_ysum mccHCS_pTable_ysum
#define pTable_dxmin mccHCS_pTable_dxmin
#define pTable_dxmax mccHCS_pTable_dxmax
#define pTable_dymin mccHCS_pTable_dymin
#define pTable_dymax mccHCS_pTable_dymax
{   /* Declarations of HCS=Source_gen() SETTING parameters. */
char* flux_file = mccHCS_flux_file;
char* xdiv_file = mccHCS_xdiv_file;
char* ydiv_file = mccHCS_ydiv_file;
MCNUM radius = mccHCS_radius;
MCNUM dist = mccHCS_dist;
MCNUM focus_xw = mccHCS_focus_xw;
MCNUM focus_yh = mccHCS_focus_yh;
MCNUM focus_aw = mccHCS_focus_aw;
MCNUM focus_ah = mccHCS_focus_ah;
MCNUM E0 = mccHCS_E0;
MCNUM dE = mccHCS_dE;
MCNUM lambda0 = mccHCS_lambda0;
MCNUM dlambda = mccHCS_dlambda;
MCNUM I1 = mccHCS_I1;
MCNUM yheight = mccHCS_yheight;
MCNUM xwidth = mccHCS_xwidth;
MCNUM verbose = mccHCS_verbose;
MCNUM T1 = mccHCS_T1;
MCNUM flux_file_perAA = mccHCS_flux_file_perAA;
MCNUM flux_file_log = mccHCS_flux_file_log;
MCNUM Lmin = mccHCS_Lmin;
MCNUM Lmax = mccHCS_Lmax;
MCNUM Emin = mccHCS_Emin;
MCNUM Emax = mccHCS_Emax;
MCNUM T2 = mccHCS_T2;
MCNUM I2 = mccHCS_I2;
MCNUM T3 = mccHCS_T3;
MCNUM I3 = mccHCS_I3;
MCNUM zdepth = mccHCS_zdepth;
int target_index = mccHCS_target_index;
#line 479 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"
{
  double dx=0,dy=0,xf,yf,rf,pdir,chi,v,r, lambda;
  double Maxwell;

  if (verbose >= 0)
  {

    z=0;

    if (radius)
    {
      chi=2*PI*rand01();                          /* Choose point on source */
      r=sqrt(rand01())*radius;                    /* with uniform distribution. */
      x=r*cos(chi);
      y=r*sin(chi);
    }
    else
    {
      x = xwidth*randpm1()/2;   /* select point on source (uniform) */
      y = yheight*randpm1()/2;
    }
    if (zdepth != 0)
      z = zdepth*randpm1()/2;
  /* Assume linear wavelength distribution */
    lambda = lambda0+dlambda*randpm1();
    if (lambda <= 0) ABSORB;
    v = K2V*(2*PI/lambda);

    if (!focus_ah && !focus_aw) {
      randvec_target_rect_real(&xf, &yf, &rf, &pdir,
       0, 0, dist, focus_xw, focus_yh, ROT_A_CURRENT_COMP, x, y, z, 2);

      dx = xf-x;
      dy = yf-y;
      rf = sqrt(dx*dx+dy*dy+dist*dist);

      vz=v*dist/rf;
      vy=v*dy/rf;
      vx=v*dx/rf;
    } else {

      randvec_target_rect_angular(&vx, &vy, &vz, &pdir,
          0, 0, 1, focus_aw*DEG2RAD, focus_ah*DEG2RAD, ROT_A_CURRENT_COMP);
      dx = vx; dy = vy; /* from unit vector */
      vx *= v; vy *= v; vz *= v;
    }
    p = p_in*pdir;

    /* spectral dependency from files or Maxwellians */
    if (flux_file && strlen(flux_file) && strcmp(flux_file,"NULL") && strcmp(flux_file,"0"))
    {
       double xwidth=Table_Value(pTable, lambda, 1);
       if (flux_file_log) xwidth=exp(xwidth);
       p *= xwidth;
    }
    else if (T1 > 0 && I1 > 0)
    {
      Maxwell = I1 * SG_Maxwell(lambda, T1);;  /* 1/AA */

      if ((T2 > 0) && (I2 > 0))
      {
        Maxwell += I2 * SG_Maxwell(lambda, T2);
      }
      if ((T3 > 0) && (I3 > 0))
      {
        Maxwell += I3 * SG_Maxwell(lambda, T3);;
      }
      p *= Maxwell;
    }

    /* optional x-xdiv and y-ydiv weightening: position=along columns, div=along rows */
    if (xdiv_file && strlen(xdiv_file)
      && strcmp(xdiv_file,"NULL") && strcmp(xdiv_file,"0") && pTable_xsum > 0) {
      double i,j;
      j = (x-            pTable_xmin) /(pTable_xmax -pTable_xmin) *pTable_x.columns;
      i = (atan2(dx,rf)*RAD2DEG-pTable_dxmin)/(pTable_dxmax-pTable_dxmin)*pTable_x.rows;
      r = Table_Value2d(pTable_x, i,j); /* row, column */
      p *= r/pTable_xsum;
    }
    if (ydiv_file && strlen(ydiv_file)
       && strcmp(ydiv_file,"NULL") && strcmp(ydiv_file,"0") && pTable_ysum > 0) {
      double i,j;
      j = (y-            pTable_ymin) /(pTable_ymax -pTable_ymin) *pTable_y.columns;
      i = (atan2(dy,rf)*RAD2DEG-  pTable_dymin)/(pTable_dymax-pTable_dymin)*pTable_y.rows;
      r = Table_Value2d(pTable_y, i,j);
      p *= r/pTable_ysum;
    }
    SCATTER;
  }
}
#line 16280 "./ThALES_resolution_v2.c"
}   /* End of HCS=Source_gen() SETTING parameter declarations. */
#undef pTable_dymax
#undef pTable_dymin
#undef pTable_dxmax
#undef pTable_dxmin
#undef pTable_ysum
#undef pTable_ymax
#undef pTable_ymin
#undef pTable_xsum
#undef pTable_xmax
#undef pTable_xmin
#undef pTable_y
#undef pTable_x
#undef pTable
#undef lambda3
#undef lambda2
#undef lambda1
#undef p_in
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompHCS:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(2,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H5 [3] */
  mccoordschange(mcposrH5, mcrotrH5,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H5 (without coords transformations) */
  mcJumpTrace_H5:
  SIG_MESSAGE("H5 (Trace)");
  mcDEBUG_COMP("H5")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH5
  STORE_NEUTRON(3,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[3]++;
  mcPCounter[3] += p;
  mcP2Counter[3] += p*p;
#define mccompcurname  H5
#define mccompcurtype  Arm
#define mccompcurindex 3
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH5:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(3,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H5_rect [4] */
  mccoordschange(mcposrH5_rect, mcrotrH5_rect,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H5_rect (without coords transformations) */
  mcJumpTrace_H5_rect:
  SIG_MESSAGE("H5_rect (Trace)");
  mcDEBUG_COMP("H5_rect")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH5_rect
  STORE_NEUTRON(4,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[4]++;
  mcPCounter[4] += p;
  mcP2Counter[4] += p*p;
#define mccompcurname  H5_rect
#define mccompcurtype  Guide_gravity
#define mccompcurindex 4
#define GVars mccH5_rect_GVars
#define pTable mccH5_rect_pTable
{   /* Declarations of H5_rect=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH5_rect_w1;
MCNUM h1 = mccH5_rect_h1;
MCNUM w2 = mccH5_rect_w2;
MCNUM h2 = mccH5_rect_h2;
MCNUM l = mccH5_rect_l;
MCNUM R0 = mccH5_rect_R0;
MCNUM Qc = mccH5_rect_Qc;
MCNUM alpha = mccH5_rect_alpha;
MCNUM m = mccH5_rect_m;
MCNUM W = mccH5_rect_W;
MCNUM nslit = mccH5_rect_nslit;
MCNUM d = mccH5_rect_d;
MCNUM mleft = mccH5_rect_mleft;
MCNUM mright = mccH5_rect_mright;
MCNUM mtop = mccH5_rect_mtop;
MCNUM mbottom = mccH5_rect_mbottom;
MCNUM nhslit = mccH5_rect_nhslit;
MCNUM G = mccH5_rect_G;
MCNUM aleft = mccH5_rect_aleft;
MCNUM aright = mccH5_rect_aright;
MCNUM atop = mccH5_rect_atop;
MCNUM abottom = mccH5_rect_abottom;
MCNUM wavy = mccH5_rect_wavy;
MCNUM wavy_z = mccH5_rect_wavy_z;
MCNUM wavy_tb = mccH5_rect_wavy_tb;
MCNUM wavy_lr = mccH5_rect_wavy_lr;
MCNUM chamfers = mccH5_rect_chamfers;
MCNUM chamfers_z = mccH5_rect_chamfers_z;
MCNUM chamfers_lr = mccH5_rect_chamfers_lr;
MCNUM chamfers_tb = mccH5_rect_chamfers_tb;
MCNUM nelements = mccH5_rect_nelements;
MCNUM nu = mccH5_rect_nu;
MCNUM phase = mccH5_rect_phase;
char* reflect = mccH5_rect_reflect;
#line 392 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  if (l > 0 && nelements > 0) {
    double B, C, dt;
    int    ret, bounces = 0, i=0;
    double this_width, this_height;
    double angle=0;

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      double dt=(-z+l/2)/vz; /* time shift to each center of slit package */
      angle=fmod(360*GVars.fc_freq*(t+dt)+GVars.fc_phase, 360); /* in deg */
      /* modify angle so that Z0 guide side is always in front of incoming neutron */
      if (angle > 90 && angle < 270) { angle -= 180; }
      angle *= DEG2RAD;
      rot_set_rotation(R, 0, -angle, 0); /* will rotate neutron instead of comp: negative side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

    for (i=0; i<7; GVars.N_reflection[i++] = 0);

    /* propagate to box input (with gravitation) in comp local coords */
    /* A = 0.5 n.g; B = n.v; C = n.(r-W); */
    /* 0=Z0 side: n=(0, 0, -l) ; W = (0, 0, 0) (at z=0, guide input)*/
    B = -l*vz; C = -l*z;

    ret = solve_2nd_order(&dt, NULL, GVars.A[0], B, C);
    if (ret==0) ABSORB;

    if (dt>0.0) PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz); else if (angle) ABSORB;
    GVars.N_reflection[6]++;

    this_width  = w1;
    this_height = h1;

  /* check if we are in the box input, else absorb */
    if (fabs(x) > this_width/2 || fabs(y) > this_height/2)
      ABSORB;
    else
    {
      double w_edge, w_adj; /* Channel displacement on X */
      double h_edge, h_adj; /* Channel displacement on Y */
      double w_chnum,h_chnum; /* channel indexes */

      SCATTER;

      /* X: Shift origin to center of channel hit (absorb if hit dividing walls) */
      x += w1/2.0;
      w_chnum = floor(x/(GVars.w1c+d));  /* 0= right side, nslit+1=left side  */
      w_edge  = w_chnum*(GVars.w1c+d);
      if(x - w_edge > GVars.w1c)
      {
        x -= w1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      w_adj = w_edge + (GVars.w1c)/2.0;
      x -= w_adj; w_adj -=  w1/2.0;

      /* Y: Shift origin to center of channel hit (absorb if hit dividing walls) */
      y += h1/2.0;
      h_chnum = floor(y/(GVars.h1c+d));  /* 0= lower side, nslit+1=upper side  */
      h_edge  = h_chnum*(GVars.h1c+d);
      if(y - h_edge > GVars.h1c)
      {
        y -= h1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      h_adj = h_edge + (GVars.h1c)/2.0;
      y -= h_adj; h_adj -=  h1/2.0;

      /* neutron is now in the input window of the guide */
      /* do loops on reflections in the box */
      for(;;)
      {
        /* get intersections for all box sides */
        double q, nx,ny,nz;
        double this_length;
        int side=0;

        bounces++;
        /* now look for intersection with guide sides and exit */
        side = Gravity_guide_Trace(&dt, &GVars, x, y, z,
            vx, vy, vz, w_chnum, nslit, h_chnum, nhslit,
            &nx, &ny, &nz);

        /* only positive dt are valid */
        /* exit reflection loops if no intersection (neutron is after box) */
        if (side == 0 || dt <= 0)
          { if (GVars.warnings < 100)
              fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
            GVars.warnings++;
            x += w_adj; y += h_adj; ABSORB; } /* should never occur */

        /* propagate to dt */
        PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz);

        /* do reflection on speed for l/r/u/d sides */
        if (side == 5) /* neutron reaches end of guide: end loop and exit comp */
          { GVars.N_reflection[side]++; x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj; break; }
        /* else reflection on a guide wall */
        if(GVars.M[side] == 0 || Qc == 0 || R0 == 0)  /* walls are absorbing */
          { x += w_adj; y += h_adj; ABSORB; }
        /* handle chamfers */
        this_width = w1+(w2-w1)*z/l;
        this_height= h1+(h2-h1)*z/l;
        this_length= fmod(z, l/nelements);
        /* absorb on input/output of element parts */
        if (GVars.chamfer_z && (this_length<GVars.chamfer_z || this_length>l/nelements-GVars.chamfer_z))
        { x += w_adj; y += h_adj; ABSORB; }
        /* absorb on l/r/t/b sides */
        if (GVars.chamfer_lr && (side==1 || side==2) && (fabs(y+h_adj)>this_height/2-GVars.chamfer_lr))
        { x += w_adj; y += h_adj; ABSORB; }
        if (GVars.chamfer_tb && (side==3 || side==4) && (fabs(x+w_adj)>this_width/2- GVars.chamfer_tb))
        { x += w_adj; y += h_adj; ABSORB; }
        /* change/mirror velocity: h_f = v - n.2*n.v/|n|^2 */
        GVars.N_reflection[side]++; /* GVars.norm_n2 > 0 was checked at INIT */
        /* compute n.v using current values */
        B = scalar_prod(vx,vy,vz,nx,ny,nz);
        dt = 2*B/GVars.norm_n2[side]; /* 2*n.v/|n|^2 */
        vx -= nx*dt;
        vy -= ny*dt;
        vz -= nz*dt;

        /* compute q and modify neutron weight */
        /* scattering q=|n_i-n_f| = V2Q*|vf - v| = V2Q*2*n.v/|n| */
        q = 2*V2Q*fabs(B)/GVars.norm_n[side];

        if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
          TableReflecFunc(q, &pTable, &B);
        else {
          double par[] = {R0, Qc, GVars.Alpha[side], GVars.M[side], W};
          StdReflecFunc(q, par, &B);
        }
        if (B <= 0) { x += w_adj; y += h_adj; ABSORB; }
        else p *= B;
        x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj;
        GVars.N_reflection[0]++;
        /* go to the next reflection */
        if (bounces > 1000) ABSORB;
      } /* end for */
      x += w_adj; y += h_adj; /* Re-adjust origin after SCATTER */
    }

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate back neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      rot_set_rotation(R, 0, angle, 0); /* will rotate back neutron: positive side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

  } /* if l */
}
#line 16711 "./ThALES_resolution_v2.c"
}   /* End of H5_rect=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH5_rect:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(4,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_origin [5] */
  mccoordschange(mcposrH53_origin, mcrotrH53_origin,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_origin (without coords transformations) */
  mcJumpTrace_H53_origin:
  SIG_MESSAGE("H53_origin (Trace)");
  mcDEBUG_COMP("H53_origin")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_origin
  STORE_NEUTRON(5,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[5]++;
  mcPCounter[5] += p;
  mcP2Counter[5] += p*p;
#define mccompcurname  H53_origin
#define mccompcurtype  Arm
#define mccompcurindex 5
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_origin:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(5,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_start [6] */
  mccoordschange(mcposrH53_start, mcrotrH53_start,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_start (without coords transformations) */
  mcJumpTrace_H53_start:
  SIG_MESSAGE("H53_start (Trace)");
  mcDEBUG_COMP("H53_start")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_start
  STORE_NEUTRON(6,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[6]++;
  mcPCounter[6] += p;
  mcP2Counter[6] += p*p;
#define mccompcurname  H53_start
#define mccompcurtype  Arm
#define mccompcurindex 6
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_start:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(6,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_inpile [7] */
  mccoordschange(mcposrH53_inpile, mcrotrH53_inpile,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_inpile (without coords transformations) */
  mcJumpTrace_H53_inpile:
  SIG_MESSAGE("H53_inpile (Trace)");
  mcDEBUG_COMP("H53_inpile")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_inpile
  STORE_NEUTRON(7,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[7]++;
  mcPCounter[7] += p;
  mcP2Counter[7] += p*p;
#define mccompcurname  H53_inpile
#define mccompcurtype  Guide_gravity
#define mccompcurindex 7
#define GVars mccH53_inpile_GVars
#define pTable mccH53_inpile_pTable
{   /* Declarations of H53_inpile=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_inpile_w1;
MCNUM h1 = mccH53_inpile_h1;
MCNUM w2 = mccH53_inpile_w2;
MCNUM h2 = mccH53_inpile_h2;
MCNUM l = mccH53_inpile_l;
MCNUM R0 = mccH53_inpile_R0;
MCNUM Qc = mccH53_inpile_Qc;
MCNUM alpha = mccH53_inpile_alpha;
MCNUM m = mccH53_inpile_m;
MCNUM W = mccH53_inpile_W;
MCNUM nslit = mccH53_inpile_nslit;
MCNUM d = mccH53_inpile_d;
MCNUM mleft = mccH53_inpile_mleft;
MCNUM mright = mccH53_inpile_mright;
MCNUM mtop = mccH53_inpile_mtop;
MCNUM mbottom = mccH53_inpile_mbottom;
MCNUM nhslit = mccH53_inpile_nhslit;
MCNUM G = mccH53_inpile_G;
MCNUM aleft = mccH53_inpile_aleft;
MCNUM aright = mccH53_inpile_aright;
MCNUM atop = mccH53_inpile_atop;
MCNUM abottom = mccH53_inpile_abottom;
MCNUM wavy = mccH53_inpile_wavy;
MCNUM wavy_z = mccH53_inpile_wavy_z;
MCNUM wavy_tb = mccH53_inpile_wavy_tb;
MCNUM wavy_lr = mccH53_inpile_wavy_lr;
MCNUM chamfers = mccH53_inpile_chamfers;
MCNUM chamfers_z = mccH53_inpile_chamfers_z;
MCNUM chamfers_lr = mccH53_inpile_chamfers_lr;
MCNUM chamfers_tb = mccH53_inpile_chamfers_tb;
MCNUM nelements = mccH53_inpile_nelements;
MCNUM nu = mccH53_inpile_nu;
MCNUM phase = mccH53_inpile_phase;
char* reflect = mccH53_inpile_reflect;
#line 392 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  if (l > 0 && nelements > 0) {
    double B, C, dt;
    int    ret, bounces = 0, i=0;
    double this_width, this_height;
    double angle=0;

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      double dt=(-z+l/2)/vz; /* time shift to each center of slit package */
      angle=fmod(360*GVars.fc_freq*(t+dt)+GVars.fc_phase, 360); /* in deg */
      /* modify angle so that Z0 guide side is always in front of incoming neutron */
      if (angle > 90 && angle < 270) { angle -= 180; }
      angle *= DEG2RAD;
      rot_set_rotation(R, 0, -angle, 0); /* will rotate neutron instead of comp: negative side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

    for (i=0; i<7; GVars.N_reflection[i++] = 0);

    /* propagate to box input (with gravitation) in comp local coords */
    /* A = 0.5 n.g; B = n.v; C = n.(r-W); */
    /* 0=Z0 side: n=(0, 0, -l) ; W = (0, 0, 0) (at z=0, guide input)*/
    B = -l*vz; C = -l*z;

    ret = solve_2nd_order(&dt, NULL, GVars.A[0], B, C);
    if (ret==0) ABSORB;

    if (dt>0.0) PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz); else if (angle) ABSORB;
    GVars.N_reflection[6]++;

    this_width  = w1;
    this_height = h1;

  /* check if we are in the box input, else absorb */
    if (fabs(x) > this_width/2 || fabs(y) > this_height/2)
      ABSORB;
    else
    {
      double w_edge, w_adj; /* Channel displacement on X */
      double h_edge, h_adj; /* Channel displacement on Y */
      double w_chnum,h_chnum; /* channel indexes */

      SCATTER;

      /* X: Shift origin to center of channel hit (absorb if hit dividing walls) */
      x += w1/2.0;
      w_chnum = floor(x/(GVars.w1c+d));  /* 0= right side, nslit+1=left side  */
      w_edge  = w_chnum*(GVars.w1c+d);
      if(x - w_edge > GVars.w1c)
      {
        x -= w1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      w_adj = w_edge + (GVars.w1c)/2.0;
      x -= w_adj; w_adj -=  w1/2.0;

      /* Y: Shift origin to center of channel hit (absorb if hit dividing walls) */
      y += h1/2.0;
      h_chnum = floor(y/(GVars.h1c+d));  /* 0= lower side, nslit+1=upper side  */
      h_edge  = h_chnum*(GVars.h1c+d);
      if(y - h_edge > GVars.h1c)
      {
        y -= h1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      h_adj = h_edge + (GVars.h1c)/2.0;
      y -= h_adj; h_adj -=  h1/2.0;

      /* neutron is now in the input window of the guide */
      /* do loops on reflections in the box */
      for(;;)
      {
        /* get intersections for all box sides */
        double q, nx,ny,nz;
        double this_length;
        int side=0;

        bounces++;
        /* now look for intersection with guide sides and exit */
        side = Gravity_guide_Trace(&dt, &GVars, x, y, z,
            vx, vy, vz, w_chnum, nslit, h_chnum, nhslit,
            &nx, &ny, &nz);

        /* only positive dt are valid */
        /* exit reflection loops if no intersection (neutron is after box) */
        if (side == 0 || dt <= 0)
          { if (GVars.warnings < 100)
              fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
            GVars.warnings++;
            x += w_adj; y += h_adj; ABSORB; } /* should never occur */

        /* propagate to dt */
        PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz);

        /* do reflection on speed for l/r/u/d sides */
        if (side == 5) /* neutron reaches end of guide: end loop and exit comp */
          { GVars.N_reflection[side]++; x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj; break; }
        /* else reflection on a guide wall */
        if(GVars.M[side] == 0 || Qc == 0 || R0 == 0)  /* walls are absorbing */
          { x += w_adj; y += h_adj; ABSORB; }
        /* handle chamfers */
        this_width = w1+(w2-w1)*z/l;
        this_height= h1+(h2-h1)*z/l;
        this_length= fmod(z, l/nelements);
        /* absorb on input/output of element parts */
        if (GVars.chamfer_z && (this_length<GVars.chamfer_z || this_length>l/nelements-GVars.chamfer_z))
        { x += w_adj; y += h_adj; ABSORB; }
        /* absorb on l/r/t/b sides */
        if (GVars.chamfer_lr && (side==1 || side==2) && (fabs(y+h_adj)>this_height/2-GVars.chamfer_lr))
        { x += w_adj; y += h_adj; ABSORB; }
        if (GVars.chamfer_tb && (side==3 || side==4) && (fabs(x+w_adj)>this_width/2- GVars.chamfer_tb))
        { x += w_adj; y += h_adj; ABSORB; }
        /* change/mirror velocity: h_f = v - n.2*n.v/|n|^2 */
        GVars.N_reflection[side]++; /* GVars.norm_n2 > 0 was checked at INIT */
        /* compute n.v using current values */
        B = scalar_prod(vx,vy,vz,nx,ny,nz);
        dt = 2*B/GVars.norm_n2[side]; /* 2*n.v/|n|^2 */
        vx -= nx*dt;
        vy -= ny*dt;
        vz -= nz*dt;

        /* compute q and modify neutron weight */
        /* scattering q=|n_i-n_f| = V2Q*|vf - v| = V2Q*2*n.v/|n| */
        q = 2*V2Q*fabs(B)/GVars.norm_n[side];

        if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
          TableReflecFunc(q, &pTable, &B);
        else {
          double par[] = {R0, Qc, GVars.Alpha[side], GVars.M[side], W};
          StdReflecFunc(q, par, &B);
        }
        if (B <= 0) { x += w_adj; y += h_adj; ABSORB; }
        else p *= B;
        x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj;
        GVars.N_reflection[0]++;
        /* go to the next reflection */
        if (bounces > 1000) ABSORB;
      } /* end for */
      x += w_adj; y += h_adj; /* Re-adjust origin after SCATTER */
    }

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate back neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      rot_set_rotation(R, 0, angle, 0); /* will rotate back neutron: positive side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

  } /* if l */
}
#line 17230 "./ThALES_resolution_v2.c"
}   /* End of H53_inpile=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_inpile:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(7,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_Obt [8] */
  mccoordschange(mcposrH53_Obt, mcrotrH53_Obt,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_Obt (without coords transformations) */
  mcJumpTrace_H53_Obt:
  SIG_MESSAGE("H53_Obt (Trace)");
  mcDEBUG_COMP("H53_Obt")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_Obt
  STORE_NEUTRON(8,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[8]++;
  mcPCounter[8] += p;
  mcP2Counter[8] += p*p;
#define mccompcurname  H53_Obt
#define mccompcurtype  Guide_gravity
#define mccompcurindex 8
#define GVars mccH53_Obt_GVars
#define pTable mccH53_Obt_pTable
{   /* Declarations of H53_Obt=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_Obt_w1;
MCNUM h1 = mccH53_Obt_h1;
MCNUM w2 = mccH53_Obt_w2;
MCNUM h2 = mccH53_Obt_h2;
MCNUM l = mccH53_Obt_l;
MCNUM R0 = mccH53_Obt_R0;
MCNUM Qc = mccH53_Obt_Qc;
MCNUM alpha = mccH53_Obt_alpha;
MCNUM m = mccH53_Obt_m;
MCNUM W = mccH53_Obt_W;
MCNUM nslit = mccH53_Obt_nslit;
MCNUM d = mccH53_Obt_d;
MCNUM mleft = mccH53_Obt_mleft;
MCNUM mright = mccH53_Obt_mright;
MCNUM mtop = mccH53_Obt_mtop;
MCNUM mbottom = mccH53_Obt_mbottom;
MCNUM nhslit = mccH53_Obt_nhslit;
MCNUM G = mccH53_Obt_G;
MCNUM aleft = mccH53_Obt_aleft;
MCNUM aright = mccH53_Obt_aright;
MCNUM atop = mccH53_Obt_atop;
MCNUM abottom = mccH53_Obt_abottom;
MCNUM wavy = mccH53_Obt_wavy;
MCNUM wavy_z = mccH53_Obt_wavy_z;
MCNUM wavy_tb = mccH53_Obt_wavy_tb;
MCNUM wavy_lr = mccH53_Obt_wavy_lr;
MCNUM chamfers = mccH53_Obt_chamfers;
MCNUM chamfers_z = mccH53_Obt_chamfers_z;
MCNUM chamfers_lr = mccH53_Obt_chamfers_lr;
MCNUM chamfers_tb = mccH53_Obt_chamfers_tb;
MCNUM nelements = mccH53_Obt_nelements;
MCNUM nu = mccH53_Obt_nu;
MCNUM phase = mccH53_Obt_phase;
char* reflect = mccH53_Obt_reflect;
#line 392 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  if (l > 0 && nelements > 0) {
    double B, C, dt;
    int    ret, bounces = 0, i=0;
    double this_width, this_height;
    double angle=0;

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      double dt=(-z+l/2)/vz; /* time shift to each center of slit package */
      angle=fmod(360*GVars.fc_freq*(t+dt)+GVars.fc_phase, 360); /* in deg */
      /* modify angle so that Z0 guide side is always in front of incoming neutron */
      if (angle > 90 && angle < 270) { angle -= 180; }
      angle *= DEG2RAD;
      rot_set_rotation(R, 0, -angle, 0); /* will rotate neutron instead of comp: negative side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

    for (i=0; i<7; GVars.N_reflection[i++] = 0);

    /* propagate to box input (with gravitation) in comp local coords */
    /* A = 0.5 n.g; B = n.v; C = n.(r-W); */
    /* 0=Z0 side: n=(0, 0, -l) ; W = (0, 0, 0) (at z=0, guide input)*/
    B = -l*vz; C = -l*z;

    ret = solve_2nd_order(&dt, NULL, GVars.A[0], B, C);
    if (ret==0) ABSORB;

    if (dt>0.0) PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz); else if (angle) ABSORB;
    GVars.N_reflection[6]++;

    this_width  = w1;
    this_height = h1;

  /* check if we are in the box input, else absorb */
    if (fabs(x) > this_width/2 || fabs(y) > this_height/2)
      ABSORB;
    else
    {
      double w_edge, w_adj; /* Channel displacement on X */
      double h_edge, h_adj; /* Channel displacement on Y */
      double w_chnum,h_chnum; /* channel indexes */

      SCATTER;

      /* X: Shift origin to center of channel hit (absorb if hit dividing walls) */
      x += w1/2.0;
      w_chnum = floor(x/(GVars.w1c+d));  /* 0= right side, nslit+1=left side  */
      w_edge  = w_chnum*(GVars.w1c+d);
      if(x - w_edge > GVars.w1c)
      {
        x -= w1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      w_adj = w_edge + (GVars.w1c)/2.0;
      x -= w_adj; w_adj -=  w1/2.0;

      /* Y: Shift origin to center of channel hit (absorb if hit dividing walls) */
      y += h1/2.0;
      h_chnum = floor(y/(GVars.h1c+d));  /* 0= lower side, nslit+1=upper side  */
      h_edge  = h_chnum*(GVars.h1c+d);
      if(y - h_edge > GVars.h1c)
      {
        y -= h1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      h_adj = h_edge + (GVars.h1c)/2.0;
      y -= h_adj; h_adj -=  h1/2.0;

      /* neutron is now in the input window of the guide */
      /* do loops on reflections in the box */
      for(;;)
      {
        /* get intersections for all box sides */
        double q, nx,ny,nz;
        double this_length;
        int side=0;

        bounces++;
        /* now look for intersection with guide sides and exit */
        side = Gravity_guide_Trace(&dt, &GVars, x, y, z,
            vx, vy, vz, w_chnum, nslit, h_chnum, nhslit,
            &nx, &ny, &nz);

        /* only positive dt are valid */
        /* exit reflection loops if no intersection (neutron is after box) */
        if (side == 0 || dt <= 0)
          { if (GVars.warnings < 100)
              fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
            GVars.warnings++;
            x += w_adj; y += h_adj; ABSORB; } /* should never occur */

        /* propagate to dt */
        PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz);

        /* do reflection on speed for l/r/u/d sides */
        if (side == 5) /* neutron reaches end of guide: end loop and exit comp */
          { GVars.N_reflection[side]++; x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj; break; }
        /* else reflection on a guide wall */
        if(GVars.M[side] == 0 || Qc == 0 || R0 == 0)  /* walls are absorbing */
          { x += w_adj; y += h_adj; ABSORB; }
        /* handle chamfers */
        this_width = w1+(w2-w1)*z/l;
        this_height= h1+(h2-h1)*z/l;
        this_length= fmod(z, l/nelements);
        /* absorb on input/output of element parts */
        if (GVars.chamfer_z && (this_length<GVars.chamfer_z || this_length>l/nelements-GVars.chamfer_z))
        { x += w_adj; y += h_adj; ABSORB; }
        /* absorb on l/r/t/b sides */
        if (GVars.chamfer_lr && (side==1 || side==2) && (fabs(y+h_adj)>this_height/2-GVars.chamfer_lr))
        { x += w_adj; y += h_adj; ABSORB; }
        if (GVars.chamfer_tb && (side==3 || side==4) && (fabs(x+w_adj)>this_width/2- GVars.chamfer_tb))
        { x += w_adj; y += h_adj; ABSORB; }
        /* change/mirror velocity: h_f = v - n.2*n.v/|n|^2 */
        GVars.N_reflection[side]++; /* GVars.norm_n2 > 0 was checked at INIT */
        /* compute n.v using current values */
        B = scalar_prod(vx,vy,vz,nx,ny,nz);
        dt = 2*B/GVars.norm_n2[side]; /* 2*n.v/|n|^2 */
        vx -= nx*dt;
        vy -= ny*dt;
        vz -= nz*dt;

        /* compute q and modify neutron weight */
        /* scattering q=|n_i-n_f| = V2Q*|vf - v| = V2Q*2*n.v/|n| */
        q = 2*V2Q*fabs(B)/GVars.norm_n[side];

        if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
          TableReflecFunc(q, &pTable, &B);
        else {
          double par[] = {R0, Qc, GVars.Alpha[side], GVars.M[side], W};
          StdReflecFunc(q, par, &B);
        }
        if (B <= 0) { x += w_adj; y += h_adj; ABSORB; }
        else p *= B;
        x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj;
        GVars.N_reflection[0]++;
        /* go to the next reflection */
        if (bounces > 1000) ABSORB;
      } /* end for */
      x += w_adj; y += h_adj; /* Re-adjust origin after SCATTER */
    }

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate back neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      rot_set_rotation(R, 0, angle, 0); /* will rotate back neutron: positive side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

  } /* if l */
}
#line 17543 "./ThALES_resolution_v2.c"
}   /* End of H53_Obt=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_Obt:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(8,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_Obt_Out [9] */
  mccoordschange(mcposrH53_Obt_Out, mcrotrH53_Obt_Out,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_Obt_Out (without coords transformations) */
  mcJumpTrace_H53_Obt_Out:
  SIG_MESSAGE("H53_Obt_Out (Trace)");
  mcDEBUG_COMP("H53_Obt_Out")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_Obt_Out
  STORE_NEUTRON(9,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[9]++;
  mcPCounter[9] += p;
  mcP2Counter[9] += p*p;
#define mccompcurname  H53_Obt_Out
#define mccompcurtype  Arm
#define mccompcurindex 9
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_Obt_Out:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(9,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_VSComC1 [10] */
  mccoordschange(mcposrH53_VSComC1, mcrotrH53_VSComC1,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_VSComC1 (without coords transformations) */
  mcJumpTrace_H53_VSComC1:
  SIG_MESSAGE("H53_VSComC1 (Trace)");
  mcDEBUG_COMP("H53_VSComC1")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_VSComC1
  STORE_NEUTRON(10,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[10]++;
  mcPCounter[10] += p;
  mcP2Counter[10] += p*p;
#define mccompcurname  H53_VSComC1
#define mccompcurtype  Guide_gravity
#define mccompcurindex 10
#define GVars mccH53_VSComC1_GVars
#define pTable mccH53_VSComC1_pTable
{   /* Declarations of H53_VSComC1=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_VSComC1_w1;
MCNUM h1 = mccH53_VSComC1_h1;
MCNUM w2 = mccH53_VSComC1_w2;
MCNUM h2 = mccH53_VSComC1_h2;
MCNUM l = mccH53_VSComC1_l;
MCNUM R0 = mccH53_VSComC1_R0;
MCNUM Qc = mccH53_VSComC1_Qc;
MCNUM alpha = mccH53_VSComC1_alpha;
MCNUM m = mccH53_VSComC1_m;
MCNUM W = mccH53_VSComC1_W;
MCNUM nslit = mccH53_VSComC1_nslit;
MCNUM d = mccH53_VSComC1_d;
MCNUM mleft = mccH53_VSComC1_mleft;
MCNUM mright = mccH53_VSComC1_mright;
MCNUM mtop = mccH53_VSComC1_mtop;
MCNUM mbottom = mccH53_VSComC1_mbottom;
MCNUM nhslit = mccH53_VSComC1_nhslit;
MCNUM G = mccH53_VSComC1_G;
MCNUM aleft = mccH53_VSComC1_aleft;
MCNUM aright = mccH53_VSComC1_aright;
MCNUM atop = mccH53_VSComC1_atop;
MCNUM abottom = mccH53_VSComC1_abottom;
MCNUM wavy = mccH53_VSComC1_wavy;
MCNUM wavy_z = mccH53_VSComC1_wavy_z;
MCNUM wavy_tb = mccH53_VSComC1_wavy_tb;
MCNUM wavy_lr = mccH53_VSComC1_wavy_lr;
MCNUM chamfers = mccH53_VSComC1_chamfers;
MCNUM chamfers_z = mccH53_VSComC1_chamfers_z;
MCNUM chamfers_lr = mccH53_VSComC1_chamfers_lr;
MCNUM chamfers_tb = mccH53_VSComC1_chamfers_tb;
MCNUM nelements = mccH53_VSComC1_nelements;
MCNUM nu = mccH53_VSComC1_nu;
MCNUM phase = mccH53_VSComC1_phase;
char* reflect = mccH53_VSComC1_reflect;
#line 392 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
  if (l > 0 && nelements > 0) {
    double B, C, dt;
    int    ret, bounces = 0, i=0;
    double this_width, this_height;
    double angle=0;

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      double dt=(-z+l/2)/vz; /* time shift to each center of slit package */
      angle=fmod(360*GVars.fc_freq*(t+dt)+GVars.fc_phase, 360); /* in deg */
      /* modify angle so that Z0 guide side is always in front of incoming neutron */
      if (angle > 90 && angle < 270) { angle -= 180; }
      angle *= DEG2RAD;
      rot_set_rotation(R, 0, -angle, 0); /* will rotate neutron instead of comp: negative side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

    for (i=0; i<7; GVars.N_reflection[i++] = 0);

    /* propagate to box input (with gravitation) in comp local coords */
    /* A = 0.5 n.g; B = n.v; C = n.(r-W); */
    /* 0=Z0 side: n=(0, 0, -l) ; W = (0, 0, 0) (at z=0, guide input)*/
    B = -l*vz; C = -l*z;

    ret = solve_2nd_order(&dt, NULL, GVars.A[0], B, C);
    if (ret==0) ABSORB;

    if (dt>0.0) PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz); else if (angle) ABSORB;
    GVars.N_reflection[6]++;

    this_width  = w1;
    this_height = h1;

  /* check if we are in the box input, else absorb */
    if (fabs(x) > this_width/2 || fabs(y) > this_height/2)
      ABSORB;
    else
    {
      double w_edge, w_adj; /* Channel displacement on X */
      double h_edge, h_adj; /* Channel displacement on Y */
      double w_chnum,h_chnum; /* channel indexes */

      SCATTER;

      /* X: Shift origin to center of channel hit (absorb if hit dividing walls) */
      x += w1/2.0;
      w_chnum = floor(x/(GVars.w1c+d));  /* 0= right side, nslit+1=left side  */
      w_edge  = w_chnum*(GVars.w1c+d);
      if(x - w_edge > GVars.w1c)
      {
        x -= w1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      w_adj = w_edge + (GVars.w1c)/2.0;
      x -= w_adj; w_adj -=  w1/2.0;

      /* Y: Shift origin to center of channel hit (absorb if hit dividing walls) */
      y += h1/2.0;
      h_chnum = floor(y/(GVars.h1c+d));  /* 0= lower side, nslit+1=upper side  */
      h_edge  = h_chnum*(GVars.h1c+d);
      if(y - h_edge > GVars.h1c)
      {
        y -= h1/2.0; /* Re-adjust origin */
        ABSORB;
      }
      h_adj = h_edge + (GVars.h1c)/2.0;
      y -= h_adj; h_adj -=  h1/2.0;

      /* neutron is now in the input window of the guide */
      /* do loops on reflections in the box */
      for(;;)
      {
        /* get intersections for all box sides */
        double q, nx,ny,nz;
        double this_length;
        int side=0;

        bounces++;
        /* now look for intersection with guide sides and exit */
        side = Gravity_guide_Trace(&dt, &GVars, x, y, z,
            vx, vy, vz, w_chnum, nslit, h_chnum, nhslit,
            &nx, &ny, &nz);

        /* only positive dt are valid */
        /* exit reflection loops if no intersection (neutron is after box) */
        if (side == 0 || dt <= 0)
          { if (GVars.warnings < 100)
              fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
            GVars.warnings++;
            x += w_adj; y += h_adj; ABSORB; } /* should never occur */

        /* propagate to dt */
        PROP_GRAV_DT(dt, GVars.gx, GVars.gy, GVars.gz);

        /* do reflection on speed for l/r/u/d sides */
        if (side == 5) /* neutron reaches end of guide: end loop and exit comp */
          { GVars.N_reflection[side]++; x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj; break; }
        /* else reflection on a guide wall */
        if(GVars.M[side] == 0 || Qc == 0 || R0 == 0)  /* walls are absorbing */
          { x += w_adj; y += h_adj; ABSORB; }
        /* handle chamfers */
        this_width = w1+(w2-w1)*z/l;
        this_height= h1+(h2-h1)*z/l;
        this_length= fmod(z, l/nelements);
        /* absorb on input/output of element parts */
        if (GVars.chamfer_z && (this_length<GVars.chamfer_z || this_length>l/nelements-GVars.chamfer_z))
        { x += w_adj; y += h_adj; ABSORB; }
        /* absorb on l/r/t/b sides */
        if (GVars.chamfer_lr && (side==1 || side==2) && (fabs(y+h_adj)>this_height/2-GVars.chamfer_lr))
        { x += w_adj; y += h_adj; ABSORB; }
        if (GVars.chamfer_tb && (side==3 || side==4) && (fabs(x+w_adj)>this_width/2- GVars.chamfer_tb))
        { x += w_adj; y += h_adj; ABSORB; }
        /* change/mirror velocity: h_f = v - n.2*n.v/|n|^2 */
        GVars.N_reflection[side]++; /* GVars.norm_n2 > 0 was checked at INIT */
        /* compute n.v using current values */
        B = scalar_prod(vx,vy,vz,nx,ny,nz);
        dt = 2*B/GVars.norm_n2[side]; /* 2*n.v/|n|^2 */
        vx -= nx*dt;
        vy -= ny*dt;
        vz -= nz*dt;

        /* compute q and modify neutron weight */
        /* scattering q=|n_i-n_f| = V2Q*|vf - v| = V2Q*2*n.v/|n| */
        q = 2*V2Q*fabs(B)/GVars.norm_n[side];

        if (reflect && strlen(reflect) && strcmp(reflect,"NULL") && strcmp(reflect,"0"))
          TableReflecFunc(q, &pTable, &B);
        else {
          double par[] = {R0, Qc, GVars.Alpha[side], GVars.M[side], W};
          StdReflecFunc(q, par, &B);
        }
        if (B <= 0) { x += w_adj; y += h_adj; ABSORB; }
        else p *= B;
        x += w_adj; y += h_adj; SCATTER; x -= w_adj; y -= h_adj;
        GVars.N_reflection[0]++;
        /* go to the next reflection */
        if (bounces > 1000) ABSORB;
      } /* end for */
      x += w_adj; y += h_adj; /* Re-adjust origin after SCATTER */
    }

    if (GVars.fc_freq != 0 || GVars.fc_phase != 0) { /* rotate back neutron w/r to guide element */
      /* approximation of rotating straight Fermi Chopper */
      Coords   X = coords_set(x,y,z-l/2);  /* current coordinates of neutron in centered static frame */
      Rotation R;
      rot_set_rotation(R, 0, angle, 0); /* will rotate back neutron: positive side */
      /* apply rotation to centered coordinates */
      Coords   RX = rot_apply(R, X);
      coords_get(RX, &x, &y, &z);
      z = z+l/2;
      /* rotate speed */
      X  = coords_set(vx,vy,vz);
      RX = rot_apply(R, X);
      coords_get(RX, &vx, &vy, &vz);
    }

  } /* if l */
}
#line 17959 "./ThALES_resolution_v2.c"
}   /* End of H53_VSComC1=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_VSComC1:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(10,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_Nose [11] */
  mccoordschange(mcposrH53_Nose, mcrotrH53_Nose,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_Nose (without coords transformations) */
  mcJumpTrace_H53_Nose:
  SIG_MESSAGE("H53_Nose (Trace)");
  mcDEBUG_COMP("H53_Nose")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_Nose
  STORE_NEUTRON(11,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[11]++;
  mcPCounter[11] += p;
  mcP2Counter[11] += p*p;
#define mccompcurname  H53_Nose
#define mccompcurtype  Guide_tapering
#define mccompcurindex 11
#define w1c mccH53_Nose_w1c
#define w2c mccH53_Nose_w2c
#define ww mccH53_Nose_ww
#define hh mccH53_Nose_hh
#define whalf mccH53_Nose_whalf
#define hhalf mccH53_Nose_hhalf
#define lwhalf mccH53_Nose_lwhalf
#define lhhalf mccH53_Nose_lhhalf
#define h1_in mccH53_Nose_h1_in
#define h2_out mccH53_Nose_h2_out
#define w1_in mccH53_Nose_w1_in
#define w2_out mccH53_Nose_w2_out
#define l_seg mccH53_Nose_l_seg
#define seg mccH53_Nose_seg
#define h12 mccH53_Nose_h12
#define h2 mccH53_Nose_h2
#define w12 mccH53_Nose_w12
#define w2 mccH53_Nose_w2
#define a_ell_q mccH53_Nose_a_ell_q
#define b_ell_q mccH53_Nose_b_ell_q
#define lbw mccH53_Nose_lbw
#define lbh mccH53_Nose_lbh
#define mxi mccH53_Nose_mxi
#define u1 mccH53_Nose_u1
#define u2 mccH53_Nose_u2
#define div1 mccH53_Nose_div1
#define p2_para mccH53_Nose_p2_para
#define test mccH53_Nose_test
#define Div1 mccH53_Nose_Div1
#define i mccH53_Nose_i
#define ii mccH53_Nose_ii
#define seg mccH53_Nose_seg
#define fu mccH53_Nose_fu
#define pos mccH53_Nose_pos
#define file_name mccH53_Nose_file_name
#define ep mccH53_Nose_ep
#define num mccH53_Nose_num
#define rotation_h mccH53_Nose_rotation_h
#define rotation_v mccH53_Nose_rotation_v
{   /* Declarations of H53_Nose=Guide_tapering() SETTING parameters. */
char* option = mccH53_Nose_option;
MCNUM w1 = mccH53_Nose_w1;
MCNUM h1 = mccH53_Nose_h1;
MCNUM l = mccH53_Nose_l;
MCNUM linw = mccH53_Nose_linw;
MCNUM loutw = mccH53_Nose_loutw;
MCNUM linh = mccH53_Nose_linh;
MCNUM louth = mccH53_Nose_louth;
MCNUM R0 = mccH53_Nose_R0;
MCNUM Qcx = mccH53_Nose_Qcx;
MCNUM Qcy = mccH53_Nose_Qcy;
MCNUM alphax = mccH53_Nose_alphax;
MCNUM alphay = mccH53_Nose_alphay;
MCNUM W = mccH53_Nose_W;
MCNUM mx = mccH53_Nose_mx;
MCNUM my = mccH53_Nose_my;
MCNUM segno = mccH53_Nose_segno;
MCNUM curvature = mccH53_Nose_curvature;
MCNUM curvature_v = mccH53_Nose_curvature_v;
#line 453 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"
{
  double t1,t2,ts,zr;                           /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */
  double sz=0;
  int ii;
  Coords mctc1,mctc2;
  Rotation mctr1;

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  for (ii=0;ii<seg;ii++)
  {
    zr=ii*l_seg;
    /* Propagate neutron to segment entrance. */
    ts=(zr-z)/vz;
    PROP_DT(ts);
    if(x <= w1_in[ii]/-2.0 || x >= w1_in[ii]/2.0 || y <= -hhalf[ii] || y >= hhalf[ii])
      ABSORB;
    /* Shift origin to center of channel hit (absorb if hit dividing walls) */
    x += w1_in[ii]/2.0;
    edge = floor(x/w1c[ii])*w1c[ii];
    if(x - edge > w1c[ii])
    {
      x -= w1_in[ii]/2.0; /* Re-adjust origin */
      ABSORB;
    }
    x -= (edge + (w1c[ii]/2.0));
    hadj = edge + (w1c[ii]/2.0) - w1_in[ii]/2.0;
    for(;;)
    {
      /* Compute the dot products of v and n for the four mirrors. */
      ts=(zr-z)/vz;
      av = l_seg*vx; bv = ww[ii]*vz;
      ah = l_seg*vy; bh = hh[ii]*vz;
      vdotn_v1 = bv + av;         /* Left vertical */
      vdotn_v2 = bv - av;         /* Right vertical */
      vdotn_h1 = bh + ah;         /* Lower horizontal */
      vdotn_h2 = bh - ah;         /* Upper horizontal */
      /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
      cv1 = -whalf[ii]*l_seg - (z-zr)*ww[ii]; cv2 = x*l_seg;
      ch1 = -hhalf[ii]*l_seg - (z-zr)*hh[ii]; ch2 = y*l_seg;
      /* Compute intersection times. */
      t1 = (zr + l_seg - z)/vz;
      i = 0;
      if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
      {
        t1 = t2;
        i = 1;
      }
      if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
      {
        t1 = t2;
        i = 2;
      }
      if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
      {
        t1 = t2;
        i = 3;
      }
      if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
      {
        t1 = t2;
        i = 4;
      }
      if(i == 0)
      {
        break;                    /* Neutron left guide. */
      }
      PROP_DT(t1);
      switch(i)
      {
        case 1:                   /* Left vertical mirror */
          nlen2 = l_seg*l_seg + ww[ii]*ww[ii];
          q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
          dd = 2*vdotn_v1/nlen2;
          vx = vx - dd*l_seg;
          vz = vz - dd*ww[ii];
          break;
        case 2:                   /* Right vertical mirror */
          nlen2 = l_seg*l_seg + ww[ii]*ww[ii];
          q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
          dd = 2*vdotn_v2/nlen2;
          vx = vx + dd*l_seg;
          vz = vz - dd*ww[ii];
          break;
        case 3:                   /* Lower horizontal mirror */
          nlen2 = l_seg*l_seg + hh[ii]*hh[ii];
          q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
          dd = 2*vdotn_h1/nlen2;
          vy = vy - dd*l_seg;
          vz = vz - dd*hh[ii];
          break;
        case 4:                   /* Upper horizontal mirror */
          nlen2 = l_seg*l_seg + hh[ii]*hh[ii];
          q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
          dd = 2*vdotn_h2/nlen2;
          vy = vy + dd*l_seg;
          vz = vz - dd*hh[ii];
          break;
      }
      /* Now compute reflectivity. */
      if((i <= 2 && mx == 0) || (i > 2 && my == 0))
      {
        x += hadj; /* Re-adjust origin */
        ABSORB;
      } else {
        double ref=1;
        if (i <= 2)
        {
          double m     = (mx > 0 ? mx : fabs(mx*w1/w1_in[ii]));
          double par[] = {R0, Qcx, alphax, m, W};
          StdReflecFunc(q, par, &ref);
          if (ref > 0)
            p *= ref;
          else {
            x += hadj; /* Re-adjust origin */
            ABSORB;                               /* Cutoff ~ 1E-10 */
          }
        } else {
          double m     = (my > 0 ? my : fabs(my*h1/h1_in[ii]));
          double par[] = {R0, Qcy, alphay, m, W};
          StdReflecFunc(q, par, &ref);
          if (ref > 0)
            p *= ref;
          else {
            x += hadj; /* Re-adjust origin */
            ABSORB;                               /* Cutoff ~ 1E-10 */
          }
        }
      }
      x += hadj; SCATTER; x -= hadj;
    } /* loop on reflections inside segment */
    x += hadj; /* Re-adjust origin */

    /* rotate neutron according to actual guide curvature */
    if (rotation_h) {
      double nvx, nvy, nvz;
      rotate(nvx,nvy,nvz, vx,vy,vz, -rotation_h, 0,1,0);
      vx = nvx; vy=nvy; vz=nvz;
    }
    if (rotation_v) {
      double nvx, nvy, nvz;
      rotate(nvx,nvy,nvz, vx,vy,vz, -rotation_v, 1,0,0);
      vx = nvx; vy=nvy; vz=nvz;
    }
  } /* loop on segments */

}
#line 18280 "./ThALES_resolution_v2.c"
}   /* End of H53_Nose=Guide_tapering() SETTING parameter declarations. */
#undef rotation_v
#undef rotation_h
#undef num
#undef ep
#undef file_name
#undef pos
#undef fu
#undef seg
#undef ii
#undef i
#undef Div1
#undef test
#undef p2_para
#undef div1
#undef u2
#undef u1
#undef mxi
#undef lbh
#undef lbw
#undef b_ell_q
#undef a_ell_q
#undef w2
#undef w12
#undef h2
#undef h12
#undef seg
#undef l_seg
#undef w2_out
#undef w1_in
#undef h2_out
#undef h1_in
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_Nose:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(11,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component before_monochromator_slit [12] */
  mccoordschange(mcposrbefore_monochromator_slit, mcrotrbefore_monochromator_slit,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component before_monochromator_slit (without coords transformations) */
  mcJumpTrace_before_monochromator_slit:
  SIG_MESSAGE("before_monochromator_slit (Trace)");
  mcDEBUG_COMP("before_monochromator_slit")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompbefore_monochromator_slit
  STORE_NEUTRON(12,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[12]++;
  mcPCounter[12] += p;
  mcP2Counter[12] += p*p;
#define mccompcurname  before_monochromator_slit
#define mccompcurtype  Slit
#define mccompcurindex 12
{   /* Declarations of before_monochromator_slit=Slit() SETTING parameters. */
MCNUM xmin = mccbefore_monochromator_slit_xmin;
MCNUM xmax = mccbefore_monochromator_slit_xmax;
MCNUM ymin = mccbefore_monochromator_slit_ymin;
MCNUM ymax = mccbefore_monochromator_slit_ymax;
MCNUM radius = mccbefore_monochromator_slit_radius;
MCNUM xwidth = mccbefore_monochromator_slit_xwidth;
MCNUM yheight = mccbefore_monochromator_slit_yheight;
#line 71 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
    PROP_Z0;
    if (((radius == 0) && (x<xmin || x>xmax || y<ymin || y>ymax))
	|| ((radius != 0) && (x*x + y*y > radius*radius))) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
      ABSORB;
    }
    else
        SCATTER;
}
#line 18443 "./ThALES_resolution_v2.c"
}   /* End of before_monochromator_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompbefore_monochromator_slit:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(12,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component l_monitor [13] */
  mccoordschange(mcposrl_monitor, mcrotrl_monitor,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component l_monitor (without coords transformations) */
  mcJumpTrace_l_monitor:
  SIG_MESSAGE("l_monitor (Trace)");
  mcDEBUG_COMP("l_monitor")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompl_monitor
  STORE_NEUTRON(13,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[13]++;
  mcPCounter[13] += p;
  mcP2Counter[13] += p*p;
#define mccompcurname  l_monitor
#define mccompcurtype  L_monitor
#define mccompcurindex 13
#define nL mccl_monitor_nL
#define L_N mccl_monitor_L_N
#define L_p mccl_monitor_L_p
#define L_p2 mccl_monitor_L_p2
{   /* Declarations of l_monitor=L_monitor() SETTING parameters. */
char* filename = mccl_monitor_filename;
MCNUM xmin = mccl_monitor_xmin;
MCNUM xmax = mccl_monitor_xmax;
MCNUM ymin = mccl_monitor_ymin;
MCNUM ymax = mccl_monitor_ymax;
MCNUM xwidth = mccl_monitor_xwidth;
MCNUM yheight = mccl_monitor_yheight;
MCNUM Lmin = mccl_monitor_Lmin;
MCNUM Lmax = mccl_monitor_Lmax;
MCNUM restore_neutron = mccl_monitor_restore_neutron;
int nowritefile = mccl_monitor_nowritefile;
#line 84 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/L_monitor.comp"
{
    int i;
    double L;

    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
    {
      L = (2*PI/V2K)/sqrt(vx*vx + vy*vy + vz*vz);
      i = floor((L-Lmin)*nL/(Lmax-Lmin));
      if(i >= 0 && i < nL)
      {
        L_N[i]++;
        L_p[i] += p;
        L_p2[i] += p*p;
        SCATTER;
      }
    }
    if (restore_neutron) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
}
#line 18586 "./ThALES_resolution_v2.c"
}   /* End of l_monitor=L_monitor() SETTING parameter declarations. */
#undef L_p2
#undef L_p
#undef L_N
#undef nL
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompl_monitor:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(13,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_ThALES_Monochromator_Cradle [14] */
  mccoordschange(mcposrH53_ThALES_Monochromator_Cradle, mcrotrH53_ThALES_Monochromator_Cradle,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_ThALES_Monochromator_Cradle (without coords transformations) */
  mcJumpTrace_H53_ThALES_Monochromator_Cradle:
  SIG_MESSAGE("H53_ThALES_Monochromator_Cradle (Trace)");
  mcDEBUG_COMP("H53_ThALES_Monochromator_Cradle")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_ThALES_Monochromator_Cradle
  STORE_NEUTRON(14,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[14]++;
  mcPCounter[14] += p;
  mcP2Counter[14] += p*p;
#define mccompcurname  H53_ThALES_Monochromator_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 14
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_ThALES_Monochromator_Cradle:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(14,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_ThALES_Monochromator [15] */
  mccoordschange(mcposrH53_ThALES_Monochromator, mcrotrH53_ThALES_Monochromator,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_ThALES_Monochromator (without coords transformations) */
  mcJumpTrace_H53_ThALES_Monochromator:
  SIG_MESSAGE("H53_ThALES_Monochromator (Trace)");
  mcDEBUG_COMP("H53_ThALES_Monochromator")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_ThALES_Monochromator
  STORE_NEUTRON(15,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[15]++;
  mcPCounter[15] += p;
  mcP2Counter[15] += p*p;
#define mccompcurname  H53_ThALES_Monochromator
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 15
#define mos_rms_y mccH53_ThALES_Monochromator_mos_rms_y
#define mos_rms_z mccH53_ThALES_Monochromator_mos_rms_z
#define mos_rms_max mccH53_ThALES_Monochromator_mos_rms_max
#define mono_Q mccH53_ThALES_Monochromator_mono_Q
#define SlabWidth mccH53_ThALES_Monochromator_SlabWidth
#define SlabHeight mccH53_ThALES_Monochromator_SlabHeight
#define rTable mccH53_ThALES_Monochromator_rTable
#define tTable mccH53_ThALES_Monochromator_tTable
#define row mccH53_ThALES_Monochromator_row
#define col mccH53_ThALES_Monochromator_col
#define tiltH mccH53_ThALES_Monochromator_tiltH
#define tiltV mccH53_ThALES_Monochromator_tiltV
{   /* Declarations of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameters. */
char* reflect = mccH53_ThALES_Monochromator_reflect;
char* transmit = mccH53_ThALES_Monochromator_transmit;
MCNUM zwidth = mccH53_ThALES_Monochromator_zwidth;
MCNUM yheight = mccH53_ThALES_Monochromator_yheight;
MCNUM gap = mccH53_ThALES_Monochromator_gap;
MCNUM NH = mccH53_ThALES_Monochromator_NH;
MCNUM NV = mccH53_ThALES_Monochromator_NV;
MCNUM mosaich = mccH53_ThALES_Monochromator_mosaich;
MCNUM mosaicv = mccH53_ThALES_Monochromator_mosaicv;
MCNUM r0 = mccH53_ThALES_Monochromator_r0;
MCNUM t0 = mccH53_ThALES_Monochromator_t0;
MCNUM Q = mccH53_ThALES_Monochromator_Q;
MCNUM RV = mccH53_ThALES_Monochromator_RV;
MCNUM RH = mccH53_ThALES_Monochromator_RH;
MCNUM DM = mccH53_ThALES_Monochromator_DM;
MCNUM mosaic = mccH53_ThALES_Monochromator_mosaic;
MCNUM width = mccH53_ThALES_Monochromator_width;
MCNUM height = mccH53_ThALES_Monochromator_height;
MCNUM verbose = mccH53_ThALES_Monochromator_verbose;
MCNUM order = mccH53_ThALES_Monochromator_order;
#line 230 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  double dt;

  if(vx != 0.0 && (dt = -x/vx) >= 0.0 && r0)
  {                             /* Moving towards crystal? */
    double zmin,zmax, ymin,ymax;

    /* Propagate to crystal plane */
    PROP_DT(dt);    /* now in the vertical plane of monochromator */

    zmax = ((NH*(SlabWidth+gap))-gap)/2;
    zmin = -zmax;
    ymax = ((NV*(SlabHeight+gap))-gap)/2;
    ymin = -ymax;

    /* hit a slab or a gap ? */

    if (z>zmin && z<zmax && y>ymin && y<ymax) { /* Intersect the crystal? */
      double tilth,tiltv;         /* used to calculate tilt angle of slab */
      double ratio, Q_order, k, kux,kuy,kuz;
      double kix,kiy,kiz;
      int    do_transmit = 0;

      col = ceil ( (z-zmin)/(SlabWidth +gap));  /* which slab hit ? */
      row = ceil ( (y-ymin)/(SlabHeight+gap));
      if (RH != 0) tilth = tiltH ? tiltH[(int)col] :  asin((col-(NH+1)/2)*(SlabWidth+gap)/RH);
      else tilth=0;
      if (RV != 0) tiltv = tiltV ? tiltV[(int)row] : -asin((row-(NV+1)/2)*(SlabHeight+gap)/RV);
      else tiltv=0;

      /* restore neutron in order to transform to slab coordinates */
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);

      /* rotate with tilth (around Y) and tiltv (around Z), center on plate */
      double center_z=zmin+(col-0.5)*(SlabWidth+gap) -gap/2;
      double center_y=ymin+(row-0.5)*(SlabHeight+gap)-gap/2;
      Rotation T;
      rot_set_rotation(T, 0, tilth,    tiltv);
      /* now make the coordinate system change */
      mccoordschange_polarisation(T, &vx, &vy, &vz);
      y-=center_y;
      z-=center_z;
      coords_get(rot_apply(T,coords_set(x,y,z)),&x,&y,&z);

      /* this is where polaisation should be handled, plus further down */
      /* mccoordschange_polarisation(t, &sx, &sy, &sz); */

      /* now propagate to slab plane */
      PROP_X0;

      if (fabs(z) <= SlabWidth/2 && fabs(y) <= SlabHeight/2) { /* not in gap ? */
        kix = V2K*vx;             /* Initial wave vector */
        kiy = V2K*vy;
        kiz = V2K*vz;
        /* Get reflection order and corresponding nominal scattering vector q0
          of correct length and direction. Only the order with the closest
          scattering vector is considered */
        ratio = -2*kix/mono_Q;
        Q_order = floor(ratio + .5);
        if(Q_order == 0.0) Q_order = ratio < 0 ? -1 : 1;
        /* Order will be negative when the neutron enters from the back, in
          which case the direction of Q0 is flipped. */
        if(Q_order < 0) Q_order = -Q_order;
        /* Make sure the order is small enough to allow Bragg scattering at the
          given neutron wavelength */
        k = sqrt(kix*kix + kiy*kiy + kiz*kiz);
        kux = kix/k;              /* Unit vector along ki */
        kuy = kiy/k;
        kuz = kiz/k;
        if(Q_order > 2*k/mono_Q) Q_order--;
        if((!order && Q_order > 0) || (Q_order == fabs(order) && order)) {           /* Bragg scattering possible? */
          double q0, q0x, theta, delta, p_reflect, my_r0;

          q0 = Q_order*mono_Q;
          q0x = ratio < 0 ? -q0 : q0;
          theta = asin(q0/(2*k)); /* Actual bragg angle */
          /* Make MC choice: reflect or transmit? */
          delta = asin(fabs(kux)) - theta;

          if (rTable.data != NULL)
          {
            my_r0 = r0*Table_Value(rTable, k, 1); /* 2nd column */
          }
          else my_r0 = r0;
          if (my_r0 > 1)
          {
            if (my_r0 > 1.01 && verbose) fprintf(stdout, "Warning: Monochromator_curved : lowered reflectivity from %f to 1 (k=%f)\n", my_r0, k);
            my_r0=0.999;
          }
          if (my_r0 < 0)
          {
            if (verbose) fprintf(stdout, "Warning: Monochromator_curved : raised reflectivity from %f to 0 (k=%f)\n", my_r0, k);
            my_r0=0;
          }

          p_reflect = fabs(my_r0)*exp(-kiz*kiz/(kiy*kiy + kiz*kiz)*(delta*delta)/
                            (2*mos_rms_y*mos_rms_y))*
                        exp(-kiy*kiy/(kiy*kiy + kiz*kiz)*(delta*delta)/
                            (2*mos_rms_z*mos_rms_z));

          if(rand01() <= p_reflect) { /* Reflect */
            double bx,by,bz,ax,ay,az,phi;
            double cos_2theta,k_sin_2theta,cos_phi,sin_phi,q_x,q_y,q_z;
            double total,c1x,c1y,c1z,w,mos_sample;
            int i=0;

            cos_2theta   = cos(2*theta);
            k_sin_2theta = k*sin(2*theta);
            /* Get unit normal to plane containing ki and most probable kf */
            vec_prod(bx, by, bz, kix, kiy, kiz, q0x, 0, 0);
            NORM(bx,by,bz);
            bx *= k_sin_2theta;
            by *= k_sin_2theta;
            bz *= k_sin_2theta;
            /* Get unit vector normal to ki and b */
            vec_prod(ax, ay, az, bx, by, bz, kux, kuy, kuz);
            /* Compute the total scattering probability at this ki */
            total = 0;
            /* Choose width of Gaussian distribution to sample the angle
            * phi on the Debye-Scherrer cone for the scattered neutron.
            * The radius of the Debye-Scherrer cone is smaller by a
            * factor 1/cos(theta) than the radius of the (partial) sphere
            * describing the possible orientations of Q due to mosaicity, so we
            * start with a width 1/cos(theta) greater than the largest of
            * the two mosaics. */
            mos_sample = mos_rms_max/cos(theta);
            c1x = kix*(cos_2theta-1);
            c1y = kiy*(cos_2theta-1);
            c1z = kiz*(cos_2theta-1);
            /* Loop, repeatedly reducing the sample width until it is small
            * enough to avoid sampling scattering directions with
            * ridiculously low scattering probability.
            * Use a cut-off at 5 times the gauss width for considering
            * scattering probability as well as for integration limits
            * when integrating the sampled distribution below. */
            for(i=0; i<100; i++) {
              w = 5*mos_sample;
              cos_phi = cos(w);
              sin_phi = sin(w);
              q_x =  c1x + cos_phi*ax + sin_phi*bx;
              q_y = (c1y + cos_phi*ay + sin_phi*by)/mos_rms_z;
              q_z = (c1z + cos_phi*az + sin_phi*bz)/mos_rms_y;
              /* Stop when we get near a factor of 25=5^2. */
              if(q_z*q_z + q_y*q_y < (25/(2.0/3.0))*(q_x*q_x))
                break;
              mos_sample *= (2.0/3.0);
            }
            /* Now integrate the chosen sampling distribution, using a
            * cut-off at five times sigma. */
            for(i = 0; i < (sizeof(Gauss_X)/sizeof(double)); i++)
            {
              phi = w*Gauss_X[i];
              cos_phi = cos(phi);
              sin_phi = sin(phi);
              q_x = c1x + cos_phi*ax + sin_phi*bx;
              q_y = c1y + cos_phi*ay + sin_phi*by;
              q_z = c1z + cos_phi*az + sin_phi*bz;
              p_reflect = GAUSS((q_z/q_x),0,mos_rms_y)*
                          GAUSS((q_y/q_x),0,mos_rms_z);
              total += Gauss_W[i]*p_reflect;
            }
            total *= w;
            /* Choose point on Debye-Scherrer cone. Sample from a Gaussian of
             * width 1/cos(theta) greater than the mosaic and correct for any
             * error by adjusting the neutron weight later. */
            phi = mos_sample*randnorm();
            /* Compute final wave vector kf and scattering vector q = ki - kf */
            cos_phi = cos(phi);
            sin_phi = sin(phi);
            q_x = c1x + cos_phi*ax + sin_phi*bx;
            q_y = c1y + cos_phi*ay + sin_phi*by;
            q_z = c1z + cos_phi*az + sin_phi*bz;
            p_reflect = GAUSS((q_z/q_x),0,mos_rms_y)*
                        GAUSS((q_y/q_x),0,mos_rms_z);

            vx = K2V*(kix+q_x);
            vy = K2V*(kiy+q_y);
            vz = K2V*(kiz+q_z);
            p_reflect /= total*GAUSS(phi,0,mos_sample);
            if (p_reflect <= 0) ABSORB;
            if (p_reflect > 1)  p_reflect = 1;
            p *= p_reflect;

          } /* End MC choice to reflect or transmit neutron (if tmp<p_reflect) */
          else do_transmit = 1;
            /* else transmit neutron */
        } /* End bragg scattering possible (if order) */
        else do_transmit=1;
        if (do_transmit)
        {
          double my_t0;
          if (tTable.data != NULL)
          {
            my_t0 = t0*Table_Value(tTable, k, 1); /* 2nd column */
          }
          else my_t0 = t0;
          /* do not SCATTER, else GROUP does not work */
          if (my_t0 > 1)
          {
            if (my_t0 > 1.01 && verbose) fprintf(stdout, "Warning: Monochromator_curved : lowered transmission from %f to 1 (k=%f)\n", my_t0, k);
            my_t0=0.999;
          }
          if (my_t0 > 0) p*= my_t0;
          else ABSORB;
        }
      } /* end if not in gap */
      /* rotate back in component frame */
      Rotation TT;
      rot_transpose(T, TT);
      /* now make the coordinate system change */
      mccoordschange_polarisation(TT, &vx, &vy, &vz);
      coords_get(rot_apply(TT,coords_set(x,y,z)),&x,&y,&z);
      y+=center_y;
      z+=center_z;
      /* Visualise scattering point in proper, component frame 
	 - but only if the neutron is reflected, that is none of:
	 * transmitted
	 * falling outside the slab material */	
      if(!do_transmit) SCATTER;

      /* mccoordschange_polarisation(tt, &sx, &sy, &sz); */
    } /* End intersect the crystal (if z) */
    else {
      /* restore neutron state when no interaction */
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
  } /* End neutron moving towards crystal (if vx)*/
}
#line 19060 "./ThALES_resolution_v2.c"
/* 'H53_ThALES_Monochromator=Monochromator_curved()' component instance extend code */
    SIG_MESSAGE("H53_ThALES_Monochromator (Trace:Extend)");
#line 259 "ThALES_resolution_v2.instr"
  flag=SCATTERED;
#line 19065 "./ThALES_resolution_v2.c"
}   /* End of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_ThALES_Monochromator:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(15,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component H53_ThALES_Monochromator_Out [16] */
  mccoordschange(mcposrH53_ThALES_Monochromator_Out, mcrotrH53_ThALES_Monochromator_Out,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component H53_ThALES_Monochromator_Out (without coords transformations) */
  mcJumpTrace_H53_ThALES_Monochromator_Out:
  SIG_MESSAGE("H53_ThALES_Monochromator_Out (Trace)");
  mcDEBUG_COMP("H53_ThALES_Monochromator_Out")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompH53_ThALES_Monochromator_Out
  STORE_NEUTRON(16,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[16]++;
  mcPCounter[16] += p;
  mcP2Counter[16] += p*p;
#define mccompcurname  H53_ThALES_Monochromator_Out
#define mccompcurtype  Arm
#define mccompcurindex 16
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompH53_ThALES_Monochromator_Out:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(16,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component before_sample_slit [17] */
  mccoordschange(mcposrbefore_sample_slit, mcrotrbefore_sample_slit,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component before_sample_slit (without coords transformations) */
  mcJumpTrace_before_sample_slit:
  SIG_MESSAGE("before_sample_slit (Trace)");
  mcDEBUG_COMP("before_sample_slit")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompbefore_sample_slit
  STORE_NEUTRON(17,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[17]++;
  mcPCounter[17] += p;
  mcP2Counter[17] += p*p;
#define mccompcurname  before_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 17
{   /* Declarations of before_sample_slit=Slit() SETTING parameters. */
MCNUM xmin = mccbefore_sample_slit_xmin;
MCNUM xmax = mccbefore_sample_slit_xmax;
MCNUM ymin = mccbefore_sample_slit_ymin;
MCNUM ymax = mccbefore_sample_slit_ymax;
MCNUM radius = mccbefore_sample_slit_radius;
MCNUM xwidth = mccbefore_sample_slit_xwidth;
MCNUM yheight = mccbefore_sample_slit_yheight;
#line 71 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
    PROP_Z0;
    if (((radius == 0) && (x<xmin || x>xmax || y<ymin || y>ymax))
	|| ((radius != 0) && (x*x + y*y > radius*radius))) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
      ABSORB;
    }
    else
        SCATTER;
}
#line 19304 "./ThALES_resolution_v2.c"
}   /* End of before_sample_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompbefore_sample_slit:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(17,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component E_sample_mon [18] */
  mccoordschange(mcposrE_sample_mon, mcrotrE_sample_mon,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component E_sample_mon (without coords transformations) */
  mcJumpTrace_E_sample_mon:
  SIG_MESSAGE("E_sample_mon (Trace)");
  mcDEBUG_COMP("E_sample_mon")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompE_sample_mon
  STORE_NEUTRON(18,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[18]++;
  mcPCounter[18] += p;
  mcP2Counter[18] += p*p;
#define mccompcurname  E_sample_mon
#define mccompcurtype  E_monitor
#define mccompcurindex 18
#define nE mccE_sample_mon_nE
#define E_N mccE_sample_mon_E_N
#define E_p mccE_sample_mon_E_p
#define E_p2 mccE_sample_mon_E_p2
#define S_p mccE_sample_mon_S_p
#define S_pE mccE_sample_mon_S_pE
#define S_pE2 mccE_sample_mon_S_pE2
{   /* Declarations of E_sample_mon=E_monitor() SETTING parameters. */
char* filename = mccE_sample_mon_filename;
MCNUM xmin = mccE_sample_mon_xmin;
MCNUM xmax = mccE_sample_mon_xmax;
MCNUM ymin = mccE_sample_mon_ymin;
MCNUM ymax = mccE_sample_mon_ymax;
MCNUM xwidth = mccE_sample_mon_xwidth;
MCNUM yheight = mccE_sample_mon_yheight;
MCNUM Emin = mccE_sample_mon_Emin;
MCNUM Emax = mccE_sample_mon_Emax;
MCNUM restore_neutron = mccE_sample_mon_restore_neutron;
int nowritefile = mccE_sample_mon_nowritefile;
#line 89 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/E_monitor.comp"
{
    int i;
    double E;

    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
    {
      E = VS2E*(vx*vx + vy*vy + vz*vz);

      S_p += p;
      S_pE += p*E;
      S_pE2 += p*E*E;

      i = floor((E-Emin)*nE/(Emax-Emin));
      if(i >= 0 && i < nE)
      {
        E_N[i]++;
        E_p[i] += p;
        E_p2[i] += p*p;
        SCATTER;
      }
    }
    if (restore_neutron) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
}
#line 19455 "./ThALES_resolution_v2.c"
}   /* End of E_sample_mon=E_monitor() SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef nE
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompE_sample_mon:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(18,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component PSD_sample_mon [19] */
  mccoordschange(mcposrPSD_sample_mon, mcrotrPSD_sample_mon,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component PSD_sample_mon (without coords transformations) */
  mcJumpTrace_PSD_sample_mon:
  SIG_MESSAGE("PSD_sample_mon (Trace)");
  mcDEBUG_COMP("PSD_sample_mon")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompPSD_sample_mon
  STORE_NEUTRON(19,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[19]++;
  mcPCounter[19] += p;
  mcP2Counter[19] += p*p;
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
{   /* Declarations of PSD_sample_mon=PSD_monitor() SETTING parameters. */
int nx = mccPSD_sample_mon_nx;
int ny = mccPSD_sample_mon_ny;
char* filename = mccPSD_sample_mon_filename;
MCNUM xmin = mccPSD_sample_mon_xmin;
MCNUM xmax = mccPSD_sample_mon_xmax;
MCNUM ymin = mccPSD_sample_mon_ymin;
MCNUM ymax = mccPSD_sample_mon_ymax;
MCNUM xwidth = mccPSD_sample_mon_xwidth;
MCNUM yheight = mccPSD_sample_mon_yheight;
MCNUM restore_neutron = mccPSD_sample_mon_restore_neutron;
int nowritefile = mccPSD_sample_mon_nowritefile;
#line 95 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  PROP_Z0;
  if (x>xmin && x<xmax && y>ymin && y<ymax){
    int i = floor((x - xmin)*nx/(xmax - xmin));
    int j = floor((y - ymin)*ny/(ymax - ymin));
    PSD_N[i][j]++;
    PSD_p[i][j] += p;
    PSD_p2[i][j] += p*p;
    SCATTER;
  }
  if (restore_neutron) {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 19597 "./ThALES_resolution_v2.c"
}   /* End of PSD_sample_mon=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompPSD_sample_mon:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(19,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component sample_arm [20] */
  mccoordschange(mcposrsample_arm, mcrotrsample_arm,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component sample_arm (without coords transformations) */
  mcJumpTrace_sample_arm:
  SIG_MESSAGE("sample_arm (Trace)");
  mcDEBUG_COMP("sample_arm")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompsample_arm
  STORE_NEUTRON(20,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[20]++;
  mcPCounter[20] += p;
  mcP2Counter[20] += p*p;
#define mccompcurname  sample_arm
#define mccompcurtype  Arm
#define mccompcurindex 20
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompsample_arm:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(20,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component res_sample [21] */
  mccoordschange(mcposrres_sample, mcrotrres_sample,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component res_sample (without coords transformations) */
  mcJumpTrace_res_sample:
  SIG_MESSAGE("res_sample (Trace)");
  mcDEBUG_COMP("res_sample")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompres_sample
  STORE_NEUTRON(21,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[21]++;
  mcPCounter[21] += p;
  mcP2Counter[21] += p*p;
#define mccompcurname  res_sample
#define mccompcurtype  Res_sample
#define mccompcurindex 21
#define res_struct mccres_sample_res_struct
{   /* Declarations of res_sample=Res_sample() SETTING parameters. */
MCNUM thickness = mccres_sample_thickness;
MCNUM radius = mccres_sample_radius;
MCNUM focus_r = mccres_sample_focus_r;
MCNUM E0 = mccres_sample_E0;
MCNUM dE = mccres_sample_dE;
MCNUM target_x = mccres_sample_target_x;
MCNUM target_y = mccres_sample_target_y;
MCNUM target_z = mccres_sample_target_z;
MCNUM focus_xw = mccres_sample_focus_xw;
MCNUM focus_yh = mccres_sample_focus_yh;
MCNUM focus_aw = mccres_sample_focus_aw;
MCNUM focus_ah = mccres_sample_focus_ah;
MCNUM xwidth = mccres_sample_xwidth;
MCNUM yheight = mccres_sample_yheight;
MCNUM zdepth = mccres_sample_zdepth;
int target_index = mccres_sample_target_index;
/* 'res_sample=Res_sample()' component instance has conditional execution */
if (( mcipSAMPLE == 0 ))

#line 129 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../samples/Res_sample.comp"
{
  double t0, t3;                /* Entry/exit time for outer cylinder */
  double t1, t2;                /* Entry/exit time for inner cylinder */
  double v;                     /* Neutron velocity */
  double E;
  double l_full;                /* Flight path length for non-scattered neutron */
  double dt0, dt1, dt2, dt;     /* Flight times through sample */
  double solid_angle=0;         /* Solid angle of target as seen from scattering point */
  double aim_x, aim_y, aim_z;   /* Position of target relative to scattering point */
  double scat_factor;           /* Simple cross-section model */
  int    intersect=0;

  if(res_struct.isrect)
    intersect = box_intersect(&t0, &t3, x, y, z, vx, vy, vz, xwidth, yheight, zdepth);
  else
    intersect = cylinder_intersect(&t0, &t3, x, y, z, vx, vy, vz, radius, yheight);

  if(intersect)
  {
    if(t0 < 0) ABSORB;
    if(res_struct.isrect) { t1 = t2 = t3; scat_factor = 2*zdepth; } /* box sample */
    else {  /* Hollow cylinder sample */
      /* Neutron enters at t=t0. */
      if(!thickness || !cylinder_intersect(&t1, &t2, x, y, z, vx, vy, vz, radius-thickness, yheight))
        t1 = t2 = t3;
      scat_factor = 2*radius; }
    dt0 = t1-t0;                  /* Time in sample, ingoing */
    dt1 = t2-t1;                  /* Time in hole */
    dt2 = t3-t2;                  /* Time in sample, outgoing */
    v = sqrt(vx*vx + vy*vy + vz*vz);
    l_full = v * (dt0 + dt2);     /* Length of full path through sample */
    p *= l_full/scat_factor;      /* Scattering probability */
    dt = rand01()*(dt0+dt2);      /* Time of scattering (relative to t0) */
    if (dt > dt0)
      dt += dt1;

    PROP_DT(dt+t0);             /* Point of scattering */

    /* Store initial neutron state. */
    if(p == 0) ABSORB;
    res_struct.pi = p;
    res_struct.ki_x = V2K*vx;
    res_struct.ki_y = V2K*vy;
    res_struct.ki_z = V2K*vz;
    res_struct.rx = x;
    res_struct.ry = y;
    res_struct.rz = z;

    aim_x = res_struct.tx-x;         /* Vector pointing at target (anal./det.) */
    aim_y = res_struct.ty-y;
    aim_z = res_struct.tz-z;
    if(res_struct.aw && res_struct.ah) {
        randvec_target_rect_angular(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, res_struct.aw, res_struct.ah, ROT_A_CURRENT_COMP);
    } else if(res_struct.xw && res_struct.yh) {
        randvec_target_rect(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, res_struct.xw, res_struct.yh, ROT_A_CURRENT_COMP);
    } else {
        randvec_target_circle(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, focus_r);
    }
    NORM(vx, vy, vz);
    E=E0+dE*randpm1();
    v=sqrt(E)*SE2V;
    vx *= v;
    vy *= v;
    vz *= v;
    SCATTER;

      /* Store final neutron state. */
    res_struct.kf_x = V2K*vx;
    res_struct.kf_y = V2K*vy;
    res_struct.kf_z = V2K*vz;
  }
}
#line 19904 "./ThALES_resolution_v2.c"
}   /* End of res_sample=Res_sample() SETTING parameter declarations. */
#undef res_struct
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompres_sample:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(21,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component v_sample [22] */
  mccoordschange(mcposrv_sample, mcrotrv_sample,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component v_sample (without coords transformations) */
  mcJumpTrace_v_sample:
  SIG_MESSAGE("v_sample (Trace)");
  mcDEBUG_COMP("v_sample")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompv_sample
  STORE_NEUTRON(22,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[22]++;
  mcPCounter[22] += p;
  mcP2Counter[22] += p*p;
#define mccompcurname  v_sample
#define mccompcurtype  V_sample
#define mccompcurindex 22
#define VarsV mccv_sample_VarsV
{   /* Declarations of v_sample=V_sample() SETTING parameters. */
MCNUM radius = mccv_sample_radius;
MCNUM thickness = mccv_sample_thickness;
MCNUM zdepth = mccv_sample_zdepth;
MCNUM Vc = mccv_sample_Vc;
MCNUM sigma_abs = mccv_sample_sigma_abs;
MCNUM sigma_inc = mccv_sample_sigma_inc;
MCNUM radius_i = mccv_sample_radius_i;
MCNUM radius_o = mccv_sample_radius_o;
MCNUM h = mccv_sample_h;
MCNUM focus_r = mccv_sample_focus_r;
MCNUM pack = mccv_sample_pack;
MCNUM frac = mccv_sample_frac;
MCNUM f_QE = mccv_sample_f_QE;
MCNUM gamma = mccv_sample_gamma;
MCNUM target_x = mccv_sample_target_x;
MCNUM target_y = mccv_sample_target_y;
MCNUM target_z = mccv_sample_target_z;
MCNUM focus_xw = mccv_sample_focus_xw;
MCNUM focus_yh = mccv_sample_focus_yh;
MCNUM focus_aw = mccv_sample_focus_aw;
MCNUM focus_ah = mccv_sample_focus_ah;
MCNUM xwidth = mccv_sample_xwidth;
MCNUM yheight = mccv_sample_yheight;
MCNUM zthick = mccv_sample_zthick;
MCNUM rad_sphere = mccv_sample_rad_sphere;
MCNUM sig_a = mccv_sample_sig_a;
MCNUM sig_i = mccv_sample_sig_i;
MCNUM V0 = mccv_sample_V0;
int target_index = mccv_sample_target_index;
MCNUM multiples = mccv_sample_multiples;
/* 'v_sample=V_sample()' component instance has conditional execution */
if (( mcipSAMPLE == 1 ))

#line 180 "V_sample.comp"
{
  double t0, t3;                /* Entry/exit time for outer cylinder */
  double t1, t2;                /* Entry/exit time for inner cylinder */
  double v;                     /* Neutron velocity */
  double dt0, dt1, dt2, dt;     /* Flight times through sample */
  double l_full;                /* Flight path length for non-scattered neutron */
  double l_i, l_o=0;            /* Flight path lenght in/out for scattered neutron */
  double my_a=0;                  /* Velocity-dependent attenuation factor */
  double solid_angle=0;         /* Solid angle of target as seen from scattering point */
  double aim_x=0, aim_y=0, aim_z=1;   /* Position of target relative to scattering point */
  double v_i, v_f, E_i, E_f; /* initial and final energies and velocities */
  double dE;                 /* Energy transfer */
  int    intersect=0;

  if (VarsV.shapetyp == 2)
    intersect = sphere_intersect(&t0, &t3, x, y, z, vx, vy, vz, rad_sphere);
  else
    if (VarsV.shapetyp == 1)
      intersect = box_intersect(&t0, &t3, x, y, z, vx, vy, vz, xwidth, yheight, zthick);
  else
    intersect = cylinder_intersect(&t0, &t3, x, y, z, vx, vy, vz, radius_o, h);
  if(intersect)
  {
    if(t0 < 0) ABSORB; /* we already passed the sample; this is illegal */
    /* Neutron enters at t=t0. */
    if(VarsV.shapetyp == 1 || VarsV.shapetyp == 2)
      t1 = t2 = t3;
    else
      if(!radius_i || !cylinder_intersect(&t1, &t2, x, y, z, vx, vy, vz, radius_i, h))
        t1 = t2 = t3;

    dt0 = t1-t0;                /* Time in sample, ingoing */
    dt1 = t2-t1;                /* Time in hole */
    dt2 = t3-t2;                /* Time in sample, outgoing */
    v = sqrt(vx*vx + vy*vy + vz*vz);
    l_full = v * (dt0 + dt2);   /* Length of full path through sample */
    if (v) my_a = VarsV.my_a_v*(2200/v);

    if (frac >= 1 || rand01()<frac)          /* Scattering */
    {
      dt = rand01()*(dt0+dt2);    /* Time of scattering (relative to t0) */
      l_i = v*dt;                 /* Penetration in sample: scattering+abs */
      if (dt > dt0)
        dt += dt1;                /* jump to 2nd side of cylinder */

      PROP_DT(dt+t0);             /* Point of scattering */

      if ((VarsV.tx || VarsV.ty || VarsV.tz)) {
        aim_x = VarsV.tx-x;       /* Vector pointing at target (anal./det.) */
        aim_y = VarsV.ty-y;
        aim_z = VarsV.tz-z;
      }
      if(VarsV.aw && VarsV.ah) {
        randvec_target_rect_angular(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, VarsV.aw, VarsV.ah, ROT_A_CURRENT_COMP);
      } else if(VarsV.xw && VarsV.yh) {
        randvec_target_rect(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, VarsV.xw, VarsV.yh, ROT_A_CURRENT_COMP);
      } else {
        randvec_target_circle(&vx, &vy, &vz, &solid_angle, aim_x, aim_y, aim_z, focus_r);
      }
      NORM(vx, vy, vz);

      v_i = v;          /* Store initial velocity in case of quasielastic */
      if (rand01()<f_QE)	/* Quasielastic contribution */
	{
          E_i = VS2E*v_i*v_i;
          dE = gamma*tan(PI/2*randpm1());
          E_f = E_i + dE;
          if (E_f <= 0)
            ABSORB;
	  v_f = SE2V*sqrt(E_f);
          v = v_f;
	  /*          printf("vi: %g Ei: %g dE: %g Ef %g vf: %g v: %g \n",
		      v_i,E_i,dE,E_f,v_f,v); */
	}

      vx *= v;
      vy *= v;
      vz *= v;

      if(VarsV.shapetyp == 0) {
        if(!cylinder_intersect(&t0, &t3, x, y, z, vx, vy, vz, radius_o, h)) {
          /* ??? did not hit cylinder */
          printf("FATAL ERROR: Did not hit cylinder from inside.\n");
          exit(1);
        }
        dt = t3; /* outgoing point */
        if(cylinder_intersect(&t1, &t2, x, y, z, vx, vy, vz, radius_i, h) &&
           t2 > 0)
          dt -= (t2-t1);            /* Subtract hollow part */
      }
      else {
        if(VarsV.shapetyp == 1) {
	      if(!box_intersect(&t0, &t3, x, y, z, vx, vy, vz, xwidth, yheight, zthick)) {
            /* ??? did not hit box */
            printf("FATAL ERROR: Did not hit box from inside.\n");
            exit(1);
          }
          dt = t3;
        }
        else {
	      if(!sphere_intersect(&t0, &t3, x, y, z, vx, vy, vz, rad_sphere)) {
            /* ??? did not hit sphere */
            printf("FATAL ERROR: Did not hit sphere from inside.\n");
            exit(1);
          }
          dt = t3;  
        }
      }
      l_o = v*dt; /* trajectory after scattering point: absorption only */

      p *= v/v_i*l_full*VarsV.my_s*exp(-my_a*(l_i+v_i/v*l_o)-VarsV.my_s*l_i);
      if (!multiples) {
	/* If no "multiples", correct by applying scattering cross-sec and
	   implicitly "absorb" further scattering (as in PowderN) 
	   We are currently (august 2007) having a debate on which solution 
	   is the most reasonable */
	p *= exp(-VarsV.my_s*l_o);
      }
      /* We do not consider scattering from 2nd part (outgoing) */
      p /= 4*PI/solid_angle;
      p /= frac;

      /* Polarisation part (1/3 NSF, 2/3 SF) */
      sx *= -1.0/3.0;
      sy *= -1.0/3.0;
      sz *= -1.0/3.0;

      SCATTER;
    }
    else /* Transmitting; always elastic */
    {
      p *= exp(-(my_a+VarsV.my_s)*l_full);
      p /= (1-frac);
    }
  }
}
#line 20183 "./ThALES_resolution_v2.c"
}   /* End of v_sample=V_sample() SETTING parameter declarations. */
#undef VarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompv_sample:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(22,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component Sample_Out [23] */
  mccoordschange(mcposrSample_Out, mcrotrSample_Out,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component Sample_Out (without coords transformations) */
  mcJumpTrace_Sample_Out:
  SIG_MESSAGE("Sample_Out (Trace)");
  mcDEBUG_COMP("Sample_Out")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompSample_Out
  STORE_NEUTRON(23,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[23]++;
  mcPCounter[23] += p;
  mcP2Counter[23] += p*p;
#define mccompcurname  Sample_Out
#define mccompcurtype  Arm
#define mccompcurindex 23
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompSample_Out:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(23,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component after_sample_slit [24] */
  mccoordschange(mcposrafter_sample_slit, mcrotrafter_sample_slit,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component after_sample_slit (without coords transformations) */
  mcJumpTrace_after_sample_slit:
  SIG_MESSAGE("after_sample_slit (Trace)");
  mcDEBUG_COMP("after_sample_slit")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompafter_sample_slit
  STORE_NEUTRON(24,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[24]++;
  mcPCounter[24] += p;
  mcP2Counter[24] += p*p;
#define mccompcurname  after_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 24
{   /* Declarations of after_sample_slit=Slit() SETTING parameters. */
MCNUM xmin = mccafter_sample_slit_xmin;
MCNUM xmax = mccafter_sample_slit_xmax;
MCNUM ymin = mccafter_sample_slit_ymin;
MCNUM ymax = mccafter_sample_slit_ymax;
MCNUM radius = mccafter_sample_slit_radius;
MCNUM xwidth = mccafter_sample_slit_xwidth;
MCNUM yheight = mccafter_sample_slit_yheight;
#line 71 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
    PROP_Z0;
    if (((radius == 0) && (x<xmin || x>xmax || y<ymin || y>ymax))
	|| ((radius != 0) && (x*x + y*y > radius*radius))) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
      ABSORB;
    }
    else
        SCATTER;
}
#line 20411 "./ThALES_resolution_v2.c"
}   /* End of after_sample_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompafter_sample_slit:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(24,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component Ana_Cradle [25] */
  mccoordschange(mcposrAna_Cradle, mcrotrAna_Cradle,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component Ana_Cradle (without coords transformations) */
  mcJumpTrace_Ana_Cradle:
  SIG_MESSAGE("Ana_Cradle (Trace)");
  mcDEBUG_COMP("Ana_Cradle")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompAna_Cradle
  STORE_NEUTRON(25,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[25]++;
  mcPCounter[25] += p;
  mcP2Counter[25] += p*p;
#define mccompcurname  Ana_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 25
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompAna_Cradle:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(25,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component PSD_analyzer [26] */
  mccoordschange(mcposrPSD_analyzer, mcrotrPSD_analyzer,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component PSD_analyzer (without coords transformations) */
  mcJumpTrace_PSD_analyzer:
  SIG_MESSAGE("PSD_analyzer (Trace)");
  mcDEBUG_COMP("PSD_analyzer")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompPSD_analyzer
  STORE_NEUTRON(26,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[26]++;
  mcPCounter[26] += p;
  mcP2Counter[26] += p*p;
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
{   /* Declarations of PSD_analyzer=PSD_monitor() SETTING parameters. */
int nx = mccPSD_analyzer_nx;
int ny = mccPSD_analyzer_ny;
char* filename = mccPSD_analyzer_filename;
MCNUM xmin = mccPSD_analyzer_xmin;
MCNUM xmax = mccPSD_analyzer_xmax;
MCNUM ymin = mccPSD_analyzer_ymin;
MCNUM ymax = mccPSD_analyzer_ymax;
MCNUM xwidth = mccPSD_analyzer_xwidth;
MCNUM yheight = mccPSD_analyzer_yheight;
MCNUM restore_neutron = mccPSD_analyzer_restore_neutron;
int nowritefile = mccPSD_analyzer_nowritefile;
#line 95 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  PROP_Z0;
  if (x>xmin && x<xmax && y>ymin && y<ymax){
    int i = floor((x - xmin)*nx/(xmax - xmin));
    int j = floor((y - ymin)*ny/(ymax - ymin));
    PSD_N[i][j]++;
    PSD_p[i][j] += p;
    PSD_p2[i][j] += p*p;
    SCATTER;
  }
  if (restore_neutron) {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 20649 "./ThALES_resolution_v2.c"
}   /* End of PSD_analyzer=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompPSD_analyzer:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(26,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component analyzer [27] */
  mccoordschange(mcposranalyzer, mcrotranalyzer,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component analyzer (without coords transformations) */
  mcJumpTrace_analyzer:
  SIG_MESSAGE("analyzer (Trace)");
  mcDEBUG_COMP("analyzer")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompanalyzer
  STORE_NEUTRON(27,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[27]++;
  mcPCounter[27] += p;
  mcP2Counter[27] += p*p;
#define mccompcurname  analyzer
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 27
#define mos_rms_y mccanalyzer_mos_rms_y
#define mos_rms_z mccanalyzer_mos_rms_z
#define mos_rms_max mccanalyzer_mos_rms_max
#define mono_Q mccanalyzer_mono_Q
#define SlabWidth mccanalyzer_SlabWidth
#define SlabHeight mccanalyzer_SlabHeight
#define rTable mccanalyzer_rTable
#define tTable mccanalyzer_tTable
#define row mccanalyzer_row
#define col mccanalyzer_col
#define tiltH mccanalyzer_tiltH
#define tiltV mccanalyzer_tiltV
{   /* Declarations of analyzer=Monochromator_curved() SETTING parameters. */
char* reflect = mccanalyzer_reflect;
char* transmit = mccanalyzer_transmit;
MCNUM zwidth = mccanalyzer_zwidth;
MCNUM yheight = mccanalyzer_yheight;
MCNUM gap = mccanalyzer_gap;
MCNUM NH = mccanalyzer_NH;
MCNUM NV = mccanalyzer_NV;
MCNUM mosaich = mccanalyzer_mosaich;
MCNUM mosaicv = mccanalyzer_mosaicv;
MCNUM r0 = mccanalyzer_r0;
MCNUM t0 = mccanalyzer_t0;
MCNUM Q = mccanalyzer_Q;
MCNUM RV = mccanalyzer_RV;
MCNUM RH = mccanalyzer_RH;
MCNUM DM = mccanalyzer_DM;
MCNUM mosaic = mccanalyzer_mosaic;
MCNUM width = mccanalyzer_width;
MCNUM height = mccanalyzer_height;
MCNUM verbose = mccanalyzer_verbose;
MCNUM order = mccanalyzer_order;
#line 230 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  double dt;

  if(vx != 0.0 && (dt = -x/vx) >= 0.0 && r0)
  {                             /* Moving towards crystal? */
    double zmin,zmax, ymin,ymax;

    /* Propagate to crystal plane */
    PROP_DT(dt);    /* now in the vertical plane of monochromator */

    zmax = ((NH*(SlabWidth+gap))-gap)/2;
    zmin = -zmax;
    ymax = ((NV*(SlabHeight+gap))-gap)/2;
    ymin = -ymax;

    /* hit a slab or a gap ? */

    if (z>zmin && z<zmax && y>ymin && y<ymax) { /* Intersect the crystal? */
      double tilth,tiltv;         /* used to calculate tilt angle of slab */
      double ratio, Q_order, k, kux,kuy,kuz;
      double kix,kiy,kiz;
      int    do_transmit = 0;

      col = ceil ( (z-zmin)/(SlabWidth +gap));  /* which slab hit ? */
      row = ceil ( (y-ymin)/(SlabHeight+gap));
      if (RH != 0) tilth = tiltH ? tiltH[(int)col] :  asin((col-(NH+1)/2)*(SlabWidth+gap)/RH);
      else tilth=0;
      if (RV != 0) tiltv = tiltV ? tiltV[(int)row] : -asin((row-(NV+1)/2)*(SlabHeight+gap)/RV);
      else tiltv=0;

      /* restore neutron in order to transform to slab coordinates */
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);

      /* rotate with tilth (around Y) and tiltv (around Z), center on plate */
      double center_z=zmin+(col-0.5)*(SlabWidth+gap) -gap/2;
      double center_y=ymin+(row-0.5)*(SlabHeight+gap)-gap/2;
      Rotation T;
      rot_set_rotation(T, 0, tilth,    tiltv);
      /* now make the coordinate system change */
      mccoordschange_polarisation(T, &vx, &vy, &vz);
      y-=center_y;
      z-=center_z;
      coords_get(rot_apply(T,coords_set(x,y,z)),&x,&y,&z);

      /* this is where polaisation should be handled, plus further down */
      /* mccoordschange_polarisation(t, &sx, &sy, &sz); */

      /* now propagate to slab plane */
      PROP_X0;

      if (fabs(z) <= SlabWidth/2 && fabs(y) <= SlabHeight/2) { /* not in gap ? */
        kix = V2K*vx;             /* Initial wave vector */
        kiy = V2K*vy;
        kiz = V2K*vz;
        /* Get reflection order and corresponding nominal scattering vector q0
          of correct length and direction. Only the order with the closest
          scattering vector is considered */
        ratio = -2*kix/mono_Q;
        Q_order = floor(ratio + .5);
        if(Q_order == 0.0) Q_order = ratio < 0 ? -1 : 1;
        /* Order will be negative when the neutron enters from the back, in
          which case the direction of Q0 is flipped. */
        if(Q_order < 0) Q_order = -Q_order;
        /* Make sure the order is small enough to allow Bragg scattering at the
          given neutron wavelength */
        k = sqrt(kix*kix + kiy*kiy + kiz*kiz);
        kux = kix/k;              /* Unit vector along ki */
        kuy = kiy/k;
        kuz = kiz/k;
        if(Q_order > 2*k/mono_Q) Q_order--;
        if((!order && Q_order > 0) || (Q_order == fabs(order) && order)) {           /* Bragg scattering possible? */
          double q0, q0x, theta, delta, p_reflect, my_r0;

          q0 = Q_order*mono_Q;
          q0x = ratio < 0 ? -q0 : q0;
          theta = asin(q0/(2*k)); /* Actual bragg angle */
          /* Make MC choice: reflect or transmit? */
          delta = asin(fabs(kux)) - theta;

          if (rTable.data != NULL)
          {
            my_r0 = r0*Table_Value(rTable, k, 1); /* 2nd column */
          }
          else my_r0 = r0;
          if (my_r0 > 1)
          {
            if (my_r0 > 1.01 && verbose) fprintf(stdout, "Warning: Monochromator_curved : lowered reflectivity from %f to 1 (k=%f)\n", my_r0, k);
            my_r0=0.999;
          }
          if (my_r0 < 0)
          {
            if (verbose) fprintf(stdout, "Warning: Monochromator_curved : raised reflectivity from %f to 0 (k=%f)\n", my_r0, k);
            my_r0=0;
          }

          p_reflect = fabs(my_r0)*exp(-kiz*kiz/(kiy*kiy + kiz*kiz)*(delta*delta)/
                            (2*mos_rms_y*mos_rms_y))*
                        exp(-kiy*kiy/(kiy*kiy + kiz*kiz)*(delta*delta)/
                            (2*mos_rms_z*mos_rms_z));

          if(rand01() <= p_reflect) { /* Reflect */
            double bx,by,bz,ax,ay,az,phi;
            double cos_2theta,k_sin_2theta,cos_phi,sin_phi,q_x,q_y,q_z;
            double total,c1x,c1y,c1z,w,mos_sample;
            int i=0;

            cos_2theta   = cos(2*theta);
            k_sin_2theta = k*sin(2*theta);
            /* Get unit normal to plane containing ki and most probable kf */
            vec_prod(bx, by, bz, kix, kiy, kiz, q0x, 0, 0);
            NORM(bx,by,bz);
            bx *= k_sin_2theta;
            by *= k_sin_2theta;
            bz *= k_sin_2theta;
            /* Get unit vector normal to ki and b */
            vec_prod(ax, ay, az, bx, by, bz, kux, kuy, kuz);
            /* Compute the total scattering probability at this ki */
            total = 0;
            /* Choose width of Gaussian distribution to sample the angle
            * phi on the Debye-Scherrer cone for the scattered neutron.
            * The radius of the Debye-Scherrer cone is smaller by a
            * factor 1/cos(theta) than the radius of the (partial) sphere
            * describing the possible orientations of Q due to mosaicity, so we
            * start with a width 1/cos(theta) greater than the largest of
            * the two mosaics. */
            mos_sample = mos_rms_max/cos(theta);
            c1x = kix*(cos_2theta-1);
            c1y = kiy*(cos_2theta-1);
            c1z = kiz*(cos_2theta-1);
            /* Loop, repeatedly reducing the sample width until it is small
            * enough to avoid sampling scattering directions with
            * ridiculously low scattering probability.
            * Use a cut-off at 5 times the gauss width for considering
            * scattering probability as well as for integration limits
            * when integrating the sampled distribution below. */
            for(i=0; i<100; i++) {
              w = 5*mos_sample;
              cos_phi = cos(w);
              sin_phi = sin(w);
              q_x =  c1x + cos_phi*ax + sin_phi*bx;
              q_y = (c1y + cos_phi*ay + sin_phi*by)/mos_rms_z;
              q_z = (c1z + cos_phi*az + sin_phi*bz)/mos_rms_y;
              /* Stop when we get near a factor of 25=5^2. */
              if(q_z*q_z + q_y*q_y < (25/(2.0/3.0))*(q_x*q_x))
                break;
              mos_sample *= (2.0/3.0);
            }
            /* Now integrate the chosen sampling distribution, using a
            * cut-off at five times sigma. */
            for(i = 0; i < (sizeof(Gauss_X)/sizeof(double)); i++)
            {
              phi = w*Gauss_X[i];
              cos_phi = cos(phi);
              sin_phi = sin(phi);
              q_x = c1x + cos_phi*ax + sin_phi*bx;
              q_y = c1y + cos_phi*ay + sin_phi*by;
              q_z = c1z + cos_phi*az + sin_phi*bz;
              p_reflect = GAUSS((q_z/q_x),0,mos_rms_y)*
                          GAUSS((q_y/q_x),0,mos_rms_z);
              total += Gauss_W[i]*p_reflect;
            }
            total *= w;
            /* Choose point on Debye-Scherrer cone. Sample from a Gaussian of
             * width 1/cos(theta) greater than the mosaic and correct for any
             * error by adjusting the neutron weight later. */
            phi = mos_sample*randnorm();
            /* Compute final wave vector kf and scattering vector q = ki - kf */
            cos_phi = cos(phi);
            sin_phi = sin(phi);
            q_x = c1x + cos_phi*ax + sin_phi*bx;
            q_y = c1y + cos_phi*ay + sin_phi*by;
            q_z = c1z + cos_phi*az + sin_phi*bz;
            p_reflect = GAUSS((q_z/q_x),0,mos_rms_y)*
                        GAUSS((q_y/q_x),0,mos_rms_z);

            vx = K2V*(kix+q_x);
            vy = K2V*(kiy+q_y);
            vz = K2V*(kiz+q_z);
            p_reflect /= total*GAUSS(phi,0,mos_sample);
            if (p_reflect <= 0) ABSORB;
            if (p_reflect > 1)  p_reflect = 1;
            p *= p_reflect;

          } /* End MC choice to reflect or transmit neutron (if tmp<p_reflect) */
          else do_transmit = 1;
            /* else transmit neutron */
        } /* End bragg scattering possible (if order) */
        else do_transmit=1;
        if (do_transmit)
        {
          double my_t0;
          if (tTable.data != NULL)
          {
            my_t0 = t0*Table_Value(tTable, k, 1); /* 2nd column */
          }
          else my_t0 = t0;
          /* do not SCATTER, else GROUP does not work */
          if (my_t0 > 1)
          {
            if (my_t0 > 1.01 && verbose) fprintf(stdout, "Warning: Monochromator_curved : lowered transmission from %f to 1 (k=%f)\n", my_t0, k);
            my_t0=0.999;
          }
          if (my_t0 > 0) p*= my_t0;
          else ABSORB;
        }
      } /* end if not in gap */
      /* rotate back in component frame */
      Rotation TT;
      rot_transpose(T, TT);
      /* now make the coordinate system change */
      mccoordschange_polarisation(TT, &vx, &vy, &vz);
      coords_get(rot_apply(TT,coords_set(x,y,z)),&x,&y,&z);
      y+=center_y;
      z+=center_z;
      /* Visualise scattering point in proper, component frame 
	 - but only if the neutron is reflected, that is none of:
	 * transmitted
	 * falling outside the slab material */	
      if(!do_transmit) SCATTER;

      /* mccoordschange_polarisation(tt, &sx, &sy, &sz); */
    } /* End intersect the crystal (if z) */
    else {
      /* restore neutron state when no interaction */
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
  } /* End neutron moving towards crystal (if vx)*/
}
#line 21019 "./ThALES_resolution_v2.c"
}   /* End of analyzer=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompanalyzer:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(27,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component Ana_Out [28] */
  mccoordschange(mcposrAna_Out, mcrotrAna_Out,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component Ana_Out (without coords transformations) */
  mcJumpTrace_Ana_Out:
  SIG_MESSAGE("Ana_Out (Trace)");
  mcDEBUG_COMP("Ana_Out")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompAna_Out
  STORE_NEUTRON(28,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[28]++;
  mcPCounter[28] += p;
  mcP2Counter[28] += p*p;
#define mccompcurname  Ana_Out
#define mccompcurtype  Arm
#define mccompcurindex 28
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompAna_Out:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(28,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component slit [29] */
  mccoordschange(mcposrslit, mcrotrslit,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component slit (without coords transformations) */
  mcJumpTrace_slit:
  SIG_MESSAGE("slit (Trace)");
  mcDEBUG_COMP("slit")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompslit
  STORE_NEUTRON(29,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[29]++;
  mcPCounter[29] += p;
  mcP2Counter[29] += p*p;
#define mccompcurname  slit
#define mccompcurtype  Slit
#define mccompcurindex 29
{   /* Declarations of slit=Slit() SETTING parameters. */
MCNUM xmin = mccslit_xmin;
MCNUM xmax = mccslit_xmax;
MCNUM ymin = mccslit_ymin;
MCNUM ymax = mccslit_ymax;
MCNUM radius = mccslit_radius;
MCNUM xwidth = mccslit_xwidth;
MCNUM yheight = mccslit_yheight;
#line 71 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
    PROP_Z0;
    if (((radius == 0) && (x<xmin || x>xmax || y<ymin || y>ymax))
	|| ((radius != 0) && (x*x + y*y > radius*radius))) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
      ABSORB;
    }
    else
        SCATTER;
}
#line 21258 "./ThALES_resolution_v2.c"
}   /* End of slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompslit:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(29,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component PSD_det [30] */
  mccoordschange(mcposrPSD_det, mcrotrPSD_det,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component PSD_det (without coords transformations) */
  mcJumpTrace_PSD_det:
  SIG_MESSAGE("PSD_det (Trace)");
  mcDEBUG_COMP("PSD_det")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompPSD_det
  STORE_NEUTRON(30,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[30]++;
  mcPCounter[30] += p;
  mcP2Counter[30] += p*p;
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
{   /* Declarations of PSD_det=PSD_monitor() SETTING parameters. */
int nx = mccPSD_det_nx;
int ny = mccPSD_det_ny;
char* filename = mccPSD_det_filename;
MCNUM xmin = mccPSD_det_xmin;
MCNUM xmax = mccPSD_det_xmax;
MCNUM ymin = mccPSD_det_ymin;
MCNUM ymax = mccPSD_det_ymax;
MCNUM xwidth = mccPSD_det_xwidth;
MCNUM yheight = mccPSD_det_yheight;
MCNUM restore_neutron = mccPSD_det_restore_neutron;
int nowritefile = mccPSD_det_nowritefile;
#line 95 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  PROP_Z0;
  if (x>xmin && x<xmax && y>ymin && y<ymax){
    int i = floor((x - xmin)*nx/(xmax - xmin));
    int j = floor((y - ymin)*ny/(ymax - ymin));
    PSD_N[i][j]++;
    PSD_p[i][j] += p;
    PSD_p2[i][j] += p*p;
    SCATTER;
  }
  if (restore_neutron) {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 21393 "./ThALES_resolution_v2.c"
}   /* End of PSD_det=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompPSD_det:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(30,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component res_monitor [31] */
  mccoordschange(mcposrres_monitor, mcrotrres_monitor,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component res_monitor (without coords transformations) */
  mcJumpTrace_res_monitor:
  SIG_MESSAGE("res_monitor (Trace)");
  mcDEBUG_COMP("res_monitor")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompres_monitor
  STORE_NEUTRON(31,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[31]++;
  mcPCounter[31] += p;
  mcP2Counter[31] += p*p;
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
{   /* Declarations of res_monitor=Res_monitor() SETTING parameters. */
char* filename = mccres_monitor_filename;
char* options = mccres_monitor_options;
MCNUM xwidth = mccres_monitor_xwidth;
MCNUM yheight = mccres_monitor_yheight;
MCNUM zdepth = mccres_monitor_zdepth;
MCNUM radius = mccres_monitor_radius;
MCNUM xmin = mccres_monitor_xmin;
MCNUM xmax = mccres_monitor_xmax;
MCNUM ymin = mccres_monitor_ymin;
MCNUM ymax = mccres_monitor_ymax;
MCNUM zmin = mccres_monitor_zmin;
MCNUM zmax = mccres_monitor_zmax;
MCNUM bufsize = mccres_monitor_bufsize;
MCNUM restore_neutron = mccres_monitor_restore_neutron;
/* 'res_monitor=Res_monitor()' component instance has conditional execution */
if (( mcipSAMPLE == 0 ))

#line 131 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
{
  double  t0 = 0;
  double  t1 = 0;
  int     intersect   = 0;

  if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SQUARE) /* square xy */
  {
    PROP_Z0;
    intersect = (x>=Vars.mxmin && x<=Vars.mxmax && y>=Vars.mymin && y<=Vars.mymax);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_DISK)   /* disk xy */
  {
    PROP_Z0;
    intersect = ((x*x + y*y) <= Vars.Sphere_Radius*Vars.Sphere_Radius);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) /* sphere */
  {
    intersect = sphere_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius);
  /*      intersect = (intersect && t0 > 0); */
  }
  else if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA)) /* cylinder */
  {
    intersect = cylinder_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius, Vars.Cylinder_Height);
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA) && (intersect != 1)) intersect = 0; /* remove top/bottom for banana */
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) /* box */
  {
    intersect = box_intersect(&t0, &t1, x, y, z, vx, vy, vz, fabs(Vars.mxmax-Vars.mxmin), fabs(Vars.mymax-Vars.mymin), fabs(Vars.mzmax-Vars.mzmin));
  }

  if (intersect)
  {
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA))
    {
      if (t0 < 0 && t1 > 0)
        t0 = t;  /* neutron was already inside ! */
      if (t1 < 0 && t0 > 0) /* neutron exit before entering !! */
        t1 = t;
      /* t0 is now time of incoming intersection with the sphere. */
      if ((Vars.Flag_Shape < 0) && (t1 > 0))
        PROP_DT(t1); /* t1 outgoing beam */
      else
        PROP_DT(t0); /* t0 incoming beam */
    }

    /* Now fetch data from the Res_sample. */
    if(p && (!bufsize || buffer_index<bufsize))
    {
      struct Res_sample_struct *s =
        &(MC_GETPAR(res_sample_comp, res_struct));
      if(s->pi != 0)
      {
        Vars.cp  = s->ki_x;
        Vars.cx  = s->ki_y;
        Vars.cvx = s->ki_z;
        Vars.csx = s->kf_x;
        Vars.cy  = s->kf_y;
        Vars.cvy = s->kf_z;
        Vars.csy = s->rx;
        Vars.cz  = s->ry;
        Vars.cvz = s->rz;
        Vars.csz = s->pi;
        Vars.ct  = p/s->pi;
        Monitor_nD_Trace(&DEFS, &Vars);
      } /* if s->pi */
      SCATTER;
    } /* if p */

  } /* end if intersection */
  if (restore_neutron) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }

}
#line 21597 "./ThALES_resolution_v2.c"
}   /* End of res_monitor=Res_monitor() SETTING parameter declarations. */
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompres_monitor:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(31,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  /* TRACE Component detector_all [32] */
  mccoordschange(mcposrdetector_all, mcrotrdetector_all,
    &mcnlx,
    &mcnly,
    &mcnlz,
    &mcnlvx,
    &mcnlvy,
    &mcnlvz,
    &mcnlsx,
    &mcnlsy,
    &mcnlsz);
  /* define label inside component detector_all (without coords transformations) */
  mcJumpTrace_detector_all:
  SIG_MESSAGE("detector_all (Trace)");
  mcDEBUG_COMP("detector_all")
  mcDEBUG_STATE(
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
#define p mcnlp

#define mcabsorbComp mcabsorbCompdetector_all
  STORE_NEUTRON(32,
    mcnlx,
    mcnly,
    mcnlz,
    mcnlvx,
    mcnlvy,
    mcnlvz,
    mcnlt,
    mcnlsx,
    mcnlsy,
    mcnlsz,
    mcnlp);
  mcScattered=0;
  mcRestore=0;
  mcNCounter[32]++;
  mcPCounter[32] += p;
  mcP2Counter[32] += p*p;
#define mccompcurname  detector_all
#define mccompcurtype  Monitor
#define mccompcurindex 32
#define Nsum mccdetector_all_Nsum
#define psum mccdetector_all_psum
#define p2sum mccdetector_all_p2sum
{   /* Declarations of detector_all=Monitor() SETTING parameters. */
MCNUM xmin = mccdetector_all_xmin;
MCNUM xmax = mccdetector_all_xmax;
MCNUM ymin = mccdetector_all_ymin;
MCNUM ymax = mccdetector_all_ymax;
MCNUM xwidth = mccdetector_all_xwidth;
MCNUM yheight = mccdetector_all_yheight;
MCNUM restore_neutron = mccdetector_all_restore_neutron;
#line 74 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Monitor.comp"
{
    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
    {
      Nsum++;
      psum += p;
      p2sum += p*p;
      SCATTER;
    }
    if (restore_neutron) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
}
#line 21731 "./ThALES_resolution_v2.c"
}   /* End of detector_all=Monitor() SETTING parameter declarations. */
#undef p2sum
#undef psum
#undef Nsum
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  /* Label for restoring  neutron */
  mcabsorbCompdetector_all:
  if (RESTORE) /* restore if needed */
  { RESTORE_NEUTRON(32,
      mcnlx,
      mcnly,
      mcnlz,
      mcnlvx,
      mcnlvy,
      mcnlvz,
      mcnlt,
      mcnlsx,
      mcnlsy,
      mcnlsz,
      mcnlp); }
#undef mcabsorbComp
#undef p
#undef sz
#undef sy
#undef sx
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)

  mcabsorbAll:
  mcDEBUG_LEAVE()
  mcDEBUG_STATE(
mcnlx,
mcnly,
mcnlz,
mcnlvx,
mcnlvy,
mcnlvz,
mcnlt,
mcnlsx,
mcnlsy,
mcnlsz,
mcnlp)
  /* Copy neutron state to global variables. */
  mcnx = mcnlx;
  mcny = mcnly;
  mcnz = mcnlz;
  mcnvx = mcnlvx;
  mcnvy = mcnlvy;
  mcnvz = mcnlvz;
  mcnt = mcnlt;
  mcnsx = mcnlsx;
  mcnsy = mcnlsy;
  mcnsz = mcnlsz;
  mcnp = mcnlp;

} /* end trace */

void mcsave(FILE *handle) {
  if (!handle) mcsiminfo_init(NULL);
  /* User component SAVE code. */

  /* User SAVE code for component 'Origin'. */
  SIG_MESSAGE("Origin (Save)");
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
{   /* Declarations of Origin=Progress_bar() SETTING parameters. */
char* profile = mccOrigin_profile;
MCNUM percent = mccOrigin_percent;
MCNUM flag_save = mccOrigin_flag_save;
MCNUM minutes = mccOrigin_minutes;
#line 115 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
{
  MPI_MASTER(fprintf(stdout, "\nSave [%s]\n", mcinstrument_name););
  if (profile && strlen(profile) && strcmp(profile,"NULL") && strcmp(profile,"0")) {
    char filename[256];
    if (!strlen(profile) || !strcmp(profile,"NULL") || !strcmp(profile,"0")) strcpy(filename, mcinstrument_name);
    else strcpy(filename, profile);
    DETECTOR_OUT_1D(
        "Intensity profiler",
        "Component index [1]",
        "Intensity",
        "prof", 1, mcNUMCOMP, mcNUMCOMP-1,
        &mcNCounter[1],&mcPCounter[1],&mcP2Counter[1],
        filename);

  }
}
#line 21843 "./ThALES_resolution_v2.c"
}   /* End of Origin=Progress_bar() SETTING parameter declarations. */
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'l_monitor'. */
  SIG_MESSAGE("l_monitor (Save)");
#define mccompcurname  l_monitor
#define mccompcurtype  L_monitor
#define mccompcurindex 13
#define nL mccl_monitor_nL
#define L_N mccl_monitor_L_N
#define L_p mccl_monitor_L_p
#define L_p2 mccl_monitor_L_p2
{   /* Declarations of l_monitor=L_monitor() SETTING parameters. */
char* filename = mccl_monitor_filename;
MCNUM xmin = mccl_monitor_xmin;
MCNUM xmax = mccl_monitor_xmax;
MCNUM ymin = mccl_monitor_ymin;
MCNUM ymax = mccl_monitor_ymax;
MCNUM xwidth = mccl_monitor_xwidth;
MCNUM yheight = mccl_monitor_yheight;
MCNUM Lmin = mccl_monitor_Lmin;
MCNUM Lmax = mccl_monitor_Lmax;
MCNUM restore_neutron = mccl_monitor_restore_neutron;
int nowritefile = mccl_monitor_nowritefile;
#line 107 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/L_monitor.comp"
{
    if (!nowritefile) {
    DETECTOR_OUT_1D(
        "Wavelength monitor",
        "Wavelength [AA]",
        "Intensity",
        "L", Lmin, Lmax, nL,
        &L_N[0],&L_p[0],&L_p2[0],
        filename);
    }
}
#line 21886 "./ThALES_resolution_v2.c"
}   /* End of l_monitor=L_monitor() SETTING parameter declarations. */
#undef L_p2
#undef L_p
#undef L_N
#undef nL
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'E_sample_mon'. */
  SIG_MESSAGE("E_sample_mon (Save)");
#define mccompcurname  E_sample_mon
#define mccompcurtype  E_monitor
#define mccompcurindex 18
#define nE mccE_sample_mon_nE
#define E_N mccE_sample_mon_E_N
#define E_p mccE_sample_mon_E_p
#define E_p2 mccE_sample_mon_E_p2
#define S_p mccE_sample_mon_S_p
#define S_pE mccE_sample_mon_S_pE
#define S_pE2 mccE_sample_mon_S_pE2
{   /* Declarations of E_sample_mon=E_monitor() SETTING parameters. */
char* filename = mccE_sample_mon_filename;
MCNUM xmin = mccE_sample_mon_xmin;
MCNUM xmax = mccE_sample_mon_xmax;
MCNUM ymin = mccE_sample_mon_ymin;
MCNUM ymax = mccE_sample_mon_ymax;
MCNUM xwidth = mccE_sample_mon_xwidth;
MCNUM yheight = mccE_sample_mon_yheight;
MCNUM Emin = mccE_sample_mon_Emin;
MCNUM Emax = mccE_sample_mon_Emax;
MCNUM restore_neutron = mccE_sample_mon_restore_neutron;
int nowritefile = mccE_sample_mon_nowritefile;
#line 117 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/E_monitor.comp"
{
    if (!nowritefile) {
    DETECTOR_OUT_1D(
        "Energy monitor",
        "Energy [meV]",
        "Intensity",
        "E", Emin, Emax, nE,
        &E_N[0],&E_p[0],&E_p2[0],
        filename);
    if (S_p) printf("<E> : %g meV , E-width : %g meV \n",
     S_pE/S_p,sqrt(S_pE2/S_p - S_pE*S_pE/(S_p*S_p)) );
    }
}
#line 21934 "./ThALES_resolution_v2.c"
}   /* End of E_sample_mon=E_monitor() SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef nE
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'PSD_sample_mon'. */
  SIG_MESSAGE("PSD_sample_mon (Save)");
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
{   /* Declarations of PSD_sample_mon=PSD_monitor() SETTING parameters. */
int nx = mccPSD_sample_mon_nx;
int ny = mccPSD_sample_mon_ny;
char* filename = mccPSD_sample_mon_filename;
MCNUM xmin = mccPSD_sample_mon_xmin;
MCNUM xmax = mccPSD_sample_mon_xmax;
MCNUM ymin = mccPSD_sample_mon_ymin;
MCNUM ymax = mccPSD_sample_mon_ymax;
MCNUM xwidth = mccPSD_sample_mon_xwidth;
MCNUM yheight = mccPSD_sample_mon_yheight;
MCNUM restore_neutron = mccPSD_sample_mon_restore_neutron;
int nowritefile = mccPSD_sample_mon_nowritefile;
#line 111 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
if (!nowritefile) {
  DETECTOR_OUT_2D(
    "PSD monitor",
    "X position [cm]",
    "Y position [cm]",
    xmin*100.0, xmax*100.0, ymin*100.0, ymax*100.0,
    nx, ny,
    &PSD_N[0][0],&PSD_p[0][0],&PSD_p2[0][0],
    filename);
}
}
#line 21980 "./ThALES_resolution_v2.c"
}   /* End of PSD_sample_mon=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'PSD_analyzer'. */
  SIG_MESSAGE("PSD_analyzer (Save)");
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
{   /* Declarations of PSD_analyzer=PSD_monitor() SETTING parameters. */
int nx = mccPSD_analyzer_nx;
int ny = mccPSD_analyzer_ny;
char* filename = mccPSD_analyzer_filename;
MCNUM xmin = mccPSD_analyzer_xmin;
MCNUM xmax = mccPSD_analyzer_xmax;
MCNUM ymin = mccPSD_analyzer_ymin;
MCNUM ymax = mccPSD_analyzer_ymax;
MCNUM xwidth = mccPSD_analyzer_xwidth;
MCNUM yheight = mccPSD_analyzer_yheight;
MCNUM restore_neutron = mccPSD_analyzer_restore_neutron;
int nowritefile = mccPSD_analyzer_nowritefile;
#line 111 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
if (!nowritefile) {
  DETECTOR_OUT_2D(
    "PSD monitor",
    "X position [cm]",
    "Y position [cm]",
    xmin*100.0, xmax*100.0, ymin*100.0, ymax*100.0,
    nx, ny,
    &PSD_N[0][0],&PSD_p[0][0],&PSD_p2[0][0],
    filename);
}
}
#line 22022 "./ThALES_resolution_v2.c"
}   /* End of PSD_analyzer=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'PSD_det'. */
  SIG_MESSAGE("PSD_det (Save)");
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
{   /* Declarations of PSD_det=PSD_monitor() SETTING parameters. */
int nx = mccPSD_det_nx;
int ny = mccPSD_det_ny;
char* filename = mccPSD_det_filename;
MCNUM xmin = mccPSD_det_xmin;
MCNUM xmax = mccPSD_det_xmax;
MCNUM ymin = mccPSD_det_ymin;
MCNUM ymax = mccPSD_det_ymax;
MCNUM xwidth = mccPSD_det_xwidth;
MCNUM yheight = mccPSD_det_yheight;
MCNUM restore_neutron = mccPSD_det_restore_neutron;
int nowritefile = mccPSD_det_nowritefile;
#line 111 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
if (!nowritefile) {
  DETECTOR_OUT_2D(
    "PSD monitor",
    "X position [cm]",
    "Y position [cm]",
    xmin*100.0, xmax*100.0, ymin*100.0, ymax*100.0,
    nx, ny,
    &PSD_N[0][0],&PSD_p[0][0],&PSD_p2[0][0],
    filename);
}
}
#line 22064 "./ThALES_resolution_v2.c"
}   /* End of PSD_det=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'res_monitor'. */
  SIG_MESSAGE("res_monitor (Save)");
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
{   /* Declarations of res_monitor=Res_monitor() SETTING parameters. */
char* filename = mccres_monitor_filename;
char* options = mccres_monitor_options;
MCNUM xwidth = mccres_monitor_xwidth;
MCNUM yheight = mccres_monitor_yheight;
MCNUM zdepth = mccres_monitor_zdepth;
MCNUM radius = mccres_monitor_radius;
MCNUM xmin = mccres_monitor_xmin;
MCNUM xmax = mccres_monitor_xmax;
MCNUM ymin = mccres_monitor_ymin;
MCNUM ymax = mccres_monitor_ymax;
MCNUM zmin = mccres_monitor_zmin;
MCNUM zmax = mccres_monitor_zmax;
MCNUM bufsize = mccres_monitor_bufsize;
MCNUM restore_neutron = mccres_monitor_restore_neutron;
#line 207 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
{
  /* save results, but do not free pointers */
  Monitor_nD_Save(&DEFS, &Vars);
}
#line 22102 "./ThALES_resolution_v2.c"
}   /* End of res_monitor=Res_monitor() SETTING parameter declarations. */
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'detector_all'. */
  SIG_MESSAGE("detector_all (Save)");
#define mccompcurname  detector_all
#define mccompcurtype  Monitor
#define mccompcurindex 32
#define Nsum mccdetector_all_Nsum
#define psum mccdetector_all_psum
#define p2sum mccdetector_all_p2sum
{   /* Declarations of detector_all=Monitor() SETTING parameters. */
MCNUM xmin = mccdetector_all_xmin;
MCNUM xmax = mccdetector_all_xmax;
MCNUM ymin = mccdetector_all_ymin;
MCNUM ymax = mccdetector_all_ymax;
MCNUM xwidth = mccdetector_all_xwidth;
MCNUM yheight = mccdetector_all_yheight;
MCNUM restore_neutron = mccdetector_all_restore_neutron;
#line 89 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Monitor.comp"
{
    char title[1024];
    sprintf(title, "Single monitor %s", NAME_CURRENT_COMP);
    DETECTOR_OUT_0D(title, Nsum, psum, p2sum);
}
#line 22134 "./ThALES_resolution_v2.c"
}   /* End of detector_all=Monitor() SETTING parameter declarations. */
#undef p2sum
#undef psum
#undef Nsum
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  if (!handle) mcsiminfo_close(); 
} /* end save */
void mcfinally(void) {
  /* User component FINALLY code. */
  mcsiminfo_init(NULL);
  mcsave(mcsiminfo_file); /* save data when simulation ends */

  /* User FINALLY code for component 'Origin'. */
  SIG_MESSAGE("Origin (Finally)");
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
{   /* Declarations of Origin=Progress_bar() SETTING parameters. */
char* profile = mccOrigin_profile;
MCNUM percent = mccOrigin_percent;
MCNUM flag_save = mccOrigin_flag_save;
MCNUM minutes = mccOrigin_minutes;
#line 133 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
{
  time_t NowTime;
  time(&NowTime);
  fprintf(stdout, "\nFinally [%s: %s]. Time: ", mcinstrument_name, mcdirname ? mcdirname : ".");
  if (difftime(NowTime,StartTime) < 60.0)
    fprintf(stdout, "%g [s] ", difftime(NowTime,StartTime));
  else if (difftime(NowTime,StartTime) > 3600.0)
    fprintf(stdout, "%g [h] ", difftime(NowTime,StartTime)/3660.0);
  else
    fprintf(stdout, "%g [min] ", difftime(NowTime,StartTime)/60.0);
  fprintf(stdout, "\n");
}
#line 22177 "./ThALES_resolution_v2.c"
}   /* End of Origin=Progress_bar() SETTING parameter declarations. */
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[1]) fprintf(stderr, "Warning: No neutron could reach Component[1] Origin\n");
    if (mcAbsorbProp[1]) fprintf(stderr, "Warning: %g events were removed in Component[1] Origin=Progress_bar()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[1]);
  /* User FINALLY code for component 'HCS'. */
  SIG_MESSAGE("HCS (Finally)");
#define mccompcurname  HCS
#define mccompcurtype  Source_gen
#define mccompcurindex 2
#define p_in mccHCS_p_in
#define lambda1 mccHCS_lambda1
#define lambda2 mccHCS_lambda2
#define lambda3 mccHCS_lambda3
#define pTable mccHCS_pTable
#define pTable_x mccHCS_pTable_x
#define pTable_y mccHCS_pTable_y
#define pTable_xmin mccHCS_pTable_xmin
#define pTable_xmax mccHCS_pTable_xmax
#define pTable_xsum mccHCS_pTable_xsum
#define pTable_ymin mccHCS_pTable_ymin
#define pTable_ymax mccHCS_pTable_ymax
#define pTable_ysum mccHCS_pTable_ysum
#define pTable_dxmin mccHCS_pTable_dxmin
#define pTable_dxmax mccHCS_pTable_dxmax
#define pTable_dymin mccHCS_pTable_dymin
#define pTable_dymax mccHCS_pTable_dymax
{   /* Declarations of HCS=Source_gen() SETTING parameters. */
char* flux_file = mccHCS_flux_file;
char* xdiv_file = mccHCS_xdiv_file;
char* ydiv_file = mccHCS_ydiv_file;
MCNUM radius = mccHCS_radius;
MCNUM dist = mccHCS_dist;
MCNUM focus_xw = mccHCS_focus_xw;
MCNUM focus_yh = mccHCS_focus_yh;
MCNUM focus_aw = mccHCS_focus_aw;
MCNUM focus_ah = mccHCS_focus_ah;
MCNUM E0 = mccHCS_E0;
MCNUM dE = mccHCS_dE;
MCNUM lambda0 = mccHCS_lambda0;
MCNUM dlambda = mccHCS_dlambda;
MCNUM I1 = mccHCS_I1;
MCNUM yheight = mccHCS_yheight;
MCNUM xwidth = mccHCS_xwidth;
MCNUM verbose = mccHCS_verbose;
MCNUM T1 = mccHCS_T1;
MCNUM flux_file_perAA = mccHCS_flux_file_perAA;
MCNUM flux_file_log = mccHCS_flux_file_log;
MCNUM Lmin = mccHCS_Lmin;
MCNUM Lmax = mccHCS_Lmax;
MCNUM Emin = mccHCS_Emin;
MCNUM Emax = mccHCS_Emax;
MCNUM T2 = mccHCS_T2;
MCNUM I2 = mccHCS_I2;
MCNUM T3 = mccHCS_T3;
MCNUM I3 = mccHCS_I3;
MCNUM zdepth = mccHCS_zdepth;
int target_index = mccHCS_target_index;
#line 571 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"
{
  Table_Free(&pTable);
  Table_Free(&pTable_x);
  Table_Free(&pTable_y);
}
#line 22248 "./ThALES_resolution_v2.c"
}   /* End of HCS=Source_gen() SETTING parameter declarations. */
#undef pTable_dymax
#undef pTable_dymin
#undef pTable_dxmax
#undef pTable_dxmin
#undef pTable_ysum
#undef pTable_ymax
#undef pTable_ymin
#undef pTable_xsum
#undef pTable_xmax
#undef pTable_xmin
#undef pTable_y
#undef pTable_x
#undef pTable
#undef lambda3
#undef lambda2
#undef lambda1
#undef p_in
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[2]) fprintf(stderr, "Warning: No neutron could reach Component[2] HCS\n");
    if (mcAbsorbProp[2]) fprintf(stderr, "Warning: %g events were removed in Component[2] HCS=Source_gen()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[2]);
    if (!mcNCounter[3]) fprintf(stderr, "Warning: No neutron could reach Component[3] H5\n");
    if (mcAbsorbProp[3]) fprintf(stderr, "Warning: %g events were removed in Component[3] H5=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[3]);
  /* User FINALLY code for component 'H5_rect'. */
  SIG_MESSAGE("H5_rect (Finally)");
#define mccompcurname  H5_rect
#define mccompcurtype  Guide_gravity
#define mccompcurindex 4
#define GVars mccH5_rect_GVars
#define pTable mccH5_rect_pTable
{   /* Declarations of H5_rect=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH5_rect_w1;
MCNUM h1 = mccH5_rect_h1;
MCNUM w2 = mccH5_rect_w2;
MCNUM h2 = mccH5_rect_h2;
MCNUM l = mccH5_rect_l;
MCNUM R0 = mccH5_rect_R0;
MCNUM Qc = mccH5_rect_Qc;
MCNUM alpha = mccH5_rect_alpha;
MCNUM m = mccH5_rect_m;
MCNUM W = mccH5_rect_W;
MCNUM nslit = mccH5_rect_nslit;
MCNUM d = mccH5_rect_d;
MCNUM mleft = mccH5_rect_mleft;
MCNUM mright = mccH5_rect_mright;
MCNUM mtop = mccH5_rect_mtop;
MCNUM mbottom = mccH5_rect_mbottom;
MCNUM nhslit = mccH5_rect_nhslit;
MCNUM G = mccH5_rect_G;
MCNUM aleft = mccH5_rect_aleft;
MCNUM aright = mccH5_rect_aright;
MCNUM atop = mccH5_rect_atop;
MCNUM abottom = mccH5_rect_abottom;
MCNUM wavy = mccH5_rect_wavy;
MCNUM wavy_z = mccH5_rect_wavy_z;
MCNUM wavy_tb = mccH5_rect_wavy_tb;
MCNUM wavy_lr = mccH5_rect_wavy_lr;
MCNUM chamfers = mccH5_rect_chamfers;
MCNUM chamfers_z = mccH5_rect_chamfers_z;
MCNUM chamfers_lr = mccH5_rect_chamfers_lr;
MCNUM chamfers_tb = mccH5_rect_chamfers_tb;
MCNUM nelements = mccH5_rect_nelements;
MCNUM nu = mccH5_rect_nu;
MCNUM phase = mccH5_rect_phase;
char* reflect = mccH5_rect_reflect;
#line 562 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
if (GVars.warnings > 100) {
  fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
  fprintf(stderr,"%s: warning: This message has been repeated %g times\n", GVars.compcurname, GVars.warnings);
}
}
#line 22324 "./ThALES_resolution_v2.c"
}   /* End of H5_rect=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[4]) fprintf(stderr, "Warning: No neutron could reach Component[4] H5_rect\n");
    if (mcAbsorbProp[4]) fprintf(stderr, "Warning: %g events were removed in Component[4] H5_rect=Guide_gravity()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[4]);
    if (!mcNCounter[5]) fprintf(stderr, "Warning: No neutron could reach Component[5] H53_origin\n");
    if (mcAbsorbProp[5]) fprintf(stderr, "Warning: %g events were removed in Component[5] H53_origin=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[5]);
    if (!mcNCounter[6]) fprintf(stderr, "Warning: No neutron could reach Component[6] H53_start\n");
    if (mcAbsorbProp[6]) fprintf(stderr, "Warning: %g events were removed in Component[6] H53_start=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[6]);
  /* User FINALLY code for component 'H53_inpile'. */
  SIG_MESSAGE("H53_inpile (Finally)");
#define mccompcurname  H53_inpile
#define mccompcurtype  Guide_gravity
#define mccompcurindex 7
#define GVars mccH53_inpile_GVars
#define pTable mccH53_inpile_pTable
{   /* Declarations of H53_inpile=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_inpile_w1;
MCNUM h1 = mccH53_inpile_h1;
MCNUM w2 = mccH53_inpile_w2;
MCNUM h2 = mccH53_inpile_h2;
MCNUM l = mccH53_inpile_l;
MCNUM R0 = mccH53_inpile_R0;
MCNUM Qc = mccH53_inpile_Qc;
MCNUM alpha = mccH53_inpile_alpha;
MCNUM m = mccH53_inpile_m;
MCNUM W = mccH53_inpile_W;
MCNUM nslit = mccH53_inpile_nslit;
MCNUM d = mccH53_inpile_d;
MCNUM mleft = mccH53_inpile_mleft;
MCNUM mright = mccH53_inpile_mright;
MCNUM mtop = mccH53_inpile_mtop;
MCNUM mbottom = mccH53_inpile_mbottom;
MCNUM nhslit = mccH53_inpile_nhslit;
MCNUM G = mccH53_inpile_G;
MCNUM aleft = mccH53_inpile_aleft;
MCNUM aright = mccH53_inpile_aright;
MCNUM atop = mccH53_inpile_atop;
MCNUM abottom = mccH53_inpile_abottom;
MCNUM wavy = mccH53_inpile_wavy;
MCNUM wavy_z = mccH53_inpile_wavy_z;
MCNUM wavy_tb = mccH53_inpile_wavy_tb;
MCNUM wavy_lr = mccH53_inpile_wavy_lr;
MCNUM chamfers = mccH53_inpile_chamfers;
MCNUM chamfers_z = mccH53_inpile_chamfers_z;
MCNUM chamfers_lr = mccH53_inpile_chamfers_lr;
MCNUM chamfers_tb = mccH53_inpile_chamfers_tb;
MCNUM nelements = mccH53_inpile_nelements;
MCNUM nu = mccH53_inpile_nu;
MCNUM phase = mccH53_inpile_phase;
char* reflect = mccH53_inpile_reflect;
#line 562 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
if (GVars.warnings > 100) {
  fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
  fprintf(stderr,"%s: warning: This message has been repeated %g times\n", GVars.compcurname, GVars.warnings);
}
}
#line 22387 "./ThALES_resolution_v2.c"
}   /* End of H53_inpile=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[7]) fprintf(stderr, "Warning: No neutron could reach Component[7] H53_inpile\n");
    if (mcAbsorbProp[7]) fprintf(stderr, "Warning: %g events were removed in Component[7] H53_inpile=Guide_gravity()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[7]);
  /* User FINALLY code for component 'H53_Obt'. */
  SIG_MESSAGE("H53_Obt (Finally)");
#define mccompcurname  H53_Obt
#define mccompcurtype  Guide_gravity
#define mccompcurindex 8
#define GVars mccH53_Obt_GVars
#define pTable mccH53_Obt_pTable
{   /* Declarations of H53_Obt=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_Obt_w1;
MCNUM h1 = mccH53_Obt_h1;
MCNUM w2 = mccH53_Obt_w2;
MCNUM h2 = mccH53_Obt_h2;
MCNUM l = mccH53_Obt_l;
MCNUM R0 = mccH53_Obt_R0;
MCNUM Qc = mccH53_Obt_Qc;
MCNUM alpha = mccH53_Obt_alpha;
MCNUM m = mccH53_Obt_m;
MCNUM W = mccH53_Obt_W;
MCNUM nslit = mccH53_Obt_nslit;
MCNUM d = mccH53_Obt_d;
MCNUM mleft = mccH53_Obt_mleft;
MCNUM mright = mccH53_Obt_mright;
MCNUM mtop = mccH53_Obt_mtop;
MCNUM mbottom = mccH53_Obt_mbottom;
MCNUM nhslit = mccH53_Obt_nhslit;
MCNUM G = mccH53_Obt_G;
MCNUM aleft = mccH53_Obt_aleft;
MCNUM aright = mccH53_Obt_aright;
MCNUM atop = mccH53_Obt_atop;
MCNUM abottom = mccH53_Obt_abottom;
MCNUM wavy = mccH53_Obt_wavy;
MCNUM wavy_z = mccH53_Obt_wavy_z;
MCNUM wavy_tb = mccH53_Obt_wavy_tb;
MCNUM wavy_lr = mccH53_Obt_wavy_lr;
MCNUM chamfers = mccH53_Obt_chamfers;
MCNUM chamfers_z = mccH53_Obt_chamfers_z;
MCNUM chamfers_lr = mccH53_Obt_chamfers_lr;
MCNUM chamfers_tb = mccH53_Obt_chamfers_tb;
MCNUM nelements = mccH53_Obt_nelements;
MCNUM nu = mccH53_Obt_nu;
MCNUM phase = mccH53_Obt_phase;
char* reflect = mccH53_Obt_reflect;
#line 562 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
if (GVars.warnings > 100) {
  fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
  fprintf(stderr,"%s: warning: This message has been repeated %g times\n", GVars.compcurname, GVars.warnings);
}
}
#line 22446 "./ThALES_resolution_v2.c"
}   /* End of H53_Obt=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[8]) fprintf(stderr, "Warning: No neutron could reach Component[8] H53_Obt\n");
    if (mcAbsorbProp[8]) fprintf(stderr, "Warning: %g events were removed in Component[8] H53_Obt=Guide_gravity()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[8]);
    if (!mcNCounter[9]) fprintf(stderr, "Warning: No neutron could reach Component[9] H53_Obt_Out\n");
    if (mcAbsorbProp[9]) fprintf(stderr, "Warning: %g events were removed in Component[9] H53_Obt_Out=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[9]);
  /* User FINALLY code for component 'H53_VSComC1'. */
  SIG_MESSAGE("H53_VSComC1 (Finally)");
#define mccompcurname  H53_VSComC1
#define mccompcurtype  Guide_gravity
#define mccompcurindex 10
#define GVars mccH53_VSComC1_GVars
#define pTable mccH53_VSComC1_pTable
{   /* Declarations of H53_VSComC1=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_VSComC1_w1;
MCNUM h1 = mccH53_VSComC1_h1;
MCNUM w2 = mccH53_VSComC1_w2;
MCNUM h2 = mccH53_VSComC1_h2;
MCNUM l = mccH53_VSComC1_l;
MCNUM R0 = mccH53_VSComC1_R0;
MCNUM Qc = mccH53_VSComC1_Qc;
MCNUM alpha = mccH53_VSComC1_alpha;
MCNUM m = mccH53_VSComC1_m;
MCNUM W = mccH53_VSComC1_W;
MCNUM nslit = mccH53_VSComC1_nslit;
MCNUM d = mccH53_VSComC1_d;
MCNUM mleft = mccH53_VSComC1_mleft;
MCNUM mright = mccH53_VSComC1_mright;
MCNUM mtop = mccH53_VSComC1_mtop;
MCNUM mbottom = mccH53_VSComC1_mbottom;
MCNUM nhslit = mccH53_VSComC1_nhslit;
MCNUM G = mccH53_VSComC1_G;
MCNUM aleft = mccH53_VSComC1_aleft;
MCNUM aright = mccH53_VSComC1_aright;
MCNUM atop = mccH53_VSComC1_atop;
MCNUM abottom = mccH53_VSComC1_abottom;
MCNUM wavy = mccH53_VSComC1_wavy;
MCNUM wavy_z = mccH53_VSComC1_wavy_z;
MCNUM wavy_tb = mccH53_VSComC1_wavy_tb;
MCNUM wavy_lr = mccH53_VSComC1_wavy_lr;
MCNUM chamfers = mccH53_VSComC1_chamfers;
MCNUM chamfers_z = mccH53_VSComC1_chamfers_z;
MCNUM chamfers_lr = mccH53_VSComC1_chamfers_lr;
MCNUM chamfers_tb = mccH53_VSComC1_chamfers_tb;
MCNUM nelements = mccH53_VSComC1_nelements;
MCNUM nu = mccH53_VSComC1_nu;
MCNUM phase = mccH53_VSComC1_phase;
char* reflect = mccH53_VSComC1_reflect;
#line 562 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{
if (GVars.warnings > 100) {
  fprintf(stderr,"%s: warning: neutron has entered guide, but can not exit !\n", GVars.compcurname);
  fprintf(stderr,"%s: warning: This message has been repeated %g times\n", GVars.compcurname, GVars.warnings);
}
}
#line 22507 "./ThALES_resolution_v2.c"
}   /* End of H53_VSComC1=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[10]) fprintf(stderr, "Warning: No neutron could reach Component[10] H53_VSComC1\n");
    if (mcAbsorbProp[10]) fprintf(stderr, "Warning: %g events were removed in Component[10] H53_VSComC1=Guide_gravity()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[10]);
  /* User FINALLY code for component 'H53_Nose'. */
  SIG_MESSAGE("H53_Nose (Finally)");
#define mccompcurname  H53_Nose
#define mccompcurtype  Guide_tapering
#define mccompcurindex 11
#define w1c mccH53_Nose_w1c
#define w2c mccH53_Nose_w2c
#define ww mccH53_Nose_ww
#define hh mccH53_Nose_hh
#define whalf mccH53_Nose_whalf
#define hhalf mccH53_Nose_hhalf
#define lwhalf mccH53_Nose_lwhalf
#define lhhalf mccH53_Nose_lhhalf
#define h1_in mccH53_Nose_h1_in
#define h2_out mccH53_Nose_h2_out
#define w1_in mccH53_Nose_w1_in
#define w2_out mccH53_Nose_w2_out
#define l_seg mccH53_Nose_l_seg
#define seg mccH53_Nose_seg
#define h12 mccH53_Nose_h12
#define h2 mccH53_Nose_h2
#define w12 mccH53_Nose_w12
#define w2 mccH53_Nose_w2
#define a_ell_q mccH53_Nose_a_ell_q
#define b_ell_q mccH53_Nose_b_ell_q
#define lbw mccH53_Nose_lbw
#define lbh mccH53_Nose_lbh
#define mxi mccH53_Nose_mxi
#define u1 mccH53_Nose_u1
#define u2 mccH53_Nose_u2
#define div1 mccH53_Nose_div1
#define p2_para mccH53_Nose_p2_para
#define test mccH53_Nose_test
#define Div1 mccH53_Nose_Div1
#define i mccH53_Nose_i
#define ii mccH53_Nose_ii
#define seg mccH53_Nose_seg
#define fu mccH53_Nose_fu
#define pos mccH53_Nose_pos
#define file_name mccH53_Nose_file_name
#define ep mccH53_Nose_ep
#define num mccH53_Nose_num
#define rotation_h mccH53_Nose_rotation_h
#define rotation_v mccH53_Nose_rotation_v
{   /* Declarations of H53_Nose=Guide_tapering() SETTING parameters. */
char* option = mccH53_Nose_option;
MCNUM w1 = mccH53_Nose_w1;
MCNUM h1 = mccH53_Nose_h1;
MCNUM l = mccH53_Nose_l;
MCNUM linw = mccH53_Nose_linw;
MCNUM loutw = mccH53_Nose_loutw;
MCNUM linh = mccH53_Nose_linh;
MCNUM louth = mccH53_Nose_louth;
MCNUM R0 = mccH53_Nose_R0;
MCNUM Qcx = mccH53_Nose_Qcx;
MCNUM Qcy = mccH53_Nose_Qcy;
MCNUM alphax = mccH53_Nose_alphax;
MCNUM alphay = mccH53_Nose_alphay;
MCNUM W = mccH53_Nose_W;
MCNUM mx = mccH53_Nose_mx;
MCNUM my = mccH53_Nose_my;
MCNUM segno = mccH53_Nose_segno;
MCNUM curvature = mccH53_Nose_curvature;
MCNUM curvature_v = mccH53_Nose_curvature_v;
#line 609 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"
{
  free(w1c);
  free(w2c);
  free(ww);
  free(hh);
  free(whalf);
  free(hhalf);
  free(lwhalf);
  free(lhhalf);
  free(h1_in);
  free(h2_out);
  free(w1_in);
  free(w2_out);
}
#line 22596 "./ThALES_resolution_v2.c"
}   /* End of H53_Nose=Guide_tapering() SETTING parameter declarations. */
#undef rotation_v
#undef rotation_h
#undef num
#undef ep
#undef file_name
#undef pos
#undef fu
#undef seg
#undef ii
#undef i
#undef Div1
#undef test
#undef p2_para
#undef div1
#undef u2
#undef u1
#undef mxi
#undef lbh
#undef lbw
#undef b_ell_q
#undef a_ell_q
#undef w2
#undef w12
#undef h2
#undef h12
#undef seg
#undef l_seg
#undef w2_out
#undef w1_in
#undef h2_out
#undef h1_in
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[11]) fprintf(stderr, "Warning: No neutron could reach Component[11] H53_Nose\n");
    if (mcAbsorbProp[11]) fprintf(stderr, "Warning: %g events were removed in Component[11] H53_Nose=Guide_tapering()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[11]);
    if (!mcNCounter[12]) fprintf(stderr, "Warning: No neutron could reach Component[12] before_monochromator_slit\n");
    if (mcAbsorbProp[12]) fprintf(stderr, "Warning: %g events were removed in Component[12] before_monochromator_slit=Slit()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[12]);
    if (!mcNCounter[13]) fprintf(stderr, "Warning: No neutron could reach Component[13] l_monitor\n");
    if (mcAbsorbProp[13]) fprintf(stderr, "Warning: %g events were removed in Component[13] l_monitor=L_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[13]);
    if (!mcNCounter[14]) fprintf(stderr, "Warning: No neutron could reach Component[14] H53_ThALES_Monochromator_Cradle\n");
    if (mcAbsorbProp[14]) fprintf(stderr, "Warning: %g events were removed in Component[14] H53_ThALES_Monochromator_Cradle=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[14]);
  /* User FINALLY code for component 'H53_ThALES_Monochromator'. */
  SIG_MESSAGE("H53_ThALES_Monochromator (Finally)");
#define mccompcurname  H53_ThALES_Monochromator
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 15
#define mos_rms_y mccH53_ThALES_Monochromator_mos_rms_y
#define mos_rms_z mccH53_ThALES_Monochromator_mos_rms_z
#define mos_rms_max mccH53_ThALES_Monochromator_mos_rms_max
#define mono_Q mccH53_ThALES_Monochromator_mono_Q
#define SlabWidth mccH53_ThALES_Monochromator_SlabWidth
#define SlabHeight mccH53_ThALES_Monochromator_SlabHeight
#define rTable mccH53_ThALES_Monochromator_rTable
#define tTable mccH53_ThALES_Monochromator_tTable
#define row mccH53_ThALES_Monochromator_row
#define col mccH53_ThALES_Monochromator_col
#define tiltH mccH53_ThALES_Monochromator_tiltH
#define tiltV mccH53_ThALES_Monochromator_tiltV
{   /* Declarations of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameters. */
char* reflect = mccH53_ThALES_Monochromator_reflect;
char* transmit = mccH53_ThALES_Monochromator_transmit;
MCNUM zwidth = mccH53_ThALES_Monochromator_zwidth;
MCNUM yheight = mccH53_ThALES_Monochromator_yheight;
MCNUM gap = mccH53_ThALES_Monochromator_gap;
MCNUM NH = mccH53_ThALES_Monochromator_NH;
MCNUM NV = mccH53_ThALES_Monochromator_NV;
MCNUM mosaich = mccH53_ThALES_Monochromator_mosaich;
MCNUM mosaicv = mccH53_ThALES_Monochromator_mosaicv;
MCNUM r0 = mccH53_ThALES_Monochromator_r0;
MCNUM t0 = mccH53_ThALES_Monochromator_t0;
MCNUM Q = mccH53_ThALES_Monochromator_Q;
MCNUM RV = mccH53_ThALES_Monochromator_RV;
MCNUM RH = mccH53_ThALES_Monochromator_RH;
MCNUM DM = mccH53_ThALES_Monochromator_DM;
MCNUM mosaic = mccH53_ThALES_Monochromator_mosaic;
MCNUM width = mccH53_ThALES_Monochromator_width;
MCNUM height = mccH53_ThALES_Monochromator_height;
MCNUM verbose = mccH53_ThALES_Monochromator_verbose;
MCNUM order = mccH53_ThALES_Monochromator_order;
#line 460 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  Table_Free(&rTable);
  Table_Free(&tTable);
  if (tiltH) free(tiltH);
  if (tiltV) free(tiltV);
}
#line 22694 "./ThALES_resolution_v2.c"
}   /* End of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[15]) fprintf(stderr, "Warning: No neutron could reach Component[15] H53_ThALES_Monochromator\n");
    if (mcAbsorbProp[15]) fprintf(stderr, "Warning: %g events were removed in Component[15] H53_ThALES_Monochromator=Monochromator_curved()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[15]);
    if (!mcNCounter[16]) fprintf(stderr, "Warning: No neutron could reach Component[16] H53_ThALES_Monochromator_Out\n");
    if (mcAbsorbProp[16]) fprintf(stderr, "Warning: %g events were removed in Component[16] H53_ThALES_Monochromator_Out=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[16]);
    if (!mcNCounter[17]) fprintf(stderr, "Warning: No neutron could reach Component[17] before_sample_slit\n");
    if (mcAbsorbProp[17]) fprintf(stderr, "Warning: %g events were removed in Component[17] before_sample_slit=Slit()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[17]);
    if (!mcNCounter[18]) fprintf(stderr, "Warning: No neutron could reach Component[18] E_sample_mon\n");
    if (mcAbsorbProp[18]) fprintf(stderr, "Warning: %g events were removed in Component[18] E_sample_mon=E_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[18]);
  /* User FINALLY code for component 'PSD_sample_mon'. */
  SIG_MESSAGE("PSD_sample_mon (Finally)");
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
{   /* Declarations of PSD_sample_mon=PSD_monitor() SETTING parameters. */
int nx = mccPSD_sample_mon_nx;
int ny = mccPSD_sample_mon_ny;
char* filename = mccPSD_sample_mon_filename;
MCNUM xmin = mccPSD_sample_mon_xmin;
MCNUM xmax = mccPSD_sample_mon_xmax;
MCNUM ymin = mccPSD_sample_mon_ymin;
MCNUM ymax = mccPSD_sample_mon_ymax;
MCNUM xwidth = mccPSD_sample_mon_xwidth;
MCNUM yheight = mccPSD_sample_mon_yheight;
MCNUM restore_neutron = mccPSD_sample_mon_restore_neutron;
int nowritefile = mccPSD_sample_mon_nowritefile;
#line 125 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  destroy_darr2d(PSD_N);
  destroy_darr2d(PSD_p);
  destroy_darr2d(PSD_p2);
}
#line 22746 "./ThALES_resolution_v2.c"
}   /* End of PSD_sample_mon=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[19]) fprintf(stderr, "Warning: No neutron could reach Component[19] PSD_sample_mon\n");
    if (mcAbsorbProp[19]) fprintf(stderr, "Warning: %g events were removed in Component[19] PSD_sample_mon=PSD_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[19]);
    if (!mcNCounter[20]) fprintf(stderr, "Warning: No neutron could reach Component[20] sample_arm\n");
    if (mcAbsorbProp[20]) fprintf(stderr, "Warning: %g events were removed in Component[20] sample_arm=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[20]);
    if (!mcNCounter[21]) fprintf(stderr, "Warning: No neutron could reach Component[21] res_sample\n");
    if (mcAbsorbProp[21]) fprintf(stderr, "Warning: %g events were removed in Component[21] res_sample=Res_sample()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[21]);
    if (!mcNCounter[22]) fprintf(stderr, "Warning: No neutron could reach Component[22] v_sample\n");
    if (mcAbsorbProp[22]) fprintf(stderr, "Warning: %g events were removed in Component[22] v_sample=V_sample()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[22]);
    if (!mcNCounter[23]) fprintf(stderr, "Warning: No neutron could reach Component[23] Sample_Out\n");
    if (mcAbsorbProp[23]) fprintf(stderr, "Warning: %g events were removed in Component[23] Sample_Out=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[23]);
    if (!mcNCounter[24]) fprintf(stderr, "Warning: No neutron could reach Component[24] after_sample_slit\n");
    if (mcAbsorbProp[24]) fprintf(stderr, "Warning: %g events were removed in Component[24] after_sample_slit=Slit()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[24]);
    if (!mcNCounter[25]) fprintf(stderr, "Warning: No neutron could reach Component[25] Ana_Cradle\n");
    if (mcAbsorbProp[25]) fprintf(stderr, "Warning: %g events were removed in Component[25] Ana_Cradle=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[25]);
  /* User FINALLY code for component 'PSD_analyzer'. */
  SIG_MESSAGE("PSD_analyzer (Finally)");
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
{   /* Declarations of PSD_analyzer=PSD_monitor() SETTING parameters. */
int nx = mccPSD_analyzer_nx;
int ny = mccPSD_analyzer_ny;
char* filename = mccPSD_analyzer_filename;
MCNUM xmin = mccPSD_analyzer_xmin;
MCNUM xmax = mccPSD_analyzer_xmax;
MCNUM ymin = mccPSD_analyzer_ymin;
MCNUM ymax = mccPSD_analyzer_ymax;
MCNUM xwidth = mccPSD_analyzer_xwidth;
MCNUM yheight = mccPSD_analyzer_yheight;
MCNUM restore_neutron = mccPSD_analyzer_restore_neutron;
int nowritefile = mccPSD_analyzer_nowritefile;
#line 125 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  destroy_darr2d(PSD_N);
  destroy_darr2d(PSD_p);
  destroy_darr2d(PSD_p2);
}
#line 22795 "./ThALES_resolution_v2.c"
}   /* End of PSD_analyzer=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[26]) fprintf(stderr, "Warning: No neutron could reach Component[26] PSD_analyzer\n");
    if (mcAbsorbProp[26]) fprintf(stderr, "Warning: %g events were removed in Component[26] PSD_analyzer=PSD_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[26]);
  /* User FINALLY code for component 'analyzer'. */
  SIG_MESSAGE("analyzer (Finally)");
#define mccompcurname  analyzer
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 27
#define mos_rms_y mccanalyzer_mos_rms_y
#define mos_rms_z mccanalyzer_mos_rms_z
#define mos_rms_max mccanalyzer_mos_rms_max
#define mono_Q mccanalyzer_mono_Q
#define SlabWidth mccanalyzer_SlabWidth
#define SlabHeight mccanalyzer_SlabHeight
#define rTable mccanalyzer_rTable
#define tTable mccanalyzer_tTable
#define row mccanalyzer_row
#define col mccanalyzer_col
#define tiltH mccanalyzer_tiltH
#define tiltV mccanalyzer_tiltV
{   /* Declarations of analyzer=Monochromator_curved() SETTING parameters. */
char* reflect = mccanalyzer_reflect;
char* transmit = mccanalyzer_transmit;
MCNUM zwidth = mccanalyzer_zwidth;
MCNUM yheight = mccanalyzer_yheight;
MCNUM gap = mccanalyzer_gap;
MCNUM NH = mccanalyzer_NH;
MCNUM NV = mccanalyzer_NV;
MCNUM mosaich = mccanalyzer_mosaich;
MCNUM mosaicv = mccanalyzer_mosaicv;
MCNUM r0 = mccanalyzer_r0;
MCNUM t0 = mccanalyzer_t0;
MCNUM Q = mccanalyzer_Q;
MCNUM RV = mccanalyzer_RV;
MCNUM RH = mccanalyzer_RH;
MCNUM DM = mccanalyzer_DM;
MCNUM mosaic = mccanalyzer_mosaic;
MCNUM width = mccanalyzer_width;
MCNUM height = mccanalyzer_height;
MCNUM verbose = mccanalyzer_verbose;
MCNUM order = mccanalyzer_order;
#line 460 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  Table_Free(&rTable);
  Table_Free(&tTable);
  if (tiltH) free(tiltH);
  if (tiltV) free(tiltV);
}
#line 22851 "./ThALES_resolution_v2.c"
}   /* End of analyzer=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[27]) fprintf(stderr, "Warning: No neutron could reach Component[27] analyzer\n");
    if (mcAbsorbProp[27]) fprintf(stderr, "Warning: %g events were removed in Component[27] analyzer=Monochromator_curved()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[27]);
    if (!mcNCounter[28]) fprintf(stderr, "Warning: No neutron could reach Component[28] Ana_Out\n");
    if (mcAbsorbProp[28]) fprintf(stderr, "Warning: %g events were removed in Component[28] Ana_Out=Arm()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[28]);
    if (!mcNCounter[29]) fprintf(stderr, "Warning: No neutron could reach Component[29] slit\n");
    if (mcAbsorbProp[29]) fprintf(stderr, "Warning: %g events were removed in Component[29] slit=Slit()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[29]);
  /* User FINALLY code for component 'PSD_det'. */
  SIG_MESSAGE("PSD_det (Finally)");
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
{   /* Declarations of PSD_det=PSD_monitor() SETTING parameters. */
int nx = mccPSD_det_nx;
int ny = mccPSD_det_ny;
char* filename = mccPSD_det_filename;
MCNUM xmin = mccPSD_det_xmin;
MCNUM xmax = mccPSD_det_xmax;
MCNUM ymin = mccPSD_det_ymin;
MCNUM ymax = mccPSD_det_ymax;
MCNUM xwidth = mccPSD_det_xwidth;
MCNUM yheight = mccPSD_det_yheight;
MCNUM restore_neutron = mccPSD_det_restore_neutron;
int nowritefile = mccPSD_det_nowritefile;
#line 125 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  destroy_darr2d(PSD_N);
  destroy_darr2d(PSD_p);
  destroy_darr2d(PSD_p2);
}
#line 22901 "./ThALES_resolution_v2.c"
}   /* End of PSD_det=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[30]) fprintf(stderr, "Warning: No neutron could reach Component[30] PSD_det\n");
    if (mcAbsorbProp[30]) fprintf(stderr, "Warning: %g events were removed in Component[30] PSD_det=PSD_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[30]);
  /* User FINALLY code for component 'res_monitor'. */
  SIG_MESSAGE("res_monitor (Finally)");
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
{   /* Declarations of res_monitor=Res_monitor() SETTING parameters. */
char* filename = mccres_monitor_filename;
char* options = mccres_monitor_options;
MCNUM xwidth = mccres_monitor_xwidth;
MCNUM yheight = mccres_monitor_yheight;
MCNUM zdepth = mccres_monitor_zdepth;
MCNUM radius = mccres_monitor_radius;
MCNUM xmin = mccres_monitor_xmin;
MCNUM xmax = mccres_monitor_xmax;
MCNUM ymin = mccres_monitor_ymin;
MCNUM ymax = mccres_monitor_ymax;
MCNUM zmin = mccres_monitor_zmin;
MCNUM zmax = mccres_monitor_zmax;
MCNUM bufsize = mccres_monitor_bufsize;
MCNUM restore_neutron = mccres_monitor_restore_neutron;
#line 213 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
{

  /* free pointers */
  Monitor_nD_Finally(&DEFS, &Vars);

}
#line 22943 "./ThALES_resolution_v2.c"
}   /* End of res_monitor=Res_monitor() SETTING parameter declarations. */
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[31]) fprintf(stderr, "Warning: No neutron could reach Component[31] res_monitor\n");
    if (mcAbsorbProp[31]) fprintf(stderr, "Warning: %g events were removed in Component[31] res_monitor=Res_monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[31]);
    if (!mcNCounter[32]) fprintf(stderr, "Warning: No neutron could reach Component[32] detector_all\n");
    if (mcAbsorbProp[32]) fprintf(stderr, "Warning: %g events were removed in Component[32] detector_all=Monitor()\n"
"         (negative time, miss next components, rounding errors, Nan, Inf).\n", mcAbsorbProp[32]);
  mcsiminfo_close(); 
} /* end finally */
#define magnify mcdis_magnify
#define line mcdis_line
#define dashed_line mcdis_dashed_line
#define multiline mcdis_multiline
#define rectangle mcdis_rectangle
#define box mcdis_box
#define circle mcdis_circle
#define cylinder mcdis_cylinder
#define sphere mcdis_sphere
void mcdisplay(void) {
  printf("MCDISPLAY: start\n");
  /* Components MCDISPLAY code. */

  /* MCDISPLAY code for component 'Origin'. */
  SIG_MESSAGE("Origin (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Origin");
#define mccompcurname  Origin
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define IntermediateCnts mccOrigin_IntermediateCnts
#define StartTime mccOrigin_StartTime
#define EndTime mccOrigin_EndTime
#define CurrentTime mccOrigin_CurrentTime
{   /* Declarations of Origin=Progress_bar() SETTING parameters. */
char* profile = mccOrigin_profile;
MCNUM percent = mccOrigin_percent;
MCNUM flag_save = mccOrigin_flag_save;
MCNUM minutes = mccOrigin_minutes;
#line 147 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../misc/Progress_bar.comp"
{
  
}
#line 22991 "./ThALES_resolution_v2.c"
}   /* End of Origin=Progress_bar() SETTING parameter declarations. */
#undef CurrentTime
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'HCS'. */
  SIG_MESSAGE("HCS (McDisplay)");
  printf("MCDISPLAY: component %s\n", "HCS");
#define mccompcurname  HCS
#define mccompcurtype  Source_gen
#define mccompcurindex 2
#define p_in mccHCS_p_in
#define lambda1 mccHCS_lambda1
#define lambda2 mccHCS_lambda2
#define lambda3 mccHCS_lambda3
#define pTable mccHCS_pTable
#define pTable_x mccHCS_pTable_x
#define pTable_y mccHCS_pTable_y
#define pTable_xmin mccHCS_pTable_xmin
#define pTable_xmax mccHCS_pTable_xmax
#define pTable_xsum mccHCS_pTable_xsum
#define pTable_ymin mccHCS_pTable_ymin
#define pTable_ymax mccHCS_pTable_ymax
#define pTable_ysum mccHCS_pTable_ysum
#define pTable_dxmin mccHCS_pTable_dxmin
#define pTable_dxmax mccHCS_pTable_dxmax
#define pTable_dymin mccHCS_pTable_dymin
#define pTable_dymax mccHCS_pTable_dymax
{   /* Declarations of HCS=Source_gen() SETTING parameters. */
char* flux_file = mccHCS_flux_file;
char* xdiv_file = mccHCS_xdiv_file;
char* ydiv_file = mccHCS_ydiv_file;
MCNUM radius = mccHCS_radius;
MCNUM dist = mccHCS_dist;
MCNUM focus_xw = mccHCS_focus_xw;
MCNUM focus_yh = mccHCS_focus_yh;
MCNUM focus_aw = mccHCS_focus_aw;
MCNUM focus_ah = mccHCS_focus_ah;
MCNUM E0 = mccHCS_E0;
MCNUM dE = mccHCS_dE;
MCNUM lambda0 = mccHCS_lambda0;
MCNUM dlambda = mccHCS_dlambda;
MCNUM I1 = mccHCS_I1;
MCNUM yheight = mccHCS_yheight;
MCNUM xwidth = mccHCS_xwidth;
MCNUM verbose = mccHCS_verbose;
MCNUM T1 = mccHCS_T1;
MCNUM flux_file_perAA = mccHCS_flux_file_perAA;
MCNUM flux_file_log = mccHCS_flux_file_log;
MCNUM Lmin = mccHCS_Lmin;
MCNUM Lmax = mccHCS_Lmax;
MCNUM Emin = mccHCS_Emin;
MCNUM Emax = mccHCS_Emax;
MCNUM T2 = mccHCS_T2;
MCNUM I2 = mccHCS_I2;
MCNUM T3 = mccHCS_T3;
MCNUM I3 = mccHCS_I3;
MCNUM zdepth = mccHCS_zdepth;
int target_index = mccHCS_target_index;
#line 578 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../sources/Source_gen.comp"
{
  double xmin;
  double xmax;
  double ymin;
  double ymax;

  if (radius)
  {
    
    circle("xy",0,0,0,radius);
    if (zdepth) {
      circle("xy",0,0,-zdepth/2,radius);
      circle("xy",0,0, zdepth/2,radius);
    }
  }
  else
  {
    xmin = -xwidth/2; xmax = xwidth/2;
    ymin = -yheight/2; ymax = yheight/2;

    
    multiline(5, (double)xmin, (double)ymin, 0.0,
             (double)xmax, (double)ymin, 0.0,
             (double)xmax, (double)ymax, 0.0,
             (double)xmin, (double)ymax, 0.0,
             (double)xmin, (double)ymin, 0.0);
    if (zdepth) {
      multiline(5, (double)xmin, (double)ymin, -zdepth/2,
             (double)xmax, (double)ymin, -zdepth/2,
             (double)xmax, (double)ymax, -zdepth/2,
             (double)xmin, (double)ymax, -zdepth/2,
             (double)xmin, (double)ymin, -zdepth/2);
      multiline(5, (double)xmin, (double)ymin, zdepth/2,
             (double)xmax, (double)ymin, zdepth/2,
             (double)xmax, (double)ymax, zdepth/2,
             (double)xmin, (double)ymax, zdepth/2,
             (double)xmin, (double)ymin, zdepth/2);
    }
  }
  if (dist) {
    if (focus_aw) focus_xw=dist*tan(focus_aw*DEG2RAD);
    if (focus_ah) focus_yh=dist*tan(focus_ah*DEG2RAD);
    dashed_line(0,0,0, -focus_xw/2,-focus_yh/2,dist, 4);
    dashed_line(0,0,0,  focus_xw/2,-focus_yh/2,dist, 4);
    dashed_line(0,0,0,  focus_xw/2, focus_yh/2,dist, 4);
    dashed_line(0,0,0, -focus_xw/2, focus_yh/2,dist, 4);
  }
}
#line 23104 "./ThALES_resolution_v2.c"
}   /* End of HCS=Source_gen() SETTING parameter declarations. */
#undef pTable_dymax
#undef pTable_dymin
#undef pTable_dxmax
#undef pTable_dxmin
#undef pTable_ysum
#undef pTable_ymax
#undef pTable_ymin
#undef pTable_xsum
#undef pTable_xmax
#undef pTable_xmin
#undef pTable_y
#undef pTable_x
#undef pTable
#undef lambda3
#undef lambda2
#undef lambda1
#undef p_in
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H5'. */
  SIG_MESSAGE("H5 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H5");
#define mccompcurname  H5
#define mccompcurtype  Arm
#define mccompcurindex 3
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 23141 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H5_rect'. */
  SIG_MESSAGE("H5_rect (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H5_rect");
#define mccompcurname  H5_rect
#define mccompcurtype  Guide_gravity
#define mccompcurindex 4
#define GVars mccH5_rect_GVars
#define pTable mccH5_rect_pTable
{   /* Declarations of H5_rect=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH5_rect_w1;
MCNUM h1 = mccH5_rect_h1;
MCNUM w2 = mccH5_rect_w2;
MCNUM h2 = mccH5_rect_h2;
MCNUM l = mccH5_rect_l;
MCNUM R0 = mccH5_rect_R0;
MCNUM Qc = mccH5_rect_Qc;
MCNUM alpha = mccH5_rect_alpha;
MCNUM m = mccH5_rect_m;
MCNUM W = mccH5_rect_W;
MCNUM nslit = mccH5_rect_nslit;
MCNUM d = mccH5_rect_d;
MCNUM mleft = mccH5_rect_mleft;
MCNUM mright = mccH5_rect_mright;
MCNUM mtop = mccH5_rect_mtop;
MCNUM mbottom = mccH5_rect_mbottom;
MCNUM nhslit = mccH5_rect_nhslit;
MCNUM G = mccH5_rect_G;
MCNUM aleft = mccH5_rect_aleft;
MCNUM aright = mccH5_rect_aright;
MCNUM atop = mccH5_rect_atop;
MCNUM abottom = mccH5_rect_abottom;
MCNUM wavy = mccH5_rect_wavy;
MCNUM wavy_z = mccH5_rect_wavy_z;
MCNUM wavy_tb = mccH5_rect_wavy_tb;
MCNUM wavy_lr = mccH5_rect_wavy_lr;
MCNUM chamfers = mccH5_rect_chamfers;
MCNUM chamfers_z = mccH5_rect_chamfers_z;
MCNUM chamfers_lr = mccH5_rect_chamfers_lr;
MCNUM chamfers_tb = mccH5_rect_chamfers_tb;
MCNUM nelements = mccH5_rect_nelements;
MCNUM nu = mccH5_rect_nu;
MCNUM phase = mccH5_rect_phase;
char* reflect = mccH5_rect_reflect;
#line 571 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{

  if (l > 0 && nelements > 0) {
    int i,j,n;
    double x1,x2,x3,x4;
    double y1,y2,y3,y4;
    double nel = (nelements > 11 ? 11 : nelements);

    
    for (n=0; n<nel; n++)
    {
      double z0, z1;
      z0 =     n*(l/nel);
      z1 = (n+1)*(l/nel);

      for(j = 0; j < nhslit; j++)
      {
        y1 = j*(GVars.h1c+d)         - h1/2.0;
        y2 = j*(GVars.h2c+d)         - h2/2.0;
        y3 = (j+1)*(GVars.h1c+d) - d - h1/2.0;
        y4 = (j+1)*(GVars.h2c+d) - d - h2/2.0;
        for(i = 0; i < nslit; i++)
        {
          x1 = i*(GVars.w1c+d)         - w1/2.0;
          x2 = i*(GVars.w2c+d)         - w2/2.0;
          x3 = (i+1)*(GVars.w1c+d) - d - w1/2.0;
          x4 = (i+1)*(GVars.w2c+d) - d - w2/2.0;
          multiline(5,
                    x1, y1, z0,
                    x2, y2, z1,
                    x2, y4, z1,
                    x1, y3, z0,
                    x1, y1, z0);
          multiline(5,
                    x3, y1, z0,
                    x4, y2, z1,
                    x4, y4, z1,
                    x3, y3, z0,
                    x3, y1, z0);
        }
        line(-w1/2.0, y1, z0, w1/2.0, y1, z0);
        line(-w2/2.0, y2, z1, w2/2.0, y2, z1);
      }
    }

    if (nu || phase) {
      double radius = sqrt(w1*w1+l*l);
      /* cylinder top/center/bottom  */
      circle("xz", 0,-h1/2,l/2,radius);
      circle("xz", 0,0    ,l/2,radius);
      circle("xz", 0, h1/2,l/2,radius);
    }
  }
  else {
    /* A bit ugly; hard-coded dimensions. */
    
    line(0,0,0,0.2,0,0);
    line(0,0,0,0,0.2,0);
    line(0,0,0,0,0,0.2);
  }

}
#line 23252 "./ThALES_resolution_v2.c"
}   /* End of H5_rect=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_origin'. */
  SIG_MESSAGE("H53_origin (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_origin");
#define mccompcurname  H53_origin
#define mccompcurtype  Arm
#define mccompcurindex 5
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 23274 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_start'. */
  SIG_MESSAGE("H53_start (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_start");
#define mccompcurname  H53_start
#define mccompcurtype  Arm
#define mccompcurindex 6
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 23293 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_inpile'. */
  SIG_MESSAGE("H53_inpile (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_inpile");
#define mccompcurname  H53_inpile
#define mccompcurtype  Guide_gravity
#define mccompcurindex 7
#define GVars mccH53_inpile_GVars
#define pTable mccH53_inpile_pTable
{   /* Declarations of H53_inpile=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_inpile_w1;
MCNUM h1 = mccH53_inpile_h1;
MCNUM w2 = mccH53_inpile_w2;
MCNUM h2 = mccH53_inpile_h2;
MCNUM l = mccH53_inpile_l;
MCNUM R0 = mccH53_inpile_R0;
MCNUM Qc = mccH53_inpile_Qc;
MCNUM alpha = mccH53_inpile_alpha;
MCNUM m = mccH53_inpile_m;
MCNUM W = mccH53_inpile_W;
MCNUM nslit = mccH53_inpile_nslit;
MCNUM d = mccH53_inpile_d;
MCNUM mleft = mccH53_inpile_mleft;
MCNUM mright = mccH53_inpile_mright;
MCNUM mtop = mccH53_inpile_mtop;
MCNUM mbottom = mccH53_inpile_mbottom;
MCNUM nhslit = mccH53_inpile_nhslit;
MCNUM G = mccH53_inpile_G;
MCNUM aleft = mccH53_inpile_aleft;
MCNUM aright = mccH53_inpile_aright;
MCNUM atop = mccH53_inpile_atop;
MCNUM abottom = mccH53_inpile_abottom;
MCNUM wavy = mccH53_inpile_wavy;
MCNUM wavy_z = mccH53_inpile_wavy_z;
MCNUM wavy_tb = mccH53_inpile_wavy_tb;
MCNUM wavy_lr = mccH53_inpile_wavy_lr;
MCNUM chamfers = mccH53_inpile_chamfers;
MCNUM chamfers_z = mccH53_inpile_chamfers_z;
MCNUM chamfers_lr = mccH53_inpile_chamfers_lr;
MCNUM chamfers_tb = mccH53_inpile_chamfers_tb;
MCNUM nelements = mccH53_inpile_nelements;
MCNUM nu = mccH53_inpile_nu;
MCNUM phase = mccH53_inpile_phase;
char* reflect = mccH53_inpile_reflect;
#line 571 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{

  if (l > 0 && nelements > 0) {
    int i,j,n;
    double x1,x2,x3,x4;
    double y1,y2,y3,y4;
    double nel = (nelements > 11 ? 11 : nelements);

    
    for (n=0; n<nel; n++)
    {
      double z0, z1;
      z0 =     n*(l/nel);
      z1 = (n+1)*(l/nel);

      for(j = 0; j < nhslit; j++)
      {
        y1 = j*(GVars.h1c+d)         - h1/2.0;
        y2 = j*(GVars.h2c+d)         - h2/2.0;
        y3 = (j+1)*(GVars.h1c+d) - d - h1/2.0;
        y4 = (j+1)*(GVars.h2c+d) - d - h2/2.0;
        for(i = 0; i < nslit; i++)
        {
          x1 = i*(GVars.w1c+d)         - w1/2.0;
          x2 = i*(GVars.w2c+d)         - w2/2.0;
          x3 = (i+1)*(GVars.w1c+d) - d - w1/2.0;
          x4 = (i+1)*(GVars.w2c+d) - d - w2/2.0;
          multiline(5,
                    x1, y1, z0,
                    x2, y2, z1,
                    x2, y4, z1,
                    x1, y3, z0,
                    x1, y1, z0);
          multiline(5,
                    x3, y1, z0,
                    x4, y2, z1,
                    x4, y4, z1,
                    x3, y3, z0,
                    x3, y1, z0);
        }
        line(-w1/2.0, y1, z0, w1/2.0, y1, z0);
        line(-w2/2.0, y2, z1, w2/2.0, y2, z1);
      }
    }

    if (nu || phase) {
      double radius = sqrt(w1*w1+l*l);
      /* cylinder top/center/bottom  */
      circle("xz", 0,-h1/2,l/2,radius);
      circle("xz", 0,0    ,l/2,radius);
      circle("xz", 0, h1/2,l/2,radius);
    }
  }
  else {
    /* A bit ugly; hard-coded dimensions. */
    
    line(0,0,0,0.2,0,0);
    line(0,0,0,0,0.2,0);
    line(0,0,0,0,0,0.2);
  }

}
#line 23404 "./ThALES_resolution_v2.c"
}   /* End of H53_inpile=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_Obt'. */
  SIG_MESSAGE("H53_Obt (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_Obt");
#define mccompcurname  H53_Obt
#define mccompcurtype  Guide_gravity
#define mccompcurindex 8
#define GVars mccH53_Obt_GVars
#define pTable mccH53_Obt_pTable
{   /* Declarations of H53_Obt=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_Obt_w1;
MCNUM h1 = mccH53_Obt_h1;
MCNUM w2 = mccH53_Obt_w2;
MCNUM h2 = mccH53_Obt_h2;
MCNUM l = mccH53_Obt_l;
MCNUM R0 = mccH53_Obt_R0;
MCNUM Qc = mccH53_Obt_Qc;
MCNUM alpha = mccH53_Obt_alpha;
MCNUM m = mccH53_Obt_m;
MCNUM W = mccH53_Obt_W;
MCNUM nslit = mccH53_Obt_nslit;
MCNUM d = mccH53_Obt_d;
MCNUM mleft = mccH53_Obt_mleft;
MCNUM mright = mccH53_Obt_mright;
MCNUM mtop = mccH53_Obt_mtop;
MCNUM mbottom = mccH53_Obt_mbottom;
MCNUM nhslit = mccH53_Obt_nhslit;
MCNUM G = mccH53_Obt_G;
MCNUM aleft = mccH53_Obt_aleft;
MCNUM aright = mccH53_Obt_aright;
MCNUM atop = mccH53_Obt_atop;
MCNUM abottom = mccH53_Obt_abottom;
MCNUM wavy = mccH53_Obt_wavy;
MCNUM wavy_z = mccH53_Obt_wavy_z;
MCNUM wavy_tb = mccH53_Obt_wavy_tb;
MCNUM wavy_lr = mccH53_Obt_wavy_lr;
MCNUM chamfers = mccH53_Obt_chamfers;
MCNUM chamfers_z = mccH53_Obt_chamfers_z;
MCNUM chamfers_lr = mccH53_Obt_chamfers_lr;
MCNUM chamfers_tb = mccH53_Obt_chamfers_tb;
MCNUM nelements = mccH53_Obt_nelements;
MCNUM nu = mccH53_Obt_nu;
MCNUM phase = mccH53_Obt_phase;
char* reflect = mccH53_Obt_reflect;
#line 571 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{

  if (l > 0 && nelements > 0) {
    int i,j,n;
    double x1,x2,x3,x4;
    double y1,y2,y3,y4;
    double nel = (nelements > 11 ? 11 : nelements);

    
    for (n=0; n<nel; n++)
    {
      double z0, z1;
      z0 =     n*(l/nel);
      z1 = (n+1)*(l/nel);

      for(j = 0; j < nhslit; j++)
      {
        y1 = j*(GVars.h1c+d)         - h1/2.0;
        y2 = j*(GVars.h2c+d)         - h2/2.0;
        y3 = (j+1)*(GVars.h1c+d) - d - h1/2.0;
        y4 = (j+1)*(GVars.h2c+d) - d - h2/2.0;
        for(i = 0; i < nslit; i++)
        {
          x1 = i*(GVars.w1c+d)         - w1/2.0;
          x2 = i*(GVars.w2c+d)         - w2/2.0;
          x3 = (i+1)*(GVars.w1c+d) - d - w1/2.0;
          x4 = (i+1)*(GVars.w2c+d) - d - w2/2.0;
          multiline(5,
                    x1, y1, z0,
                    x2, y2, z1,
                    x2, y4, z1,
                    x1, y3, z0,
                    x1, y1, z0);
          multiline(5,
                    x3, y1, z0,
                    x4, y2, z1,
                    x4, y4, z1,
                    x3, y3, z0,
                    x3, y1, z0);
        }
        line(-w1/2.0, y1, z0, w1/2.0, y1, z0);
        line(-w2/2.0, y2, z1, w2/2.0, y2, z1);
      }
    }

    if (nu || phase) {
      double radius = sqrt(w1*w1+l*l);
      /* cylinder top/center/bottom  */
      circle("xz", 0,-h1/2,l/2,radius);
      circle("xz", 0,0    ,l/2,radius);
      circle("xz", 0, h1/2,l/2,radius);
    }
  }
  else {
    /* A bit ugly; hard-coded dimensions. */
    
    line(0,0,0,0.2,0,0);
    line(0,0,0,0,0.2,0);
    line(0,0,0,0,0,0.2);
  }

}
#line 23518 "./ThALES_resolution_v2.c"
}   /* End of H53_Obt=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_Obt_Out'. */
  SIG_MESSAGE("H53_Obt_Out (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_Obt_Out");
#define mccompcurname  H53_Obt_Out
#define mccompcurtype  Arm
#define mccompcurindex 9
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 23540 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_VSComC1'. */
  SIG_MESSAGE("H53_VSComC1 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_VSComC1");
#define mccompcurname  H53_VSComC1
#define mccompcurtype  Guide_gravity
#define mccompcurindex 10
#define GVars mccH53_VSComC1_GVars
#define pTable mccH53_VSComC1_pTable
{   /* Declarations of H53_VSComC1=Guide_gravity() SETTING parameters. */
MCNUM w1 = mccH53_VSComC1_w1;
MCNUM h1 = mccH53_VSComC1_h1;
MCNUM w2 = mccH53_VSComC1_w2;
MCNUM h2 = mccH53_VSComC1_h2;
MCNUM l = mccH53_VSComC1_l;
MCNUM R0 = mccH53_VSComC1_R0;
MCNUM Qc = mccH53_VSComC1_Qc;
MCNUM alpha = mccH53_VSComC1_alpha;
MCNUM m = mccH53_VSComC1_m;
MCNUM W = mccH53_VSComC1_W;
MCNUM nslit = mccH53_VSComC1_nslit;
MCNUM d = mccH53_VSComC1_d;
MCNUM mleft = mccH53_VSComC1_mleft;
MCNUM mright = mccH53_VSComC1_mright;
MCNUM mtop = mccH53_VSComC1_mtop;
MCNUM mbottom = mccH53_VSComC1_mbottom;
MCNUM nhslit = mccH53_VSComC1_nhslit;
MCNUM G = mccH53_VSComC1_G;
MCNUM aleft = mccH53_VSComC1_aleft;
MCNUM aright = mccH53_VSComC1_aright;
MCNUM atop = mccH53_VSComC1_atop;
MCNUM abottom = mccH53_VSComC1_abottom;
MCNUM wavy = mccH53_VSComC1_wavy;
MCNUM wavy_z = mccH53_VSComC1_wavy_z;
MCNUM wavy_tb = mccH53_VSComC1_wavy_tb;
MCNUM wavy_lr = mccH53_VSComC1_wavy_lr;
MCNUM chamfers = mccH53_VSComC1_chamfers;
MCNUM chamfers_z = mccH53_VSComC1_chamfers_z;
MCNUM chamfers_lr = mccH53_VSComC1_chamfers_lr;
MCNUM chamfers_tb = mccH53_VSComC1_chamfers_tb;
MCNUM nelements = mccH53_VSComC1_nelements;
MCNUM nu = mccH53_VSComC1_nu;
MCNUM phase = mccH53_VSComC1_phase;
char* reflect = mccH53_VSComC1_reflect;
#line 571 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_gravity.comp"
{

  if (l > 0 && nelements > 0) {
    int i,j,n;
    double x1,x2,x3,x4;
    double y1,y2,y3,y4;
    double nel = (nelements > 11 ? 11 : nelements);

    
    for (n=0; n<nel; n++)
    {
      double z0, z1;
      z0 =     n*(l/nel);
      z1 = (n+1)*(l/nel);

      for(j = 0; j < nhslit; j++)
      {
        y1 = j*(GVars.h1c+d)         - h1/2.0;
        y2 = j*(GVars.h2c+d)         - h2/2.0;
        y3 = (j+1)*(GVars.h1c+d) - d - h1/2.0;
        y4 = (j+1)*(GVars.h2c+d) - d - h2/2.0;
        for(i = 0; i < nslit; i++)
        {
          x1 = i*(GVars.w1c+d)         - w1/2.0;
          x2 = i*(GVars.w2c+d)         - w2/2.0;
          x3 = (i+1)*(GVars.w1c+d) - d - w1/2.0;
          x4 = (i+1)*(GVars.w2c+d) - d - w2/2.0;
          multiline(5,
                    x1, y1, z0,
                    x2, y2, z1,
                    x2, y4, z1,
                    x1, y3, z0,
                    x1, y1, z0);
          multiline(5,
                    x3, y1, z0,
                    x4, y2, z1,
                    x4, y4, z1,
                    x3, y3, z0,
                    x3, y1, z0);
        }
        line(-w1/2.0, y1, z0, w1/2.0, y1, z0);
        line(-w2/2.0, y2, z1, w2/2.0, y2, z1);
      }
    }

    if (nu || phase) {
      double radius = sqrt(w1*w1+l*l);
      /* cylinder top/center/bottom  */
      circle("xz", 0,-h1/2,l/2,radius);
      circle("xz", 0,0    ,l/2,radius);
      circle("xz", 0, h1/2,l/2,radius);
    }
  }
  else {
    /* A bit ugly; hard-coded dimensions. */
    
    line(0,0,0,0.2,0,0);
    line(0,0,0,0,0.2,0);
    line(0,0,0,0,0,0.2);
  }

}
#line 23651 "./ThALES_resolution_v2.c"
}   /* End of H53_VSComC1=Guide_gravity() SETTING parameter declarations. */
#undef pTable
#undef GVars
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_Nose'. */
  SIG_MESSAGE("H53_Nose (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_Nose");
#define mccompcurname  H53_Nose
#define mccompcurtype  Guide_tapering
#define mccompcurindex 11
#define w1c mccH53_Nose_w1c
#define w2c mccH53_Nose_w2c
#define ww mccH53_Nose_ww
#define hh mccH53_Nose_hh
#define whalf mccH53_Nose_whalf
#define hhalf mccH53_Nose_hhalf
#define lwhalf mccH53_Nose_lwhalf
#define lhhalf mccH53_Nose_lhhalf
#define h1_in mccH53_Nose_h1_in
#define h2_out mccH53_Nose_h2_out
#define w1_in mccH53_Nose_w1_in
#define w2_out mccH53_Nose_w2_out
#define l_seg mccH53_Nose_l_seg
#define seg mccH53_Nose_seg
#define h12 mccH53_Nose_h12
#define h2 mccH53_Nose_h2
#define w12 mccH53_Nose_w12
#define w2 mccH53_Nose_w2
#define a_ell_q mccH53_Nose_a_ell_q
#define b_ell_q mccH53_Nose_b_ell_q
#define lbw mccH53_Nose_lbw
#define lbh mccH53_Nose_lbh
#define mxi mccH53_Nose_mxi
#define u1 mccH53_Nose_u1
#define u2 mccH53_Nose_u2
#define div1 mccH53_Nose_div1
#define p2_para mccH53_Nose_p2_para
#define test mccH53_Nose_test
#define Div1 mccH53_Nose_Div1
#define i mccH53_Nose_i
#define ii mccH53_Nose_ii
#define seg mccH53_Nose_seg
#define fu mccH53_Nose_fu
#define pos mccH53_Nose_pos
#define file_name mccH53_Nose_file_name
#define ep mccH53_Nose_ep
#define num mccH53_Nose_num
#define rotation_h mccH53_Nose_rotation_h
#define rotation_v mccH53_Nose_rotation_v
{   /* Declarations of H53_Nose=Guide_tapering() SETTING parameters. */
char* option = mccH53_Nose_option;
MCNUM w1 = mccH53_Nose_w1;
MCNUM h1 = mccH53_Nose_h1;
MCNUM l = mccH53_Nose_l;
MCNUM linw = mccH53_Nose_linw;
MCNUM loutw = mccH53_Nose_loutw;
MCNUM linh = mccH53_Nose_linh;
MCNUM louth = mccH53_Nose_louth;
MCNUM R0 = mccH53_Nose_R0;
MCNUM Qcx = mccH53_Nose_Qcx;
MCNUM Qcy = mccH53_Nose_Qcy;
MCNUM alphax = mccH53_Nose_alphax;
MCNUM alphay = mccH53_Nose_alphay;
MCNUM W = mccH53_Nose_W;
MCNUM mx = mccH53_Nose_mx;
MCNUM my = mccH53_Nose_my;
MCNUM segno = mccH53_Nose_segno;
MCNUM curvature = mccH53_Nose_curvature;
MCNUM curvature_v = mccH53_Nose_curvature_v;
#line 625 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Guide_tapering.comp"
{
  double x;
  int i,ii;

  

  for (ii=0; ii < segno; ii++)
  {
     multiline(5,
        -w1_in[ii]/2.0, -h1_in[ii]/2.0,l_seg*(double)ii,
        -w2_out[ii]/2.0, -h2_out[ii]/2.0,l_seg*((double)ii+1.0),
        -w2_out[ii]/2.0,  h2_out[ii]/2.0,l_seg*((double)ii+1.0),
        -w1_in[ii]/2.0,  h1_in[ii]/2.0,l_seg*(double)ii,
        -w1_in[ii]/2.0, -h1_in[ii]/2.0,l_seg*(double)ii);
     multiline(5,
        w1_in[ii]/2.0, -h1_in[ii]/2.0,l_seg*(double)ii,
        w2_out[ii]/2.0, -h2_out[ii]/2.0,l_seg*((double)ii+1.0),
        w2_out[ii]/2.0,  h2_out[ii]/2.0,l_seg*((double)ii+1.0),
        w1_in[ii]/2.0,  h1_in[ii]/2.0,l_seg*(double)ii,
        w1_in[ii]/2.0, -h1_in[ii]/2.0,l_seg*(double)ii);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w1/2.0, h1/2.0, 0.0, w1/2.0, h1/2.0, 0.0);
  for(i=0; i<segno;i++)
  {
     line(-w2_out[i]/2.0, -h2_out[i]/2.0, l_seg*(double)(i+1),
     w2_out[i]/2.0, -h2_out[i]/2.0, l_seg*(double)(i+1));
     line(-w2_out[i]/2.0, h2_out[i]/2.0, l_seg*(double)(i+1),
     w2_out[i]/2.0, h2_out[i]/2.0, l_seg*(double)(i+1));
  }

}
#line 23757 "./ThALES_resolution_v2.c"
}   /* End of H53_Nose=Guide_tapering() SETTING parameter declarations. */
#undef rotation_v
#undef rotation_h
#undef num
#undef ep
#undef file_name
#undef pos
#undef fu
#undef seg
#undef ii
#undef i
#undef Div1
#undef test
#undef p2_para
#undef div1
#undef u2
#undef u1
#undef mxi
#undef lbh
#undef lbw
#undef b_ell_q
#undef a_ell_q
#undef w2
#undef w12
#undef h2
#undef h12
#undef seg
#undef l_seg
#undef w2_out
#undef w1_in
#undef h2_out
#undef h1_in
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'before_monochromator_slit'. */
  SIG_MESSAGE("before_monochromator_slit (McDisplay)");
  printf("MCDISPLAY: component %s\n", "before_monochromator_slit");
#define mccompcurname  before_monochromator_slit
#define mccompcurtype  Slit
#define mccompcurindex 12
{   /* Declarations of before_monochromator_slit=Slit() SETTING parameters. */
MCNUM xmin = mccbefore_monochromator_slit_xmin;
MCNUM xmax = mccbefore_monochromator_slit_xmax;
MCNUM ymin = mccbefore_monochromator_slit_ymin;
MCNUM ymax = mccbefore_monochromator_slit_ymax;
MCNUM radius = mccbefore_monochromator_slit_radius;
MCNUM xwidth = mccbefore_monochromator_slit_xwidth;
MCNUM yheight = mccbefore_monochromator_slit_yheight;
#line 83 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
  
  if (radius == 0) {
    double xw, yh;
    xw = (xmax - xmin)/2.0;
    yh = (ymax - ymin)/2.0;
    multiline(3, xmin-xw, (double)ymax, 0.0,
              (double)xmin, (double)ymax, 0.0,
              (double)xmin, ymax+yh, 0.0);
    multiline(3, xmax+xw, (double)ymax, 0.0,
              (double)xmax, (double)ymax, 0.0,
              (double)xmax, ymax+yh, 0.0);
    multiline(3, xmin-xw, (double)ymin, 0.0,
              (double)xmin, (double)ymin, 0.0,
              (double)xmin, ymin-yh, 0.0);
    multiline(3, xmax+xw, (double)ymin, 0.0,
              (double)xmax, (double)ymin, 0.0,
              (double)xmax, ymin-yh, 0.0);
  } else {
    circle("xy",0,0,0,radius);
  }
}
#line 23839 "./ThALES_resolution_v2.c"
}   /* End of before_monochromator_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'l_monitor'. */
  SIG_MESSAGE("l_monitor (McDisplay)");
  printf("MCDISPLAY: component %s\n", "l_monitor");
#define mccompcurname  l_monitor
#define mccompcurtype  L_monitor
#define mccompcurindex 13
#define nL mccl_monitor_nL
#define L_N mccl_monitor_L_N
#define L_p mccl_monitor_L_p
#define L_p2 mccl_monitor_L_p2
{   /* Declarations of l_monitor=L_monitor() SETTING parameters. */
char* filename = mccl_monitor_filename;
MCNUM xmin = mccl_monitor_xmin;
MCNUM xmax = mccl_monitor_xmax;
MCNUM ymin = mccl_monitor_ymin;
MCNUM ymax = mccl_monitor_ymax;
MCNUM xwidth = mccl_monitor_xwidth;
MCNUM yheight = mccl_monitor_yheight;
MCNUM Lmin = mccl_monitor_Lmin;
MCNUM Lmax = mccl_monitor_Lmax;
MCNUM restore_neutron = mccl_monitor_restore_neutron;
int nowritefile = mccl_monitor_nowritefile;
#line 120 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/L_monitor.comp"
{
  
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 23876 "./ThALES_resolution_v2.c"
}   /* End of l_monitor=L_monitor() SETTING parameter declarations. */
#undef L_p2
#undef L_p
#undef L_N
#undef nL
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_ThALES_Monochromator_Cradle'. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Cradle (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_ThALES_Monochromator_Cradle");
#define mccompcurname  H53_ThALES_Monochromator_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 14
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 23900 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_ThALES_Monochromator'. */
  SIG_MESSAGE("H53_ThALES_Monochromator (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_ThALES_Monochromator");
#define mccompcurname  H53_ThALES_Monochromator
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 15
#define mos_rms_y mccH53_ThALES_Monochromator_mos_rms_y
#define mos_rms_z mccH53_ThALES_Monochromator_mos_rms_z
#define mos_rms_max mccH53_ThALES_Monochromator_mos_rms_max
#define mono_Q mccH53_ThALES_Monochromator_mono_Q
#define SlabWidth mccH53_ThALES_Monochromator_SlabWidth
#define SlabHeight mccH53_ThALES_Monochromator_SlabHeight
#define rTable mccH53_ThALES_Monochromator_rTable
#define tTable mccH53_ThALES_Monochromator_tTable
#define row mccH53_ThALES_Monochromator_row
#define col mccH53_ThALES_Monochromator_col
#define tiltH mccH53_ThALES_Monochromator_tiltH
#define tiltV mccH53_ThALES_Monochromator_tiltV
{   /* Declarations of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameters. */
char* reflect = mccH53_ThALES_Monochromator_reflect;
char* transmit = mccH53_ThALES_Monochromator_transmit;
MCNUM zwidth = mccH53_ThALES_Monochromator_zwidth;
MCNUM yheight = mccH53_ThALES_Monochromator_yheight;
MCNUM gap = mccH53_ThALES_Monochromator_gap;
MCNUM NH = mccH53_ThALES_Monochromator_NH;
MCNUM NV = mccH53_ThALES_Monochromator_NV;
MCNUM mosaich = mccH53_ThALES_Monochromator_mosaich;
MCNUM mosaicv = mccH53_ThALES_Monochromator_mosaicv;
MCNUM r0 = mccH53_ThALES_Monochromator_r0;
MCNUM t0 = mccH53_ThALES_Monochromator_t0;
MCNUM Q = mccH53_ThALES_Monochromator_Q;
MCNUM RV = mccH53_ThALES_Monochromator_RV;
MCNUM RH = mccH53_ThALES_Monochromator_RH;
MCNUM DM = mccH53_ThALES_Monochromator_DM;
MCNUM mosaic = mccH53_ThALES_Monochromator_mosaic;
MCNUM width = mccH53_ThALES_Monochromator_width;
MCNUM height = mccH53_ThALES_Monochromator_height;
MCNUM verbose = mccH53_ThALES_Monochromator_verbose;
MCNUM order = mccH53_ThALES_Monochromator_order;
#line 468 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  int ih;

  for(ih = 0; ih < NH; ih++)
  {
    int iv;
    for(iv = 0; iv < NV; iv++)
    {
      double zmin,zmax,ymin,ymax;
      double xt, yt;

      zmin = (SlabWidth+gap)*(ih-NH/2.0)+gap/2;
      zmax = zmin+SlabWidth;
      ymin = (SlabHeight+gap)*(iv-NV/2.0)+gap/2;
      ymax = ymin+SlabHeight;

      if (RH) xt = -(zmax*zmax - zmin*zmin)/RH/2;
      else    xt = 0;

      if (RV) yt = -(ymax*ymax - ymin*ymin)/RV/2;
      else    yt = 0;
      multiline(5, xt+yt, (double)ymin, (double)zmin,
                   xt-yt, (double)ymax, (double)zmin,
                  -xt-yt, (double)ymax, (double)zmax,
                  -xt+yt, (double)ymin, (double)zmax,
                   xt+yt, (double)ymin, (double)zmin);
     }
   }
}
#line 23974 "./ThALES_resolution_v2.c"
}   /* End of H53_ThALES_Monochromator=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'H53_ThALES_Monochromator_Out'. */
  SIG_MESSAGE("H53_ThALES_Monochromator_Out (McDisplay)");
  printf("MCDISPLAY: component %s\n", "H53_ThALES_Monochromator_Out");
#define mccompcurname  H53_ThALES_Monochromator_Out
#define mccompcurtype  Arm
#define mccompcurindex 16
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 24006 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'before_sample_slit'. */
  SIG_MESSAGE("before_sample_slit (McDisplay)");
  printf("MCDISPLAY: component %s\n", "before_sample_slit");
#define mccompcurname  before_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 17
{   /* Declarations of before_sample_slit=Slit() SETTING parameters. */
MCNUM xmin = mccbefore_sample_slit_xmin;
MCNUM xmax = mccbefore_sample_slit_xmax;
MCNUM ymin = mccbefore_sample_slit_ymin;
MCNUM ymax = mccbefore_sample_slit_ymax;
MCNUM radius = mccbefore_sample_slit_radius;
MCNUM xwidth = mccbefore_sample_slit_xwidth;
MCNUM yheight = mccbefore_sample_slit_yheight;
#line 83 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
  
  if (radius == 0) {
    double xw, yh;
    xw = (xmax - xmin)/2.0;
    yh = (ymax - ymin)/2.0;
    multiline(3, xmin-xw, (double)ymax, 0.0,
              (double)xmin, (double)ymax, 0.0,
              (double)xmin, ymax+yh, 0.0);
    multiline(3, xmax+xw, (double)ymax, 0.0,
              (double)xmax, (double)ymax, 0.0,
              (double)xmax, ymax+yh, 0.0);
    multiline(3, xmin-xw, (double)ymin, 0.0,
              (double)xmin, (double)ymin, 0.0,
              (double)xmin, ymin-yh, 0.0);
    multiline(3, xmax+xw, (double)ymin, 0.0,
              (double)xmax, (double)ymin, 0.0,
              (double)xmax, ymin-yh, 0.0);
  } else {
    circle("xy",0,0,0,radius);
  }
}
#line 24048 "./ThALES_resolution_v2.c"
}   /* End of before_sample_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'E_sample_mon'. */
  SIG_MESSAGE("E_sample_mon (McDisplay)");
  printf("MCDISPLAY: component %s\n", "E_sample_mon");
#define mccompcurname  E_sample_mon
#define mccompcurtype  E_monitor
#define mccompcurindex 18
#define nE mccE_sample_mon_nE
#define E_N mccE_sample_mon_E_N
#define E_p mccE_sample_mon_E_p
#define E_p2 mccE_sample_mon_E_p2
#define S_p mccE_sample_mon_S_p
#define S_pE mccE_sample_mon_S_pE
#define S_pE2 mccE_sample_mon_S_pE2
{   /* Declarations of E_sample_mon=E_monitor() SETTING parameters. */
char* filename = mccE_sample_mon_filename;
MCNUM xmin = mccE_sample_mon_xmin;
MCNUM xmax = mccE_sample_mon_xmax;
MCNUM ymin = mccE_sample_mon_ymin;
MCNUM ymax = mccE_sample_mon_ymax;
MCNUM xwidth = mccE_sample_mon_xwidth;
MCNUM yheight = mccE_sample_mon_yheight;
MCNUM Emin = mccE_sample_mon_Emin;
MCNUM Emax = mccE_sample_mon_Emax;
MCNUM restore_neutron = mccE_sample_mon_restore_neutron;
int nowritefile = mccE_sample_mon_nowritefile;
#line 132 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/E_monitor.comp"
{
  
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 24088 "./ThALES_resolution_v2.c"
}   /* End of E_sample_mon=E_monitor() SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef nE
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'PSD_sample_mon'. */
  SIG_MESSAGE("PSD_sample_mon (McDisplay)");
  printf("MCDISPLAY: component %s\n", "PSD_sample_mon");
#define mccompcurname  PSD_sample_mon
#define mccompcurtype  PSD_monitor
#define mccompcurindex 19
#define PSD_N mccPSD_sample_mon_PSD_N
#define PSD_p mccPSD_sample_mon_PSD_p
#define PSD_p2 mccPSD_sample_mon_PSD_p2
{   /* Declarations of PSD_sample_mon=PSD_monitor() SETTING parameters. */
int nx = mccPSD_sample_mon_nx;
int ny = mccPSD_sample_mon_ny;
char* filename = mccPSD_sample_mon_filename;
MCNUM xmin = mccPSD_sample_mon_xmin;
MCNUM xmax = mccPSD_sample_mon_xmax;
MCNUM ymin = mccPSD_sample_mon_ymin;
MCNUM ymax = mccPSD_sample_mon_ymax;
MCNUM xwidth = mccPSD_sample_mon_xwidth;
MCNUM yheight = mccPSD_sample_mon_yheight;
MCNUM restore_neutron = mccPSD_sample_mon_restore_neutron;
int nowritefile = mccPSD_sample_mon_nowritefile;
#line 132 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  multiline(5,
    (double)xmin, (double)ymin, 0.0,
    (double)xmax, (double)ymin, 0.0,
    (double)xmax, (double)ymax, 0.0,
    (double)xmin, (double)ymax, 0.0,
    (double)xmin, (double)ymin, 0.0);
}
#line 24131 "./ThALES_resolution_v2.c"
}   /* End of PSD_sample_mon=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'sample_arm'. */
  SIG_MESSAGE("sample_arm (McDisplay)");
  printf("MCDISPLAY: component %s\n", "sample_arm");
#define mccompcurname  sample_arm
#define mccompcurtype  Arm
#define mccompcurindex 20
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 24154 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'res_sample'. */
  SIG_MESSAGE("res_sample (McDisplay)");
  printf("MCDISPLAY: component %s\n", "res_sample");
#define mccompcurname  res_sample
#define mccompcurtype  Res_sample
#define mccompcurindex 21
#define res_struct mccres_sample_res_struct
{   /* Declarations of res_sample=Res_sample() SETTING parameters. */
MCNUM thickness = mccres_sample_thickness;
MCNUM radius = mccres_sample_radius;
MCNUM focus_r = mccres_sample_focus_r;
MCNUM E0 = mccres_sample_E0;
MCNUM dE = mccres_sample_dE;
MCNUM target_x = mccres_sample_target_x;
MCNUM target_y = mccres_sample_target_y;
MCNUM target_z = mccres_sample_target_z;
MCNUM focus_xw = mccres_sample_focus_xw;
MCNUM focus_yh = mccres_sample_focus_yh;
MCNUM focus_aw = mccres_sample_focus_aw;
MCNUM focus_ah = mccres_sample_focus_ah;
MCNUM xwidth = mccres_sample_xwidth;
MCNUM yheight = mccres_sample_yheight;
MCNUM zdepth = mccres_sample_zdepth;
int target_index = mccres_sample_target_index;
#line 206 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../samples/Res_sample.comp"
{
  
  if(res_struct.isrect)
  {                             /* Flat sample. */
    double xmin = -0.5*xwidth;
    double xmax =  0.5*xwidth;
    double ymin = -0.5*yheight;
    double ymax =  0.5*yheight;
    double len = zdepth/2;
    multiline(5, xmin, ymin, -len,
                 xmax, ymin, -len,
                 xmax, ymax, -len,
                 xmin, ymax, -len,
                 xmin, ymin, -len);
    multiline(5, xmin, ymin, len,
                 xmax, ymin, len,
                 xmax, ymax, len,
                 xmin, ymax, len,
                 xmin, ymin, len);
    line(xmin, ymin, -len, xmin, ymin, len);
    line(xmax, ymin, -len, xmax, ymin, len);
    line(xmin, ymax, -len, xmin, ymax, len);
    line(xmax, ymax, -len, xmax, ymax, len);
  }
  else
  {
    circle("xz", 0,  yheight/2.0, 0, radius);
    circle("xz", 0, -yheight/2.0, 0, radius);
    line(-radius, -yheight/2.0, 0, -radius, +yheight/2.0, 0);
    line(+radius, -yheight/2.0, 0, +radius, +yheight/2.0, 0);
    line(0, -yheight/2.0, -radius, 0, +yheight/2.0, -radius);
    line(0, -yheight/2.0, +radius, 0, +yheight/2.0, +radius);
    if (thickness) {
      double radius_i=radius-thickness;
      circle("xz", 0,  yheight/2.0, 0, radius_i);
      circle("xz", 0, -yheight/2.0, 0, radius_i);
      line(-radius_i, -yheight/2.0, 0, -radius_i, +yheight/2.0, 0);
      line(+radius_i, -yheight/2.0, 0, +radius_i, +yheight/2.0, 0);
      line(0, -yheight/2.0, -radius_i, 0, +yheight/2.0, -radius_i);
      line(0, -yheight/2.0, +radius_i, 0, +yheight/2.0, +radius_i);
    }
  }
}
#line 24227 "./ThALES_resolution_v2.c"
}   /* End of res_sample=Res_sample() SETTING parameter declarations. */
#undef res_struct
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'v_sample'. */
  SIG_MESSAGE("v_sample (McDisplay)");
  printf("MCDISPLAY: component %s\n", "v_sample");
#define mccompcurname  v_sample
#define mccompcurtype  V_sample
#define mccompcurindex 22
#define VarsV mccv_sample_VarsV
{   /* Declarations of v_sample=V_sample() SETTING parameters. */
MCNUM radius = mccv_sample_radius;
MCNUM thickness = mccv_sample_thickness;
MCNUM zdepth = mccv_sample_zdepth;
MCNUM Vc = mccv_sample_Vc;
MCNUM sigma_abs = mccv_sample_sigma_abs;
MCNUM sigma_inc = mccv_sample_sigma_inc;
MCNUM radius_i = mccv_sample_radius_i;
MCNUM radius_o = mccv_sample_radius_o;
MCNUM h = mccv_sample_h;
MCNUM focus_r = mccv_sample_focus_r;
MCNUM pack = mccv_sample_pack;
MCNUM frac = mccv_sample_frac;
MCNUM f_QE = mccv_sample_f_QE;
MCNUM gamma = mccv_sample_gamma;
MCNUM target_x = mccv_sample_target_x;
MCNUM target_y = mccv_sample_target_y;
MCNUM target_z = mccv_sample_target_z;
MCNUM focus_xw = mccv_sample_focus_xw;
MCNUM focus_yh = mccv_sample_focus_yh;
MCNUM focus_aw = mccv_sample_focus_aw;
MCNUM focus_ah = mccv_sample_focus_ah;
MCNUM xwidth = mccv_sample_xwidth;
MCNUM yheight = mccv_sample_yheight;
MCNUM zthick = mccv_sample_zthick;
MCNUM rad_sphere = mccv_sample_rad_sphere;
MCNUM sig_a = mccv_sample_sig_a;
MCNUM sig_i = mccv_sample_sig_i;
MCNUM V0 = mccv_sample_V0;
int target_index = mccv_sample_target_index;
MCNUM multiples = mccv_sample_multiples;
#line 320 "V_sample.comp"
{
  
  if (VarsV.shapetyp == 0) {
    circle("xz", 0,  h/2.0, 0, radius_i);
    circle("xz", 0,  h/2.0, 0, radius_o);
    circle("xz", 0, -h/2.0, 0, radius_i);
    circle("xz", 0, -h/2.0, 0, radius_o);
    line(-radius_i, -h/2.0, 0, -radius_i, +h/2.0, 0);
    line(+radius_i, -h/2.0, 0, +radius_i, +h/2.0, 0);
    line(0, -h/2.0, -radius_i, 0, +h/2.0, -radius_i);
    line(0, -h/2.0, +radius_i, 0, +h/2.0, +radius_i);
    line(-radius_o, -h/2.0, 0, -radius_o, +h/2.0, 0);
    line(+radius_o, -h/2.0, 0, +radius_o, +h/2.0, 0);
    line(0, -h/2.0, -radius_o, 0, +h/2.0, -radius_o);
    line(0, -h/2.0, +radius_o, 0, +h/2.0, +radius_o);
  }
  else { 
	if (VarsV.shapetyp == 1) {
      double xmin = -0.5*xwidth;
      double xmax =  0.5*xwidth;
      double ymin = -0.5*yheight;
      double ymax =  0.5*yheight;
      double zmin = -0.5*zthick;
      double zmax =  0.5*zthick;
      multiline(5, xmin, ymin, zmin,
                   xmax, ymin, zmin,
                   xmax, ymax, zmin,
                   xmin, ymax, zmin,
                   xmin, ymin, zmin);
      multiline(5, xmin, ymin, zmax,
                   xmax, ymin, zmax,
                   xmax, ymax, zmax,
                   xmin, ymax, zmax,
                   xmin, ymin, zmax);
      line(xmin, ymin, zmin, xmin, ymin, zmax);
      line(xmax, ymin, zmin, xmax, ymin, zmax);
      line(xmin, ymax, zmin, xmin, ymax, zmax);
      line(xmax, ymax, zmin, xmax, ymax, zmax);
    }
    else {
      circle("xy", 0,  0.0, 0, rad_sphere);
      circle("xz", 0,  0.0, 0, rad_sphere);
      circle("yz", 0,  0.0, 0, rad_sphere);        
    }
  }
}
#line 24319 "./ThALES_resolution_v2.c"
}   /* End of v_sample=V_sample() SETTING parameter declarations. */
#undef VarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'Sample_Out'. */
  SIG_MESSAGE("Sample_Out (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Sample_Out");
#define mccompcurname  Sample_Out
#define mccompcurtype  Arm
#define mccompcurindex 23
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 24340 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'after_sample_slit'. */
  SIG_MESSAGE("after_sample_slit (McDisplay)");
  printf("MCDISPLAY: component %s\n", "after_sample_slit");
#define mccompcurname  after_sample_slit
#define mccompcurtype  Slit
#define mccompcurindex 24
{   /* Declarations of after_sample_slit=Slit() SETTING parameters. */
MCNUM xmin = mccafter_sample_slit_xmin;
MCNUM xmax = mccafter_sample_slit_xmax;
MCNUM ymin = mccafter_sample_slit_ymin;
MCNUM ymax = mccafter_sample_slit_ymax;
MCNUM radius = mccafter_sample_slit_radius;
MCNUM xwidth = mccafter_sample_slit_xwidth;
MCNUM yheight = mccafter_sample_slit_yheight;
#line 83 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
  
  if (radius == 0) {
    double xw, yh;
    xw = (xmax - xmin)/2.0;
    yh = (ymax - ymin)/2.0;
    multiline(3, xmin-xw, (double)ymax, 0.0,
              (double)xmin, (double)ymax, 0.0,
              (double)xmin, ymax+yh, 0.0);
    multiline(3, xmax+xw, (double)ymax, 0.0,
              (double)xmax, (double)ymax, 0.0,
              (double)xmax, ymax+yh, 0.0);
    multiline(3, xmin-xw, (double)ymin, 0.0,
              (double)xmin, (double)ymin, 0.0,
              (double)xmin, ymin-yh, 0.0);
    multiline(3, xmax+xw, (double)ymin, 0.0,
              (double)xmax, (double)ymin, 0.0,
              (double)xmax, ymin-yh, 0.0);
  } else {
    circle("xy",0,0,0,radius);
  }
}
#line 24382 "./ThALES_resolution_v2.c"
}   /* End of after_sample_slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'Ana_Cradle'. */
  SIG_MESSAGE("Ana_Cradle (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Ana_Cradle");
#define mccompcurname  Ana_Cradle
#define mccompcurtype  Arm
#define mccompcurindex 25
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 24402 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'PSD_analyzer'. */
  SIG_MESSAGE("PSD_analyzer (McDisplay)");
  printf("MCDISPLAY: component %s\n", "PSD_analyzer");
#define mccompcurname  PSD_analyzer
#define mccompcurtype  PSD_monitor
#define mccompcurindex 26
#define PSD_N mccPSD_analyzer_PSD_N
#define PSD_p mccPSD_analyzer_PSD_p
#define PSD_p2 mccPSD_analyzer_PSD_p2
{   /* Declarations of PSD_analyzer=PSD_monitor() SETTING parameters. */
int nx = mccPSD_analyzer_nx;
int ny = mccPSD_analyzer_ny;
char* filename = mccPSD_analyzer_filename;
MCNUM xmin = mccPSD_analyzer_xmin;
MCNUM xmax = mccPSD_analyzer_xmax;
MCNUM ymin = mccPSD_analyzer_ymin;
MCNUM ymax = mccPSD_analyzer_ymax;
MCNUM xwidth = mccPSD_analyzer_xwidth;
MCNUM yheight = mccPSD_analyzer_yheight;
MCNUM restore_neutron = mccPSD_analyzer_restore_neutron;
int nowritefile = mccPSD_analyzer_nowritefile;
#line 132 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  multiline(5,
    (double)xmin, (double)ymin, 0.0,
    (double)xmax, (double)ymin, 0.0,
    (double)xmax, (double)ymax, 0.0,
    (double)xmin, (double)ymax, 0.0,
    (double)xmin, (double)ymin, 0.0);
}
#line 24437 "./ThALES_resolution_v2.c"
}   /* End of PSD_analyzer=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'analyzer'. */
  SIG_MESSAGE("analyzer (McDisplay)");
  printf("MCDISPLAY: component %s\n", "analyzer");
#define mccompcurname  analyzer
#define mccompcurtype  Monochromator_curved
#define mccompcurindex 27
#define mos_rms_y mccanalyzer_mos_rms_y
#define mos_rms_z mccanalyzer_mos_rms_z
#define mos_rms_max mccanalyzer_mos_rms_max
#define mono_Q mccanalyzer_mono_Q
#define SlabWidth mccanalyzer_SlabWidth
#define SlabHeight mccanalyzer_SlabHeight
#define rTable mccanalyzer_rTable
#define tTable mccanalyzer_tTable
#define row mccanalyzer_row
#define col mccanalyzer_col
#define tiltH mccanalyzer_tiltH
#define tiltV mccanalyzer_tiltV
{   /* Declarations of analyzer=Monochromator_curved() SETTING parameters. */
char* reflect = mccanalyzer_reflect;
char* transmit = mccanalyzer_transmit;
MCNUM zwidth = mccanalyzer_zwidth;
MCNUM yheight = mccanalyzer_yheight;
MCNUM gap = mccanalyzer_gap;
MCNUM NH = mccanalyzer_NH;
MCNUM NV = mccanalyzer_NV;
MCNUM mosaich = mccanalyzer_mosaich;
MCNUM mosaicv = mccanalyzer_mosaicv;
MCNUM r0 = mccanalyzer_r0;
MCNUM t0 = mccanalyzer_t0;
MCNUM Q = mccanalyzer_Q;
MCNUM RV = mccanalyzer_RV;
MCNUM RH = mccanalyzer_RH;
MCNUM DM = mccanalyzer_DM;
MCNUM mosaic = mccanalyzer_mosaic;
MCNUM width = mccanalyzer_width;
MCNUM height = mccanalyzer_height;
MCNUM verbose = mccanalyzer_verbose;
MCNUM order = mccanalyzer_order;
#line 468 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Monochromator_curved.comp"
{
  int ih;

  for(ih = 0; ih < NH; ih++)
  {
    int iv;
    for(iv = 0; iv < NV; iv++)
    {
      double zmin,zmax,ymin,ymax;
      double xt, yt;

      zmin = (SlabWidth+gap)*(ih-NH/2.0)+gap/2;
      zmax = zmin+SlabWidth;
      ymin = (SlabHeight+gap)*(iv-NV/2.0)+gap/2;
      ymax = ymin+SlabHeight;

      if (RH) xt = -(zmax*zmax - zmin*zmin)/RH/2;
      else    xt = 0;

      if (RV) yt = -(ymax*ymax - ymin*ymin)/RV/2;
      else    yt = 0;
      multiline(5, xt+yt, (double)ymin, (double)zmin,
                   xt-yt, (double)ymax, (double)zmin,
                  -xt-yt, (double)ymax, (double)zmax,
                  -xt+yt, (double)ymin, (double)zmax,
                   xt+yt, (double)ymin, (double)zmin);
     }
   }
}
#line 24515 "./ThALES_resolution_v2.c"
}   /* End of analyzer=Monochromator_curved() SETTING parameter declarations. */
#undef tiltV
#undef tiltH
#undef col
#undef row
#undef tTable
#undef rTable
#undef SlabHeight
#undef SlabWidth
#undef mono_Q
#undef mos_rms_max
#undef mos_rms_z
#undef mos_rms_y
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'Ana_Out'. */
  SIG_MESSAGE("Ana_Out (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Ana_Out");
#define mccompcurname  Ana_Out
#define mccompcurtype  Arm
#define mccompcurindex 28
#line 40 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 24547 "./ThALES_resolution_v2.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'slit'. */
  SIG_MESSAGE("slit (McDisplay)");
  printf("MCDISPLAY: component %s\n", "slit");
#define mccompcurname  slit
#define mccompcurtype  Slit
#define mccompcurindex 29
{   /* Declarations of slit=Slit() SETTING parameters. */
MCNUM xmin = mccslit_xmin;
MCNUM xmax = mccslit_xmax;
MCNUM ymin = mccslit_ymin;
MCNUM ymax = mccslit_ymax;
MCNUM radius = mccslit_radius;
MCNUM xwidth = mccslit_xwidth;
MCNUM yheight = mccslit_yheight;
#line 83 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../optics/Slit.comp"
{
  
  if (radius == 0) {
    double xw, yh;
    xw = (xmax - xmin)/2.0;
    yh = (ymax - ymin)/2.0;
    multiline(3, xmin-xw, (double)ymax, 0.0,
              (double)xmin, (double)ymax, 0.0,
              (double)xmin, ymax+yh, 0.0);
    multiline(3, xmax+xw, (double)ymax, 0.0,
              (double)xmax, (double)ymax, 0.0,
              (double)xmax, ymax+yh, 0.0);
    multiline(3, xmin-xw, (double)ymin, 0.0,
              (double)xmin, (double)ymin, 0.0,
              (double)xmin, ymin-yh, 0.0);
    multiline(3, xmax+xw, (double)ymin, 0.0,
              (double)xmax, (double)ymin, 0.0,
              (double)xmax, ymin-yh, 0.0);
  } else {
    circle("xy",0,0,0,radius);
  }
}
#line 24589 "./ThALES_resolution_v2.c"
}   /* End of slit=Slit() SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'PSD_det'. */
  SIG_MESSAGE("PSD_det (McDisplay)");
  printf("MCDISPLAY: component %s\n", "PSD_det");
#define mccompcurname  PSD_det
#define mccompcurtype  PSD_monitor
#define mccompcurindex 30
#define PSD_N mccPSD_det_PSD_N
#define PSD_p mccPSD_det_PSD_p
#define PSD_p2 mccPSD_det_PSD_p2
{   /* Declarations of PSD_det=PSD_monitor() SETTING parameters. */
int nx = mccPSD_det_nx;
int ny = mccPSD_det_ny;
char* filename = mccPSD_det_filename;
MCNUM xmin = mccPSD_det_xmin;
MCNUM xmax = mccPSD_det_xmax;
MCNUM ymin = mccPSD_det_ymin;
MCNUM ymax = mccPSD_det_ymax;
MCNUM xwidth = mccPSD_det_xwidth;
MCNUM yheight = mccPSD_det_yheight;
MCNUM restore_neutron = mccPSD_det_restore_neutron;
int nowritefile = mccPSD_det_nowritefile;
#line 132 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/PSD_monitor.comp"
{
  multiline(5,
    (double)xmin, (double)ymin, 0.0,
    (double)xmax, (double)ymin, 0.0,
    (double)xmax, (double)ymax, 0.0,
    (double)xmin, (double)ymax, 0.0,
    (double)xmin, (double)ymin, 0.0);
}
#line 24625 "./ThALES_resolution_v2.c"
}   /* End of PSD_det=PSD_monitor() SETTING parameter declarations. */
#undef PSD_p2
#undef PSD_p
#undef PSD_N
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'res_monitor'. */
  SIG_MESSAGE("res_monitor (McDisplay)");
  printf("MCDISPLAY: component %s\n", "res_monitor");
#define mccompcurname  res_monitor
#define mccompcurtype  Res_monitor
#define mccompcurindex 31
#define res_sample_comp mccres_monitor_res_sample_comp
#define DEFS mccres_monitor_DEFS
#define Vars mccres_monitor_Vars
#define buffer_index mccres_monitor_buffer_index
{   /* Declarations of res_monitor=Res_monitor() SETTING parameters. */
char* filename = mccres_monitor_filename;
char* options = mccres_monitor_options;
MCNUM xwidth = mccres_monitor_xwidth;
MCNUM yheight = mccres_monitor_yheight;
MCNUM zdepth = mccres_monitor_zdepth;
MCNUM radius = mccres_monitor_radius;
MCNUM xmin = mccres_monitor_xmin;
MCNUM xmax = mccres_monitor_xmax;
MCNUM ymin = mccres_monitor_ymin;
MCNUM ymax = mccres_monitor_ymax;
MCNUM zmin = mccres_monitor_zmin;
MCNUM zmax = mccres_monitor_zmax;
MCNUM bufsize = mccres_monitor_bufsize;
MCNUM restore_neutron = mccres_monitor_restore_neutron;
#line 221 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Res_monitor.comp"
{
  Monitor_nD_McDisplay(&DEFS, &Vars);
}
#line 24663 "./ThALES_resolution_v2.c"
}   /* End of res_monitor=Res_monitor() SETTING parameter declarations. */
#undef buffer_index
#undef Vars
#undef DEFS
#undef res_sample_comp
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'detector_all'. */
  SIG_MESSAGE("detector_all (McDisplay)");
  printf("MCDISPLAY: component %s\n", "detector_all");
#define mccompcurname  detector_all
#define mccompcurtype  Monitor
#define mccompcurindex 32
#define Nsum mccdetector_all_Nsum
#define psum mccdetector_all_psum
#define p2sum mccdetector_all_p2sum
{   /* Declarations of detector_all=Monitor() SETTING parameters. */
MCNUM xmin = mccdetector_all_xmin;
MCNUM xmax = mccdetector_all_xmax;
MCNUM ymin = mccdetector_all_ymin;
MCNUM ymax = mccdetector_all_ymax;
MCNUM xwidth = mccdetector_all_xwidth;
MCNUM yheight = mccdetector_all_yheight;
MCNUM restore_neutron = mccdetector_all_restore_neutron;
#line 96 "/usr/share/mcstas/2.7.1/tools/Python/mcrun/../mccodelib/../../../monitors/Monitor.comp"
{
  
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 24699 "./ThALES_resolution_v2.c"
}   /* End of detector_all=Monitor() SETTING parameter declarations. */
#undef p2sum
#undef psum
#undef Nsum
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  printf("MCDISPLAY: end\n");
} /* end display */
#undef magnify
#undef line
#undef dashed_line
#undef multiline
#undef rectangle
#undef box
#undef circle
#undef cylinder
#undef sphere
/* end of generated C code ./ThALES_resolution_v2.c */
