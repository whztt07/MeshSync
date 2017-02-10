﻿#pragma once

class MeshSyncClientMaya
{
public:
    enum class TargetScope
    {
        Unknown,
        Selection,
        All,
    };

    MeshSyncClientMaya(MObject obj);
    ~MeshSyncClientMaya();

    void onIdle();
    void onSceneUpdate();

    void setServerAddress(const char *v);
    void setServerPort(uint16_t v);
    void setAutoSync(bool v);

    void notifyUpdateTransform(MObject obj);
    void notifyUpdateMesh(MObject obj);
    void sendScene();
    void sendSelected();
    void importScene();

private:
    bool isAsyncSendInProgress() const;
    void registerCallbacks();
    void removeCallbacks();
    int getMaterialID(MUuid uid);
    void extractMeshData(ms::Mesh& dst, MObject src);
    void kickAsyncSend();

private:
    using ClientMeshes = std::vector<ms::MeshPtr>;
    using HostMeshes = std::map<int, ms::MeshPtr>;
    using ExistRecords = std::map<std::string, bool>;
    using Materials = std::vector<ms::Material>;
    using Joints = std::vector<ms::JointPtr>;

    MObject m_obj;
    MFnPlugin m_iplugin;
    bool m_auto_sync = true;

    std::vector<MCallbackId> m_cids;
    std::vector<MUuid> m_material_id_table;
    std::vector<MUuid> m_object_id_table;
    std::vector<MObject> m_mtransforms;
    std::vector<MObject> m_mmeshes;

    ms::ClientSettings m_client_settings;
    float m_scale_factor = 1.0f;
    ClientMeshes m_client_meshes;
    HostMeshes m_host_meshes;
    Joints m_joints;
    Materials m_materials;
    ExistRecords m_exist_record;
    std::future<void> m_future_send;
    bool m_pending_send_meshes = false;
};
