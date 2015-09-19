#include "Board.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

// セルの入れ替え
bool Board::change(std::pair<int, int> p, std::pair<int, int> q) {
	int n = board.size(), m = board[0].size();
	assert(0 <= p.first && p.first < n && 0 <= p.second && p.second < m);
	assert(0 <= q.first && q.first < n && 0 <= q.second && q.second < m);
	if (abs(p.first - q.first) + abs(p.second - q.second) != 1) return false;
	swap(board[p.first][p.second], board[q.first][q.second]);
	return true;
}

// 寿司ネタを提出する
// 要求に合ってないなら false を, あっているなら true を返す
bool Board::submit() {
	int n = board.size(), m = board[0].size();
	// 要求リストの作成
	vector<int> required(SUSHI_NUM);
	for (Request req : requests) {
		for (pair<int, int> p : req.request) {
			required[p.first] += p.second;
		}
	}
	// ボードを全探索して要求リストを消化する
	// 3 段のやつ
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] >= NETA_NEGITORO) continue;
			if (board[i + 1][j] == NETA_SHARI && board[i + 2][j] == SARA) {
				required[board[i][j]]--;
			}
		}
	}
	// 4 段のやつ
	for (int i = 0; i <= n - 4; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] != HOUCHOU) continue;
			if (board[i+1][j] < NETA_NEGITORO || board[i+1][j] > NETA_UNI) continue;
			if (board[i + 2][j] == NETA_GUNKAN && board[i + 3][j] == SARA) {
				required[board[i + 1][j]]--;
			}
		}
	}
	for (int i = 0; i < SUSHI_NUM; i++) {
		if (required[i] > 0) return false;
	}
	return true;
}

// ボード情報を渡す
std::vector<std::vector<int> > Board::getBoard() {
	return board;
}
// 要求情報を渡す
std::vector<Request> Board::getRequest() {
	return requests;
}

void Board::init(const std::string filename) {
	ifstream ifs(filename);
	assert(!ifs.fail());
	// ボードの入力
	int n, m;
	ifs >> n >> m;
	board.resize(n);
	for (int i = 0; i < n; i++) board[i].resize(m);
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		ifs >> board[i][j];
	}
	// 要求の入力
	int num;
	ifs >> num;
	requests.resize(num);
	for (int i = 0; i < num; i++) {
		int t;
		ifs >> t;
		vector<pair<int, int> > ps;
		for (int j = 0; j < t; j++) {
			int a, b;
			ifs >> a >> b;
			ps.emplace_back(a, b);
		}
		requests[i].request = ps;
	}
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > Board::getComplete() {
	int n = board.size(), m = board[0].size();
	vector<pair<pair<int, int>, pair<int, int> > > ret;
	// 3 段のやつ
	for (int i = 0; i <= n - 3; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] >= NETA_NEGITORO) continue;
			if (board[i + 1][j] == NETA_SHARI && board[i + 2][j] == SARA) {
				pair<int, int> p(i, j), q(i + 2, j);
				ret.emplace_back(p, q);
			}
		}
	}
	// 4 段のやつ
	for (int i = 0; i <= n - 4; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] != HOUCHOU) continue;
			if (board[i + 1][j] < NETA_NEGITORO || board[i + 1][j] > NETA_UNI) continue;
			if (board[i + 2][j] == NETA_GUNKAN && board[i + 3][j] == SARA) {
				pair<int, int> p(i, j), q(i + 3, j);
				ret.emplace_back(p, q);
			}
		}
	}
	return ret;
}

void Board::printBoard() const {
	int n = board.size(), m = board[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void Board::printRequests() const {
	vector<int> required(SUSHI_NUM);
	for (Request req : requests) {
		for (pair<int, int> p : req.request) {
			required[p.first] += p.second;
		}
	}
	for (int i = 0; i < SUSHI_NUM; i++) {
		cout << i << " " << required[i] << endl;
	}
}