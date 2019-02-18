#pragma once

#include <Atrc/Editor/ResourceManagement/ResourceManager.h>
#include <Atrc/Editor/EditorCore.h>
#include <Atrc/Editor/LauncherScriptExportingContext.h>

class LauncherScriptExporter
{
    ResourceManager &rscMgr_;
    LauncherScriptExportingContext &ctx_;

public:

    LauncherScriptExporter(ResourceManager &rscMgr, LauncherScriptExportingContext &ctx);

    std::string Export() const;
};

class LauncherScriptImporter
{
    template<typename TResource>
    const std::string &GetCompletePoolName()
    {
        static const std::string ret = std::string("pool.") + TResource::GetPoolName();
        return ret;
    }

    // ֱ�Ӹ��ݲ�������һ������
    // paramsһ����������
    template<typename TResource>
    std::shared_ptr<TResource> CreateResourceFromScratch(ResourceManager &rscMgr, std::string instanceName, const AGZ::ConfigGroup &root, const AGZ::ConfigGroup &params)
    {
        auto &type = params["type"].AsValue();
        auto instance = rscMgr.GetCreatorManager<TResource>().Create(rscMgr, type, std::move(instanceName));
        instance->Import(rscMgr, root, params);
        return instance;
    }

    // ������ȡ��һ�������еĶ���
    // �������һ���������ã�����ֱ�Ӵ���
    // ����������Ѿ����ˣ���ֱ�ӷ���
    // ���򣬸��ݲ��������������������
    template<typename TResource>
    std::shared_ptr<TResource> GetResourceInPool(ResourceManager &rscMgr, const AGZ::ConfigGroup &root, const std::string &rscName)
    {
        auto &pool = rscMgr.GetPool<TResource>();
        if(auto instance = pool.GetByName(rscName))
            return instance;

        auto &poolName = GetCompletePoolName<TResource>();
        std::string paramPath = poolName + "." + rscName;
        auto newInstance = CreateResourceFromScratch<TResource>(rscMgr, rscName, root, root[paramPath].AsGroup());
        pool.AddInstance(newInstance);

        return newInstance;
    }

    // ����ĳ�����͵ĳ����е���������
    template<typename TResource>
    void ImportFromPool(const AGZ::ConfigGroup &root, ResourceManager &rscMgr)
    {
        auto &children = root[GetCompletePoolName<TResource>()].AsGroup().GetChildren();
        for(auto &it : children)
            GetResourceInPool<TResource>(rscMgr, root, it.first);
    }

    const AGZ::ConfigGroup &GetFinalNonReferenceParam(const AGZ::ConfigGroup &root, const AGZ::ConfigNode &node)
    {
        if(auto pVal = node.TryAsValue())
            return GetFinalNonReferenceParam(root, root[*pVal]);

        auto &grp = node.AsGroup();
        if(grp["type"].AsValue() == "Reference")
            return GetFinalNonReferenceParam(root, root[grp["name"].AsValue()]);

        return grp;
    }

public:

    // ȡ��һ��resource����
    // ����ö�����һ��Ŀ��Ϊ�����ж�������ã���ô�������Ҫ
    // ��������ö�����һ�����ã��ݹ�ش���������ú�Ľ��
    // ����ԭ���ò���������������
    template<typename TResource>
    std::shared_ptr<TResource> GetResourceInstance(ResourceManager &rscMgr, const AGZ::ConfigGroup &root, const AGZ::ConfigNode &params)
    {
        if(auto pVal = params.TryAsValue()) // ���ֱ�Ȼ������
        {
            auto &poolName = GetCompletePoolName<TResource>();
            if(AGZ::StartsWith(*pVal, poolName)) // ����һ����Գ����еĶ��������
                return GetResourceInPool<TResource>(rscMgr, root, pVal->substr(poolName.length()));

            // ��Բ��ڳ����е����ã��ݹ�ص�������
            auto &referencedParams = root[*pVal];
            return GetResourceInstance<TResource>(rscMgr, root, referencedParams);
        }

        auto &grp = params.AsGroup();
        if(grp["type"].AsValue() == "Reference") // ��һ����������
        {
            auto &name = grp["name"].AsValue();

            auto &poolName = GetCompletePoolName<TResource>();
            if(AGZ::StartsWith(name, poolName)) // ����һ����Գ����еĶ��������
                return GetResourceInPool<TResource>(rscMgr, root, name.substr(poolName.length()));

            // ��Բ��ڳ����е����ã��ݹ�ص�������
            auto &referencedParams = root[name];
            return GetResourceInstance<TResource>(rscMgr, root, referencedParams);
        }

        // ֱ�Ӵ�����������
        return CreateResourceFromScratch<TResource>(rscMgr, "", root, grp);
    }

    void Import(const AGZ::ConfigGroup &root, EditorData *data, std::string_view scriptPath);
};
