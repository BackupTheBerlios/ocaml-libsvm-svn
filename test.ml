module Test =
struct
  type data = (float, Bigarray.float64_elt, Bigarray.fortran_layout) Bigarray.Array2.t
  type testrecord = { a:int; b:int }
  type some_var = Hello | There
  type some_p
  external mytest : unit -> int = "mytest"
  external mydouble : data -> unit = "mydouble"
  external myretrec : unit -> testrecord = "myretrec"
  external dismantle_variant : some_var -> (int * int) = "dismantle_variant"
  external dynalloc : unit -> some_p = "dynalloc"
  external dynfree : some_p -> unit = "dynfree"
  let say_abc = "abc"
end
;;
