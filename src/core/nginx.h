
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGINX_H_INCLUDED_      /*如果 .nginx.h.included.不存在就引入  防止重复引用？*/
#define _NGINX_H_INCLUDED_


#define nginx_version      1023001       /* nginx_version = 1023001？数字替换成版本号英文？*/
#define NGINX_VERSION      "1.23.1"
#define NGINX_VER          "nginx/" NGINX_VERSION   /* NGINX_VER = "nginx/" & 变量NGINX_VERSION？*/

#ifdef NGX_BUILD           /*如果当前的宏已被定义过，则对“程序段1”进行编译*/
#define NGINX_VER_BUILD    NGINX_VER " (" NGX_BUILD ")"     /*运行 NGX_BUILD 说明一些东西应该*/
#else
#define NGINX_VER_BUILD    NGINX_VER     /*NGINX_VER_BUILD为NGINX_VER应该是版本的路径*/
#endif

#define NGINX_VAR          "NGINX"    /*NGINX_VAR  =字符串 "NGINX" */
#define NGX_OLDPID_EXT     ".oldbin"


#endif /* _NGINX_H_INCLUDED_ */   /* 否则不引入？*/
