typedef long unsigned int dddirection;

/* directions: */
#define ddlt		(dddirection)0x1
#define ddeq		(dddirection)0x2
#define ddgt		(dddirection)0x4
#define ddall		(dddirection)0x7
#define ddrr		(dddirection)0x8
#define ddne		(dddirection)0xd
#define ddanydir	(dddirection)0xf
/* #define ddeqeq		(dddirection)0x10000000 unused */
#define ddallnone	(dddirection)0
#define ddcovers        (dddirection)0x80000000
#define ddterminates    (dddirection)0x40000000
#define ddrefined       (dddirection)0x20000000
#define ddisCovered     (dddirection)0x10000000
#define ddisTerminated  (dddirection)0x08000000
#define ddisRefined     (dddirection)0x04000000 /* what dd was before refine */
#define ddkilled        (dddirection)0x02000000
#define ddzappableWC    (dddirection)0x01000000
#define ddzappable      (dddirection)0x00800000
#define dddirBits       (dddirection)0x00777777
/* added new flags 2/92 - 3/92 davew@cs.umd.edu */

/* test to see if a dd has been killed by a kill or cover */
#define ddisDead(d)             ((d) & (ddkilled | ddisCovered | ddisTerminated| ddisRefined))
/* shift a direction 'd' to appropriate position for nest 'n' */
#define dddirnest(d,n)		((d)<<(((n)-1)*4))
/* test if direction vector 'dv' has direction 'd' set at nest 'n' */
#define dddirtest(dv,d,n)	((dv)&dddirnest(d,n))
/* test if direction vector 'dv' all-equal bit set */
#define ddeqtest(dv)		((dv)&(ddallequal))
/* return direction vector except for direction n */
#define ddallBut(dv,n)		((dv)&(dddirBits & ~dddirnest(ddall,n)))
/* set direction 'd' at nest 'dv' for nest 'n' */
#define dddirset(dv,d,n)	(dv|=dddirnest(d,n))
/* reset all directions at nest 'n' in 'dv' except for 'd' */
#define dddironly(dv,d,n)	(dv=(((dv)&~dddirnest(ddanydir,n))|((dv)&dddirnest(d,n))))
/* reset all directions at nest 'n' in 'dv', then set 'd' */
#define dddirsetonly(dv,d,n)	(dv=(((dv)&~dddirnest(ddanydir,n))|(dddirnest(d,n))))
/* set all-equal bit in 'dv' */
#define ddeqset(dv)		(dv|=(ddallequal))
/* reset direction 'd' at nest 'n' in 'dv' */
#define dddirreset(dv,d,n)	(dv&=(~dddirnest(d,n)))
/* reset all-equal bit in 'dv' */
#define ddeqreset(dv)		(dv&=(~(ddallequal)))
/* extract direction vector element at nest 'n' from 'dv' */
#define ddextract1(dv,n)	(((dv)>>(((n)-1)*4))&0xF)
/* test direction 'd' in extracted direction vector element 'dv' */
#define ddtest1(dv,d)		((dv)&(d))
/* reset direction 'd' in extracted direction vector element 'dv' */
#define ddreset1(dv,d)		(dv&=(~(d)))
/* set direction 'd' in extracted direction vector element 'dv' */
#define ddset1(dv,d)		(dv|=(d))
/* filter all direction vector elements with direction 'd' set in 'dv' */
#define ddfilter(dv,d)		(((dv)&((d)|(d<<4)|(d<<8)|(d<<12)|(d<<16)|(d<<20)|(d<<24)))/d)
/* set all filtered direction vector elements to direction 'd' */
#define ddsetfilter(dv,f,d)	(dv|=((f)*(d)))

/* unknown distance */
#define ddunknown	(dddirection)0x80000000

/* return the depth of the loop that carries dv, or the length+1 for loop ind.
   dv has only the 0 bit set at levels [1 .. dd_carried_by(dv, length(dv))]
 */
extern int dd_carried_by(dddirection dv, int length);
extern int leading_zeros(dddirection dv, int length);
extern void append_dd_flags(char *, dddirection dv);
/* code for the above is currently in ddodriver.c */
