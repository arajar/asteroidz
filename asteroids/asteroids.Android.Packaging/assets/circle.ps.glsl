varying float v_radius;
varying vec3 v_color;

#define between(v,x1,x2) (v>= x1 && v<=x2)
#define pi 3.141592653589793238462643383279

void main()
{
    vec2  pnt = vec2(0.5,0.5);
    float dr = 0.005;
    float fr = 0.15;
    float r1 = fr;
    float r2 = 1.5*fr;
    float r3 = 2.0*fr;
    float r4 = 2.5*fr;
    float r5 = 3.0*fr;
    float rp = distance(pnt,gl_FragCoord.xy);
    vec4 col1 = vec4(0.4,0.1,0.,1.);
    vec4 col2 = vec4(1.,1.,1.,1.);
    float angle = atan(gl_FragCoord.y,gl_FragCoord.x);
    vec4 rezcol;
    rezcol = (between(rp,r1-dr,r1+dr) && between(angle,-pi,pi))? col1:col2;
    rezcol = (between(rp,r2-dr,r2+dr) && between(angle,-pi,pi/3.1) && rezcol==col2)? col1:rezcol;
    rezcol = (between(rp,r3-dr,r3+dr) && between(angle,-pi,pi/4.6) && rezcol==col2)? col1:rezcol;
    rezcol = (between(rp,r4-dr,r4+dr) && between(angle,-pi,pi/8.8) && rezcol==col2)? col1:rezcol;
    rezcol = (between(rp,r5-dr,r5+dr) && between(angle,-pi,pi/22.8) && rezcol==col2)? col1:rezcol;
    gl_FragColor = rezcol;
}