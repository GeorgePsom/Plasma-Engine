#pragma once




// #if def ANDROID TODO

#define VK_CHECK_RESULT(f)													\
{																			\
	VkResult res = (f);														\
	if (res != VK_SUCCESS)													\
	{																		\
		std::cout << "Fatal : VkResult is \"" << Tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__  << "\n";	\
	}																		\
}																			\


const std::string getAssetPath();
namespace Tools
{
	/** @brief Disable message boxes on fatal errors */
	extern bool errorModeSilent;

	/** @brief Returns an error code as a string */
	std::string errorString(VkResult errorCode);

	/** @brief Display error and exit on fatal error*/
	void exitFatal(const std::string& message, int32_t exitCode);

	/** @brief Display error and exit on fatal error*/
	void exitFatal(const std::string& message, VkResult resultCode);
	
}