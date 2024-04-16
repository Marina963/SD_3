/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "claves.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
init_x_1(int *clnt_res, CLIENT *clnt)
{
	 return (clnt_call (clnt, init_x, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));

}

enum clnt_stat 
set_value_x_1(struct arg arg1, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, set_value_x,
		(xdrproc_t) xdr_arg, (caddr_t) &arg1,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
get_value_x_1(int key, struct res *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, get_value_x,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_res, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
modify_value_x_1(struct arg arg1, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, modify_value_x,
		(xdrproc_t) xdr_arg, (caddr_t) &arg1,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
delete_key_x_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, delete_key_x,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
exist_x_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, exist_x,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}