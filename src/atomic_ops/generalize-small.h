/*
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* char_load */
#if defined(AO_HAVE_char_load_full) && !defined(AO_HAVE_char_load_acquire)
# define AO_char_load_acquire(addr) AO_char_load_full(addr)
# define AO_HAVE_char_load_acquire
#endif

#if defined(AO_HAVE_char_load_acquire) && !defined(AO_HAVE_char_load)
# define AO_char_load(addr) AO_char_load_acquire(addr)
# define AO_HAVE_char_load
#endif

#if defined(AO_HAVE_char_load_full) && !defined(AO_HAVE_char_load_read)
# define AO_char_load_read(addr) AO_char_load_full(addr)
# define AO_HAVE_char_load_read
#endif

#if !defined(AO_HAVE_char_load_acquire_read) \
    && defined(AO_HAVE_char_load_acquire)
# define AO_char_load_acquire_read(addr) AO_char_load_acquire(addr)
# define AO_HAVE_char_load_acquire_read
#endif

#if defined(AO_HAVE_char_load) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_load_acquire)
  AO_INLINE unsigned/**/char
  AO_char_load_acquire(const volatile unsigned/**/char *addr)
  {
    unsigned/**/char result = AO_char_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_full();
    return result;
  }
# define AO_HAVE_char_load_acquire
#endif

#if defined(AO_HAVE_char_load) && defined(AO_HAVE_nop_read) \
    && !defined(AO_HAVE_char_load_read)
  AO_INLINE unsigned/**/char
  AO_char_load_read(const volatile unsigned/**/char *addr)
  {
    unsigned/**/char result = AO_char_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_read();
    return result;
  }
# define AO_HAVE_char_load_read
#endif

#if defined(AO_HAVE_char_load_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_load_full)
# define AO_char_load_full(addr) (AO_nop_full(), AO_char_load_acquire(addr))
# define AO_HAVE_char_load_full
#endif

#if !defined(AO_HAVE_char_load_acquire_read) \
    && defined(AO_HAVE_char_load_read)
# define AO_char_load_acquire_read(addr) AO_char_load_read(addr)
# define AO_HAVE_char_load_acquire_read
#endif

#if defined(AO_HAVE_char_load_acquire_read) && !defined(AO_HAVE_char_load)
# define AO_char_load(addr) AO_char_load_acquire_read(addr)
# define AO_HAVE_char_load
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_char_load_acquire_read)
#   define AO_char_load_dd_acquire_read(addr) AO_char_load_acquire_read(addr)
#   define AO_HAVE_char_load_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_char_load)
#   define AO_char_load_dd_acquire_read(addr) AO_char_load(addr)
#   define AO_HAVE_char_load_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* char_store */
#if defined(AO_HAVE_char_store_full) && !defined(AO_HAVE_char_store_release)
# define AO_char_store_release(addr,val) AO_char_store_full(addr,val)
# define AO_HAVE_char_store_release
#endif

#if defined(AO_HAVE_char_store_release) && !defined(AO_HAVE_char_store)
# define AO_char_store(addr, val) AO_char_store_release(addr,val)
# define AO_HAVE_char_store
#endif

#if defined(AO_HAVE_char_store_full) && !defined(AO_HAVE_char_store_write)
# define AO_char_store_write(addr,val) AO_char_store_full(addr,val)
# define AO_HAVE_char_store_write
#endif

#if defined(AO_HAVE_char_store_release) \
    && !defined(AO_HAVE_char_store_release_write)
# define AO_char_store_release_write(addr, val) \
                            AO_char_store_release(addr,val)
# define AO_HAVE_char_store_release_write
#endif

#if defined(AO_HAVE_char_store_write) && !defined(AO_HAVE_char_store)
# define AO_char_store(addr, val) AO_char_store_write(addr,val)
# define AO_HAVE_char_store
#endif

#if defined(AO_HAVE_char_store) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_store_release)
# define AO_char_store_release(addr,val) \
                                (AO_nop_full(), AO_char_store(addr,val))
# define AO_HAVE_char_store_release
#endif

#if defined(AO_HAVE_nop_write) && defined(AO_HAVE_char_store) \
    && !defined(AO_HAVE_char_store_write)
# define AO_char_store_write(addr, val) \
                                (AO_nop_write(), AO_char_store(addr,val))
# define AO_HAVE_char_store_write
#endif

#if defined(AO_HAVE_char_store_write) \
    && !defined(AO_HAVE_char_store_release_write)
# define AO_char_store_release_write(addr, val) AO_char_store_write(addr,val)
# define AO_HAVE_char_store_release_write
#endif

#if defined(AO_HAVE_char_store_release) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_store_full)
# define AO_char_store_full(addr, val) \
                        (AO_char_store_release(addr, val), AO_nop_full())
# define AO_HAVE_char_store_full
#endif

/* char_compare_and_swap */
#if defined(AO_HAVE_char_fetch_compare_and_swap_full) \
    && !defined(AO_HAVE_char_compare_and_swap_full)
  AO_INLINE int
  AO_char_compare_and_swap_full(volatile unsigned/**/char *addr, unsigned/**/char old_val,
                                 unsigned/**/char new_val)
  {
    return AO_char_fetch_compare_and_swap_full(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_char_compare_and_swap_full
#endif

#if defined(AO_HAVE_char_fetch_compare_and_swap_acquire) \
    && !defined(AO_HAVE_char_compare_and_swap_acquire)
  AO_INLINE int
  AO_char_compare_and_swap_acquire(volatile unsigned/**/char *addr, unsigned/**/char old_val,
                                    unsigned/**/char new_val)
  {
    return AO_char_fetch_compare_and_swap_acquire(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_char_compare_and_swap_acquire
#endif

#if defined(AO_HAVE_char_fetch_compare_and_swap_release) \
    && !defined(AO_HAVE_char_compare_and_swap_release)
  AO_INLINE int
  AO_char_compare_and_swap_release(volatile unsigned/**/char *addr, unsigned/**/char old_val,
                                    unsigned/**/char new_val)
  {
    return AO_char_fetch_compare_and_swap_release(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_char_compare_and_swap_release
#endif

#if defined(AO_HAVE_char_fetch_compare_and_swap) \
    && !defined(AO_HAVE_char_compare_and_swap)
  AO_INLINE int
  AO_char_compare_and_swap(volatile unsigned/**/char *addr, unsigned/**/char old_val,
                            unsigned/**/char new_val)
  {
    return AO_char_fetch_compare_and_swap(addr, old_val, new_val) == old_val;
  }
# define AO_HAVE_char_compare_and_swap
#endif

/* char_fetch_and_add */
/* We first try to implement fetch_and_add variants in terms of the     */
/* corresponding compare_and_swap variants to minimize adding barriers. */
#if defined(AO_HAVE_char_compare_and_swap_full) \
    && !defined(AO_HAVE_char_fetch_and_add_full)
  AO_INLINE unsigned/**/char
  AO_char_fetch_and_add_full(volatile unsigned/**/char *addr, unsigned/**/char incr)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_full(addr, old,
                                                           old + incr)));
    return old;
  }
# define AO_HAVE_char_fetch_and_add_full
#endif

#if defined(AO_HAVE_char_compare_and_swap_acquire) \
    && !defined(AO_HAVE_char_fetch_and_add_acquire)
  AO_INLINE unsigned/**/char
  AO_char_fetch_and_add_acquire(volatile unsigned/**/char *addr, unsigned/**/char incr)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_acquire(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_char_fetch_and_add_acquire
#endif

#if defined(AO_HAVE_char_compare_and_swap_release) \
    && !defined(AO_HAVE_char_fetch_and_add_release)
  AO_INLINE unsigned/**/char
  AO_char_fetch_and_add_release(volatile unsigned/**/char *addr, unsigned/**/char incr)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_release(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_char_fetch_and_add_release
#endif

#if defined(AO_HAVE_char_compare_and_swap) \
    && !defined(AO_HAVE_char_fetch_and_add)
  AO_INLINE unsigned/**/char
  AO_char_fetch_and_add(volatile unsigned/**/char *addr, unsigned/**/char incr)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap(addr, old,
                                                      old + incr)));
    return old;
  }
# define AO_HAVE_char_fetch_and_add
#endif

#if defined(AO_HAVE_char_fetch_and_add_full)
# if !defined(AO_HAVE_char_fetch_and_add_release)
#   define AO_char_fetch_and_add_release(addr, val) \
                                AO_char_fetch_and_add_full(addr, val)
#   define AO_HAVE_char_fetch_and_add_release
# endif
# if !defined(AO_HAVE_char_fetch_and_add_acquire)
#   define AO_char_fetch_and_add_acquire(addr, val) \
                                AO_char_fetch_and_add_full(addr, val)
#   define AO_HAVE_char_fetch_and_add_acquire
# endif
# if !defined(AO_HAVE_char_fetch_and_add_write)
#   define AO_char_fetch_and_add_write(addr, val) \
                                AO_char_fetch_and_add_full(addr, val)
#   define AO_HAVE_char_fetch_and_add_write
# endif
# if !defined(AO_HAVE_char_fetch_and_add_read)
#   define AO_char_fetch_and_add_read(addr, val) \
                                AO_char_fetch_and_add_full(addr, val)
#   define AO_HAVE_char_fetch_and_add_read
# endif
#endif /* AO_HAVE_char_fetch_and_add_full */

#if !defined(AO_HAVE_char_fetch_and_add) \
    && defined(AO_HAVE_char_fetch_and_add_release)
# define AO_char_fetch_and_add(addr, val) \
                                AO_char_fetch_and_add_release(addr, val)
# define AO_HAVE_char_fetch_and_add
#endif
#if !defined(AO_HAVE_char_fetch_and_add) \
    && defined(AO_HAVE_char_fetch_and_add_acquire)
# define AO_char_fetch_and_add(addr, val) \
                                AO_char_fetch_and_add_acquire(addr, val)
# define AO_HAVE_char_fetch_and_add
#endif
#if !defined(AO_HAVE_char_fetch_and_add) \
    && defined(AO_HAVE_char_fetch_and_add_write)
# define AO_char_fetch_and_add(addr, val) \
                                AO_char_fetch_and_add_write(addr, val)
# define AO_HAVE_char_fetch_and_add
#endif
#if !defined(AO_HAVE_char_fetch_and_add) \
    && defined(AO_HAVE_char_fetch_and_add_read)
# define AO_char_fetch_and_add(addr, val) \
                                AO_char_fetch_and_add_read(addr, val)
# define AO_HAVE_char_fetch_and_add
#endif

#if defined(AO_HAVE_char_fetch_and_add_acquire) \
    && defined(AO_HAVE_nop_full) && !defined(AO_HAVE_char_fetch_and_add_full)
# define AO_char_fetch_and_add_full(addr, val) \
                (AO_nop_full(), AO_char_fetch_and_add_acquire(addr, val))
# define AO_HAVE_char_fetch_and_add_full
#endif

#if !defined(AO_HAVE_char_fetch_and_add_release_write) \
    && defined(AO_HAVE_char_fetch_and_add_write)
# define AO_char_fetch_and_add_release_write(addr, val) \
                                AO_char_fetch_and_add_write(addr, val)
# define AO_HAVE_char_fetch_and_add_release_write
#endif
#if !defined(AO_HAVE_char_fetch_and_add_release_write) \
    && defined(AO_HAVE_char_fetch_and_add_release)
# define AO_char_fetch_and_add_release_write(addr, val) \
                                AO_char_fetch_and_add_release(addr, val)
# define AO_HAVE_char_fetch_and_add_release_write
#endif

#if !defined(AO_HAVE_char_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_add_read)
# define AO_char_fetch_and_add_acquire_read(addr, val) \
                                AO_char_fetch_and_add_read(addr, val)
# define AO_HAVE_char_fetch_and_add_acquire_read
#endif
#if !defined(AO_HAVE_char_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_add_acquire)
# define AO_char_fetch_and_add_acquire_read(addr, val) \
                                AO_char_fetch_and_add_acquire(addr, val)
# define AO_HAVE_char_fetch_and_add_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_char_fetch_and_add_acquire_read)
#   define AO_char_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_char_fetch_and_add_acquire_read(addr, val)
#   define AO_HAVE_char_fetch_and_add_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_char_fetch_and_add)
#   define AO_char_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_char_fetch_and_add(addr, val)
#   define AO_HAVE_char_fetch_and_add_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* char_fetch_and_add1 */
#if defined(AO_HAVE_char_fetch_and_add_full) \
    && !defined(AO_HAVE_char_fetch_and_add1_full)
# define AO_char_fetch_and_add1_full(addr) \
                                AO_char_fetch_and_add_full(addr,1)
# define AO_HAVE_char_fetch_and_add1_full
#endif
#if defined(AO_HAVE_char_fetch_and_add_release) \
    && !defined(AO_HAVE_char_fetch_and_add1_release)
# define AO_char_fetch_and_add1_release(addr) \
                                AO_char_fetch_and_add_release(addr,1)
# define AO_HAVE_char_fetch_and_add1_release
#endif
#if defined(AO_HAVE_char_fetch_and_add_acquire) \
    && !defined(AO_HAVE_char_fetch_and_add1_acquire)
# define AO_char_fetch_and_add1_acquire(addr) \
                                AO_char_fetch_and_add_acquire(addr,1)
# define AO_HAVE_char_fetch_and_add1_acquire
#endif
#if defined(AO_HAVE_char_fetch_and_add_write) \
    && !defined(AO_HAVE_char_fetch_and_add1_write)
# define AO_char_fetch_and_add1_write(addr) \
                                AO_char_fetch_and_add_write(addr,1)
# define AO_HAVE_char_fetch_and_add1_write
#endif
#if defined(AO_HAVE_char_fetch_and_add_read) \
    && !defined(AO_HAVE_char_fetch_and_add1_read)
# define AO_char_fetch_and_add1_read(addr) \
                                AO_char_fetch_and_add_read(addr,1)
# define AO_HAVE_char_fetch_and_add1_read
#endif
#if defined(AO_HAVE_char_fetch_and_add_release_write) \
    && !defined(AO_HAVE_char_fetch_and_add1_release_write)
# define AO_char_fetch_and_add1_release_write(addr) \
                                AO_char_fetch_and_add_release_write(addr,1)
# define AO_HAVE_char_fetch_and_add1_release_write
#endif
#if defined(AO_HAVE_char_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_char_fetch_and_add1_acquire_read)
# define AO_char_fetch_and_add1_acquire_read(addr) \
                                AO_char_fetch_and_add_acquire_read(addr,1)
# define AO_HAVE_char_fetch_and_add1_acquire_read
#endif
#if defined(AO_HAVE_char_fetch_and_add) \
    && !defined(AO_HAVE_char_fetch_and_add1)
# define AO_char_fetch_and_add1(addr) AO_char_fetch_and_add(addr,1)
# define AO_HAVE_char_fetch_and_add1
#endif

#if defined(AO_HAVE_char_fetch_and_add1_full)
# if !defined(AO_HAVE_char_fetch_and_add1_release)
#   define AO_char_fetch_and_add1_release(addr) \
                                AO_char_fetch_and_add1_full(addr)
#   define AO_HAVE_char_fetch_and_add1_release
# endif
# if !defined(AO_HAVE_char_fetch_and_add1_acquire)
#   define AO_char_fetch_and_add1_acquire(addr) \
                                AO_char_fetch_and_add1_full(addr)
#   define AO_HAVE_char_fetch_and_add1_acquire
# endif
# if !defined(AO_HAVE_char_fetch_and_add1_write)
#   define AO_char_fetch_and_add1_write(addr) \
                                AO_char_fetch_and_add1_full(addr)
#   define AO_HAVE_char_fetch_and_add1_write
# endif
# if !defined(AO_HAVE_char_fetch_and_add1_read)
#   define AO_char_fetch_and_add1_read(addr) \
                                AO_char_fetch_and_add1_full(addr)
#   define AO_HAVE_char_fetch_and_add1_read
# endif
#endif /* AO_HAVE_char_fetch_and_add1_full */

#if !defined(AO_HAVE_char_fetch_and_add1) \
    && defined(AO_HAVE_char_fetch_and_add1_release)
# define AO_char_fetch_and_add1(addr) AO_char_fetch_and_add1_release(addr)
# define AO_HAVE_char_fetch_and_add1
#endif
#if !defined(AO_HAVE_char_fetch_and_add1) \
    && defined(AO_HAVE_char_fetch_and_add1_acquire)
# define AO_char_fetch_and_add1(addr) AO_char_fetch_and_add1_acquire(addr)
# define AO_HAVE_char_fetch_and_add1
#endif
#if !defined(AO_HAVE_char_fetch_and_add1) \
    && defined(AO_HAVE_char_fetch_and_add1_write)
# define AO_char_fetch_and_add1(addr) AO_char_fetch_and_add1_write(addr)
# define AO_HAVE_char_fetch_and_add1
#endif
#if !defined(AO_HAVE_char_fetch_and_add1) \
    && defined(AO_HAVE_char_fetch_and_add1_read)
# define AO_char_fetch_and_add1(addr) AO_char_fetch_and_add1_read(addr)
# define AO_HAVE_char_fetch_and_add1
#endif

#if defined(AO_HAVE_char_fetch_and_add1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_fetch_and_add1_full)
# define AO_char_fetch_and_add1_full(addr) \
                        (AO_nop_full(), AO_char_fetch_and_add1_acquire(addr))
# define AO_HAVE_char_fetch_and_add1_full
#endif

#if !defined(AO_HAVE_char_fetch_and_add1_release_write) \
    && defined(AO_HAVE_char_fetch_and_add1_write)
# define AO_char_fetch_and_add1_release_write(addr) \
                                AO_char_fetch_and_add1_write(addr)
# define AO_HAVE_char_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_char_fetch_and_add1_release_write) \
    && defined(AO_HAVE_char_fetch_and_add1_release)
# define AO_char_fetch_and_add1_release_write(addr) \
                                AO_char_fetch_and_add1_release(addr)
# define AO_HAVE_char_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_char_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_add1_read)
# define AO_char_fetch_and_add1_acquire_read(addr) \
                                AO_char_fetch_and_add1_read(addr)
# define AO_HAVE_char_fetch_and_add1_acquire_read
#endif
#if !defined(AO_HAVE_char_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_add1_acquire)
# define AO_char_fetch_and_add1_acquire_read(addr) \
                                AO_char_fetch_and_add1_acquire(addr)
# define AO_HAVE_char_fetch_and_add1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_char_fetch_and_add1_acquire_read)
#   define AO_char_fetch_and_add1_dd_acquire_read(addr) \
                                AO_char_fetch_and_add1_acquire_read(addr)
#   define AO_HAVE_char_fetch_and_add1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_char_fetch_and_add1)
#   define AO_char_fetch_and_add1_dd_acquire_read(addr) \
                                AO_char_fetch_and_add1(addr)
#   define AO_HAVE_char_fetch_and_add1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* char_fetch_and_sub1 */
#if defined(AO_HAVE_char_fetch_and_add_full) \
    && !defined(AO_HAVE_char_fetch_and_sub1_full)
# define AO_char_fetch_and_sub1_full(addr) \
                AO_char_fetch_and_add_full(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_full
#endif
#if defined(AO_HAVE_char_fetch_and_add_release) \
    && !defined(AO_HAVE_char_fetch_and_sub1_release)
# define AO_char_fetch_and_sub1_release(addr) \
                AO_char_fetch_and_add_release(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_release
#endif
#if defined(AO_HAVE_char_fetch_and_add_acquire) \
    && !defined(AO_HAVE_char_fetch_and_sub1_acquire)
# define AO_char_fetch_and_sub1_acquire(addr) \
                AO_char_fetch_and_add_acquire(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_acquire
#endif
#if defined(AO_HAVE_char_fetch_and_add_write) \
    && !defined(AO_HAVE_char_fetch_and_sub1_write)
# define AO_char_fetch_and_sub1_write(addr) \
                AO_char_fetch_and_add_write(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_write
#endif
#if defined(AO_HAVE_char_fetch_and_add_read) \
    && !defined(AO_HAVE_char_fetch_and_sub1_read)
# define AO_char_fetch_and_sub1_read(addr) \
                AO_char_fetch_and_add_read(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_read
#endif
#if defined(AO_HAVE_char_fetch_and_add_release_write) \
    && !defined(AO_HAVE_char_fetch_and_sub1_release_write)
# define AO_char_fetch_and_sub1_release_write(addr) \
                AO_char_fetch_and_add_release_write(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_release_write
#endif
#if defined(AO_HAVE_char_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_char_fetch_and_sub1_acquire_read)
# define AO_char_fetch_and_sub1_acquire_read(addr) \
                AO_char_fetch_and_add_acquire_read(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1_acquire_read
#endif
#if defined(AO_HAVE_char_fetch_and_add) \
    && !defined(AO_HAVE_char_fetch_and_sub1)
# define AO_char_fetch_and_sub1(addr) \
                AO_char_fetch_and_add(addr, (unsigned/**/char)(-1))
# define AO_HAVE_char_fetch_and_sub1
#endif

#if defined(AO_HAVE_char_fetch_and_sub1_full)
# if !defined(AO_HAVE_char_fetch_and_sub1_release)
#   define AO_char_fetch_and_sub1_release(addr) \
                                AO_char_fetch_and_sub1_full(addr)
#   define AO_HAVE_char_fetch_and_sub1_release
# endif
# if !defined(AO_HAVE_char_fetch_and_sub1_acquire)
#   define AO_char_fetch_and_sub1_acquire(addr) \
                                AO_char_fetch_and_sub1_full(addr)
#   define AO_HAVE_char_fetch_and_sub1_acquire
# endif
# if !defined(AO_HAVE_char_fetch_and_sub1_write)
#   define AO_char_fetch_and_sub1_write(addr) \
                                AO_char_fetch_and_sub1_full(addr)
#   define AO_HAVE_char_fetch_and_sub1_write
# endif
# if !defined(AO_HAVE_char_fetch_and_sub1_read)
#   define AO_char_fetch_and_sub1_read(addr) \
                                AO_char_fetch_and_sub1_full(addr)
#   define AO_HAVE_char_fetch_and_sub1_read
# endif
#endif /* AO_HAVE_char_fetch_and_sub1_full */

#if !defined(AO_HAVE_char_fetch_and_sub1) \
    && defined(AO_HAVE_char_fetch_and_sub1_release)
# define AO_char_fetch_and_sub1(addr) AO_char_fetch_and_sub1_release(addr)
# define AO_HAVE_char_fetch_and_sub1
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1) \
    && defined(AO_HAVE_char_fetch_and_sub1_acquire)
# define AO_char_fetch_and_sub1(addr) AO_char_fetch_and_sub1_acquire(addr)
# define AO_HAVE_char_fetch_and_sub1
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1) \
    && defined(AO_HAVE_char_fetch_and_sub1_write)
# define AO_char_fetch_and_sub1(addr) AO_char_fetch_and_sub1_write(addr)
# define AO_HAVE_char_fetch_and_sub1
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1) \
    && defined(AO_HAVE_char_fetch_and_sub1_read)
# define AO_char_fetch_and_sub1(addr) AO_char_fetch_and_sub1_read(addr)
# define AO_HAVE_char_fetch_and_sub1
#endif

#if defined(AO_HAVE_char_fetch_and_sub1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_fetch_and_sub1_full)
# define AO_char_fetch_and_sub1_full(addr) \
                        (AO_nop_full(), AO_char_fetch_and_sub1_acquire(addr))
# define AO_HAVE_char_fetch_and_sub1_full
#endif

#if !defined(AO_HAVE_char_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_char_fetch_and_sub1_write)
# define AO_char_fetch_and_sub1_release_write(addr) \
                                AO_char_fetch_and_sub1_write(addr)
# define AO_HAVE_char_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_char_fetch_and_sub1_release)
# define AO_char_fetch_and_sub1_release_write(addr) \
                                AO_char_fetch_and_sub1_release(addr)
# define AO_HAVE_char_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_sub1_read)
# define AO_char_fetch_and_sub1_acquire_read(addr) \
                                AO_char_fetch_and_sub1_read(addr)
# define AO_HAVE_char_fetch_and_sub1_acquire_read
#endif
#if !defined(AO_HAVE_char_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_char_fetch_and_sub1_acquire)
# define AO_char_fetch_and_sub1_acquire_read(addr) \
                                AO_char_fetch_and_sub1_acquire(addr)
# define AO_HAVE_char_fetch_and_sub1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_char_fetch_and_sub1_acquire_read)
#   define AO_char_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_char_fetch_and_sub1_acquire_read(addr)
#   define AO_HAVE_char_fetch_and_sub1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_char_fetch_and_sub1)
#   define AO_char_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_char_fetch_and_sub1(addr)
#   define AO_HAVE_char_fetch_and_sub1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* char_and */
#if defined(AO_HAVE_char_compare_and_swap_full) \
    && !defined(AO_HAVE_char_and_full)
  AO_INLINE void
  AO_char_and_full(volatile unsigned/**/char *addr, unsigned/**/char value)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_full(addr, old,
                                                           old & value)));
  }
# define AO_HAVE_char_and_full
#endif

#if defined(AO_HAVE_char_and_full)
# if !defined(AO_HAVE_char_and_release)
#   define AO_char_and_release(addr, val) AO_char_and_full(addr, val)
#   define AO_HAVE_char_and_release
# endif
# if !defined(AO_HAVE_char_and_acquire)
#   define AO_char_and_acquire(addr, val) AO_char_and_full(addr, val)
#   define AO_HAVE_char_and_acquire
# endif
# if !defined(AO_HAVE_char_and_write)
#   define AO_char_and_write(addr, val) AO_char_and_full(addr, val)
#   define AO_HAVE_char_and_write
# endif
# if !defined(AO_HAVE_char_and_read)
#   define AO_char_and_read(addr, val) AO_char_and_full(addr, val)
#   define AO_HAVE_char_and_read
# endif
#endif /* AO_HAVE_char_and_full */

#if !defined(AO_HAVE_char_and) && defined(AO_HAVE_char_and_release)
# define AO_char_and(addr, val) AO_char_and_release(addr, val)
# define AO_HAVE_char_and
#endif
#if !defined(AO_HAVE_char_and) && defined(AO_HAVE_char_and_acquire)
# define AO_char_and(addr, val) AO_char_and_acquire(addr, val)
# define AO_HAVE_char_and
#endif
#if !defined(AO_HAVE_char_and) && defined(AO_HAVE_char_and_write)
# define AO_char_and(addr, val) AO_char_and_write(addr, val)
# define AO_HAVE_char_and
#endif
#if !defined(AO_HAVE_char_and) && defined(AO_HAVE_char_and_read)
# define AO_char_and(addr, val) AO_char_and_read(addr, val)
# define AO_HAVE_char_and
#endif

#if defined(AO_HAVE_char_and_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_and_full)
# define AO_char_and_full(addr, val) \
                        (AO_nop_full(), AO_char_and_acquire(addr, val))
# define AO_HAVE_char_and_full
#endif

#if !defined(AO_HAVE_char_and_release_write) \
    && defined(AO_HAVE_char_and_write)
# define AO_char_and_release_write(addr, val) AO_char_and_write(addr, val)
# define AO_HAVE_char_and_release_write
#endif
#if !defined(AO_HAVE_char_and_release_write) \
    && defined(AO_HAVE_char_and_release)
# define AO_char_and_release_write(addr, val) AO_char_and_release(addr, val)
# define AO_HAVE_char_and_release_write
#endif
#if !defined(AO_HAVE_char_and_acquire_read) \
    && defined(AO_HAVE_char_and_read)
# define AO_char_and_acquire_read(addr, val) AO_char_and_read(addr, val)
# define AO_HAVE_char_and_acquire_read
#endif
#if !defined(AO_HAVE_char_and_acquire_read) \
    && defined(AO_HAVE_char_and_acquire)
# define AO_char_and_acquire_read(addr, val) AO_char_and_acquire(addr, val)
# define AO_HAVE_char_and_acquire_read
#endif

/* char_or */
#if defined(AO_HAVE_char_compare_and_swap_full) \
    && !defined(AO_HAVE_char_or_full)
  AO_INLINE void
  AO_char_or_full(volatile unsigned/**/char *addr, unsigned/**/char value)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_full(addr, old,
                                                           old | value)));
  }
# define AO_HAVE_char_or_full
#endif

#if defined(AO_HAVE_char_or_full)
# if !defined(AO_HAVE_char_or_release)
#   define AO_char_or_release(addr, val) AO_char_or_full(addr, val)
#   define AO_HAVE_char_or_release
# endif
# if !defined(AO_HAVE_char_or_acquire)
#   define AO_char_or_acquire(addr, val) AO_char_or_full(addr, val)
#   define AO_HAVE_char_or_acquire
# endif
# if !defined(AO_HAVE_char_or_write)
#   define AO_char_or_write(addr, val) AO_char_or_full(addr, val)
#   define AO_HAVE_char_or_write
# endif
# if !defined(AO_HAVE_char_or_read)
#   define AO_char_or_read(addr, val) AO_char_or_full(addr, val)
#   define AO_HAVE_char_or_read
# endif
#endif /* AO_HAVE_char_or_full */

#if !defined(AO_HAVE_char_or) && defined(AO_HAVE_char_or_release)
# define AO_char_or(addr, val) AO_char_or_release(addr, val)
# define AO_HAVE_char_or
#endif
#if !defined(AO_HAVE_char_or) && defined(AO_HAVE_char_or_acquire)
# define AO_char_or(addr, val) AO_char_or_acquire(addr, val)
# define AO_HAVE_char_or
#endif
#if !defined(AO_HAVE_char_or) && defined(AO_HAVE_char_or_write)
# define AO_char_or(addr, val) AO_char_or_write(addr, val)
# define AO_HAVE_char_or
#endif
#if !defined(AO_HAVE_char_or) && defined(AO_HAVE_char_or_read)
# define AO_char_or(addr, val) AO_char_or_read(addr, val)
# define AO_HAVE_char_or
#endif

#if defined(AO_HAVE_char_or_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_or_full)
# define AO_char_or_full(addr, val) \
                        (AO_nop_full(), AO_char_or_acquire(addr, val))
# define AO_HAVE_char_or_full
#endif

#if !defined(AO_HAVE_char_or_release_write) \
    && defined(AO_HAVE_char_or_write)
# define AO_char_or_release_write(addr, val) AO_char_or_write(addr, val)
# define AO_HAVE_char_or_release_write
#endif
#if !defined(AO_HAVE_char_or_release_write) \
    && defined(AO_HAVE_char_or_release)
# define AO_char_or_release_write(addr, val) AO_char_or_release(addr, val)
# define AO_HAVE_char_or_release_write
#endif
#if !defined(AO_HAVE_char_or_acquire_read) && defined(AO_HAVE_char_or_read)
# define AO_char_or_acquire_read(addr, val) AO_char_or_read(addr, val)
# define AO_HAVE_char_or_acquire_read
#endif
#if !defined(AO_HAVE_char_or_acquire_read) \
    && defined(AO_HAVE_char_or_acquire)
# define AO_char_or_acquire_read(addr, val) AO_char_or_acquire(addr, val)
# define AO_HAVE_char_or_acquire_read
#endif

/* char_xor */
#if defined(AO_HAVE_char_compare_and_swap_full) \
    && !defined(AO_HAVE_char_xor_full)
  AO_INLINE void
  AO_char_xor_full(volatile unsigned/**/char *addr, unsigned/**/char value)
  {
    unsigned/**/char old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_char_compare_and_swap_full(addr, old,
                                                           old ^ value)));
  }
# define AO_HAVE_char_xor_full
#endif

#if defined(AO_HAVE_char_xor_full)
# if !defined(AO_HAVE_char_xor_release)
#   define AO_char_xor_release(addr, val) AO_char_xor_full(addr, val)
#   define AO_HAVE_char_xor_release
# endif
# if !defined(AO_HAVE_char_xor_acquire)
#   define AO_char_xor_acquire(addr, val) AO_char_xor_full(addr, val)
#   define AO_HAVE_char_xor_acquire
# endif
# if !defined(AO_HAVE_char_xor_write)
#   define AO_char_xor_write(addr, val) AO_char_xor_full(addr, val)
#   define AO_HAVE_char_xor_write
# endif
# if !defined(AO_HAVE_char_xor_read)
#   define AO_char_xor_read(addr, val) AO_char_xor_full(addr, val)
#   define AO_HAVE_char_xor_read
# endif
#endif /* AO_HAVE_char_xor_full */

#if !defined(AO_HAVE_char_xor) && defined(AO_HAVE_char_xor_release)
# define AO_char_xor(addr, val) AO_char_xor_release(addr, val)
# define AO_HAVE_char_xor
#endif
#if !defined(AO_HAVE_char_xor) && defined(AO_HAVE_char_xor_acquire)
# define AO_char_xor(addr, val) AO_char_xor_acquire(addr, val)
# define AO_HAVE_char_xor
#endif
#if !defined(AO_HAVE_char_xor) && defined(AO_HAVE_char_xor_write)
# define AO_char_xor(addr, val) AO_char_xor_write(addr, val)
# define AO_HAVE_char_xor
#endif
#if !defined(AO_HAVE_char_xor) && defined(AO_HAVE_char_xor_read)
# define AO_char_xor(addr, val) AO_char_xor_read(addr, val)
# define AO_HAVE_char_xor
#endif

#if defined(AO_HAVE_char_xor_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_char_xor_full)
# define AO_char_xor_full(addr, val) \
                        (AO_nop_full(), AO_char_xor_acquire(addr, val))
# define AO_HAVE_char_xor_full
#endif

#if !defined(AO_HAVE_char_xor_release_write) \
    && defined(AO_HAVE_char_xor_write)
# define AO_char_xor_release_write(addr, val) AO_char_xor_write(addr, val)
# define AO_HAVE_char_xor_release_write
#endif
#if !defined(AO_HAVE_char_xor_release_write) \
    && defined(AO_HAVE_char_xor_release)
# define AO_char_xor_release_write(addr, val) AO_char_xor_release(addr, val)
# define AO_HAVE_char_xor_release_write
#endif
#if !defined(AO_HAVE_char_xor_acquire_read) \
    && defined(AO_HAVE_char_xor_read)
# define AO_char_xor_acquire_read(addr, val) AO_char_xor_read(addr, val)
# define AO_HAVE_char_xor_acquire_read
#endif
#if !defined(AO_HAVE_char_xor_acquire_read) \
    && defined(AO_HAVE_char_xor_acquire)
# define AO_char_xor_acquire_read(addr, val) AO_char_xor_acquire(addr, val)
# define AO_HAVE_char_xor_acquire_read
#endif

/* char_and/or/xor_dd_aquire_read are meaningless.     */
/*
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* short_load */
#if defined(AO_HAVE_short_load_full) && !defined(AO_HAVE_short_load_acquire)
# define AO_short_load_acquire(addr) AO_short_load_full(addr)
# define AO_HAVE_short_load_acquire
#endif

#if defined(AO_HAVE_short_load_acquire) && !defined(AO_HAVE_short_load)
# define AO_short_load(addr) AO_short_load_acquire(addr)
# define AO_HAVE_short_load
#endif

#if defined(AO_HAVE_short_load_full) && !defined(AO_HAVE_short_load_read)
# define AO_short_load_read(addr) AO_short_load_full(addr)
# define AO_HAVE_short_load_read
#endif

#if !defined(AO_HAVE_short_load_acquire_read) \
    && defined(AO_HAVE_short_load_acquire)
# define AO_short_load_acquire_read(addr) AO_short_load_acquire(addr)
# define AO_HAVE_short_load_acquire_read
#endif

#if defined(AO_HAVE_short_load) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_load_acquire)
  AO_INLINE unsigned/**/short
  AO_short_load_acquire(const volatile unsigned/**/short *addr)
  {
    unsigned/**/short result = AO_short_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_full();
    return result;
  }
# define AO_HAVE_short_load_acquire
#endif

#if defined(AO_HAVE_short_load) && defined(AO_HAVE_nop_read) \
    && !defined(AO_HAVE_short_load_read)
  AO_INLINE unsigned/**/short
  AO_short_load_read(const volatile unsigned/**/short *addr)
  {
    unsigned/**/short result = AO_short_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_read();
    return result;
  }
# define AO_HAVE_short_load_read
#endif

#if defined(AO_HAVE_short_load_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_load_full)
# define AO_short_load_full(addr) (AO_nop_full(), AO_short_load_acquire(addr))
# define AO_HAVE_short_load_full
#endif

#if !defined(AO_HAVE_short_load_acquire_read) \
    && defined(AO_HAVE_short_load_read)
# define AO_short_load_acquire_read(addr) AO_short_load_read(addr)
# define AO_HAVE_short_load_acquire_read
#endif

#if defined(AO_HAVE_short_load_acquire_read) && !defined(AO_HAVE_short_load)
# define AO_short_load(addr) AO_short_load_acquire_read(addr)
# define AO_HAVE_short_load
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_short_load_acquire_read)
#   define AO_short_load_dd_acquire_read(addr) AO_short_load_acquire_read(addr)
#   define AO_HAVE_short_load_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_short_load)
#   define AO_short_load_dd_acquire_read(addr) AO_short_load(addr)
#   define AO_HAVE_short_load_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* short_store */
#if defined(AO_HAVE_short_store_full) && !defined(AO_HAVE_short_store_release)
# define AO_short_store_release(addr,val) AO_short_store_full(addr,val)
# define AO_HAVE_short_store_release
#endif

#if defined(AO_HAVE_short_store_release) && !defined(AO_HAVE_short_store)
# define AO_short_store(addr, val) AO_short_store_release(addr,val)
# define AO_HAVE_short_store
#endif

#if defined(AO_HAVE_short_store_full) && !defined(AO_HAVE_short_store_write)
# define AO_short_store_write(addr,val) AO_short_store_full(addr,val)
# define AO_HAVE_short_store_write
#endif

#if defined(AO_HAVE_short_store_release) \
    && !defined(AO_HAVE_short_store_release_write)
# define AO_short_store_release_write(addr, val) \
                            AO_short_store_release(addr,val)
# define AO_HAVE_short_store_release_write
#endif

#if defined(AO_HAVE_short_store_write) && !defined(AO_HAVE_short_store)
# define AO_short_store(addr, val) AO_short_store_write(addr,val)
# define AO_HAVE_short_store
#endif

#if defined(AO_HAVE_short_store) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_store_release)
# define AO_short_store_release(addr,val) \
                                (AO_nop_full(), AO_short_store(addr,val))
# define AO_HAVE_short_store_release
#endif

#if defined(AO_HAVE_nop_write) && defined(AO_HAVE_short_store) \
    && !defined(AO_HAVE_short_store_write)
# define AO_short_store_write(addr, val) \
                                (AO_nop_write(), AO_short_store(addr,val))
# define AO_HAVE_short_store_write
#endif

#if defined(AO_HAVE_short_store_write) \
    && !defined(AO_HAVE_short_store_release_write)
# define AO_short_store_release_write(addr, val) AO_short_store_write(addr,val)
# define AO_HAVE_short_store_release_write
#endif

#if defined(AO_HAVE_short_store_release) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_store_full)
# define AO_short_store_full(addr, val) \
                        (AO_short_store_release(addr, val), AO_nop_full())
# define AO_HAVE_short_store_full
#endif

/* short_compare_and_swap */
#if defined(AO_HAVE_short_fetch_compare_and_swap_full) \
    && !defined(AO_HAVE_short_compare_and_swap_full)
  AO_INLINE int
  AO_short_compare_and_swap_full(volatile unsigned/**/short *addr, unsigned/**/short old_val,
                                 unsigned/**/short new_val)
  {
    return AO_short_fetch_compare_and_swap_full(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_short_compare_and_swap_full
#endif

#if defined(AO_HAVE_short_fetch_compare_and_swap_acquire) \
    && !defined(AO_HAVE_short_compare_and_swap_acquire)
  AO_INLINE int
  AO_short_compare_and_swap_acquire(volatile unsigned/**/short *addr, unsigned/**/short old_val,
                                    unsigned/**/short new_val)
  {
    return AO_short_fetch_compare_and_swap_acquire(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_short_compare_and_swap_acquire
#endif

#if defined(AO_HAVE_short_fetch_compare_and_swap_release) \
    && !defined(AO_HAVE_short_compare_and_swap_release)
  AO_INLINE int
  AO_short_compare_and_swap_release(volatile unsigned/**/short *addr, unsigned/**/short old_val,
                                    unsigned/**/short new_val)
  {
    return AO_short_fetch_compare_and_swap_release(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_short_compare_and_swap_release
#endif

#if defined(AO_HAVE_short_fetch_compare_and_swap) \
    && !defined(AO_HAVE_short_compare_and_swap)
  AO_INLINE int
  AO_short_compare_and_swap(volatile unsigned/**/short *addr, unsigned/**/short old_val,
                            unsigned/**/short new_val)
  {
    return AO_short_fetch_compare_and_swap(addr, old_val, new_val) == old_val;
  }
# define AO_HAVE_short_compare_and_swap
#endif

/* short_fetch_and_add */
/* We first try to implement fetch_and_add variants in terms of the     */
/* corresponding compare_and_swap variants to minimize adding barriers. */
#if defined(AO_HAVE_short_compare_and_swap_full) \
    && !defined(AO_HAVE_short_fetch_and_add_full)
  AO_INLINE unsigned/**/short
  AO_short_fetch_and_add_full(volatile unsigned/**/short *addr, unsigned/**/short incr)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_full(addr, old,
                                                           old + incr)));
    return old;
  }
# define AO_HAVE_short_fetch_and_add_full
#endif

#if defined(AO_HAVE_short_compare_and_swap_acquire) \
    && !defined(AO_HAVE_short_fetch_and_add_acquire)
  AO_INLINE unsigned/**/short
  AO_short_fetch_and_add_acquire(volatile unsigned/**/short *addr, unsigned/**/short incr)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_acquire(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_short_fetch_and_add_acquire
#endif

#if defined(AO_HAVE_short_compare_and_swap_release) \
    && !defined(AO_HAVE_short_fetch_and_add_release)
  AO_INLINE unsigned/**/short
  AO_short_fetch_and_add_release(volatile unsigned/**/short *addr, unsigned/**/short incr)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_release(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_short_fetch_and_add_release
#endif

#if defined(AO_HAVE_short_compare_and_swap) \
    && !defined(AO_HAVE_short_fetch_and_add)
  AO_INLINE unsigned/**/short
  AO_short_fetch_and_add(volatile unsigned/**/short *addr, unsigned/**/short incr)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap(addr, old,
                                                      old + incr)));
    return old;
  }
# define AO_HAVE_short_fetch_and_add
#endif

#if defined(AO_HAVE_short_fetch_and_add_full)
# if !defined(AO_HAVE_short_fetch_and_add_release)
#   define AO_short_fetch_and_add_release(addr, val) \
                                AO_short_fetch_and_add_full(addr, val)
#   define AO_HAVE_short_fetch_and_add_release
# endif
# if !defined(AO_HAVE_short_fetch_and_add_acquire)
#   define AO_short_fetch_and_add_acquire(addr, val) \
                                AO_short_fetch_and_add_full(addr, val)
#   define AO_HAVE_short_fetch_and_add_acquire
# endif
# if !defined(AO_HAVE_short_fetch_and_add_write)
#   define AO_short_fetch_and_add_write(addr, val) \
                                AO_short_fetch_and_add_full(addr, val)
#   define AO_HAVE_short_fetch_and_add_write
# endif
# if !defined(AO_HAVE_short_fetch_and_add_read)
#   define AO_short_fetch_and_add_read(addr, val) \
                                AO_short_fetch_and_add_full(addr, val)
#   define AO_HAVE_short_fetch_and_add_read
# endif
#endif /* AO_HAVE_short_fetch_and_add_full */

#if !defined(AO_HAVE_short_fetch_and_add) \
    && defined(AO_HAVE_short_fetch_and_add_release)
# define AO_short_fetch_and_add(addr, val) \
                                AO_short_fetch_and_add_release(addr, val)
# define AO_HAVE_short_fetch_and_add
#endif
#if !defined(AO_HAVE_short_fetch_and_add) \
    && defined(AO_HAVE_short_fetch_and_add_acquire)
# define AO_short_fetch_and_add(addr, val) \
                                AO_short_fetch_and_add_acquire(addr, val)
# define AO_HAVE_short_fetch_and_add
#endif
#if !defined(AO_HAVE_short_fetch_and_add) \
    && defined(AO_HAVE_short_fetch_and_add_write)
# define AO_short_fetch_and_add(addr, val) \
                                AO_short_fetch_and_add_write(addr, val)
# define AO_HAVE_short_fetch_and_add
#endif
#if !defined(AO_HAVE_short_fetch_and_add) \
    && defined(AO_HAVE_short_fetch_and_add_read)
# define AO_short_fetch_and_add(addr, val) \
                                AO_short_fetch_and_add_read(addr, val)
# define AO_HAVE_short_fetch_and_add
#endif

#if defined(AO_HAVE_short_fetch_and_add_acquire) \
    && defined(AO_HAVE_nop_full) && !defined(AO_HAVE_short_fetch_and_add_full)
# define AO_short_fetch_and_add_full(addr, val) \
                (AO_nop_full(), AO_short_fetch_and_add_acquire(addr, val))
# define AO_HAVE_short_fetch_and_add_full
#endif

#if !defined(AO_HAVE_short_fetch_and_add_release_write) \
    && defined(AO_HAVE_short_fetch_and_add_write)
# define AO_short_fetch_and_add_release_write(addr, val) \
                                AO_short_fetch_and_add_write(addr, val)
# define AO_HAVE_short_fetch_and_add_release_write
#endif
#if !defined(AO_HAVE_short_fetch_and_add_release_write) \
    && defined(AO_HAVE_short_fetch_and_add_release)
# define AO_short_fetch_and_add_release_write(addr, val) \
                                AO_short_fetch_and_add_release(addr, val)
# define AO_HAVE_short_fetch_and_add_release_write
#endif

#if !defined(AO_HAVE_short_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_add_read)
# define AO_short_fetch_and_add_acquire_read(addr, val) \
                                AO_short_fetch_and_add_read(addr, val)
# define AO_HAVE_short_fetch_and_add_acquire_read
#endif
#if !defined(AO_HAVE_short_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_add_acquire)
# define AO_short_fetch_and_add_acquire_read(addr, val) \
                                AO_short_fetch_and_add_acquire(addr, val)
# define AO_HAVE_short_fetch_and_add_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_short_fetch_and_add_acquire_read)
#   define AO_short_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_short_fetch_and_add_acquire_read(addr, val)
#   define AO_HAVE_short_fetch_and_add_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_short_fetch_and_add)
#   define AO_short_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_short_fetch_and_add(addr, val)
#   define AO_HAVE_short_fetch_and_add_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* short_fetch_and_add1 */
#if defined(AO_HAVE_short_fetch_and_add_full) \
    && !defined(AO_HAVE_short_fetch_and_add1_full)
# define AO_short_fetch_and_add1_full(addr) \
                                AO_short_fetch_and_add_full(addr,1)
# define AO_HAVE_short_fetch_and_add1_full
#endif
#if defined(AO_HAVE_short_fetch_and_add_release) \
    && !defined(AO_HAVE_short_fetch_and_add1_release)
# define AO_short_fetch_and_add1_release(addr) \
                                AO_short_fetch_and_add_release(addr,1)
# define AO_HAVE_short_fetch_and_add1_release
#endif
#if defined(AO_HAVE_short_fetch_and_add_acquire) \
    && !defined(AO_HAVE_short_fetch_and_add1_acquire)
# define AO_short_fetch_and_add1_acquire(addr) \
                                AO_short_fetch_and_add_acquire(addr,1)
# define AO_HAVE_short_fetch_and_add1_acquire
#endif
#if defined(AO_HAVE_short_fetch_and_add_write) \
    && !defined(AO_HAVE_short_fetch_and_add1_write)
# define AO_short_fetch_and_add1_write(addr) \
                                AO_short_fetch_and_add_write(addr,1)
# define AO_HAVE_short_fetch_and_add1_write
#endif
#if defined(AO_HAVE_short_fetch_and_add_read) \
    && !defined(AO_HAVE_short_fetch_and_add1_read)
# define AO_short_fetch_and_add1_read(addr) \
                                AO_short_fetch_and_add_read(addr,1)
# define AO_HAVE_short_fetch_and_add1_read
#endif
#if defined(AO_HAVE_short_fetch_and_add_release_write) \
    && !defined(AO_HAVE_short_fetch_and_add1_release_write)
# define AO_short_fetch_and_add1_release_write(addr) \
                                AO_short_fetch_and_add_release_write(addr,1)
# define AO_HAVE_short_fetch_and_add1_release_write
#endif
#if defined(AO_HAVE_short_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_short_fetch_and_add1_acquire_read)
# define AO_short_fetch_and_add1_acquire_read(addr) \
                                AO_short_fetch_and_add_acquire_read(addr,1)
# define AO_HAVE_short_fetch_and_add1_acquire_read
#endif
#if defined(AO_HAVE_short_fetch_and_add) \
    && !defined(AO_HAVE_short_fetch_and_add1)
# define AO_short_fetch_and_add1(addr) AO_short_fetch_and_add(addr,1)
# define AO_HAVE_short_fetch_and_add1
#endif

#if defined(AO_HAVE_short_fetch_and_add1_full)
# if !defined(AO_HAVE_short_fetch_and_add1_release)
#   define AO_short_fetch_and_add1_release(addr) \
                                AO_short_fetch_and_add1_full(addr)
#   define AO_HAVE_short_fetch_and_add1_release
# endif
# if !defined(AO_HAVE_short_fetch_and_add1_acquire)
#   define AO_short_fetch_and_add1_acquire(addr) \
                                AO_short_fetch_and_add1_full(addr)
#   define AO_HAVE_short_fetch_and_add1_acquire
# endif
# if !defined(AO_HAVE_short_fetch_and_add1_write)
#   define AO_short_fetch_and_add1_write(addr) \
                                AO_short_fetch_and_add1_full(addr)
#   define AO_HAVE_short_fetch_and_add1_write
# endif
# if !defined(AO_HAVE_short_fetch_and_add1_read)
#   define AO_short_fetch_and_add1_read(addr) \
                                AO_short_fetch_and_add1_full(addr)
#   define AO_HAVE_short_fetch_and_add1_read
# endif
#endif /* AO_HAVE_short_fetch_and_add1_full */

#if !defined(AO_HAVE_short_fetch_and_add1) \
    && defined(AO_HAVE_short_fetch_and_add1_release)
# define AO_short_fetch_and_add1(addr) AO_short_fetch_and_add1_release(addr)
# define AO_HAVE_short_fetch_and_add1
#endif
#if !defined(AO_HAVE_short_fetch_and_add1) \
    && defined(AO_HAVE_short_fetch_and_add1_acquire)
# define AO_short_fetch_and_add1(addr) AO_short_fetch_and_add1_acquire(addr)
# define AO_HAVE_short_fetch_and_add1
#endif
#if !defined(AO_HAVE_short_fetch_and_add1) \
    && defined(AO_HAVE_short_fetch_and_add1_write)
# define AO_short_fetch_and_add1(addr) AO_short_fetch_and_add1_write(addr)
# define AO_HAVE_short_fetch_and_add1
#endif
#if !defined(AO_HAVE_short_fetch_and_add1) \
    && defined(AO_HAVE_short_fetch_and_add1_read)
# define AO_short_fetch_and_add1(addr) AO_short_fetch_and_add1_read(addr)
# define AO_HAVE_short_fetch_and_add1
#endif

#if defined(AO_HAVE_short_fetch_and_add1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_fetch_and_add1_full)
# define AO_short_fetch_and_add1_full(addr) \
                        (AO_nop_full(), AO_short_fetch_and_add1_acquire(addr))
# define AO_HAVE_short_fetch_and_add1_full
#endif

#if !defined(AO_HAVE_short_fetch_and_add1_release_write) \
    && defined(AO_HAVE_short_fetch_and_add1_write)
# define AO_short_fetch_and_add1_release_write(addr) \
                                AO_short_fetch_and_add1_write(addr)
# define AO_HAVE_short_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_short_fetch_and_add1_release_write) \
    && defined(AO_HAVE_short_fetch_and_add1_release)
# define AO_short_fetch_and_add1_release_write(addr) \
                                AO_short_fetch_and_add1_release(addr)
# define AO_HAVE_short_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_short_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_add1_read)
# define AO_short_fetch_and_add1_acquire_read(addr) \
                                AO_short_fetch_and_add1_read(addr)
# define AO_HAVE_short_fetch_and_add1_acquire_read
#endif
#if !defined(AO_HAVE_short_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_add1_acquire)
# define AO_short_fetch_and_add1_acquire_read(addr) \
                                AO_short_fetch_and_add1_acquire(addr)
# define AO_HAVE_short_fetch_and_add1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_short_fetch_and_add1_acquire_read)
#   define AO_short_fetch_and_add1_dd_acquire_read(addr) \
                                AO_short_fetch_and_add1_acquire_read(addr)
#   define AO_HAVE_short_fetch_and_add1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_short_fetch_and_add1)
#   define AO_short_fetch_and_add1_dd_acquire_read(addr) \
                                AO_short_fetch_and_add1(addr)
#   define AO_HAVE_short_fetch_and_add1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* short_fetch_and_sub1 */
#if defined(AO_HAVE_short_fetch_and_add_full) \
    && !defined(AO_HAVE_short_fetch_and_sub1_full)
# define AO_short_fetch_and_sub1_full(addr) \
                AO_short_fetch_and_add_full(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_full
#endif
#if defined(AO_HAVE_short_fetch_and_add_release) \
    && !defined(AO_HAVE_short_fetch_and_sub1_release)
# define AO_short_fetch_and_sub1_release(addr) \
                AO_short_fetch_and_add_release(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_release
#endif
#if defined(AO_HAVE_short_fetch_and_add_acquire) \
    && !defined(AO_HAVE_short_fetch_and_sub1_acquire)
# define AO_short_fetch_and_sub1_acquire(addr) \
                AO_short_fetch_and_add_acquire(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_acquire
#endif
#if defined(AO_HAVE_short_fetch_and_add_write) \
    && !defined(AO_HAVE_short_fetch_and_sub1_write)
# define AO_short_fetch_and_sub1_write(addr) \
                AO_short_fetch_and_add_write(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_write
#endif
#if defined(AO_HAVE_short_fetch_and_add_read) \
    && !defined(AO_HAVE_short_fetch_and_sub1_read)
# define AO_short_fetch_and_sub1_read(addr) \
                AO_short_fetch_and_add_read(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_read
#endif
#if defined(AO_HAVE_short_fetch_and_add_release_write) \
    && !defined(AO_HAVE_short_fetch_and_sub1_release_write)
# define AO_short_fetch_and_sub1_release_write(addr) \
                AO_short_fetch_and_add_release_write(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_release_write
#endif
#if defined(AO_HAVE_short_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_short_fetch_and_sub1_acquire_read)
# define AO_short_fetch_and_sub1_acquire_read(addr) \
                AO_short_fetch_and_add_acquire_read(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1_acquire_read
#endif
#if defined(AO_HAVE_short_fetch_and_add) \
    && !defined(AO_HAVE_short_fetch_and_sub1)
# define AO_short_fetch_and_sub1(addr) \
                AO_short_fetch_and_add(addr, (unsigned/**/short)(-1))
# define AO_HAVE_short_fetch_and_sub1
#endif

#if defined(AO_HAVE_short_fetch_and_sub1_full)
# if !defined(AO_HAVE_short_fetch_and_sub1_release)
#   define AO_short_fetch_and_sub1_release(addr) \
                                AO_short_fetch_and_sub1_full(addr)
#   define AO_HAVE_short_fetch_and_sub1_release
# endif
# if !defined(AO_HAVE_short_fetch_and_sub1_acquire)
#   define AO_short_fetch_and_sub1_acquire(addr) \
                                AO_short_fetch_and_sub1_full(addr)
#   define AO_HAVE_short_fetch_and_sub1_acquire
# endif
# if !defined(AO_HAVE_short_fetch_and_sub1_write)
#   define AO_short_fetch_and_sub1_write(addr) \
                                AO_short_fetch_and_sub1_full(addr)
#   define AO_HAVE_short_fetch_and_sub1_write
# endif
# if !defined(AO_HAVE_short_fetch_and_sub1_read)
#   define AO_short_fetch_and_sub1_read(addr) \
                                AO_short_fetch_and_sub1_full(addr)
#   define AO_HAVE_short_fetch_and_sub1_read
# endif
#endif /* AO_HAVE_short_fetch_and_sub1_full */

#if !defined(AO_HAVE_short_fetch_and_sub1) \
    && defined(AO_HAVE_short_fetch_and_sub1_release)
# define AO_short_fetch_and_sub1(addr) AO_short_fetch_and_sub1_release(addr)
# define AO_HAVE_short_fetch_and_sub1
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1) \
    && defined(AO_HAVE_short_fetch_and_sub1_acquire)
# define AO_short_fetch_and_sub1(addr) AO_short_fetch_and_sub1_acquire(addr)
# define AO_HAVE_short_fetch_and_sub1
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1) \
    && defined(AO_HAVE_short_fetch_and_sub1_write)
# define AO_short_fetch_and_sub1(addr) AO_short_fetch_and_sub1_write(addr)
# define AO_HAVE_short_fetch_and_sub1
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1) \
    && defined(AO_HAVE_short_fetch_and_sub1_read)
# define AO_short_fetch_and_sub1(addr) AO_short_fetch_and_sub1_read(addr)
# define AO_HAVE_short_fetch_and_sub1
#endif

#if defined(AO_HAVE_short_fetch_and_sub1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_fetch_and_sub1_full)
# define AO_short_fetch_and_sub1_full(addr) \
                        (AO_nop_full(), AO_short_fetch_and_sub1_acquire(addr))
# define AO_HAVE_short_fetch_and_sub1_full
#endif

#if !defined(AO_HAVE_short_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_short_fetch_and_sub1_write)
# define AO_short_fetch_and_sub1_release_write(addr) \
                                AO_short_fetch_and_sub1_write(addr)
# define AO_HAVE_short_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_short_fetch_and_sub1_release)
# define AO_short_fetch_and_sub1_release_write(addr) \
                                AO_short_fetch_and_sub1_release(addr)
# define AO_HAVE_short_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_sub1_read)
# define AO_short_fetch_and_sub1_acquire_read(addr) \
                                AO_short_fetch_and_sub1_read(addr)
# define AO_HAVE_short_fetch_and_sub1_acquire_read
#endif
#if !defined(AO_HAVE_short_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_short_fetch_and_sub1_acquire)
# define AO_short_fetch_and_sub1_acquire_read(addr) \
                                AO_short_fetch_and_sub1_acquire(addr)
# define AO_HAVE_short_fetch_and_sub1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_short_fetch_and_sub1_acquire_read)
#   define AO_short_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_short_fetch_and_sub1_acquire_read(addr)
#   define AO_HAVE_short_fetch_and_sub1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_short_fetch_and_sub1)
#   define AO_short_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_short_fetch_and_sub1(addr)
#   define AO_HAVE_short_fetch_and_sub1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* short_and */
#if defined(AO_HAVE_short_compare_and_swap_full) \
    && !defined(AO_HAVE_short_and_full)
  AO_INLINE void
  AO_short_and_full(volatile unsigned/**/short *addr, unsigned/**/short value)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_full(addr, old,
                                                           old & value)));
  }
# define AO_HAVE_short_and_full
#endif

#if defined(AO_HAVE_short_and_full)
# if !defined(AO_HAVE_short_and_release)
#   define AO_short_and_release(addr, val) AO_short_and_full(addr, val)
#   define AO_HAVE_short_and_release
# endif
# if !defined(AO_HAVE_short_and_acquire)
#   define AO_short_and_acquire(addr, val) AO_short_and_full(addr, val)
#   define AO_HAVE_short_and_acquire
# endif
# if !defined(AO_HAVE_short_and_write)
#   define AO_short_and_write(addr, val) AO_short_and_full(addr, val)
#   define AO_HAVE_short_and_write
# endif
# if !defined(AO_HAVE_short_and_read)
#   define AO_short_and_read(addr, val) AO_short_and_full(addr, val)
#   define AO_HAVE_short_and_read
# endif
#endif /* AO_HAVE_short_and_full */

#if !defined(AO_HAVE_short_and) && defined(AO_HAVE_short_and_release)
# define AO_short_and(addr, val) AO_short_and_release(addr, val)
# define AO_HAVE_short_and
#endif
#if !defined(AO_HAVE_short_and) && defined(AO_HAVE_short_and_acquire)
# define AO_short_and(addr, val) AO_short_and_acquire(addr, val)
# define AO_HAVE_short_and
#endif
#if !defined(AO_HAVE_short_and) && defined(AO_HAVE_short_and_write)
# define AO_short_and(addr, val) AO_short_and_write(addr, val)
# define AO_HAVE_short_and
#endif
#if !defined(AO_HAVE_short_and) && defined(AO_HAVE_short_and_read)
# define AO_short_and(addr, val) AO_short_and_read(addr, val)
# define AO_HAVE_short_and
#endif

#if defined(AO_HAVE_short_and_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_and_full)
# define AO_short_and_full(addr, val) \
                        (AO_nop_full(), AO_short_and_acquire(addr, val))
# define AO_HAVE_short_and_full
#endif

#if !defined(AO_HAVE_short_and_release_write) \
    && defined(AO_HAVE_short_and_write)
# define AO_short_and_release_write(addr, val) AO_short_and_write(addr, val)
# define AO_HAVE_short_and_release_write
#endif
#if !defined(AO_HAVE_short_and_release_write) \
    && defined(AO_HAVE_short_and_release)
# define AO_short_and_release_write(addr, val) AO_short_and_release(addr, val)
# define AO_HAVE_short_and_release_write
#endif
#if !defined(AO_HAVE_short_and_acquire_read) \
    && defined(AO_HAVE_short_and_read)
# define AO_short_and_acquire_read(addr, val) AO_short_and_read(addr, val)
# define AO_HAVE_short_and_acquire_read
#endif
#if !defined(AO_HAVE_short_and_acquire_read) \
    && defined(AO_HAVE_short_and_acquire)
# define AO_short_and_acquire_read(addr, val) AO_short_and_acquire(addr, val)
# define AO_HAVE_short_and_acquire_read
#endif

/* short_or */
#if defined(AO_HAVE_short_compare_and_swap_full) \
    && !defined(AO_HAVE_short_or_full)
  AO_INLINE void
  AO_short_or_full(volatile unsigned/**/short *addr, unsigned/**/short value)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_full(addr, old,
                                                           old | value)));
  }
# define AO_HAVE_short_or_full
#endif

#if defined(AO_HAVE_short_or_full)
# if !defined(AO_HAVE_short_or_release)
#   define AO_short_or_release(addr, val) AO_short_or_full(addr, val)
#   define AO_HAVE_short_or_release
# endif
# if !defined(AO_HAVE_short_or_acquire)
#   define AO_short_or_acquire(addr, val) AO_short_or_full(addr, val)
#   define AO_HAVE_short_or_acquire
# endif
# if !defined(AO_HAVE_short_or_write)
#   define AO_short_or_write(addr, val) AO_short_or_full(addr, val)
#   define AO_HAVE_short_or_write
# endif
# if !defined(AO_HAVE_short_or_read)
#   define AO_short_or_read(addr, val) AO_short_or_full(addr, val)
#   define AO_HAVE_short_or_read
# endif
#endif /* AO_HAVE_short_or_full */

#if !defined(AO_HAVE_short_or) && defined(AO_HAVE_short_or_release)
# define AO_short_or(addr, val) AO_short_or_release(addr, val)
# define AO_HAVE_short_or
#endif
#if !defined(AO_HAVE_short_or) && defined(AO_HAVE_short_or_acquire)
# define AO_short_or(addr, val) AO_short_or_acquire(addr, val)
# define AO_HAVE_short_or
#endif
#if !defined(AO_HAVE_short_or) && defined(AO_HAVE_short_or_write)
# define AO_short_or(addr, val) AO_short_or_write(addr, val)
# define AO_HAVE_short_or
#endif
#if !defined(AO_HAVE_short_or) && defined(AO_HAVE_short_or_read)
# define AO_short_or(addr, val) AO_short_or_read(addr, val)
# define AO_HAVE_short_or
#endif

#if defined(AO_HAVE_short_or_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_or_full)
# define AO_short_or_full(addr, val) \
                        (AO_nop_full(), AO_short_or_acquire(addr, val))
# define AO_HAVE_short_or_full
#endif

#if !defined(AO_HAVE_short_or_release_write) \
    && defined(AO_HAVE_short_or_write)
# define AO_short_or_release_write(addr, val) AO_short_or_write(addr, val)
# define AO_HAVE_short_or_release_write
#endif
#if !defined(AO_HAVE_short_or_release_write) \
    && defined(AO_HAVE_short_or_release)
# define AO_short_or_release_write(addr, val) AO_short_or_release(addr, val)
# define AO_HAVE_short_or_release_write
#endif
#if !defined(AO_HAVE_short_or_acquire_read) && defined(AO_HAVE_short_or_read)
# define AO_short_or_acquire_read(addr, val) AO_short_or_read(addr, val)
# define AO_HAVE_short_or_acquire_read
#endif
#if !defined(AO_HAVE_short_or_acquire_read) \
    && defined(AO_HAVE_short_or_acquire)
# define AO_short_or_acquire_read(addr, val) AO_short_or_acquire(addr, val)
# define AO_HAVE_short_or_acquire_read
#endif

/* short_xor */
#if defined(AO_HAVE_short_compare_and_swap_full) \
    && !defined(AO_HAVE_short_xor_full)
  AO_INLINE void
  AO_short_xor_full(volatile unsigned/**/short *addr, unsigned/**/short value)
  {
    unsigned/**/short old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_short_compare_and_swap_full(addr, old,
                                                           old ^ value)));
  }
# define AO_HAVE_short_xor_full
#endif

#if defined(AO_HAVE_short_xor_full)
# if !defined(AO_HAVE_short_xor_release)
#   define AO_short_xor_release(addr, val) AO_short_xor_full(addr, val)
#   define AO_HAVE_short_xor_release
# endif
# if !defined(AO_HAVE_short_xor_acquire)
#   define AO_short_xor_acquire(addr, val) AO_short_xor_full(addr, val)
#   define AO_HAVE_short_xor_acquire
# endif
# if !defined(AO_HAVE_short_xor_write)
#   define AO_short_xor_write(addr, val) AO_short_xor_full(addr, val)
#   define AO_HAVE_short_xor_write
# endif
# if !defined(AO_HAVE_short_xor_read)
#   define AO_short_xor_read(addr, val) AO_short_xor_full(addr, val)
#   define AO_HAVE_short_xor_read
# endif
#endif /* AO_HAVE_short_xor_full */

#if !defined(AO_HAVE_short_xor) && defined(AO_HAVE_short_xor_release)
# define AO_short_xor(addr, val) AO_short_xor_release(addr, val)
# define AO_HAVE_short_xor
#endif
#if !defined(AO_HAVE_short_xor) && defined(AO_HAVE_short_xor_acquire)
# define AO_short_xor(addr, val) AO_short_xor_acquire(addr, val)
# define AO_HAVE_short_xor
#endif
#if !defined(AO_HAVE_short_xor) && defined(AO_HAVE_short_xor_write)
# define AO_short_xor(addr, val) AO_short_xor_write(addr, val)
# define AO_HAVE_short_xor
#endif
#if !defined(AO_HAVE_short_xor) && defined(AO_HAVE_short_xor_read)
# define AO_short_xor(addr, val) AO_short_xor_read(addr, val)
# define AO_HAVE_short_xor
#endif

#if defined(AO_HAVE_short_xor_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_short_xor_full)
# define AO_short_xor_full(addr, val) \
                        (AO_nop_full(), AO_short_xor_acquire(addr, val))
# define AO_HAVE_short_xor_full
#endif

#if !defined(AO_HAVE_short_xor_release_write) \
    && defined(AO_HAVE_short_xor_write)
# define AO_short_xor_release_write(addr, val) AO_short_xor_write(addr, val)
# define AO_HAVE_short_xor_release_write
#endif
#if !defined(AO_HAVE_short_xor_release_write) \
    && defined(AO_HAVE_short_xor_release)
# define AO_short_xor_release_write(addr, val) AO_short_xor_release(addr, val)
# define AO_HAVE_short_xor_release_write
#endif
#if !defined(AO_HAVE_short_xor_acquire_read) \
    && defined(AO_HAVE_short_xor_read)
# define AO_short_xor_acquire_read(addr, val) AO_short_xor_read(addr, val)
# define AO_HAVE_short_xor_acquire_read
#endif
#if !defined(AO_HAVE_short_xor_acquire_read) \
    && defined(AO_HAVE_short_xor_acquire)
# define AO_short_xor_acquire_read(addr, val) AO_short_xor_acquire(addr, val)
# define AO_HAVE_short_xor_acquire_read
#endif

/* short_and/or/xor_dd_aquire_read are meaningless.     */
/*
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* int_load */
#if defined(AO_HAVE_int_load_full) && !defined(AO_HAVE_int_load_acquire)
# define AO_int_load_acquire(addr) AO_int_load_full(addr)
# define AO_HAVE_int_load_acquire
#endif

#if defined(AO_HAVE_int_load_acquire) && !defined(AO_HAVE_int_load)
# define AO_int_load(addr) AO_int_load_acquire(addr)
# define AO_HAVE_int_load
#endif

#if defined(AO_HAVE_int_load_full) && !defined(AO_HAVE_int_load_read)
# define AO_int_load_read(addr) AO_int_load_full(addr)
# define AO_HAVE_int_load_read
#endif

#if !defined(AO_HAVE_int_load_acquire_read) \
    && defined(AO_HAVE_int_load_acquire)
# define AO_int_load_acquire_read(addr) AO_int_load_acquire(addr)
# define AO_HAVE_int_load_acquire_read
#endif

#if defined(AO_HAVE_int_load) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_load_acquire)
  AO_INLINE unsigned
  AO_int_load_acquire(const volatile unsigned *addr)
  {
    unsigned result = AO_int_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_full();
    return result;
  }
# define AO_HAVE_int_load_acquire
#endif

#if defined(AO_HAVE_int_load) && defined(AO_HAVE_nop_read) \
    && !defined(AO_HAVE_int_load_read)
  AO_INLINE unsigned
  AO_int_load_read(const volatile unsigned *addr)
  {
    unsigned result = AO_int_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_read();
    return result;
  }
# define AO_HAVE_int_load_read
#endif

#if defined(AO_HAVE_int_load_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_load_full)
# define AO_int_load_full(addr) (AO_nop_full(), AO_int_load_acquire(addr))
# define AO_HAVE_int_load_full
#endif

#if !defined(AO_HAVE_int_load_acquire_read) \
    && defined(AO_HAVE_int_load_read)
# define AO_int_load_acquire_read(addr) AO_int_load_read(addr)
# define AO_HAVE_int_load_acquire_read
#endif

#if defined(AO_HAVE_int_load_acquire_read) && !defined(AO_HAVE_int_load)
# define AO_int_load(addr) AO_int_load_acquire_read(addr)
# define AO_HAVE_int_load
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_int_load_acquire_read)
#   define AO_int_load_dd_acquire_read(addr) AO_int_load_acquire_read(addr)
#   define AO_HAVE_int_load_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_int_load)
#   define AO_int_load_dd_acquire_read(addr) AO_int_load(addr)
#   define AO_HAVE_int_load_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* int_store */
#if defined(AO_HAVE_int_store_full) && !defined(AO_HAVE_int_store_release)
# define AO_int_store_release(addr,val) AO_int_store_full(addr,val)
# define AO_HAVE_int_store_release
#endif

#if defined(AO_HAVE_int_store_release) && !defined(AO_HAVE_int_store)
# define AO_int_store(addr, val) AO_int_store_release(addr,val)
# define AO_HAVE_int_store
#endif

#if defined(AO_HAVE_int_store_full) && !defined(AO_HAVE_int_store_write)
# define AO_int_store_write(addr,val) AO_int_store_full(addr,val)
# define AO_HAVE_int_store_write
#endif

#if defined(AO_HAVE_int_store_release) \
    && !defined(AO_HAVE_int_store_release_write)
# define AO_int_store_release_write(addr, val) \
                            AO_int_store_release(addr,val)
# define AO_HAVE_int_store_release_write
#endif

#if defined(AO_HAVE_int_store_write) && !defined(AO_HAVE_int_store)
# define AO_int_store(addr, val) AO_int_store_write(addr,val)
# define AO_HAVE_int_store
#endif

#if defined(AO_HAVE_int_store) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_store_release)
# define AO_int_store_release(addr,val) \
                                (AO_nop_full(), AO_int_store(addr,val))
# define AO_HAVE_int_store_release
#endif

#if defined(AO_HAVE_nop_write) && defined(AO_HAVE_int_store) \
    && !defined(AO_HAVE_int_store_write)
# define AO_int_store_write(addr, val) \
                                (AO_nop_write(), AO_int_store(addr,val))
# define AO_HAVE_int_store_write
#endif

#if defined(AO_HAVE_int_store_write) \
    && !defined(AO_HAVE_int_store_release_write)
# define AO_int_store_release_write(addr, val) AO_int_store_write(addr,val)
# define AO_HAVE_int_store_release_write
#endif

#if defined(AO_HAVE_int_store_release) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_store_full)
# define AO_int_store_full(addr, val) \
                        (AO_int_store_release(addr, val), AO_nop_full())
# define AO_HAVE_int_store_full
#endif

/* int_compare_and_swap */
#if defined(AO_HAVE_int_fetch_compare_and_swap_full) \
    && !defined(AO_HAVE_int_compare_and_swap_full)
  AO_INLINE int
  AO_int_compare_and_swap_full(volatile unsigned *addr, unsigned old_val,
                                 unsigned new_val)
  {
    return AO_int_fetch_compare_and_swap_full(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_int_compare_and_swap_full
#endif

#if defined(AO_HAVE_int_fetch_compare_and_swap_acquire) \
    && !defined(AO_HAVE_int_compare_and_swap_acquire)
  AO_INLINE int
  AO_int_compare_and_swap_acquire(volatile unsigned *addr, unsigned old_val,
                                    unsigned new_val)
  {
    return AO_int_fetch_compare_and_swap_acquire(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_int_compare_and_swap_acquire
#endif

#if defined(AO_HAVE_int_fetch_compare_and_swap_release) \
    && !defined(AO_HAVE_int_compare_and_swap_release)
  AO_INLINE int
  AO_int_compare_and_swap_release(volatile unsigned *addr, unsigned old_val,
                                    unsigned new_val)
  {
    return AO_int_fetch_compare_and_swap_release(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_int_compare_and_swap_release
#endif

#if defined(AO_HAVE_int_fetch_compare_and_swap) \
    && !defined(AO_HAVE_int_compare_and_swap)
  AO_INLINE int
  AO_int_compare_and_swap(volatile unsigned *addr, unsigned old_val,
                            unsigned new_val)
  {
    return AO_int_fetch_compare_and_swap(addr, old_val, new_val) == old_val;
  }
# define AO_HAVE_int_compare_and_swap
#endif

/* int_fetch_and_add */
/* We first try to implement fetch_and_add variants in terms of the     */
/* corresponding compare_and_swap variants to minimize adding barriers. */
#if defined(AO_HAVE_int_compare_and_swap_full) \
    && !defined(AO_HAVE_int_fetch_and_add_full)
  AO_INLINE unsigned
  AO_int_fetch_and_add_full(volatile unsigned *addr, unsigned incr)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_full(addr, old,
                                                           old + incr)));
    return old;
  }
# define AO_HAVE_int_fetch_and_add_full
#endif

#if defined(AO_HAVE_int_compare_and_swap_acquire) \
    && !defined(AO_HAVE_int_fetch_and_add_acquire)
  AO_INLINE unsigned
  AO_int_fetch_and_add_acquire(volatile unsigned *addr, unsigned incr)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_acquire(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_int_fetch_and_add_acquire
#endif

#if defined(AO_HAVE_int_compare_and_swap_release) \
    && !defined(AO_HAVE_int_fetch_and_add_release)
  AO_INLINE unsigned
  AO_int_fetch_and_add_release(volatile unsigned *addr, unsigned incr)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_release(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_int_fetch_and_add_release
#endif

#if defined(AO_HAVE_int_compare_and_swap) \
    && !defined(AO_HAVE_int_fetch_and_add)
  AO_INLINE unsigned
  AO_int_fetch_and_add(volatile unsigned *addr, unsigned incr)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap(addr, old,
                                                      old + incr)));
    return old;
  }
# define AO_HAVE_int_fetch_and_add
#endif

#if defined(AO_HAVE_int_fetch_and_add_full)
# if !defined(AO_HAVE_int_fetch_and_add_release)
#   define AO_int_fetch_and_add_release(addr, val) \
                                AO_int_fetch_and_add_full(addr, val)
#   define AO_HAVE_int_fetch_and_add_release
# endif
# if !defined(AO_HAVE_int_fetch_and_add_acquire)
#   define AO_int_fetch_and_add_acquire(addr, val) \
                                AO_int_fetch_and_add_full(addr, val)
#   define AO_HAVE_int_fetch_and_add_acquire
# endif
# if !defined(AO_HAVE_int_fetch_and_add_write)
#   define AO_int_fetch_and_add_write(addr, val) \
                                AO_int_fetch_and_add_full(addr, val)
#   define AO_HAVE_int_fetch_and_add_write
# endif
# if !defined(AO_HAVE_int_fetch_and_add_read)
#   define AO_int_fetch_and_add_read(addr, val) \
                                AO_int_fetch_and_add_full(addr, val)
#   define AO_HAVE_int_fetch_and_add_read
# endif
#endif /* AO_HAVE_int_fetch_and_add_full */

#if !defined(AO_HAVE_int_fetch_and_add) \
    && defined(AO_HAVE_int_fetch_and_add_release)
# define AO_int_fetch_and_add(addr, val) \
                                AO_int_fetch_and_add_release(addr, val)
# define AO_HAVE_int_fetch_and_add
#endif
#if !defined(AO_HAVE_int_fetch_and_add) \
    && defined(AO_HAVE_int_fetch_and_add_acquire)
# define AO_int_fetch_and_add(addr, val) \
                                AO_int_fetch_and_add_acquire(addr, val)
# define AO_HAVE_int_fetch_and_add
#endif
#if !defined(AO_HAVE_int_fetch_and_add) \
    && defined(AO_HAVE_int_fetch_and_add_write)
# define AO_int_fetch_and_add(addr, val) \
                                AO_int_fetch_and_add_write(addr, val)
# define AO_HAVE_int_fetch_and_add
#endif
#if !defined(AO_HAVE_int_fetch_and_add) \
    && defined(AO_HAVE_int_fetch_and_add_read)
# define AO_int_fetch_and_add(addr, val) \
                                AO_int_fetch_and_add_read(addr, val)
# define AO_HAVE_int_fetch_and_add
#endif

#if defined(AO_HAVE_int_fetch_and_add_acquire) \
    && defined(AO_HAVE_nop_full) && !defined(AO_HAVE_int_fetch_and_add_full)
# define AO_int_fetch_and_add_full(addr, val) \
                (AO_nop_full(), AO_int_fetch_and_add_acquire(addr, val))
# define AO_HAVE_int_fetch_and_add_full
#endif

#if !defined(AO_HAVE_int_fetch_and_add_release_write) \
    && defined(AO_HAVE_int_fetch_and_add_write)
# define AO_int_fetch_and_add_release_write(addr, val) \
                                AO_int_fetch_and_add_write(addr, val)
# define AO_HAVE_int_fetch_and_add_release_write
#endif
#if !defined(AO_HAVE_int_fetch_and_add_release_write) \
    && defined(AO_HAVE_int_fetch_and_add_release)
# define AO_int_fetch_and_add_release_write(addr, val) \
                                AO_int_fetch_and_add_release(addr, val)
# define AO_HAVE_int_fetch_and_add_release_write
#endif

#if !defined(AO_HAVE_int_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_add_read)
# define AO_int_fetch_and_add_acquire_read(addr, val) \
                                AO_int_fetch_and_add_read(addr, val)
# define AO_HAVE_int_fetch_and_add_acquire_read
#endif
#if !defined(AO_HAVE_int_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_add_acquire)
# define AO_int_fetch_and_add_acquire_read(addr, val) \
                                AO_int_fetch_and_add_acquire(addr, val)
# define AO_HAVE_int_fetch_and_add_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_int_fetch_and_add_acquire_read)
#   define AO_int_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_int_fetch_and_add_acquire_read(addr, val)
#   define AO_HAVE_int_fetch_and_add_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_int_fetch_and_add)
#   define AO_int_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_int_fetch_and_add(addr, val)
#   define AO_HAVE_int_fetch_and_add_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* int_fetch_and_add1 */
#if defined(AO_HAVE_int_fetch_and_add_full) \
    && !defined(AO_HAVE_int_fetch_and_add1_full)
# define AO_int_fetch_and_add1_full(addr) \
                                AO_int_fetch_and_add_full(addr,1)
# define AO_HAVE_int_fetch_and_add1_full
#endif
#if defined(AO_HAVE_int_fetch_and_add_release) \
    && !defined(AO_HAVE_int_fetch_and_add1_release)
# define AO_int_fetch_and_add1_release(addr) \
                                AO_int_fetch_and_add_release(addr,1)
# define AO_HAVE_int_fetch_and_add1_release
#endif
#if defined(AO_HAVE_int_fetch_and_add_acquire) \
    && !defined(AO_HAVE_int_fetch_and_add1_acquire)
# define AO_int_fetch_and_add1_acquire(addr) \
                                AO_int_fetch_and_add_acquire(addr,1)
# define AO_HAVE_int_fetch_and_add1_acquire
#endif
#if defined(AO_HAVE_int_fetch_and_add_write) \
    && !defined(AO_HAVE_int_fetch_and_add1_write)
# define AO_int_fetch_and_add1_write(addr) \
                                AO_int_fetch_and_add_write(addr,1)
# define AO_HAVE_int_fetch_and_add1_write
#endif
#if defined(AO_HAVE_int_fetch_and_add_read) \
    && !defined(AO_HAVE_int_fetch_and_add1_read)
# define AO_int_fetch_and_add1_read(addr) \
                                AO_int_fetch_and_add_read(addr,1)
# define AO_HAVE_int_fetch_and_add1_read
#endif
#if defined(AO_HAVE_int_fetch_and_add_release_write) \
    && !defined(AO_HAVE_int_fetch_and_add1_release_write)
# define AO_int_fetch_and_add1_release_write(addr) \
                                AO_int_fetch_and_add_release_write(addr,1)
# define AO_HAVE_int_fetch_and_add1_release_write
#endif
#if defined(AO_HAVE_int_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_int_fetch_and_add1_acquire_read)
# define AO_int_fetch_and_add1_acquire_read(addr) \
                                AO_int_fetch_and_add_acquire_read(addr,1)
# define AO_HAVE_int_fetch_and_add1_acquire_read
#endif
#if defined(AO_HAVE_int_fetch_and_add) \
    && !defined(AO_HAVE_int_fetch_and_add1)
# define AO_int_fetch_and_add1(addr) AO_int_fetch_and_add(addr,1)
# define AO_HAVE_int_fetch_and_add1
#endif

#if defined(AO_HAVE_int_fetch_and_add1_full)
# if !defined(AO_HAVE_int_fetch_and_add1_release)
#   define AO_int_fetch_and_add1_release(addr) \
                                AO_int_fetch_and_add1_full(addr)
#   define AO_HAVE_int_fetch_and_add1_release
# endif
# if !defined(AO_HAVE_int_fetch_and_add1_acquire)
#   define AO_int_fetch_and_add1_acquire(addr) \
                                AO_int_fetch_and_add1_full(addr)
#   define AO_HAVE_int_fetch_and_add1_acquire
# endif
# if !defined(AO_HAVE_int_fetch_and_add1_write)
#   define AO_int_fetch_and_add1_write(addr) \
                                AO_int_fetch_and_add1_full(addr)
#   define AO_HAVE_int_fetch_and_add1_write
# endif
# if !defined(AO_HAVE_int_fetch_and_add1_read)
#   define AO_int_fetch_and_add1_read(addr) \
                                AO_int_fetch_and_add1_full(addr)
#   define AO_HAVE_int_fetch_and_add1_read
# endif
#endif /* AO_HAVE_int_fetch_and_add1_full */

#if !defined(AO_HAVE_int_fetch_and_add1) \
    && defined(AO_HAVE_int_fetch_and_add1_release)
# define AO_int_fetch_and_add1(addr) AO_int_fetch_and_add1_release(addr)
# define AO_HAVE_int_fetch_and_add1
#endif
#if !defined(AO_HAVE_int_fetch_and_add1) \
    && defined(AO_HAVE_int_fetch_and_add1_acquire)
# define AO_int_fetch_and_add1(addr) AO_int_fetch_and_add1_acquire(addr)
# define AO_HAVE_int_fetch_and_add1
#endif
#if !defined(AO_HAVE_int_fetch_and_add1) \
    && defined(AO_HAVE_int_fetch_and_add1_write)
# define AO_int_fetch_and_add1(addr) AO_int_fetch_and_add1_write(addr)
# define AO_HAVE_int_fetch_and_add1
#endif
#if !defined(AO_HAVE_int_fetch_and_add1) \
    && defined(AO_HAVE_int_fetch_and_add1_read)
# define AO_int_fetch_and_add1(addr) AO_int_fetch_and_add1_read(addr)
# define AO_HAVE_int_fetch_and_add1
#endif

#if defined(AO_HAVE_int_fetch_and_add1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_fetch_and_add1_full)
# define AO_int_fetch_and_add1_full(addr) \
                        (AO_nop_full(), AO_int_fetch_and_add1_acquire(addr))
# define AO_HAVE_int_fetch_and_add1_full
#endif

#if !defined(AO_HAVE_int_fetch_and_add1_release_write) \
    && defined(AO_HAVE_int_fetch_and_add1_write)
# define AO_int_fetch_and_add1_release_write(addr) \
                                AO_int_fetch_and_add1_write(addr)
# define AO_HAVE_int_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_int_fetch_and_add1_release_write) \
    && defined(AO_HAVE_int_fetch_and_add1_release)
# define AO_int_fetch_and_add1_release_write(addr) \
                                AO_int_fetch_and_add1_release(addr)
# define AO_HAVE_int_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_int_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_add1_read)
# define AO_int_fetch_and_add1_acquire_read(addr) \
                                AO_int_fetch_and_add1_read(addr)
# define AO_HAVE_int_fetch_and_add1_acquire_read
#endif
#if !defined(AO_HAVE_int_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_add1_acquire)
# define AO_int_fetch_and_add1_acquire_read(addr) \
                                AO_int_fetch_and_add1_acquire(addr)
# define AO_HAVE_int_fetch_and_add1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_int_fetch_and_add1_acquire_read)
#   define AO_int_fetch_and_add1_dd_acquire_read(addr) \
                                AO_int_fetch_and_add1_acquire_read(addr)
#   define AO_HAVE_int_fetch_and_add1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_int_fetch_and_add1)
#   define AO_int_fetch_and_add1_dd_acquire_read(addr) \
                                AO_int_fetch_and_add1(addr)
#   define AO_HAVE_int_fetch_and_add1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* int_fetch_and_sub1 */
#if defined(AO_HAVE_int_fetch_and_add_full) \
    && !defined(AO_HAVE_int_fetch_and_sub1_full)
# define AO_int_fetch_and_sub1_full(addr) \
                AO_int_fetch_and_add_full(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_full
#endif
#if defined(AO_HAVE_int_fetch_and_add_release) \
    && !defined(AO_HAVE_int_fetch_and_sub1_release)
# define AO_int_fetch_and_sub1_release(addr) \
                AO_int_fetch_and_add_release(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_release
#endif
#if defined(AO_HAVE_int_fetch_and_add_acquire) \
    && !defined(AO_HAVE_int_fetch_and_sub1_acquire)
# define AO_int_fetch_and_sub1_acquire(addr) \
                AO_int_fetch_and_add_acquire(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_acquire
#endif
#if defined(AO_HAVE_int_fetch_and_add_write) \
    && !defined(AO_HAVE_int_fetch_and_sub1_write)
# define AO_int_fetch_and_sub1_write(addr) \
                AO_int_fetch_and_add_write(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_write
#endif
#if defined(AO_HAVE_int_fetch_and_add_read) \
    && !defined(AO_HAVE_int_fetch_and_sub1_read)
# define AO_int_fetch_and_sub1_read(addr) \
                AO_int_fetch_and_add_read(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_read
#endif
#if defined(AO_HAVE_int_fetch_and_add_release_write) \
    && !defined(AO_HAVE_int_fetch_and_sub1_release_write)
# define AO_int_fetch_and_sub1_release_write(addr) \
                AO_int_fetch_and_add_release_write(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_release_write
#endif
#if defined(AO_HAVE_int_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_int_fetch_and_sub1_acquire_read)
# define AO_int_fetch_and_sub1_acquire_read(addr) \
                AO_int_fetch_and_add_acquire_read(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1_acquire_read
#endif
#if defined(AO_HAVE_int_fetch_and_add) \
    && !defined(AO_HAVE_int_fetch_and_sub1)
# define AO_int_fetch_and_sub1(addr) \
                AO_int_fetch_and_add(addr, (unsigned)(-1))
# define AO_HAVE_int_fetch_and_sub1
#endif

#if defined(AO_HAVE_int_fetch_and_sub1_full)
# if !defined(AO_HAVE_int_fetch_and_sub1_release)
#   define AO_int_fetch_and_sub1_release(addr) \
                                AO_int_fetch_and_sub1_full(addr)
#   define AO_HAVE_int_fetch_and_sub1_release
# endif
# if !defined(AO_HAVE_int_fetch_and_sub1_acquire)
#   define AO_int_fetch_and_sub1_acquire(addr) \
                                AO_int_fetch_and_sub1_full(addr)
#   define AO_HAVE_int_fetch_and_sub1_acquire
# endif
# if !defined(AO_HAVE_int_fetch_and_sub1_write)
#   define AO_int_fetch_and_sub1_write(addr) \
                                AO_int_fetch_and_sub1_full(addr)
#   define AO_HAVE_int_fetch_and_sub1_write
# endif
# if !defined(AO_HAVE_int_fetch_and_sub1_read)
#   define AO_int_fetch_and_sub1_read(addr) \
                                AO_int_fetch_and_sub1_full(addr)
#   define AO_HAVE_int_fetch_and_sub1_read
# endif
#endif /* AO_HAVE_int_fetch_and_sub1_full */

#if !defined(AO_HAVE_int_fetch_and_sub1) \
    && defined(AO_HAVE_int_fetch_and_sub1_release)
# define AO_int_fetch_and_sub1(addr) AO_int_fetch_and_sub1_release(addr)
# define AO_HAVE_int_fetch_and_sub1
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1) \
    && defined(AO_HAVE_int_fetch_and_sub1_acquire)
# define AO_int_fetch_and_sub1(addr) AO_int_fetch_and_sub1_acquire(addr)
# define AO_HAVE_int_fetch_and_sub1
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1) \
    && defined(AO_HAVE_int_fetch_and_sub1_write)
# define AO_int_fetch_and_sub1(addr) AO_int_fetch_and_sub1_write(addr)
# define AO_HAVE_int_fetch_and_sub1
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1) \
    && defined(AO_HAVE_int_fetch_and_sub1_read)
# define AO_int_fetch_and_sub1(addr) AO_int_fetch_and_sub1_read(addr)
# define AO_HAVE_int_fetch_and_sub1
#endif

#if defined(AO_HAVE_int_fetch_and_sub1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_fetch_and_sub1_full)
# define AO_int_fetch_and_sub1_full(addr) \
                        (AO_nop_full(), AO_int_fetch_and_sub1_acquire(addr))
# define AO_HAVE_int_fetch_and_sub1_full
#endif

#if !defined(AO_HAVE_int_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_int_fetch_and_sub1_write)
# define AO_int_fetch_and_sub1_release_write(addr) \
                                AO_int_fetch_and_sub1_write(addr)
# define AO_HAVE_int_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_int_fetch_and_sub1_release)
# define AO_int_fetch_and_sub1_release_write(addr) \
                                AO_int_fetch_and_sub1_release(addr)
# define AO_HAVE_int_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_sub1_read)
# define AO_int_fetch_and_sub1_acquire_read(addr) \
                                AO_int_fetch_and_sub1_read(addr)
# define AO_HAVE_int_fetch_and_sub1_acquire_read
#endif
#if !defined(AO_HAVE_int_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_int_fetch_and_sub1_acquire)
# define AO_int_fetch_and_sub1_acquire_read(addr) \
                                AO_int_fetch_and_sub1_acquire(addr)
# define AO_HAVE_int_fetch_and_sub1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_int_fetch_and_sub1_acquire_read)
#   define AO_int_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_int_fetch_and_sub1_acquire_read(addr)
#   define AO_HAVE_int_fetch_and_sub1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_int_fetch_and_sub1)
#   define AO_int_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_int_fetch_and_sub1(addr)
#   define AO_HAVE_int_fetch_and_sub1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* int_and */
#if defined(AO_HAVE_int_compare_and_swap_full) \
    && !defined(AO_HAVE_int_and_full)
  AO_INLINE void
  AO_int_and_full(volatile unsigned *addr, unsigned value)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_full(addr, old,
                                                           old & value)));
  }
# define AO_HAVE_int_and_full
#endif

#if defined(AO_HAVE_int_and_full)
# if !defined(AO_HAVE_int_and_release)
#   define AO_int_and_release(addr, val) AO_int_and_full(addr, val)
#   define AO_HAVE_int_and_release
# endif
# if !defined(AO_HAVE_int_and_acquire)
#   define AO_int_and_acquire(addr, val) AO_int_and_full(addr, val)
#   define AO_HAVE_int_and_acquire
# endif
# if !defined(AO_HAVE_int_and_write)
#   define AO_int_and_write(addr, val) AO_int_and_full(addr, val)
#   define AO_HAVE_int_and_write
# endif
# if !defined(AO_HAVE_int_and_read)
#   define AO_int_and_read(addr, val) AO_int_and_full(addr, val)
#   define AO_HAVE_int_and_read
# endif
#endif /* AO_HAVE_int_and_full */

#if !defined(AO_HAVE_int_and) && defined(AO_HAVE_int_and_release)
# define AO_int_and(addr, val) AO_int_and_release(addr, val)
# define AO_HAVE_int_and
#endif
#if !defined(AO_HAVE_int_and) && defined(AO_HAVE_int_and_acquire)
# define AO_int_and(addr, val) AO_int_and_acquire(addr, val)
# define AO_HAVE_int_and
#endif
#if !defined(AO_HAVE_int_and) && defined(AO_HAVE_int_and_write)
# define AO_int_and(addr, val) AO_int_and_write(addr, val)
# define AO_HAVE_int_and
#endif
#if !defined(AO_HAVE_int_and) && defined(AO_HAVE_int_and_read)
# define AO_int_and(addr, val) AO_int_and_read(addr, val)
# define AO_HAVE_int_and
#endif

#if defined(AO_HAVE_int_and_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_and_full)
# define AO_int_and_full(addr, val) \
                        (AO_nop_full(), AO_int_and_acquire(addr, val))
# define AO_HAVE_int_and_full
#endif

#if !defined(AO_HAVE_int_and_release_write) \
    && defined(AO_HAVE_int_and_write)
# define AO_int_and_release_write(addr, val) AO_int_and_write(addr, val)
# define AO_HAVE_int_and_release_write
#endif
#if !defined(AO_HAVE_int_and_release_write) \
    && defined(AO_HAVE_int_and_release)
# define AO_int_and_release_write(addr, val) AO_int_and_release(addr, val)
# define AO_HAVE_int_and_release_write
#endif
#if !defined(AO_HAVE_int_and_acquire_read) \
    && defined(AO_HAVE_int_and_read)
# define AO_int_and_acquire_read(addr, val) AO_int_and_read(addr, val)
# define AO_HAVE_int_and_acquire_read
#endif
#if !defined(AO_HAVE_int_and_acquire_read) \
    && defined(AO_HAVE_int_and_acquire)
# define AO_int_and_acquire_read(addr, val) AO_int_and_acquire(addr, val)
# define AO_HAVE_int_and_acquire_read
#endif

/* int_or */
#if defined(AO_HAVE_int_compare_and_swap_full) \
    && !defined(AO_HAVE_int_or_full)
  AO_INLINE void
  AO_int_or_full(volatile unsigned *addr, unsigned value)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_full(addr, old,
                                                           old | value)));
  }
# define AO_HAVE_int_or_full
#endif

#if defined(AO_HAVE_int_or_full)
# if !defined(AO_HAVE_int_or_release)
#   define AO_int_or_release(addr, val) AO_int_or_full(addr, val)
#   define AO_HAVE_int_or_release
# endif
# if !defined(AO_HAVE_int_or_acquire)
#   define AO_int_or_acquire(addr, val) AO_int_or_full(addr, val)
#   define AO_HAVE_int_or_acquire
# endif
# if !defined(AO_HAVE_int_or_write)
#   define AO_int_or_write(addr, val) AO_int_or_full(addr, val)
#   define AO_HAVE_int_or_write
# endif
# if !defined(AO_HAVE_int_or_read)
#   define AO_int_or_read(addr, val) AO_int_or_full(addr, val)
#   define AO_HAVE_int_or_read
# endif
#endif /* AO_HAVE_int_or_full */

#if !defined(AO_HAVE_int_or) && defined(AO_HAVE_int_or_release)
# define AO_int_or(addr, val) AO_int_or_release(addr, val)
# define AO_HAVE_int_or
#endif
#if !defined(AO_HAVE_int_or) && defined(AO_HAVE_int_or_acquire)
# define AO_int_or(addr, val) AO_int_or_acquire(addr, val)
# define AO_HAVE_int_or
#endif
#if !defined(AO_HAVE_int_or) && defined(AO_HAVE_int_or_write)
# define AO_int_or(addr, val) AO_int_or_write(addr, val)
# define AO_HAVE_int_or
#endif
#if !defined(AO_HAVE_int_or) && defined(AO_HAVE_int_or_read)
# define AO_int_or(addr, val) AO_int_or_read(addr, val)
# define AO_HAVE_int_or
#endif

#if defined(AO_HAVE_int_or_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_or_full)
# define AO_int_or_full(addr, val) \
                        (AO_nop_full(), AO_int_or_acquire(addr, val))
# define AO_HAVE_int_or_full
#endif

#if !defined(AO_HAVE_int_or_release_write) \
    && defined(AO_HAVE_int_or_write)
# define AO_int_or_release_write(addr, val) AO_int_or_write(addr, val)
# define AO_HAVE_int_or_release_write
#endif
#if !defined(AO_HAVE_int_or_release_write) \
    && defined(AO_HAVE_int_or_release)
# define AO_int_or_release_write(addr, val) AO_int_or_release(addr, val)
# define AO_HAVE_int_or_release_write
#endif
#if !defined(AO_HAVE_int_or_acquire_read) && defined(AO_HAVE_int_or_read)
# define AO_int_or_acquire_read(addr, val) AO_int_or_read(addr, val)
# define AO_HAVE_int_or_acquire_read
#endif
#if !defined(AO_HAVE_int_or_acquire_read) \
    && defined(AO_HAVE_int_or_acquire)
# define AO_int_or_acquire_read(addr, val) AO_int_or_acquire(addr, val)
# define AO_HAVE_int_or_acquire_read
#endif

/* int_xor */
#if defined(AO_HAVE_int_compare_and_swap_full) \
    && !defined(AO_HAVE_int_xor_full)
  AO_INLINE void
  AO_int_xor_full(volatile unsigned *addr, unsigned value)
  {
    unsigned old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_int_compare_and_swap_full(addr, old,
                                                           old ^ value)));
  }
# define AO_HAVE_int_xor_full
#endif

#if defined(AO_HAVE_int_xor_full)
# if !defined(AO_HAVE_int_xor_release)
#   define AO_int_xor_release(addr, val) AO_int_xor_full(addr, val)
#   define AO_HAVE_int_xor_release
# endif
# if !defined(AO_HAVE_int_xor_acquire)
#   define AO_int_xor_acquire(addr, val) AO_int_xor_full(addr, val)
#   define AO_HAVE_int_xor_acquire
# endif
# if !defined(AO_HAVE_int_xor_write)
#   define AO_int_xor_write(addr, val) AO_int_xor_full(addr, val)
#   define AO_HAVE_int_xor_write
# endif
# if !defined(AO_HAVE_int_xor_read)
#   define AO_int_xor_read(addr, val) AO_int_xor_full(addr, val)
#   define AO_HAVE_int_xor_read
# endif
#endif /* AO_HAVE_int_xor_full */

#if !defined(AO_HAVE_int_xor) && defined(AO_HAVE_int_xor_release)
# define AO_int_xor(addr, val) AO_int_xor_release(addr, val)
# define AO_HAVE_int_xor
#endif
#if !defined(AO_HAVE_int_xor) && defined(AO_HAVE_int_xor_acquire)
# define AO_int_xor(addr, val) AO_int_xor_acquire(addr, val)
# define AO_HAVE_int_xor
#endif
#if !defined(AO_HAVE_int_xor) && defined(AO_HAVE_int_xor_write)
# define AO_int_xor(addr, val) AO_int_xor_write(addr, val)
# define AO_HAVE_int_xor
#endif
#if !defined(AO_HAVE_int_xor) && defined(AO_HAVE_int_xor_read)
# define AO_int_xor(addr, val) AO_int_xor_read(addr, val)
# define AO_HAVE_int_xor
#endif

#if defined(AO_HAVE_int_xor_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_int_xor_full)
# define AO_int_xor_full(addr, val) \
                        (AO_nop_full(), AO_int_xor_acquire(addr, val))
# define AO_HAVE_int_xor_full
#endif

#if !defined(AO_HAVE_int_xor_release_write) \
    && defined(AO_HAVE_int_xor_write)
# define AO_int_xor_release_write(addr, val) AO_int_xor_write(addr, val)
# define AO_HAVE_int_xor_release_write
#endif
#if !defined(AO_HAVE_int_xor_release_write) \
    && defined(AO_HAVE_int_xor_release)
# define AO_int_xor_release_write(addr, val) AO_int_xor_release(addr, val)
# define AO_HAVE_int_xor_release_write
#endif
#if !defined(AO_HAVE_int_xor_acquire_read) \
    && defined(AO_HAVE_int_xor_read)
# define AO_int_xor_acquire_read(addr, val) AO_int_xor_read(addr, val)
# define AO_HAVE_int_xor_acquire_read
#endif
#if !defined(AO_HAVE_int_xor_acquire_read) \
    && defined(AO_HAVE_int_xor_acquire)
# define AO_int_xor_acquire_read(addr, val) AO_int_xor_acquire(addr, val)
# define AO_HAVE_int_xor_acquire_read
#endif

/* int_and/or/xor_dd_aquire_read are meaningless.     */
/*
 * Copyright (c) 2003-2011 Hewlett-Packard Development Company, L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* load */
#if defined(AO_HAVE_load_full) && !defined(AO_HAVE_load_acquire)
# define AO_load_acquire(addr) AO_load_full(addr)
# define AO_HAVE_load_acquire
#endif

#if defined(AO_HAVE_load_acquire) && !defined(AO_HAVE_load)
# define AO_load(addr) AO_load_acquire(addr)
# define AO_HAVE_load
#endif

#if defined(AO_HAVE_load_full) && !defined(AO_HAVE_load_read)
# define AO_load_read(addr) AO_load_full(addr)
# define AO_HAVE_load_read
#endif

#if !defined(AO_HAVE_load_acquire_read) \
    && defined(AO_HAVE_load_acquire)
# define AO_load_acquire_read(addr) AO_load_acquire(addr)
# define AO_HAVE_load_acquire_read
#endif

#if defined(AO_HAVE_load) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_load_acquire)
  AO_INLINE AO_t
  AO_load_acquire(const volatile AO_t *addr)
  {
    AO_t result = AO_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_full();
    return result;
  }
# define AO_HAVE_load_acquire
#endif

#if defined(AO_HAVE_load) && defined(AO_HAVE_nop_read) \
    && !defined(AO_HAVE_load_read)
  AO_INLINE AO_t
  AO_load_read(const volatile AO_t *addr)
  {
    AO_t result = AO_load(addr);

    /* Acquire barrier would be useless, since the load could be delayed    */
    /* beyond it.                                                           */
    AO_nop_read();
    return result;
  }
# define AO_HAVE_load_read
#endif

#if defined(AO_HAVE_load_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_load_full)
# define AO_load_full(addr) (AO_nop_full(), AO_load_acquire(addr))
# define AO_HAVE_load_full
#endif

#if !defined(AO_HAVE_load_acquire_read) \
    && defined(AO_HAVE_load_read)
# define AO_load_acquire_read(addr) AO_load_read(addr)
# define AO_HAVE_load_acquire_read
#endif

#if defined(AO_HAVE_load_acquire_read) && !defined(AO_HAVE_load)
# define AO_load(addr) AO_load_acquire_read(addr)
# define AO_HAVE_load
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_load_acquire_read)
#   define AO_load_dd_acquire_read(addr) AO_load_acquire_read(addr)
#   define AO_HAVE_load_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_load)
#   define AO_load_dd_acquire_read(addr) AO_load(addr)
#   define AO_HAVE_load_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* store */
#if defined(AO_HAVE_store_full) && !defined(AO_HAVE_store_release)
# define AO_store_release(addr,val) AO_store_full(addr,val)
# define AO_HAVE_store_release
#endif

#if defined(AO_HAVE_store_release) && !defined(AO_HAVE_store)
# define AO_store(addr, val) AO_store_release(addr,val)
# define AO_HAVE_store
#endif

#if defined(AO_HAVE_store_full) && !defined(AO_HAVE_store_write)
# define AO_store_write(addr,val) AO_store_full(addr,val)
# define AO_HAVE_store_write
#endif

#if defined(AO_HAVE_store_release) \
    && !defined(AO_HAVE_store_release_write)
# define AO_store_release_write(addr, val) \
                            AO_store_release(addr,val)
# define AO_HAVE_store_release_write
#endif

#if defined(AO_HAVE_store_write) && !defined(AO_HAVE_store)
# define AO_store(addr, val) AO_store_write(addr,val)
# define AO_HAVE_store
#endif

#if defined(AO_HAVE_store) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_store_release)
# define AO_store_release(addr,val) \
                                (AO_nop_full(), AO_store(addr,val))
# define AO_HAVE_store_release
#endif

#if defined(AO_HAVE_nop_write) && defined(AO_HAVE_store) \
    && !defined(AO_HAVE_store_write)
# define AO_store_write(addr, val) \
                                (AO_nop_write(), AO_store(addr,val))
# define AO_HAVE_store_write
#endif

#if defined(AO_HAVE_store_write) \
    && !defined(AO_HAVE_store_release_write)
# define AO_store_release_write(addr, val) AO_store_write(addr,val)
# define AO_HAVE_store_release_write
#endif

#if defined(AO_HAVE_store_release) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_store_full)
# define AO_store_full(addr, val) \
                        (AO_store_release(addr, val), AO_nop_full())
# define AO_HAVE_store_full
#endif

/* compare_and_swap */
#if defined(AO_HAVE_fetch_compare_and_swap_full) \
    && !defined(AO_HAVE_compare_and_swap_full)
  AO_INLINE int
  AO_compare_and_swap_full(volatile AO_t *addr, AO_t old_val,
                                 AO_t new_val)
  {
    return AO_fetch_compare_and_swap_full(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_compare_and_swap_full
#endif

#if defined(AO_HAVE_fetch_compare_and_swap_acquire) \
    && !defined(AO_HAVE_compare_and_swap_acquire)
  AO_INLINE int
  AO_compare_and_swap_acquire(volatile AO_t *addr, AO_t old_val,
                                    AO_t new_val)
  {
    return AO_fetch_compare_and_swap_acquire(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_compare_and_swap_acquire
#endif

#if defined(AO_HAVE_fetch_compare_and_swap_release) \
    && !defined(AO_HAVE_compare_and_swap_release)
  AO_INLINE int
  AO_compare_and_swap_release(volatile AO_t *addr, AO_t old_val,
                                    AO_t new_val)
  {
    return AO_fetch_compare_and_swap_release(addr, old_val, new_val)
             == old_val;
  }
# define AO_HAVE_compare_and_swap_release
#endif

#if defined(AO_HAVE_fetch_compare_and_swap) \
    && !defined(AO_HAVE_compare_and_swap)
  AO_INLINE int
  AO_compare_and_swap(volatile AO_t *addr, AO_t old_val,
                            AO_t new_val)
  {
    return AO_fetch_compare_and_swap(addr, old_val, new_val) == old_val;
  }
# define AO_HAVE_compare_and_swap
#endif

/* fetch_and_add */
/* We first try to implement fetch_and_add variants in terms of the     */
/* corresponding compare_and_swap variants to minimize adding barriers. */
#if defined(AO_HAVE_compare_and_swap_full) \
    && !defined(AO_HAVE_fetch_and_add_full)
  AO_INLINE AO_t
  AO_fetch_and_add_full(volatile AO_t *addr, AO_t incr)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_full(addr, old,
                                                           old + incr)));
    return old;
  }
# define AO_HAVE_fetch_and_add_full
#endif

#if defined(AO_HAVE_compare_and_swap_acquire) \
    && !defined(AO_HAVE_fetch_and_add_acquire)
  AO_INLINE AO_t
  AO_fetch_and_add_acquire(volatile AO_t *addr, AO_t incr)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_acquire(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_fetch_and_add_acquire
#endif

#if defined(AO_HAVE_compare_and_swap_release) \
    && !defined(AO_HAVE_fetch_and_add_release)
  AO_INLINE AO_t
  AO_fetch_and_add_release(volatile AO_t *addr, AO_t incr)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_release(addr, old,
                                                              old + incr)));
    return old;
  }
# define AO_HAVE_fetch_and_add_release
#endif

#if defined(AO_HAVE_compare_and_swap) \
    && !defined(AO_HAVE_fetch_and_add)
  AO_INLINE AO_t
  AO_fetch_and_add(volatile AO_t *addr, AO_t incr)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap(addr, old,
                                                      old + incr)));
    return old;
  }
# define AO_HAVE_fetch_and_add
#endif

#if defined(AO_HAVE_fetch_and_add_full)
# if !defined(AO_HAVE_fetch_and_add_release)
#   define AO_fetch_and_add_release(addr, val) \
                                AO_fetch_and_add_full(addr, val)
#   define AO_HAVE_fetch_and_add_release
# endif
# if !defined(AO_HAVE_fetch_and_add_acquire)
#   define AO_fetch_and_add_acquire(addr, val) \
                                AO_fetch_and_add_full(addr, val)
#   define AO_HAVE_fetch_and_add_acquire
# endif
# if !defined(AO_HAVE_fetch_and_add_write)
#   define AO_fetch_and_add_write(addr, val) \
                                AO_fetch_and_add_full(addr, val)
#   define AO_HAVE_fetch_and_add_write
# endif
# if !defined(AO_HAVE_fetch_and_add_read)
#   define AO_fetch_and_add_read(addr, val) \
                                AO_fetch_and_add_full(addr, val)
#   define AO_HAVE_fetch_and_add_read
# endif
#endif /* AO_HAVE_fetch_and_add_full */

#if !defined(AO_HAVE_fetch_and_add) \
    && defined(AO_HAVE_fetch_and_add_release)
# define AO_fetch_and_add(addr, val) \
                                AO_fetch_and_add_release(addr, val)
# define AO_HAVE_fetch_and_add
#endif
#if !defined(AO_HAVE_fetch_and_add) \
    && defined(AO_HAVE_fetch_and_add_acquire)
# define AO_fetch_and_add(addr, val) \
                                AO_fetch_and_add_acquire(addr, val)
# define AO_HAVE_fetch_and_add
#endif
#if !defined(AO_HAVE_fetch_and_add) \
    && defined(AO_HAVE_fetch_and_add_write)
# define AO_fetch_and_add(addr, val) \
                                AO_fetch_and_add_write(addr, val)
# define AO_HAVE_fetch_and_add
#endif
#if !defined(AO_HAVE_fetch_and_add) \
    && defined(AO_HAVE_fetch_and_add_read)
# define AO_fetch_and_add(addr, val) \
                                AO_fetch_and_add_read(addr, val)
# define AO_HAVE_fetch_and_add
#endif

#if defined(AO_HAVE_fetch_and_add_acquire) \
    && defined(AO_HAVE_nop_full) && !defined(AO_HAVE_fetch_and_add_full)
# define AO_fetch_and_add_full(addr, val) \
                (AO_nop_full(), AO_fetch_and_add_acquire(addr, val))
# define AO_HAVE_fetch_and_add_full
#endif

#if !defined(AO_HAVE_fetch_and_add_release_write) \
    && defined(AO_HAVE_fetch_and_add_write)
# define AO_fetch_and_add_release_write(addr, val) \
                                AO_fetch_and_add_write(addr, val)
# define AO_HAVE_fetch_and_add_release_write
#endif
#if !defined(AO_HAVE_fetch_and_add_release_write) \
    && defined(AO_HAVE_fetch_and_add_release)
# define AO_fetch_and_add_release_write(addr, val) \
                                AO_fetch_and_add_release(addr, val)
# define AO_HAVE_fetch_and_add_release_write
#endif

#if !defined(AO_HAVE_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_fetch_and_add_read)
# define AO_fetch_and_add_acquire_read(addr, val) \
                                AO_fetch_and_add_read(addr, val)
# define AO_HAVE_fetch_and_add_acquire_read
#endif
#if !defined(AO_HAVE_fetch_and_add_acquire_read) \
    && defined(AO_HAVE_fetch_and_add_acquire)
# define AO_fetch_and_add_acquire_read(addr, val) \
                                AO_fetch_and_add_acquire(addr, val)
# define AO_HAVE_fetch_and_add_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_fetch_and_add_acquire_read)
#   define AO_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_fetch_and_add_acquire_read(addr, val)
#   define AO_HAVE_fetch_and_add_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_fetch_and_add)
#   define AO_fetch_and_add_dd_acquire_read(addr, val) \
                                AO_fetch_and_add(addr, val)
#   define AO_HAVE_fetch_and_add_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* fetch_and_add1 */
#if defined(AO_HAVE_fetch_and_add_full) \
    && !defined(AO_HAVE_fetch_and_add1_full)
# define AO_fetch_and_add1_full(addr) \
                                AO_fetch_and_add_full(addr,1)
# define AO_HAVE_fetch_and_add1_full
#endif
#if defined(AO_HAVE_fetch_and_add_release) \
    && !defined(AO_HAVE_fetch_and_add1_release)
# define AO_fetch_and_add1_release(addr) \
                                AO_fetch_and_add_release(addr,1)
# define AO_HAVE_fetch_and_add1_release
#endif
#if defined(AO_HAVE_fetch_and_add_acquire) \
    && !defined(AO_HAVE_fetch_and_add1_acquire)
# define AO_fetch_and_add1_acquire(addr) \
                                AO_fetch_and_add_acquire(addr,1)
# define AO_HAVE_fetch_and_add1_acquire
#endif
#if defined(AO_HAVE_fetch_and_add_write) \
    && !defined(AO_HAVE_fetch_and_add1_write)
# define AO_fetch_and_add1_write(addr) \
                                AO_fetch_and_add_write(addr,1)
# define AO_HAVE_fetch_and_add1_write
#endif
#if defined(AO_HAVE_fetch_and_add_read) \
    && !defined(AO_HAVE_fetch_and_add1_read)
# define AO_fetch_and_add1_read(addr) \
                                AO_fetch_and_add_read(addr,1)
# define AO_HAVE_fetch_and_add1_read
#endif
#if defined(AO_HAVE_fetch_and_add_release_write) \
    && !defined(AO_HAVE_fetch_and_add1_release_write)
# define AO_fetch_and_add1_release_write(addr) \
                                AO_fetch_and_add_release_write(addr,1)
# define AO_HAVE_fetch_and_add1_release_write
#endif
#if defined(AO_HAVE_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_fetch_and_add1_acquire_read)
# define AO_fetch_and_add1_acquire_read(addr) \
                                AO_fetch_and_add_acquire_read(addr,1)
# define AO_HAVE_fetch_and_add1_acquire_read
#endif
#if defined(AO_HAVE_fetch_and_add) \
    && !defined(AO_HAVE_fetch_and_add1)
# define AO_fetch_and_add1(addr) AO_fetch_and_add(addr,1)
# define AO_HAVE_fetch_and_add1
#endif

#if defined(AO_HAVE_fetch_and_add1_full)
# if !defined(AO_HAVE_fetch_and_add1_release)
#   define AO_fetch_and_add1_release(addr) \
                                AO_fetch_and_add1_full(addr)
#   define AO_HAVE_fetch_and_add1_release
# endif
# if !defined(AO_HAVE_fetch_and_add1_acquire)
#   define AO_fetch_and_add1_acquire(addr) \
                                AO_fetch_and_add1_full(addr)
#   define AO_HAVE_fetch_and_add1_acquire
# endif
# if !defined(AO_HAVE_fetch_and_add1_write)
#   define AO_fetch_and_add1_write(addr) \
                                AO_fetch_and_add1_full(addr)
#   define AO_HAVE_fetch_and_add1_write
# endif
# if !defined(AO_HAVE_fetch_and_add1_read)
#   define AO_fetch_and_add1_read(addr) \
                                AO_fetch_and_add1_full(addr)
#   define AO_HAVE_fetch_and_add1_read
# endif
#endif /* AO_HAVE_fetch_and_add1_full */

#if !defined(AO_HAVE_fetch_and_add1) \
    && defined(AO_HAVE_fetch_and_add1_release)
# define AO_fetch_and_add1(addr) AO_fetch_and_add1_release(addr)
# define AO_HAVE_fetch_and_add1
#endif
#if !defined(AO_HAVE_fetch_and_add1) \
    && defined(AO_HAVE_fetch_and_add1_acquire)
# define AO_fetch_and_add1(addr) AO_fetch_and_add1_acquire(addr)
# define AO_HAVE_fetch_and_add1
#endif
#if !defined(AO_HAVE_fetch_and_add1) \
    && defined(AO_HAVE_fetch_and_add1_write)
# define AO_fetch_and_add1(addr) AO_fetch_and_add1_write(addr)
# define AO_HAVE_fetch_and_add1
#endif
#if !defined(AO_HAVE_fetch_and_add1) \
    && defined(AO_HAVE_fetch_and_add1_read)
# define AO_fetch_and_add1(addr) AO_fetch_and_add1_read(addr)
# define AO_HAVE_fetch_and_add1
#endif

#if defined(AO_HAVE_fetch_and_add1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_fetch_and_add1_full)
# define AO_fetch_and_add1_full(addr) \
                        (AO_nop_full(), AO_fetch_and_add1_acquire(addr))
# define AO_HAVE_fetch_and_add1_full
#endif

#if !defined(AO_HAVE_fetch_and_add1_release_write) \
    && defined(AO_HAVE_fetch_and_add1_write)
# define AO_fetch_and_add1_release_write(addr) \
                                AO_fetch_and_add1_write(addr)
# define AO_HAVE_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_fetch_and_add1_release_write) \
    && defined(AO_HAVE_fetch_and_add1_release)
# define AO_fetch_and_add1_release_write(addr) \
                                AO_fetch_and_add1_release(addr)
# define AO_HAVE_fetch_and_add1_release_write
#endif
#if !defined(AO_HAVE_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_fetch_and_add1_read)
# define AO_fetch_and_add1_acquire_read(addr) \
                                AO_fetch_and_add1_read(addr)
# define AO_HAVE_fetch_and_add1_acquire_read
#endif
#if !defined(AO_HAVE_fetch_and_add1_acquire_read) \
    && defined(AO_HAVE_fetch_and_add1_acquire)
# define AO_fetch_and_add1_acquire_read(addr) \
                                AO_fetch_and_add1_acquire(addr)
# define AO_HAVE_fetch_and_add1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_fetch_and_add1_acquire_read)
#   define AO_fetch_and_add1_dd_acquire_read(addr) \
                                AO_fetch_and_add1_acquire_read(addr)
#   define AO_HAVE_fetch_and_add1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_fetch_and_add1)
#   define AO_fetch_and_add1_dd_acquire_read(addr) \
                                AO_fetch_and_add1(addr)
#   define AO_HAVE_fetch_and_add1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* fetch_and_sub1 */
#if defined(AO_HAVE_fetch_and_add_full) \
    && !defined(AO_HAVE_fetch_and_sub1_full)
# define AO_fetch_and_sub1_full(addr) \
                AO_fetch_and_add_full(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_full
#endif
#if defined(AO_HAVE_fetch_and_add_release) \
    && !defined(AO_HAVE_fetch_and_sub1_release)
# define AO_fetch_and_sub1_release(addr) \
                AO_fetch_and_add_release(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_release
#endif
#if defined(AO_HAVE_fetch_and_add_acquire) \
    && !defined(AO_HAVE_fetch_and_sub1_acquire)
# define AO_fetch_and_sub1_acquire(addr) \
                AO_fetch_and_add_acquire(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_acquire
#endif
#if defined(AO_HAVE_fetch_and_add_write) \
    && !defined(AO_HAVE_fetch_and_sub1_write)
# define AO_fetch_and_sub1_write(addr) \
                AO_fetch_and_add_write(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_write
#endif
#if defined(AO_HAVE_fetch_and_add_read) \
    && !defined(AO_HAVE_fetch_and_sub1_read)
# define AO_fetch_and_sub1_read(addr) \
                AO_fetch_and_add_read(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_read
#endif
#if defined(AO_HAVE_fetch_and_add_release_write) \
    && !defined(AO_HAVE_fetch_and_sub1_release_write)
# define AO_fetch_and_sub1_release_write(addr) \
                AO_fetch_and_add_release_write(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_release_write
#endif
#if defined(AO_HAVE_fetch_and_add_acquire_read) \
    && !defined(AO_HAVE_fetch_and_sub1_acquire_read)
# define AO_fetch_and_sub1_acquire_read(addr) \
                AO_fetch_and_add_acquire_read(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1_acquire_read
#endif
#if defined(AO_HAVE_fetch_and_add) \
    && !defined(AO_HAVE_fetch_and_sub1)
# define AO_fetch_and_sub1(addr) \
                AO_fetch_and_add(addr, (AO_t)(-1))
# define AO_HAVE_fetch_and_sub1
#endif

#if defined(AO_HAVE_fetch_and_sub1_full)
# if !defined(AO_HAVE_fetch_and_sub1_release)
#   define AO_fetch_and_sub1_release(addr) \
                                AO_fetch_and_sub1_full(addr)
#   define AO_HAVE_fetch_and_sub1_release
# endif
# if !defined(AO_HAVE_fetch_and_sub1_acquire)
#   define AO_fetch_and_sub1_acquire(addr) \
                                AO_fetch_and_sub1_full(addr)
#   define AO_HAVE_fetch_and_sub1_acquire
# endif
# if !defined(AO_HAVE_fetch_and_sub1_write)
#   define AO_fetch_and_sub1_write(addr) \
                                AO_fetch_and_sub1_full(addr)
#   define AO_HAVE_fetch_and_sub1_write
# endif
# if !defined(AO_HAVE_fetch_and_sub1_read)
#   define AO_fetch_and_sub1_read(addr) \
                                AO_fetch_and_sub1_full(addr)
#   define AO_HAVE_fetch_and_sub1_read
# endif
#endif /* AO_HAVE_fetch_and_sub1_full */

#if !defined(AO_HAVE_fetch_and_sub1) \
    && defined(AO_HAVE_fetch_and_sub1_release)
# define AO_fetch_and_sub1(addr) AO_fetch_and_sub1_release(addr)
# define AO_HAVE_fetch_and_sub1
#endif
#if !defined(AO_HAVE_fetch_and_sub1) \
    && defined(AO_HAVE_fetch_and_sub1_acquire)
# define AO_fetch_and_sub1(addr) AO_fetch_and_sub1_acquire(addr)
# define AO_HAVE_fetch_and_sub1
#endif
#if !defined(AO_HAVE_fetch_and_sub1) \
    && defined(AO_HAVE_fetch_and_sub1_write)
# define AO_fetch_and_sub1(addr) AO_fetch_and_sub1_write(addr)
# define AO_HAVE_fetch_and_sub1
#endif
#if !defined(AO_HAVE_fetch_and_sub1) \
    && defined(AO_HAVE_fetch_and_sub1_read)
# define AO_fetch_and_sub1(addr) AO_fetch_and_sub1_read(addr)
# define AO_HAVE_fetch_and_sub1
#endif

#if defined(AO_HAVE_fetch_and_sub1_acquire) \
    && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_fetch_and_sub1_full)
# define AO_fetch_and_sub1_full(addr) \
                        (AO_nop_full(), AO_fetch_and_sub1_acquire(addr))
# define AO_HAVE_fetch_and_sub1_full
#endif

#if !defined(AO_HAVE_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_fetch_and_sub1_write)
# define AO_fetch_and_sub1_release_write(addr) \
                                AO_fetch_and_sub1_write(addr)
# define AO_HAVE_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_fetch_and_sub1_release_write) \
    && defined(AO_HAVE_fetch_and_sub1_release)
# define AO_fetch_and_sub1_release_write(addr) \
                                AO_fetch_and_sub1_release(addr)
# define AO_HAVE_fetch_and_sub1_release_write
#endif
#if !defined(AO_HAVE_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_fetch_and_sub1_read)
# define AO_fetch_and_sub1_acquire_read(addr) \
                                AO_fetch_and_sub1_read(addr)
# define AO_HAVE_fetch_and_sub1_acquire_read
#endif
#if !defined(AO_HAVE_fetch_and_sub1_acquire_read) \
    && defined(AO_HAVE_fetch_and_sub1_acquire)
# define AO_fetch_and_sub1_acquire_read(addr) \
                                AO_fetch_and_sub1_acquire(addr)
# define AO_HAVE_fetch_and_sub1_acquire_read
#endif

#ifdef AO_NO_DD_ORDERING
# if defined(AO_HAVE_fetch_and_sub1_acquire_read)
#   define AO_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_fetch_and_sub1_acquire_read(addr)
#   define AO_HAVE_fetch_and_sub1_dd_acquire_read
# endif
#else
# if defined(AO_HAVE_fetch_and_sub1)
#   define AO_fetch_and_sub1_dd_acquire_read(addr) \
                                AO_fetch_and_sub1(addr)
#   define AO_HAVE_fetch_and_sub1_dd_acquire_read
# endif
#endif /* !AO_NO_DD_ORDERING */

/* and */
#if defined(AO_HAVE_compare_and_swap_full) \
    && !defined(AO_HAVE_and_full)
  AO_INLINE void
  AO_and_full(volatile AO_t *addr, AO_t value)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_full(addr, old,
                                                           old & value)));
  }
# define AO_HAVE_and_full
#endif

#if defined(AO_HAVE_and_full)
# if !defined(AO_HAVE_and_release)
#   define AO_and_release(addr, val) AO_and_full(addr, val)
#   define AO_HAVE_and_release
# endif
# if !defined(AO_HAVE_and_acquire)
#   define AO_and_acquire(addr, val) AO_and_full(addr, val)
#   define AO_HAVE_and_acquire
# endif
# if !defined(AO_HAVE_and_write)
#   define AO_and_write(addr, val) AO_and_full(addr, val)
#   define AO_HAVE_and_write
# endif
# if !defined(AO_HAVE_and_read)
#   define AO_and_read(addr, val) AO_and_full(addr, val)
#   define AO_HAVE_and_read
# endif
#endif /* AO_HAVE_and_full */

#if !defined(AO_HAVE_and) && defined(AO_HAVE_and_release)
# define AO_and(addr, val) AO_and_release(addr, val)
# define AO_HAVE_and
#endif
#if !defined(AO_HAVE_and) && defined(AO_HAVE_and_acquire)
# define AO_and(addr, val) AO_and_acquire(addr, val)
# define AO_HAVE_and
#endif
#if !defined(AO_HAVE_and) && defined(AO_HAVE_and_write)
# define AO_and(addr, val) AO_and_write(addr, val)
# define AO_HAVE_and
#endif
#if !defined(AO_HAVE_and) && defined(AO_HAVE_and_read)
# define AO_and(addr, val) AO_and_read(addr, val)
# define AO_HAVE_and
#endif

#if defined(AO_HAVE_and_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_and_full)
# define AO_and_full(addr, val) \
                        (AO_nop_full(), AO_and_acquire(addr, val))
# define AO_HAVE_and_full
#endif

#if !defined(AO_HAVE_and_release_write) \
    && defined(AO_HAVE_and_write)
# define AO_and_release_write(addr, val) AO_and_write(addr, val)
# define AO_HAVE_and_release_write
#endif
#if !defined(AO_HAVE_and_release_write) \
    && defined(AO_HAVE_and_release)
# define AO_and_release_write(addr, val) AO_and_release(addr, val)
# define AO_HAVE_and_release_write
#endif
#if !defined(AO_HAVE_and_acquire_read) \
    && defined(AO_HAVE_and_read)
# define AO_and_acquire_read(addr, val) AO_and_read(addr, val)
# define AO_HAVE_and_acquire_read
#endif
#if !defined(AO_HAVE_and_acquire_read) \
    && defined(AO_HAVE_and_acquire)
# define AO_and_acquire_read(addr, val) AO_and_acquire(addr, val)
# define AO_HAVE_and_acquire_read
#endif

/* or */
#if defined(AO_HAVE_compare_and_swap_full) \
    && !defined(AO_HAVE_or_full)
  AO_INLINE void
  AO_or_full(volatile AO_t *addr, AO_t value)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_full(addr, old,
                                                           old | value)));
  }
# define AO_HAVE_or_full
#endif

#if defined(AO_HAVE_or_full)
# if !defined(AO_HAVE_or_release)
#   define AO_or_release(addr, val) AO_or_full(addr, val)
#   define AO_HAVE_or_release
# endif
# if !defined(AO_HAVE_or_acquire)
#   define AO_or_acquire(addr, val) AO_or_full(addr, val)
#   define AO_HAVE_or_acquire
# endif
# if !defined(AO_HAVE_or_write)
#   define AO_or_write(addr, val) AO_or_full(addr, val)
#   define AO_HAVE_or_write
# endif
# if !defined(AO_HAVE_or_read)
#   define AO_or_read(addr, val) AO_or_full(addr, val)
#   define AO_HAVE_or_read
# endif
#endif /* AO_HAVE_or_full */

#if !defined(AO_HAVE_or) && defined(AO_HAVE_or_release)
# define AO_or(addr, val) AO_or_release(addr, val)
# define AO_HAVE_or
#endif
#if !defined(AO_HAVE_or) && defined(AO_HAVE_or_acquire)
# define AO_or(addr, val) AO_or_acquire(addr, val)
# define AO_HAVE_or
#endif
#if !defined(AO_HAVE_or) && defined(AO_HAVE_or_write)
# define AO_or(addr, val) AO_or_write(addr, val)
# define AO_HAVE_or
#endif
#if !defined(AO_HAVE_or) && defined(AO_HAVE_or_read)
# define AO_or(addr, val) AO_or_read(addr, val)
# define AO_HAVE_or
#endif

#if defined(AO_HAVE_or_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_or_full)
# define AO_or_full(addr, val) \
                        (AO_nop_full(), AO_or_acquire(addr, val))
# define AO_HAVE_or_full
#endif

#if !defined(AO_HAVE_or_release_write) \
    && defined(AO_HAVE_or_write)
# define AO_or_release_write(addr, val) AO_or_write(addr, val)
# define AO_HAVE_or_release_write
#endif
#if !defined(AO_HAVE_or_release_write) \
    && defined(AO_HAVE_or_release)
# define AO_or_release_write(addr, val) AO_or_release(addr, val)
# define AO_HAVE_or_release_write
#endif
#if !defined(AO_HAVE_or_acquire_read) && defined(AO_HAVE_or_read)
# define AO_or_acquire_read(addr, val) AO_or_read(addr, val)
# define AO_HAVE_or_acquire_read
#endif
#if !defined(AO_HAVE_or_acquire_read) \
    && defined(AO_HAVE_or_acquire)
# define AO_or_acquire_read(addr, val) AO_or_acquire(addr, val)
# define AO_HAVE_or_acquire_read
#endif

/* xor */
#if defined(AO_HAVE_compare_and_swap_full) \
    && !defined(AO_HAVE_xor_full)
  AO_INLINE void
  AO_xor_full(volatile AO_t *addr, AO_t value)
  {
    AO_t old;

    do
      {
        old = *addr;
      }
    while (AO_EXPECT_FALSE(!AO_compare_and_swap_full(addr, old,
                                                           old ^ value)));
  }
# define AO_HAVE_xor_full
#endif

#if defined(AO_HAVE_xor_full)
# if !defined(AO_HAVE_xor_release)
#   define AO_xor_release(addr, val) AO_xor_full(addr, val)
#   define AO_HAVE_xor_release
# endif
# if !defined(AO_HAVE_xor_acquire)
#   define AO_xor_acquire(addr, val) AO_xor_full(addr, val)
#   define AO_HAVE_xor_acquire
# endif
# if !defined(AO_HAVE_xor_write)
#   define AO_xor_write(addr, val) AO_xor_full(addr, val)
#   define AO_HAVE_xor_write
# endif
# if !defined(AO_HAVE_xor_read)
#   define AO_xor_read(addr, val) AO_xor_full(addr, val)
#   define AO_HAVE_xor_read
# endif
#endif /* AO_HAVE_xor_full */

#if !defined(AO_HAVE_xor) && defined(AO_HAVE_xor_release)
# define AO_xor(addr, val) AO_xor_release(addr, val)
# define AO_HAVE_xor
#endif
#if !defined(AO_HAVE_xor) && defined(AO_HAVE_xor_acquire)
# define AO_xor(addr, val) AO_xor_acquire(addr, val)
# define AO_HAVE_xor
#endif
#if !defined(AO_HAVE_xor) && defined(AO_HAVE_xor_write)
# define AO_xor(addr, val) AO_xor_write(addr, val)
# define AO_HAVE_xor
#endif
#if !defined(AO_HAVE_xor) && defined(AO_HAVE_xor_read)
# define AO_xor(addr, val) AO_xor_read(addr, val)
# define AO_HAVE_xor
#endif

#if defined(AO_HAVE_xor_acquire) && defined(AO_HAVE_nop_full) \
    && !defined(AO_HAVE_xor_full)
# define AO_xor_full(addr, val) \
                        (AO_nop_full(), AO_xor_acquire(addr, val))
# define AO_HAVE_xor_full
#endif

#if !defined(AO_HAVE_xor_release_write) \
    && defined(AO_HAVE_xor_write)
# define AO_xor_release_write(addr, val) AO_xor_write(addr, val)
# define AO_HAVE_xor_release_write
#endif
#if !defined(AO_HAVE_xor_release_write) \
    && defined(AO_HAVE_xor_release)
# define AO_xor_release_write(addr, val) AO_xor_release(addr, val)
# define AO_HAVE_xor_release_write
#endif
#if !defined(AO_HAVE_xor_acquire_read) \
    && defined(AO_HAVE_xor_read)
# define AO_xor_acquire_read(addr, val) AO_xor_read(addr, val)
# define AO_HAVE_xor_acquire_read
#endif
#if !defined(AO_HAVE_xor_acquire_read) \
    && defined(AO_HAVE_xor_acquire)
# define AO_xor_acquire_read(addr, val) AO_xor_acquire(addr, val)
# define AO_HAVE_xor_acquire_read
#endif

/* and/or/xor_dd_aquire_read are meaningless.     */
