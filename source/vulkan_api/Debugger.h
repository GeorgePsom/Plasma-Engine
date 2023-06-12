#pragma once

class Debugger
{
public:
	Debugger(bool value) : enableValidationLayers(value) {}
	void SetValidationLayerFlag(bool value);
	bool CheckValidationLayerSupport();
	inline bool GetValidationFlag() { return enableValidationLayers; }
	const std::vector<const char*>* GetValidationLayers()
	{
		return &validationLayers;
	}
private:
	bool enableValidationLayers;
	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};
};