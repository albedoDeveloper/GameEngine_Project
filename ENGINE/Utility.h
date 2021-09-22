#ifdef _DEBUG

#define CHECK_GL_ERROR() \
	if(glGetError() == GL_INVALID_ENUM){printf("GL_INVALID_ENUM\n");__debugbreak();} \
	else if(glGetError() == GL_INVALID_VALUE){printf("GL_INVALID_VALUE\n");__debugbreak();} \
	else if(glGetError() == GL_INVALID_OPERATION){printf("GL_INVALID_OPERATION\n");__debugbreak();} \
	else if(glGetError() == GL_INVALID_FRAMEBUFFER_OPERATION){printf("GL_INVALID_FRAMEBUFFER_OPERATION\n"); __debugbreak();} \
	else if(glGetError() == GL_OUT_OF_MEMORY){printf("GL_OUT_OF_MEMORY\n");__debugbreak();} \
	else if(glGetError() == GL_STACK_UNDERFLOW){printf("GL_STACK_UNDERFLOW\n");__debugbreak();} \
	else if(glGetError() == GL_STACK_OVERFLOW){printf("GL_STACK_OVERFLOW\n");__debugbreak();}

#else

#define CHECK_GL_ERROR() ;

#endif
