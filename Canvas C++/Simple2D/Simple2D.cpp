#include "Simple2D.h"


int ScreenWidth = 700;
int ScreenHeight = 500;

struct Quad
{
	Quad(float p[16], unsigned int i[6]);

	VertexBuffer vb;
	IndexBuffer ib;
	VertexArray va;
};

class Canvas
{
public:
	void Init(GLFWwindow* v);
	   

	void SetColor(double r, double g, double b);

	int AddShape(std::string& path);

	void ReSize(int w, int h);
	void Draw(int index, glm::mat4& matrix);

	GLFWwindow* ventana;

private:

	Renderer renderer;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<Quad> quad;

	std::vector<std::unique_ptr<Shape>> shapes;


	glm::mat4 proj;
	glm::mat4 view = glm::mat4(1.0f);
};

Canvas canvas;
double mouseX, mouseY;


bool mousePast[3];
bool mousePresent[3];

#pragma region
void SetColor(int r, int g, int b)
{
	canvas.SetColor(r / 255.0, g / 255.0, b / 255.0);
}

void DrawCircle(int x, int y, int r)
{
	DrawShape(0, x, y, r, r);
}

void DrawRect(int x, int y, int w, int h)
{
	DrawShape(1, x, y, w, h);
}
void DrawRect(int x, int y, int w)
{
	DrawShape(1, x, y, w, w);
}

void DrawLine(int x1, int y1, int x2, int y2, int w)
{
	double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	int x = (x2 + x1) / 2;
	int y = (y2 + y1) / 2;

	double angulo = atan2(y2 - y1, x2 - x1);

	DrawShape(1, x, y, length, w, angulo);
}

void DrawShape(int i, int x, int y, float w, float h, float r)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0));
	model = glm::rotate(model, r, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(w, h, 1));

	canvas.Draw(i, model);
}
void DrawShape(int i, int x, int y, float w, float h)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0));
	model = glm::scale(model, glm::vec3(w, h, 1));

	canvas.Draw(i, model);
}
void DrawShape(int i, int x, int y, float w)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0));
	model = glm::scale(model, glm::vec3(w, w, 1));

	canvas.Draw(i, model);
}

void Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void ReSize(GLFWwindow* v, int w, int h)
{
	ScreenWidth = w;
	ScreenHeight = h;

	canvas.ReSize(w, h);
}

int Width()
{
	return ScreenWidth;
}
int Height()
{
	return ScreenHeight;
}

bool Buttom(int x, int y, int r)
{
	DrawCircle(x, y, r);

	return MouseButtonDown(0) && (round(sqrt(pow(x - mouseX, 2) + pow(y - mouseY, 2))) < r / 2);
}

bool Buttom(int x, int y, int w, int h)
{
	DrawRect(x, y, w, h);
	return (MouseButtonDown(0) && mouseX > x - w / 2 && mouseY > y - h / 2 && mouseX < x + w / 2 && mouseY < y + h / 2);
}

#pragma endregion Utility


#pragma region

void Canvas::Init(GLFWwindow* v)
{
	ventana = v;

	float posiciones[16] = { -0.5f, -0.5f, 0.0f, 0.0f,
							0.5f, -0.5f, 1.0f, 0.0f,
							0.5f,  0.5f, 1.0f, 1.0f,
						   -0.5f,  0.5f, 0.0f, 1.0f };

	unsigned int indices[6] = { 0, 1, 2,
								2, 3, 0 };

	quad = std::make_unique<Quad>(posiciones, indices);


	shader = std::make_unique<Shader>("Simple2D/res/shaders/Basic.shader");
	shapes.push_back(std::make_unique<Shape>("Simple2D/res/texturas/ChernoLogo.png"));
	shapes.push_back(std::make_unique<Shape>("Simple2D/res/texturas/descarga.png"));
}

void Canvas::SetColor(double r, double g, double b)
{
	shader->Bind();
	shader->SetUniform4f("color", r, g, b, 1.0f);
}

void Canvas::Draw(int index, glm::mat4& model)
{
	glm::mat4 mvp = proj * view * model;

	shader->Bind();
	shapes[index]->Bind();
	shader->SetUniform1i("Texture", 0);
	shader->SetUniformMat4f("MVP", mvp);

	renderer.Draw(quad->va, quad->ib, *shader);
}

void Canvas::ReSize(int w, int h)
{
	proj = glm::ortho(-w / 2.0f, w / 2.0f, -h / 2.0f, h / 2.0f, -.1f, .1f);
	glViewport(0, 0, w, h);
}

int Canvas::AddShape(std::string& path) 
{
	shapes.push_back(std::make_unique<Shape>(path));

	return shapes.size() - 1;
}
#pragma endregion Canvas


#pragma region



void update(GLFWwindow* ventana)
{
	glfwGetCursorPos(ventana, &mouseX, &mouseY);

	int w, h;
	glfwGetFramebufferSize(ventana, &w, &h);
	mouseX -= w / 2;
	mouseY -= h / 2;
	mouseY = -mouseY;

	for (int j = 0; j < 3; j++)
	{
		mousePast[j] = mousePresent[j];
	}
}


bool MouseButtonDown(int i)
{
	return !mousePast[i] && mousePresent[i];
}
bool MouseButtonUp(int i)
{
	return mousePast[i] && !mousePresent[i];
}
bool MouseButton(int i)
{
	return mousePresent[i];
}
int MouseX()
{
	return mouseX;
}
int MouseY()
{
	return mouseY;
}

void key_callback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(w, GLFW_TRUE);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		mousePresent[button] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		mousePresent[button] = false;
	}
}


#pragma endregion Input


//Quad

Quad::Quad(float p[16], unsigned int i[6]) : vb(p, 16 * sizeof(float)), ib(i, 6)
{
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
}


// Other


GLFWwindow* InitOpenGL(int w, int h, std::string name = "Hola Mundo")
{
	if (!glfwInit())
	{
		std::cout << "Error al iniciar GLFW" << std::endl;
		glfwTerminate();
	}

	GLFWwindow* ventana = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
	if (!ventana)
	{
		std::cout << "Error al crear ventana" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(ventana);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error al iniciar GLWE" << std::endl;
		glfwTerminate();
	}

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// CallBacks

	//glfwSetMouseButtonCallback(ventana, mouse_button_callback);
	//glfwSetFramebufferSizeCallback(ventana, framebuffer_size_callback);
	glDebugMessageCallback(GLerrorCallback, nullptr);

	return ventana;
}


void Setup();
void Loop();

int main()
{
	auto v = InitOpenGL(ScreenWidth, ScreenHeight);
	

	canvas.Init(v);
	canvas.ReSize(ScreenWidth, ScreenHeight);

	// Callbacks

	glfwSetFramebufferSizeCallback(v, ReSize);
	glfwSetMouseButtonCallback(v, mouse_button_callback);
	glfwSetKeyCallback(v, key_callback);


	Setup();

	while (!glfwWindowShouldClose(v))
	{
		Loop();

		update(v);

		glfwSwapBuffers(v);	

		glfwPollEvents();
	}


	glfwDestroyWindow(v);
	glfwTerminate();

	return 0;
}