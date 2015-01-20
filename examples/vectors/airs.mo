model Pd2Model
  parameter Real VecInt_1_p[5] = {0, 1e-06, 0.001, 18.4302, 1};
  constant Integer VecInt_1_N = 1;
  parameter Real VecInt_1_x0 = 18.4302;
  Real VecInt_1_u[VecInt_1_N];
  Real VecInt_1_y[VecInt_1_N];
  constant Real Scalar2Vector_3_p[2] = {-1, 1};
  constant Integer Scalar2Vector_3_N = integer(Scalar2Vector_3_p[2]);
  parameter Integer Scalar2Vector_3_Index = -1;
  Real Scalar2Vector_3_u;
  Real Scalar2Vector_3_y[Scalar2Vector_3_N];
  constant Real Vec2Scalar_4_p[2] = {0, 1};
  constant Integer Vec2Scalar_4_Index = 0 + 1;
  constant Integer Vec2Scalar_4_N = integer(Vec2Scalar_4_p[2]);
  Real Vec2Scalar_4_u[Vec2Scalar_4_N];
  Real Vec2Scalar_4_y;
  parameter Real vector_sum_5_p[2] = {-0.0725239, 1};
  constant Integer vector_sum_5_N = 1;
  /************/
  Real vector_sum_5_u[vector_sum_5_N] = {1.0};
  /*******************/
  Real vector_sum_5_y;
  Real vector_sum_5_K = -0.0725239;
  constant Real hysteretic_vec_6_p[5] = {-0.5, 0.5, -13.1602, 0, 1};
  parameter Real hysteretic_vec_6_xl = -0.5;
  parameter Real hysteretic_vec_6_xu = 0.5;
  parameter Real hysteretic_vec_6_yl = -13.1602;
  parameter Real hysteretic_vec_6_yu = 0;
  constant Integer hysteretic_vec_6_N = integer(1);
  /*********/
  Real hysteretic_vec_6_u[hysteretic_vec_6_N] = {1};
  /*********/
  Real hysteretic_vec_6_y[hysteretic_vec_6_N];
  discrete Real hysteretic_vec_6_state[hysteretic_vec_6_N];
  parameter Real VectorSum_7_p[10] = {1, -1, 0, 0, 0, 0, 0, 0, 2, 1};
  constant Integer VectorSum_7_N = 1;
  constant Integer VectorSum_7_nin = 2;
  parameter Real VectorSum_7_w[VectorSum_7_nin] = VectorSum_7_p[1:VectorSum_7_nin];
  Real VectorSum_7_u[VectorSum_7_N, VectorSum_7_nin];
  Real VectorSum_7_y[VectorSum_7_N];
  parameter Real VectorSum_8_p[10] = {0.000750286, 0.000750286, 0.0016399, -0.000750286, 0, 0, 0, 0, 4, 1};
  constant Integer VectorSum_8_N = 1;
  constant Integer VectorSum_8_nin = 2;
  parameter Real VectorSum_8_w[VectorSum_8_nin] = VectorSum_8_p[1:VectorSum_8_nin];
  Real VectorSum_8_u[VectorSum_8_N, VectorSum_8_nin];
  Real VectorSum_8_y[VectorSum_8_N];
  parameter Real Constant_9_k = 1;
  Real Constant_9_y;
  constant Real Scalar2Vector_10_p[2] = {-1, 1};
  constant Integer Scalar2Vector_10_N = integer(Scalar2Vector_10_p[2]);
  parameter Integer Scalar2Vector_10_Index = -1;
  Real Scalar2Vector_10_u;
  Real Scalar2Vector_10_y[Scalar2Vector_10_N];
  constant Real pulse_sci_12_p[4] = {20, 0.5, 1000, 2000};
  parameter Real pulse_sci_12_low = 20;
  parameter Real pulse_sci_12_amplitude = 0.5;
  parameter Real pulse_sci_12_ti = 1000;
  parameter Real pulse_sci_12_tf = 2000;
  Real pulse_sci_12_d(start = pulse_sci_12_low);
  Real pulse_sci_12_y;
initial equation
  for VecInt_1_i in 1:VecInt_1_N loop
    VecInt_1_y[VecInt_1_i] = VecInt_1_x0;
  end for;
algorithm
  for hysteretic_vec_6_i in 1:hysteretic_vec_6_N loop
    when hysteretic_vec_6_u[hysteretic_vec_6_i] > hysteretic_vec_6_xu then
      hysteretic_vec_6_state[hysteretic_vec_6_i] := hysteretic_vec_6_yu;
    end when;
  end for;
  for hysteretic_vec_6_i in 1:hysteretic_vec_6_N loop
    when hysteretic_vec_6_u[hysteretic_vec_6_N] < hysteretic_vec_6_xl then
      hysteretic_vec_6_state[hysteretic_vec_6_i] := hysteretic_vec_6_yl;
    end when;
  end for;
  when time > pulse_sci_12_ti then
    pulse_sci_12_d := pulse_sci_12_low + pulse_sci_12_amplitude;
  end when;
  when time > pulse_sci_12_tf then
    pulse_sci_12_d := pulse_sci_12_low;
  end when;
equation
  for VecInt_1_i in 1:VecInt_1_N loop
    der(VecInt_1_y[VecInt_1_i]) = VecInt_1_u[VecInt_1_i];
  end for;
  for Scalar2Vector_3_i in 1:Scalar2Vector_3_N loop
    Scalar2Vector_3_y[Scalar2Vector_3_i] = if Scalar2Vector_3_Index + 1 == Scalar2Vector_3_i or Scalar2Vector_3_Index == (-1) then Scalar2Vector_3_u else 0;
  end for;
  Vec2Scalar_4_y = Vec2Scalar_4_u[Vec2Scalar_4_Index];
  vector_sum_5_y = vector_sum_5_K * sum(vector_sum_5_u[:]);
  for hysteretic_vec_6_i in 1:hysteretic_vec_6_N loop
    hysteretic_vec_6_y[hysteretic_vec_6_i] = hysteretic_vec_6_state[hysteretic_vec_6_i];
  end for;
  for VectorSum_7_i in 1:VectorSum_7_N loop
    VectorSum_7_y[VectorSum_7_i] = VectorSum_7_u[VectorSum_7_i, 1:VectorSum_7_nin] * VectorSum_7_w;
  end for;
  for VectorSum_8_i in 1:VectorSum_8_N loop
    VectorSum_8_y[VectorSum_8_i] = VectorSum_8_u[VectorSum_8_i, 1:VectorSum_8_nin] * VectorSum_8_w;
  end for;
  Constant_9_y = Constant_9_k;
  for Scalar2Vector_10_i in 1:Scalar2Vector_10_N loop
    Scalar2Vector_10_y[Scalar2Vector_10_i] = if Scalar2Vector_10_Index + 1 == Scalar2Vector_10_i or Scalar2Vector_10_Index == (-1) then Scalar2Vector_10_u else 0;
  end for;
  pulse_sci_12_y = pulse_sci_12_d;
  Scalar2Vector_3_u = pulse_sci_12_y;
  for i in 1:VectorSum_8_N loop
    VecInt_1_u[i] = VectorSum_8_y[i];
  end for;
  for i in 1:Scalar2Vector_3_N loop
    VectorSum_7_u[i, 1] = Scalar2Vector_3_y[i];
  end for;
  Scalar2Vector_10_u = Constant_9_y;
  for i in 1:Scalar2Vector_10_N loop
    VectorSum_8_u[i, 1] = Scalar2Vector_10_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    Vec2Scalar_4_u[i] = VecInt_1_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    VectorSum_8_u[i, 4] = VecInt_1_y[i];
  end for;
  for i in 1:VecInt_1_N loop
    VectorSum_7_u[i, 2] = VecInt_1_y[i];
  end for;
end Pd2Model;
