﻿#ifndef _H_SIMPLEC_STRUCT
#define _H_SIMPLEC_STRUCT

//
// 数据结构从这个头文件集成开始
// 构建统一的标识文件, 构建统一的注册函数, 构建统一基础头文件
//
// author : wz
//

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

//
// 定义的函数操作基本行为返回的枚举, 用于判断返回值状态的状态码
// 使用举例:
// 
//	flag_e flag = xxx("heoo");
//	if(flag < RT_Success_Base) {
//		fprintf(stderr, "error msg xxx!\n");
//		exit(EXIT_FAILURE);
//	}
//
//	>=0 标识 Success状态, <0 标识 Error状态
//
typedef enum {
	RT_Success_Close	= +1,			//文件描述符读取关闭, 读取完毕也会返回这个
	RT_Success_Base		= +0,			//结果正确的返回宏

	RT_Error_Base		= -1,			//错误基类型, 所有错误都可用它, 在不清楚的情况下
	RT_Error_Param		= -2,			//调用的参数错误
	RT_Error_Malloc		= -3,			//内存分配错误
	RT_Error_Fopen		= -4,			//文件打开失败	
} flag_e;

//
// 定义一些通用的函数指针帮助,主要用于基库的封装中.
// 有构造函数, 析构函数, 比较函数, 轮询函数等 
//
typedef void *	(* new_f)();
typedef void	(* die_f)(void * node);
// cmp_f 最好 是 int cmp(const void * ln, const void * rn); 标准结构
typedef int		(* cmp_f)();
// 循环操作函数, arg 外部参数, node 内部节点
typedef flag_e	(* each_f)(void * node, void * arg);

// 
// 控制台输出完整的消息提示信息, 其中fmt必须是 "" 包裹的字符串
// CERR			-> 简单的消息打印
// CERR_EXIT	-> 输出错误信息, 并推出当前进程
// CERR_IF		-> if语句检查, 如果符合标准错误直接退出
// 
#ifndef _H_CERR
#define _H_CERR

#define CERR(fmt, ...) \
	fprintf(stderr, "[%s:%s:%d][errno %d:%s]" fmt "\n",\
		__FILE__, __func__, __LINE__, errno, strerror(errno), ##__VA_ARGS__)

#define CERR_EXIT(fmt,...) \
	CERR(fmt, ##__VA_ARGS__), exit(EXIT_FAILURE)

#define CERR_IF(code) \
	if((code) < 0) \
		CERR_EXIT(#code)

#endif

#endif // !_H_SIMPLEC_STRUCT