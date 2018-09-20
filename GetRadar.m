
function r = GetRadar(dt)
persistent posp

posp = 0;
if isempty(posp)
  posp = 0;
end


vel = rand;
alt = 1000 + 10*rand;

pos = posp + vel*dt;

v = 0 + pos*0.05*randn;

r = sqrt(pos^2 + alt^2) + v;

posp = pos;
end

