model Pd2Model
  parameter Real VecInt_1_p[5] = {0,1e-06,0.001,0,50};
  constant Integer VecInt_1_N = 50;
  parameter Real VecInt_1_x0 = 0;
  Real VecInt_1_u[VecInt_1_N];
  Real VecInt_1_y[VecInt_1_N];
  parameter Real VecInt_2_p[5] = {0,1e-06,0.001,0,50};
  constant Integer VecInt_2_N = 50;
  parameter Real VecInt_2_x0 = 0;
  Real VecInt_2_u[VecInt_2_N];
  Real VecInt_2_y[VecInt_2_N];
  parameter Real VectorSum_3_p[10] = {1,(-1),0,0,0,0,0,0,2,50};
  constant Integer VectorSum_3_N = 50;
  constant Integer VectorSum_3_nin = 2;
  parameter Real VectorSum_3_w[VectorSum_3_nin] = VectorSum_3_p[1:VectorSum_3_nin];
  Real VectorSum_3_u[VectorSum_3_N,VectorSum_3_nin];
  Real VectorSum_3_y[VectorSum_3_N];
  parameter Real IndexShift_4_p[2] = {1,50};
  parameter Integer IndexShift_4_Shift = 1;
  constant Integer IndexShift_4_N = 50;
  Real IndexShift_4_u[IndexShift_4_N];
  Real IndexShift_4_y[IndexShift_4_N];
  parameter Real VectorSum_5_p[10] = {1,1,(-1),0,0,0,0,0,3,50};
  constant Integer VectorSum_5_N = 50;
  constant Integer VectorSum_5_nin = 2;
  parameter Real VectorSum_5_w[VectorSum_5_nin] = VectorSum_5_p[1:VectorSum_5_nin];
  Real VectorSum_5_u[VectorSum_5_N,VectorSum_5_nin];
  Real VectorSum_5_y[VectorSum_5_N];
  parameter Real IndexShift_6_p[2] = {(-1),50};
  parameter Integer IndexShift_6_Shift = (-1);
  constant Integer IndexShift_6_N = 50;
  Real IndexShift_6_u[IndexShift_6_N];
  Real IndexShift_6_y[IndexShift_6_N];
  parameter Real Scalar2Vector_7_p[2] = {0,50};
  constant Integer Scalar2Vector_7_N = 50;
  parameter Integer Scalar2Vector_7_Index = 0;
  Real Scalar2Vector_7_u;
  Real Scalar2Vector_7_y[Scalar2Vector_7_N];
  constant Real pulse_sci_8_p[4] = {0,1,0,1};
  parameter Real pulse_sci_8_low = 0;
  parameter Real pulse_sci_8_amplitude = 1;
  parameter Real pulse_sci_8_ti = 0;
  parameter Real pulse_sci_8_tf = 1;
  Real pulse_sci_8_d(start = pulse_sci_8_low);
  Real pulse_sci_8_y;
  parameter Real Vec2Scalar_10_p[2] = {0,50};
  parameter Integer Vec2Scalar_10_Index = 0+1;
  constant Integer Vec2Scalar_10_N = 50;
  Real Vec2Scalar_10_u[Vec2Scalar_10_N];
  Real Vec2Scalar_10_y;
  parameter Real Vec2Scalar_11_p[2] = {49,50};
  parameter Integer Vec2Scalar_11_Index = 49+1;
  constant Integer Vec2Scalar_11_N = 50;
  Real Vec2Scalar_11_u[Vec2Scalar_11_N];
  Real Vec2Scalar_11_y;
  initial equation
    for VecInt_1_i in 1:VecInt_1_N loop
      VecInt_1_y[VecInt_1_i] = VecInt_1_x0;
    end for;
    for VecInt_2_i in 1:VecInt_2_N loop
      VecInt_2_y[VecInt_2_i] = VecInt_2_x0;
    end for;
  algorithm
    when time>pulse_sci_8_ti then
      pulse_sci_8_d:=pulse_sci_8_low+pulse_sci_8_amplitude;
    end when;
    when time>pulse_sci_8_tf then
      pulse_sci_8_d:=pulse_sci_8_low;
    end when;
  equation
    for VecInt_1_i in 1:VecInt_1_N loop
      der(VecInt_1_y[VecInt_1_i]) = VecInt_1_u[VecInt_1_i];
    end for;
    for VecInt_2_i in 1:VecInt_2_N loop
      der(VecInt_2_y[VecInt_2_i]) = VecInt_2_u[VecInt_2_i];
    end for;
    for VectorSum_3_i in 1:VectorSum_3_N loop
      VectorSum_3_y[VectorSum_3_i] = VectorSum_3_u[VectorSum_3_i,1:VectorSum_3_nin]*VectorSum_3_w;
    end for;
    for IndexShift_4_i in 1:IndexShift_4_N loop
      IndexShift_4_y[IndexShift_4_i] = if IndexShift_4_i-IndexShift_4_Shift>0 and IndexShift_4_i-IndexShift_4_Shift<IndexShift_4_N then IndexShift_4_u[IndexShift_4_i-IndexShift_4_Shift] else 0;
    end for;
    for VectorSum_5_i in 1:VectorSum_5_N loop
      VectorSum_5_y[VectorSum_5_i] = VectorSum_5_u[VectorSum_5_i,1:VectorSum_5_nin]*VectorSum_5_w;
    end for;
    for IndexShift_6_i in 1:IndexShift_6_N loop
      IndexShift_6_y[IndexShift_6_i] = if IndexShift_6_i-IndexShift_6_Shift>0 and IndexShift_6_i-IndexShift_6_Shift<IndexShift_6_N then IndexShift_6_u[IndexShift_6_i-IndexShift_6_Shift] else 0;
    end for;
    for Scalar2Vector_7_i in 1:Scalar2Vector_7_N loop
      Scalar2Vector_7_y[Scalar2Vector_7_i] = (if Scalar2Vector_7_Index+1==Scalar2Vector_7_i or Scalar2Vector_7_Index==((-1)) then Scalar2Vector_7_u else 0);
    end for;
    pulse_sci_8_y = pulse_sci_8_d;
    Vec2Scalar_10_y = Vec2Scalar_10_u[Vec2Scalar_10_Index];
    Vec2Scalar_11_y = Vec2Scalar_11_u[Vec2Scalar_11_Index];
    for i in 1:VectorSum_3_N loop
      VecInt_1_u[i] = VectorSum_3_y[i];
    end for;
    for i in 1:VecInt_2_N loop
      VectorSum_3_u[i,1] = VecInt_2_y[i];
    end for;
    for i in 1:IndexShift_4_N loop
      VectorSum_3_u[i,2] = IndexShift_4_y[i];
    end for;
    for i in 1:VecInt_2_N loop
      IndexShift_4_u[i] = VecInt_2_y[i];
    end for;
    for i in 1:VectorSum_5_N loop
      VecInt_2_u[i] = VectorSum_5_y[i];
    end for;
    for i in 1:VecInt_1_N loop
      VectorSum_5_u[i,3] = VecInt_1_y[i];
    end for;
    for i in 1:IndexShift_6_N loop
      VectorSum_5_u[i,2] = IndexShift_6_y[i];
    end for;
    for i in 1:VecInt_1_N loop
      IndexShift_6_u[i] = VecInt_1_y[i];
    end for;
    for i in 1:Scalar2Vector_7_N loop
      VectorSum_5_u[i,1] = Scalar2Vector_7_y[i];
    end for;
    Scalar2Vector_7_u = pulse_sci_8_y;
    for i in 1:VecInt_1_N loop
      Vec2Scalar_10_u[i] = VecInt_1_y[i];
    end for;
    for i in 1:VecInt_1_N loop
      Vec2Scalar_11_u[i] = VecInt_1_y[i];
    end for;
end Pd2Model;

