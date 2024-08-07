/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CLAVES_H_RPCGEN
#define _CLAVES_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct arg {
	int key;
	char value1[256];
	int N_value2;
	double V_value2[32];
};
typedef struct arg arg;

struct res {
	char value1[256];
	int N_value2;
	double V_value2[32];
	int error_code;
};
typedef struct res res;

#define CLAVES 99
#define CLAVESVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define init_x 1
extern  enum clnt_stat init_x_1(int *, CLIENT *);
extern  bool_t init_x_1_svc(int *, struct svc_req *);
#define set_value_x 2
extern  enum clnt_stat set_value_x_1(struct arg , int *, CLIENT *);
extern  bool_t set_value_x_1_svc(struct arg , int *, struct svc_req *);
#define get_value_x 3
extern  enum clnt_stat get_value_x_1(int , struct res *, CLIENT *);
extern  bool_t get_value_x_1_svc(int , struct res *, struct svc_req *);
#define modify_value_x 4
extern  enum clnt_stat modify_value_x_1(struct arg , int *, CLIENT *);
extern  bool_t modify_value_x_1_svc(struct arg , int *, struct svc_req *);
#define delete_key_x 5
extern  enum clnt_stat delete_key_x_1(int , int *, CLIENT *);
extern  bool_t delete_key_x_1_svc(int , int *, struct svc_req *);
#define exist_x 6
extern  enum clnt_stat exist_x_1(int , int *, CLIENT *);
extern  bool_t exist_x_1_svc(int , int *, struct svc_req *);
extern int claves_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define init_x 1
extern  enum clnt_stat init_x_1();
extern  bool_t init_x_1_svc();
#define set_value_x 2
extern  enum clnt_stat set_value_x_1();
extern  bool_t set_value_x_1_svc();
#define get_value_x 3
extern  enum clnt_stat get_value_x_1();
extern  bool_t get_value_x_1_svc();
#define modify_value_x 4
extern  enum clnt_stat modify_value_x_1();
extern  bool_t modify_value_x_1_svc();
#define delete_key_x 5
extern  enum clnt_stat delete_key_x_1();
extern  bool_t delete_key_x_1_svc();
#define exist_x 6
extern  enum clnt_stat exist_x_1();
extern  bool_t exist_x_1_svc();
extern int claves_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_arg (XDR *, arg*);
extern  bool_t xdr_res (XDR *, res*);

#else /* K&R C */
extern bool_t xdr_arg ();
extern bool_t xdr_res ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CLAVES_H_RPCGEN */
