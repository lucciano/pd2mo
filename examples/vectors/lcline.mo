model Pd2Model
  parameter Real VectorSum_3_p[10] = {1, -1, 0, 0, 0, 0, 0, 0, 2, 50};
  constant Integer VectorSum_3_N = 50;
  constant Integer VectorSum_3_nin = 2;
  parameter Real VectorSum_3_w[VectorSum_3_nin] = VectorSum_3_p[1:VectorSum_3_nin];
  Real VectorSum_3_u[VectorSum_3_N, VectorSum_3_nin];
  Real VectorSum_3_y[VectorSum_3_N];
equation
  for VectorSum_3_i in 1:VectorSum_3_N loop
    VectorSum_3_y[VectorSum_3_i] = VectorSum_3_u[VectorSum_3_i, 1:VectorSum_3_nin] * VectorSum_3_w;
  end for;
  for IndexShift_6_i in IndexShift_6_N + IndexShift_6_Shift + 1:IndexShift_6_N loop
    IndexShift_6_y[IndexShift_6_i] = 0;
  end for;
  for Scalar2Vector_7_i in 1:Scalar2Vector_7_Index loop
    Scalar2Vector_7_y[Scalar2Vector_7_i] = 0;
  end for;
  Scalar2Vector_7_y[Scalar2Vector_7_Index + 1] = Scalar2Vector_7_u;
  for Scalar2Vector_7_i in Scalar2Vector_7_Index + 2:Scalar2Vector_7_N loop
    Scalar2Vector_7_y[Scalar2Vector_7_i] = 0;
  end for;
  pulse_sci_8_y = pulse_sci_8_d;
  Vec2Scalar_10_y = Vec2Scalar_10_u[Vec2Scalar_10_Index];
  Vec2Scalar_11_y = Vec2Scalar_11_u[Vec2Scalar_11_Index];
  for i in 1:VectorSum_3_N loop
    VecInt_1_u[i] = VectorSum_3_y[i];
  end for;
  for i in 1:VecInt_2_N loop
    VectorSum_3_u[i, 1] = VecInt_2_y[i];
  end for;
  for i in 1:IndexShift_4_N loop
    VectorSum_3_u[i, 2] = IndexShift_4_y[i];
  end for;
  for i in 1:VecInt_2_N loop
    IndexShift_4_u[i] = VecInt_2_y[i];
  end for;
  for i in 1:VectorSum_5_N loop
    VecInt_2_u[i] = VectorSum_5_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    VectorSum_5_u[i, 3] = VecInt_1_y[i];
  end for;
  for i in 1:IndexShift_6_N loop
    VectorSum_5_u[i, 2] = IndexShift_6_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    IndexShift_6_u[i] = VecInt_1_y[i];
  end for;
  for i in 1:Scalar2Vector_7_N loop
    VectorSum_5_u[i, 1] = Scalar2Vector_7_y[i];
  end for;
  Scalar2Vector_7_u = pulse_sci_8_y;
  for i in 1:VecInt_1_N loop
    Vec2Scalar_10_u[i] = VecInt_1_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    Vec2Scalar_11_u[i] = VecInt_1_y[i];
  end for;
end Pd2Model;