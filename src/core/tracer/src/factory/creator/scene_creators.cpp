#include <agz/tracer/core/entity.h>
#include <agz/tracer/core/light.h>
#include <agz/tracer/core/scene.h>
#include <agz/tracer/factory/creator/scene_creators.h>
#include <agz/tracer/factory/raw/aggregate.h>
#include <agz/tracer/factory/raw/scene.h>
#include <agz/tracer/utility/logger.h>
#include <agz/utility/string.h>

AGZ_TRACER_FACTORY_BEGIN

namespace scene
{
    
    class DefaultSceneCreator : public Creator<Scene>
    {
    public:

        std::string name() const override
        {
            return "default";
        }

        std::shared_ptr<Scene> create(const ConfigGroup &params, CreatingContext &context) const override
        {
            DefaultSceneParams scene_params;

            if(auto ent_arr = params.find_child_array("entities"))
            {
                if(ent_arr->size() == 1)
                    AGZ_INFO("creating 1 entity");
                else
                    AGZ_INFO("creating {} entities", ent_arr->size());

                for(size_t i = 0; i < ent_arr->size(); ++i)
                {
                    auto &group = ent_arr->at_group(i);
                    if(stdstr::ends_with(group.child_str("type"), "//"))
                    {
                        AGZ_INFO("skip entity with type ending with //");
                        continue;
                    }

                    auto ent = context.create<Entity>(group);
                    scene_params.entities.push_back(ent);
                }
            }

            if(auto group = params.find_child_group("env"))
                scene_params.envir_lights.push_back(context.create<EnvirLight>(*group));

            std::vector<std::shared_ptr<EnvirLight>> nonarea_lights;
            if(auto lht_arr = params.find_child_array("lights"))
            {
                if(lht_arr->size() == 1)
                    AGZ_INFO("creating 1 envir light");
                else
                    AGZ_INFO("creating {} envir lights", lht_arr->size());

                for(size_t i = 0; i < lht_arr->size(); ++i)
                {
                    auto &group = lht_arr->at_group(i);
                    if(stdstr::ends_with(group.child_str("type"), "//"))
                    {
                        AGZ_INFO("skip envir light with type ending with //");
                        continue;
                    }

                    auto lht = context.create<EnvirLight>(group);
                    scene_params.envir_lights.push_back(lht);
                }
            }

            if(auto group = params.find_child_group("aggregate"))
                scene_params.aggregate = context.create<Aggregate>(*group);
            else
                scene_params.aggregate = create_native_aggregate();

            return create_default_scene(scene_params);
        }
    };

} // namespace scene

void initialize_scene_factory(Factory<Scene> &factory)
{
    factory.add_creator(std::make_unique<scene::DefaultSceneCreator>());
}

AGZ_TRACER_FACTORY_END
