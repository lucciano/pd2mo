model Pd2Model
  parameter Real Constant_8_k = 1;
  parameter Integer Scalar2Vector_2_Index = integer((-1));
  parameter Integer Scalar2Vector_9_Index = integer((-1));
  parameter Integer Vec2Scalar_3_Index = 0+1;
  parameter Real [2] Vec2Scalar_3_p = {0,200};
  parameter Real [5] VecInt_1_p = {0,1e-06,0.001,18.8453,200};
  parameter Real VecInt_1_x0 = 18.8453;
  parameter Real [10] VectorSum_6_p = {1,(-1),0,0,0,0,0,0,2,200};
  parameter Real [VectorSum_6_nin] VectorSum_6_w = VectorSum_6_p[1:VectorSum_6_nin];
  parameter Real [10] VectorSum_7_p = {0.00081669,0.00081669,0.00173431,(-0.00081669),0,0,0,0,3,200};
  parameter Real [VectorSum_7_nin] VectorSum_7_w = VectorSum_7_p[1:VectorSum_7_nin];
  parameter Real hysteretic_vec_5_xl = (-0.5);
  parameter Real hysteretic_vec_5_xu = 0.5;
  parameter Real hysteretic_vec_5_yl = (-13.0747);
  parameter Real hysteretic_vec_5_yu = 0;
  parameter Real pulse_sci_11_amplitude = 0.5;
  parameter Real pulse_sci_11_low = 20;
  parameter Real pulse_sci_11_tf = 2000;
  parameter Real pulse_sci_11_ti = 1000;
  parameter Real [2] vector_sum_4_p = {(-0.000356739),200};
  Real [1] Constant_8_y;
  constant Integer Scalar2Vector_2_N = integer(200);
  constant Real [2] Scalar2Vector_2_p = {(-1),200};
  Real [1] Scalar2Vector_2_u;
  Real [Scalar2Vector_2_N,1] Scalar2Vector_2_y;
  constant Integer Scalar2Vector_9_N = integer(200);
  constant Real [2] Scalar2Vector_9_p = {(-1),200};
  Real [1] Scalar2Vector_9_u;
  Real [Scalar2Vector_9_N,1] Scalar2Vector_9_y;
  constant Integer Vec2Scalar_3_N = 200;
  Real [Vec2Scalar_3_N,1] Vec2Scalar_3_u;
  Real [1] Vec2Scalar_3_y;
  constant Integer VecInt_1_N = 200;
  Real [VecInt_1_N,1] VecInt_1_u;
  Real [VecInt_1_N,1] VecInt_1_y;
  constant Integer VectorSum_6_N = 200;
  constant Integer VectorSum_6_nin = 2;
  Real [VectorSum_6_N,VectorSum_6_nin] VectorSum_6_u;
  Real [VectorSum_6_N,1] VectorSum_6_y;
  constant Integer VectorSum_7_N = 200;
  constant Integer VectorSum_7_nin = 2;
  Real [VectorSum_7_N,VectorSum_7_nin] VectorSum_7_u;
  Real [VectorSum_7_N,1] VectorSum_7_y;
  constant Integer hysteretic_vec_5_N = integer(200);
  constant Real [5] hysteretic_vec_5_p = {(-0.5),0.5,(-13.0747),0,200};
  discrete Real [hysteretic_vec_5_N] hysteretic_vec_5_state;
  Real [hysteretic_vec_5_N,1] hysteretic_vec_5_u;
  Real [hysteretic_vec_5_N,1] hysteretic_vec_5_y;
  Real pulse_sci_11_d(start = pulse_sci_11_low);
  constant Real [4] pulse_sci_11_p = {20,0.5,1000,2000};
  Real [1] pulse_sci_11_y;
  Real vector_sum_4_K = (-0.000356739);
  constant Integer vector_sum_4_N = 200;
  Real [vector_sum_4_N,1] vector_sum_4_u;
  Real [1] vector_sum_4_y;
initial equation
  for VecInt_1_i in 1:VecInt_1_N loop
    VecInt_1_y[VecInt_1_i,1] = VecInt_1_x0;
  end for;
equation
  for VecInt_1_i in 1:VecInt_1_N loop
    der(VecInt_1_y[VecInt_1_i,1]) = VecInt_1_u[VecInt_1_i,1];
  end for;
  if ((Scalar2Vector_2_Index==(((-1))))) then 
    for Scalar2Vector_2_i in 1:Scalar2Vector_2_N loop
      Scalar2Vector_2_y[Scalar2Vector_2_i,1] = Scalar2Vector_2_u[1];
    end for;
  else
    for Scalar2Vector_2_i in 1:Scalar2Vector_2_Index loop
      Scalar2Vector_2_y[Scalar2Vector_2_i,1] = 0;
    end for;
    Scalar2Vector_2_y[Scalar2Vector_2_Index+1,1] = Scalar2Vector_2_u[1];
    for Scalar2Vector_2_i in Scalar2Vector_2_Index+2:Scalar2Vector_2_N loop
      Scalar2Vector_2_y[Scalar2Vector_2_i,1] = 0;
    end for;
  end if;
  Vec2Scalar_3_y[1] = Vec2Scalar_3_u[Vec2Scalar_3_Index,1];
  vector_sum_4_y[1] = vector_sum_4_K*sum(vector_sum_4_u[:,1]);
  for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
    hysteretic_vec_5_y[hysteretic_vec_5_i,1] = hysteretic_vec_5_state[hysteretic_vec_5_i];
  end for;
  for VectorSum_6_i in 1:VectorSum_6_N loop
    VectorSum_6_y[VectorSum_6_i,1] = VectorSum_6_u[VectorSum_6_i,1:VectorSum_6_nin]*VectorSum_6_w;
  end for;
  for VectorSum_7_i in 1:VectorSum_7_N loop
    VectorSum_7_y[VectorSum_7_i,1] = VectorSum_7_u[VectorSum_7_i,1:VectorSum_7_nin]*VectorSum_7_w;
  end for;
  Constant_8_y[1] = Constant_8_k;
  if ((Scalar2Vector_9_Index==(((-1))))) then 
    for Scalar2Vector_9_i in 1:Scalar2Vector_9_N loop
      Scalar2Vector_9_y[Scalar2Vector_9_i,1] = Scalar2Vector_9_u[1];
    end for;
  else
    for Scalar2Vector_9_i in 1:Scalar2Vector_9_Index loop
      Scalar2Vector_9_y[Scalar2Vector_9_i,1] = 0;
    end for;
    Scalar2Vector_9_y[Scalar2Vector_9_Index+1,1] = Scalar2Vector_9_u[1];
    for Scalar2Vector_9_i in Scalar2Vector_9_Index+2:Scalar2Vector_9_N loop
      Scalar2Vector_9_y[Scalar2Vector_9_i,1] = 0;
    end for;
  end if;
  pulse_sci_11_y[1] = pulse_sci_11_d;
  Scalar2Vector_2_u[1] = pulse_sci_11_y[1];
  for i in 1:VectorSum_7_N loop
    VecInt_1_u[i,1] = VectorSum_7_y[i,1];
  end for;
  Scalar2Vector_9_u[1] = Constant_8_y[1];
  for i in 1:VecInt_1_N loop
    VectorSum_7_u[i,3] = VecInt_1_y[i,1];
  end for;
  for i in 1:VecInt_1_N loop
    VectorSum_6_u[i,2] = VecInt_1_y[i,1];
  end for;
  for i in 1:VecInt_1_N loop
    Vec2Scalar_3_u[i,1] = VecInt_1_y[i,1];
  end for;
algorithm
  for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
    when hysteretic_vec_5_u[hysteretic_vec_5_i,1]>hysteretic_vec_5_xu then
      hysteretic_vec_5_state[hysteretic_vec_5_i]:=hysteretic_vec_5_yu;
    end when;
  end for;
  for hysteretic_vec_5_i in 1:hysteretic_vec_5_N loop
    when hysteretic_vec_5_u[hysteretic_vec_5_N,1]<hysteretic_vec_5_xl then
      hysteretic_vec_5_state[hysteretic_vec_5_i]:=hysteretic_vec_5_yl;
    end when;
  end for;
  when time>pulse_sci_11_ti then
    pulse_sci_11_d:=pulse_sci_11_low+pulse_sci_11_amplitude;
  end when;
  when time>pulse_sci_11_tf then
    pulse_sci_11_d:=pulse_sci_11_low;
  end when;
end Pd2Model;
