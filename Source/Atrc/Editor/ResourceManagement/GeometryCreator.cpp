#include <AGZUtils/Utils/Mesh.h>
#include <Atrc/Editor/ResourceManagement/GeometryCreator.h>
#include <Atrc/Editor/FileBrowser.h>
#include <Atrc/Editor/FilenameSlot.h>

namespace
{
    class WavefrontOBJInstance : public GeometryInstance
    {
        std::shared_ptr<GL::VertexBuffer<Vertex>> vtxBuf_;
        AGZ::Mesh::GeometryMeshGroup<float> meshGroup_;
        TFilenameSlot<true> filename_;

        void BuildVertexBufferFromMeshGroup()
        {
            std::shared_ptr<GL::VertexBuffer<Vertex>> buf = std::make_shared<GL::VertexBuffer<Vertex>>();
            std::vector<Vertex> vtxData;

            for(auto &it : meshGroup_.submeshes)
            {
                for(auto &v : it.second.vertices)
                {
                    Vertex nv;
                    nv.pos = v.pos;
                    nv.nor = v.nor;
                    vtxData.push_back(nv);
                }
            }

            buf->InitializeHandle();
            buf->ReinitializeData(vtxData.data(), static_cast<uint32_t>(vtxData.size()), GL_STATIC_DRAW);
            vtxBuf_ = std::move(buf);
        }

        void Clear()
        {
            vtxBuf_ = nullptr;
            meshGroup_.submeshes.clear();
        }

        void LoadWavefrontOBJ(std::string filename)
        {
            Clear();
            AGZ::ScopeGuard clearGuard([&]
            {
                Clear();
                filename_.Clear();
            });

            AGZ::Mesh::WavefrontObj<float> obj;
            if(!obj.LoadFromFile(filename) || obj.name2Obj.empty())
                return;

            meshGroup_ = obj.ToGeometryMeshGroup();
            if(!meshGroup_.submeshes.size())
                return;
            obj.Clear();
            BuildVertexBufferFromMeshGroup();
            clearGuard.Dismiss();
        }

    public:

        using GeometryInstance::GeometryInstance;

        std::shared_ptr<const GL::VertexBuffer<Vertex>> GetVertexBuffer() const override
        {
            return vtxBuf_;
        }

        void Display(ResourceManager&) override
        {
            static FileBrowser fileBrowser("browse .obj", false, "");
            if(filename_.Display(fileBrowser))
                LoadWavefrontOBJ(fileBrowser.GetResult());
        }

        std::vector<std::string> GetSubmeshNames() const override
        {
            std::vector<std::string> ret;
            std::transform(begin(meshGroup_.submeshes), end(meshGroup_.submeshes), std::back_inserter(ret),
                [](auto &it) { return it.first; });
            return ret;
        }

        void Export(const ResourceManager &rscMgr, LauncherScriptExportingContext &ctx) const override
        {
            ctx.AddLine("type = TriangleBVH;");
            ctx.AddLine("filename = \"", filename_.GetExportedFilename(ctx), "\";");
            AGZ_ASSERT(ctx.entityTransform);
            ctx.AddLine("transform = (");
            ctx.IncIndent();
            ctx.AddLine("Translate", AGZ::To<char>(ctx.entityTransform->GetTranslate()), ",");
            ctx.AddLine("RotateZ(Deg(", std::to_string(ctx.entityTransform->GetRotate().z), ")),");
            ctx.AddLine("RotateY(Deg(", std::to_string(ctx.entityTransform->GetRotate().y), ")),");
            ctx.AddLine("RotateX(Deg(", std::to_string(ctx.entityTransform->GetRotate().x), ")),");
            ctx.AddLine("Scale(", std::to_string(ctx.entityTransform->GetScale()), ")");
            ctx.DecIndent();
            ctx.AddLine(");");
        }
    };
}

void RegisterGeometryCreators(ResourceManager &rscMgr)
{
    static const WavefrontOBJCreator iWavefrontOBJCreator;
    rscMgr.AddCreator(&iWavefrontOBJCreator);
}

std::shared_ptr<GeometryInstance> WavefrontOBJCreator::Create(std::string name) const
{
    return std::make_shared<WavefrontOBJInstance>(std::move(name));
}