#pragma once

#include <vector>
#include <utility>
#include <string>

// �l�^
enum NETA {
	// �����V����
	NETA_SHARI = 0,
	NETA_GUNKAN,
	// ��������l�^
	NETA_MAGURO,
	NETA_TAMAGO,
	NETA_TAKO,
	NETA_IKA,
	NETA_EBI,
	// ��������R�̓l�^
	NETA_NEGITORO,
	NETA_UNI,
	// �������炻�̑�
	HOUCHOU,
	SARA,
};
// ���i
enum SUSHI {
	// �l�^
	MAGURO = 2,
	TAMAGO,
	TAKO,
	IKA,
	EBI,
	NEGITORO,
	// ��������R�̓l�^
	UNI,
	SUSHI_NUM,
};

// �v�����Ǘ�����\����
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
	// �{�[�h���
	std::vector<std::vector<int> > board;
	// �v�����X�g
	std::vector<Request> requests;
	// �Z���̓���ւ�
	bool change(std::pair<int, int>, std::pair<int, int>);
	// ���i�l�^���o����
	// �v���ɍ����ĂȂ��Ȃ� false ��, �����Ă���Ȃ� true ��Ԃ�
	bool submit();
	// �{�[�h����n��
	std::vector<std::vector<int> > getBoard();
	// �v������n��
	std::vector<Request> getRequest();
	// �t�@�C������ǂݍ���ŏ���������
	void init(const std::string filename);
	// �f�o�b�O�p
	// board ���v�����g����
	void printBoard() const;
	// requests ���v�����g����
	void printRequests() const;
	// ���łɊ������Ă���l�^��, ��Ɖ��̍��W�����߂�
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > getComplete();
};

