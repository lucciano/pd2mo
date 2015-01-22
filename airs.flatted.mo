model Pd2Model
  parameter Real VecInt_1_p[5] = {0,1e-06,0.001,20.4648,200};
  constant Integer VecInt_1_N = 200;
  parameter Real VecInt_1_x0 = 20.4648;
  Real VecInt_1_u[VecInt_1_N];
  Real VecInt_1_y[VecInt_1_N];
  constant Real Scalar2Vector_2_p[2] = {(-1),200};
  constant Integer Scalar2Vector_2_N = integer(200);
  parameter Integer Scalar2Vector_2_Index = integer((-1));
  Real Scalar2Vector_2_u;
  Real Scalar2Vector_2_y[Scalar2Vector_2_N];
  parameter Real Vec2Scalar_3_p[2] = {0,200};
  parameter Integer Vec2Scalar_3_Index = 0+1;
  constant Integer Vec2Scalar_3_N = 200;
  Real Vec2Scalar_3_u[Vec2Scalar_3_N];
  Real Vec2Scalar_3_y;
  parameter Real vector_sum_4_p[2] = {(-0.000357109),200};
  constant Integer vector_sum_4_N = 200;
  Real vector_sum_4_u[vector_sum_4_N];
  Real vector_sum_4_y;
  Real vector_sum_4_K = (-0.000357109);
  constant Real hysteretic_vec_5_p[5] = {(-0.5),0.5,(-14.498),0,200};
  parameter Real hysteretic_vec_5_xl = (-0.5);
  parameter Real hysteretic_vec_5_xu = 0.5;
  parameter Real hysteretic_vec_5_yl = (-14.498);
  parameter Real hysteretic_vec_5_yu = 0;
  constant Integer hysteretic_vec_5_N = integer(200);
  Real hysteretic_vec_5_u[hysteretic_vec_5_N];
  Real hysteretic_vec_5_y[hysteretic_vec_5_N];
  discrete Real hysteretic_vec_5_state[hysteretic_vec_5_N];
  parameter Real VectorSum_6_p[10] = {1,(-1),0,0,0,0,0,0,2,200};
  constant Integer VectorSum_6_N = 200;
  constant Integer VectorSum_6_nin = 2;
  parameter Real VectorSum_6_w[VectorSum_6_nin] = VectorSum_6_p[1:VectorSum_6_nin];
  Real VectorSum_6_u[VectorSum_6_N,VectorSum_6_nin];
  Real VectorSum_6_y[VectorSum_6_N];
  parameter Real VectorSum_7_p[10] = {0.000844084,0.000844084,0.00157873,(-0.000844084),0,0,0,0,3,200};
  constant Integer VectorSum_7_N = 200;
  constant Integer VectorSum_7_nin = 3;
  parameter Real VectorSum_7_w[VectorSum_7_nin] = VectorSum_7_p[1:VectorSum_7_nin];
  Real VectorSum_7_u[VectorSum_7_N,VectorSum_7_nin];
  Real VectorSum_7_y[VectorSum_7_N];
  parameter Real Constant_8_k = 1;
  Real Constant_8_y;
  constant Real Scalar2Vector_9_p[2] = {(-1),200};
  constant Integer Scalar2Vector_9_N = integer(200);
  parameter Integer Scalar2Vector_9_Index = integer((-1));
  Real Scalar2Vector_9_u;
  Real Scalar2Vector_9_y[Scalar2Vector_9_N];
  constant Real pulse_sci_11_p[4] = {20,0.5,1000,2000};
  parameter Real pulse_sci_11_low = 20;
  parameter Real pulse_sci_11_amplitude = 0.5;
  parameter Real pulse_sci_11_ti = 1000;
  parameter Real pulse_sci_11_tf = 2000;
  Real pulse_sci_11_d(start = pulse_sci_11_low);
  Real pulse_sci_11_y;
  initial equation
    for VecInt_1_i in 1:VecInt_1_N loop
      VecInt_1_y[VecInt_1_i] = VecInt_1_x0;
    end for;
  algorithm
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      when hysteretic_vec_5_u[hysteretic_vec_5_i]>hysteretic_vec_5_xu then
        hysteretic_vec_5_state[hysteretic_vec_5_i]:=hysteretic_vec_5_yu;
      end when;
    end for;
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      when hysteretic_vec_5_u[hysteretic_vec_5_N]<hysteretic_vec_5_xl then
        hysteretic_vec_5_state[hysteretic_vec_5_i]:=hysteretic_vec_5_yl;
      end when;
    end for;
    when time>pulse_sci_11_ti then
      pulse_sci_11_d:=pulse_sci_11_low+pulse_sci_11_amplitude;
    end when;
    when time>pulse_sci_11_tf then
      pulse_sci_11_d:=pulse_sci_11_low;
    end when;
  equation
    for VecInt_1_i in 1:VecInt_1_N loop
      der(VecInt_1_y[VecInt_1_i]) = VecInt_1_u[VecInt_1_i];
    end for;
    for Scalar2Vector_2_i in 1:Scalar2Vector_2_N loop
      Scalar2Vector_2_y[Scalar2Vector_2_i] = Scalar2Vector_2_u;
    end for;
    Vec2Scalar_3_y = Vec2Scalar_3_u[Vec2Scalar_3_Index];
    vector_sum_4_y = vector_sum_4_K*sum(vector_sum_4_u[:]);
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      hysteretic_vec_5_y[hysteretic_vec_5_i] = hysteretic_vec_5_state[hysteretic_vec_5_i];
    end for;
    for VectorSum_6_i in 1:VectorSum_6_N loop
      VectorSum_6_y[VectorSum_6_i] = VectorSum_6_u[VectorSum_6_i,1:VectorSum_6_nin]*VectorSum_6_w;
    end for;
    for VectorSum_7_i in 1:VectorSum_7_N loop
      VectorSum_7_y[VectorSum_7_i] = VectorSum_7_u[VectorSum_7_i,1:VectorSum_7_nin]*VectorSum_7_w;
    end for;
    Constant_8_y = Constant_8_k;
    for Scalar2Vector_9_i in 1:Scalar2Vector_9_N loop
      Scalar2Vector_9_y[Scalar2Vector_9_i] = Scalar2Vector_9_u;
    end for;
    pulse_sci_11_y = pulse_sci_11_d;
    for i in 1:VecInt_1_N loop
      Vec2Scalar_3_u[i] = VecInt_1_y[i];
    end for;
    for i in 1:VecInt_1_N loop
      VectorSum_6_u[i,2] = VecInt_1_y[i];
    end for;
    for i in 1:VectorSum_7_N loop
      VecInt_1_u[i] = VectorSum_7_y[i];
    end for;
    for i in 1:VecInt_1_N loop
      VectorSum_7_u[i,3] = VecInt_1_y[i];
    end for;
    Scalar2Vector_9_u = Constant_8_y;
    Scalar2Vector_2_u = pulse_sci_11_y;
end Pd2Model;

