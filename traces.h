#ifndef _TRACES_H
#define _TRACES_H

#define DEBUG 1

#if DEBUG
#define TRACE_DEBUG(fmt, args ...) printf("[DEBUG] %s(%d): "fmt"\n",__FUNCTION__, __LINE__, ##args) 
#endif

#define TRACE_ERR(fmt, args ...) printf("[ERR] %s(%d): "fmt"\n",__FUNCTION__, __LINE__, ##args) 
#define TRACE_WARNING(fmt, args ...) printf("[WARNING] %s(%d): "fmt"\n",__FUNCTION__, __LINE__, ##args)
#define TRACE_INFO(fmt, args ...) printf("[INFO] %s(%d): "fmt"\n",__FUNCTION__, __LINE__, ##args)
#define TRACE_NOTICE(fmt, args ...) printf("[NOTICE] %s(%d): "fmt"\n",__FUNCTION__, __LINE__, ##args)
#endif //_TRACES_H
