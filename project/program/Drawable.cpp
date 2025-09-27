#include"Drawable.h"
#include"system_Renderer.h"

Drawable::Drawable(int layer)
	:layer_(layer), isVisible_(Flag::On)
{

}

void Drawable::AddRegister()
{
	RendererSystem::Instance().RegisterRenderer(shared_from_this());
}
