/*
 * Geco Gaming Company
 * All Rights Reserved.
 * Copyright (c)  2016 GECOEngine.
 *
 * GECOEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GECOEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * wheel 1 has 256 slots
 * wheel 2 has 64  slots
 * wheel 3 has 64  slots
 * wheel 4 has 64  slots
 * wheel 5 has 64  slots
 *
 *In practice it's done by categorizing all future jiffies into 5 wheels:
 * wheel 1  jiffies of [1, 2^8]  1..256,
 * wheel 2  jiffies of [2^8, 2^14] 257..16384,
 * wheel 3  jiffies of [2^14, 2^20] 16385..1048576,
 * wheel 4  jiffies of [2^20, 2^26] 1048577..67108864,
 * wheel 5  jiffies of [2^26, 2^32] 67108865..4294967295
 *
 * the first wheel consists of 256 buckets
 * (each bucket representing a single jiffy),
 * the second category consists of 64 buckets equally divided
 * (each bucket represents 256 subsequent jiffies),
 * the third category consists of 64 buckets too
 * (each bucket representing 256*64 ==16384 jiffies),
 * the fourth category consists of 64 buckets too
 * (each bucket representing 256*64*64 == 1048576 jiffies),
 * the fifth category consists of 64 buckets too (each bucket representing 67108864 jiffies).
 *
 */

/*
 * created on 06-June-2016 by Jackie Zhang
 */

#ifndef SRC_COMMON_DS_WHEELTIMERMGRT_H_
#define SRC_COMMON_DS_WHEELTIMERMGRT_H_
#include <stdbool.h>    /* bool */
#include <stdio.h>      /* FILE */
#include <inttypes.h>   /* PRIu64 PRIx64 PRIX64 uint64_t */
#include <list>
#include <functional>
#include <limits.h>    /* CHAR_BIT */
#include <stddef.h>    /* NULL */
#include <stdlib.h>    /* malloc(3) free(3) */
#include <string.h>    /* memset(3) */
#if defined(__linux__) || defined(__unix__)
#include <errno.h>     /* errno */
#define get_last_error() errno
#else
#define get_last_error() WSAGetLastError()
#endif
#include "geco-engine-ultils.h"
#include "geco-malloc.h"

/* type defines */
#define TIMEOUT_C(n) UINT64_C(n)
#define TIMEOUT_PRIu PRIu64
#define TIMEOUT_PRIx PRIx64
#define TIMEOUT_PRIX PRIX64
#define TIMEOUT_mHZ TIMEOUT_C(1000)
#define TIMEOUT_uHZ TIMEOUT_C(1000000)
#define TIMEOUT_nHZ TIMEOUT_C(1000000000)
#define timeout_error_t int /* for documentation purposes */

#define REPEAT_TIMER 0x01 /* interval (repeating) TIMER */
#define ABS_TIMEOUT 0x02 /* treat timeout values as absolute */
#define TIMEOUT_INITIALIZER(flags) { (flags) }
#define timeout_setcb(to, fn, arg) do { \
    (to)->callback.fn = (fn);       \
    (to)->callback.arg = (arg);     \
} while (0)

/*
 * helpers
 * * * * * */
#define countof(a) (sizeof (a) / sizeof *(a))
#define endof(a) (&(a)[countof(a)])
#define MIN(a, b) (((a) < (b))? (a) : (b))
#define MAX(a, b) (((a) > (b))? (a) : (b))

/*
 * B I T  M A N I P U L A T I O N  R O U T I N E S
 *
 * The macros and routines below implement wheel parameterization. The
 * inputs are:
 *
 *   WHEEL_BIT - The number of value bits mapped in each wheel. The
 *               lowest-order WHEEL_BIT bits index the lowest-order (highest
 *               resolution) wheel, the next group of WHEEL_BIT bits the
 *               higher wheel, etc.
 *
 *   WHEEL_NUM - The number of wheels. WHEEL_BIT * WHEEL_NUM = the number of
 *               value bits used by all the wheels. For the default of 6 and
 *               4, only the low 24 bits are processed. Any timeout value
 *               larger than this will cycle through again.
 *
 * The implementation uses bit fields to remember which slot in each wheel
 * is populated, and to generate masks of expiring slots according to the
 * current update interval (i.e. the "tickless" aspect). The slots to
 * process in a wheel are (populated-set & interval-mask).
 *
 * WHEEL_BIT cannot be larger than 6 bits because 2^6 -> 64 is the largest
 * number of slots which can be tracked in a uint64_t integer bit field.
 * WHEEL_BIT cannot be smaller than 3 bits because of our rotr and rotl
 * routines, which only operate on all the value bits in an integer, and
 * there's no integer smaller than uint8_t.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define WHEEL_BIT 6 // optional 6,5,4,3
#define WHEEL_NUM 4
#define WHEEL_LEN (1U << WHEEL_BIT) // 2^6 = 64
#define WHEEL_MAX (WHEEL_LEN - 1) // 63
#define WHEEL_MASK (WHEEL_LEN - 1) // 63 = 01111111
#define TIMEOUT_MAX \
((TIMEOUT_C(1) << (WHEEL_BIT * WHEEL_NUM)) - 1)

#if WHEEL_BIT == 6
#define ctz(n) ctz64(n)
#define clz(n) clz64(n)
#define fls(n) ((int)(64 - clz64(n)))
#else
#define ctz(n) ctz32(n)
#define clz(n) clz32(n)
#define fls(n) ((int)(32 - clz32(n)))
#endif

#if WHEEL_BIT == 6 // max timeout allowed is 4.66 hours
#define WHEEL_C(n) UINT64_C(n)
#define WHEEL_PRIu PRIu64
#define WHEEL_PRIx PRIx64
typedef uint64_t wheel_t;
#elif WHEEL_BIT == 5 // max timeout allowed is 17 minutes
#define WHEEL_C(n) UINT32_C(n)
#define WHEEL_PRIu PRIu32
#define WHEEL_PRIx PRIx32
typedef uint32_t wheel_t;
#elif WHEEL_BIT == 4 // max timeout allowed is 65.5 seconds
#define WHEEL_C(n) UINT16_C(n)
#define WHEEL_PRIu PRIu16
#define WHEEL_PRIx PRIx16
typedef uint16_t wheel_t;
#elif WHEEL_BIT == 3 // max timeout allowed is 4.09 seconds
#define WHEEL_C(n) UINT8_C(n)
#define WHEEL_PRIu PRIu8
#define WHEEL_PRIx PRIx8
typedef uint8_t wheel_t;
#else
#error invalid WHEEL_BIT value
#endif

#define TIMEOUTS_PENDING 0x10
#define TIMEOUTS_EXPIRED 0x20
#define TIMEOUTS_ALL     (TIMEOUTS_PENDING|TIMEOUTS_EXPIRED)
#define TIMEOUTS_CLEAR   0x40
#define TIMEOUTS_IT_INITIALIZER(flags) { (flags), 0, 0, 0, 0 }
#define TIMEOUTS_IT_INIT(cur, _flags) do {                              \
    (cur)->flags = (_flags);                                        \
    (cur)->pc = 0;                                                  \
} while (0)
#define GET_SLOT_IDX(curtime, wheel) \
(WHEEL_MASK & (curtime >> wheel * WHEEL_BIT))
/*
 * B O N U S  W H E E L  I N T E R F A C E S
 *
 * I usually use floating point timeouts in all my code, but it's cleaner to
 * separate it to keep the core algorithmic code simple.
 *
 * Using macros instead of static inline routines where <math.h> routines
 * might be used to keep -lm linking optional.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <math.h> /* ceil(3) */
/* prefer late expiration over early */
#define timeouts_f2i(T, f) ((time_t)ceil((f) * timeouts_hz((T))))
#define timeouts_i2f(T, i) ((double)(i) / timeouts_hz((T)))
#define timeouts_addf(T, to, timeout)  \
timeouts_add((T), (to), timeouts_f2i((T), (timeout)))

namespace geco
{
    namespace ultils
    {
        /*
         * Callback function parameters unspecified to make embedding into existing
         * applications easier, you can always force cast the func ptr to the one you need
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        struct event_handler_t
        {
                unsigned int event_type;
                unsigned int owner_type;
                void* owner;
                void (*fn)();
                void *arg;
        };

//        struct timeout_cb
//        {
//            void(*fn)();
//            void *arg;
//        };
        struct wtimers_t;
        struct wtimer_t;
        typedef std::list<wtimer_t*> timer_list;
        typedef timer_list::iterator wtimer_id_t;
        struct timeout_cb_t
        {
                std::function<int(wtimer_t* timer, void* args)> fuc;
                void* args;
        };
        struct wtimer_t
        {
                wtimer_id_t id;
                int intid; /* 0 means id is an empty iterator */
                int flags;
                time_t abs_expires; /*abs expiration time*/
                timer_list* pending; /* timer list if pended on wheel or expiry list*/
#ifndef TIMEOUT_DISABLE_CALLBACKS
                timeout_cb_t callback; /* optional callback information */
#endif
#ifndef TIMEOUT_DISABLE_INTERVALS
                time_t interval; /* timeout interval if periodic */
#endif
#ifndef TIMEOUT_DISABLE_RELATIVE_ACCESS
                struct wtimers_t *wtimers; /* timer collection*/
#endif
                /* initialize timeout structure (same as TIMEOUT_INITIALIZER) */
                void init(int wt_flags);
#ifndef TIMEOUT_DISABLE_RELATIVE_ACCESS
                /* true if on timing wheel, false otherwise */
                bool pending_wheel();
                /* true if on expired queue, false otherwise */
                bool pending_expired(wtimer_t *);
                /* remove timeout from any timing wheel (okay if not member of any) */
                void stop();
#endif
        };

        class wtimers_t
        {
            public:
                /*
                 * WHEEL SLOTS            JIFFIES
                 *     0        64         [1,        2^6-1 ]
                 *     1        64         [2^6,   2^12-1]
                 *     2        64         [2^12, 2^18-1]
                 *     3        64         [2^18, 2^24-1]
                 * */
                timer_list wheel[WHEEL_NUM][WHEEL_LEN];
                timer_list expired;
                wheel_t pending[WHEEL_NUM];
                time_t curtime;
                time_t hertz;
                timer_list todo;

            public:
                /**
                 * Calculate the interval before needing to process any timeouts
                 * pending on any wheel. (This is separated from the public API
                 * routine so we can evaluate our wheel invariant assertions irrespective
                 * of the expired queue.)
                 *
                 * This might return a timeout value sooner than any installed timeout
                 * if only higher-order wheels have timeouts pending.
                 * We can only know when to process a wheel, not precisely when a
                 * timeout is scheduled.
                 *
                 * Our timeout accuracy could be off by 2^(N*M)-1 units where N is
                 * the wheel number and M is WHEEL_BIT. Only timeouts which have
                 * fallen through to wheel 0 can be known exactly.
                 *
                 * We should never return a timeout larger than the lowest
                 * actual timeout.*/
                time_t get_interval();

                void close(){reset();}
                void reset()
                {
                    timer_list reset;
                    wtimer_t* to;
                    unsigned i,j;
                    for (i = 0; i < WHEEL_NUM; i++)
                       {
                           for (j = 0; j < WHEEL_LEN; j++)
                           {

                           }
                       }
                }
                time_t get_hz()
                {
                    return this->hertz;
                }
                void open(time_t hz); //timeouts_init
                void stop_timer(wtimer_t*); //timeouts_del
                int get_slot_idx(int wheel, time_t expires)
                {
                    return WHEEL_MASK
                            & ((expires >> (wheel * WHEEL_BIT)) - !!wheel);
                }
                int get_wheel_idx(time_t timeout) //timeout_wheel
                {
                    /* must be called with timeout != 0, so fls input is nonzero */
                    return (fls(MIN(timeout, TIMEOUT_MAX)) - 1) / WHEEL_BIT;
                }
                time_t get_rem(wtimer_t* to) //timeout_rem
                {
                    return to->abs_expires - this->curtime;
                }
                bool has_expired_timer() //timeouts_expired
                {
                    return !this->expired.empty();
                }
                bool has_pending_timer() //timeouts_pending
                {
                    wheel_t pending = 0;
                    int wheel;

                    for (wheel = 0; wheel < WHEEL_NUM; wheel++)
                    {
                        pending |= this->pending[wheel];
                    }
                    return !!pending;
                } /* timeouts_pending() */
                void add_timer(wtimer_t *to, time_t timeout);
                void sche_timer(wtimer_t *to, time_t expires);
#ifndef TIMEOUT_DISABLE_INTERVALS
                void readd_timer(wtimer_t *to);
#endif
                /** return any expired timeout (caller should loop until NULL-return) */
                wtimer_t *get_expired_timer(); //timeouts_get

                /**
                 *interval our caller can wait before needing to processevents.
                 * return interval to next required update */
                time_t get_timout_delta()
                {
                    return this->expired.empty() ? this->get_interval() : 0;
                }

                /** step timing wheel by relative time */
                void step(time_t elapsedtime)
                {
                    update(this->curtime + elapsedtime);
                }

                /**
                 * Calculate the slots expiring in this wheel
                 *
                 * If the elapsed time is greater than the maximum period of
                 * the wheel, mark every position as expiring.
                 *
                 * Otherwise, to determine the expired slots fill in all the
                 * bits between the last slot processed and the current
                 * slot, inclusive of the last slot. We'll bitwise-AND this
                 * with our pending set below.
                 *
                 * If a wheel rolls over, force a tick of the next higher wheel */
                void update(time_t abstime);
        };
        struct wtimers_it
        {
                int flags;
                unsigned pc, i, j;
                wtimer_t *to;
        };
    } /* namespace ds */
} /* namespace geco */

#endif /* SRC_COMMON_DS_WHEELTIMERMGRT_H_ */
