/* NetHack 3.7	global.h	$NHDT-Date: 1642630918 2022/01/19 22:21:58 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.131 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Michael Allison, 2006. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

/*
 * Files expected to exist in the playground directory (possibly inside
 * a dlb container file).
 */

#define RECORD "record"         /* file containing list of topscorers */
#define HELP "help"             /* file containing command descriptions */
#define SHELP "hh"              /* abbreviated form of the same */
#define KEYHELP "keyhelp"       /* explanatory text for 'whatdoes' command */
#define DEBUGHELP "wizhelp"     /* file containing debug mode cmds */
#define RUMORFILE "rumors"      /* file with fortune cookies */
#define ORACLEFILE "oracles"    /* file with oracular information */
#define DATAFILE "data"         /* file giving the meaning of symbols used */
#define CMDHELPFILE "cmdhelp"   /* file telling what commands do */
#define HISTORY "history"       /* file giving nethack's history */
#define LICENSE "license"       /* file with license information */
#define OPTIONFILE "opthelp"    /* file explaining runtime options */
#define OPTMENUHELP "optmenu"   /* file explaining #options command */
#define OPTIONS_USED "options"  /* compile-time options, for #version */
#define SYMBOLS "symbols"       /* replacement symbol sets */
#define EPITAPHFILE "epitaph"   /* random epitaphs on graves */
#define ENGRAVEFILE "engrave"   /* random engravings on the floor */
#define BOGUSMONFILE "bogusmon" /* hallucinatory monsters */
#define TRIBUTEFILE "tribute"   /* 3.6 tribute to Terry Pratchett */
#define LEV_EXT ".lua"          /* extension for special level files */

/* padding amounts for files that have lines chosen by fseek to random spot,
   advancing to the next line, and using that line; makedefs forces shorter
   lines to be padded to these lengths; value of 0 will inhibit any padding,
   avoiding an increase in files' sizes, but resulting in biased selection;
   used by makedefs while building and by core's callers of get_rnd_text() */
#define MD_PAD_RUMORS 60u /* for RUMORFILE, EPITAPHFILE, and ENGRAVEFILE */
#define MD_PAD_BOGONS 20u /* for BOGUSMONFILE */

/* Assorted definitions that may depend on selections in config.h. */

/*
 * for DUMB preprocessor and compiler, e.g., cpp and pcc supplied
 * with Microport SysV/AT, which have small symbol tables;
 * DUMB if needed is defined in CFLAGS
 */
#ifdef DUMB
#ifdef BITFIELDS
#undef BITFIELDS
#endif
#ifndef STUPID
#define STUPID
#endif
#endif /* DUMB */

/*
 * type xchar: small integers (typedef'd as signed char,
 * so in the range -127 - 127), usually coordinates.
 */
typedef schar xchar;

#ifdef __MINGW32__
/* Resolve conflict with Qt 5 and MinGW-w32 */
typedef unsigned char boolean; /* 0 or 1 */
#else
#ifndef SKIP_BOOLEAN
typedef xchar boolean; /* 0 or 1 */
#endif
#endif

#ifndef TRUE /* defined in some systems' native include files */
#define TRUE ((boolean) 1)
#define FALSE ((boolean) 0)
#endif
#define BOOL_RANDOM (-1)

enum optchoice { opt_in, opt_out};

/*
 * type nhsym: loadable symbols go into this type
 */
typedef uchar nhsym;

#ifndef STRNCMPI
#ifndef __SASC_60 /* SAS/C already shifts to stricmp */
#define strcmpi(a, b) strncmpi((a), (b), -1)
#endif
#endif

#if 0
/* comment out to test effects of each #define -- these will probably
 * disappear eventually
 */
#ifdef INTERNAL_COMP
#define RLECOMP  /* run-length compression of levl array - JLee */
#define ZEROCOMP /* zero-run compression of everything - Olaf Seibert */
#endif
#endif

/* #define SPECIALIZATION */ /* do "specialized" version of new topology */

#ifdef BITFIELDS
#define Bitfield(x, n) unsigned x : n
#else
#define Bitfield(x, n) uchar x
#endif

#define SIZE(x) (int)(sizeof(x) / sizeof(x[0]))

/* A limit for some NetHack int variables.  It need not, and for comparable
 * scoring should not, depend on the actual limit on integers for a
 * particular machine, although it is set to the minimum required maximum
 * signed integer for C (2^15 -1).
 */
#define LARGEST_INT 32767

#include "coord.h"

/*
 * Automatic inclusions for the subsidiary files.
 * Please don't change the order.  It does matter.
 */

#ifdef VMS
#include "vmsconf.h"
#endif

#ifdef UNIX
#include "unixconf.h"
#endif

#ifdef MSDOS
#include "pcconf.h"
#endif

#ifdef WIN32
#include "windconf.h"
#endif

#include "warnings.h"

/* amiconf.h needs to be the last nested #include of config.h because
   'make depend' will turn it into a comment, hiding anything after it */
#ifdef AMIGA
#include "amiconf.h"
#endif

/* Displayable name of this port; don't redefine if defined in *conf.h */
#ifndef PORT_ID
#ifdef AMIGA
#define PORT_ID "Amiga"
#endif
#ifdef MAC
#define PORT_ID "Mac"
#endif
#ifdef __APPLE__
#define PORT_ID "MacOS"
#endif
#ifdef MSDOS
#ifdef PC9800
#define PORT_ID "PC-9800"
#else
#define PORT_ID "PC"
#endif
#ifdef DJGPP
#define PORT_SUB_ID "djgpp"
#else
#ifdef OVERLAY
#define PORT_SUB_ID "overlaid"
#else
#define PORT_SUB_ID "non-overlaid"
#endif
#endif
#endif
#ifdef OS2
#define PORT_ID "OS/2"
#endif
#ifdef TOS
#define PORT_ID "ST"
#endif
/* Check again in case something more specific has been defined above. */
#ifndef PORT_ID
#ifdef UNIX
#define PORT_ID "Unix"
#endif
#endif
#ifdef VMS
#define PORT_ID "VMS"
#endif
#ifdef WIN32
#define PORT_ID "Windows"
#endif
#endif

#if !defined(CROSSCOMPILE)
#if defined(MICRO)
#if !defined(AMIGA) && !defined(TOS) && !defined(OS2_HPFS)
#define SHORT_FILENAMES /* filenames are 8.3 */
#endif
#endif
#endif

#include "fnamesiz.h" /* file sizes shared between nethack and recover */

#ifdef VMS
/* vms_exit() (sys/vms/vmsmisc.c) expects the non-VMS EXIT_xxx values below.
 * these definitions allow all systems to be treated uniformly, provided
 * main() routines do not terminate with return(), whose value is not
 * so massaged.
 */
#ifdef EXIT_SUCCESS
#undef EXIT_SUCCESS
#endif
#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#if defined(X11_GRAPHICS) || defined(QT_GRAPHICS) || defined(GNOME_GRAPHICS) \
    || defined(WIN32)
#ifndef NO_TILE_C
#ifndef USE_TILES
#define USE_TILES /* glyphmap[] with prefilled tile mappings will be available */
#endif
#endif
#endif
#if defined(AMII_GRAPHICS) || defined(GEM_GRAPHICS)
#ifndef NO_TILE_C
#ifndef USE_TILES
#define USE_TILES
#endif
#endif
#endif

#if defined(UNIX) || defined(VMS) || defined(__EMX__) || defined(WIN32)
#define HANGUPHANDLING
#endif
#if defined(SAFERHANGUP) \
    && (defined(NOSAVEONHANGUP) || !defined(HANGUPHANDLING))
#undef SAFERHANGUP
#endif

#define Sprintf (void) sprintf
#define Strcat (void) strcat
#define Strcpy (void) strcpy
#ifdef NEED_VARARGS
#define Vprintf (void) vprintf
#define Vfprintf (void) vfprintf
#define Vsprintf (void) vsprintf
#endif

/*
 *  Memory allocation.  Functions are declared here rather than in
 *  extern.h so that source files which use config.h instead of hack.h
 *  will see the declarations.
 *
 *  NetHack does not use malloc() [except to implement alloc() in alloc.c]
 *  or realloc() or calloc().  They return Null if memory runs out and
 *  nethack's code relies on alloc() to intercept that so that a zillion
 *  callers don't need to test for Null result.  alloc() never returns
 *  Null; if memory runs out, it calls panic() and does not return at all.
 */

/* dupstr() is unconditional in alloc.c but not used when MONITOR_HEAP
   is enabled; some utility programs link with alloc.{o,obj} and need it
   if nethack is built with MONITOR_HEAP enabled and they aren't; this
   declaration has been moved out of the '#else' below to avoid getting
   a complaint from -Wmissing-prototypes when building with MONITOR_HEAP */
extern char *dupstr(const char *);

/*
 * MONITOR_HEAP is conditionally used for primitive memory leak debugging.
 * When enabled, NH_HEAPLOG (if defined in the environment) is used as the
 * name of a log file to create for capturing allocations and releases.
 * [The 'heaputil' program to analyze that file isn't included in releases.]
 *
 * See alloc.c.
 */
#ifdef MONITOR_HEAP
/* plain alloc() is not declared except in alloc.c */
extern long *nhalloc(unsigned int, const char *, int);
extern void nhfree(genericptr_t, const char *, int);
extern char *nhdupstr(const char *, const char *, int);
/* this predates C99's __func__; that is trickier to use conditionally
   because it is not implemented as a preprocessor macro; MONITOR_HEAP
   wouldn't gain much benefit from it anyway so continue to live without it;
   if func's caller were accessible, that would be a very different issue */
#ifndef __FILE__
#define __FILE__ ""
#endif
#ifndef __LINE__
#define __LINE__ 0
#endif
#define alloc(a) nhalloc(a, __FILE__, (int) __LINE__)
#define free(a) nhfree(a, __FILE__, (int) __LINE__)
#define dupstr(s) nhdupstr(s, __FILE__, (int) __LINE__)
#else /* !MONITOR_HEAP */
/* declare alloc.c's alloc(); allocations made with it use ordinary free() */
extern long *alloc(unsigned int);  /* alloc.c */
#endif /* ?MONITOR_HEAP */

/* Used for consistency checks of various data files; declare it here so
   that utility programs which include config.h but not hack.h can see it. */
struct version_info {
    unsigned long incarnation;   /* actual version number */
    unsigned long feature_set;   /* bitmask of config settings */
    unsigned long entity_count;  /* # of monsters and objects */
    unsigned long struct_sizes1; /* size of key structs */
    unsigned long struct_sizes2; /* size of more key structs */
};

struct savefile_info {
    unsigned long sfi1; /* compression etc. */
    unsigned long sfi2; /* miscellaneous */
    unsigned long sfi3; /* thirdparty */
};
#ifdef NHSTDC
#define SFI1_EXTERNALCOMP (1UL)
#define SFI1_RLECOMP (1UL << 1)
#define SFI1_ZEROCOMP (1UL << 2)
#else
#define SFI1_EXTERNALCOMP (1L)
#define SFI1_RLECOMP (1L << 1)
#define SFI1_ZEROCOMP (1L << 2)
#endif

/* This is used to store some build-info data that used
   to be present in makedefs-generated header file date.h */

struct nomakedefs_s {
    const char *build_date;
    const char *copyright_banner_c;
    const char *git_sha;
    const char *git_branch;
    const char *version_string;
    const char *version_id;
    unsigned long version_number;
    unsigned long version_features;
    unsigned long ignored_features;
    unsigned long version_sanity1;
    unsigned long version_sanity2;
    unsigned long version_sanity3;
    unsigned long build_time;
};
extern struct nomakedefs_s nomakedefs;

/*
 * Configurable internal parameters.
 *
 * Please be very careful if you are going to change one of these.  Any
 * changes in these parameters, unless properly done, can render the
 * executable inoperative.
 */

/* size of terminal screen is (at least) (ROWNO+3) by COLNO */
#define COLNO 80
#define ROWNO 21

#define MAXNROFROOMS 40 /* max number of rooms per level */
#define MAX_SUBROOMS 24 /* max # of subrooms in a given room */
#define DOORMAX 120     /* max number of doors per level */

#define BUFSZ 256  /* for getlin buffers */
#define QBUFSZ 128 /* for building question text */
#define TBUFSZ 300 /* g.toplines[] buffer max msg: 3 81char names */
/* plus longest prefix plus a few extra words */

/* COLBUFSZ is the larger of BUFSZ and COLNO */
#if BUFSZ > COLNO
#define COLBUFSZ BUFSZ
#else
#define COLBUFSZ COLNO
#endif

#define PL_NSIZ 32 /* name of player, ghost, shopkeeper */
#define PL_CSIZ 32 /* sizeof pl_character */
#define PL_FSIZ 32 /* fruit name */
#define PL_PSIZ 63 /* player-given names for pets, other monsters, objects */

#define MAXDUNGEON 16 /* current maximum number of dungeons */
#define MAXLEVEL 32   /* max number of levels in one dungeon */
#define MAXSTAIRS 1   /* max # of special stairways in a dungeon */
#define ALIGNWEIGHT 4 /* generation weight of alignment */

#define MAXULEV 30 /* max character experience level */

#define MAXMONNO 120 /* extinct monst after this number created */
#define MHPMAX 500   /* maximum monster hp */

/*
 * Version 3.7.x has aspirations of portable file formats. We
 * make a distinction between MAIL functionality and MAIL_STRUCTURES
 * so that the underlying structures are consistent, whether MAIL is
 * defined or not.
 */
#define MAIL_STRUCTURES

/* PANICTRACE: Always defined for NH_DEVEL_STATUS != NH_STATUS_RELEASED
   but only for supported platforms. */
#ifdef UNIX
#if (NH_DEVEL_STATUS != NH_STATUS_RELEASED)
/* see end.c */
#if !defined(CROSS_TO_WASM)
#ifndef PANICTRACE
#define PANICTRACE
#endif  /* PANICTRACE */
#endif  /* CROSS_TO_WASM */
#endif  /* NH_DEVEL_STATUS != NH_STATUS_RELEASED */
#endif  /* UNIX */

/* The following are meaningless if PANICTRACE is not defined: */
#if defined(__linux__) && defined(__GLIBC__) && (__GLIBC__ >= 2)
#define PANICTRACE_LIBC
#endif
#if defined(MACOS)
#define PANICTRACE_LIBC
#endif
#ifdef UNIX
#if !defined(CROSS_TO_WASM) /* no popen in WASM */
#define PANICTRACE_GDB
#endif
#endif

/* Supply nethack_enter macro if not supplied by port */
#ifndef nethack_enter
#define nethack_enter(argc, argv) ((void) 0)
#endif

/* Supply nhassert macro if not supplied by port */
#ifndef nhassert
#define nhassert(expression) (void)((!!(expression)) || \
        (nhassert_failed(#expression, __FILE__, __LINE__), 0))
#endif

/* Macros for meta and ctrl modifiers:
 *   M and C return the meta/ctrl code for the given character;
 *     e.g., (C('c') is ctrl-c
 */
#ifndef M
#ifndef NHSTDC
#define M(c) (0x80 | (c))
#else
#define M(c) ((c) - 128)
#endif /* NHSTDC */
#endif

#ifndef C
#define C(c) (0x1f & (c))
#endif

#define unctrl(c) ((c) <= C('z') ? (0x60 | (c)) : (c))
#define unmeta(c) (0x7f & (c))

#endif /* GLOBAL_H */
