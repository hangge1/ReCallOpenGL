#version 460 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient; //环境光反射率
    vec3 diffuse; //漫反射率
    vec3 specular; //高光反射率
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    //环境光
    vec3 ambient = light.ambient * material.ambient; 

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    //漫反射
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);


    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //计算入射光线的反射光线
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //镜面高光
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = (ambient + diffuse + specular); //objectColor取消
    FragColor = vec4(result, 1.0);
}