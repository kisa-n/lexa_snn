#pragma once
#include"externs.h"
class heron;

float ** restructer_copyf(float *start_list, int len);
heron*** restructer_copyh(heron**start_list, int len);

float** collapc_link(int pokrytie, heron * from_where, int size_fx, int size_fy, heron * where_to, int size_tx, int size_ty);

//it is impractical to create links in a number(= size_fr) that is not a multiple of 32
void linking(heron* from_where, int size_f, heron* where_to, int size_t);

