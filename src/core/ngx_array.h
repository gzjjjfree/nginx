
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_ARRAY_H_INCLUDED_      /* 防止ngx_array.h重复引入 */
#define _NGX_ARRAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


typedef struct {
    void        *elts;               /* 定义无类型指针*elts */
    ngx_uint_t   nelts;              /* 定义ngx_uint_t类型变量nelts */
    size_t       size;               /* 定义size_t类型变量size */
    ngx_uint_t   nalloc;             /* 定义ngx_uint_t类型变量nalloc */
    ngx_pool_t  *pool;               /* 定义ngx_pool_t类型指针*pool */
} ngx_array_t;                       /*ngx_array_t的数据结构*/


ngx_array_t *ngx_array_create(ngx_pool_t *p, ngx_uint_t n, size_t size);     /*定义ngx_array_create为ngx_array_t类型的指针（包含参数三个）*/
void ngx_array_destroy(ngx_array_t *a);                                      /*定义无类型函数(参数为ngx_array_t型指针)*/
void *ngx_array_push(ngx_array_t *a);                                        /*定义无类型函数指针(参数为ngx_array_t型指针)*/
void *ngx_array_push_n(ngx_array_t *a, ngx_uint_t n);                        /*定义无类型函数指针(参数为ngx_array_t型指针，ngx_uint_t类型变量)*/


static ngx_inline ngx_int_t
ngx_array_init(ngx_array_t *array, ngx_pool_t *pool, ngx_uint_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    array->elts = ngx_palloc(pool, n * size);
    if (array->elts == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;
}


#endif /* _NGX_ARRAY_H_INCLUDED_ */
