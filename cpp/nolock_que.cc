template <typename _Tp>
class CQue
{
public
	CQue(int size);
	~CQue();
	int Enq(_Tp& e);
	int Deq();
	_Tp* Get();

private:
	int m_nSize;
	int m_nNum;
	int m_nPos;
	int64_t m_nIndex;
	_Tp* m_pData;
};

template <typename _Tp>
CQue::CQue(int size)
	: m_nSize(size), m_nNum(0)
{
	m_pData = new _Tp[m_nSize];
}

CQue::~CQue()
{
	delete [] m_pData;
}

template <typename _Tp>
int Enq(_Tp& e)
{
	if (__sync_add_and_fetch(&m_nNum, 1) > m_nSize) {
		__sync_sub_and_fetch(&m_nNum, 1);
		return -1;
	}

	if (__sync_fetch_and_or(&m_nIndex, ))
}
