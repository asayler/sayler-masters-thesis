/* custos.h
 *
 * custos_client interface - C bindings
 *
 * By Andy Sayler (www.andysayler.com)
 * Initially created  05/13
 *
 */

#ifndef CUSTOS_CLIENT_H
#define CUSTOS_CLIENT_H

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <uuid/uuid.h>
#include <json/json.h>

#include "custos_http.h"
#include "custos_json.h"

#define CUS_VERSION "0.2-dev"

#define CUSTOS_ENDPOINT_GRP "/grp"
#define CUSTOS_ENDPOINT_OBJ "/obj"
#define CUSTOS_ENDPOINT_ADT "/audit"
#define CUSTOS_ENDPOINT_ACS "/acs"

#define CUSTOS_QUERY_AA  "aa"
#define CUSTOS_QUERY_CHK "chk"
#define CUSTOS_QUERY_REV "rev"

typedef enum custosOp {
    CUS_OP_OBJ_CREATE = 0,
    CUS_OP_OBJ_DELETE,
    CUS_OP_OBJ_READ,
    CUS_OP_OBJ_UPDATE,
    CUS_OP_OBJ_MAX
} custosOp_t;

typedef enum custosResStatus {
    CUS_RESSTAT_OKAY = 0,
    CUS_RESSTAT_UGROUP,
    CUS_RESSTAT_UOBJECT,
    CUS_RESSTAT_ERROR,
    CUS_RESSTAT_MAX
} custosResStatus_t;

#define CUS_RESSTAT_ACCEPTED_STR "okay"
#define CUS_RESSTAT_UGROUP_STR   "unknown_group"
#define CUS_RESSTAT_UOBJECT_STR  "unknown_object"
#define CUS_RESSTAT_ERROR_STR    "error"

typedef enum custosAttrStatus {
    CUS_ATTRSTAT_ACCEPTED = 0,
    CUS_ATTRSTAT_DENIED,
    CUS_ATTRSTAT_REQUIRED,
    CUS_ATTRSTAT_OPTIONAL,
    CUS_ATTRSTAT_IGNORED,
    CUS_ATTRSTAT_MAX
} custosAttrStatus_t;

#define CUS_ATTRSTAT_ACCEPTED_STR "accepted"
#define CUS_ATTRSTAT_DENIED_STR   "denied"
#define CUS_ATTRSTAT_REQUIRED_STR "required"
#define CUS_ATTRSTAT_OPTIONAL_STR "optional"
#define CUS_ATTRSTAT_IGNORED_STR  "ignored"

typedef enum custosKeyStatus {
    CUS_KEYSTAT_ACCEPTED = 0,
    CUS_KEYSTAT_DENIED,
    CUS_KEYSTAT_MAX
} custosKeyStatus_t;

#define CUS_KEYSTAT_ACCEPTED_STR "accepted"
#define CUS_KEYSTAT_DENIED_STR   "denied"

typedef enum custosACSStatus_t {
    CUS_ACSSTAT_ACCEPTED = 0,
    CUS_ACSSTAT_DENIED,
    CUS_AVSSTAT_MAX
}

#define CUS_ACSSTAT_ACCEPTED_STR "accepted"
#define CUS_ACSSTAT_DENIED_STR   "denied"

typedef enum custosAttrClass {
    CUS_ATTRCLASS_IMPLICIT = 0,
    CUS_ATTRCLASS_EXPLICIT,
    CUS_ATTRCLASS_MAX
} custosAttrClass_t;

#define CUS_ATTRCLASS_IMPLICIT_STR "implicit"
#define CUS_ATTRCLASS_EXPLICIT_STR "explicit"

typedef enum custosAttrType {
    CUS_ATTRTYPE_EXP_USR = 0,
    CUS_ATTRTYPE_EXP_PSK,
    CUS_ATTRTYPE_EXP_PSKSHA2,
    CUS_ATTRTYPE_EXP_PSHBCRPT,
    CUS_ATTRTYPE_IMP_SOURCEIP = 0,
    CUS_ATTRTYPE_IMP_USRAGENT,
    CUS_ATTRTYPE_IMP_AUTHTYPE,
    CUS_ATTRTYPE_IMP_AUTHVAL,
    CUS_ATTRTYPE_IMP_TIMEUTC,
    CUS_ATTRTYPE_IMP_MAX
} custosAttrType_t;

#define CUS_ATTRTYPE_MAX CUS_ATTRTYPE_IMP_MAX
#define CUS_ATTRTYPE_EXP_USR_STR        "user_id"
#define CUS_ATTRTYPE_EXP_PSK_STR        "psk"
#define CUS_ATTRTYPE_EXP_PSKSHA2_STR    "psk_sha256"
#define CUS_ATTRTYPE_EXP_PSKBCRPT_STR   "psk_bcrypt"
#define CUS_ATTRTYPE_IMP_SOURCEIP_STR   "ip_src"
#define CUS_ATTRTYPE_IMP_USRAGENT_STR   "user_agent"
#define CUS_ATTRTYPE_IMP_AUTHTYPE_STR   "auth_type"
#define CUS_ATTRTYPE_IMP_AUTHVAL_STR    "auth_value"
#define CUS_ATTRTYPE_IMP_TIMEUTC_STR    "time_utc"

typedef enum custosObjPerm_t {
    CUS_OBJPERM_DELETE = 0,
    CUS_OBJPERM_READ,
    CUS_OBJPERM_UPDATE,
    CUS_OBJPERM_AUDIT,
    CUS_OBJPERM_CLEAN,
    CUS_OBJPERM_ACSGET,
    CUS_OBJPERM_ACSSET,
    CUS_OBJPERM_MAX
}

#define CUS_OBJPERM_DELETE "obj_delete"
#define CUS_OBJPERM_READ   "obj_read"
#define CUS_OBJPERM_UPDATE "obj_update"
#define CUS_OBJPERM_AUDIT  "obj_audit"
#define CUS_OBJPERM_CLEAN  "obj_clean"
#define CUS_OBJPERM_ACSGET "obj_acs_get"
#define CUS_OBJPERM_ACSSET "obj_acs_set"

typedef struct custosAttr {
    custosAttrClass_t  class;
    custosAttrType_t   type;
    size_t             size;
    uint8_t*           val;
} custosAttr_t;

typedef struct custosAttrReq {
    bool               echo;
    custosAttr_t*      attr;
} custosAttrReq_t;

typedef struct custosAttrRes {
    custosAttrStatus_t status;
    bool               echo;
    size_t             res_size;
    uint8_t*           res_val;
    custosAttr_t*      attr;
} custosAttrRes_t;

typedef struct custosKey {
    uuid_t   uuid;
    uint64_t revision;
    size_t   size;
    uint8_t* val;
} custosKey_t;

typedef struct custosKeyReq {
    bool              echo;
    custosKey_t*      key;
} custosKeyReq_t;

typedef struct custosKeyRes {
    custosKeyStatus_t status;
    bool              echo;
    custosKey_t*      key;
} custosKeyRes_t;

typedef struct custosObjACS {
    size_t        perm_cnts[CUS_OBJPERM_MAX];
    custosAttr_t* perm_vals[CUS_OBJPERM_MAX];
} custsObjACS_t;

typedef struct custosObjACSReq {
    bool            echo;
    custosObjACS_t* acs;
} custoObjACSReq_t;

typedef struct custosObjACSRes {
    custosACSStatus_t status;
    bool              echo;
    custosObjACS_t*   acs;
} custoObjACSRes_t;

typedef struct custosReq {
    char*              target;
    size_t             num_attrs;
    custosAttrReq_t*   attrs;
    size_t             num_keys;
    custosKeyReq_t*    keys;
    size_t             num_acss;
    custosObjACSReq_t* acss;
} custosReq_t;

typedef struct custosRes {
    custosResStatus_t  status;
    size_t             num_attrs;
    custosAttrRes_t*   attrs;
    size_t             num_keys;
    custosKeyRes_t*    keys;
    size_t             num_acss;
    custosObjACSRes_t* acss;
} custosRes_t;


/* custosAttr Functions */
extern custosAttr_t* custos_createAttr(const custosAttrClass_t class,
                                       const custosAttrType_t type,
                                       const size_t size, const uint8_t* val);
extern int custos_destroyAttr(custosAttr_t** attrp);
extern custosAttr_t* custos_duplicateAttr(const custosAttr_t* attr, bool echo);
extern int custos_updateAttr(custosAttr_t* attr,
                             const custosAttrClass_t class,
                             const custosAttrType_t type,
                             const size_t size, const uint8_t* val);

extern const char* custos_AttrClassToStr(const custosAttrClass_t class);
extern custosAttrClass_t custos_StrToAttrClass(const char* str);
extern const char* custos_AttrTypeToStr(const custosAttrClass_t class,
                                        const custosAttrType_t type);
extern custosAttrType_t custos_StrToAttrType(const custosAttrClass_t class,
                                             const char* str);

/* custosKey Functions */
extern custosKey_t* custos_createKey(const uuid_t uuid,
                                     const uint64_t revision,
                                     const size_t size, const uint8_t* val);
extern int custos_destroyKey(custosKey_t** keyp);
extern custosKey_t* custos_duplicateKey(const custosKey_t* key, bool echo);
extern int custos_updateKey(custosKey_t* key,
                            const uuid_t uuid,
                            const uint64_t revision,
                            const size_t size, const uint8_t* val);

/* custosObjACS Functions */
extern custosObjACS_t* custos_createObjACS();
extern int custos_destroyObjACS(custosObjACS_t** acsp);
extern custosObjACS_t* custos_duplicateObjACS(const custosObjACS_t* acs, bool echo);
extern int custos_updateObjACSAppendAttr(custosObjACS_t* acs,
                                         const custosObjPerm_t perm,
                                         custosAttr_t* attr);

extern const char* custos_ObjPermToStr(const custosObjPerm_t perm);
extern custosObjPerm_t custos_StrToObjPerm(const char* str);

/* custosAttrReq Functions */
extern custosAttrReq_t* custos_createAttrReq(const bool echo);
extern int custos_destroyAttrReq(custosAttrReq_t** attrreqp);
extern int custos_updateAttrReqAddAttr(custosAttrReq_t* attrreq,
                                       custosAttr_t* attr);

/* custosKeyReq Functions */
extern custosKeyReq_t* custos_createKeyReq(const bool echo);
extern int custos_destroyKeyReq(custosKeyReq_t** keyreqp);
extern int custos_updateKeyReqAddKey(custosKeyReq_t* keyreq,
                                     custosKey_t* key);

/* custosObjACSReq Functions */
extern custosObjACSReq_t* custos_createObjACSReq(const bool echo);
extern int custos_destroyObjACSReq(custosObjACSReq_t** acsreqp);
extern int custos_updateObjACSReqAddACS(custosObjACSReq_t* acsreq,
                                        custosObjACS_t* acs);

/* custosAttrRes Functions */
extern custosAttrRes_t* custos_createAttrRes(const custosAttrStatus_t status,
                                             const bool echo,
                                             const size_t res_size,
                                             const uint8_t* res_value);
extern int custos_destroyAttrRes(custosAttrRes_t** attrresp);
extern int custos_updateAttrResAddAttr(custosAttrRes_t* attrres,
                                       custosAttr_t* attr);

extern const char* custos_AttrStatusToStr(const custosAttrStatus_t status);
extern custosAttrStatus_t custos_StrToAttrStatus(const char* str);

/* custosKeyRes Functions */
extern custosKeyRes_t* custos_createKeyRes(const custosKeyStatus_t status,
                                           const bool echo);
extern int custos_destroyKeyRes(custosKeyRes_t** keyresp);
extern int custos_updateKeyResAddKey(custosKeyRes_t* keyres,
                                     custosKey_t* key);

extern const char* custos_KeyStatusToStr(const custosKeyStatus_t status);
extern custosKeyStatus_t custos_StrToKeyStatus(const char* str);

/* custosObjACSRes Functions */
extern custosKeyRes_t* custos_createObjACSRes(const custosACSStatus_t status,
                                              const bool echo);
extern int custos_destroyObjACSRes(custosObjACSRes_t** acsresp);
extern int custos_updateObjACSResAddACS(custosObjACSRes_t* acsres,
                                        custosObjACS_t* acs);

extern const char* custos_ACSStatusToStr(const custosACSStatus_t status);
extern custosKeyStatus_t custos_StrToACSStatus(const char* str);

/* custosReq Functions */
extern custosReq_t* custos_createReq(const char* target);
extern int custos_destroyReq(custosReq_t** reqp);
extern int custos_updateReqAddAttrReq(custosReq_t* req,
                                      custosAttrReq_t* attrreq);
extern int custos_updateReqAddKeyReq(custosReq_t* req,
                                     custosKeyReq_t* keyreq);
extern int custos_updateReqAddObjACSReq(custosReq_t* req,
                                        custosObjACSReq_t* acsreq);

/* custosRes Functions */
extern custosRes_t* custos_getRes(const custosReq_t* req,
                                  const custosOp_t op,
                                  const uuid_t group);
extern int custos_destroyRes(custosRes_t** resp);

extern const char* custos_ResStatusToStr(const custosResStatus_t status);
extern custosResStatus_t custos_StrToResStatus(const char* str);

/* JSON */
extern json_object* custos_AttrToJson(const custosAttr_t* attr);
extern json_object* custos_KeyToJson(const custosKey_t* key);
extern json_object* custos_ObjACSToJson(const custosObjACS_t* acs);

extern json_object* custos_AttrReqToJson(const custosAttrReq_t* attrreq);
extern json_object* custos_KeyReqToJson(const custosKeyReq_t* keyreq);
extern json_object* custos_ObjACSReqToJson(const custosObjACSReq_t* acsreq);

extern json_object* custos_ReqToJson(const custosReq_t* req);

extern custosAttr_t* custos_JsonToAttr(json_object* attrjson);
extern custosKey_t* custos_JsonToKey(json_object* keyjson);
extern custosObjACS_t* custos_JsonToObjACS(json_object* acsjson);

extern custosAttrRes_t* custos_JsonToAttrRes(json_object* attrresjson);
extern custosKeyRes_t* custos_JsonToKeyRes(json_object* keyresjson);
extern custosObjACSRes_t* custos_JsonToObjACSRes(json_object* acsresjson);

extern custosRes_t* custos_JsonToRes(json_object* resjson);

#endif
