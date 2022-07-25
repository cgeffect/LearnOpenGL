#version 330 core
out vec4 FragColor;

in vec2 outUV;
in vec3 outFragPos;
in vec3 outNormal;

struct Material
{
    sampler2D   m_diffuse;
    sampler2D   m_specular;

    float       m_shiness;
};

uniform Material myMaterial;

struct Light
{
    vec3 m_pos;
    vec3 m_direction;
    float m_cutOff;
    float m_outCutOff;

    vec3 m_ambient;
    vec3 m_diffuse;
    vec3 m_specular;

    float m_c;
    float m_l;
    float m_q;
};

uniform Light myLight;


uniform sampler2D  ourTexture;
uniform vec3 view_pos;

void main()
{
//边缘模糊系数
    vec3 _lightDir = normalize(myLight.m_pos - outFragPos);
    vec3 _spotDir= normalize(myLight.m_direction);
    float cosTheta = dot(_lightDir , -_spotDir);
    float epsilon = myLight.m_cutOff - myLight.m_outCutOff;
    float intensity = clamp((cosTheta - myLight.m_outCutOff) / epsilon , 0.0f , 1.0f);

//长度衰减系数
    float _dist = length(myLight.m_pos - outFragPos);
    float _attenuation = 1.0f / (myLight.m_c + myLight.m_l * _dist + myLight.m_q * _dist * _dist);
    
    //环境光
    vec3 _ambient = myLight.m_ambient * vec3(texture(myMaterial.m_diffuse , outUV));

//漫反射
    vec3 _normal = normalize(outNormal);
    float _diff = max(dot(_normal , _lightDir) , 0.0f);
    vec3 _diffuse = myLight.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse , outUV));

//镜面反射
    float _specular_strength = 0.5;
    vec3 _viewDir = normalize(view_pos - outFragPos);
    vec3 _reflectDir = reflect(-_lightDir , outNormal);

    float _spec = pow(max(dot(_viewDir , _reflectDir) , 0.0f) , myMaterial.m_shiness);

    vec3 _sepcular = myLight.m_specular * _spec * vec3(texture(myMaterial.m_specular , outUV));

    _diffuse *= intensity;
    _sepcular *= intensity;

    vec3 result = _ambient  + _diffuse + _sepcular;
    FragColor = texture(ourTexture , outUV) * vec4(result ,1.0f) * _attenuation;

}
