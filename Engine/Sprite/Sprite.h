#pragma once
#include "DirectXCommon.h"
#include "StringUtility.h"
#include "ShaderCompile.h"
#include "CreateResource.h"
#include "GraphicsPipeline.h"
#include "Matrix4x4.h"
#include "Mathfunction.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "Vector2.h"

class Sprite {
public: // メンバ関数

	Sprite() = default;
	~Sprite();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// スプライト生成
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	static Sprite* Create(Vector2 position, Vector4 color = {1,1,1,1});

#pragma region Getter
	// 座標の取得
	const Vector2& GetPosition() const { return position_; }

#pragma endregion 

#pragma region Setter
	// 座標の設定
	void SetPosition(const Vector2& position) { position_ = position; }
	// 色の設定
	void SetColor(const Vector4& color) { *materialData_ = color; }

#pragma endregion

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="v"></param>
	/// <param name="t"></param>
	void Draw(ViewProjection viewProjection,uint32_t texHandle);

private: // メンバ変数

	D3D12_VERTEX_BUFFER_VIEW sVBV_{};
	Resource sResource_ = {};
	WorldTransform worldTransform_ = {};
	Vector2 position_ = {};
	static Sprite* sprite_;
	Vector4* materialData_ = nullptr;
};
