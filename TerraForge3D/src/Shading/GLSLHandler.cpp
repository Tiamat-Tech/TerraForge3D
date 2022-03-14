#include "Shading/GLSLHandler.h"

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

static std::string dashes = "---------------------------";

#define DASHIT(x) dashes + x + dashes


GLSLUniform::GLSLUniform(std::string name, std::string type, std::string value)
	:name(name), type(type), value(value), comment("")
{
}

GLSLUniform::~GLSLUniform()
{
}

std::string GLSLUniform::GenerateGLSL()
{
	std::stringstream c;
	c << "uniform " << type << " " << name;

	if(value.size() > 0)
	{
		c << " = " << value;
	}

	c << ";";

	if(comment.size() > 0)
	{
		c << " // " << comment;
	}

	return c.str();
}

GLSLMacro::GLSLMacro(std::string name, std::string value, std::string comment)
	:name(name), value(value), comment(comment)
{
}

GLSLMacro::~GLSLMacro()
{
}

std::string GLSLMacro::GenerateGLSL()
{
	std::stringstream c;

	if(comment.size() > 0)
	{
		c << "// " << comment << "\n";
	}

	c << "#define " << name << " " << value;
	return c.str();
}

GLSLLine::GLSLLine(std::string line, std::string comment)
	: line(line), comment(comment)
{
}

GLSLLine::~GLSLLine()
{
}

std::string GLSLLine::GenerateGLSL()
{
	std::stringstream c;
	c << line;

	if(comment.size() > 0)
	{
		c << " // " << comment;
	}

	return c.str();
}

GLSLFunction::GLSLFunction(std::string name, std::string params, std::string returnType)
	: name(name), returnType(returnType), params(params), comment("")
{
	lines.clear();
}

GLSLFunction::~GLSLFunction()
{
}

std::string GLSLFunction::GenerateGLSL()
{
	std::stringstream c;

	if(comment.size() > 0)
	{
		c << comment << "\n";
	}

	c << returnType << " " << name << "(" << params << ")" << "\n";
	c << "{\n";

	for(GLSLLine &line : lines)
	{
		c << "\t" << line.GenerateGLSL() << "\n";
	}

	c << "}";
	return c.str();
}

void GLSLFunction::AddLine(GLSLLine line)
{
	lines.push_back(line);
}

GLSLHandler::GLSLHandler(std::string name)
	: name(name)
{
}

GLSLHandler::~GLSLHandler()
{
}

std::string GLSLHandler::GenerateGLSL()
{
	code = "";
	std::stringstream c;
	c << "#version " << version << "\n\n";
	c << "// This code has benn generated by TerraForge3D Shader Generator\n";
	c << "// Shader Name : " << name << "\n";
	c << "\n\n";

	if(topLines.size() > 0)
	{
		c << "// " << DASHIT("MISC") << "\n";

		for(GLSLLine &line : topLines)
		{
			c << line.GenerateGLSL() << "\n";
		}

		c << "\n\n";
	}

	if(macros.size() > 0)
	{
		c << "// " << DASHIT("MACROS") << "\n";

		for(GLSLMacro macro : macros)
		{
			c << macro.GenerateGLSL() << "\n";
		}

		c << "\n\n";
	}

	if(uniforms.size() > 0)
	{
		c << "//" << DASHIT("UNIFORMS") << "\n";

		for(GLSLUniform uniform : uniforms)
		{
			c << uniform.GenerateGLSL() << "\n";
		}

		c << "\n\n";
	}

	if(functions.size() > 0)
	{
		c << "//" << DASHIT("FUNCTIONS") << "\n";

		for(GLSLFunction function : functions)
		{
			c << "// " << function.name << "\n";
			c << function.GenerateGLSL() << "\n\n";
		}
	}

	code = c.str();
	return code;
}

void GLSLHandler::AddTopLine(GLSLLine line)
{
	topLines.push_back(line);
}

void GLSLHandler::AddUniform(GLSLUniform uniform)
{
	uniforms.push_back(uniform);
}

void GLSLHandler::AddMacro(GLSLMacro macro)
{
	macros.push_back(macro);
}

void GLSLHandler::AddFunction(GLSLFunction function)
{
	if(!HasFunction(function.name))
	{
		functions.push_back(function);
		functionNames.push_back(function.name);
	}
}

bool GLSLHandler::HasFunction(std::string name)
{
	return std::find(functionNames.begin(), functionNames.end(), name) != functionNames.end();
}

void GLSLHandler::Clear()
{
	uniforms.clear();
	functions.clear();
	functionNames.clear();
	macros.clear();
	topLines.clear();
	code = "";
}