/* ====================================================================
 * Copyright (c) 2001-2005 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */

#ifndef HEADER_GOST_ERR_H
# define HEADER_GOST_ERR_H

#ifdef  __cplusplus
extern "C" {
#endif

/* BEGIN ERROR CODES */
/*
 * The following lines are auto generated by the script mkerr.pl. Any changes
 * made after this point may be overwritten when the script is next run.
 */
void ERR_load_GOST_strings(void);
void ERR_unload_GOST_strings(void);
void ERR_GOST_error(int function, int reason, char *file, int line);
# define GOSTerr(f,r) ERR_GOST_error((f),(r),__FILE__,__LINE__)

/* Error codes for the GOST functions. */

/* Function codes. */
# define GOST_F_DECODE_GOST_ALGOR_PARAMS                  99
# define GOST_F_ENCODE_GOST_ALGOR_PARAMS                  100
# define GOST_F_FILL_GOST2001_PARAMS                      101
# define GOST_F_FILL_GOST94_PARAMS                        102
# define GOST_F_GET_ENCRYPTION_PARAMS                     103
# define GOST_F_GOST2001_COMPUTE_PUBLIC                   104
# define GOST_F_GOST2001_DO_SIGN                          105
# define GOST_F_GOST2001_DO_VERIFY                        106
# define GOST_F_GOST2001_KEYGEN                           107
# define GOST_F_GOST89_GET_ASN1_PARAMETERS                108
# define GOST_F_GOST89_SET_ASN1_PARAMETERS                109
# define GOST_F_GOST94_COMPUTE_PUBLIC                     110
# define GOST_F_GOST_CIPHER_CTL                           111
# define GOST_F_GOST_DO_SIGN                              112
# define GOST_F_GOST_DO_VERIFY                            113
# define GOST_F_GOST_IMIT_CTRL                            114
# define GOST_F_GOST_IMIT_FINAL                           140
# define GOST_F_GOST_IMIT_UPDATE                          115
# define GOST_F_GOST_SIGN_KEYGEN                          142
# define GOST_F_PARAM_COPY_GOST01                         116
# define GOST_F_PARAM_COPY_GOST94                         117
# define GOST_F_PKEY_GOST01CP_DECRYPT                     118
# define GOST_F_PKEY_GOST01CP_ENCRYPT                     119
# define GOST_F_PKEY_GOST01CP_KEYGEN                      120
# define GOST_F_PKEY_GOST01_PARAMGEN                      138
# define GOST_F_PKEY_GOST2001_DERIVE                      121
# define GOST_F_PKEY_GOST94CP_DECRYPT                     122
# define GOST_F_PKEY_GOST94CP_ENCRYPT                     123
# define GOST_F_PKEY_GOST94CP_KEYGEN                      124
# define GOST_F_PKEY_GOST94_PARAMGEN                      139
# define GOST_F_PKEY_GOST_CTRL                            125
# define GOST_F_PKEY_GOST_CTRL01_STR                      126
# define GOST_F_PKEY_GOST_CTRL94_STR                      127
# define GOST_F_PKEY_GOST_MAC_CTRL                        128
# define GOST_F_PKEY_GOST_MAC_CTRL_STR                    129
# define GOST_F_PKEY_GOST_MAC_KEYGEN                      130
# define GOST_F_PRINT_GOST_01                             131
# define GOST_F_PRIV_DECODE_GOST                          132
# define GOST_F_PUB_DECODE_GOST01                         133
# define GOST_F_PUB_DECODE_GOST94                         134
# define GOST_F_PUB_ENCODE_GOST01                         135
# define GOST_F_UNPACK_CC_SIGNATURE                       136
# define GOST_F_UNPACK_CP_SIGNATURE                       137

/* Reason codes. */
# define GOST_R_BAD_KEY_PARAMETERS_FORMAT                 99
# define GOST_R_BAD_PKEY_PARAMETERS_FORMAT                100
# define GOST_R_CANNOT_PACK_EPHEMERAL_KEY                 101
# define GOST_R_CTRL_CALL_FAILED                          132
# define GOST_R_ERROR_COMPUTING_SHARED_KEY                102
# define GOST_R_ERROR_PACKING_KEY_TRANSPORT_INFO          103
# define GOST_R_ERROR_PARSING_KEY_TRANSPORT_INFO          104
# define GOST_R_INCOMPATIBLE_ALGORITHMS                   105
# define GOST_R_INCOMPATIBLE_PEER_KEY                     131
# define GOST_R_INVALID_CIPHER_PARAMS                     106
# define GOST_R_INVALID_CIPHER_PARAM_OID                  107
# define GOST_R_INVALID_DIGEST_TYPE                       108
# define GOST_R_INVALID_GOST94_PARMSET                    109
# define GOST_R_INVALID_IV_LENGTH                         110
# define GOST_R_INVALID_MAC_KEY_LENGTH                    111
# define GOST_R_INVALID_PARAMSET                          112
# define GOST_R_KEY_IS_NOT_INITALIZED                     113
# define GOST_R_KEY_IS_NOT_INITIALIZED                    114
# define GOST_R_KEY_PARAMETERS_MISSING                    115
# define GOST_R_MAC_KEY_NOT_SET                           116
# define GOST_R_MALLOC_FAILURE                            117
# define GOST_R_NO_MEMORY                                 118
# define GOST_R_NO_PARAMETERS_SET                         119
# define GOST_R_NO_PEER_KEY                               120
# define GOST_R_NO_PRIVATE_PART_OF_NON_EPHEMERAL_KEYPAIR  121
# define GOST_R_PUBLIC_KEY_UNDEFINED                      122
# define GOST_R_RANDOM_GENERATOR_ERROR                    123
# define GOST_R_RANDOM_GENERATOR_FAILURE                  124
# define GOST_R_RANDOM_NUMBER_GENERATOR_FAILED            125
# define GOST_R_SIGNATURE_MISMATCH                        126
# define GOST_R_SIGNATURE_PARTS_GREATER_THAN_Q            127
# define GOST_R_UKM_NOT_SET                               128
# define GOST_R_UNSUPPORTED_CIPHER_CTL_COMMAND            129
# define GOST_R_UNSUPPORTED_PARAMETER_SET                 130

#ifdef  __cplusplus
}
#endif
#endif
