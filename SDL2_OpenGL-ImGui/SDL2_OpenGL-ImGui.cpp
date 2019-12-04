/*
 *   Author:  Michael McGuire
 *  Purpose:  looking at ImGui to develop GUI's, this toolset utilizes SDL2 and OpenGL to render beautiful, graphics enhanced user interfaces 
 * Language:  c++
 */

// headers
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"


int main(int, char**)
{
	// initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		// if issue initializing SDL2 print error message to console
		printf("Error: %s\n", SDL_GetError());
		// end main
		return -1;
	}

	// create SDL window
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
	// create openGL context for display on SDL2 window
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	// enable vsync
	SDL_GL_SetSwapInterval(1);

	// create ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup binding for ImGui and OpenGL
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL2_Init();

	// create a color
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// this is the variable we are controlling with the slider
	float f = 0.0f;

	// real-time loop, ImGui runs with a real-time paradigm (vs. event driven)
	bool done = false;
	while (!done)
	{
		// use SDL2 to pull for events such as key presses
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
		}

		// create ImGui frame
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		
		// make window with ImGui
		ImGui::Begin("Hello, world!");

		// add this text to ImGui window
		ImGui::Text("This is some useful text.");               
		// create a slider that update the variable f, this slider has a min value and max value
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::End();

	
		//ImGui::Checkbox("Demo Window", &show_demo_window);   
		//ImGui::Checkbox("Another Window", &show_another_window);
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		
		
		// render the ImGui window
		ImGui::Render();
		// make a viewport
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		// place ImGui rendered image on SDL2 window
		SDL_GL_SwapWindow(window);
	}

	// destroy ImGui bindings and objects
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// detete context
	SDL_GL_DeleteContext(gl_context);
	// remove SDL2 window from memory
	SDL_DestroyWindow(window);
	// quit SDL2
	SDL_Quit();

	// end main
	return 0;
}
