/* PRIME.H - header file for PRIME.C
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

int GeneratePrime PROTO_LIST
  ((NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int,
    R_RANDOM_STRUCT *));
