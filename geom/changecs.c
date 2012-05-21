/*

        O,(I,J,K) : World Coordinate System
        A,(u,v,w) : View Coordinate System

        A(VC)=(0, 0, 0)
        u(VC)=(1, 0, 0)
        ...

        A(WC)=(Xa, Ya, Za) ie: Xa.I + Ya.J + Za.K
        u(WC)=(Xu, Yu, Zu) ...

        M(VC)=(x,y,z) ie: x.u + y.v + z.w

        M(WC)   = x.u(WC) + y.v(WC) + z.w(WC) + OA(WC)
                = x.(Xu.I + Yu.J + Zu.K) +
                  y.(Xv.I + Yv.J + Zv.K) +
                  z.(Xw.I + Yw.J + Zw.K) +
                  Xa.I + Ya.J + Za.K

                = (Xu.x + Xv.y + Xw.z + Xa.1).I +
                  (Yu.x + Yv.y + Yw.z + Ya.1).J +
                  (Zu.x + Zv.y + Zw.z + Za.1).K

                  | Xu   Xv   Xw   Xa |   |  x  |
                  |                   |   |     |
                  | Yu   Yv   Yw   Ya |   |  y  |
                = |                   | . |     |
                  | Zu   Zv   Zw   Za |   |  z  |
                  |                   |   |     |
                  |  0    0    0    1 |   |  1  |
         
*/

