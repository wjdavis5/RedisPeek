#include "redismodule.h"
#include <stdlib.h>

int HelloworldRand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    if (argc != 2){
        return RedisModule_WrongArity(ctx);
    }
    
    RedisModuleCallReply *rep = RedisModule_Call(ctx, "TYPE", "s",argv[1]);
    if (RedisModule_CallReplyType(rep) == REDISMODULE_REPLY_ERROR) {
        RedisModule_ReplyWithCallReply(ctx, rep);
        return REDISMODULE_ERR;
    }
    RedisModule_ReplyWithCallReply(ctx, rep);
    switch (RedisModule_CallReplyType(rep))
    {
    case REDISMODULE_REPLY_STRING:
        rep = RedisModule_Call(ctx, "GET", "s", argv[1]);
        break;
    
    default:
        break;
    }
    
    RedisModule_ReplyWithCallReply(ctx, rep);
    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"PEEK",1,REDISMODULE_APIVER_1) == REDISMODULE_ERR) 
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"PEEK",
        HelloworldRand_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
/*
RedisModuleCtx *ctx, 
const char *name, 
RedisModuleCmdFunc cmdfunc, 
const char *strflags, 
int firstkey, 
int lastkey, 
int keystep);

*/
