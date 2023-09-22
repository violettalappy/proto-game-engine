#pragma once

#include <raylib.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <rlImGui.h>

#include "fmt/format.h"

#include "ProgramProcessor.h"
#include "ProgramConfig.h"

//Dear Imgui and RmlUi

class ProgramEditor {
private:
	mutable ProgramProcessor m_processor;
	mutable ProgramConfig m_config;		
public:
	ProgramEditor();
	~ProgramEditor();
public:
	ProgramConfig GetConfig() const {
		return m_config;
	}
	void SetConfig(ProgramConfig arg_config) {
		m_config = arg_config;
	}
	void SetProcessor(ProgramProcessor arg_processor) {
		m_processor = arg_processor;
	}
public:
	void Start();
	void Update(float arg_dt, float arg_unscaledDt);
	void Terminate();
private:
	static void ShowWorkspaceScene(bool* p_open);
	static void ShowWorkspaceGame(bool* p_open);
private:
	static void ShowOverlay(bool* arg_status);
	static void ShowAboutWindow(bool* arg_status);
	static void ShowContentDrawer(bool* arg_status);
public:
	static void EnableContentDrawer(bool* arg_status);
	static void DisableContentDrawer(bool* arg_status);
};