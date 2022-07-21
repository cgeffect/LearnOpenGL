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
    vec3 m_ambient;
    vec3 m_diffuse;
    vec3 m_specular;
};

uniform Light myLight;


uniform sampler2D  ourTexture;
uniform vec3 view_pos;

void main()
{
//环境光
    vec3 _ambient = myLight.m_ambient * vec3(texture(myMaterial.m_diffuse , outUV));

//漫反射
    vec3 _normal = normalize(outNormal);
    vec3 _lightDir = normalize(myLight.m_pos - outFragPos);
    float _diff = max(dot(_normal , _lightDir) , 0.0f);
    vec3 _diffuse = myLight.m_diffuse * _diff * vec3(texture(myMaterial.m_diffuse , outUV));

//镜面反射
    float _specular_strength = 0.5;
    vec3 _viewDir = normalize(view_pos - outFragPos);
    vec3 _reflectDir = reflect(-_lightDir , outNormal);

    float _spec = pow(max(dot(_viewDir , _reflectDir) , 0.0f) , myMaterial.m_shiness);

    vec3 _sepcular = myLight.m_specular * _spec * vec3(texture(myMaterial.m_specular , outUV));


    vec3 result = _ambient  + _diffuse + _sepcular;
    FragColor = texture(ourTexture , outUV) * vec4(result ,1.0f);
}
