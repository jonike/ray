// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include "ogl_types.h"

_NAME_BEGIN

int OGLExtenstion::initExtention = 0;

bool OGLFeatures::ARB_bindless_texture = 0;
bool OGLFeatures::ARB_vertex_array_object = 0;
bool OGLFeatures::ARB_vertex_attrib_binding = 0;
bool OGLFeatures::ARB_provoking_vertex = 0;
bool OGLFeatures::ARB_direct_state_access = 0;
bool OGLFeatures::ARB_buffer_storage = 0;
bool OGLFeatures::ARB_viewport_array = 0;
bool OGLFeatures::KHR_debug = 0;
bool OGLFeatures::NV_command_list = 0;
bool OGLFeatures::NV_shader_buffer_load = 0;
bool OGLFeatures::NV_vertex_buffer_unified_memory = 0;

#ifdef _BUILD_OPENGL
#	ifdef GLEW_MX
	GLEWContext _glewctx;
#	endif
#endif

GLenum
OGLTypes::asOGLVertexType(VertexType type) noexcept
{
	switch (type)
	{
	case VertexType::Point:
		return GL_POINTS;
	case VertexType::Line:
		return GL_LINES;
	case VertexType::Triangle:
		return GL_TRIANGLES;
	case VertexType::Fan:
		return GL_TRIANGLE_FAN;
	case VertexType::PointOrLine:
		return GL_POINTS;
	case VertexType::TriangleOrLine:
		return GL_TRIANGLES;
	case VertexType::FanOrLine:
		return GL_TRIANGLE_FAN;
	default:
		assert(false);
		return GL_TRIANGLES;
	}
}

GLenum
OGLTypes::asOGLVertexFormat(VertexFormat format) noexcept
{
	switch (format)
	{
	case VertexFormat::Char:
	case VertexFormat::Char2:
	case VertexFormat::Char3:
	case VertexFormat::Char4:
		return GL_BYTE;
	case VertexFormat::Short:
	case VertexFormat::Short2:
	case VertexFormat::Short3:
	case VertexFormat::Short4:
		return GL_SHORT;
	case VertexFormat::Int:
	case VertexFormat::Int2:
	case VertexFormat::Int3:
	case VertexFormat::Int4:
		return GL_INT;
	case VertexFormat::Uchar:
	case VertexFormat::Uchar2:
	case VertexFormat::Uchar3:
	case VertexFormat::Uchar4:
		return GL_UNSIGNED_BYTE;
	case VertexFormat::Ushort:
	case VertexFormat::Ushort2:
	case VertexFormat::Ushort3:
	case VertexFormat::Ushort4:
		return GL_UNSIGNED_SHORT;
	case VertexFormat::Uint:
	case VertexFormat::Uint2:
	case VertexFormat::Uint3:
	case VertexFormat::Uint4:
		return GL_UNSIGNED_INT;
	case VertexFormat::Float:
	case VertexFormat::Float2:
	case VertexFormat::Float3:
	case VertexFormat::Float4:
		return GL_FLOAT;
	default:
		assert(false);
		return GL_INVALID_ENUM;
	}
}

GLenum
OGLTypes::asOGLIndexType(IndexType type) noexcept
{
	switch (type)
	{
	case IndexType::None:
		return GL_NONE;
	case IndexType::Uint16:
		return GL_UNSIGNED_SHORT;
	case IndexType::Uint32:
		return GL_UNSIGNED_INT;
	default:
		assert(false);
		return GL_UNSIGNED_SHORT;
	}
}

GLenum
OGLTypes::asOGLShaderType(ShaderType type) noexcept
{
	switch (type)
	{
	case ShaderType::ST_VERTEX:
		return GL_VERTEX_SHADER;
	case ShaderType::ST_FRAGMENT:
		return GL_FRAGMENT_SHADER;
	case ShaderType::ST_COMPUTE:
		return GL_COMPUTE_SHADER;
	case ShaderType::ST_GEOMETRY:
		return GL_GEOMETRY_SHADER;
	case ShaderType::ST_TESS_CONTROL:
		return GL_TESS_CONTROL_SHADER;
	case ShaderType::ST_TESS_EVALUATION:
		return GL_TESS_EVALUATION_SHADER;
	case ShaderType::ST_CG_VERTEX:
		return GL_CG_VERTEX_SHADER_EXT;
	case ShaderType::ST_CG_FRAGMENT:
		return GL_CG_FRAGMENT_SHADER_EXT;
	default:
		assert(false);
		return GL_VERTEX_SHADER;
	}
}

GLenum
OGLTypes::asOGLTarget(TextureDim target, bool multisampler) noexcept
{
	if (target == TextureDim::DIM_2D)
	{
		if (multisampler)
			return GL_TEXTURE_2D_MULTISAMPLE;
		else
			return GL_TEXTURE_2D;
	}
	else if (target == TextureDim::DIM_3D)
	{
		if (multisampler)
			return GL_INVALID_ENUM;
		else
			return GL_TEXTURE_3D;
	}
	else if (target == TextureDim::DIM_2D_ARRAY)
	{
		if (multisampler)
			return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
		else
			return GL_TEXTURE_2D_ARRAY;
	}
	else if (target == TextureDim::DIM_3D_ARRAY)
	{
		if (multisampler)
			return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
		else
			return GL_TEXTURE_2D;
	}
	else if (target == TextureDim::DIM_CUBE)
	{
		if (multisampler)
			return GL_INVALID_ENUM;
		else
			return GL_TEXTURE_CUBE_MAP;
	}
	else if (target == TextureDim::DIM_CUBE_ARRAY)
	{
		if (multisampler)
			return GL_INVALID_ENUM;
		else
			return GL_TEXTURE_CUBE_MAP_ARRAY;
	}

	assert(false);
	return (GLenum)GL_INVALID_ENUM;
}

GLenum
OGLTypes::asOGLFormat(TextureFormat format) noexcept
{
	if (format == TextureFormat::DEPTH_COMPONENT16 || format == TextureFormat::DEPTH_COMPONENT24 || format == TextureFormat::DEPTH_COMPONENT32)
		return GL_DEPTH_COMPONENT;

	if (format == TextureFormat::DEPTH24_STENCIL8 || format == TextureFormat::DEPTH32_STENCIL8)
		return GL_DEPTH_STENCIL;

	if (format == TextureFormat::STENCIL8)
		return GL_STENCIL_INDEX;

	if (format == TextureFormat::R8G8B8 || format == TextureFormat::R16G16B16 || format == TextureFormat::R16G16B16F || format == TextureFormat::R32G32B32F)
		return GL_RGB;

	if (format == TextureFormat::R8G8B8A8 || format == TextureFormat::R16G16B16A16 || format == TextureFormat::R16G16B16A16F || format == TextureFormat::R32G32B32A32F)
		return GL_RGBA;

	if (format == TextureFormat::R16G16B16A16_SNORM)
		return GL_RGBA;

	if (format == TextureFormat::SR8G8B8 || format == TextureFormat::SRGB)
		return GL_RGB;

	if (format == TextureFormat::SR8G8B8A8 || format == TextureFormat::SRGBA)
		return GL_RGBA;

	if (format == TextureFormat::R8 || format == TextureFormat::R16F || format == TextureFormat::R32F)
		return GL_RED;

	if (format == TextureFormat::RG16F || format == TextureFormat::RG32F)
		return GL_RG;

	if (format == TextureFormat::R11G11B10F)
		return GL_RGB;

	assert(false);
	return GL_INVALID_ENUM;
}

GLenum
OGLTypes::asOGLType(TextureFormat format) noexcept
{
	if (format == TextureFormat::DEPTH24_STENCIL8)
		return GL_UNSIGNED_INT_24_8;

	if (format == TextureFormat::DEPTH32_STENCIL8)
		return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;

	if (format == TextureFormat::STENCIL8)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::DEPTH_COMPONENT32)
		return GL_FLOAT;

	if (format == TextureFormat::DEPTH_COMPONENT16 || format == TextureFormat::DEPTH_COMPONENT24)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::R8G8B8 || format == TextureFormat::R8G8B8A8)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::R16G16B16 || format == TextureFormat::R16G16B16A16)
		return GL_UNSIGNED_SHORT;

	if (format == TextureFormat::R8)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::R16G16B16F || format == TextureFormat::R32G32B32F)
		return GL_FLOAT;

	if (format == TextureFormat::R16G16B16A16_SNORM)
		return GL_FLOAT;

	if (format == TextureFormat::R16G16B16A16F || format == TextureFormat::R32G32B32A32F)
		return GL_FLOAT;

	if (format == TextureFormat::SR8G8B8 || format == TextureFormat::SRGB)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::SR8G8B8A8 || format == TextureFormat::SRGBA)
		return GL_UNSIGNED_BYTE;

	if (format == TextureFormat::R16F || format == TextureFormat::R32F)
		return GL_FLOAT;

	if (format == TextureFormat::RG16F || format == TextureFormat::RG32F)
		return GL_FLOAT;

	if (format == TextureFormat::R11G11B10F)
		return GL_FLOAT;

	assert(false);
	return GL_INVALID_ENUM;
}

GLint
OGLTypes::asOGLInternalformat(TextureFormat format) noexcept
{
	switch (format)
	{
	case TextureFormat::STENCIL8:
		return GL_STENCIL_INDEX8;
	case TextureFormat::DEPTH_COMPONENT16:
		return GL_DEPTH_COMPONENT16;
	case TextureFormat::DEPTH_COMPONENT24:
		return GL_DEPTH_COMPONENT24;
	case TextureFormat::DEPTH_COMPONENT32:
		return GL_DEPTH_COMPONENT32F;
	case TextureFormat::DEPTH24_STENCIL8:
		return GL_DEPTH24_STENCIL8;
	case TextureFormat::DEPTH32_STENCIL8:
		return GL_DEPTH32F_STENCIL8;
	case TextureFormat::R8G8B8:
		return GL_RGB8;
	case TextureFormat::R8G8B8A8:
		return GL_RGBA8;
	case TextureFormat::R16G16B16:
		return GL_RGB16UI;
	case TextureFormat::R16G16B16A16:
		return GL_RGBA16UI;
	case TextureFormat::R16G16B16A16_SNORM:
		return GL_RGBA16_SNORM;
	case TextureFormat::R16G16B16F:
		return GL_RGB16F;
	case TextureFormat::R32G32B32F:
		return GL_RGB32F;
	case TextureFormat::R16G16B16A16F:
		return GL_RGBA16F;
	case TextureFormat::R32G32B32A32F:
		return GL_RGBA32F;
	case TextureFormat::SR8G8B8:
		return GL_SRGB8;
	case TextureFormat::SR8G8B8A8:
		return GL_SRGB8_ALPHA8;
	case TextureFormat::SRGB:
		return GL_SRGB;
	case TextureFormat::SRGBA:
		return GL_SRGB_ALPHA_EXT;
	case TextureFormat::R8:
		return GL_R8;
	case TextureFormat::R16F:
		return GL_R16F;
	case TextureFormat::R32F:
		return GL_R32F;
	case TextureFormat::RG16F:
		return GL_RG16F;
	case TextureFormat::RG32F:
		return GL_RG32F;
	case TextureFormat::R11G11B10F:
		return GL_R11F_G11F_B10F;
	case TextureFormat::RGB_DXT1:
		return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
	case TextureFormat::RGBA_DXT1:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case TextureFormat::RGBA_DXT3:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case TextureFormat::RGBA_DXT5:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case TextureFormat::RG_ATI2:
		return GL_COMPRESSED_RG_RGTC2;
	default:
		assert(false);
		return GL_INVALID_ENUM;
	}
}

GLenum
OGLTypes::asCompareFunction(CompareFunction func) noexcept
{
	switch (func)
	{
	case ray::GPU_NONE:
		return GL_NONE;
	case ray::GPU_LEQUAL:
		return GL_LEQUAL;
	case ray::GPU_EQUAL:
		return GL_EQUAL;
	case ray::GPU_GREATER:
		return GL_GREATER;
	case ray::GPU_LESS:
		return GL_LESS;
	case ray::GPU_GEQUAL:
		return GL_GEQUAL;
	case ray::GPU_NOTEQUAL:
		return GL_NOTEQUAL;
	case ray::GPU_ALWAYS:
		return GL_ALWAYS;
	case ray::GPU_NEVER:
		return GL_NEVER;
	default:
		assert(false);
		return GL_ALWAYS;
	}
}

GLenum
OGLTypes::asBlendFactor(BlendFactor func) noexcept
{
	switch (func)
	{
	case ray::GPU_ZERO:
		return GL_ZERO;
	case ray::GPU_ONE:
		return GL_ONE;
	case ray::GPU_DSTCOL:
		return GL_DST_COLOR;
	case ray::GPU_SRCCOLOR:
		return GL_SRC_COLOR;
	case ray::GPU_SRCALPHA:
		return GL_SRC_ALPHA;
	case ray::GPU_DSTALPHA:
		return GL_DST_ALPHA;
	case ray::GPU_ONEMINUSSRCCOL:
		return GL_ONE_MINUS_SRC_COLOR;
	case ray::GPU_ONEMINUSDSTCOL:
		return GL_ONE_MINUS_DST_COLOR;
	case ray::GPU_ONEMINUSSRCALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case ray::GPU_ONEMINUSDSTALPHA:
		return GL_ONE_MINUS_DST_ALPHA;
	case ray::GPU_CONSTANT_COLOR:
		return GL_CONSTANT_COLOR;
	case ray::GPU_CONSTANT_ALPHA:
		return GL_CONSTANT_ALPHA;
	case GPU_ONE_MINUS_CONSTANT_COLOR:
		return GL_CONSTANT_ALPHA;
	case GPU_ONE_MINUS_CONSTANT_ALPHA:
		return GL_CONSTANT_ALPHA;
	case GPU_SRC_ALPHA_SATURATE:
		return GL_SRC_ALPHA_SATURATE;
	default:
		assert(false);
		return GL_ZERO;
	}
}

GLenum
OGLTypes::asBlendOperation(BlendOperation blendop) noexcept
{
	switch (blendop)
	{
	case ray::GPU_ADD:
		return GL_FUNC_ADD;
	case ray::GPU_SUBSTRACT:
		return GL_FUNC_SUBTRACT;
	case ray::GPU_REVSUBTRACT:
		return GL_FUNC_REVERSE_SUBTRACT;
	default:
		assert(false);
		return GL_FUNC_ADD;
	}
}

GLenum
OGLTypes::asCullMode(CullMode mode) noexcept
{
	switch (mode)
	{
	case ray::GPU_CULL_NONE:
		return GL_NONE;
	case ray::GPU_CULL_FRONT:
		return GL_FRONT;
	case ray::GPU_CULL_BACK:
		return GL_BACK;
	case ray::GPU_CULL_FRONT_BACK:
		return GL_FRONT_AND_BACK;
	default:
		assert(false);
		return GL_NONE;
	}
}

GLenum
OGLTypes::asFillMode(FillMode mode) noexcept
{
#if !defined(EGLAPI)
	switch (mode)
	{
	case ray::PointMode:
		return GL_POINT;
	case ray::WireframeMode:
		return GL_LINE;
	case ray::SolidMode:
		return GL_FILL;
	default:
		assert(false);
		return GL_FILL;
	}
#else
	assert(false);
	return GL_INVALID_ENUM;
#endif
}

GLenum
OGLTypes::asStencilOperation(StencilOperation stencilop) noexcept
{
	switch (stencilop)
	{
	case ray::STENCILOP_KEEP:
		return GL_KEEP;
	case ray::STENCILOP_REPLACE:
		return GL_REPLACE;
	case ray::STENCILOP_INCR:
		return GL_INCR;
	case ray::STENCILOP_DECR:
		return GL_DECR;
	case ray::STENCILOP_ZERO:
		return GL_ZERO;
	case ray::STENCILOP_INCR_WRAP:
		return GL_INCR_WRAP;
	case ray::STENCILOP_DECR_WRAP:
		return GL_DECR_WRAP;
	default:
		assert(false);
		return GL_KEEP;
	}
}

OGLExtenstion::OGLExtenstion() noexcept
{
}

OGLExtenstion::~OGLExtenstion() noexcept
{
}

bool
OGLExtenstion::initExtensions() except
{
	if (initExtention) return 0;

#if !defined(EGLAPI)
	glewInit();

	OGLFeatures::ARB_bindless_texture = GLEW_ARB_bindless_texture ? true : false;
	OGLFeatures::ARB_vertex_array_object = GLEW_ARB_vertex_array_object ? true : false;
	OGLFeatures::ARB_vertex_attrib_binding = false; //GLEW_ARB_vertex_attrib_binding ? true : false;
	OGLFeatures::ARB_provoking_vertex = GLEW_ARB_provoking_vertex ? true : false;
	OGLFeatures::ARB_direct_state_access = GLEW_ARB_direct_state_access ? true : false;
	OGLFeatures::ARB_buffer_storage = GLEW_ARB_buffer_storage ? true : false;
	OGLFeatures::ARB_viewport_array = GLEW_ARB_viewport_array ? true : false;
	OGLFeatures::KHR_debug = GLEW_KHR_debug;
	OGLFeatures::NV_shader_buffer_load = false; //GLEW_NV_shader_buffer_load ? true : false;
	OGLFeatures::NV_vertex_buffer_unified_memory = false;//GLEW_NV_vertex_buffer_unified_memory ? true : false;

#endif

	initExtention = true;

	return initExtention;
}

void
OGLCheck::checkError() noexcept
{
#ifdef _DEBUG
	GLenum result = ::glGetError();
	if (GL_NO_ERROR != result)
	{
		switch (result)
		{
		case GL_INVALID_ENUM:
			std::cerr << "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			std::cerr << "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			std::cerr << "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			std::cerr << "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			std::cerr << "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			std::cerr << "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		default:
			assert(false);
		};
	}

	result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (GL_FRAMEBUFFER_COMPLETE != result)
	{
		switch (result)
		{
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cerr << "FBO:Incomplete attachment";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cerr << "FBO:Incomplete missing attachment";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cerr << "FBO:Unsupported";
			break;
#if !defined(EGLAPI)
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			std::cerr << "FBO:Incomplete draw buffer";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			std::cerr << "FBO:Incomplete read buffer";
			break;
#endif
		}
	}
#endif
}

_NAME_END