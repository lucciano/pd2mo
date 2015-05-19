model adr
  parameter Real VecInt_1_p[5] = {0,0.0009,0.001,0,50};
  constant Integer VecInt_1_N = 50;
  parameter Real VecInt_1_x0 = 0;
  Real VecInt_1_u_1[50];
  Real VecInt_1_y_1[50];
  constant Real IndexShift_2_p[2] = {1,50};
  constant Integer IndexShift_2_Shift = integer(1);
  constant Integer IndexShift_2_N = integer(50);
  Real IndexShift_2_u_1[IndexShift_2_N];
  Real IndexShift_2_y_1[IndexShift_2_N];
  constant Real Scalar2Vector_3_p[2] = {0,50};
  constant Integer Scalar2Vector_3_N = integer(50);
  parameter Integer Scalar2Vector_3_Index = integer(0);
  Real Scalar2Vector_3_u[1];
  Real Scalar2Vector_3_y_1[Scalar2Vector_3_N];
  parameter Real Constant_4_p[1] = {1};
  parameter Real Constant_4_k = 1;
  Real Constant_4_y[1];
  parameter Real Vec2Scalar_5_p[2] = {0,50};
  parameter Integer Vec2Scalar_5_Index = 1;
  constant Integer Vec2Scalar_5_N = 50;
  Real Vec2Scalar_5_u_1[50];
  Real Vec2Scalar_5_y[1];
  constant Real vector_pow2_6_p[1] = {50};
  constant Integer vector_pow2_6_N = integer(50);
  Real vector_pow2_6_u_1[vector_pow2_6_N];
  Real vector_pow2_6_y_1[vector_pow2_6_N];
  parameter Real qss_multiplier_vec_7_p[2] = {2,50};
  constant Integer qss_multiplier_vec_7_N = 50;
  constant Integer qss_multiplier_vec_7_nin = 2;
  Real qss_multiplier_vec_7_u_1[50],qss_multiplier_vec_7_u_2[50];
  Real qss_multiplier_vec_7_y_1[50];
  parameter Real VectorSum_8_p[10] = {1,(-1),0,0,0,0,0,0,2,50};
  constant Integer VectorSum_8_N = 50;
  constant Integer VectorSum_8_nin = 2;
  parameter Real VectorSum_8_w[2] = VectorSum_8_p[1:2];
  Real VectorSum_8_u_1[50],VectorSum_8_u_2[50];
  Real VectorSum_8_y_1[50];
  constant Real Scalar2Vector_9_p[2] = {(-1),50};
  constant Integer Scalar2Vector_9_N = integer(50);
  parameter Integer Scalar2Vector_9_Index = integer((-1));
  Real Scalar2Vector_9_u[1];
  Real Scalar2Vector_9_y_1[Scalar2Vector_9_N];
  parameter Real Constant_10_p[1] = {1};
  parameter Real Constant_10_k = 1;
  Real Constant_10_y[1];
  parameter Real Vec2Scalar_11_p[2] = {49,50};
  parameter Integer Vec2Scalar_11_Index = 50;
  constant Integer Vec2Scalar_11_N = 50;
  Real Vec2Scalar_11_u_1[50];
  Real Vec2Scalar_11_y[1];
  parameter Real VectorSum_12_p[10] = {5,(-5),5,1000,0,0,0,0,4,50};
  constant Integer VectorSum_12_N = 50;
  constant Integer VectorSum_12_nin = 4;
  parameter Real VectorSum_12_w[4] = VectorSum_12_p[1:4];
  Real VectorSum_12_u_1[50],VectorSum_12_u_2[50],VectorSum_12_u_3[50],VectorSum_12_u_4[50];
  Real VectorSum_12_y_1[50];
  initial algorithm
    for VecInt_1_i in 1:50 loop
      VecInt_1_y_1[VecInt_1_i]:=0;
    end for;
  equation
    for VecInt_1_i in 1:50 loop
      der(VecInt_1_y_1[VecInt_1_i]) = VecInt_1_u_1[VecInt_1_i];
    end for;
    for IndexShift_2_i in 1:IndexShift_2_N-IndexShift_2_Shift loop
      IndexShift_2_y_1[IndexShift_2_i+IndexShift_2_Shift] = IndexShift_2_u_1[IndexShift_2_i];
    end for;
    for IndexShift_2_i in 1:IndexShift_2_Shift loop
      IndexShift_2_y_1[IndexShift_2_i] = 0;
    end for;
    for Scalar2Vector_3_i in 1:Scalar2Vector_3_Index loop
      Scalar2Vector_3_y_1[Scalar2Vector_3_i] = 0;
    end for;
    Scalar2Vector_3_y_1[Scalar2Vector_3_Index+1] = Scalar2Vector_3_u[1];
    for Scalar2Vector_3_i in Scalar2Vector_3_Index+2:Scalar2Vector_3_N loop
      Scalar2Vector_3_y_1[Scalar2Vector_3_i] = 0;
    end for;
    Constant_4_y[1] = 1;
    Vec2Scalar_5_y[1] = Vec2Scalar_5_u_1[1];
    for vector_pow2_6_i in 1:vector_pow2_6_N loop
      vector_pow2_6_y_1[vector_pow2_6_i] = vector_pow2_6_u_1[vector_pow2_6_i]*vector_pow2_6_u_1[vector_pow2_6_i];
    end for;
    for qss_multiplier_vec_7_i in 1:50 loop
      qss_multiplier_vec_7_y_1[qss_multiplier_vec_7_i] = qss_multiplier_vec_7_u_1[qss_multiplier_vec_7_i]*qss_multiplier_vec_7_u_2[qss_multiplier_vec_7_i];
    end for;
    for VectorSum_8_i in 1:50 loop
      VectorSum_8_y_1[VectorSum_8_i] = VectorSum_8_u_1[VectorSum_8_i]*VectorSum_8_w[1]+VectorSum_8_u_2[VectorSum_8_i]*VectorSum_8_w[2];
    end for;
    for Scalar2Vector_9_i in 1:Scalar2Vector_9_N loop
      Scalar2Vector_9_y_1[Scalar2Vector_9_i] = Scalar2Vector_9_u[1];
    end for;
    Constant_10_y[1] = 1;
    Vec2Scalar_11_y[1] = Vec2Scalar_11_u_1[50];
    for VectorSum_12_i in 1:50 loop
      VectorSum_12_y_1[VectorSum_12_i] = VectorSum_12_u_1[VectorSum_12_i]*VectorSum_12_w[1]+VectorSum_12_u_2[VectorSum_12_i]*VectorSum_12_w[2]+VectorSum_12_u_3[VectorSum_12_i]*VectorSum_12_w[3]+VectorSum_12_u_4[VectorSum_12_i]*VectorSum_12_w[4];
    end for;
    for i in 1:50 loop
      IndexShift_2_u_1[i] = VecInt_1_y_1[i];
    end for;
    Scalar2Vector_3_u[1] = Constant_4_y[1];
    for i in 1:50 loop
      Vec2Scalar_5_u_1[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:50 loop
      vector_pow2_6_u_1[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:vector_pow2_6_N loop
      qss_multiplier_vec_7_u_2[i] = vector_pow2_6_y_1[i];
    end for;
    for i in 1:50 loop
      qss_multiplier_vec_7_u_1[i] = VectorSum_8_y_1[i];
    end for;
    for i in 1:50 loop
      VectorSum_8_u_2[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:Scalar2Vector_9_N loop
      VectorSum_8_u_1[i] = Scalar2Vector_9_y_1[i];
    end for;
    Scalar2Vector_9_u[1] = Constant_10_y[1];
    for i in 1:50 loop
      Vec2Scalar_11_u_1[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:IndexShift_2_N loop
      VectorSum_12_u_1[i] = IndexShift_2_y_1[i];
    end for;
    for i in 1:50 loop
      VecInt_1_u_1[i] = VectorSum_12_y_1[i];
    end for;
    for i in 1:Scalar2Vector_3_N loop
      VectorSum_12_u_3[i] = Scalar2Vector_3_y_1[i];
    end for;
    for i in 1:50 loop
      VectorSum_12_u_4[i] = qss_multiplier_vec_7_y_1[i];
    end for;
    for i in 1:50 loop
      VectorSum_12_u_2[i] = VecInt_1_y_1[i];
    end for;
end adr;

