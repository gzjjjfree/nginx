
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_BUF_H_INCLUDED_               /*防止重复引入*/
#define _NGX_BUF_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef void *            ngx_buf_tag_t;  /*定义无类型指针*/

typedef struct ngx_buf_s  ngx_buf_t;      /*定义标识为ngx_buf_s的结构体起名字为ngx_buf_t，可以用后者来定义变量(ngx_buf_t 变量名)*/

struct ngx_buf_s {
    u_char          *pos;           /*u_char是无符号的char型*/
    u_char          *last;          /*u_char是无符号的char型*/
    off_t            file_pos;      /**/
    off_t            file_last;     /**/

    u_char          *start;         /* start of buffer *//*u_char是无符号的char型*/
    u_char          *end;           /* end of buffer *//*u_char是无符号的char型*/
    ngx_buf_tag_t    tag;           /*定义无类型指针*/
    ngx_file_t      *file;          /**/
    ngx_buf_t       *shadow;        /*ngx_buf_s数据结构的指针，应该就是指向这个结构开头地方的地址*/


    /* the buf's content could be changed */
    unsigned         temporary:1;            /*标记信号*/

    /*
     * the buf's content is in a memory cache or in a read only memory
     * and must not be changed
     */
    unsigned         memory:1;              /*标记信号非负整数*/

    /* the buf's content is mmap()ed and must not be changed */
    unsigned         mmap:1;               /*标记信号*/

    unsigned         recycled:1;           /*标记信号*/
    unsigned         in_file:1;            /*标记信号*/
    unsigned         flush:1;              /*标记信号*/
    unsigned         sync:1;               /*标记信号*/
    unsigned         last_buf:1;           /*标记信号*/
    unsigned         last_in_chain:1;      /*标记信号*/

    unsigned         last_shadow:1;        /*标记信号*/
    unsigned         temp_file:1;          /*标记信号*/

    /* STUB */ int   num;                 /*定义num为整型*/
};


struct ngx_chain_s {                     /*定义ngx_chain_s数据结构类型*/
    ngx_buf_t    *buf;                   /*定义*buf为ngx_buf_t数据结构类型指针*/
    ngx_chain_t  *next;                  /*定义*next为ngx_chain_t数据结构类型指针,应该指向下个结构体*/
};


typedef struct {                         /*定义 ngx_bufs_t数据结构类型，这个应该用在复数*/
    ngx_int_t    num;                    /*定义num为ngx_int_t型*/
    size_t       size;
} ngx_bufs_t;


typedef struct ngx_output_chain_ctx_s  ngx_output_chain_ctx_t;

typedef ngx_int_t (*ngx_output_chain_filter_pt)(void *ctx, ngx_chain_t *in);   /*定义ngx_output_chain_filter_pt为ngx_int_t型指针包含(void *ctx, ngx_chain_t *in)*/

typedef void (*ngx_output_chain_aio_pt)(ngx_output_chain_ctx_t *ctx,  /*定义ngx_output_chain_aio_pt为 void型指针包含(ngx_output_chain_ctx_t *ctx,ngx_file_t *file)*/
    ngx_file_t *file);

struct ngx_output_chain_ctx_s {                           /*定义ngx_output_chain_ctx_s结构体*/
    ngx_buf_t                   *buf;                     /*定义*buf为ngx_buf_t数据结构类型指针*/ 
    ngx_chain_t                 *in;                      /*定义*in为ngx_chain_t数据结构类型指针*/
    ngx_chain_t                 *free;                    /*定义 *free为ngx_chain_t数据结构类型指针*/
    ngx_chain_t                 *busy;                    /*定义 *busy为ngx_chain_t数据结构类型指针*/

    unsigned                     sendfile:1;              /*标记信号*/
    unsigned                     directio:1;              /*标记信号*/
    unsigned                     unaligned:1;             /*标记信号*/
    unsigned                     need_in_memory:1;        /*标记信号*/
    unsigned                     need_in_temp:1;          /*标记信号*/
    unsigned                     aio:1;                   /*标记信号*/

#if (NGX_HAVE_FILE_AIO || NGX_COMPAT)
    ngx_output_chain_aio_pt      aio_handler;             /*定义aio_handler为ngx_output_chain_aio_pt类型*/
#endif

#if (NGX_THREADS || NGX_COMPAT)
    ngx_int_t                  (*thread_handler)(ngx_thread_task_t *task,   /*声明指针变量thread_handler包含(ngx_thread_task_t *task,ngx_file_t *file)*/
                                                 ngx_file_t *file);
    ngx_thread_task_t           *thread_task;                   /*声明指针变量 *thread_task为ngx_thread_task_t类型*/  
#endif

    off_t                        alignment;                /*定义alignment为off_t类型*/

    ngx_pool_t                  *pool;                     /*定义指针 *pool为ngx_pool_t类型*/
    ngx_int_t                    allocated;                /*定义allocated为ngx_int_t类型*/
    ngx_bufs_t                   bufs;                     /*定义bufs为ngx_bufs_t类型*/
    ngx_buf_tag_t                tag;                      /*定义tag为ngx_buf_tag_t类型*/

    ngx_output_chain_filter_pt   output_filter;            /*定义output_filter为ngx_output_chain_filter_pt类型*/
    void                        *filter_ctx;               /*定义指针*filter_ctx为void类型*/
};

 
typedef struct {                                           /*定义ngx_chain_writer_ctx_t数据结构体*/
    ngx_chain_t                 *out;                      /*定义指针 *out为ngx_chain_t类型*/
    ngx_chain_t                **last;                     /*定义指针 **last为ngx_chain_t类型*/
    ngx_connection_t            *connection;               /*定义指针 *connection为ngx_connection_t 类型*/
    ngx_pool_t                  *pool;                     /*定义指针*pool为 ngx_pool_t 类型*/
    off_t                        limit;                    /*定义limit为off_t类型*/
} ngx_chain_writer_ctx_t;


#define NGX_CHAIN_ERROR     (ngx_chain_t *) NGX_ERROR


#define ngx_buf_in_memory(b)       ((b)->temporary || (b)->memory || (b)->mmap)
#define ngx_buf_in_memory_only(b)  (ngx_buf_in_memory(b) && !(b)->in_file)

#define ngx_buf_special(b)                                                   \
    (((b)->flush || (b)->last_buf || (b)->sync)                              \
     && !ngx_buf_in_memory(b) && !(b)->in_file)

#define ngx_buf_sync_only(b)                                                 \
    ((b)->sync && !ngx_buf_in_memory(b)                                      \
     && !(b)->in_file && !(b)->flush && !(b)->last_buf)

#define ngx_buf_size(b)                                                      \
    (ngx_buf_in_memory(b) ? (off_t) ((b)->last - (b)->pos):                  \
                            ((b)->file_last - (b)->file_pos))

ngx_buf_t *ngx_create_temp_buf(ngx_pool_t *pool, size_t size);
ngx_chain_t *ngx_create_chain_of_bufs(ngx_pool_t *pool, ngx_bufs_t *bufs);


#define ngx_alloc_buf(pool)  ngx_palloc(pool, sizeof(ngx_buf_t))
#define ngx_calloc_buf(pool) ngx_pcalloc(pool, sizeof(ngx_buf_t))

ngx_chain_t *ngx_alloc_chain_link(ngx_pool_t *pool);
#define ngx_free_chain(pool, cl)                                             \
    (cl)->next = (pool)->chain;                                              \
    (pool)->chain = (cl)



ngx_int_t ngx_output_chain(ngx_output_chain_ctx_t *ctx, ngx_chain_t *in);
ngx_int_t ngx_chain_writer(void *ctx, ngx_chain_t *in);

ngx_int_t ngx_chain_add_copy(ngx_pool_t *pool, ngx_chain_t **chain,
    ngx_chain_t *in);
ngx_chain_t *ngx_chain_get_free_buf(ngx_pool_t *p, ngx_chain_t **free);
void ngx_chain_update_chains(ngx_pool_t *p, ngx_chain_t **free,
    ngx_chain_t **busy, ngx_chain_t **out, ngx_buf_tag_t tag);

off_t ngx_chain_coalesce_file(ngx_chain_t **in, off_t limit);

ngx_chain_t *ngx_chain_update_sent(ngx_chain_t *in, off_t sent);

#endif /* _NGX_BUF_H_INCLUDED_ */
