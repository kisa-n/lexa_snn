#pragma once
#include"externs.h"
class heron;


// will deleted starts list
float ** frestructer32(float* &start_list, int len);

// will deleted starts list
heron*** hrestructer32(heron** &start_list, int len);

// will not deleted starts list
float ** __frestructer32(float* start_list, int len);

// will not deleted starts list
heron*** __hrestructer32(heron** start_list, int len);

float* collapc_link(int pokrytie, heron * from_where, int size_fx, int size_fy, heron * where_to, int size_tx, int size_ty);

//it is impractical to create links in a number(= size_fr) that is not a multiple of 32
void linking_a(heron* from_where, int size_f, heron* where_to, int size_t);

void linking_b(heron ** from_where, int size_fr, heron ** where_to, int size_to);

// luchshe ipospolzovat etot
void linking_c(heron *** from_where, int size_fr, heron ** where_to, int size_to);

inline void linking_w(heron**from_where, float**weights, int size_fr, heron** where_to, int size_to) {
	heron***ptr2 = __hrestructer32(from_where, size_fr);

	for (int i = 0; i < size_to; i++) {
		where_to[i]->create_links32(ptr2, weights, size_fr);
	}
}


heron**copy(heron** start, int len);