#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/custom.h>
#include <caml/bigarray.h>

CAMLprim mytest(value unit){
  return Val_long(42);
}

void double_c(double *data, int dimx, int dimy){
  int i,j;
  for(i=0; i<dimx*dimy; ++i)
    data[i] *= 2;
/*   for(i=0; i<dimx; ++i) */
/*     for(j=0; j<dimy; ++j) */
/*       data[i*dimx+j] *= 2; */
}

CAMLprim mydouble(value data){
  int dimx = Bigarray_val(data)->dim[0];
  int dimy = Bigarray_val(data)->dim[1];
  double_c(Data_bigarray_val(data),dimx,dimy);
  return Val_unit;
}

CAMLprim value myretrec(value unit){
  CAMLparam0 ();
  CAMLlocal1 (result);
  result = alloc_tuple(2);
  Store_field (result, 0, Val_int(42));
  Store_field (result, 1, Val_int(7));
  CAMLreturn (result);
}

CAMLprim value dynalloc(value unit){
  CAMLparam1 (unit);
  CAMLlocal1 (result);
  double *dmem = (double *) malloc(3*sizeof(double));
  result = alloc(1,Abstract_tag);
  Field(result, 0) = dmem;
  CAMLreturn (result);
}

CAMLprim value dynfree(value v){
  CAMLparam1 (v);
  free(Field(v,0));
  CAMLreturn0;
}

CAMLprim value dismantle_variant(value v){
  CAMLparam1 (v);
  CAMLlocal1 (result);
  result = alloc_tuple(2);
/*   if(Is_long(v)){ */
  Store_field (result, 0, Val_long(Long_val(v)));
  Store_field (result, 1, Val_long(Long_val(v)));
/*   } */
/*   else{ */
/*     Store_field (result, 0, Val_long(Field(v,0))); */
/*     Store_field (result, 1, Val_long(Field(v,0))); */
/*   } */
  CAMLreturn (result);
}

/* CAMLprim value mybigarr(value unit){ */
/*   CAMLparam0 (); */
/*   CAMLlocal1 (result); */
/*   result = alloc_bigarray(| BIGARRAY_C_LAYOUT, 2, my_c_array,  */
/*   CAMLreturn (result); */
/* } */
