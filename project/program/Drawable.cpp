#include"Drawable.h"
#include"system_Renderer.h"

Drawable::Drawable(int layer)
	:layer_(layer), isVisible_(Flag::On)
{
	RendererSystem::Instance().RegisterRenderer(this);
}