/******************************************************************************\
| OpenGL 4 Example Code.                                                       |
| Accompanies written series "Anton's OpenGL 4 Tutorials"                      |
| Email: anton at antongerdelan dot net                                        |
| First version 27 Jan 2014                                                    |
| Copyright Dr Anton Gerdelan, Trinity College Dublin, Ireland.                |
| See individual libraries for separate legal notices                          |
|******************************************************************************|
| "Hello Triangle". Just the basics.                                           |
| If you're on Mac un-comment the version number code at the beginning. It     |
| will give you the latest, even if you say 3.2!                               |
| This uses the libraries GLEW and GLFW3 to start GL. Download and compile     |
| these first. Linking them might be a pain, but you'll need to master this.   |
|                                                                              |
| I wrote this so that it compiles in pedantic ISO C90, to show that it's      |
| easily done. I usually use minimalist C++ though, for tidier-looking maths   |
| functions.                                                                   |
\******************************************************************************/
#include <GL/glew.h> /* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
//
//int main () {
//	GLFWwindow* window = NULL;
//	const GLubyte* renderer;
//	const GLubyte* version;
//	GLuint vao;
//	GLuint vbo;
//	/* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
//	*/
//	GLfloat points[] = {
//		 0.0f,	0.5f,	0.0f,
//		 0.5f, -0.5f,	0.0f,
//		-0.5f, -0.5f,	0.0f
//	};
//	/* these are the strings of code for the shaders
//	the vertex shader positions each vertex point */
//	const char* vertex_shader =
//	"#version 410\n"
//	"in vec3 vp;"
//	"void main () {"
//	"	gl_Position = vec4 (vp, 1.0);"
//	"}";
//	/* the fragment shader colours each fragment (pixel-sized area of the
//	triangle) */
//	const char* fragment_shader =
//	"#version 410\n"
//	"out vec4 frag_colour;"
//	"void main () {"
//	"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
//	"}";
//	/* GL shader objects for vertex and fragment shader [components] */
//	GLuint vs, fs;
//	/* GL shader programme object [combined, to link] */
//	GLuint shader_programme;
//
//	/* start GL context and O/S window using the GLFW helper library */
//	if (!glfwInit ()) {
//		fprintf (stderr, "ERROR: could not start GLFW3\n");
//		return 1;
//	} 
//
//	/* change to 3.2 if on Apple OS X */
//	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
//	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	window = glfwCreateWindow (
//		640, 480, "Hello Triangle", NULL, NULL
//	);
//	if (!window) {
//		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
//		glfwTerminate();
//		return 1;
//	}
//	glfwMakeContextCurrent (window);
//	/* start GLEW extension handler */
//	glewExperimental = GL_TRUE;
//	glewInit ();
//
//	/* get version info */
//	renderer = glGetString (GL_RENDERER); /* get renderer string */
//	version = glGetString (GL_VERSION); /* version as a string */
//	printf ("Renderer: %s\n", renderer);
//	printf ("OpenGL version supported %s\n", version);
//
//	/* tell GL to only draw onto a pixel if the shape is closer to the viewer */
//	glEnable (GL_DEPTH_TEST); /* enable depth-testing */
//	glDepthFunc (GL_LESS);/*depth-testing interprets a smaller value as "closer"*/
//
//	/* a vertex buffer object (VBO) is created here. this stores an array of data
//	on the graphics adapter's memory. in our case - the vertex points */
//	glGenBuffers (1, &vbo);
//	glBindBuffer (GL_ARRAY_BUFFER, vbo);
//	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
//	
//	/* the vertex array object (VAO) is a little descriptor that defines which
//	data from vertex buffer objects should be used as input variables to vertex
//	shaders. in our case - use our only VBO, and say 'every three floats is a 
//	variable' */
//	glGenVertexArrays (1, &vao);
//	glBindVertexArray (vao);
//	glEnableVertexAttribArray (0);
//	glBindBuffer (GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL); 
//  // Jiaqi.
//  // http://alfonse.bitbucket.org/oldtut/Basics/Tut01%20Following%20the%20Data.html 
//  // This is a very good tutorial. 
//	
//	/* here we copy the shader strings into GL shaders, and compile them. we then
//	create an executable shader 'program' and attach both of the compiled shaders.
//	we link this, which matches the outputs of the vertex shader to the inputs of
//	the fragment shader, etc. and it is then ready to use */
//	vs = glCreateShader (GL_VERTEX_SHADER);
//	glShaderSource (vs, 1, &vertex_shader, NULL);
//	glCompileShader (vs);
//	fs = glCreateShader (GL_FRAGMENT_SHADER);
//	glShaderSource (fs, 1, &fragment_shader, NULL);
//	glCompileShader (fs);
//	shader_programme = glCreateProgram ();
//	glAttachShader (shader_programme, fs);
//	glAttachShader (shader_programme, vs);
//	glLinkProgram (shader_programme);
//	
//	/* this loop clears the drawing surface, then draws the geometry described by
//	the VAO onto the drawing surface. we 'poll events' to see if the window was
//	closed, etc. finally, we 'swap the buffers' which displays our drawing surface
//	onto the view area. we use a double-buffering system which means that we have
//	a 'currently displayed' surface, and 'currently being drawn' surface. hence
//	the 'swap' idea. in a single-buffering system we would see stuff being drawn
//	one-after-the-other */
//	while (!glfwWindowShouldClose (window)) {
//		/* wipe the drawing surface clear */
//		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glUseProgram (shader_programme);
//		glBindVertexArray (vao);
//		/* draw points 0-3 from the currently bound VAO with current in-use shader*/
//		glDrawArrays (GL_TRIANGLES, 0, 3);
//		/* update other events like input handling */
//		glfwPollEvents ();
//		/* put the stuff we've been drawing onto the display */
//		glfwSwapBuffers (window);
//	}
//	
//	/* close GL context and any other GLFW resources */
//	glfwTerminate();
//	return 0;
//}

#include <math.h>

//#define BUFFER_OFFSET(offset)  ((GLvoid*) 0 + offset)
#define BUFFER_OFFSET(offset)  ((char*) 0 + offset)
#define NumberOf(array)        (sizeof(array)/sizeof(array[0]))

typedef struct {
    GLfloat x, y, z;
} vec3;


typedef struct {
    vec3     xlate;   /* Translation */
    GLfloat  angle;
    vec3     axis;
} XForm;

enum { Cube, Cone, NumVAOs };
GLuint   VAO[NumVAOs];
GLenum   PrimType[NumVAOs];
GLsizei  NumElements[NumVAOs];
XForm    Xform[NumVAOs] = {
    { { -2.0, 0.0, 0.0 }, 0.0, { 0.0, 1.0, 0.0 } },
    { {  0.0, 0.0, 2.0 }, 0.0, { 1.0, 0.0, 0.0 } }
};
GLfloat  Angle = 0.0;

void
init()
{
    enum { Vertices, Colors, Elements, NumVBOs };
    GLuint  buffers[NumVBOs];

    glGenVertexArrays(NumVAOs, VAO);

    {
        GLfloat  cubeVerts[][3] = {
            { -1.0, -1.0, -1.0 },
            { -1.0, -1.0,  1.0 },
            { -1.0,  1.0, -1.0 },
            { -1.0,  1.0,  1.0 },
            {  1.0, -1.0, -1.0 },
            {  1.0, -1.0,  1.0 },
            {  1.0,  1.0, -1.0 },
            {  1.0,  1.0,  1.0 },
        };

        GLfloat  cubeColors[][3] = {
            {  0.0,  0.0,  0.0 },
            {  0.0,  0.0,  1.0 },
            {  0.0,  1.0,  0.0 },
            {  0.0,  1.0,  1.0 },
            {  1.0,  0.0,  0.0 },
            {  1.0,  0.0,  1.0 },
            {  1.0,  1.0,  0.0 },
            {  1.0,  1.0,  1.0 },
        };

        GLubyte  cubeIndices[] = {
            0, 1, 3, 2,
            4, 6, 7, 5,
            2, 3, 7, 6,
            0, 4, 5, 1,
            0, 2, 6, 4,
            1, 5, 7, 3
        };

        glBindVertexArray(VAO[Cube]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts),
             cubeVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors),
            cubeColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
            buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        PrimType[Cube] = GL_QUADS;
        NumElements[Cube] = NumberOf(cubeIndices);
    }

    {
        int i, idx;
        float  dTheta;
#define NumConePoints  36
        /* We add one more vertex for the cone's apex */
        GLfloat  coneVerts[NumConePoints+1][3] = {
            {0.0, 0.0, 1.0}
        };
        GLfloat  coneColors[NumConePoints+1][3] = {
            {1.0, 1.0, 1.0}
        };
        GLubyte  coneIndices[NumConePoints+1];

        dTheta = 2*M_PI / (NumConePoints - 1);
        idx = 1;
        for (i = 0; i < NumConePoints; ++i, ++idx) {
            float theta = i*dTheta;
            coneVerts[idx][0] = cos(theta);
            coneVerts[idx][1] = sin(theta);
            coneVerts[idx][2] = 0.0;

            coneColors[idx][0] = cos(theta);
            coneColors[idx][1] = sin(theta);
            coneColors[idx][2] = 0.0;

            coneIndices[idx] = idx;
        }

        glBindVertexArray(VAO[Cone]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts),
            coneVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors),
            coneColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
            buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);

        PrimType[Cone] = GL_TRIANGLE_FAN;
        NumElements[Cone] = NumberOf(coneIndices);
    }

    glEnable(GL_DEPTH_TEST);
}

void
display()
{
    int  i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(Angle, 0.0, 1.0, 0.0);

    for (i = 0; i < NumVAOs; ++i) {
        glPushMatrix();
        glTranslatef(Xform[i].xlate.x, Xform[i].xlate.y,
            Xform[i].xlate.z);
        glRotatef(Xform[i].angle, Xform[i].axis.x,
            Xform[i].axis.y, Xform[i].axis.z);
        glBindVertexArray(VAO[i]);
        glDrawElements(PrimType[i], NumElements[i],
            GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}