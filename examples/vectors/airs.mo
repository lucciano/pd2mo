model Pd2Model
  parameter Real VecInt_1_p[5] = {0,1e-06,0.001,18.8453,200};
  constant Integer VecInt_1_N = 200;
  parameter Real VecInt_1_x0 = 18.8453;
  Real VecInt_1_u_1[200];
  Real VecInt_1_y_1[200];
  constant Real Scalar2Vector_2_p[2] = {(-1),200};
  constant Integer Scalar2Vector_2_N = integer(200);
  parameter Integer Scalar2Vector_2_Index = integer((-1));
  Real Scalar2Vector_2_u[1];
  Real Scalar2Vector_2_y_1[Scalar2Vector_2_N];
  parameter Real Vec2Scalar_3_p[2] = {0,200};
  parameter Integer Vec2Scalar_3_Index = 1;
  constant Integer Vec2Scalar_3_N = 200;
  Real Vec2Scalar_3_u_1[200];
  Real Vec2Scalar_3_y[1];
  parameter Real vector_sum_4_p[2] = {(-0.000356739),200};
  constant Integer vector_sum_4_N = 200;
  Real vector_sum_4_u_1[200];
  Real vector_sum_4_y[1];
  Real vector_sum_4_K = (-0.000356739);
  constant Real hysteretic_vec_5_p[5] = {(-0.5),0.5,(-13.0747),0,200};
  parameter Real hysteretic_vec_5_xl = (-0.5);
  parameter Real hysteretic_vec_5_xu = 0.5;
  parameter Real hysteretic_vec_5_yl = (-13.0747);
  parameter Real hysteretic_vec_5_yu = 0;
  constant Integer hysteretic_vec_5_N = integer(200);
  Real hysteretic_vec_5_u_1[hysteretic_vec_5_N];
  Real hysteretic_vec_5_y_1[hysteretic_vec_5_N];
  discrete Real hysteretic_vec_5_state[hysteretic_vec_5_N];
  parameter Real VectorSum_6_p[10] = {1,(-1),0,0,0,0,0,0,2,200};
  constant Integer VectorSum_6_N = 200;
  constant Integer VectorSum_6_nin = 2;
  parameter Real VectorSum_6_w[2] = {VectorSum_6_p[1],VectorSum_6_p[2]};
  Real VectorSum_6_u_1[200],VectorSum_6_u_2[200];
  Real VectorSum_6_y_1[200];
  parameter Real VectorSum_7_p[10] = {0.00081669,0.00081669,0.00173431,(-0.00081669),0,0,0,0,3,200};
  constant Integer VectorSum_7_N = 200;
  constant Integer VectorSum_7_nin = 3;
  parameter Real VectorSum_7_w[3] = {VectorSum_7_p[1],VectorSum_7_p[2],VectorSum_7_p[3]};
  Real VectorSum_7_u_1[200],VectorSum_7_u_2[200],VectorSum_7_u_3[200];
  Real VectorSum_7_y_1[200];
  parameter Real Constant_8_k = 1;
  Real Constant_8_y[1];
  constant Real Scalar2Vector_9_p[2] = {(-1),200};
  constant Integer Scalar2Vector_9_N = integer(200);
  parameter Integer Scalar2Vector_9_Index = integer((-1));
  Real Scalar2Vector_9_u[1];
  Real Scalar2Vector_9_y_1[Scalar2Vector_9_N];
  constant Real pulse_sci_11_p[4] = {20,0.5,1000,2000};
  parameter Real pulse_sci_11_low = 20;
  parameter Real pulse_sci_11_amplitude = 0.5;
  parameter Real pulse_sci_11_ti = 1000;
  parameter Real pulse_sci_11_tf = 2000;
  Real pulse_sci_11_d(start = 20);
  Real pulse_sci_11_y[1];
  initial algorithm
    for VecInt_1_i in 1:200 loop
      VecInt_1_y_1[VecInt_1_i]:=VecInt_1_x0;
    end for;
  algorithm
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      when hysteretic_vec_5_u_1[hysteretic_vec_5_i]>hysteretic_vec_5_xu then
        hysteretic_vec_5_state[hysteretic_vec_5_i]:=0;
      end when;
    end for;
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      when hysteretic_vec_5_u_1[hysteretic_vec_5_i]<hysteretic_vec_5_xl then
        hysteretic_vec_5_state[hysteretic_vec_5_i]:=hysteretic_vec_5_yl;
      end when;
    end for;
    when time>1000 then
      pulse_sci_11_d:=20+pulse_sci_11_amplitude;
    end when;
    when time>2000 then
      pulse_sci_11_d:=20;
    end when;
  equation
    for VecInt_1_i in 1:200 loop
      der(VecInt_1_y_1[VecInt_1_i]) = VecInt_1_u_1[VecInt_1_i];
    end for;
    for Scalar2Vector_2_i in 1:Scalar2Vector_2_N loop
      Scalar2Vector_2_y_1[Scalar2Vector_2_i] = Scalar2Vector_2_u[1];
    end for;
    Vec2Scalar_3_y[1] = Vec2Scalar_3_u_1[1];
    vector_sum_4_y[1] = vector_sum_4_K*sum(vector_sum_4_u_1[:]);
    for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
      hysteretic_vec_5_y_1[hysteretic_vec_5_i] = hysteretic_vec_5_state[hysteretic_vec_5_i];
    end for;
    for VectorSum_6_i in 1:200 loop
      VectorSum_6_y_1[VectorSum_6_i] = {VectorSum_6_u_1[VectorSum_6_i],VectorSum_6_u_2[VectorSum_6_i]}*VectorSum_6_w;
    end for;
    for VectorSum_7_i in 1:200 loop
      VectorSum_7_y_1[VectorSum_7_i] = {VectorSum_7_u_1[VectorSum_7_i],VectorSum_7_u_2[VectorSum_7_i],VectorSum_7_u_3[VectorSum_7_i]}*VectorSum_7_w;
    end for;
    Constant_8_y[1] = 1;
    for Scalar2Vector_9_i in 1:Scalar2Vector_9_N loop
      Scalar2Vector_9_y_1[Scalar2Vector_9_i] = Scalar2Vector_9_u[1];
    end for;
    pulse_sci_11_y[1] = pulse_sci_11_d;
    Scalar2Vector_2_u[1] = pulse_sci_11_y[1];
    for i in 1:200 loop
      VecInt_1_u_1[i] = VectorSum_7_y_1[i];
    end for;
    for i in 1:200 loop
      hysteretic_vec_5_u_1[i] = VectorSum_6_y_1[i];
    end for;
    for i in 1:Scalar2Vector_2_N loop
      VectorSum_6_u_1[i] = Scalar2Vector_2_y_1[i];
    end for;
    Scalar2Vector_9_u[1] = Constant_8_y[1];
    for i in 1:Scalar2Vector_9_N loop
      VectorSum_7_u_1[i] = Scalar2Vector_9_y_1[i];
    end for;
    for i in 1:hysteretic_vec_5_N loop
      vector_sum_4_u_1[i] = hysteretic_vec_5_y_1[i];
    end for;
    for i in 1:hysteretic_vec_5_N loop
      VectorSum_7_u_2[i] = hysteretic_vec_5_y_1[i];
    end for;
    for i in 1:200 loop
      VectorSum_7_u_3[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:200 loop
      VectorSum_6_u_2[i] = VecInt_1_y_1[i];
    end for;
    for i in 1:200 loop
      Vec2Scalar_3_u_1[i] = VecInt_1_y_1[i];
    end for;
end Pd2Model;

