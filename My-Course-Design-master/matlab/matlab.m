%%%%%%%%%%%%%%%
num = 3;
den = [0.06 0.7 1 0];
G = tf(num,den)
G1 = feedback(G,1)
%%%%%%%%%%%%
num = 3;
den = [0.06 0.7 1 0];
G = tf(num,den)
G1 = feedback(G,1)
margin(G)
step(G1)
impulse(G1)
%%%%%%%%%%%%%%%%%>>num1=conv([0.626 1],3)
den1=conv([0.204 1],[0.04,0.5,1,0])
G2=tf(num1,den1)
G3=feedback(G2,1)
margin(G2)
step(G3)


