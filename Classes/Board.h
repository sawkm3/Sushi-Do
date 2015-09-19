#pragma once

#include <vector>
#include <utility>
#include <string>

// ネタ
enum NETA {
	// ここシャリ
	NETA_SHARI = 0,
	NETA_GUNKAN,
	// ここからネタ
	NETA_MAGURO,
	NETA_TAMAGO,
	NETA_TAKO,
	NETA_IKA,
	NETA_EBI,
	// ここから軍艦ネタ
	NETA_NEGITORO,
	NETA_UNI,
	// ここからその他
	HOUCHOU,
	SARA,
};
// 寿司
enum SUSHI {
	// ネタ
	MAGURO = 2,
	TAMAGO,
	TAKO,
	IKA,
	EBI,
	NEGITORO,
	// ここから軍艦ネタ
	UNI,
	SUSHI_NUM,
};

// 要求を管理する構造体
class Request
{
public:
	std::vector<std::pair<int, int> > request;
};

class Board
{
public:
	Board(){};
	~Board(){};
	// ボード情報
	std::vector<std::vector<int> > board;
	// 要求リスト
	std::vector<Request> requests;
	// セルの入れ替え
	bool change(std::pair<int, int>, std::pair<int, int>);
	// 寿司ネタを提出する
	// 要求に合ってないなら false を, あっているなら true を返す
	bool submit();
	// ボード情報を渡す
	std::vector<std::vector<int> > getBoard();
	// 要求情報を渡す
	std::vector<Request> getRequest();
	// ファイル名を読み込んで初期化する
	void init(const std::string filename);
	// デバッグ用
	// board をプリントする
	void printBoard() const;
	// requests をプリントする
	void printRequests() const;
	// すでに完成しているネタの, 上と下の座標を求める
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > getComplete();
};

