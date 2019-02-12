#include <Atrc/Lib/Core/Renderer.h>

#include <Atrc/Editor/FilmRTReporter.h>
#include <Atrc/Editor/SceneRenderer.h>

SceneRenderer::SceneRenderer()
    : renderer_(nullptr), sampler_(nullptr), filmFilter_(nullptr)
{
    
}

bool SceneRenderer::Start(const AGZ::Config &config, std::string_view configPath)
{
	Clear();
	AGZ::ScopeGuard clearGuard([&]{ Clear(); });
	
	try
	{
		auto &root = config.Root();
		context_ = std::make_unique<Atrc::Mgr::Context>(root, configPath);
		Atrc::Mgr::RegisterBuiltinCreators(*context_);
		
		std::string outputFilename = context_->GetPathInWorkspace(root["outputFilename"].AsValue())
		
		renderer_   = context_->Create<Atrc::Renderer>(root["renderer"]);
		sampler_    = context_->Create<Atrc::Sampler> (root["sampler"]);
		filmFilter_ = context_->Create<Atrc::FilmFilter>(root["film.filter"]);
		
		scene_ = std::make_unique<Atrc::Scene>();
		*scene_ = Atrc::Mgr::SceneBuilder::Build(root, *context_);
		
		Vec2i filmSize = Mgr::Parser::ParseVec2i(root["film.size"]);
		film_ = std::make_unique<Atrc::Film>(filmSize, *filmFilter_);
		reporter_ = std::make_unique<FilmRTReporter>(filmSize.x, filmSize.y);
		
		renderer_->Render(scene_.get(), sampler_.get(), film_.get(), reporter_.get());
	}
	catch(...)
	{
		return false;
	}
	
	clearGuard.Dismiss();
	return true;
}

void SceneRenderer::Stop()
{
    // TODOcffgfgf egg
	AGZ_ASSERT(renderer_);
	renderer_->Stop();
}

bool SceneRenderer::IsRendering() const
{
    return renderer_ != nullptr;
}

bool SceneRenderer::IsCompleted() const
{
    AGZ_ASSERT(IsRendering());
    return renderer_->IsCompleted();
}

void SceneRenderer::Join()
{
    AGZ_ASSERT(IsRendering());
    renderer_->Join(reporter_.get());
}

void Clear()
{
	context_    = nullptr;
	renderer_   = nullptr;
	sampler_    = nullptr;
	filmFilter_ = nullptr;
	
	scene_    = nullptr;
	reporter_ = nullptr;
	film_     = nullptr;
	
	filmSize_ = Vec2i(0, 0);
}