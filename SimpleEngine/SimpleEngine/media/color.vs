// global variables
// can be modified externally from the C++ code
// ͨ�������� globals ���ո���Ƶ��( ��Щ globals ����һ���޸� )���л���, �ֱ���ڲ�ͬ�� cbuffer ��( HLSL ��һ�� buffer object type )
// ��Ȼ graphics card �Ὣͬһ�� buffer ������б����浽һ��( �������� ), �洢Ч�ʸ���
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};


// �Զ���ṹ��
// ����ı����ǼĴ��� => Shader ͨ����Ĵ���ͨ�Ų���� GPU ��Ӳ����Ⱦ����
// GPU ���Դ���ȡ��һ������Ĳ�ͬ��������( ��ɫ, λ�õ� )�ֱ����Ӧ�ļĴ�����
// ���� Shader �ȵ� POSITION �Ĵ����л�ȡ����, �ٽ�������������䵽 SV_POSITION �Ĵ�����
struct VertexInputType
{
    float4 position : POSITION;	// x, y, z, w
    float4 color : COLOR;		// red, green, blue, alpha
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};


// Vertex Shader
PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // Store the input color for the pixel shader to use.
    output.color = input.color;
    
    return output;
}