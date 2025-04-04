#include "builder.h"
#include"heron.h"

heron zero;

class place_ptr32 {
public:
	int _ptrs[32];
	int s_x, s_y, dop;

	place_ptr32(int size_x, int size_y, char _dop){
		if (_dop > 5)dop = 5;
		else dop = _dop;
		s_x = (size_x + 2 * dop);
		s_y = (size_y + 2 * dop);
	}

	void zdvid_rite(int n) {
		for (int i = 0; i < 32; i++) {
			_ptrs[i] += n;
		}
	}
	void zdvig_down(int n) {
		for (int i = 0; i < 32; i++) {
			_ptrs[i] += s_x*n;
		}
	}
	void set(int index) {				 
		int i = 0;												 
		for (i = 0; i < 4; i++) {								 
			_ptrs[i] = index + i + 1;					      //index |
		}													  //   --  #### 
		for (i = 0; i < 4; i++) {								   // ######
			for (int j = 0; j < 6; j++) {						   // ######
				_ptrs[6 * i + 4] = index + (i + 1)*s_x + j;        // ######
			}													   // ######
		}														   //  #### 
		for (i=0; i < 4; i++) {
			_ptrs[i + 28] = index + i + 1 + 5 * s_x;
		}
	}
	
	heron** to_ptrs(heron*list,heron* if_null){
		heron** ptr = (heron**)malloc(sizeof(void*) * 32);
		for (int i = 0; i < 32; i++) {
			int n = _ptrs[i] - dop*s_x;
			if (n<0|| n%s_x-dop<0 || n%s_x>s_x-dop )
				ptr[i] = if_null;
			else {
				ptr[i] = &list[  ( (n / s_x)/*nomer ctroki*/ * (s_x - 2 * dop) + (n%s_x - dop)/*nomer stolbza*/ )  ];
			}
		}
		return ptr;
	}

};

float* collapc_link32(heron * from_where, int size_fx, int size_fy, heron * where_to, int size_tx, int size_ty) {
	place_ptr32 matr(size_fx, size_fy, 4);// neobyazatelno 4
	matr.set(0);
	// polozhenie matricy i kak cdvigat
	float iter_x = 0, nackolko_x = (float)(matr.dop + size_fx - 1) / (float)size_tx;
	float iter_y = 0, nackolko_y = (float)(matr.dop + size_fy - 1) / (float)size_ty;
	// weights list
	float** weights = (float**)malloc(sizeof(float*));
	*weights = (float*)malloc(sizeof(float) * 32);
	// zadat vesa, esly nado

	int k = 1;//metrica dvigaetcya zmeykoy
	for (int i = 0; i < size_ty; i++) {
		for (int j = 0; j < size_tx; j++) {
			// links create
			heron** ukhfd = matr.to_ptrs(from_where, &zero);
			where_to[i*size_tx + j].create_links32(hrestructer32(ukhfd, 32), weights, 32);

			// metrica give
			matr.zdvid_rite((int)(iter_x + nackolko_x*(float)k) - (int)iter_x);
			iter_x = iter_x + nackolko_x * (float)k;
		}
		k = k*(-1);// izmenenie napravleniya dvizheniya
		// metrica give to bak
		matr.zdvid_rite((int)(iter_x + nackolko_x*(float)k) - (int)iter_x);
		iter_x = iter_x + nackolko_x * (float)k;
		// metrica give down
		matr.zdvig_down((int)(iter_y + nackolko_y) - (int)iter_y);
		iter_y = iter_y + nackolko_y;

	}
	auto a = *weights;// delete lishniy ptr
	free(weights);
	return(a);
}


// will deleted starts list
float ** frestructer32(float* &start_list, int len) {
	float**result = (float**)malloc(sizeof(float*) * ((len + 31) / 32)); 
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num = len - i * 32) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	free( start_list);
	start_list = 0;
	return result;
}

// will deleted starts list
heron*** hrestructer32(heron** &start_list, int len) {
	heron***result = (heron***)malloc(sizeof(heron**)*((len + 31) / 32));
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (heron**)malloc(sizeof(heron*)*32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num= len - i*32) {
		result[i] = (heron**)malloc(sizeof(heron*) * end_num);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	free(start_list);
	start_list = 0;
	return result;
}

// will not deleted starts list
float ** __frestructer32(float* start_list, int len) {
	float**result = (float**)malloc(sizeof(float*) * ((len + 31) / 32));
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num = len - i * 32) {
		result[i] = (float*)malloc(sizeof(float) * 32);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	return result;
}

// will not deleted starts list
heron*** __hrestructer32(heron** start_list, int len) {
	heron***result = (heron***)malloc(sizeof(heron**)*((len + 31) / 32));
	int i;
	for (i = 0; i < len / 32; i++) {
		result[i] = (heron**)malloc(sizeof(heron*) * 32);
		for (int j = 0; j < 32; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	if (int end_num = len - i * 32) {
		result[i] = (heron**)malloc(sizeof(heron*) * end_num);
		for (int j = 0; j <end_num; j++) {
			result[i][j] = start_list[i * 32 + j];
		}
	}
	return result;
}

void linking_a(heron * from_where, int size_fr, heron * where_to, int size_to) {
	float* weights = 0;
	heron** ptr = (heron**)malloc(sizeof(heron*) * size_fr);
	for (int i = 0; i < size_fr; i++) {
		ptr[i] = &from_where[i];
	}

	heron*** ptr2 = hrestructer32(ptr, size_fr);

	for (int i = 0; i < size_to; i++) {

		weights = (float*)malloc(sizeof(float) * size_fr);
		for (int j = 0; j < size_fr; j++) {
			weights[j] = 0;// ((float)rand() - 20) / ((float)1000);
		}
		where_to[i].create_links32(ptr2, frestructer32(weights, size_fr), size_fr);

	}
}

void linking_b(heron ** from_where, int size_fr, heron ** where_to, int size_to) {

	float* weights = 0;
	heron*** ptr2 = __hrestructer32(from_where, size_fr);
	for (int i = 0; i < size_to; i++) {

		weights = (float*)malloc(sizeof(float) * size_fr);
		for (int j = 0; j < size_fr; j++) {
			weights[j] = 0;// ((float)rand() - 200) / ((float)20000);
		}

		where_to[i]->create_links32(ptr2, frestructer32( weights,size_fr), size_fr);

	}
}

// luchsh ispolzovat etot
void linking_c(heron *** from_where, int size_fr, heron ** where_to, int size_to) {
	float* weights = 0;
	for (int i = 0; i < size_to; i++) {
		weights = (float*)malloc(sizeof(float) * size_fr);
		for (int j = 0; j < size_fr; j++) {
			weights[j] = 0;// ((float)rand() - 200) / ((float)1000);
		}
		where_to[i]->create_links32(from_where, frestructer32(weights, size_fr), size_fr);
	}
}

heron**copy(heron** start, int len){
	heron** res = (heron**)malloc(sizeof(heron*)*len);
	for (int i = 0; i < len; i++) {
		res[i] = start[i];
	}
	return res;
}

/*inline heron** opredelenie_ptrs(int pokrytie, heron * from_where, int size_fx, int size_fy) {
	heron**ptrs = nullptr;
	switch (pokrytie){
	case(32)://6x6-4
		place_ptr32 matr();



	case(64)://8x8
		//ptrs = (heron**)malloc(sizeof(void*) * 64);


	case(96)://10x10-4
		//ptrs = (heron**)malloc(sizeof(void*) * 96);

	default:
		throw("problem");
	}

}
*/
//pokrytie= 32 or 64 or 96
float* collapc_link(int pokrytie, heron * from_where, int size_fx, int size_fy, heron * where_to, int size_tx, int size_ty) {
	if (size_fx*size_fy*size_tx*size_ty == 0)throw("bred\n");
	if (size_fy<size_ty || size_fx<size_tx)throw("bred\n");
	//пока нет?

	//ron**ptrs = nullptr;
	switch (pokrytie) {
	case(32)://6x6-4
		
		return collapc_link32(from_where, size_fx, size_fy, where_to, size_tx, size_ty);

	case(64)://8x8
			 //ptrs = (heron**)malloc(sizeof(void*) * 64);


	case(96)://10x10-4
			 //ptrs = (heron**)malloc(sizeof(void*) * 96);

	default:
		throw("problem");
	}



	return nullptr;
}