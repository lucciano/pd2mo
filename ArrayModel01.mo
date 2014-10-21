Pd2Model
  parameter Real Constant_1_k = 1;
  Real Constant_1_y[1](start = {1});
  parameter Real VectorSum_2_p[10] = {1,-1,0,0,0,0,0,0,2,10};
  constant Integer VectorSum_2_N = 10;
  constant Integer VectorSum_2_nin = 2;
  parameter Real VectorSum_2_w[2] = VectorSum_2_p[1:2];
  Real ;
  Real ;
  parameter Real Vec2Scalar_3_p[2] = {0,10};
  parameter Integer Vec2Scalar_3_Index = 0+1;
  constant Integer Vec2Scalar_3_N = 10;
  Real ;
  Real Vec2Scalar_3_y[1];
  parameter Real Scalar2Vector_4_p[2] = {-1,10};
  constant Integer Scalar2Vector_4_N = 10;
  parameter Integer Scalar2Vector_4_Index = -1;
  Real Scalar2Vector_4_u[1];
  Real ;
  parameter Real VecInt_5_p[5] = {0,1e-06,0.001,0,10};
  constant Integer VecInt_5_N = 10;
  parameter Real VecInt_5_x0 = 0;
  Real ;
  Real ;
  initial equation
    for VecInt_5_i in 1:VecInt_5_N loop
      VecInt_5_y_1[VecInt_5_i] = VecInt_5_x0;
    end for;
  equation
    Constant_1_y[1] = 1;
    for VectorSum_2_i in 1:VectorSum_2_N loop
      VectorSum_2_y_1[VectorSum_2_i] = VectorSum_2_u[VectorSum_2_i,1:VectorSum_2_nin]*VectorSum_2_w;
    end for;
    Vec2Scalar_3_y[1] = Vec2Scalar_3_u_1[Vec2Scalar_3_Index];
    for Scalar2Vector_4_i in 1:Scalar2Vector_4_N loop
      Scalar2Vector_4_y_1[Scalar2Vector_4_i] = (if Scalar2Vector_4_Index+1==Scalar2Vector_4_i or Scalar2Vector_4_Index==(-1) then Scalar2Vector_4_u[1] else 0);
    end for;
    for VecInt_5_i in 1:VecInt_5_N loop
      der(VecInt_5_y_1[VecInt_5_i]) = VecInt_5_u_1[VecInt_5_i];
    end for;
    for i in 1:Scalar2Vector_4_N loop
      VectorSum_2_u_1[i] = Scalar2Vector_4_y_1[i];
    end for;
    Scalar2Vector_4_u[1] = Constant_1_y[1];
    for i in 1:VectorSum_2_N loop
      VecInt_5_u_1[i] = VectorSum_2_y_1[i];
    end for;
    for i in 1:VecInt_5_N loop
      VectorSum_2_u_2[i] = VecInt_5_y_1[i];
    end for;
    for i in 1:VecInt_5_N loop
      Vec2Scalar_3_u_1[i] = VecInt_5_y_1[i];
    end for;
end Pd2Model;
