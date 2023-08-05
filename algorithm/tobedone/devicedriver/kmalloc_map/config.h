/***********************************
 Copyright(C), 2013 LCP
 FileName:  config.h
 Author:    WangXiaoLu
 Date:      2013.04.08
 Description:  .
 History:
 Author       Date            Desc
 WangXiaoLu   2013.04.08     Create
************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

//#define USE_NOPAGE
#ifndef USE_NOPAGE
    #define USE_REMAP_PFN_RANGE 
#endif

#define PAGE_NUM 1  //paginal number 
#define BUF_SIZE  (PAGE_SIZE * PAGE_NUM)

#endif//__CONFIG_H__
