

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>


// Main code
int main(int, char**)
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Setup window
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL2_Init();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float f = 0.0f;
	// Main loop
	bool done = false;
	while (!done)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		
		
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		ImGui::End();
		
		// Rendering
		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}
	//SDL_Delay(5000);

	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
