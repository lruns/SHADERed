#pragma once
#include <SDL2/SDL.h>
#include <SHADERed/Objects/InputLayout.h>
#include <SHADERed/Objects/PluginAPI/Plugin.h>
#include <SHADERed/Objects/ShaderVariable.h>
#include <string>
#include <vector>

#define CURRENT_PLUGINAPI_VERSION 2

namespace ed {
	class InterfaceManager;
	class GUIManager;

	class PluginManager {
	public:
		void Init(InterfaceManager* data, GUIManager* ui); // load all the plugins here
		void Destroy();									   // destroy all the plugins
		void Update(float delta);

		void BeginRender();
		void EndRender();

		IPlugin* GetPlugin(const std::string& plugin);
		std::string GetPluginName(IPlugin* plugin);
		int GetPluginVersion(const std::string& plugin);
		int GetPluginAPIVersion(const std::string& plugin);
		bool IsActive(const std::string& plugin);

		inline const std::vector<std::string>& GetPluginList() { return m_names; }

		void ShowCustomMenu();
		void ShowMenuItems(const std::string& menu);
		void ShowContextItems(const std::string& menu, void* owner = nullptr, void* extraData = nullptr);
		void ShowContextItems(IPlugin* plugin, const std::string& menu, void* owner = nullptr);
		void ShowOptions(const std::string& searchString = "");

		void HandleDropFile(const char* filename);

		bool ShowSystemVariables(PluginSystemVariableData* data, ShaderVariable::ValueType type);
		bool ShowVariableFunctions(PluginFunctionData* data, ShaderVariable::ValueType type);

		std::vector<InputLayoutItem> BuildInputLayout(IPlugin* plugin, const char* itemName);

		void OnEvent(const SDL_Event& e);

		inline const std::vector<IPlugin*>& Plugins() { return m_plugins; }

		inline const std::vector<std::string>& GetIncompatiblePlugins() { return m_incompatible; }

	private:
		std::vector<void*> m_proc;
		std::vector<IPlugin*> m_plugins;
		std::vector<bool> m_isActive;
		std::vector<std::string> m_names;
		std::vector<int> m_pluginVersion, m_apiVersion;

		
		std::vector<std::string> m_incompatible;
	};
}