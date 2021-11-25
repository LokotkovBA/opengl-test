#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/math/mymath.h"

#include "src/graphics/buffers/allbuffers.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/sprite.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"

#include "src/utils/timer.h"
#include "src/graphics/texture.h"


#define RESOLUTION_WIDTH 960
#define RESOLUTION_HEIGHT 540
#define RESOLUTION_SCALE_WIDTH 32.0f
#define RESOLUTION_SCALE_HEIGHT 18.0f
#define BATCHRENDERER 1
#define SPRITE_INCREMENT 0.1f
#define SPRITE_SCALE .09f
#if 1
int main()
{
	using namespace GE;
	using namespace graphics;
	using namespace mymath;

	Window window("First", RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
	//glClearColor(1.0f,1.0f,1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, RESOLUTION_SCALE_WIDTH, 0.0f, RESOLUTION_SCALE_HEIGHT, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert","src/shaders/basic.frag");
	Shader& shader = *s;

	srand(time(NULL));

	//Texture texture1("test3.png");
	//Texture texture("test4.png");
	//texture.bind();
	//texture1.bind();

	TileLayer layer(&shader);

#if BATCHRENDERER
	BatchRenderer2D renderer;
	for (float y = -9.0f; y < 9.0f; y+= SPRITE_INCREMENT)
	{
		for (float x = -16.0f; x < 16.0f; x+= SPRITE_INCREMENT)
		{
			layer.add(new Sprite(x, y, SPRITE_SCALE, SPRITE_SCALE, mymath::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else
	StaticSprite sprite1(5, 5, 4, 4, mymath::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 3, 3, mymath::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
	for (float y = 0; y < 9.0f; y+= SPRITE_INCREMENT)
	{
		for (float x = 0; x < 16.0f; x+= SPRITE_INCREMENT)
		{
			sprites.push_back(new StaticSprite(x, y, SPRITE_SCALE, SPRITE_SCALE, mymath::vec4(rand() % 1000 / 1000.0f, 0, 1, 1),shader));
		}
	}
#endif

	float widthFactor = ((float)RESOLUTION_SCALE_WIDTH / (float)RESOLUTION_WIDTH);
	float heightFactor = RESOLUTION_SCALE_HEIGHT / RESOLUTION_HEIGHT;
	vec2 curMousePos = vec2();
	vec2 lastMousePos = vec2();
	int i = 0;
	shader.enable();
	//shader.setUnfirm1i("tex", 0);
	//shader.setUniformMat4("pr_matrix", mymath::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time;
	float timer = 0;
	int frames = 0;
	
	while (!window.closed())
	{
		window.clear();
		curMousePos = window.getMousePosition();
		if (lastMousePos != curMousePos)
		{
			
			curMousePos.x *= widthFactor;
			curMousePos.x -= 16.0f;
			curMousePos.y *= (.0f - heightFactor);
			curMousePos.y += 9.0f;
			shader.enable();
			
			shader.setUnfirm2f("light_pos", curMousePos);
		}

		layer.render();
	
		window.update();
		frames++;

		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	return 0;
}
#else
int main()
{
	const char* filename = "test.png";
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return 1;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return 2;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);



	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return 3;
	
	std::map<unsigned int, GLuint> m_texID;
	GLenum image_format = GL_RGB;		//format the image is in
	GLint internal_format = GL_RGB;		//format to store the image in
	GLint level = 0;					//mipmapping level
	GLint border = 0;					//border size

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	//store the texture ID mapping
	m_texID[0] = gl_texID;
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		border, image_format, GL_UNSIGNED_BYTE, bits);

	

	unsigned int pitch = FreeImage_GetPitch(dib);
	unsigned int bpp = FreeImage_GetBPP(dib);
	for (int y = 0; y < height; y++)
	{
		BYTE* pixel = (BYTE*)bits;
		for (int i = 0; i < width; i++)
		{
			std::cout << (int) pixel[FI_RGBA_RED] << ", " << (int)pixel[FI_RGBA_GREEN] << ", " << (int)pixel[FI_RGBA_BLUE]  << std::endl;
			pixel += 3;
		}
		bits += pitch;
	}

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);
	

	//return success
	return 0;
}
#endif 

