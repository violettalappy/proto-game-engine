#include "ProgramRaylib.h"

ProgramRaylib::ProgramRaylib() {		
}

ProgramRaylib::~ProgramRaylib() {		
}

void ProgramRaylib::SetupConfig() {
	bool canIniLoadSuccess = false;
	if (canIniLoadSuccess) {
		//setup if detect file
		// TODO: if detect programconfig.ini, set up
	}
	else {
		m_config.SetProgramName("ENGINEProgram");
		m_config.SetScreenWidth(1600);
		m_config.SetScreenHeight(900);
		m_config.SetTargetFps(KFpsTarget::K_60);
		m_config.SetRefreshRate(KRefeshRate::K_30);
	}	
}

void ProgramRaylib::Init() {
	//--SETUP CONFIG & SUB SYSTEMS--
	SetupConfig();
	fmt::println(GetConfig().GetProgramName());
	fmt::println("Violetta Lappy: Setup Global Config - DONE [O]");

	m_processor.SetConfig(GetConfig());
	m_editor.SetConfig(GetConfig());
	m_render.SetConfig(GetConfig());
	fmt::println("Violetta Lappy: Setup All Services with Global Config - DONE [O]");

	m_editor.SetProcessor(m_processor);
	fmt::println("Violetta Lappy: Setup All Individual Services - DONE [O]");
	
	//--SYSTEM DO NOT CHANGE UNLESS YOU KNOW WHAT TO DO--		
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
	InitWindow(GetConfig().GetScreenWidth()
		, GetConfig().GetScreenHeight()
		, GetConfig().GetProgramName().c_str());
	SetTargetFPS(GetConfig().GetTargetFps());		
	rlImGuiSetup(true);

	//--ADD HERE--
	m_processor.Start();
	m_editor.Start();
	m_render.Start();
}

void ProgramRaylib::Run(float arg_dt, float arg_unscaledDt) {
	BeginDrawing();	
	rlImGuiBegin();

	//Update all services here	
	m_processor.Update(arg_dt, arg_unscaledDt);
	m_editor.Update(arg_dt, arg_unscaledDt);
	m_render.Update(arg_dt, arg_unscaledDt);

	rlImGuiEnd();
	EndDrawing();
}

void ProgramRaylib::Close() {
	//Terminate system by reverse order
	m_render.Terminate();
	m_editor.Terminate();
	m_processor.Terminate();
	
	//--SYSTEM DO NOT CHANGE UNLESS YOU KNOW WHAT TO DO--
	rlImGuiShutdown();
	CloseWindow();

	fmt::println("Violetta Lappy: ENGINE Shutdown Success [O]");
}
