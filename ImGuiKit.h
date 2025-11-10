#pragma once
#pragma warning(disable : 4251)
#pragma warning(disable : 4005)

// clang-format off

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(_MSC_VER)
	#if defined(IMGUIKIT_EXPORTS)
		#define IGFD_API __declspec(dllexport)
		#define IMGUI_API __declspec(dllexport)
		#define IMPLOT_API __declspec(dllexport)
		#define IMGUI_IMPL_API __declspec(dllexport)
	#elif defined(BUILD_IMGUI_PACK_SHARED_LIBS)
		#define IGFD_API __declspec(dllimport)
		#define IMGUI_API __declspec(dllimport)
		#define IMPLOT_API __declspec(dllimport)
		#define IMGUI_IMPL_API __declspec(dllimport)
	#else
		#define IGFD_API
		#define IMGUI_API
		#define IMPLOT_API
		#define IMGUI_IMPL_API
	#endif
#else
	#define IGFD_API
	#define IMGUI_API
	#define IMPLOT_API
	#define IMGUI_IMPL_API
#endif

#ifdef IMGUI_USER_CONFIG
	#include IMGUI_USER_CONFIG
#endif

#include <3rdParty/ImGui_Docking/imgui.h>
#include <3rdParty/ImGui_Docking/imgui_internal.h>

#ifdef USE_IMPLOT
	#include <3rdParty/ImGui_ImPlot/implot.h>
	#include <3rdParty/ImGui_ImPlot/implot_internal.h>
#endif

#ifdef USE_IM_TOOLS
	#include <3rdParty/ImGui_Tools/ImWidgets.h>
	#include <3rdParty/ImGui_Tools/Messaging.h>
	#ifndef ILAYOUT_PANE_INCLUDE
		#include <3rdParty/ImGui_Tools/ILayoutPane.h>
	#else
		#include ILAYOUT_PANE_INCLUDE
	#endif
	#include <3rdParty/ImGui_Tools/LayoutManager.h>
	#include <3rdParty/ImGui_Tools/ImGuiThemeHelper.h>
	#include <3rdParty/ImGui_Tools/ImCanvasWip.h>
	#include <3rdParty/ImGui_Tools/ImCanvas.h>
	#include <3rdParty/ImGui_Tools/ImCodeEditor.h>
#endif


#ifdef USE_IMGUI_FILE_DIALOG
	#include <3rdParty/ImGui_FileDialog/ImGuiFileDialog.h>
#endif


/*// others missing math function from imgui
static inline ImVec4 operator*(const float& lhs, const ImVec4 rhs) {
    return ImVec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.y, lhs * rhs.w);
}

static inline ImVec4 operator*(const ImVec4& lhs, const float rhs) {
    return ImVec4(lhs.x * rhs, lhs.y * rhs, lhs.y * rhs, lhs.w * rhs);
}*/

// clang-format on
