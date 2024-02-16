#pragma once
#include "IModelState.h"
#include "ModelSphere.h"
#include "Vector2.h"
#include <fstream>
#include <sstream>
#include "ImGuiManager/ImGuiManager.h"

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};

class Model {
public:

	~Model();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(IModelState* state);

	void InitializeObj(const std::string& filename);

	/// <summary>
	/// モデル生成
	/// </summary>
	/// <returns></returns>
	static Model* Create(IModelState* state);

	/// <summary>
	/// Obj
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	static Model* CreateObj(const std::string& filename);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform worldTransform, ViewProjection viewprojection, uint32_t texHandle);

	/// <summary>
	/// Objの描画
	/// </summary>
	void Draw(WorldTransform worldTransform, ViewProjection viewprojection);

	// setter
	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }

	// ライティングのsetter
	int32_t SetEnableLighting(int32_t enableLighting) { return materialData_->enableLighting = enableLighting; }
	// 色のsetter
	Vector4 SetColor(Vector4 color) { return materialData_->color = color; }


private:

	/// <summary>
	/// Objファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// mtlファイルを読む
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="filename"></param>
	/// <returns></returns>
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

private: // メンバ変数

	IModelState* state_ = nullptr; // モデルのパターン
	ModelData modelData_;
	Resource resource_ = {};
	D3D12_VERTEX_BUFFER_VIEW objVertexBufferView_{};
	Material* materialData_ = nullptr;
	DirectionalLight* directionalLightData_ = nullptr;
	uint32_t texHandle_ = 0;
};


