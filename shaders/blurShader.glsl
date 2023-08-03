uniform sampler2D texture;
uniform float radius;

void main() {
    vec2 texCoords = gl_TexCoord[0].xy;

    vec4 sum = vec4(0);
    vec2 tc = texCoords;
    float blur = radius/100.0;

    float hstep = 1.0/800.0;
    float vstep = 1.0/600.0;
    sum += texture2D(texture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
    sum += texture2D(texture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(texture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(texture, vec2(tc.x - blur*hstep, tc.y - blur*vstep)) * 0.1945945946;

    sum += texture2D(texture, vec2(tc.x, tc.y)) * 0.2270270270;

    sum += texture2D(texture, vec2(tc.x + blur*hstep, tc.y + blur*vstep)) * 0.1945945946;
    sum += texture2D(texture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(texture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(texture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;

    gl_FragColor = vec4(sum.rgb, 1.0);
}
