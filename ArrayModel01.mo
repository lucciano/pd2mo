model Pd2Model
  parameter Real Constant_1_k = 1;
  Real Constant_1_y[1](start = {Constant_1_k});
  parameter Real VectorSum_2_p[10] = {1,-1,0,0,0,0,0,0,2,10};
  constant Integer VectorSum_2_N = 10;
  constant Integer VectorSum_2_nin = 2;
  parameter Real VectorSum_2_w[VectorSum_2_nin] = VectorSum_2_p[1:VectorSum_2_nin];
  Real VectorSum_2_u[VectorSum_2_N,VectorSum_2_nin];
  Real VectorSum_2_y[VectorSum_2_N,1];
  parameter Real Vec2Scalar_3_p[2] = {0,10};
  parameter Integer Vec2Scalar_3_Index = 0;
  constant Integer Vec2Scalar_3_N = 10;
  Real Vec2Scalar_3_u[Vec2Scalar_3_N,1];
  Real Vec2Scalar_3_y[1];
  parameter Real Scalar2Vector_4_p[2] = {-1,10};
  constant Integer Scalar2Vector_4_N = 10;
  parameter Integer Scalar2Vector_4_Index = -1;
  Real Scalar2Vector_4_u[1];
  Real Scalar2Vector_4_y[Scalar2Vector_4_N,1];
  parameter Real VecInt_5_p[5] = {0,1e-06,0.001,0,10};
  constant Integer VecInt_5_N = 10;
  parameter Real VecInt_5_x0 = 1;
  Real VecInt_5_u[VecInt_5_N,1];
  Real VecInt_5_y[VecInt_5_N,1];
  initial equation
    for VecInt_5_i in 1:VecInt_5_N loop
      VecInt_5_y[VecInt_5_i,1] = VecInt_5_x0;
    end for;
  equation
    Constant_1_y[1] = Constant_1_k;
    for VectorSum_2_i in 1:VectorSum_2_N loop
      VectorSum_2_y[VectorSum_2_i,1] = VectorSum_2_u[VectorSum_2_i,1:VectorSum_2_nin]*VectorSum_2_w;
    end for;
    Vec2Scalar_3_y[1] = Vec2Scalar_3_u[Vec2Scalar_3_Index,1];
    for Scalar2Vector_4_i in 1:Scalar2Vector_4_N loop
      Scalar2Vector_4_y[Scalar2Vector_4_i,1] = (if Scalar2Vector_4_Index==Scalar2Vector_4_i or Scalar2Vector_4_Index==(-1) then Scalar2Vector_4_u[1] else 0);
    end for;
    for VecInt_5_i in 1:VecInt_5_N loop
      der(VecInt_5_y[VecInt_5_i,1]) = VecInt_5_u[VecInt_5_i,1];
    end for;
    for i in 1:Scalar2Vector_4_N loop
      VectorSum_2_u[i,1] = Scalar2Vector_4_y[i,1];
    end for;
    Scalar2Vector_4_u[1] = Constant_1_y[1];
    for i in 1:VectorSum_2_N loop
      VecInt_5_u[i,1] = VectorSum_2_y[i,1];
    end for;
    for i in 1:VecInt_5_N loop
      VectorSum_2_u[i,2] = VecInt_5_y[i,1];
    end for;
    for i in 1:VecInt_5_N loop
      Vec2Scalar_3_u[i,1] = VecInt_5_y[i,1];
    end for;
end Pd2Model;
